
// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// Select player

blackout_area ();

_x = 8; _y = 11; _gp_gen = "1. PACO (GAME A)"; print_str();
        _y = 12; _gp_gen = "2. PURI (GAME B)"; print_str();

#asm
		ld  bc, 0x0000 	// From 0, 0
		ld  de, 0x171F  // To 23, 31
		
		call cpc_InvalidateRect
#endasm
cpc_UpdateNow (0);

player_sprite_offset = 0;

// Punch the values directly inside the routine:

#asm
    ld  hl, PLAYER_G
    ld  (_player_gravity_add + 1), hl

    ld  hl, PLAYER_MAX_VY_CAYENDO
    ld  (_player_gravity_maximum + 1), hl

    ld  hl, PLAYER_MAX_VY_CAYENDO - PLAYER_G
    ld  (_player_gravity_comp1 + 1), hl

    ld  hl, -PLAYER_INCR_JETPAC
    ld  (_player_jetpac_increment + 1), hl

    ld  hl, -PLAYER_MAX_VY_JETPAC
    ld  (_player_jetpac_check_ld + 1), hl
#endasm

while (!cpc_TestKey (KEY_AUX3)) {
	if (cpc_TestKey (KEY_AUX4)) {
		player_sprite_offset = 16;

		#asm
		    ld  hl, 6
		    ld  (_player_gravity_add + 1), hl

		    ld  hl, 96
		    ld  (_player_gravity_maximum + 1), hl

		    ld  hl, 88
		    ld  (_player_gravity_comp1 + 1), hl

		    ld  hl, -16
		    ld  (_player_jetpac_increment + 1), hl

		    ld  hl, -96
		    ld  (_player_jetpac_check_ld + 1), hl
		#endasm
		break;
	}
}

// Outer game loop for fake multi - level

gm = 0; outer_game_loop = 1;

while (outer_game_loop) {

	hotspots_offset = gm_hotspots_offset [gm];	
	gm_ts = gm_ts_list [gm];

	blackout ();
	pal_set (my_inks);

	// Cutscene
	unpack ((unsigned int) (s_cuts), BASE_SUPERBUFF);

	_x = 6; _y = 14; _gp_gen = cuts_line1 [gm]; print_str ();
	        _y = 16; _gp_gen = cuts_line2 [gm]; print_str ();

	show_buffer_and_tiles ();

	espera_activa (5000);

	// Frame & hud
	unpack ((unsigned int) (s_frame), BASE_SUPERBUFF);
	draw_hud ();	

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

	blackout ();
	pal_set (gm_palette [gm]);
	show_buffer_and_tiles ();

	AY_PLAY_SOUND (1);
	espera_activa (100);

	/*
	blackout_area ();
	invalidate_viewport ();
	cpc_UpdateNow (0);
	*/

	// This while is closed in `my/ci/after_game.h`.
	// Constructs to exit this loop are found in game_over () and game_ending () @ my/fixed_screens.h

	// ...
