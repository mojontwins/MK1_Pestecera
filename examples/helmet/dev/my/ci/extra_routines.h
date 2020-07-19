// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

if (c_is_classic && n_pant == 0 && f_1 == 0 && gpy < 96 && p_objs == 5) {
	f_1 = 1;

	// Animation
	_gp_gen = decos_bombs;
	for (gpit = 0; gpit < 5; ++ gpit) {
		rda = *_gp_gen; _gp_gen += 2;
		_x = rda >> 4; _y = rda & 15; _t = 17;
		update_tile ();
		cpc_UpdateNow (1);
		AY_PLAY_SOUND (SFX_ENEMY_HIT);
		espera_activa (25);
	}

	#ifdef LANG_ES
		_gp_gen = "  HECHO! AHORA VUELVE A BASE  ";
	#else
		_gp_gen = "  DONE! NOW GO BACK TO BASE!  ";
	#endif
	ingame_text ();
}

if (f_0) {
	if (gpx < 64 && gpy >= 16 && gpy < 80) {
		f_0 = 0;
		AY_PLAY_SOUND (SFX_START);
		#ifdef LANG_ES
			_gp_gen = "     VENDO MOTO SEMINUEVA     ";
		#else
			_gp_gen = " HALF NEW MOTORBIKE FOR SALE! ";
		#endif
		ingame_text ();
	}
}

// Special endings for extended levels
if (level == 0 && n_pant == 18 && gpy < 48) win_level ();
