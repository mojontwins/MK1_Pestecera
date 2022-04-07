// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// If on screen 20 and gpx == 0, win game!

if (n_pant == 20) {
	if (gpx < 8) {
		success = 1;
		playing = 0;
	}

	// In case this happens exactly on screen 20
	if (p_killed == BADDIES_COUNT) {
		_x = 2; _y = 7; _t = _n = 0; update_tile ();
		_x = 2; _y = 8; _t = _n = 0; update_tile ();
	}
}