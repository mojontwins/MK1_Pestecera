
// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// Select player

blackout_area ();

_x = 8; _y = 11; _gp_gen = "1. PACO (NORMAL)"; print_str();
        _y = 12; _gp_gen = "2. PURI (EASY)"; print_str();

invalidate_viewport ();
cpc_UpdateNow (0);

player_sprite_offset = 0;
while (!cpc_TestKey (KEY_AUX3)) {
	if (cpc_TestKey (KEY_AUX4)) {
		player_sprite_offset = 16;		// Exit outter game loop!
		break;
	}
}

// Outer game loop for fake multi - level

gm = 0; outer_game_loop = 1;

while (outer_game_loop) {

	hotspots_offset = gm_hotspots_offset [gm];
	pal_set (gm_palette [gm]);

	gm_ts = gm_ts_list [gm];

	blackout_area ();	
	level_str [7] = 49 + gm;
	_x = 12; _y = 12; _gp_gen = level_str; print_str ();
	
	// Update HUD as well:
	#asm
			ld  a, 30
			ld  (__x), a
			ld  a, 21 
			ld  (__y), a 
			call __tile_address 		;; DE -> nametable address 

			ld  a, (_gm)
			add 17
			ld  (de), a 

			ld  a, (__x)
			ld  e, a 
			ld  a, (__y)
			ld  d, a 
			call cpc_UpdTileTable
	#endasm

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
