// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

void ingame_text (void) {
	// Point _gp_gen to the string to be print.
	_x = 1; _y = 0; print_str ();
}

void win_level (void) {
	AY_STOP_SOUND ();
	AY_PLAY_SOUND (0);
	espera_activa (50);
	success = 1;
	playing = 0;
}

void persist_tile (void) {
	// c_screen_address must be set
	// gpaux must be COORDS (_x, _y)
	// rdt = substitute with this tile
	
	_gp_gen = (c_screen_address + (gpaux >> 1));
	rda = *_gp_gen;

	if (gpaux & 1) {
		// Modify right nibble
		rda = (rda & 0xf0) | rdt;
	} else {
		// Modify left nibble
		rda = (rda & 0x0f) | (rdt<<4);
	}

	*_gp_gen = rda;
}