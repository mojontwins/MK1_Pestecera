// MTE MK1 (la Churrera) v5.11
// Copyleft 2010-2014, 2020-2025 by the Mojon Twins

// Levels.h

// Contains data structures used for multi level games
// Prepared for 128K level bundles and standard 48K levels

// Usually, 48K levels use the same sprites for all levels
// unless PER_LEVEL_SPRITESET is defined in 48K mode.

// Level bundles used in 128K games contain:
// Level data, 16 bytes
// Map data, 75 or 150 * (MAP_W*MAP_H) bytes
// Bolts, 32 * 4 = 128 bytes
// Tileset, 2304 bytes
// Enemies, MAP_W * MAP_H * MAX_ENEMS * 10 bytes
// Hotspots, MAP_W * MAP_H * 3 bytes
// Behs, 48 bytes
// Spriteset, 2312 bytes

// Definitions

// You can adjust this number if you need the bytes **ONLY** in 48K mode.
#define MAX_CERROJOS 32

// Types:

typedef struct {
	unsigned char map_w, map_h;
	unsigned char scr_ini, ini_x, ini_y;
	unsigned char max_objs;
	unsigned char enems_life;
	unsigned char d01;	// Reserved
	unsigned char d02;
	unsigned char d03;
	unsigned char d04;
	unsigned char d05;
	unsigned char d06;
	unsigned char d07;
	unsigned char d08;
	unsigned char d09;
} LEVELHEADER;

typedef struct {
    unsigned char np, x, y, st;
} CERROJOS;

typedef struct {
	unsigned char x, y;
	unsigned char x1, y1, x2, y2;
	char mx, my;
	unsigned char t, life;
} MALOTE;

typedef struct {
	unsigned char xy, tipo, act;
} HOTSPOT;

// This space will be overwritten by level data

extern LEVELHEADER level_data;
#asm
	._level_data defs 16
#endasm

extern unsigned char mapa [0];
#ifdef UNPACKED_MAP
	#asm
		._mapa defs MAP_W * MAP_H * 150
	#endasm
#else
	#asm
		._mapa defs MAP_W * MAP_H * 75
	#endasm
#endif

#ifndef DEACTIVATE_KEYS
	extern CERROJOS cerrojos [0];
	#asm
		._cerrojos defs 128	; 32 * 4
	#endasm
#endif

extern unsigned char tileset [0];
#asm
		XDEF tiles
	._tileset
	.tiles
	._font 
		BINARY "../bin/font.bin"
#endasm

extern unsigned char tspatterns [0];
#asm
	._tspatterns
	#ifdef PER_LEVEL_TILESET
		defs 3072 	// 16*192
	#else
		BINARY "../bin/work.bin"
	#endif
#endasm

extern MALOTE malotes [0];
#asm
	._malotes defs MAP_W * MAP_H * MAX_ENEMS * 10
#endasm

extern HOTSPOT hotspots [0];
#asm
	._hotspots defs MAP_W * MAP_H * 3
#endasm

extern unsigned char behs [0];
#asm
	._behs defs 48
#endasm

#if defined MODE_128K || defined PER_LEVEL_SPRITESET
	#include "assets/sprites-empty.h"
#else
	#include "assets/sprites.h"
#endif
