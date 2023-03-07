''
'' This program will shrink a C64 map (16x10) to a CPC/ZX map (15x10)
'' of course this conversion is LOSSY and you'll have to retouch the map.
''

'' I'll try and make this a bit intelligent just as an exercise and 'cause I'm
'' mildly bored. I mean, I will try to select which column has to go in
'' each screen based upon complexity.

'' Let's say that the first and last columns are untouched. From the rest, let's
'' select that which is least complex and delete it.

'' Let's work with REAL data, I mean, let's feed actual behaviour data.
'' Complexity = the sum of changes from tile behaviours 0, 1, 4 and 8.

#include "cmdlineparser.bi"
#include "mtparser.bi"

Sub usage
	Print "MapsrinkerC64toCPC v0.1.20220722 shrinks a C64 16x10 map to CPC/ZX 15x10"
	Print "usage:"
	Print "$ MapsrinkerC64toCPC in=input.map out=output.map size=w,h behs=<comma separated list> [verbose]"
End Sub

' Vars
Dim As Integer f, w, h, i, j, x, y, xx, yy, tidx, nPant, maxPants, prev
Redim As uByte myMap (0, 0, 0)
Redim As uByte outputMap (0, 0, 0)
Dim As uByte d
Dim As Integer onlyWidthExtrude, sizeT, module

Dim As String mandatory (3) => { "in", "out", "size", "behs" }
Dim As Integer behs (63), coords (9), complexity (15), order (15)
Dim As Integer verbose

sclpParseAttrs
If Not sclpCheck (mandatory ()) Then usage: End

parseCoordinatesString sclpGetValue ("behs"), behs ()
parseCoordinatesString sclpGetValue ("size"), coords ()

verbose = (sclpGetValue ("verbose") <> "")

w = coords (0): h = coords (1)
maxPants = w*h
Redim myMap (maxPants - 1, 15, 9)
Redim outputMap (maxPants - 1, 14, 9)

' read map
f = Freefile
Open sclpGetValue ("in") For Binary as #f

' Read maxPants screens worth of tiles (16x10=160 per screen)
For tidx = 0 To maxPants * 160 - 1
	' Screen location
	x = (tidx \ 16) Mod w
	y = tidx \ (w * 160)
	nPant = y * w + x
	
	' Screen coordinates
	xx = tidx Mod 16
	yy = (tidx \ (16 * w)) Mod 10
	
	' Read byte
	Get #f, , d
	
	' Write to mem
	myMap (nPant, xx, yy) = d
Next tidx

Close f

' Process every screen
For nPant = 0 To maxPants - 1

	' Calculate the complexity of all coluns 1-14
	
	complexity (0) = 99: complexity (15) = 99 	' Never chose these

	For x = 1 To 14
		prev = behs (myMap (nPant, x, 0))
		If verbose Then Print Hex (prev, 1);
		complexity (x) = 0
		For y = 1 To 9
			If verbose Then Print Hex (behs (myMap (nPant, x, y)), 1);
			If behs (myMap (nPant, x, y)) <> prev Then	
				complexity (x) = complexity (x) + 1 
				prev = behs (myMap (nPant, x, y))
			End If 			
		Next y
		If verbose Then Print "="; complexity (x)
	Next x

	' Bubble sort the complexity array 
	For x = 0 To 15: order (x) = x: Next x

	For i = 0 To 14
		For j = 0 To 14 - i
			If complexity (j) > complexity (j + 1) Then
				Swap complexity (j), complexity (j + 1)
				Swap order (j), order (j + 1)
			End If 
		Next j 
	Next i

	If verbose Then 
		Print "Least complex line = " & order (0) & " (" & complexity (0) & ")"
		Print
	End If

	' Copy to new map skipping two least complex lines

	xx = 0
	For x = 0 To 15
		If x <> order (0) Then
			For y = 0 To 9
				outputMap (nPant, xx, y) = myMap (nPant, x, y)
			Next y
			xx = xx + 1
		End If
	Next x

Next nPant

' Write results
f = Freefile
Open sclpGetValue ("out") For Binary As #f 

sizeT = 150: module = 10 

For tidx = 0 To maxPants * sizeT - 1 
	' Screen location
	x = (tidx \ 15) Mod w
	y = tidx \ (w * sizeT)
	nPant = y * w + x
	
	' Screen coordinates
	xx = tidx Mod 15
	yy = (tidx \ (15 * w)) Mod module
		
	Put #f, , outputMap (nPant, xx, yy)
Next tidx

Close 

Print "MapsrinkerC64toCPC v0.1.20220722, " & sclpGetValue ("in") & " shrinked into " & sclpGetValue ("out") & ". " & maxPants & " screens processed."
