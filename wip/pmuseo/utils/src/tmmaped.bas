' tmmaped.bas
#include once "crt.bi"
#include once "windows.bi"

#include "cmdlineparser.bi"
#include "mtparser.bi"

Const LEFTBUTTON = 1 
Const MIDDLEBUTTON = 4 
Const RIGHTBUTTON = 2 
Const SHOWMOUSE = 1
Const HIDEMOUSE = 0

#define CS_LEFT 	&H01
#define CS_RIGHT 	&H02
#define CS_UP 		&H04
#define CS_DOWN 	&H08
#define CS_SAVE 	&H10
#define CS_GRID 	&H20
#define CS_PLUS		&H40
#define CS_MINUS 	&H80 
#define CS_ESC 		&H100

Redim Shared As uByte map (0,0)
Dim Shared As Integer consoleW, consoleH 			' Console size
Dim Shared As Integer mW, mH
Dim Shared As Integer scrW, scrH
Dim Shared As Integer behsEnable
Dim Shared As Integer behsMode
Dim Shared As Integer behs (63)

Sub usage 
	Print "usage: "
	Print "$ tmmaped in=file.map size=w,h scrsize=w,h [behs=...]"
	Print "size w, h in screens"
	Print "scrsize w, h in tiles"
	Print "behs is a comma separated list to up to 64 behs for tiles"
End Sub

Function Window_Event_Close() As Integer
	Return (Inkey = Chr(255, 107))
End Function

Function readCursors As Integer
	Dim As Integer res 
	res = 0
	If (GetAsyncKeyState (VK_LEFT) And &H8000) <> 0 	Then res = res Or CS_LEFT
	If (GetAsyncKeyState (VK_RIGHT) And &H8000) <> 0	Then res = res Or CS_RIGHT
	If (GetAsyncKeyState (VK_UP) And &H8000) <> 0 		Then res = res Or CS_UP
	If (GetAsyncKeyState (VK_DOWN) And &H8000) <> 0 	Then res = res Or CS_DOWN
	If (GetAsyncKeyState (&H53) And &H8000) <> 0 		Then res = res Or CS_SAVE
	If (GetAsyncKeyState (&H47) And &H8000) <> 0 		Then res = res Or CS_GRID
	If (GetAsyncKeyState (VK_OEM_MINUS) And &H8000) <> 0 Then res = res Or CS_MINUS
	If (GetAsyncKeyState (VK_OEM_PLUS) And &H8000) <> 0 Then res = res Or CS_PLUS
	If (GetAsyncKeyState (VK_ESCAPE) And &H8000) <> 0 	Then res = res Or CS_ESC

	Return res
End Function

Sub loadMap (fileName As String)
	Dim As Integer fIn 
	Dim As Integer x, y, xc, yc
	Dim As uByte d

	Redim As uByte map (mW*(ScrW+1), mH*(ScrH+1))

	fIn = Freefile
	Open fileName For Binary As #fIn
	x = 0: y = 0: xc = 0: yc = 0
	While Not Eof (fIn)
		Get #fIn, , d
		map (x, y) = d 
		x = x + 1
		xc = xc + 1
		If xc Mod scrW = 0 Then x = x + 1
		If x = mW*(ScrW+1) Then 
			x = 0
			y = y + 1
			yc = yc + 1
			If yc Mod scrH = 0 Then y = y + 1
			If y = mH*(ScrH+1) Then Exit While
		End If
	Wend
	Close fIn
End Sub

Sub saveMap (fileName As String)
	Dim As Integer fOut 
	Dim As Integer x, y, xc, yc 
	Dim As uByte d 

	Name fileName As fileName & ".bak"
	fOut = Freefile
	Open fileName For Binary As #fOut

	Print "SAVING ";
	For y = 0 To mH*(ScrH+1)-1
		For x = 0 To mW*(ScrW+1)-1
			If x Mod (ScrW+1) <> ScrW And y Mod (ScrH+1) <> ScrH Then
				d = map (x, y)
				Put #fOut, , d
			End If

			If x Mod (ScrW+1) = ScrW And y Mod (ScrH+1) = ScrH Then
				Print ".";
			End If
		Next x
	Next y
	Close #fOut
End Sub

Function behsStr (beh as Integer) As String
	Dim As String res

	' Basic behs
	If beh = 0 Then 
		return "  "
	ElseIf beh = 1 Then
		return "**"
	ElseIf beh = 4 Then 
		return "~~"
	ElseIf beh = 8 Then
		return "XX"
	ElseIf beh = 10 Then
		return "()"
	ElseIf beh = 128 Then
		return "!!"
	Else
		' Combinations
		res = " "
		If (beh And 1) Then res = "*"
		If (beh And 4) Then res = "~"
		If (beh And 8) Then res = "X"

		If (beh And 2) Then 
			res = res & "h"
		ElseIf (beh And 16) Then 
			res = res & "%"
		ElseIf (beh And 128) Then 
			res = res & "!"
		Else 
			res = res  & "?"
		End If

		return res
	End If
End Function

Sub displayMap (offX As Integer, offY As Integer)
	Dim As Integer x, y, xx, yy, xc, yc
	Dim As String conc
	Dim As uByte d

	yy = offY: yc = yy Mod (scrH+1)
	
	' Code is so unrolled for speed
	If behsMode Then
		For y = 5 To consoleH-2
			If yc = scrH Then 
				conc = String (consoleW-2, "-")
			Else
				conc = ""
				xx = offX
				xc = xx Mod (scrW+1)
				For x = 1 To consoleW-2	Step 2
					If xc = scrW Then
						conc = conc & "]["
					Else					
						If xx >= 0 And xx < (mW*(scrW+1)) And yy >= 0 And yy < (mH*(scrH+1)) Then
							conc = conc & behsStr (behs (map (xx, yy)))
						Else
							conc = conc & ".."
						End If 
					End If
					xc = xc + 1: If xc = scrW+1 Then xc = 0
					xx = xx + 1
				Next x
			End If
			Locate y, 1 : Print conc & "]";
			yc = yc + 1: If yc = scrH+1 Then yc = 0
			yy = yy + 1
		Next y
	Else
		For y = 5 To consoleH-2
			If yc = scrH Then 
				conc = String (consoleW-2, "-")
			Else
				conc = ""
				xx = offX
				xc = xx Mod (scrW+1)
				For x = 1 To consoleW-2	Step 2
					If xc = scrW Then
						conc = conc & "]["
					Else					
						If xx >= 0 And xx < (mW*(scrW+1)) And yy >= 0 And yy < (mH*(scrH+1)) Then
							d = map (xx, yy)
							If d = 0 Then
								conc = conc & "  "
							Else
								conc = conc & Hex (d, 2)
							End If					
						Else
							conc = conc & ".."
						End If 
					End If
					xc = xc + 1: If xc = scrW+1 Then xc = 0
					xx = xx + 1
				Next x
			End If
			Locate y, 1 : Print conc & "]";
			yc = yc + 1: If yc = scrH+1 Then yc = 0
			yy = yy + 1
		Next y
	End If
End Sub 

Sub setupScreen 
	Dim As Integer i, x, y 
	'' Palette
	i = 0
	For y = 0 To 3 
		For x = 0 To 15
			Locate 1 + y, 2 + (x * 3)
			If behsMode Then Print behsStr(behs(i)) Else Print Hex(i, 2)
			i = i + 1
		Next x
	Next y

	Locate 1, 50: Print "[S] SAVE [ESC] EXIT [G] TOGGLE"
End Sub

Dim As Integer mX, mY, msW, mB, mC 		' Mouse
Dim As Integer r
Dim As String mandatory (2) = { "in", "size", "scrsize" }
Dim As Integer coords (64)
Dim As Integer keys, keysTF
Dim As Integer offX, offY, ooffX, ooffY
Dim As Integer psX, psY, pmX, pmY
Dim As Integer x, y, i
Dim As String psXS, psYS
Dim As Integer curT, ocurT

r = Width ()
consoleW = r And &HFFFF
consoleH = r ShR 16

sclpParseAttrs

If Not sclpCheck (mandatory ()) Then 
	usage
	End
End If

parseCoordinatesString sclpGetValue ("size"), coords ()
mw = coords (0): mH = coords (1)

parseCoordinatesString sclpGetValue ("scrsize"), coords ()
scrW = coords (0): scrH = coords (1)

behsMode = 0
behsEnable = 0
If sclpGetValue ("behs") <> "" Then
	behsEnable = -1
	parseCoordinatesString sclpGetValue ("behs"), coords ()
	For i = 0 To 63
		If coords(i) <> -1 Then behs (i) = coords (i) Else behs (i) = 0
	Next i
End If

loadMap sclpGetValue ("in")

Cls

offX = 0: offY = 0
ooffX = &HFF: ooffY = &HFF

setupScreen

curT = 0: ocurT = 1
 
Do
	If ocurT <> curT Then
		x = 1 + (ocurT And 15) * 3: y = 1 + (ocurT \ 16)
		Locate y, x: Print " ": Locate y, x + 3: Print " "
		x = 1 + (curT And 15) * 3: y = 1 + (curT \ 16)
		Locate y, x: Print "[": Locate y, x + 3: Print "]"
		ocurT = curT
	EndIf

	If offX <> ooffX Or offY <> ooffY Then 
		displayMap offX, offY
		ooffX = offX: ooffY = offY
	End If

	'' Keys status
	keysTF = keys
	keys = readCursors						' Keys pressed
	keysTF = (keysTF Xor keys) And keys 	' Keys pressed THIS frame

	'' Move around map
	If (keys And CS_LEFT)  Then offX = offX - 1
	If (keys And CS_RIGHT) Then offX = offX + 1
	If (keys And CS_UP)    Then offY = offY - 1
	If (keys And CS_DOWN)  Then offY = offY + 1

	'' Save
	If (keysTF And CS_SAVE) Then
		Cls
		saveMap sclpGetValue ("in")
		Cls
		setupScreen
		ooffX = &HFFFF
	End If

	'' TOGGLE
	If (keysTF And CS_GRID) And behsEnable Then
		behsMode = Not behsMode
		ooffX = &HFFFF
		setupScreen
	End If

	'' Calculate map positions!
	x = mX \ 2 + offX	
	psX = x Mod (scrW+1) 
	pmX = x \ (scrW+1)

	y = (mY-4) + offY
	psY = y Mod (scrH+1) 
	pmY = y \ (scrH+1)
	
	'' Read mouse
	r = GetMouse (mX, mY, msW, mB, mC)

	If mB Then 
		'' Select a tile
		If mX < 48 And mY < 4 Then
			curT = ((mX-2) \ 3) + mY*16
		End If

		'' Paint / Unpaint
		If mY > 4 And mY < consoleH-1 Then
			If mB And 1 Then
				map (pmX*(scrW+1) + psX, pmY*(scrH+1) + psY) = curT 
			ElseIf mB And 2 Then
				map (pmX*(scrW+1) + psX, pmY*(scrH+1) + psY) = 0			
			End If
			ooffX = &HFFFF
		End If
	End If

	'' Coordinates info
	If psX < scrW And psY < scrH Then 
		psXS = Hex (psX, 2) 
		psYS = Hex (psY, 2)
	Else 
		psXS = "  "
		psYS = "  "
	End If
	Locate consoleH, 1
	Print "(" & pmX & ", " & pmY & ") - (" & psXS & ", " & psYS & ")   ";

	If keys And CS_ESC Or Window_Event_Close Then 
		Exit Do
	End If
Loop
Cls
