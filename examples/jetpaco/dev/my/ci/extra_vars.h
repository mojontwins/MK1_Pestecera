// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// Load the palete for Levels B & C here

#include "assets/pal1.h"
#include "assets/pal2.h"

// Variables to control GM (game mode) for level A or level B
// These arrays & gm will be used from before_game.h

unsigned char gm;

unsigned char gm_scr_ini [] = { 28, 63, 98 };
unsigned char gm_ini_x [] = { 5, 5, 5 };
unsigned char gm_ini_y [] = { 6, 6, 6 };
unsigned char gm_max_objects [] = { 20, 20, 20 };
unsigned char gm_hotspots_offset [] = { 0, 8, 0 };
unsigned char *gm_palette [] = { my_inks, my_inks1, my_inks2 };

unsigned char hotspots_offset;

// Mapped tilesets

unsigned char gm_ts_0 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
unsigned char gm_ts_1 = { 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47};
unsigned char gm_ts_2 = { 0, 1, 14, 47, 4, 5, 38, 39, 40, 9, 10, 2, 12, 45, 46, 41};
unsigned char *gm_ts_list [] = {gm_ts_0, gm_ts_1, gm_ts_2};

unsigned char *gm_ts;

// Propellers for gm == 1

#define PROPELLERS_MAX 10
unsigned char prop_n_pant [] = {40, 40, 40, 44, 44, 55, 57, 61, 63, 67};
unsigned char prop_x      [] = { 6,  4,  2,  1,  5, 12,  3,  9,  4,  3};
unsigned char prop_y      [] = { 3,  5,  7,  9,  9,  9,  9,  9,  9,  9};

#define PLAYER_AY_FLOAT 	48
#define PLAYER_VY_FLOAT_MAX 480
