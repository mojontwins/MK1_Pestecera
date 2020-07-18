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
	#define ENABLE_FANTIES						// If defined, Fanties are enabled!
	#define FANTIES_BASE_CELL 			4		// Base sprite cell (0, 1, 2 or 3)
	//#define FANTIES_SIGHT_DISTANCE	64 		// Used in our type 6 enemies.
	#define FANTIES_MAX_V 				192 	// Flying enemies max speed (also for custom type 6 if you want)
	#define FANTIES_A 					8		// Flying enemies acceleration.
	#define FANTIES_LIFE_GAUGE			10		// Amount of shots needed to kill flying enemies.
	//#define FANTIES_TYPE_HOMING				// Unset for simple fanties.
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
		0, 0 						// <= extra sprite faces added
	};

	unsigned char sm_coy [] = { 
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0 						// <= extra sprite faces added
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

