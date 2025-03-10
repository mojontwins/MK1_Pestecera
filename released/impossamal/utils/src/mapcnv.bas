' Map converter
' Cutrecode by na_th_an

' Estos programas son tela de optimizables, pero me da igual porque tengo un dual core.
' �OLE!

Function procrust (n As Integer, l As Integer) As String
	Dim s As String
	s = Ltrim (Str (n))
	If Len (s) < l Then
		s = Space (l - Len (s)) & s
	End If
	Return s
End Function

Sub WarningMessage ()
End Sub

sub usage () 
	Print "** USO **"
	Print "   MapCnv archivo.map archivo.h ancho_mapa alto_mapa ancho_pantalla alto_pantalla tile_cerrojo [packed] [fixmappy] [errors_as_arrays]"
	Print
	Print "   - archivo.map : Archivo de entrada exportado con mappy en formato raw."
	Print "   - archivo.h : Archivo de salida"
	Print "   - ancho_mapa : Ancho del mapa en pantallas."
	Print "   - alto_mapa : Alto del mapa en pantallas."
	Print "   - ancho_pantalla : Ancho de la pantalla en tiles."
	Print "   - alto_pantalla : Alto de la pantalla en tiles."
	Print "   - tile_cerrojo : N� del tile que representa el cerrojo."
	Print "   - packed : Escribe esta opci�n para mapas de la churrera de 16 tiles."
	Print "   - fixmappy : Escribe esta opci�n para arreglar lo del tile 0 no negro"
	Print "   - errors_as_arrays: Saca los errores de rango como tres arrays np, x, y"
	Print
	Print "Por ejemplo, para un mapa de 6x5 pantallas para MTE MK1:"
	Print
	Print "   MapCnv mapa.map mapa.h 6 5 15 10 15 packed"
end sub

Function inCommand (spec As String) As Integer
	Dim As Integer res, i

	i = 0: res = 0

	Do
		If Command (i) = "" Then Exit Do
		If Command (i) = spec Then res = -1: Exit Do
		i = i + 1
	Loop

	Return res
End Function

Dim As Integer map_w, map_h, scr_w, scr_h, bolt
Dim As Integer x, y, xx, yy, i, j, f, packed, ac, ct, fixmappy, scr_x, scr_y, n_pant
Dim As Byte d
Dim As String o
Dim As Integer errorsAsArrays
Dim As Integer errorsNp(255), errorsX(255), errorsY(255), errorsT(255), errorsIdx

Type MyBolt
	np As Integer
	x As Integer
	y As Integer
End Type

Dim As MyBolt Bolts (100)

WarningMessage ()

if 	Command (1) = "" Or _
	Command (2) = "" Or _
	Val (Command (3)) <= 0 Or _
	Val (Command (4)) <= 0 Or _
	Val (Command (5)) <= 0 Or _
	Val (Command (6)) <= 0 Or _
	Val (Command (7)) <= 0 Then
	
	usage ()
	end
End If

map_w = Val (Command (3))
map_h = Val (Command (4))
scr_w = Val (Command (5))
scr_h = Val (Command (6))
bolt = Val (Command (7))

If InCommand ("packed") then
	packed = 1
else
	packed = 0
end if

If InCommand ("fixmappy") Then
	fixmappy = -1
Else
	fixmappy = 0
End If

errorsAsArrays = InCommand ("errors_as_arrays")

Dim As Integer BigOrigMap (map_h * scr_h - 1, map_w * scr_w - 1)

' Leemos el mapa original

f = FreeFile
Open Command (1) for binary as #f

For y = 0 To (map_h * scr_h - 1)
	For x = 0 To (map_w * scr_w - 1)
		get #f , , d
		If fixmappy Then d = d - 1
		If packed = 1 Then		
			If d >= 16 Then 
				' calculate screen number
				scr_x = x \ scr_w 
				scr_y = y \ scr_h
				n_pant = scr_y * map_w + scr_x 
				If Not errorsAsArrays Then
					Print "Warning! out of bounds tile " & d & " @ " & n_pant & " (" & (x Mod scr_w) & ", " & (y Mod scr_h) & ") -> wrote 0"
				Else
					errorsNp (errorsIdx) = n_pant 
					errorsX  (errorsIdx) = (x Mod scr_w)
					errorsY  (errorsIdx) = (y Mod scr_h)
					errorsT  (errorsIdx) = d
					errorsIdx = errorsIdx + 1
				End If
				d = 0
			End If
		End If
		BigOrigMap (y, x) = d
	Next x
Next y

close f

' Construimos el nuevo mapa mientras rellenamos el array de cerrojos

open Command (2) for output as #f

print #f, "// Mapa.h "
print #f, "// Generado por MapCnv de la churrera"
print #f, "// Copyleft 2010 The Mojon Twins"
print #f, " "

print #f, "unsigned char mapa [] = {"

i = 0

for yy = 0 To map_h - 1
	for xx = 0 To map_w - 1
		o = "    "
		ac = 0
		ct = 0
		for y = 0 to scr_h - 1
			for x = 0 to scr_w - 1
				
				if BigOrigMap (yy * scr_h + y, xx * scr_w + x) = bolt then
					Bolts (i).x = x
					Bolts (i).y = y
					Bolts (i).np = yy * map_w + xx
					i = i + 1
				end if
				
				if packed = 0 then
					o = o & "0x" & hex (BigOrigMap (yy * scr_h + y, xx * scr_w + x), 2)
					if yy < map_h - 1 Or xx < map_w - 1 Or y < scr_h -1 Or x < scr_w -1 then
						o = o & ", "
					end if
				else
					if ct = 0 then
						ac = BigOrigMap (yy * scr_h + y, xx * scr_w + x) * 16
					else
						ac = ac + BigOrigMap (yy * scr_h + y, xx * scr_w + x) 
						o = o & "0x" & Hex (ac, 2)
						
						if yy < map_h - 1 Or xx < map_w - 1 Or y < scr_h - 1 Or x < scr_w - 1 then
							o = o & ", "
						end if
					end if
					ct = 1 - ct
				end if
				
			next x
		next y		
		print #f, o
	next xx
	if yy < map_h - 1 then print #f, "    "
next yy
print #f, "};"

print #f, " "

' Escribimos el array de cerrojos
print #f, "#define MAX_CERROJOS " + trim(str(i))
print #f, " "
print #f, "typedef struct {"
print #f, "    unsigned char np, x, y, st;"
print #f, "} CERROJOS;"
print #f, " "
if i > 0 Then
	print #f, "CERROJOS cerrojos [MAX_CERROJOS] = {"
	
	for j = 0 to i - 1
		o = "    {" + trim(str(bolts(j).np)) + ", " + trim(str(bolts(j).x)) + ", " + trim(str(bolts(j).y)) + ", 0}"
		if j < i - 1 then o = o + ","
		print #f, o
	next j
	
	print #f, "};"
else
	print #f, "CERROJOS *cerrojos;"
end if
print #f, " "
close f

if packed = 0 then 
	Print "Se escribi� mapa.h con " + trim(str(map_h*map_w)) + " pantallas (" + trim(str(map_h*map_w*scr_h*scr_w)) + " bytes)."
else
	Print "Se escribi� mapa.h con " + trim(str(map_h*map_w)) + " pantallas empaquetadas (" + trim(str(map_h*map_w*scr_h*scr_w / 2)) + " bytes)."
end if
Print "Se encontraron " + trim(str(i)) + " cerrojos."
print " "

If errorsAsArrays Then
	Print "Errors as arrays"
	Print "unsigned char _np [] = {";
	For i = 0 To errorsIdx - 1
		Print procrust (errorsNp (i), 3) & ", ";
	Next i
	Print "};"

	Print "unsigned char _t [] = {";
	For i = 0 To errorsIdx - 1
		Print procrust (errorsT (i), 3) & ", ";
	Next i
	Print "};"

	Print "unsigned char _x [] = {";
	For i = 0 To errorsIdx - 1
		Print procrust (errorsX (i), 3) & ", ";
	Next i
	Print "};"

	Print "unsigned char _y [] = {";
	For i = 0 To errorsIdx - 1
		Print procrust (errorsY (i), 3) & ", ";
	Next i
	Print "};"

End If