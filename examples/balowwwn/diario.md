# Balowwwn

Un port rápido se vino a más, el juego tiene su potencial si ponemos algunas cosas:

1.- Tiles que se rompen al pegarles (`ENABLE_BREAKABLE`). Se deben hacer *persistentes*, y quitar vida al ser golpeados.

2.- Al principio del juego hay que rehacer el mapa. 

Al Romper un tile, se cambiará a su versión 32 tiles más arriba en el tileset, y al romperse del todo se cambiará por el tile 31.

¿Cómo "reiniciar" el mapa? La única solución que se me ocurre es guardar una copia comprimida... ¿Habría alguna forma de persistir y restaurar? Guardar una lista de tiles rotos comprendería guardar 2 bytes por tile que se rompe. 

Mirando el mapa de memoria, en de00 tenemos un buffer libre que podemos ocupar con una lista de hasta 256 sustituciones. El tema es si será suficiente, es un mapa grande. Voy a hacerme un script en LUA que integrar en mappy que me cuente las ocurrencias de un determinado tile y veo si esto es viable así. En tiempos hice el *tile replace* y no fue muy complicado, veamos si me acuerdo de cómo se hacía esto...

El `lua_scr` están los scripts. En `MAPWIN.INI` se definen los 16 scripts que aparecerán en el menú. Lo que tengo que hacer es sustituir uno que nunca vaya a usar, como `Tile graphic test.lua`.

Creo mi propio `Count tiles.lua`... A ver si me acuerdo como iba:

```lua
    function main ()
        local w = mappy.getValue(mappy.MAPWIDTH)
        local h = mappy.getValue(mappy.MAPHEIGHT)

        local blk
        
        if (w == 0) then
            mappy.msgBox ("Find block in map", "You need to load or create a map first", mappy.MMB_OK, mappy.MMB_ICONINFO)
        else
            blk = mappy.getValue (mappy.CURANIM)
            if (blk == -1) then
                blk = mappy.getValue (mappy.CURBLOCK)
            else
                -- setBlock need anims in the format below (ie: anim 1 should be a value of -2)
            blk = -(blk+1)
        end  

        local count = 0

        local y = 0
        while y < h do
            local x = 0
            while x < h do 
                if blk == mappy.getBlock (x, y) then
                    count = count + 1
                end

                x = x + 1
            end

            y = y + 1
        end

        mappy.msgBox ("Count tiles", "Tile " .. blk .. " appears " .. count .. " times", mappy.MMB_OK, mappy.MMB_ICONINFO)
    end

    test, errormsg = pcall( main )
    if not test then
        mappy.msgBox("Error ...", errormsg, mappy.MMB_OK, mappy.MMB_ICONEXCLAMATION)
    end
```

Y modifico `MAPWIN.INI` con `lua09=Count tiles.lua`.

Voie la, los tiles que te matan (en el mapa desplazado porque el tile 0 no es negro completo) son los números 2, 7 y 15, que aparecen:

|Tile|Veces
|---|---
|2|72
|7|82
|15|20

En total, 184 tiles que restaurar... Lo cual es factible.

Tengo que, por tanto, crear una función `persist_tile` que modifique el mapa en memoria y registre una entrada en el array de restauración que empezará en 0xde00 en cada partida, y que habrá que leer para restaurar el mapa cada vez que...

Espera, que estoy hablando muy rápido. 2 tiles por sustitución ¿y el número de pantalla donde te lo metes?

Back to the drawing board.

A ver, tenemos que almacenar `n_pant`, `x`, `y` y el número de tiles. Tal cual, el número de tiles lo puedo meter en 2 bits. Como hay 35 pantallas, necesito 6 bits para el número de pantalla. Esto me permite dejarlo todo en 2 bytes a coste de tener que meter más código. El formato de cada entrada en el array de restauración será:

```
    BYTE 0   BYTE 1
    xxxxyyyy pppppptt
```

Con esto y un bizcocho lo tendría. La función `persist_tile` la empiezo basándome en la que aparece en Sgt. Helmet y añado la escritura en la tabla de restauración.

```c
    void modify_map (void) {
        // _gp_gen points where.
        // rdt is the tile number to write.

        rda = *_gp_gen;

        if (gpaux & 1) {
            // Modify right nibble
            rda = (rda & 0xf0) | rdt;
        } else {
            // Modify left nibble
            rda = (rda & 0x0f) | (rdt << 4);
        }

        *_gp_gen = rda;
    }

    void persist_tile (void) {
        // c_screen_address must be set
        // gpaux must be COORDS (_x, _y)
        // rdt = substitute with this tile
        
        _gp_gen = (c_screen_address + (gpaux >> 1));
        
        modify_map ();

        *restore_table_ptr = gpaux; 
        restore_table_ptr ++;
        *restore_table_ptr = (n_pant << 2) | (tile_restore_lut [rdt]);
        restore_table_ptr ++;
    }
```

Y esta LUT de 16 bytes:

```c
    unsigned char tile_restore_lut [] = {
        0xff, 0x00, 0xff, 0xff, 
        0xff, 0xff, 0x01, 0xff, 
        0xff, 0xff, 0xff, 0xff, 
        0xff, 0xff, 0x03, 0xff
    };

    unsigned char tile_restore_reverse_lut [] = {
        0x01, 0x06, 0x0e
    };
```

que, como se ve, mapea cada uno de los tiles que se pueden romper con los números 0, 1 y 2. El 0xff hace que, en caso de error, se almacene un tile 3 en una pantalla fuera de rango (la 63), que lo la hace robusta.

La rutina que restaura el percal habría que engancharla justo al final del juego, o donde se pueda (ahora de memoria no me acuerdo cuándo había hooks). Debería recorrer desde 0xde00 hasta el sitio al que apunte el puntero e ir modificando el mapa así:

```c
    void restore_map (void) {
        gen_pt = ((unsigned char *) (0xde00));
        while (gen_pt < restore_table_ptr) {
            gpaux = *gen_pt; gen_pt ++;
            rda = *gen_pt; gen_pt ++;
            
            n_pant = rda >> 2;
            rdt = tile_restore_reverse_lut [rda & 3];

            _gp_gen = ((unsigned char *)(mapa + n_pant * 75));          
            modify_map ();
        }
    }
```

La idea sería implementarlo así y si funciona pasarlo a ensamble. Pero ahora ya no me da más el celebro.

## 20220411

Esta ha sido la implementación definitiva: empezamos con `extra_vars.h` donde he definido todas las miserias:

```c 
    unsigned char *c_screen_address;            // Current screen address in map array
    unsigned char *restore_table_ptr = 0xde00;  // Pointer to the restore table 

    // These LUTs make my life easier when it's time to restore the map

    unsigned char tile_restore_lut [] = {
        0xff, 0x00, 0xff, 0xff, 
        0xff, 0xff, 0x01, 0xff, 
        0xff, 0xff, 0xff, 0xff, 
        0xff, 0xff, 0x03, 0xff
    };

    unsigned char tile_restore_reverse_lut [] = {
        0x01, 0x06, 0x0e
    };
```

Fíjense bien en que `restore_table_ptr` empezará valiendo `0xde00`, lo cual es muy importante, ya que el siguiente código se ejecutará al empezar cada partida, en `entering_game.h`:

```c
    // Restore 

    gen_pt = (unsigned char *) (0xde00);
    while (gen_pt < restore_table_ptr) {
        gpaux = *gen_pt; gen_pt ++;
        rda =   *gen_pt; gen_pt ++;

        n_pant = rda >> 2;
        rdt = tile_restore_reverse_lut [rda & 3];

        _gp_gen = mapa + n_pant * 75 + (gpaux >> 1);
        modify_map ();
    }

    // Reset pointer

    restore_table_ptr = (unsigned char *) (0xde00);
```

El tema está en que, la primera vez que se juegue, `restore_table_ptr` valdrá 0xde00 y, por tanto, no se restaurará nada, que es exactamente lo que queremos (no hay nada que restaurar). Acto seguido, se establece el puntero a `0xde00` para la partida.

Lo siguiente es el contenido de `extra_functions.h`, donde encontramos lo que hablamos ayer (un poco refactorizado y corregido):

```c
    // MTE MK1 (la Churrera) v5.0
    // Copyleft 2010-2014, 2020 by the Mojon Twins

    void modify_map (void) {
        // _gp_gen points where.
        // rdt is the tile number to write.

        rda = *_gp_gen;

        if (gpaux & 1) {
            // Modify right nibble
            rda = (rda & 0xf0) | rdt;
        } else {
            // Modify left nibble
            rda = (rda & 0x0f) | (rdt << 4);
        }

        *_gp_gen = rda; 
    }

    void break_wall_kill_and_persist (void) {

        break_wall ();          // Breaks _x, _y. this sets gpaux!

        p_killme = SFX_SPIKES;

        // c_screen_address must be set
        // gpaux is COORDS (_x, _y)
        // rdt = substitute with this tile
        
        // Add an entry to the restore list and
        // make the changes persistent on map when it's completely broken

        if (map_buff [gpaux] == 0) {
            rdt = 0;
            _gp_gen = (c_screen_address + (gpaux >> 1));
            
            modify_map ();

            *restore_table_ptr = gpaux; 
            restore_table_ptr ++;
            *restore_table_ptr = (n_pant << 2) | (tile_restore_lut [rdt]);
            restore_table_ptr ++;
        }
    }


    void break_vertical (void) {
        // Called from obstacle_up and obstacle_down

        if (at1 & 16) {
            _y = cy1; _x = cx1; 
            break_wall_kill_and_persist ();
        }

        if (cx1 != cx2) {
            if (at2 & 16) {
                _y = cy1; _x = cx2; 
                break_wall_kill_and_persist ();
            }
        }
    }

    void break_horizontal (void) {
        // Called from obstacle_left and obstacle_right
        _x = cx1;

        if (at1 & 16) {
            _x = cx1;_y = cy1; 
            break_wall_kill_and_persist ();
        }

        if (cy1 != cy2) {
            if (at2 & 16) {
                _x = cx1; _y = cy2; 
                break_wall_kill_and_persist ();
            }
        }
    }
```

Y finalmente llamamos a `break_vertical` o `break_horizontal` desde `bg_collision/obstacle_*.h` según corresponda.

## 20220412

Esto funciona y tal y cual y pascual PERO.

Ahora he pensado que molaría también persistir los tiles empujables, lo cual requeriría más historias, y que a lo mejor lo suyo sería simplemente tener un mapa comprimido almacenado y dejar ese buffer de 512 bytes de la restauración no sé, para meter el `brk_buff` y cosas así.

Esto implica también que quizá te puedas quedar encerrado, por lo que este güego debería tener un botón para hacer el suicidio o la suicidación, lo que viene siendo abortar y regresar al menú.

Asín es, ha sido muy divertido y me lo guardo en la manga, pero por ahora se va a la basura.

Para el próximo momento:

1.- Deshacer la restauración.
2.- Incluir el binario con el mapa comprimido en el juego y descomprimirlo al principio de cada partida.
3.- Persistir los tiles que se empujan.

~~

La conversión del mapa en `compile.bat` hace fullerías:

```bat
    echo Convirtiendo mapa
    rem ..\..\..\src\utils\mapcnv.exe ..\map\mapa.map assets\mapa.h 5 7 15 10 15 packed fixmappy > nul

    rem We need a compressed copy for this game
    ..\..\..\src\utils\apultra.exe ..\map\mapa.map ..\bin\mapa.c.bin 

    rem Also, zeroing the map we'll get a shorter tape file!
    copy my\map_all_zeroes.h assets\mapa.h /y
```

`my/map_all_zeroes.h` lo hemos hecho a manaca (con un copy & replace inteligente) y sólo lleva ceros, así evitamos engordar mucho el binario general comprimido en el `.cdt` (¡porque hay que pensar en todo!). También lleva la importación del binario comprimido:

```c
    // my/map_all_zeroes.h

    // This file contains an alternate map with all zeroes.
    // Just a trick for this game.

    extern unsigned char mapa [0];
    #asm
        ._mapa defs MAP_W * MAP_H * 75
    #endasm

    typedef struct {
        unsigned char np, x, y, st;
    } CERROJOS;

    #define MAX_CERROJOS 32

    extern CERROJOS cerrojos [0];
    #asm
        ._cerrojos defs 128 ; 32 * 4
    #endasm

    extern unsigned char mapa_c [0]; 
    #asm 
        ._mapa_c
            BINARY "../bin/mapa.c.bin"
    #endasm
```

Lo único que habrá que hacer es eliminar todo rastro del restorer que montamos y simplemente hacer esto en `my/ci/entering_game.h`.

```c
    // my/ci/entering_game.h

    // Restore 

    unpack (mapa_c, mapa);
```

Y por último, vamos a hacer que los empujables sean persistentes. Cuando se empuja un tile se ejecuta el código de `my/ci/on_tile_pushed.h` y, aquí, (x0, y0) son las coordenadas de origen (donde habrá que poner un 0) y (x1, y1) son las de destino (donde habrá que poner el tile 14). Así:

```c
    // my/ci/on_tile_pushed.h

    // Persist x0, y0 (write 0)
    gpaux = COORDS (x0, y0); rdt = 0; modify_map ();

    // Persist x1, y1 (write 14)
    gpaux = COORDS (x1, y1); rdt = 14; modify_map ();
```

Nuestras funciones auxiliares quedaron así:

```c 
    void modify_map (void) {
        // gpaux is COORDS (_x, _y) & points where.
        // c_screen_address is calculated on entering_screen.h
        // rdt is the tile number to write.

        _gp_gen = (c_screen_address + (gpaux >> 1));
        rda = *_gp_gen;

        if (gpaux & 1) {
            // Modify right nibble
            rda = (rda & 0xf0) | rdt;
        } else {
            // Modify left nibble
            rda = (rda & 0x0f) | (rdt << 4);
        }

        *_gp_gen = rda; 
    }

    void break_wall_kill_and_persist (void) {

        break_wall ();          // Breaks _x, _y. this sets gpaux!

        p_killme = SFX_SPIKES;

        // c_screen_address must be set
        // gpaux is COORDS (_x, _y)
        // rdt = substitute with this tile
        
        // make the changes persistent on map only when the tile is
        // completely broken (i.e. has disappeared, 0 in this game)

        if (map_buff [gpaux] == 0) {
            rdt = 0;
            modify_map ();
        }
    }

    void break_vertical (void) {
        // Called from obstacle_up and obstacle_down

        if (at1 & 16) {
            _y = cy1; _x = cx1; 
            break_wall_kill_and_persist ();
        }

        if (cx1 != cx2) {
            if (at2 & 16) {
                _y = cy1; _x = cx2; 
                break_wall_kill_and_persist ();
            }
        }
    }

    void break_horizontal (void) {
        // Called from obstacle_left and obstacle_right
        _x = cx1;

        if (at1 & 16) {
            _x = cx1;_y = cy1; 
            break_wall_kill_and_persist ();
        }

        if (cy1 != cy2) {
            if (at2 & 16) {
                _x = cx1; _y = cy2; 
                break_wall_kill_and_persist ();
            }
        }
    }
```

Sin olvidar:

```c
    // my/ci/entering_screen.h

    // precalculate for persistence:

    c_screen_address = mapa + n_pant * 75;
```

