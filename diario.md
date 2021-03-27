Memory map

0100 tilemap
0400 ejecutable
8800 descomprimir canción
9000 buffer
C000 pantalla (a trozos)
C600 room buffers
CE00 dirty cells (tiles_tocados)
D600 arrays
DF80 buffers WYZ
E600 sprite structures
FE00 LUT


20200426
========

A ver si poco a poco voy venciendo la desidia que me embarga. Vamos a empezar este proyecto tan bonito de portar la Churrera V5 a CPC. 

Lo he estado pensando mucho y voy a portar esto con algo sencillo y que tenga pocos visos de fallar: Lala Prologue. Lo primero es hacer acopio de material. Lo segundo será conseguir importar todos los assets (cambiando la importación de los gráficos al modo pestecé). Lo tercero será construir el juego sin sonido. Y por último integrar WYZ Player.

Para convertir LALA, que es en modo 1, tendré que añadir soporte para este en `mkts_om`.

20200505
========

Ya hice la conversión en modo 1 (la cual no sé si funcionará correctamente, pero tengo que seguir adelante). También he pasado todo el set gráfico de Lala Prologue a CPC en modo 1. No sé si las historias que hice en CPCRSLIB funcionarán en modo 1, pero deberían. 

El tema del modo 1 es que para simplificar estoy haciendo sprites de 3 colores, y el color 0 es el transparente. En este juego he puesto rojo oscuro como color 0 porque es el color que no se usa en los sprites.

Vamos a sustituir todos los conversores gráficos en compile.bat para obtener todos los tiestos que necesito en el formato de CPC.

## Tileset

Tengo que recortar un charset y un tileset:

```
    ..\utils\mkts_om.exe platform=cpc cpcmode=1 pal=..\gfx\pal.png mode=chars in=..\gfx\font.png out=..\bin\font.bin silent
    ..\utils\mkts_om.exe platform=cpc cpcmode=1 pal=..\gfx\pal.png mode=strait2x2 in=..\gfx\work.png out=..\bin\work.bin silent
```

## Spriteset

Haremos como en Spectrum aunque no tengan máscaras: los sets serán, por convención, de 8 cells de ancho. Como estamos en Modo 1, tendremos 128x32 píxels. En modo 0 serán 64x32 (o más si hay sprites extra).

```
    ..\utils\mkts_om.exe platform=cpc cpcmode=1 pal=..\gfx\pal.png mode=sprites in=..\gfx\sprites.png out=..\bin\sprites.bin silent
```

Y los sprites extra:

```
    ..\utils\mkts_om.exe platform=cpc cpcmode=1 pal=..\gfx\pal.png mode=sprites in=..\gfx\sprites_extra.png out=..\bin\sprites_extra.bin silent > nul
    ..\utils\mkts_om.exe platform=cpc cpcmode=1 pal=..\gfx\pal.png mode=sprites in=..\gfx\sprites_bullet.png out=..\bin\sprites_bullet.bin metasize=1,1 silent > nul
```

## Pantallas fijas

Aquí hay que usar el modo "superbuffer" de `mkts_om`:

```
    ..\utils\mkts_om.exe platform=cpc cpcmode=1 pal=..\gfx\pal.png mode=superbuffer in=..\gfx\marco.png out=..\bin\marco.bin silent > nul
    ..\utils\mkts_om.exe platform=cpc cpcmode=1 pal=..\gfx\pal.png mode=superbuffer in=..\gfx\ending.png out=..\bin\ending.bin silent > nul
    ..\utils\mkts_om.exe platform=cpc cpcmode=1 pal=..\gfx\pal.png mode=superbuffer in=..\gfx\title.png out=..\bin\title.bin silent > nul
    ..\utils\apultra.exe ..\bin\title.bin ..\bin\titlec.bin > nul
    ..\utils\apultra.exe ..\bin\marco.bin ..\bin\marcoc.bin > nul
    ..\utils\apultra.exe ..\bin\ending.bin ..\bin\endingc.bin > nul
```

## Pantalla de carga

Para construir la cinta y el DSK:

```
    ..\utils\mkts_om.exe platform=cpc cpcmode=1 pal=..\gfx\pal.png mode=scr in=..\gfx\loading.png out=..\bin\loading.bin silent > nul
```

## La paleta principal

```
	..\utils\mkts_om.exe platform=cpc mode=pals in=..\gfx\pal.png prefix=my_inks out=assets\pal.h silent > nul
```

# CPCRSLIB

Teniendo todo esto es cuando empezamos a refrescar la memoria con **CPCRSLIB**. Lo primero que voy a hacer es traerme los tiestos desde **MK3-OM** y meter cosas en env.

## tileset

El tilemap se gestiona en `tilemap_conf.asm`. Me traigo el de **MK3_OM** que se puede usar tal cual. Tengo que ver como metía los tiles **MK3-OM**... Vale. Aquí estaba todo en un "heap" muy preparadito para el multi nivel. Allí se define la etiqueta `_ts`, que se `XREF`erencia desde `tilemap_conf.asm`, por lo que hay que `XDEF`inirla. Todo esto en `assets/tileset.h`. Pero voy a cambiar `_ts` por `_tileset` para tener la mayor cantidad de código en común con el main port de peste a rectum.

Para que funcione **CPCRSLIB** tengo que etiquetar como `tiles` (con su correspondiente `XDEF`) también:

```c
    // assets/tileset.h

    extern unsigned char tileset [0];
    #asm
            XDEF _ts
            XDEF tiles
        ._tileset
        .tiles
        ._font
            BINARY "../bin/font.bin"    // 1024 bytes for 64 patterns
        ._tspatterns
            BINARY "../bin/work.bin"   // 3072 bytes for 192 patterns
    #endasm
```

## spriteset

El spriteset estará etiquetado por `_sprites` y directamente cargará el binario:

```c
    // assets/sprites.h

    extern unsigned char sprites [0]; 
     
    #asm
        ._sprites
            BINARY "../bin/sprites.bin"
    #endasm     
```

Dejo por aquí apuntado que los sprites ocupan 64 bytes cada uno así que para referenciar al gráfico N haremos `sprites + 64 * N`.

Los extra sprites cambian para incluir los tiestos y definir a manaca un sprite vacío.

```c
    #if defined(PLAYER_CAN_FIRE) || defined(PLAYER_STEPS_ON_ENEMIES) || defined(ENABLE_PURSUERS) || defined (MODE_128K)
        extern unsigned char sprite_17_a []; 
    #endif

    extern unsigned char sprite_18_a []; 

    #if defined(PLAYER_CAN_FIRE) || defined (MODE_128K)
        extern unsigned char sprite_19_a [];
        extern unsigned char sprite_19_b [];
    #endif

    #if defined(PLAYER_CAN_FIRE) || defined(PLAYER_STEPS_ON_ENEMIES) || defined(ENABLE_PURSUERS) || defined (MODE_128K)
        #asm
            ._sprite_17_a
                BINARY "../bin/sprites_extra.bin"
        #endasm
    #endif

    #asm
        ._sprite_18_a
            defs 64, 0
    #endasm

    #if defined(PLAYER_CAN_FIRE) || defined (MODE_128K)
        #asm
            ._sprite_19_a
                BINARY "../bin/sprites_bullet.bin"
        #endasm
    #endif
```

## Levels

Pequeñas adaptaciones al archivo levels.

```c
    // assets/levels.h

    [...]

    extern unsigned char font [0];
    #asm
        ._font BINARY "../bin/font.bin"
    #endasm

    [...]

    extern unsigned char tileset [0];
    #asm
        ._tileset defs 3072     // 16*192
    #endasm

    [...]

    #if MODE_128K || defined PER_LEVEL_SPRITESET
        #include "assets/sprites-empty.h"
    #else
        #include "assets/sprites.h"
    #endif
```

Lo de MODE_128K lo voy dejando porque me vendrá bien si algún día dandanatamos o hacemos pestecé 6128 (de alguna manera).

## Pantallas fijas

Poco más que cambiar las rutas de los binarios y modificar el código del blackout para que borre saltándose los cachos que tengo listo en cada octavo. Recordemos que mi pantalla sólo usa 1536 bytes de cada octavo (24x64) y el resto tengo que dejarlos sin tocar porque voy a meter ahí búferes e historietas.

Los octavos están en C000, C800, D000, D800, E000, E800, F000, y F800 así que esté código ni tan mal:

```c
    void blackout (void) {
        #asm
                ld  a, c0
            .bo_l1
                ld  h, a
                ld  l, 0
                ld  (hl), 0
                ld  d, a
                ld  l, 1
                ld  bc, 1535
                ldir

                add 8
                jr  nz, bo_l1
        #endasm
    }
```

## Desactivar el audio susbsystem (por ahora)

Por ahora lo voy a dejar off y de camino lo meto todo en #defines por si algún día se tercia cambiar a Arkos. `wyz_play_sound` -> `AY_PLAY_SOUND`, `wyz_play_music` -> `AY_PLAY_MUSIC`, `wyz_stop_sound` -> `AY_STOP_SOUND`.

## Inicialización 

Cambio toda la inicialización el sistema en `mainloop.h`. Dejamos WYZ para luego. De nuevo, tomamos como ejemplo **MK3-OM**. Tengo que meter la LUT comprimida que luego se mete en VRAM para que funcionen los sprites. La copio tal cual de MK3_OM en `assets` y la incluyo en un `trpixlut.h`.

Para el modo gráfico usaré un define `CPC_GFX_MODE`, que se pondrá desde la orden de compilación vía -D (lo añado a `compile.bat`).

```
	zcc +cpc -m -vn -O3 -unsigned -zorg=1024 -lcpcrslib -cpcwyzlib -DCPC_GFX_MODE=%cpc_gfx_mode% -o %game%.bin tilemap_conf.asm mk1.c > nul
```

Lo siguiente que viene (tras otras cosas menores) es la inicialización de los sprites. Creo que de entrada lo haré para que luego sea fácil tener sprites de diferentes tamaños. Para ello emplearé la misma estructura ampliada que en **MK3-OM** que traía function pointers para los diferentes tamaños de los sprites.

Lo suyo sería que el tamaño se definiese a nivel de spriteset, y que luego se diese dinámicamente (en el caso de los enemigos) el tamaño correcto dependiendo del tipo. Todo esto teniendo en cuenta que debería haber un conversor que generase el mapeo dependiendo de un script o algo así. Muchas cosas que hacer en un futuro a medio plazo. Por ahora lo pongo fijo pero con soporte para que esto cambie (el mapeo apuntará todo a las mismas funciones). Lo voy a ir creando en `assets/spriteset_mappings.h` con vistas a cambiarlo.

La idea es generar este archivo automáticamente en el futuro:

```c
	// Spriteset mappings. 
	// One entry per sprite face in the spriteset!

	unsigned char sm_cox [] = { 
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0
	};

	unsigned char sm_coy [] = { 
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0
	};

	void *sm_invfunc [] = {
		cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, 
		cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, 
		cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, 
		cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16
	};

	void *sm_updfunc [] = {
		cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b,
		cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b
		cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b
		cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b
	};

	void *sm_sprptr [] = {
		_sprites + 0x000, _sprites + 0x040, sprites + 0x080, sprites + 0x0C0,
		_sprites + 0x100, _sprites + 0x140, sprites + 0x180, sprites + 0x1C0,
		_sprites + 0x200, _sprites + 0x240, sprites + 0x280, sprites + 0x2C0,
		_sprites + 0x300, _sprites + 0x340, sprites + 0x380, sprites + 0x3C0
	};
```

Por lo pronto inicializamos el player y las balas / cocos aquí:

```c
	// Sprite creation

	// Player 

	sp_sw [SP_PLAYER].cox = sm_cox [0];
	sp_sw [SP_PLAYER].coy = sm_coy [0];
	sp_sw [SP_PLAYER].invfunc = sm_invfunc [0];
	sp_sw [SP_PLAYER].updfunc = sm_updfunc [0];
	sp_sw [SP_PLAYER].sp0 = sp_sw [SP_PLAYER].sp1 = sm_sprptr [0];

	// Enemies - delegated to enems_load

	// Bullets are 4x8

	#ifdef PLAYER_CAN_FIRE
		for (gpit = SP_BULLETS_BASE; gpit < SP_BULLETS_BASE + MAX_BULLETS; gpit ++) {
			sp_sw [gpit].cox = 0;
			sp_sw [gpit].coy = 0;
			sp_sw [gpit].invfunc =cpc_PutSpTileMap4x8;
			sp_sw [gpit].updfunc = cpc_PutTrSp4x8TileMap2b;
			sp_sw [gpit].sp0 = sp_sw [SP_PLAYER].sp1 = sprite_19_a;
		}
	#endif

	// Cocos are 4x8

	#ifdef ENABLE_SIMPLE_COCOS
		for (gpit = SP_COCOS_BASE; gpit < SP_COCOS_BASE + MAX_BULLETS; gpit ++) {
			sp_sw [gpit].cox = 0;
			sp_sw [gpit].coy = 0;
			sp_sw [gpit].invfunc =cpc_PutSpTileMap4x8;
			sp_sw [gpit].updfunc = cpc_PutTrSp4x8TileMap2b;
			sp_sw [gpit].sp0 = sp_sw [SP_PLAYER].sp1 = sprite_19_a;
		}
	#endif
```

Los enemigos deberán ser inicializados en `enems_load`:

```c
	// Sprite creation

	rda = SP_ENEMS_BASE + enit;
	if (rdb = en_an_base_frame [enit] != 0xff) {
		sp_sw [rda].cox = sm_cox [rdb];
		sp_sw [rda].coy = sm_coy [rdb];
		sp_sw [rda].invfunc = sm_invfunc [rdb];
		sp_sw [rda].updfunc = sm_updfunc [rdb];
		sp_sw [rda].sp0 = sp_sw [rda].sp1 = sm_sprptr [rdb];
	} else {
		sp_sw [rda].sp0 = sp_sw [rda].sp1 = sprite_18_a;
	}
```

## Quitar splib2 y poner CPCRSLIB

Ahora es cuando me pateo todo el código y cambio splib2 por CPCRSLIB. Por ahora voy a hacer sólo las pantallas de superbuffer y todo el fondo, sin renderizar ni un sprite (luego usaré el actualzador que escribí para **MK3-OM**).

# 20200512

Me he dado cuenta, tras la primera compilación (sin sprites), que la forma de manejar la lista de actualizaciones (tiles invalidados) no es muy compatible con como hago las cosas y presenta problemas. CPCRSLIB sería mucho más utilizable de modo general (y creo que más rápida) si usase un bitfield en vez de una lista de tiles no válidos.

El bitfield usaría 1 bit por cada uno de los 768 caracteres, o lo que es lo mismo, 768/8 = 96 bytes fijos, que es bastante menos que lo que puede crecer la lista original.

Para obtener si la casilla `(x, y)` es válida, teniendo 32/8 = 4 bytes por linea, tendría que mirar en el byte `y * 4 + x / 8`, en el bit `x & 7`. ¡Oye, ni tan costoso! 

Ahora mismo tenemos `cpc_UpdTileTable` que toma `D = Y, E = X` y añade una entrada a la lista `tiles_tocados`. Modificando levemente este código podría escribir en el bitfield. 

`cpc_ResetTouchedTiles` debería poner los 96 bytes a 0.

La parte más complicada vendrá a la hora de actualizar. Haciendo una búsqueda rápida y mal, veo que sólo consultan `cpc_ShowTouchedTiles`, `cpc_TouchTileSpXY` que no sé si uso (NO), `cpc_UpdScr` (para actualizar los tiles tocados al buffer).

Ni tanto. 

Me lo planteo mucho (lo haré).

# 20200513

Leg's rock in Vietnam! Vamos a hacer el cambio y a romper la CPCRSLIB durante muchos días :D

Lo más sencillo es modificar primero `cpc_UpdTileTable`. Para ello he añadido una paqueña LUT para seleccionar el bit y la sencilla rutina `tbllookup` directamente desde splib2. El tema ha quedado así:

```
    XLIB cpc_UpdTileTable       ;marca un tile indicando las coordenadas del tile
    LIB cpc_Bit2Mask, cpc_TblLookup
    XREF tiles_tocados

    .cpc_UpdTileTable   
        ; D = y
        ; E = x

        ld  a, d
        sla a
        sla a               ; y = 0-23, 23*4 fits in a byte.
        ld  b, a            ; B = y * 4

        ld  a, e
        srl a
        srl a
        srl a               ; x / 8

        add b               ; A = x / 8 + y * 4

        ld  hl, tiles_tocados
        ld  b, 0
        ld  c, a            ; BC = x / 8 + y * 4
        add hl, bc          ; HL = tiles_tocados + x / 8 + y * 4

        ld  a, e            ; A = x
        ld  de, cpc_Bit2Mask
        call cpc_TblLookup  ; A = bit mask

        or  (hl)            ; A = bit mask | [tiles_tocados + x / 8 + y * 4]
        ld  (hl), a

        ret
```

La siguiente es `cpc_ResetTouchedTiles` que simplemente debería dejarlos todos a 0:

```
    XLIB cpc_ResetTouchedTiles
    XREF tiles_tocados
     
    .cpc_ResetTouchedTiles

        ld  hl, tiles_tocados
        ld  de, tiles_tocados + 1
        ld  bc, 95
        ld  (hl), 0
        ldir

        ret 
```

Y ahora vienen las difíciles: `cpc_ShowTouchedTiles`, `cpc_UpdScr`. El código es muy largo porque soy menso y si no lo hago desenrollado no me sale. Y cuando lo pruebe reventarán CPCs de todo el mundo.

Antes de probar, necesito una función que me invalide de forma arbitraria un rectángulo. Voy a mirar como está hecho esto en splib2... Pues resulta que hay un código bastante complejete que lo hace de forma muy optimizada, con máscaras y hostias.

Tomando BCDE así:

```
    B - row, top left.
    C - col, top left.
    D - row, bottom right.
    E - col, bottom right.
```

Primero transforma D y E en las longitudes del rectángulo. Luego hace una intersección con el rectángulo de clipping (yo no necesito hilar tan fino) y luego hace sus potagias. Creo que según la entiendo la puedo replicar. Pero a lo mejor ya va a ser mucha tela para hoy ¿no?

Al final sí. Y compilar, compila XD

¡Y tras un par de eructitos, funciona! Ya puedo añadir N tiles invalidados como quiera y cuando quiera. Para otro día intento optimizarlo, pero por ahora me vale.

Ahora lo siguiente son los sprites, y para ello voy a recordar el tema de MK3_OM para hacerlo igual con las cosas nuevas que he puesto en provisión de futuros spritesets de tamaños mezclados.

Veo que para sprite hago algo parecido a esto:

```c
    spr_on [SPR_PLAYER] = (pflickering == 0) || half_life;
    spr_x [SPR_PLAYER] = prx - 4;
    spr_y [SPR_PLAYER] = pry;
    spr_next [SPR_PLAYER] = sprite_cells [psprid];
```

Luego en el bucle principal, se recorre `spr_on`. Si está a true, se actualizan las coordenadas y el gráfico de los sprites software en las estructuras:

```c
    {
        sp_sw [(a)].cx = (((x) + SCR_X*8) >> 2); sp_sw [(a)].cy = (y) + SCR_Y*8;
        sp_sw [(a)].sp0 = (int) (spr_next [(a)]);
    }
```

si `spr_on` es false, se les asigna el sprite vacío y se ponen en 0, 0:

```c
    { sp_sw [(a)].sp0 = (int) (ss_empty); sp_sw [(a)].cx = sp_sw [(a)].cy = 0; }
```

Con todo esto relleno, se llama a una rutina `cpc_screen_update` que recorre la estructura `sp_sw` llamando a las funciones de actualización pertinentes según estén definidas para cada sprite `invfunc` y `updfunc`.

# 20200514

Vamos a tratar de habilitar primero el sprite del player. Daré directamente valores a `sp_sw [SP_PLAYER].cx`, `.cy`, y `sp0`, y tendré cuidado de poner el frame vacío cuando el jugador esté parpadeando.

Esto parece que está medio funcionando. Ahora voy a meter a los enemigos. En el proceso he tenido que revisar algunas funciones (las funciones que pintan los sprites usaban DE y la función que invalida el bitfield se los follaba) y añadir un LUT de transparencias para el modo 1.

# 20200515

Con todo medio organizado (al final he puesto teclas/joystick predefinidos y si alguien quiere añadir codigo para redefinir que lo haga), voy a ver como carajo monto la música.

Por ahora he hecho un parser de los .mus.asm de Wyz Tracker para crearme un `assets/instrumentos.h` que defina `tabla_pautas` y `tabla_instrumentos`, dos arrays que, junto con `wyz_effects_table` y `wyz_song_table` necesito para configurar el player embebido en `CPCWYZLIB`.

```
    ..\utils\wyzTrackerParser.exe ..\mus\instrumentos.asm assets\instrumentos.h
```

Luego eso lo meteré dentro de `my/sound.h` junto con la tabla de canciones y la de instrumentos.

# 20200518

Al final he decidido pasar de `CPCWYZLIB` e integrar la versión más reciente de **WYZ Player** por mi mismo. Como la documentación no existe y los fuentes y sus comentarios son algo confusos (nomenclatura mal), me he hecho unos apuntes:

## WYZ Player

La idea es tomar el original `WYZPROPLAY47c_CPC.ASM` y generar un módulo directamente compilable por z88dk que pueda linkar al igual que se hace con `tilema_conf.asm`. Eso implica cambiar algunas cosas de sitio, modificar las etiquetas, etc.

### Puntos de entrada

Estos son los puntos de entrada que necesitamo para integrar el player:

|Label|Wat|
|---|---|
|WYZPLAYER_INIT|**Inicialización**. Reserva memoria para los canales. No sé por qué hace falta dar tanta vuelta; probablemente sea porque esto está pensado para ejecutarse desde una ROM. Quizá la primera modificación que haga sea dejar esto "fijo".|
|INICIO|**Actualización**. Esta es la rutina a la que tengo que llamar cada frame.|
|INICIA_EFECTO|**Tocar un SFX**. A = # sonido; B = canal (0, 1, 2).|
|CARGA_CANCION|**Tocar una canción**. A = # canción. Empieza a tocarla delti.|
|PLAYER_OFF|**Silencio**|

### K ASE

Lo primero que voy a hacer es montarme esto en plan monolítico teniendo en cuenta que "sonidos" y "pautas" (percusiones e instrumentos) tendrán que ser inyectados posteriormente de alguna manera. El primer paso será modificar el código de `WYZPROPLAY47c_CPC.ASM` para que compile con z88dk y de camino para que incluya las interfaces con C `wyz_init`, `wyz_play_sound`, `wyz_play_music` y `wyz_stop_sound`.

# 20200520

He hecho esta pequeña interfaz C:

```c
    void wyz_init (void) {
        #asm
            call WYZPLAYER_INIT
        #endasm 
    }

    void __FASTCALL__ wyz_play_music (unsigned char m) {
        #asm
            ; Song number is in L
            ld  a, l
            call CARGA_CANCION
        #endasm
    }

    void __FASTCALL__ wyz_play_sound (unsigned char s) {
        #asm
            ; Sound number is in L
            ld  a, l
            ld  b, WYZ_FX_CHANNEL
            call INICIA_EFECTO
        #endasm
    }

    void wyz_stop_sound (void) {
        #asm
            call PLAYER_OFF
        #endasm
    }
```

Aunque ahora estoy pensando que a lo mejor es mejor usar ensamble en linea por unos bytes... Meh, da igual, así es más fácil de usar para los muggles.

También añado este enganche al ISR:

# 20200522

`DATOS_NOTAS` y `TABLA_SONG` van fijas en el código. `TABLA_EFECTOS` puedo sacarla a otro archivo, junto con los efectos de sonido, para que sea fácil cambiarlo, y `TABLA_PAUTAS` y `TABLA_SONIDOS`, que exporta WYZ Tracker, deberían ir en otro, que montaré a mano pero que, idealmente, debería generarse automáticamente.

# 20200524

He instalado WYZ Tracker 2.0.X y he reexportado los .MUS, teniendo cuidado de elegir "Amstrad CPC" en el modelo (esto lo escribo para cuando tenga que hacer la DOC pestecera).

Esto produce los archivos .mus y unos .mus.asm que en teoría deberían ser todos iguales. Uno de esos debería estar dentro de `wyz_player.h`. La idea, al menos en las primeras versiones será:

1.- Renombrar uno de estos archivos como `instrumentos.asm`.
2.- Usar wyzTrackerParser.exe para obtener `my/wiz/instrumentos.h`.

En `my/wiz/instrumentos.h` va un bloque `#asm`..`#endasm` donde se definen `TABLA_PAUTAS` (instrumentos) y `TABLA_SONIDOS` (percusiones).

He generado `my/wiz/efectos.h` usando `asm2z88dk.exe` para incluir de forma fija, pero habrá que mencionarlo en la doc para que la gente se pueda hacer sus propios efectos.

También necesito una lista con las canciones y los propios binarios de las canciones. Para esto estará `my/wiz/songs.h` que por ahora generaré a mano.

```c
    extern unsigned char *wyz_songs [0];

    #asm
        ._00_title_mus_bin
            BINARY "../mus/_00_title.mus.bin"

        ._01_ingame_mus_bin
            BINARY "../mus/_01_ingame.mus.bin"

        ._wyz_songs
            defw    _00_title_mus_bin, _01_ingame_mus_bin
    #endif
```

Ya compila pero no suena nada y el juego luego no inicia (aunque la pantalla de título parece que sí). Voy a desactivar a ver si así vuelve a funcionar. Sí que vuelve. Pues toca depurar paso a paso. Lo que me flipa es que ahora ocupa todo 3100 bytes más O_o.

Parece que se me está colgando en la rutina `PLAY`. Y dentro de ahí, a `LOCALIZA_EFECTO`.

//

Muchos días después y con la ayuda de Augusto Ruiz, esto está funcionando.

20200607
========

Entendamos la lib. A ver, que se me va la pinzorra.

`cpc_ShowTouchedTiles ()` copia los tiles marcados del buffer a la pantalla, por lo que deben haberse dibujado antes en el buffer.

Si solo modifico el nametable, no hay *nada* que me pinte el tile realmente. Por lo que muchas de mis funciones tienen un planteamiento mal y por eso no estoy viendo lo que tengo que ver.

Voy a recapitular a ver qué mierdas estoy haciendo. Porque todas mis funciones de tile solo estan escribiendo cosas en la nametable, ¿Quién está pintando las cosas realmente? 

Si llamo a `cpc_UpdateNow (); while (1);` justo tras invalidar la pantalla no se muestra nada. Estoy haciendo algo MUY MAL.

Me cango en san peo virgen, ¿quién hace esto?

Vale joder.

En la parte que actualiza los sprites, primero marca todos los sprites, luego llama a una función que copia todos los TILES DE FONDO marcados al buffer, y luego pinta los sprites encima.

Voy a reorganizar el codigo y hacer una `cpc_UpdateNow (unsigned char sprites)` que haga todo con o sin sprites y a incluirla en el resto del motor.

20200613
========

Con todo resuelto y funcionando, me puse a montar la cinta. Todo parece OK, pero obviamente algo cambia porque en un entorno no ideal (o sea, cargando de cinta y no de un snapshot super controlado) los sprites de los enemigos aparecen desplazados abajo y a la derecha, con lo que obviamente no estoy inicializando algo que debería inicializar.

Voy a intentar depurar esto. Primero con un breakpoint en $400 y comprobando como está todo a la hora de ejecutar, y luego con otro tras la inicialización, por ejemplo en `_GAME_LOOP_INIT`.

20200717
========

Todo lo de arriba lo resolví bien resuelto y eran idioteces de no inicializar la RAM. Ahora estoy portando el Helmet y encontrado fallillos.

[X] Los tipo 7 salen con el sprite mal (empieza a contar desde la base del spriteset y no desde la base de los enemigos, parece ser).

20200807
========

Corrección de errores y mejoras miscelaneas. Portado Jet Paco en 0.2. Va todo genial.

20210326
========

Greenweb me apunta fallos y carencias porque está siendo tan osado como para ponerse a escribir un juego sin documentación. ¡Ole!

Voy a tratar de resolverlas.

20210327
========

Hoy trataré que `mkts_om.exe` sea capaz de generar `spriteset_mappings.h`. Esto tiene dos trabajos:

- El fácil es que lo genere para el modo `sprites`, con todos los sprites iguales.
- El complicado es que haya un modo para spritesets con tamaños variables, y para ello habrá que leer un script.

Vamos con lo primero intentando que sea reutilizable.

Ahora mismo los sprites se convierten con:

```c
    ..\utils\mkts_om.exe platform=cpc cpcmode=%cpc_gfx_mode% pal=..\gfx\pal.png mode=sprites in=..\gfx\sprites.png out=..\bin\sprites.bin silent > nul
```

Podemos añadir un nuevo parámetro `mapping=file.h` y si existe que se genere el código necesario.

