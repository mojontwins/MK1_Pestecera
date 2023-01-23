// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// Load the palete for Levels B & C here

#include "assets/pal1.h"
#include "assets/pal2.h"

// Ending also has a different palette

#include "assets/pal_ending.h"

// This variable will control the custom outter game loop.

unsigned char outer_game_loop;

#ifdef LANG_ES
	unsigned char *level_str = "NIVEL 0X";
#else
	unsigned char *level_str = "LEVEL 0X";
#endif

// Paco / Puri sutff
// 0 for paco, 16 for puri
unsigned char player_sprite_offset = 16;

unsigned int p_g;
unsigned int p_max_vy_g;
unsigned int p_g_minus_max_vy_g;

unsigned int p_jetpac;
unsigned int p_max_vy_j;

// Variables to control GM (game mode) for level A, B or C
// These arrays & gm will be used from before_game.h

#define GM_PROPELLERS_LEVEL   0
#define GM_ESTRUJATORS_LEVEL  1

unsigned char gm;

unsigned char gm_scr_ini [] = { 63, 98, 28 };
unsigned char gm_ini_x [] = { 5, 5, 5 };
unsigned char gm_ini_y [] = { 6, 5, 6 };
unsigned char gm_max_objects [] = { 20, 20, 20 };
unsigned char gm_hotspots_offset [] = { 8, 0, 0 };
unsigned char *gm_palette [] = { my_inks1, my_inks2, my_inks };
unsigned char gm_music_ingame [] = { 6, 1, 5 };

unsigned char hotspots_offset;

// Mapped tilesets

unsigned char gm_ts_0 [] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 32 };
unsigned char gm_ts_1 [] = { 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47};
unsigned char gm_ts_2 [] = { 23, 28, 36, 15, 4, 5, 38, 39, 40, 9, 10, 2, 29, 45, 46, 41};
unsigned char *gm_ts_list [] = {gm_ts_1, gm_ts_2, gm_ts_0};

unsigned char *gm_ts;

// Propellers for gm == GM_PROPELLERS_LEVEL

#define PROPELLERS_MAX 10
unsigned char prop_n_pant [] = {40, 40, 40, 44, 44, 55, 57, 61, 63, 67};
unsigned char prop_x      [] = { 6,  4,  2,  1,  5, 12,  3,  9,  4,  3};
unsigned char prop_y      [] = { 3,  5,  7,  9,  9,  9,  9,  9,  9,  9};

#define PLAYER_AY_FLOAT 	32
#define PLAYER_VY_FLOAT_MAX 256

// Estrujators for gm == GM_ESTRUJATORS_LEVEL

#define ESTRUJATORS_MAX 34

unsigned char estr_n_pant [] = { 
	 70,  74,  73,  73,  75,  76,  71,  71,  
	 82,  77,  77,  85,  85,  88,  88,  84,  
	 84,  91,  92,  92,  91,  92,  94,  93,  
	 99,  99,  98, 101, 102, 102,  98,  98, 
	103, 103 
};

unsigned char estr_t []      = {
	  0,   1,   0,   1,   2,   2,   1,   1,
	  0,   0,   1,   0,   0,   0,   1,   1,
	  1,   1,   0,   1,   1,   2,   1,   0,
	  0,   1,   0,   0,   0,   0,   2,   0,
	  1,   1 
};

unsigned char estr_x []      = {
	  7,   1,   2,   5,  14,   0,   3,   9,
	  3,   5,   9,   3,   4,   6,   9,   9, 
	 13,  11,   4,   5,  11,   6,   5,  13,
	  3,   4,  13,   3,   9,  12,   3,  13,
	  6,   8
};

unsigned char estr_y []      = {  
	  2,   4,   5,   5,   5,   5,   6,   6,
	  1,   6,   6,   2,   2,   3,   3,   6, 
	  6,   1,   1,   1,   5,   5,   5,   6, 
	  1,   1,   2,   3,   3,   3,   6,   6, 
	  6,   6
};

// Puff of smoke

extern unsigned char spr_jumo [0];
#asm
	._spr_jumo
		BINARY "../bin/sprites_humo.bin"
#endasm

unsigned char jumo_x;
unsigned char jumo_y;
unsigned char jumo_fr;
unsigned char jumo_ct;

// Chac chac plugin for estrujators

#include "plugins/plugin_chac_chacs.h"	

// Cutscene bitmap

extern unsigned char s_cuts [0];
#asm
	._s_cuts
		BINARY "../bin/cutsc.bin"
#endasm

// Cutscene texts
unsigned char cuts_line1_0 [] = "LOST IN SPACE...";
unsigned char cuts_line2_0 [] = "IN THIS ORGANIC BASE";
unsigned char cuts_line1_1 [] = "YOU BETTER RUSH";
unsigned char cuts_line2_1 [] = "OR YOU'LL GET CRUSHED!";
unsigned char cuts_line1_2 [] = "THIS LOOKS FAMILIAR";
unsigned char cuts_line2_2 [] = "M.T. ARE SO CHEAP!";

unsigned char *cuts_line1 [] = { cuts_line1_0, cuts_line1_1, cuts_line1_2 };
unsigned char *cuts_line2 [] = { cuts_line2_0, cuts_line2_1, cuts_line2_2 };

// Frame bitmap - include by hand as we are showing it in a custom way

extern unsigned char s_frame [0];
#asm
	._s_frame
		BINARY "../bin/marcoc.bin"
#endasm
