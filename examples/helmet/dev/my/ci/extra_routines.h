// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

if (n_pant == 0 && f_1 == 0 && gpy < 96 && p_objs == 5) {
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

	_x = 1; _y = 0; _t = 71; 
	_gp_gen = "  DONE! NOW GO BACK TO BASE!  ";
	print_str ();
}

if (f_0) {
	if (gpx < 64 && gpy >= 16 && gpy < 80) {
		f_0 = 0;
		AY_PLAY_SOUND (SFX_START);
		espera_activa (25);
		_x = 1; _y = 0; _t = 71; 
		_gp_gen = " HALF NEW MOTORBIKE FOR SALE! ";
		print_str ();
	}
}
