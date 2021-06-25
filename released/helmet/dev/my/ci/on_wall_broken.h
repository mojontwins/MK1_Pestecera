// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// _x, _y = coordinates of broken walls.
// gp_aux = COORDS (_x, _y)

// Persistent broken blocks for packed maps
// This routine relies on precalculating current screen address in 
// c_screen_address, which is performed in `entering_screen.h`.

rdt = BREAKABLE_WALLS_BROKEN; persist_tile ();
