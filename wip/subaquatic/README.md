# Subaquatic

Port para MK1 Pestecé de Subaquatic.

## El mapa

En el original tenemos un mapa de 7x5 pantallas de 13x9 tiles. Lamentablemente no tenemos los archivos de mappy originales, así que tendré que extraer el mapa del binario, y luego desordenar los tiles de las pantallas para construir un .MAP raw.

Luego eso lo voy a cargar como imagen en Photoshop, lo voy a estirar al tamaño churrera (de 91x45 tiles a 105x50), lo exportaré de nuevo como RAW, y trataré de abrirlo con Mappy, a ver qué pasa.

- Exporté el mapa, 4095 bytes desde $7409.
- Escribí un sencillo script para reordenarlo.

```bas
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
```

- Lo abrí como RAW, 8 bits, 1 canal, 91x45 en Photoshop
- Estiré a 105x50, nearest neighbour
- Guardé como RAW de nuevo.
- Cargué en mappy y puse tileset

VOIE LA!

