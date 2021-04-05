# Guía de inicio rápido

En esta guía te contamos cómo montar un proyecto. Para ilustrarlo, vamos a portar Jet Paco a CPC. Veremos cómo montar el proyecto, recrear los gráficos en Modo 0, importar mapa y enemigos, hacer una OGT, replicar la configuración, y obtener una cinta lista para jugar.

Esto no es un sustituto del tutorial. Puede ser un documento muy util si ya conocías MK1 para ZX Spectrum y quieres aprender a usar la Pestecera. También puede servir para portar tu juego favorito MK1 a CPC.

## Antes de empezar

Lo primero es coger la carpeta `/src` y copiarla completa en otro sitio, y acto seguido cambiarle el nombre. Por ejemplo, para la conversión de **Jet Paco** le he cambiado el nombre a `src` por `jetpaco`, obteniendo esta estructura de directorios:

```
	jcastano@POR133 MINGW64 /d/git/MK1_Pestecera/examples (master)
	$ tree -d jetpaco
	jetpaco
	|-- bin
	|-- dev
	|   |-- assets
	|   |-- engine
	|   |   `-- enem_mods
	|   |-- loader
	|   |-- mainloop
	|   `-- my
	|       |-- ci
	|       |   `-- bg_collision
	|       `-- wyz
	|-- enems
	|-- gfx
	|-- map
	|-- mus
	|   `-- wyz
	`-- script

	17 directories
```

Una vez hecho esto, editamos `dev/compile.bat` y establecemos el nombre del juego y el modo gráfico modificando el valor de estas dos variables al principio del archivo:

```cmd
	@echo off

	if [%1]==[help] goto :help

	set game=jet_paco
	set cpc_gfx_mode=0

	[...]
```

## Los nuevos gráficos

La Pestecera soporta tanto modo 0 como modo 1. Puedes emplear el modo que más te guste. En este ejemplo haremos gráficos en modo 0. 

Antes de empezar, debes asegurarte de trabajar con los colores correctos. Como esto siempre está sujeto a implementación, hemos añadido en `/env` un archivo `.png` que contiene los 27 colores de la paleta, demás de un archivo `.act` de Photoshop y un archivo `.pal` para Paintshop Pro o Aseprite.

![Paleta CPC](https://raw.githubusercontent.com/mojontwins/MK1/master/docs/wiki-img/cpc_pal.png)

Si tu programa no soporta ninguno de estos formatos puedes cargar el jpg e ir picando cada color desde ahí, o crear la paleta a mano en tu editor siguiendo esta tabla:

|R|G|B
|===|===|===
|0|0|0
|0|0|128
|0|0|255
|128|0|0
|128|0|128
|128|0|255
|255|0|0
|255|0|128
|255|0|255
|0|128|0
|0|128|128
|0|128|255
|128|128|0
|128|128|128
|128|128|255
|255|128|0
|255|128|128
|255|128|255
|0|255|0
|0|255|128
|0|255|255
|128|255|0
|128|255|128
|128|255|255
|255|255|0
|255|255|128
|255|255|255

El conversor de gráficos de la pestecera es una evolución del viejo `mkts_om` que hemos venido empleando en paquetes tan dispares como `MK3_OM` o `AGNES SG-1000` y es capaz de procesar gráficos 1:1 (en los que cada pixel de la imagen es un "ladrillo" del CPC) o gráficos 2:1 (en los que cada dos píxeles de la imagen hacen un ladrillo del CPC). Trabaja con lo que mejor te venga. Recuerda que paquetes como Photoshop o Aseprite te permiten configurar una vista de 2:1 sobre imagenes normales para trabajar más cómodamente (los píxeles se muestran a doble de ancho).

### Paletas

Por defecto y sin tocar nada, tendrás que elegir una paleta de 16 colores para todos los elementos del juego y podrás elegir otra diferente para la pantalla de carga. El conversor `mkts_om` necesita una paleta para funcionar en un formato muy específico: como un archivo .png de 16x1 píxels en el que cada píxel representa un color de la paleta. El orden de los píxeles en la imagen es importante: el de más a la izquierda definirá la pluma 0 y el de más a la derecha la 15. Esto es importante sobre todo con los sprites: en los sprites, **el color que represente la pluma 0 será tomado como color transparente**.

Para los juegos en modo 1 sólo tendremos que colorear los 4 primeros píxeles de las imagenes.

Una vez decididas las dos paletas (que bien pueden ser una sola) las almacenaremos en el directorio `gfx/` como `pal.png` (para la paleta principal) y `pal_loading.png` para la paleta de la pantalla de carga.

### Pantallas fijas

Al igual que en `MK1` de toda la vida, tenemos tres o cuatro pantallas fijas. Las tres primeras deberán ser de 256x192 píxels en modo 1 o 128x192 píxels en modo 0 y sólo debe usar los colores definidos en `gfx/pal.png`.

* `title.png` es la pantalla de título, que además debe contener el marco de juego si activas la macro `DIRECT_TO_PLAY` en `dev/my/config.h`. 
![title.png](https://raw.githubusercontent.com/mojontwins/MK1/master/docs/wiki-img/jet_paco/title.png)

* `marco.png` es la pantalla del marco de juego, con espacio para los marcadores. Si hemos vamos a usar `DIRECT_TO_PLAY` no la necesitamos. 

* `ending.png` es la pantalla que sale cuando el jugador gana el juego (la pantalla del final). 

![ending.png](https://raw.githubusercontent.com/mojontwins/MK1/master/docs/wiki-img/jet_paco/title.png)

Finalmente, tendremos:

* `loading.png`, la pantalla de carga, que tiene que ser de 320x200 píxels en modo 1 o 160x200 píxels en modo 0 y sólo debe usar los colores definidos en `gfx/pal_loading.png`.

![loading.png](https://raw.githubusercontent.com/mojontwins/MK1/master/docs/wiki-img/jet_paco/loading.png)

### La fuente

* `font.png` contendrá la fuente y debe ser un archivo de 256x32 píxels en modo 1 o 128x32 píxels en modo 0 y debe contener los 64 caracteres correspondientes a los códigos ASCII del 32 al 95. Debe usar los colores de `gfx/pal.png`:

![font.png](https://raw.githubusercontent.com/mojontwins/MK1/master/docs/wiki-img/jet_paco/font.png)

### El tileset

* `work.png` contendrá los 48 tiles del tileset, sobre el que aplicarán las mismas restricciones y características que en **MTE MK1** para **ZX Spectrum**. El archivo deberá medir 256x48 píxels en modo 1 o 128x48 píxels en modo 0

![work.png](https://raw.githubusercontent.com/mojontwins/MK1/master/docs/wiki-img/jet_paco/work.png)

### El spriteset

* `work.png` contendrá los gráficos que necesitemos para representar los sprites de nuestro juego. En la configuración básica serán 16 cells de 16x16 píxels en modo 1 u 8x16 píxels en modo 0 (pueden ser más y pueden ser de 24 píxels de alto). El conversor espera 8 cells por fila, así que nuestro archivo deberá tener 128 píxels de ancho en modo 1 o 64 en modo 0. Se puede hacer juegos con gráficos de diferente tamaño (16 o 24 píxels de alto), pero eso es algo que no trataremos en esta guía.

La configuración básica es la misma que en **MTE MK1** para **ZX Spectrum**, pudiendo hacer los añadidos y personalizaciones que necesites mediante inyección de código y diferentes configuraciones que no trataremos en esta guía.

Ten en cuenta que la pluma 0 deberá emplearse para definir qué zonas del sprite deben ser transparentes. Recuerda que es el primer color que aparece en `gfx/pal.png`. En este caso, el amarillo pálido:

![work.png](https://raw.githubusercontent.com/mojontwins/MK1/master/docs/wiki-img/jet_paco/work.png)

### Sprites extra

En `gfx/` hay dos archivos gráficos más de tipo sprite (con lo que debes prestar atención a usar la prima 0 para marcar qué píxeles son transparentes) que puedes (debes) modificar al gusto:

* `sprites_bullet.png` contiene el gráfico empleado para representar las balas. Será de 8x8 píxels en modo 1 u 4x8 en modo 0.

* `sprites_extra.png` contiene el gráfico de la explosión. **Deberá tener el mismo tamaño que el cell más grande de tu spriteset** si estás empleando un set con diferentes tamaños. En la configuración más básica, deberá ser, como el resto de los cells para sprites, de 16x16 en modo 1 u 8x16 en modo 0.

### Convirtiendo los nuevos gráficos

La conversión de los gráficos se efectúa en su sección de `dev/compile.bat`, al igual que ocurriá en **MTE MK1** para **ZX Spectrum**. Si estás empleando la configuración básica no tendrás que cambiar nada. De todos modos, voy a detallar linea por linea lo que estamos haciendo.

```cmd
	..\utils\mkts_om.exe platform=cpc cpcmode=%cpc_gfx_mode% pal=..\gfx\pal.png mode=chars in=..\gfx\font.png out=..\bin\font.bin silent > nul
```

La primera linea utiliza `mkts_om` en modo `chars` para convertir la fuente. En ausencia de más parámetros, el conversor procesará el archivo de entrada completo. Nótese que el parámetro `cpcmode` toma el valor de la variable `%cpc_gfx_mode%` que definimos al principio. La salida es `bin/font.bin`, que es lo que espera el motor.

```cmd
	..\utils\mkts_om.exe platform=cpc cpcmode=%cpc_gfx_mode% pal=..\gfx\pal.png mode=strait2x2 in=..\gfx\work.png out=..\bin\work.bin silent > nul
```

Seguidamente se procesa el tileset en modo `strait2x2`. Al igual que con la fuente, la ausencia de más parámetros implica que se procesará la imagen completa. La salida es `bin/work.bin`, que es lo que espera el motor.

```cmd
	..\utils\mkts_om.exe platform=cpc cpcmode=%cpc_gfx_mode% pal=..\gfx\pal.png mode=sprites in=..\gfx\sprites.png out=..\bin\sprites.bin mappings=assets\spriteset_mappings.h silent > nul
	..\utils\mkts_om.exe platform=cpc cpcmode=%cpc_gfx_mode% pal=..\gfx\pal.png mode=sprites in=..\gfx\sprites_extra.png out=..\bin\sprites_extra.bin silent > nul
	..\utils\mkts_om.exe platform=cpc cpcmode=%cpc_gfx_mode% pal=..\gfx\pal.png mode=sprites in=..\gfx\sprites_bullet.png out=..\bin\sprites_bullet.bin metasize=1,1 silent > nul
```

Estas tres lineas procesan los sprites: el archivo con el spriteset principal `gfx/sprites.png`, que se convertirá a `bin/sprites.bin`, la explosión `gfx/sprites_extra.png` a `bin/sprites_extra.bin` y el proyectil `gfx/sprites_bullet.png` a `bin/sprites_bullet.bin`.

Nótese que se define el tamaño del gráfico que estamos recortando con el parámetro `metasize`. Por defecto, `mkts_om` considera `2,2`. Para sprites más altos (24 filas de pixels) deberíamos especificar manualmente `2,3`. Para los proyectiles se especifica `1,1`. Como quizá hayas adivinado, las medidas son el ancho y el alto en bloques, siendo cada bloque de 8x8 en modo 1 o 4x8 en modo 0.

El parámetro `mappings` es para que el conversor genere una serie de estructuras que el motor necesita para conocer el offset de cada sprite en el binario y las funciones que debe emplear para pintarlo. Dichas estructuras deberán generarse en `dev/assets/spriteset_mappings.h`.

```cmd
	..\utils\png2scr.exe ..\gfx\title.png ..\gfx\title.scr > nul

	..\utils\mkts_om.exe platform=cpc cpcmode=%cpc_gfx_mode% pal=..\gfx\pal.png mode=superbuffer in=..\gfx\marco.png out=..\bin\marco.bin silent > nul
	..\utils\mkts_om.exe platform=cpc cpcmode=%cpc_gfx_mode% pal=..\gfx\pal.png mode=superbuffer in=..\gfx\ending.png out=..\bin\ending.bin silent > nul
	..\utils\mkts_om.exe platform=cpc cpcmode=%cpc_gfx_mode% pal=..\gfx\pal.png mode=superbuffer in=..\gfx\title.png out=..\bin\title.bin silent > nul
	..\utils\apultra.exe ..\bin\title.bin ..\bin\titlec.bin > nul
	..\utils\apultra.exe ..\bin\marco.bin ..\bin\marcoc.bin > nul
	..\utils\apultra.exe ..\bin\ending.bin ..\bin\endingc.bin > nul

	..\utils\mkts_om.exe platform=cpc mode=pals in=..\gfx\pal.png prefix=my_inks out=assets\pal.h silent > nul
```

