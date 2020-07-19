// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

void ingame_text (void) {
	// Point _gp_gen to the string to be print.
	_x = 1; _y = 0; print_str ();
}

void win_level (void) {
	AY_PLAY_SOUND (0);
	espera_activa (50);
	success = 1;
	playing = 0;
}
