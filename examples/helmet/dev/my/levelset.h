// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// levelset.h

// Contains this game's level sequence.
// Format is different for 128K games (using level bundles)
// and 48 games (using separate assets).

#ifdef MODE_128K
	// 128K format:
	typedef struct {
		unsigned char resource_id;
		unsigned char music_id;
		#ifdef ACTIVATE_SCRIPTING
			unsigned int script_offset;
		#endif
	} LEVEL;
#else
	// 48K format:
	typedef struct {
		unsigned char map_w, map_h;
		unsigned char scr_ini, ini_x, ini_y;
		unsigned char max_objs;
		unsigned char *c_map_bolts;
		#ifdef PER_LEVEL_TILESET
			unsigned char *c_tileset;
		#endif
		unsigned char *c_enems_hotspots;
		unsigned char *c_behs;
		#ifdef PER_LEVEL_SPRITESET
			unsigned char *c_sprites;
		#endif
		#ifdef ACTIVATE_SCRIPTING
			unsigned int script_offset;
		#endif
		unsigned char music_id;
	} LEVEL;
#endif

// Include here your compressed binaries:

extern unsigned char map_bolts0 [0];
extern unsigned char map_bolts1 [0];
extern unsigned char map_bolts2 [0];
extern unsigned char enems_hotspots0 [0];
extern unsigned char enems_hotspots1 [0];
extern unsigned char enems_hotspots2 [0];
extern unsigned char enems_hotspots3 [0];
extern unsigned char enems_hotspots4 [0];
extern unsigned char behs0_1 [0];

#asm
	._map_bolts0
		BINARY "../bin/mapa0c.bin"	
	._map_bolts1
		BINARY "../bin/mapa1c.bin"
	._map_bolts2
		BINARY "../bin/mapa2c.bin"
	._enems_hotspots0
		BINARY "../bin/enems_hotspots0c.bin"
	._enems_hotspots1
		BINARY "../bin/enems_hotspots1c.bin"
	._enems_hotspots2
		BINARY "../bin/enems_hotspots2c.bin"
	._enems_hotspots3
		BINARY "../bin/enems_hotspots3c.bin"
	._enems_hotspots4
		BINARY "../bin/enems_hotspots4c.bin"
	._behs0_1
		BINARY "../bin/behs0_1c.bin"
#endasm

// Define your level sequence array here:
// map_w, map_h, scr_ini, ini_x, ini_y, max_objs, 
// c_map_bolts, [c_tileset], c_enems_hotspots, c_behs, [c_sprites], [script], music_id
LEVEL levels [] = {
	{ 1, 24, 23, 13, 7, 99, map_bolts2, enems_hotspots4, behs0_1, 1 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 24, 23, 12, 7, 99, map_bolts0, enems_hotspots0, behs0_1, 1 },
	{ 1, 24, 23, 12, 7, 99, map_bolts1, enems_hotspots1, behs0_1, 1 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 24, 23, 12, 7, 99, map_bolts0, enems_hotspots2, behs0_1, 1 },
	{ 1, 24, 23, 12, 7, 99, map_bolts1, enems_hotspots3, behs0_1, 1 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};
