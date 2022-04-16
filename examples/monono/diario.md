# Monono

He tenido una idea de remake de Monono: 

* Organizar el mapa más verticalmente, y dividirlo en etapas.
* Hay que subir y ganar etapas.
* Caer desde muy alto te hace perder una vida.
* Si te matan, se reinicia la etapa.
* Meter tiles que se desmoronan al pisarlos y otras cosas de verticalidad.

## 20220414

Una de las ideas de este juego es preparar por fin el tema del script para recortar spritesets con cells de diferentes tamaños que sea capaz de exportar un binario compuesto y el `spriteset_mappings.h` correspondiente.

Primero empezaré muy fácilmente: el script se compondrá de sentencias de este tipo

```
	CUT x, y, w, h, ox, oy
	CUTP x, y, w, h, ox, oy
```

La diferencia es que cut pilla las medidas en "cells" y la segunda en pixels. En realidad deberían valer para lo mismo porque en rigor sólo admitiremos sprites de 1x1, 2x2 o 2x3 cells. Los demás deberían cascar un error. `ox` y `oy` siepre son desplazamientos en pixels teniendo en cuenta que para el motor las entidades siempre se considerarán de 16x16 y su origen está en la esquina superior izquierda.

Tengo que ver como hacer con FreeBASIC para sacar cosas por STDERR en lugar de STDOUT (sobre todo si el `> nul` de windows solo para STDOUT, pero esto es irme por las ramas un poco).

El tema es que cada CUT debería cortar un sprite, añadirlo al binario, y meter una entrada en un array de descriptores de sprites que luego se recorrerá para generar un `spriteset_mappings.h` correcto.

La estructura podría conenter:

```
	Type TypeSpriteEntry
		w As Integer
		h As Integer
		ox As Integer
		oy As Integer
	End Type
```

Lo primero será ver como va mkts y si tiene una función que recorte un sólo sprite y que sea la que se llama desde las funciones que recortan spritesets homegeneos, y si no, encapsularla debidamente.

## 20220515 

Como sospechaba, no está encapsulado el código que recorta un único sprite, así que será lo primero que haga. Sería sacar el código de `cpcDoSprites` en una función con este aspecto:

```bas
	Sub cpcCutSimpleSprite (img As Any Ptr, x As Integer, y As Integer, _
		hMetaPixels As Integer, wMeta As Integer)

		'' hMetaPixels = sprite height in pixels,
		'' wMeta = sprite width in patterns.

		'' This function will write (hMetaPixels * wMeta * 2) bytes to the main binary

		Dim As Integer xa
		Dim As Integer yy
		Dim As Integer xx

		For yy = 0 To hMetaPixels - 1
			xa = x
			For xx = 0 To wMeta - 1
				mbWrite cpcGetBitmapFrom (xa, y + yy, img)
				mbWrite cpcGetBitmapFrom (xa + 2 * brickMultiplier, y + yy, img)
				xa = xa + patternWidthInPixels
			Next xx
		Next yy

	End Sub
```

Con esto hecho, solo se trata de hacer un sencillo parser que vaya tirando bytes al binario llamando a esta función y añadiendo entradas en el array `spriteMetaData` que se indexa con `spriteMetaIndex`.

Puedo añadir el `mode=spriteScript` complementado con un parámetro `script=XXX` con la ruta al script con los comandos para recortar el spriteset. 

He visto que ya hay un modo scripted que, sinceramente, no sé para qué lo puse (¿algo de MK3?) pero da igual.

Tengo que implementar las funciones `doSpriteScript (img As Any Ptr, spriteScript As String)` y `generateMixedMappings (mappingsFn As String)` y lo tendré hecho.

Los mappings referencian no solo a las direcciones de memoria de cada sprite en el binario, sino a qué rutinas de CPCRSLIB debe llamarse para pintar cada uno. Mi idea es tratar de permitir dimensiones arbitrarias aunque no existan rutinas en CPCRSLIB, más que nada con vistas al futuro.

Veamos cuál fue la nomenclatura que me inventé en tiempos para las diferentes rutinas, siendo wMeta y hMeta el tamaño en patrones (o celdas):

`invFunc` = `cpc_PutSpTileMap` & W & `x` & H
`updfunc` = `cpc_PutTrSp` & W & `x` & H & `TileMap2b` & PPS, donde

* Si estamos en Modo 0, W = wMeta * 4, 
* Si estamos en Modo 1, W = wMeta * 8,
* H = hMeta * 8
* PPS valdrá `Px` si tenemos modo 0 pixel perfect o `PxM1` si tenemos modo 1 pixel perfect

No dejan de referirse a número de pixels. Lo que puedo hacer es precalcular todo esto a la hora de hacer los recortes. Tengo que tener en cuenta `pixelperfectm1` y `brickMultiplier` (que puede valer 2) a la hora de calcular las posiciones de recorte y los anchos. Espero no liarme mucho :-)

## 20220416

Lo he ejecutado con este script tonto para recortar los sprites de Monono:

```spt
	# Player: 8 cells, 16x24
	cut 0, 0, 2, 3, 0, -8
	cut 2, 0, 2, 3, 0, -8
	cut 4, 0, 2, 3, 0, -8
	cut 6, 0, 2, 3, 0, -8
	cut 8, 0, 2, 3, 0, -8
	cut 10, 0, 2, 3, 0, -8
	cut 12, 0, 2, 3, 0, -8
	cut 14, 0, 2, 3, 0, -8

	# Standard enems: 8 cells, 16x16
	cut 0, 3, 2, 2, 0, 0
	cut 2, 3, 2, 2, 0, 0
	cut 4, 3, 2, 2, 0, 0
	cut 6, 3, 2, 2, 0, 0
	cut 8, 3, 2, 2, 0, 0
	cut 10, 3, 2, 2, 0, 0
	cut 12, 3, 2, 2, 0, 0
	cut 14, 3, 2, 2, 0, 0
```

¡Y parece que funciona! Bueno, al menos los mappings los ha exportado bien... Los gráficos si eso ya me lo creeré cuando lo vea en acción.

Aquí entramos en lo de siempre: muchas ideas pero pocas ganas o más bien ganas de sobra pero poca energía y menos tiempo. Quería hacer monono de nuevo. Ahora recuerdo que quizá el mapa de la versión de NES lo podría aprovechar, en principio, y luego modificar. Tenía cosas interesantes, si mal no recuerdo... Voy a echarle un ojaldrio.

Remember que en Monono NES se podía saltar sobre los enemigos, aunque no hicieran daño. En principio puedo replicar esto para ver que todo funciona y luego ya modificar o tirar y hacer de nuevo.

El mapa de NES es de 16x12. En las reducciones automaticas se pierde mucho y luego hay que ir retocando... quizá sea mejor ponerse y copiarlo mano.

