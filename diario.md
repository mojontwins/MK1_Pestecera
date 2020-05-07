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

# Quitar splib2 y poner CPCRSLIB

Ahora es cuando me pateo todo el código y cambio splib2 por CPCRSLIB. Por ahora voy a hacer sólo las pantallas de superbuffer y todo el fondo, sin renderizar ni un sprite (luego usaré el actualzador que escribí para **MK3-OM**).

