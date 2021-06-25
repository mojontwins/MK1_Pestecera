# Sgt. Helmet Training Day

Por fin portamos este juego a pestecé. La base será el port de ZX a MK1 v5, al menos las dos primeras fases. Para este port quiero más fases pero no quiero tener que usar más de un tileset. La idea es que haya Helmets variados en muchas plataformas, pero que cada iteración siga siendo única.

La primera idea es repetir el mapeado de la fase 1 con un cambio: no hay llaves, sino que estas se obtienen matando a una especie de fantasmas que recibirán un porronaco de tiros.

- Eso implica reaprovechar todo menos el binario de enemigos y hotspots.
- Puedo usar los fanties empleando sprites extra sin problemas.
- Hay que modificar el tema del respawn para que no se regeneren los fantasmas.

La mejor forma de modificar el respawn para que no se regeneren los fantasmas es desactivarlo y programándolo en un custom, concretamente en `my/ci/enems_custom_respawn.h`:

```c
    // Back to life!
    if (malotes [enoffsmasi].t != 6) {
        malotes [enoffsmasi].t &= 0xEF;     
        malotes [enoffsmasi].life = ENEMIES_LIFE_GAUGE;
    }
```

Y sin olvidarse de desactivar `RESPAWN_ON_ENTER`.

## Los fanties

Activamos los fanties:

```c
    #define ENABLE_FANTIES                      // If defined, Fanties are enabled!
    #define FANTIES_BASE_CELL           4       // Base sprite cell (0, 1, 2 or 3)
    //#define FANTIES_SIGHT_DISTANCE    64      // Used in our type 6 enemies.
    #define FANTIES_MAX_V               192     // Flying enemies max speed (also for custom type 6 if you want)
    #define FANTIES_A                   8       // Flying enemies acceleration.
    #define FANTIES_LIFE_GAUGE          10      // Amount of shots needed to kill flying enemies.
    //#define FANTIES_TYPE_HOMING               // Unset for simple fanties.
```

Base cell = 4 significa que necesitamos más sprites. He añadido dos al spriteset. Como por ahora `mkts_om` no genera el índice de punteros `spriteset_mappings.h` tendré que modificarlo para añadir a mano la información, quedando así:

```c
    // MTE MK1 (la Churrera) v5.0
    // Copyleft 2010-2014, 2020 by the Mojon Twins

    // Spriteset mappings. 
    // One entry per sprite face in the spriteset!

    #define SWSPRITES_ALL  18

    unsigned char sm_cox [] = { 
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0                        // <= extra sprite faces added
    };

    unsigned char sm_coy [] = { 
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0                        // <= extra sprite faces added
    };

    void *sm_invfunc [] = {
        cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, 
        cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, 
        cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, 
        cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16,
        cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16 // <= extra sprite faces added
    };

    void *sm_updfunc [] = {
        cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b,
        cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b,
        cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b,
        cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b,
        cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b // <= extra sprite faces added
    };

    extern void *sm_sprptr [0]; 
    #asm
        ._sm_sprptr
            defw _sprites + 0x000, _sprites + 0x040, _sprites + 0x080, _sprites + 0x0C0
            defw _sprites + 0x100, _sprites + 0x140, _sprites + 0x180, _sprites + 0x1C0
            defw _sprites + 0x200, _sprites + 0x240, _sprites + 0x280, _sprites + 0x2C0
            defw _sprites + 0x300, _sprites + 0x340, _sprites + 0x380, _sprites + 0x3C0
            defw _sprites + 0x400, _sprites + 0x440 // <= extra sprite faces added
    #endasm
```

Para hacer que los fanties dejen una llave podemos meter código en `my/ci/on_enems_killed.h`:

```c
    // Note that _en_t has bit 4 raised, so:
    if (_en_t == 0x16) {    
        // Fanties give you a key
        ++ p_keys;
        AY_PLAY_SOUND (SFX_KEY_GET);
    }
```

## Tercer nivel

(level == 2, que se cuenta desde 0) añadimos los tiestos al levelset. Nótese como se reaprovecha el mapa pero no los enemigos / hotspots:

```c
    // Include here your compressed binaries:

    extern unsigned char map_bolts0 [0];
    extern unsigned char map_bolts1 [0];
    extern unsigned char enems_hotspots0 [0];
    extern unsigned char enems_hotspots1 [0];
    extern unsigned char enems_hotspots2 [0];
    extern unsigned char behs0_1 [0];

    #asm
        ._map_bolts0
            BINARY "../bin/mapa0c.bin"  
        ._map_bolts1
            BINARY "../bin/mapa1c.bin"
        ._enems_hotspots0
            BINARY "../bin/enems_hotspots0c.bin"
        ._enems_hotspots1
            BINARY "../bin/enems_hotspots1c.bin"
        ._enems_hotspots2
            BINARY "../bin/enems_hotspots2c.bin"
        ._behs0_1
            BINARY "../bin/behs0_1c.bin"
    #endasm

    // Define your level sequence array here:
    // map_w, map_h, scr_ini, ini_x, ini_y, max_objs, 
    // c_map_bolts, [c_tileset], c_enems_hotspots, c_behs, [c_sprites], [script], music_id
    LEVEL levels [] = {
        { 1, 23, 23, 12, 7, 99, map_bolts0, enems_hotspots0, behs0_1, 1 },
        { 1, 23, 23, 12, 7, 99, map_bolts1, enems_hotspots1, behs0_1, 1 },
        { 1, 23, 23, 12, 7, 99, map_bolts0, enems_hotspots2, behs0_1, 1 }
    };
```

# 20200719

Tras un par de días haciendo y probando fases y puliendo cosas, hemos decidido hacer 8 fases empleando solo 3 mapas y 5 .enes. Cuatro de las fases serán meras 6 pantallas de un mapa de 24 que iremos reaprovechando empezando en diferentes puntos y con diferente código custom para controlar.

Estas son las fases:

1 - llegar esquivando alambradas/rayos
2 - buscar rehenes
3 - fase A original
4 - fase B original
5 - sin ammo
6 - fase A fantasmas original
7 - fase B fantasmas original
8 - moto

En cuanto haga el nuevo .ene para la fase B fantasmas original empiezo con los cambios. Como la lógica actual sólo se dará en las fase 3, 4, 6, 7, lo guardaré todo tras una variable `classic_level_logic` que pondré a 1 al empezar esas fases.

## Persistencia de vallas rotas

Vamos a programar la persistencia de breakables en un custom empleando el CIP `on_wall_broken.h`. Aquí llegamos con las coordenadas en `_x, _y` y la pantalla en `n_pant`. El mapa está a partir de la dirección apuntada por `mapa`. La fórmula pues sería `mapa + n_pant * 75 + COORDS [_x, _y] / 2`. Resulta que `COORDS [_x, _y]` lo tenemos precalculado ya en `gpaux`. Tendremos que tomar el byte que haya y modificar el nibble derecho si `gpaux & 1`, o el izquierdo en caso contrario.

La dirección base de la pantalla la vamos a calcular en `on_entering_screen.h`:

```c
    // on_entering_screen.h
    
    c_screen_address = mapa + n_pant * 75;
```

Y con esto:

```c
    // on_wall_broken.h

    _gp_gen = (c_screen_address + (gpaux >> 1));
    rda = *_gp_gen;

    if (gpaux & 1) {
        // Modify right nibble
        rda = (rda & 0xf0) | BREAKABLE_WALLS_BROKEN;
    } else {
        // Modify left nibble
        rda = (rda & 0x0f) | (BREAKABLE_WALLS_BROKEN<<4);
    }

    *_gp_gen = rda;
```

Obviamente el tile que se escribe en el mapa debe ser del rango 0..15 porque estamos en packed.

## Cómo se monta la OGT

Porque siempre es bueno repetirlo para recordarlo. Estos son los pasos:

1. Necesito `instrumentos.asm`, que contiene `TABLA_PAUTAS` y `TABLA_EFECTOS` en `mus/`
2. Necesito cada `*.mus` y llamarlos `00_title.mus` y `00_ingame.mus` en `mus/`
3. Ejecuto `compress_songs.bat` *(Si tuviera más músicas tendría que modificarlo antes)*
4. Uso `wyztrackerparser.exe` para obtener `my/wyz/instrumentos.h`:

```
    $ ..\..\..\src\utils\wyzTrackerParser.exe instrumentos.asm ..\dev\my\wyz\instrumentos.h
```

Oye, no está tan mal.

# La fase de los hostages

Podría haberlo hecho usando hotspots pero no me dan 6 pantallas para 5 rehenes y llaves y hostias en vinegar, así que vamos a implementarlo de otra forma.

* En `level == 1`, los tiles #13 se sustituirán por el rehén (tile 21) al pintar.
* Cuando el jugador toque el tile 21 (le pondré el beh especial 128, que lanza `on_special_tile`), el tile se sustituirá por el tile 0 (tengo que mover por tanto el persistidor de mapas a una función para usarlo desde aquí y desde el tile roto) y se incrementará `p_objs`.
* Si `level == 1` y `p_objs == 5`, fin.

```c
    // extra_functions.h
        
    void persist_tile (void) {
        // c_screen_address must be set
        // gpaux must be COORDS (_x, _y)
        // rdt = substitute with this tile
        
        _gp_gen = (c_screen_address + (gpaux >> 1));
        rda = *_gp_gen;

        if (gpaux & 1) {
            // Modify right nibble
            rda = (rda & 0xf0) | rdt;
        } else {
            // Modify left nibble
            rda = (rda & 0x0f) | (rdt<<4);
        }

        *_gp_gen = rda;
    }
```

Cambiamos tiles 13 por tile 21:

```c
    // map_renderer_t_modification.h

    #asm
            ld  a, (__t)
            or  a
            jr  nz, _ds_custom_packed_noalt

            // Alt tile #2

        ._ds_custom_packed_alt
            call _rand
            ld  a, l
            and 15
            cp  1
            jr  z, _ds_custom_packed_alt_subst

            ld  a, (__t)
            jr  _ds_custom_packed_noalt

        ._ds_custom_packed_alt_subst
            ld  a, 30
            ld  (__t), a

        ._ds_custom_packed_noalt

            // Hostages, tile == 13?
            cp  13
            jr  nz, _ds_custom_end

            // On level 1?
            ld  a, (_level)
            dec a
            jr  nz, _ds_custom_end

            // Clear behs
            ld  a, 128
            ld  hl, _map_attr
            add hl, bc
            ld  (hl), a

            ld  a, 21
            ld  (__t), a

        ._ds_custom_end
    #endasm
```

Y ahora hay que detectar y modificar:

```c
    // 
```

# 20200721

La última fase: la moto. Hay que pintar la moto en la pantalla 5, me vale con la misma deco porque queda bien en las mismas coordenadas. La fase acaba si `n_pant == 5`, `p_objs == 1`, `gpy < 48` y `gpx < 80`. Y poco más.

## La pantalla de continue?

Tras el game over debe mostrarse "CONTINUE?" "ENTER=SI, ESC=NO". Si se continua. debería reiniciarse el nivel actual. Para ello emplearemos `my/ci/after_game_over.h`.

# 20200816

Añadì un mòdulo para que las rocas empujables desplacen a los enemigos, y lo puse para que lo hicieran con los patrollers tipo 3 y los demás, pero esto se ha visto que causa problemas:

- Cuando colocas el boulder sobre el sitio donde aparecen los tipo 7 - no deberían aparecer.
- Cuando desplazas a un tipo 3 lo puedes sacar fuera de su trayectoria y liarla parda - los tipos 3 deberían morir instantaneamente cuando mueves un boulder contra ellos.



Actualizar en ZX: `after_game_over` y lo de las 0 vidas.

~

Sorted! Ya lo han probau y el juego se puede de sacal.
