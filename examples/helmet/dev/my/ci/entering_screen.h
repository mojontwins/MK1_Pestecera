// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// For all screens

// Precalc this address which will be used with broken tile 
// persistence.

c_screen_address = mapa + n_pant * 75;

// General text & decorations

_gp_gen = level_briefings [level];

if (c_is_classic) {
	#ifdef LANG_ES
		_gp_gen = " PON 5 BOMBAS EN EL ORDENADOR";
	#else
		_gp_gen = " SET 5 BOMBS IN EVIL COMPUTER";
	#endif
	if (n_pant == 0) {
		_gp_gen = decos_computer; draw_decorations ();
		if (f_1) {
			_gp_gen = decos_bombs; draw_decorations ();
			#ifdef LANG_ES
				_gp_gen = "BOMBAS PUESTAS! VUELVE A BASE!";
			#else
				_gp_gen = "BOMBS ARE SET! RETURN TO BASE!";
			#endif
		} else {
			#ifdef LANG_ES
				_gp_gen = " ACERCATE Y COLOCA LAS BOMBAS";
			#else
				_gp_gen = "  SET BOMBS IN EVIL COMPUTER";
			#endif
		}
	} else {
		if (level > 4 && n_pant < 23) {
			#ifdef LANG_ES
				_gp_gen = "MATA FANTASMAS,CONSIGUE LLAVES";
			#else
				_gp_gen = " KILL GHOSTS TO COLLECT KEYS!";
			#endif
		}
	}
} 
if (level != 1 || (n_pant == 17 && f_3)) ingame_text ();
f_3 = 0;

// Half new motorcycle for sale

if (n_pant == 21 && (level == 2 || level == 5)) {
	_gp_gen = decos_moto; draw_decorations ();
	f_0 = 1;
} else f_0 = 0;

// Last level motorcycle

if (level == 7 && n_pant == 5) {
	_gp_gen = decos_moto; draw_decorations ();
}

// Ending condition

if (n_pant == 23 && f_1) win_level ();
