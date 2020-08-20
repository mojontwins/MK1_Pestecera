// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// This code is ran just before looping back to the title screen

// COMPRESSED_LEVELS: Note that `continue` here would restart the main loop
// (i.e. reload current level).

// Continue screen
if (level) {
	#ifdef LANG_ES
		_x = 10; _y = 12; _gp_gen = " CONTINUAR?"; print_str ();
		_x = 10; _y = 13; _gp_gen = "   1   SI   "; print_str ();
		_x = 10; _y = 14; _gp_gen = "   2   NO   "; print_str ();
	#else
		_x = 10; _y = 12; _gp_gen = " CONTINUE? "; print_str ();
		_x = 10; _y = 13; _gp_gen = "   1   YES  "; print_str ();
		_x = 10; _y = 14; _gp_gen = "   2   NO   "; print_str ();
	#endif

	_x = 10; _y = 15; _gp_gen = spacer; print_str ();
	cpc_UpdateNow (0);

	rda = 0;
	while (!cpc_TestKey (KEY_AUX4)) {
		if (cpc_TestKey (KEY_AUX3)) { rda = 1; break; }
	}

	if (rda) continue;
}
