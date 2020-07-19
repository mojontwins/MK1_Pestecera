// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

unsigned char decos_computer [] = { 0x63, 32, 0x73, 33, 0x83, 34, 0x64, 36, 0x74, 37, 0x84, 38, 0xff };
unsigned char decos_bombs [] = { 0x44, 17, 0x42, 17, 0x71, 17, 0xA2, 17, 0xA4, 17, 0xff };
unsigned char decos_moto [] = { 0x13, 40, 0x23, 41, 0xff };

unsigned char f_0, f_1;

#include "assets/pal_b.h"
#include "assets/pal_c.h"
#include "assets/pal_d.h"

unsigned char *level_pal [] = {
	0, 0, 
	my_inks, my_inks_2, 
	0,
	my_inks_3, my_inks_4,
	0
};

unsigned char *level_names [] = {
	" FIRST BOOT!",
	" GET'EM SAFE",
	"EVIL COMPUTER",
	"NIGHT MISSION",
	" PEACE MAKER",
	" GHOST ARMY!",
	" GHOST NIGHT",
	"BIKE RENEWAL!",
};

unsigned char *level_briefings [] = {
	"  MAKE YOUR WAY TO THE GOAL!",
	"      RESCUE 5 HOSTAGES",
	"",
	"",
	"STEAL THE PLANS WITH NO AMMO!",
	"",
	"",
	"  BLAST THE BIKE WITH A BOMB"
};

unsigned char l_is_classic [] = {
	0, 0, 1, 1, 0, 1, 1, 0
};
unsigned char c_is_classic;

unsigned char *c_screen_address;
