// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

gm = 0; outer_game_loop = 1;

while (outer_game_loop) {

	hotspots_offset = gm_hotspots_offset [gm];
	pal_set (gm_palette [gm]);

	gm_ts = gm_ts_list [gm];

	blackout_area ();	
	level_str [7] = 49 + gm;
	_x = 12; _y = 12; _gp_gen = level_str; print_str ();
	invalidate_viewport ();
	cpc_UpdateNow (0);

	AY_PLAY_SOUND (1);
	espera_activa (100);

	blackout_area ();
	invalidate_viewport ();
	cpc_UpdateNow (0);

	// This while is closed in `my/ci/after_game.h`.
	// Constructs to exit this loop are found in game_over () and game_ending () @ my/fixed_screens.h

	// ...
