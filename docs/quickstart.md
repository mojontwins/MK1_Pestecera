# Guía de inicio rápido

En esta guía te contamos cómo montar un proyecto. Para ilustrarlo, vamos a portar Jet Paco a CPC. Veremos cómo montar el proyecto, recrear los gráficos en Modo 0, importar mapa y enemigos, hacer una OGT, replicar la configuración, y obtener una cinta lista para jugar.

Esto no es un sustituto del tutorial. Puede ser un documento muy util si ya conocías MK1 para ZX Spectrum y quieres aprender a usar la Pestecera. También puede servir para portar tu juego favorito MK1 a CPC.

## Antes de empezar

Lo primero es coger el directorio `/src` y copiarla completa en otro sitio, y acto seguido cambiarle el nombre. Por ejemplo, para la conversión de **Jet Paco** le he cambiado el nombre a `src` por `jetpaco`, obteniendo esta estructura de directorios:

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

![Paleta CPC](https://raw.githubusercontent.com/mojontwins/MK1_Pestecera/master/docs/wiki-img/cpc_pal.png)

Si tu programa no soporta ninguno de estos formatos puedes cargar el jpg e ir picando cada color desde ahí, o crear la paleta a mano en tu editor siguiendo esta tabla:

|R|G|B
|---|---|---
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

![title.png](https://raw.githubusercontent.com/mojontwins/MK1_Pestecera/master/docs/wiki-img/jet_paco/title.png)

* `marco.png` es la pantalla del marco de juego, con espacio para los marcadores. Si hemos vamos a usar `DIRECT_TO_PLAY` no la necesitamos. 

* `ending.png` es la pantalla que sale cuando el jugador gana el juego (la pantalla del final). 

![ending.png](https://raw.githubusercontent.com/mojontwins/MK1_Pestecera/master/docs/wiki-img/jet_paco/title.png)

Finalmente, tendremos:

* `loading.png`, la pantalla de carga, que tiene que ser de 320x200 píxels en modo 1 o 160x200 píxels en modo 0 y sólo debe usar los colores definidos en `gfx/pal_loading.png`.

![loading.png](https://raw.githubusercontent.com/mojontwins/MK1_Pestecera/master/docs/wiki-img/jet_paco/loading.png)

### La fuente

* `font.png` contendrá la fuente y debe ser un archivo de 256x32 píxels en modo 1 o 128x32 píxels en modo 0 y debe contener los 64 caracteres correspondientes a los códigos ASCII del 32 al 95. Debe usar los colores de `gfx/pal.png`:

![font.png](https://raw.githubusercontent.com/mojontwins/MK1_Pestecera/master/docs/wiki-img/jet_paco/font.png)

### El tileset

* `work.png` contendrá los 48 tiles del tileset, sobre el que aplicarán las mismas restricciones y características que en **MTE MK1** para **ZX Spectrum**. El archivo deberá medir 256x48 píxels en modo 1 o 128x48 píxels en modo 0

![work.png](https://raw.githubusercontent.com/mojontwins/MK1_Pestecera/master/docs/wiki-img/jet_paco/work.png)

### El spriteset

* `sprites.png` contendrá los gráficos que necesitemos para representar los sprites de nuestro juego. En la configuración básica serán 16 cells de 16x16 píxels en modo 1 u 8x16 píxels en modo 0 (pueden ser más y pueden ser de 24 píxels de alto). El conversor espera 8 cells por fila, así que nuestro archivo deberá tener 128 píxels de ancho en modo 1 o 64 en modo 0. Se puede hacer juegos con gráficos de diferente tamaño (16 o 24 píxels de alto), pero eso es algo que no trataremos en esta guía.

La configuración básica es la misma que en **MTE MK1** para **ZX Spectrum**, pudiendo hacer los añadidos y personalizaciones que necesites mediante inyección de código y diferentes configuraciones que no trataremos en esta guía.

Ten en cuenta que la pluma 0 deberá emplearse para definir qué zonas del sprite deben ser transparentes. Recuerda que es el primer color que aparece en `gfx/pal.png`. En este caso, el amarillo pálido:

![sprites.png](https://raw.githubusercontent.com/mojontwins/MK1_Pestecera/master/docs/wiki-img/jet_paco/sprites.png)

### Sprites extra

En `gfx/` hay dos archivos gráficos más de tipo sprite (con lo que debes prestar atención a usar la pluma 0 para marcar qué píxeles son transparentes) que puedes (debes) modificar al gusto:

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
    ..\utils\mkts_om.exe platform=cpc cpcmode=%cpc_gfx_mode% pal=..\gfx\pal.png mode=superbuffer in=..\gfx\marco.png out=..\bin\marco.bin silent > nul
    ..\utils\mkts_om.exe platform=cpc cpcmode=%cpc_gfx_mode% pal=..\gfx\pal.png mode=superbuffer in=..\gfx\ending.png out=..\bin\ending.bin silent > nul
    ..\utils\mkts_om.exe platform=cpc cpcmode=%cpc_gfx_mode% pal=..\gfx\pal.png mode=superbuffer in=..\gfx\title.png out=..\bin\title.bin silent > nul
    ..\utils\apultra.exe ..\bin\title.bin ..\bin\titlec.bin > nul
    ..\utils\apultra.exe ..\bin\marco.bin ..\bin\marcoc.bin > nul
    ..\utils\apultra.exe ..\bin\ending.bin ..\bin\endingc.bin > nul
```

Esta sección convierte las tres pantallas fijas y posteriormente las comprime usando apultra. `mtks_om` trabaja en esta ocasión en modo `superbuffer` produciendo una imagen binaria directamente compatible con el sistema empleado en `MK1` (básicamente, 192 lineas de 64 bytes).

```cmd
    ..\utils\mkts_om.exe platform=cpc mode=pals in=..\gfx\pal.png prefix=my_inks out=assets\pal.h silent > nul
```

Finalmente, utilizamos `mkts_om` en modo `pals` para generar `dev/assets/pal.h` con la información sobre la paleta que se empleará en el juego.

Un poco más abajo, en la sección de `compile.bat` donde se genera el archivo `.cdt`, aparece la linea que ejecuta `mkts_om` en modo `scr` para exportar la pantalla de carga usando, esta vez, la paleta en `pal_loading.png`:

```cmd
    echo Construyendo cinta
    ..\utils\mkts_om.exe platform=cpc cpcmode=%cpc_gfx_mode% pal=..\gfx\pal_loading.png mode=scr in=..\gfx\loading.png out=..\bin\loading.bin silent > nul
    [...]
```

Seguidamente se crea la cinta. Nótese que si tienes tu paleta de la pantalla de carga en una ubicación distinta o no se llama `pal_loading.png` tendrás que modificar tambien eso.

## Adaptando mapa y enemigos

En realidad no vamos a adaptar mucho. Más que nada vamos a modificar `mapa.fmp` para que emplée los gráficos de CPC y modificar el archivo con el tileset que emplea Ponedor para que se muestre también con estos gráficos.

Como hemos trabajado en este juego en modo 0, tendremos que *engañar* a Mappy y Ponedor generando una nueva versión del tileset con píxeles ladrillo. Básicamente, abriremos nuestro `work.png` y lo escalaremos al doble de ancho, resultando en una imagen de 256x48 con los píxeles rectangulares que almacenaremos como `work.png` dentro de el directorio `enems/`.

![work.png a doble de ancho en enems](https://raw.githubusercontent.com/mojontwins/MK1_Pestecera/master/docs/wiki-img/jet_paco/enems-work.png)

Hecho esto, copiamos el archivo con el mapa original de la versión de spectrum en el directorio `map/`, sobrescribiendo el `mapa.fmp` por defecto (el de **Lala Prologue**). Al abrirlo veremos el tileset original:

![El mapa original de Jet Paco](https://raw.githubusercontent.com/mojontwins/MK1_Pestecera/master/docs/wiki-img/jet_paco/mappy_orig.png)

Ahora lo que haremos será sustituir el tileset. Vamos a `File` → `Import` y buscamos el archivo `work.png` que hemos grabado en `enems/`. Pero hay un problema:

![Mapa corrupto](https://raw.githubusercontent.com/mojontwins/MK1_Pestecera/master/docs/wiki-img/jet_paco/mappy_new_wrong.png)

Efectivamente, el nuevo `work.png` no tiene el primer tile en negro y Mappy hace su gracia desplazando todo el tileset. Para repararlo, buscamos en el menú `Layer` → `Adjust Values` y en el diálogo `adjust non-0 blocks in this layer by` escribimos `1` y pulsamos `Ok`. 

Esto corregirá casi todo el mapa, pero el fondo sigue usando el tile 0 que en Mappy está vacío. Todo tiene solución: vamos a `Custom` → `Tile Replace`, introducimos el texto `0,1` y pulsamos `Ok`. Con esto, Mappy sustituirá todas las ocurrencias del tile 0 por el tile 1, con lo que el fondo se restaurará.

![Mapa para CPC](https://raw.githubusercontent.com/mojontwins/MK1_Pestecera/master/docs/wiki-img/jet_paco/mappy_new.png)

Tras esto, no debemos olvidar **grabar** de nuevo el mapa en `map/` sustituyendo lo que haya, tanto en formato `.fmp` como en formato `.map`. Igualmente haremos una copia de `mapa.map` en `enems/` para el ponedor.

Ahora sólo tendremos que acordarnos de que tenemos que emplear `fixmappy` en la conversión del mapa en `compile,bat`:

```cmd
    echo Convirtiendo mapa
    ..\..\..\src\utils\mapcnv.exe ..\map\mapa.map assets\mapa.h 7 5 15 10 15 packed fixmappy > nul
```

Hecho esto vamos con los enemigos. Si estás adaptando un juego que hayas hecho con **MK1 v5** y más o menos has seguido las instrucciones del tutorial en lo referente a los nombres de archivos, probablemente no tengas que cambiar gran cosa. Sin embargo, he decidido precisamente portar un juego *viejo* de **MK1** (en concreto **Jet Paco** se confeccionó con una versión *3.9 beta* previa a la primera que distribuímos) para que tengamos todos los problemas posibles.

El problema es, principalmente, que los archivos `.ene` del Ponedor contienen referencias a los archivos de mapa y tileset y que, probablemente, el nombre de estos archivos haya cambiado. Para corregirlo emplearemos un editor hexadecimal. Si estás en Windows puedes usar `XVI32`, incluido en `/env`. 

Empezaremos copiando el `enems.ene` original en `enems/`, sustituyendo al `enems.ene` por defecto (el de **Lala Prologue**). En este directorio deberían estar ya disponibles el archivo `work.png` a doble de ancho que preparamos antes y que acabamos de importar en `mapa.fmp` y el archivo `mapa.map` actualizado.

Si abrimos el archivo `enems.ene` original de Jet Paco en tu editor hexadecimal deberías ver algo parecido a esto (si no se ve bien alineado probablemente tengas que configurar tu editor para que muestre 16 valores por linea):

![enems.ene en XVI32](https://raw.githubusercontent.com/mojontwins/MK1_Pestecera/master/docs/wiki-img/jet_paco/hex_1.png)

En nuestro caso vemos que el nombre del mapa está bien (`mapa.map`). Sin embargo, el nombre del tileset no: aparece `mappy.bmp`. Lo que haremos será cambiarlo por `work.png` - para ello editaremos el texto directamente en la ventana de la derecha (1). Hay que tener en cuenta que el resto de la cadena debe quedarse a "0", y la forma más fácil es escribir los ceros en la columna de la izquierda (2). Si te equivocas *don't panic*: sólo tienes que recargar el archivo y empezar de nuevo.

![modificando enems.ene en XVI32](https://raw.githubusercontent.com/mojontwins/MK1_Pestecera/master/docs/wiki-img/jet_paco/hex_2.png)

Una vez hecho esto, grabamos nuestro archivo `enems.ene` modificado. Nos vamos a una ventana de linea de comandos y ejecutamos `ponedor.exe` pasándoloe `enems.ene` como parámetro:

```cmd
    $ ..\utils\ponedor.exe enems.ene
```

Aún no está del todo bien. Por un lado, Ponedor no sabe aún que nuestro mapa tiene la fullería de Mappy. Por otro lado, en `enems.ene` original de Jet Paco usaba el formato antiguo de 2 bytes por Hotspot como se nos muestra en la parte superior de la ventana con ese **2b**:

![enems.ene sin ajustar](https://raw.githubusercontent.com/mojontwins/MK1_Pestecera/master/docs/wiki-img/jet_paco/ponedor_1.png)

Para corregirlo, pulsamos primero "+" en el teclado numérico para deshacer el desbarajuste de Mappy, y posteriormente "L" para convertir desde modo *legacy* al actual de 3 bytes por Hotspot. Ahora las pantallas se visualizarán correctamente y la leyenda habrá cambiado a **3b**. Hecho esto, **salvamos** el archivo pulsando `Save` o la tecla "S".

![enems.ene ajustado](https://raw.githubusercontent.com/mojontwins/MK1_Pestecera/master/docs/wiki-img/jet_paco/ponedor_2.png)

## La configuración

Lo siguiente será editar `dev/my/config.h` para establecer la configuración del juego, sustituyendo la que viene por defecto (escrita para **Lala Prologue**) por una adecuada para **Jet Paco**. Puedes consultar la [referencia de config.h](https://raw.githubusercontent.com/mojontwins/MK1_Pestecera/master/docs/config.h.md).

Obviamente, cuando estás convirtiendo juegos de versiones más antiguas de la churrera, encontrarás un montón de opciones que no existían y algunas es posible que hayan cambiado de nombre. Sin embargo, es muy sencillo partir del proyecto por defecto, que tiene prácticamente todo desactivado, e ir recorriendo en `config.h` original y buscando en el nuevo cada una de las opciones.

Para nuestro **Jet Paco**, por ejemplo, apenas hemos cambiado unas cuantas cosas: 

* El número de pluma equivalente al color negro:

```c
    #define BLACK_PEN                   5       // Which palette entry is black
```

* Las dimensiones del mapa y las coordenadas de inicio:

```c
    #define MAP_W                       7       //
    #define MAP_H                       5       // Map dimensions in screens
    #define SCR_INICIO                  28      // Initial screen
    #define PLAYER_INI_X                5       //
    #define PLAYER_INI_Y                6       // Initial tile coordinates
```

* El número máximo de objetos, la vida inicial y el valor de las recargas.

```c
    #define PLAYER_NUM_OBJETOS          20      // Objects to get to finish game
    #define PLAYER_LIFE                 15      // Max and starting life gauge.
    #define PLAYER_REFILL               1       // Life recharge
```

* Que la pantalla de título contiene el marco:

```c
    #define DIRECT_TO_PLAY                      // If defined, title screen is also the game frame.
```

* Que no usamos llaves

```c
    #define DEACTIVATE_KEYS                     // If defined, keys are not present.
```

* Que no queremos rebotar contra los enemigos

```c
    //#define PLAYER_BOUNCES                    // If defined, collisions make player bounce
```

* Que queremos que el jugador parpadée tras ser alcanzado o golpée pinchos

```c
    #define PLAYER_FLICKERS                     // If defined, collisions make player flicker instead.
```

* Que queremos jetpac en vez de salto:

```c
    //#define PLAYER_HAS_JUMP                   // If defined, player is able to jump.
    #define PLAYER_HAS_JETPAC                   // If defined, player can thrust a vertical jetpac
```

* La posición de los elementos en el marco:

```c
    #define VIEWPORT_X                  0       //
    #define VIEWPORT_Y                  2       // Viewport character coordinates
    #define LIFE_X                      30      //
    #define LIFE_Y                      8       // Life gauge counter character coordinates
    #define OBJECTS_X                   30      //
    #define OBJECTS_Y                   12      // Objects counter character coordinates
    #define OBJECTS_ICON_X              99      // 
    #define OBJECTS_ICON_Y              99      // Objects icon character coordinates (use with ONLY_ONE_OBJECT)
    #define KEYS_X                      99      //
    #define KEYS_Y                      99      // Keys counter character coordinates
    #define KILLED_X                    99      //
    #define KILLED_Y                    99      // Kills counter character coordinates
    #define AMMO_X                      99      // 
    #define AMMO_Y                      99      // Ammo counter character coordinates
    #define TIMER_X                     99      //
    #define TIMER_Y                     99      // Timer counter coordinates
```

* Reajustamos la velocidad máxima cayendo y la gravedad a valores más pequeños para "flotar" más

```c
    #define PLAYER_MAX_VY_CAYENDO       128     // Max falling speed 
    #define PLAYER_G                    8       // Gravity acceleration 
```

* Definimos valores para la aceleración y velocidad máxima del jetpac:

```c
    #define PLAYER_INCR_JETPAC          16      // Vertical jetpac gauge
    #define PLAYER_MAX_VY_JETPAC        128     // Max vertical jetpac speed
```

* Y, por último, definimos el comportamiento de los tiles:

```c
    unsigned char behs [] = {
        0, 1, 8, 8, 8, 8, 0, 0, 0, 4, 8, 8, 4, 8, 8, 8,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };
```

## Montando la OGT

Los juegos de CPC tienen una OGT que hay que montar a menos que decidas no tener sonido (con SOUND_NONE). Para este ejemplo vamos a montar la OGT mínima basada en dos canciones: una para la pantalla de título y otra de fondo mientras jugamos.

Para montar el sistema de sonido necesitaremos:

* **WYZ Tracker 2** de **Augusto Ruiz** [link](https://github.com/AugustoRuiz/WYZTracker).

* **Todas las canciones deben estar hechas con el mismo set de instrumentos y efectos de percusión**.

* Exportar todas las canciones en formato `mus`. Hay que tener mucho cuidado de configurar **Wyz Tracker** para que exporte para **Amstrad CPC**. Las guardaremos en el directorio `mus/` y anotaremos sus tamaños. Nos interesa el tamaño de la más grande. Por convención, las llamaremos `00_title.mus` y `01_ingame.mus`. Esto también generará `00_title.mus.asm` y `01_ingame.mus.asm` que, **si lo hemos hecho bien, deberían ser idénticos**.

* Configurar `wyz_player.h`, que incluye el player propiamente dicho. Si lo editamos, veremos que empieza con dos macros:

```c
    #define WYZ_SONG_BUFFER 0x8800
    #define BASE_WYZ        0xDF80
```

La primera de ellas, `WYZ_SONG_BUFFER`, que es la que nos interesa, define el espacio que se empleará para descomprimir la canción que se vaya a tocar. Este espacio va desde la dirección definida en la macro hasta 0x8FFF. Esto significa que, de entrada y sin tocar, tendremos 0x800 bytes, o lo que es lo mismo, 2Kb, para descomprimir nuestra canción. Esto significa que nuestro archivo .mus exportado más grande debe medir menos de 2Kb. Si hemos hecho músicas muy largas y la mayor ocupa más de 2Kb, habrá que dejar más espacio bajando el valor de `WYZ_SONG_BUFFER` hasta que quepa. Pero si nuestras canciones son más cortas, lo suyo es subir el valor todo lo que podamos para liberar más espacio para nuestro juego.

Para saber el valor tendremos que restar el tamaño del MUS más grande de 0x9000, o 36864. En el ejemplo el mus más grande es el de la música que suena mientras jugamos, que ocupa 1843 bytes. Siendo así, podríamos usar el valor 36864-1843 = 35021 (o 0x88CD) en `WYZ_SONG_BUFFER` lo que nos daría 205 bytes extra. No es mucho, pero todo cuenta.

* Comprimir todas los archivos `mus` con `apultra` dentro del directorio `mus/`. Podemos crearnos un archivo  `compress_songs.bat` para hacerlo porque si tenemos un músico competente como el señor Davidian retocará las canciones varias veces ;-). Por convención, generaremos `00_title.mus.bin` y `01_ingame.mus.bin`:

```cmd
    ..\utils\apultra.exe 00_title.mus 00_title.mus.bin
    ..\utils\apultra.exe 01_ingame.mus 01_ingame.mus.bin
```

* Renombrar uno de los archivos `*.mus.asm` (todos deberían ser iguales, repito) a `instrumentos.asm`. Este archivo `mus/instrumentos.asm` será convertido durante la compilación por `compile.bat` a un archivo directamente usable por el motor (si estamos respetando la nomenclatura no tendremos que cambiar nada):

```cmd
    ..\..\..\src\utils\wyzTrackerParser.exe ..\mus\instrumentos.asm my\wyz\instrumentos.h
```

* Construir la lista de canciones. El motor debe saber qué canciones tiene disponibles y qué datos tienen. Para ello generaremos `my/wyz/songs.h` con esta estructura:

```c
    // MTE MK1 (la Churrera) v5.0
    // Copyleft 2010-2014, 2020 by the Mojon Twins

    extern unsigned char *wyz_songs [0];

    #asm
        ._00_title_mus_bin
            BINARY "../mus/00_title.mus.bin"

        ._01_ingame_mus_bin
            BINARY "../mus/01_ingame.mus.bin"

        ._wyz_songs
            defw    _00_title_mus_bin, _01_ingame_mus_bin
    #endasm
```

Si añadiésemos más canciones habría que importarlas bajo una etiqueta `_NN_MUSICA_mus_bin` y luego añadirla a la lista bajo `_wyz_songs`.

Si no tocamos nada más, el motor llamará a `AY_PLAY_MUSIC (0)` en la pantalla de título para tocar la canción 0 de la lista `wyz_songs` (la primera) y a `AY_PLAY_MUSIC (1)` al empezar la partida para tocar la canción 1 de la lista. Si quieres cambiar este comportamiento o añadir más canciones tendrás que tocar el código. Por suerte, casi todos los sitios donde tocar están en `my/`.

En los juegos multifase la canción que sonará durante cada nivel se define en el array `levels` de `my/levelset.h`.

## Los colores de la carga

Cuando carga el juego se ven bandas de dos colores en el fondo. Las puedes cambiar editando el archivo `dev/loader/loadercpc.asm-orig` y cambiando el valor de la primera linea que es:

```asm
    COLORES_CARGA equ $5c56
```

El valor de la variable comprende los dos colores (2 dígitos hexadecimales cada uno), que no son más que los valores "Hardware" de la paleta del CPC que puedes consultar, entre otros lugares, [aquí](http://www.cpcwiki.eu/index.php/CPC_Palette).

## ¡Y ya está!

Ahora es el momento de abrir una ventana de linea de comandos, ejecutar `setenv.bat` y luego `compile.bat` para generar un archivo .SNA o `compile.bat andtape` para generar además un archivo .CDT
