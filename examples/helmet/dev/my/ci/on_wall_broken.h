// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// _x, _y = coordinates of broken walls.
// gp_aux = COORDS (_x, _y)

// Persistent broken blocks for packed maps
// This routine relies on precalculating current screen address in 
// c_screen_address, which is performed in `entering_screen.h`.

_gp_gen = (c_screen_address + (gpaux >> 1));
rda = *_gp_gen;

if (gpaux & 1) {
	// Modify right nibble
	rda = (rda & 0xf0) | BREAKABLE_WALLS_BROKEN;
} else {
	// Modify left nibble
	rda = (rda & 0x0f) | (BREAKABLE_WALLS_BROKEN<<4);
}

*_gp_gen = rda;
