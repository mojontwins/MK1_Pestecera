// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// Load the palete for Level B here

#include "assets/pal1.h"

// Variables to control GM (game mode) for level A or level B
// These arrays & gm will be used from before_game.h

unsigned char gm;

unsigned char gm_scr_ini [] = { 28, 63 };
unsigned char gm_ini_x [] = { 5, 5 };
unsigned char gm_ini_y [] = { 6, 6 };
unsigned char gm_max_objects [] = { 20, 20 };
unsigned char gm_tile_offset [] = { 0, 32 };
unsigned char gm_hotspots_offset [] = { 0, 8 };
unsigned char *gm_palette [] = { my_inks, my_inks1 };

unsigned char tile_offset, hotspots_offset;

// Propellers for gm == 1

#define PROPELLERS_MAX 10
unsigned char prop_n_pant [] = {40, 40, 40, 44, 44, 55, 57, 61, 63, 67};
unsigned char prop_x      [] = { 6,  4,  2,  1,  5, 12,  3,  9,  4,  3};
unsigned char prop_y      [] = { 3,  5,  7,  9,  9,  9,  9,  9,  9,  9};

#define PLAYER_AY_FLOAT 	64
#define PLAYER_VY_FLOAT_MAX 512
