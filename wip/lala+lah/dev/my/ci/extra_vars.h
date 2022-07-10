// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// Lala Lah palette (prologue's is the default one)

#include "assets/pal1.h"

// Variables to control GM (game mode) Prologue (0) or Lah (1)

unsigned char gm;

unsigned char gm_scr_ini [] = { 24, 47 };
unsigned char gm_ini_x [] = { 1, 13 };
unsigned char gm_ini_y [] = { 2, 7 };
unsigned char gm_max_objects [] = { 25, 12 };
unsigned char gm_tile_offset [] = { 0, 32 };
unsigned char gm_hotspots_offset [] = { 0, 8 };
unsigned char *gm_palette [] = { my_inks, my_inks1 };

unsigned char tile_offset, hotspots_offset;

// These arrays & gm will be used from before_game.h
