Const scrW=13
Const scrH=9
Const mapW=7
Const mapH=5

Dim As uByte full_map (scrH * mapH - 1, scrW * mapW - 1)
Dim As integer fIn, fOut, x, y, xx, yy
Dim As uByte u

'' Read all screens

fIn = FreeFile
Open "mapa.pan" For Binary As #fIn
While Not Eof (fIn)
	For y = 0 To mapH - 1
		For x = 0 To mapW - 1
			For yy = 0 To scrH - 1
				For xx = 0 To scrW - 1
					Get #fIn, , full_map (y * scrH + yy, x * scrW + xx)
	Next xx, yy, x, y
Wend
Close #fIn

'' Write full map
fOut = FreeFile
Open "mapa.raw" For Binary As #fOut
For y = 0 To scrH * mapH - 1
	For x = 0 To scrW * mapW - 1
		Put #fOut, , full_map (y, x)
	Next x
Next y
Close #fOut

