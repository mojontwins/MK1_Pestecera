# Balowwwn

Un port rápido se vino a más, el juego tiene su potencial si ponemos algunas cosas:

1.- Tiles que se rompen al pegarles (`ENABLE_BREAKABLE`). Se deben hacer *persistentes*, y quitar vida al ser golpeados.

2.- Al principio del juego hay que rehacer el mapa. 

Al Romper un tile, se cambiará a su versión 32 tiles más arriba en el tileset, y al romperse del todo se cambiará por el tile 31.

¿Cómo "reiniciar" el mapa? La única solución que se me ocurre es guardar una copia comprimida... ¿Habría alguna forma de persistir y restaurar? Guardar una lista de tiles rotos comprendería guardar 2 bytes por tile que se rompe. 

Mirando el mapa de memoria, en D800 tenemos un buffer libre que podemos ocupar con una lista de hasta 256 sustituciones. El tema es si será suficiente, es un mapa grande. Voy a hacerme un script en LUA que integrar en mappy que me cuente las ocurrencias de un determinado tile y veo si esto es viable así. En tiempos hice el *tile replace* y no fue muy complicado, veamos si me acuerdo de cómo se hacía esto...

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

Tengo que, por tanto, crear una función `persist_tile` que modifique el mapa en memoria y registre una entrada en el array de restauración que empezará en 0xD800 en cada partida, y que habrá que leer para restaurar el mapa cada vez que...

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

La rutina que restaura el percal habría que engancharla justo al final del juego, o donde se pueda (ahora de memoria no me acuerdo cuándo había hooks). Debería recorrer desde 0xD800 hasta el sitio al que apunte el puntero e ir modificando el mapa así:

```c
	void restore_map (void) {
		gen_pt = ((unsigned char *) (0xD800));
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

