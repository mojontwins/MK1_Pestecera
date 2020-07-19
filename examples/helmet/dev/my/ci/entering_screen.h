// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// For all screens

// Precalc this address which will be used with broken tile 
// persistence.

c_screen_address = mapa + n_pant * 75;

// General text

if (c_is_classic) {
	if (f_1) {
		_gp_gen = "BOMBS ARE SET! RETURN TO BASE!";
	} else {
		if (level == 2 && n_pant < 22) {
			_gp_gen = " KILL GHOSTS TO COLLECT KEYS!";
		} else {
			_gp_gen = " SET 5 BOMBS IN EVIL COMPUTER";	
		}
	}
} else {
	_gp_gen = level_briefings [level];
}
_x = 1; _y = 0; _t = 71;
print_str ();

// Screen 0: Paint computer / bomb & message

if (n_pant == 0 && c_is_classic) {
	_gp_gen = decos_computer; draw_decorations ();

	if (f_1) {
		_gp_gen = decos_bombs; draw_decorations ();
	} else {
		_gp_gen = " SET BOMBS IN EVIL COMPUTER ";
		_x = 1; _y = 0; _t = 71;
		print_str ();
	}
}

// Half new motorcycle for sale

if (n_pant == 21 && (level == 2 || level == 5)) {
	_gp_gen = decos_moto; draw_decorations ();
	f_0 = 1;
} else f_0 = 0;

// Ending condition

if (n_pant == 23 && f_1) {
	AY_PLAY_SOUND (0);
	espera_activa (50);
	success = 1;
	playing = 0;
}
