' Modification.
' This version will move some enemies coordinates x1, y1, x2, y2.

' If X > 7 -> X -= 1;

Sub strToArr128 (mstr As String, arr () As uByte)
	Dim As Integer i
	For i = 0 To 127
		arr (i) = 0
	Next i
	For i = 1 To Len (mstr)
		arr (i - 1) = Asc (Mid (mstr, i, 1))
	Next i
End Sub

Dim as Integer xy, x, y, t, f1, f2, i, j
Dim as uByte d, arr (127), map_w, map_h, nenems

? "v0.3 20220629 [C64 16x10 -> CPC/ZX 15x10]"

' enshrinker.bas
If Command (4) = "" Then ?"enshrinker enems.ene output.ene mappy.bmp mapa.map [2bytes]":?:End

' read / write header

f1 = Freefile
Open Command (1) For Binary as #f1
f2 = Freefile
Open Command (2) For Binary as #f2

' Dummy read 256 bytes
For i = 1 To 256
	Get #f1, , d
Next i

' Write correct filenames

strToArr128 Command (4), arr ()
For i = 0 To 127
	Put #f2, , arr (i)
Next i
strToArr128 Command (3), arr ()
For i = 0 To 127
	Put #f2, , arr (i)
Next i

' Read/modify headers

' map_w, map_h, scr_w, scr_h, nenems
get #f1, , map_w
put #f2, , map_w
get #f1, , map_h
put #f2, , map_h
get #f1, , d
d = 16: put #f2, , d
get #f1, , d
d = 10: put #f2, , d
get #f1, , nenems
put #f2, , nenems

' Read / Modify / Write enems

For i = 1 To (nenems * map_w * map_h)
	' t x y xx yy n s1 s2
	get #f1, , d ' t
	put #f2, , d
	?"T:";d;" ";

	get #f1, , d ' x
	If d > 7 Then d = d-1
	put #f2, , d
	?"X:";d;" ";
	
	get #f1, , d ' y	
	put #f2, , d
	?"Y:";d;" ";
	
	get #f1, , d ' xx
	If d > 6 Then d = d + 1
	put #f2, , d
	?"XX:";d;" ";
	
	get #f1, , d ' yy
	'If d > 5 Then d = d + 2
	put #f2, , d
	?"YY:";d;" ";
	
	get #f1, , d ' n
	put #f2, , d
	get #f1, , d ' s1
	put #f2, , d
	get #f1, , d ' s2
	put #f2, , d
	?
Next i

' Read / Write hotspots

If Command (5) = "2bytes" Then
	For i = 1 To (map_w * map_h)
		get #f1, , d: xy = d
		x = xy Shr 4
		y = xy And 15
		get #f1, , d: t = d
		print Hex (x, 2) & " " & hex (y, 2) & " " & hex (t, 2) & ".. ";
		Print "[" & Hex (i - 1, 2) & "]: (" & x & ", " & y & ") -> ";
		If x > 7 Then x = x -1
		Print "(" & x & ", " & y  & ")."
		xy = (x Shl 4) Or (y And 15)
		'd = xy: put #f2, , d
		d = x: put #f2, , d
		d = y: put #f2, , d
		d = t: put #f2, , d
	Next i
Else
	For i = 1 To (map_w * map_h)
		'get #f1, , d: xy = d
		'x = xy Shr 4
		'y = xy And 15
		get #f1, , d: x = d
		get #f1, , d: y = d
		get #f1, , d: t = d
		print Hex (x, 2) & " " & hex (y, 2) & " " & hex (t, 2) & ".. ";
		Print "[" & Hex (i - 1, 2) & "]: (" & x & ", " & y & ") -> ";
		If x > 7 Then x = x -1
		Print "(" & x & ", " & y  & ")."
		xy = (x Shl 4) Or (y And 15)
		'd = xy: put #f2, , d
		d = x: put #f2, , d
		d = y: put #f2, , d
		d = t: put #f2, , d
	Next i
End If

Close

? "DONE!"
