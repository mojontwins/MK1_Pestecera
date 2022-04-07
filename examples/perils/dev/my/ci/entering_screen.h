// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// Check if n_pant == 20 && p_killed == BADDIES_COUNT
// then clear the spiked balls blocking the exit

// Print an "EXIT" sign on n_pant == 20

if (n_pant == 20) {
	if (p_killed == BADDIES_COUNT) {
		_x = 2; _y = 7; _t = _n = 0; update_tile ();
		_x = 2; _y = 8; _t = _n = 0; update_tile ();
	}

	// x = 1, y = 9, t = 17
	_x = 1; _y = 8; _t = 17; _n = 0; update_tile ();
}
