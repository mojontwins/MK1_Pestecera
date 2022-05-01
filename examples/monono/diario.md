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

## 20220418

Voy a ir probando el juego aunque solo haya hecho unas cuantas pantallas (6), como en los viejos tiempos. Por lo pronto he tenido que restaurar el código de `PLAYER_CUMULATIVE_JUMP` que había desaparecido totalmente. Lo siguiente es cambiar `compile.bat` para convertir `spriteset.png` usando `spriteset.spt` así:

```cmd
	..\..\..\src\utils\mkts_om.exe platform=cpc cpcmode=%cpc_gfx_mode% pal=..\gfx\pal.png mode=spritescript script=..\gfx\spriteset.spt in=..\gfx\spriteset.png out=..\bin\sprites.bin mappings=assets\spriteset_mappings.h pixelperfectm1 silent > nul
```

¡También he visto que faltaban las rutinas de 16x24 en Modo 1 al pixel en CPCRSLIB! A meterlas.

## 20220428

Había una terrible miseria que tenía más que ver con cómo el nuevo z88dk generaba código que otra cosa, pero me ha llevado siglos arreglarlo.

Hecho esto, y tras un par de tweaks, tengo el mono saltando. Ha habido que añadir una animación custom en `my/custom_animation.h` (activando `PLAYER_CUSTOM_ANIMATION` en `config.h`: 

```c
	if (p_killme) {
		gpit = 3;
	} else if (possee || p_gotten) {
		if (p_vx == 0) gpit = 0;
		else {
			gpit = ((gpx + 4) >> 3) & 3;
			if (gpit == 3) gpit = 1;
		}
	} else if (p_vy < 0) {
		gpit = 2;
	} else if (p_vy >= (PLAYER_MAX_VY_SALTANDO/6)) {
		gpit = 0;
	} else gpit = 1;

	gpit += (p_facing ? 0 : 4);

	sp_sw [SP_PLAYER].sp0 = (int) (sm_sprptr [gpit]);
```

Lo siguente que hay que conseguir es que las plataformitas pisables se rompan. Puedo hacerlo de varias formas. Lo primero que hay que hacer de todos modos es activar `BREAKABLE_WALLS`.

Como no tenemos muchas historias que controlar, podemos marcar estos tiles levantando el bit 4 del comportamiento. Como son plataformas, serían 4|16 = 20. El tile que usaremos como "intermedio" deberán tener el mismo comportamiento, para que se sigan rompiendo.

Configuraremos el motor así:


```c
	#define BREAKABLE_WALLS 					// Breakable walls
	#define BREAKABLE_WALLS_LIFE		2		// N+1 = Amount of hits to break wall
	//#define BREAKABLE_WALLS_BROKEN 	30 		// Use this tile for a broken wall, 0 if not def.
	#define BREAKABLE_WALLS_BREAKING 	24 		// Use this tile while the wall is breaking (if defined)
```

Esto permitirá cierto margen hasta que se rompan del todo.

La colisión sería hacia abajo (pisar), por lo que añadiremos el código en `my/ci/bg_collision/obstacle_down.h`. Cuando se hacen estas cosas, es interesante saber estos datos:

* El código se añade al principio del todo, justo tras detectar la colisión. Aún no se ha modificado nada: ni se ha ajustado al jugador, ni se ha detenido. Si haces `break` no se ejecutará nada de esto.
* `gpx` y `gpy` son las coordenadas del jugador en pixels y aún no se han ajustado (estamos colisionando). Se ajustarán luego.
* (`cx1`, `cy1`) y (`cx2`, `cy2`) son las coordenadas de tile de los puntos del cuadro de colisión que se han comprobado. `at1` y `at2` son los atributos de los tiles implicados (que pueden ser el mismo, cuidado). Si hemos llegado a este punto es porque `at1` o `at2` representan un obstáculo (tienen levantado el bit 3) o, en el caso de la colisión hacia abajo en vista lateral, una plataforma (bit 2).

Sabiendo esto podríamos escribir:

```c
	// Detect breakable platforms

	if (at1 == 20) {
		_x = cx1; _y = cy1; break_wall ();
	} 

	// If we are stepping over TWO different platforms
	if (cx1 != cx2 && at2 == 20) {
		_x = cx2; _y = cy1; break_wall ();
	}
```

No va del todo fino y tengo que ver por qué. Parece que en ocasiones la última rompesión no registra colisión suficiente para el salto - o eso o tengo un problema de carrera.

Otra cosa que ocurre es que los tiles se presentan rotos con el mismo gráfico hasta romperse del todo. Como les he puesto 2 de energía, lo suyo sería tener dos gráficos para que se rompan. Para poder hacer esto tendré que hacer un par de perivueltas:

- Los gráficos que se rompen son el 24 y el 25.
- Al iniciarse la pantalla, el buffer de "daño" de los tiles está a 0 para cada casilla. Al golpear la primera vez se pone en 1, y la segunda vez en 2. A la siguiente, se rompen.
- Mirando el código en `engine/breakable.h` vemos que el tile *breaking* se imprime *antes* de incrementar el daño, por lo que el valor del daño a la hora de imprimir el tile será 0 o 1. 
- Para conseguir que eso se refleje en los gráficos, nos basta por tanto con hacer esto en `my/config.h` (esto es una de las cosas pro de MK1 que aprendes únicamente mirando estos documentos):

```c
	#define BREAKABLE_WALLS_BREAKING (brk_buff [gpaux] + 24)
```

De esa forma al primer golpe se imprimirá el tile 24 y al segundo el 25. Nos tenemos que asegurar que el comportamiento de ambos tiles es plataforma + breakable, o sea, 20.

Nos hemos dado cuenta además de que tal y como está las plataformas se rompen con solo pisarlas, aunque estemos parados sobre otro obstáculo y la tengamos bajo un pie. Por eso nos hemos inventado esta tosca aunque eficiente solución:

```c
	// my/ci/bg_collision/obstacle_down.h	

	if (p_vy > PLAYER_G) {
		if (at1 == 20) {
			_x = cx1; _y = cy1; break_wall ();
		} 

		// If we are stepping over TWO different platforms
		if (cx1 != cx2 && at2 == 20) {
			_x = cx2; _y = cy1; break_wall ();
		}
	}

```

## Colisión con pinchos custom

La colisión con pinchos que trae MK1 no nos vale para este juego. Vamos a cambiarla para que los pinchos solo colisionen por abajo y cuando estemos cayendo, porque si no es imposible salir de los pinchos. Luego en el diseño de niveles enmascararemos esto un poco no permitiendo al jugador entrar en pinchos lateralmente.

Para ello primero activamos `CUSTOM_EVIL_TILE_CHECK`. Esto desactiva todo el sistema de tile malo pero incluye el código de `my/ci/custom_evil_tile_check.h`.  La llamada a esta función se hace después de todo el movimiento y la colisión en ambos ejes, por lo que sólo deberemos emplear esta técnica en casos muy sencillos.

Nuestra idea es detectar cuando `p_vy > 0` (cayendo) en los puntos (gpx+4, gpy+15) y (gpx+11, gpy+15). Lo vamos a hacer medio en ensamble aprovechando que es muy sencillo y que el código para este tipo de tareas tontas que genera z88dk suele ser un poco malo.

