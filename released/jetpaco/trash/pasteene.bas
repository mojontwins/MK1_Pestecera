Dim As Integer fIn1, fIn2, fOut

Dim As Integer i, j, mapPants
Dim As uByte d, mapW1, mapH1, mapW2, mapH2, nEnems
Dim As uByte t, a, b, xx, yy, mn, x, y, s1, s2, xy
Dim As Integer typeCounters (255)
Dim As Integer enTypeCounters (255)
Dim As String Dummy

Print "This program pastes enems0 and enems1, enems0 goes on top of enems1."
Print "If you have different needs make another shitty script."

fIn1 = FreeFile
Open "enems0.ene" For Binary As #fIn1 
fIn2 = FreeFile
Open "enems1.ene" For Binary As #fIn2
fOut = FreeFile
Open "enems.ene" For Binary As #fOut

dummy = Input (256, fIn1)
Get #fIn1, , d: mapW1 = d
Get #fIn1, , d: mapH1 = d
Get #fIn1, , d: Get #fIn1, , d
Get #fIn1, , d: nEnems = d

Put #fOut, , dummy

dummy = Input (256, fIn2)
Get #fIn2, , d: mapW2 = d
Get #fIn2, , d: mapH2 = d
Get #fIn2, , d: Get #fIn2, , d
Get #fIn2, , d: nEnems = d

' Write new headers

d = mapW1: Put #fOut, , d 
d = mapH1 + mapH2: Put #fOut, , d 
d = 15: Put #fOut, , d 
d = 10: Put #fOut, , d 
d = nEnems: Put #fOut, , d 

' Write enemies from enems0

For i = 1 To mapW1*mapH1
	For j = 1 To nEnems
		Get #fIn1, , t
		Get #fIn1, , x
		Get #fIn1, , y
		Get #fIn1, , xx
		Get #fIn1, , yy 
		Get #fIn1, , mn
		Get #fIn1, , s1
		Get #fIn1, , s2

		Put #fOut, , t 
		Put #fOut, , x
		Put #fOut, , y
		Put #fOut, , xx
		Put #fOut, , yy
		Put #fOut, , mn
		Put #fOut, , s1
		Put #fOut, , s2
	Next j
Next i

' Write enemies from enems1

For i = 1 To mapW2*mapH2
	For j = 1 To nEnems
		Get #fIn2, , t
		Get #fIn2, , x
		Get #fIn2, , y
		Get #fIn2, , xx
		Get #fIn2, , yy 
		Get #fIn2, , mn
		Get #fIn2, , s1
		Get #fIn2, , s2

		Put #fOut, , t 
		Put #fOut, , x
		Put #fOut, , y
		Put #fOut, , xx
		Put #fOut, , yy
		Put #fOut, , mn
		Put #fOut, , s1
		Put #fOut, , s2
	Next j
Next i

' Write hotspots from enems0 

For i = 1 To  mapW1*mapH1
	Get #fIn1, , x
	Get #fIn1, , y
	Get #fIn1, , t

	Put #fOut, , x 
	Put #fOut, , y 
	Put #fOut, , t
Next

' Write hotspots from enems1

For i = 1 To  mapW2*mapH2
	Get #fIn2, , x
	Get #fIn2, , y
	Get #fIn2, , t

	Put #fOut, , x 
	Put #fOut, , y 
	Put #fOut, , t
Next

Print "Hecho "
