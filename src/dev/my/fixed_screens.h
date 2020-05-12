// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

void game_ending (void) {
	blackout ();
	#ifdef MODE_128K
		// Resource 2 = ending
		get_resource (ENDING_BIN, BASE_SUPERBUFF);
	#else
		#asm
			ld hl, _s_ending
			ld de, BASE_SUPERBUFF
			call depack
		#endasm
	#endif
	cpc_ShowTileMap (1);
	
	espera_activa (500);
}

void game_over (void) {
	_x = 10; _y = 11; _t = 79; _gp_gen = spacer; print_str ();
	_x = 10; _y = 12; _t = 79; _gp_gen = " GAME OVER! "; print_str ();
	_x = 10; _y = 13; _t = 79; _gp_gen = spacer; print_str ();
	
	cpc_ShowTileMap (0);

	espera_activa (500);
}

#if defined(TIMER_ENABLE) && defined(SHOW_TIMER_OVER)
	void time_over (void) {
		_x = 10; _y = 11; _t = 79; _gp_gen = spacer; print_str ();
		_x = 10; _y = 12; _t = 79; _gp_gen = " TIME'S UP! "; print_str ();
		_x = 10; _y = 13; _t = 79; _gp_gen = spacer; print_str ();
		
		cpc_ShowTileMap (0);
			
		espera_activa (250);
	}
#endif

#ifdef PAUSE_ABORT
	void pause_screen (void) {
		_x = 10; _y = 11; _t = 79; _gp_gen = spacer; print_str ();
		_x = 10; _y = 12; _t = 79; _gp_gen = "   PAUSED   "; print_str ();
		_x = 10; _y = 13; _t = 79; _gp_gen = spacer; print_str ();
		
		cpc_ShowTileMap (0);
	}
#endif

#ifdef COMPRESSED_LEVELS
	void zone_clear (void) {
		_x = 10; _y = 11; _t = 79; _gp_gen = spacer; print_str ();
		_x = 10; _y = 12; _t = 79; _gp_gen = " ZONE CLEAR "; print_str ();
		_x = 10; _y = 13; _t = 79; _gp_gen = spacer; print_str ();
		
		cpc_ShowTileMap (0);
		espera_activa (250);			
	}
#endif
