// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

#define ENABLE_ZONE_CLEAR

void req (void) {
	_x = 10; _y = 12; print_str ();
	_y = 11; _gp_gen = (unsigned char *)(spacer); print_str ();
	_y = 13; print_str ();

	cpc_UpdateNow (0);
}

#if defined COMPRESSED_LEVELS || defined ENABLE_ZONE_CLEAR
	void zone_clear (void) {		
		_gp_gen = " ZONE CLEAR "; req ();
		
		#ifdef MUSIC_SCLEAR
			AY_PLAY_MUSIC (MUSIC_SCLEAR);
		#endif
		espera_activa (250);
		#ifdef MUSIC_SCLEAR
			AY_STOP_SOUND ();
		#endif

		blackout_area ();
		invalidate_viewport ();
		cpc_UpdateNow (0);
	}
#endif

void game_ending (void) {
	// Rather custom code.
	zone_clear ();
	gm ++;
	
	if (gm == 3) {
		blackout ();
		#ifdef MODE_128K
			// Resource 2 = ending
			get_resource (ENDING_BIN, BASE_SUPERBUFF);
		#else
			unpack ((unsigned int) (s_ending), BASE_SUPERBUFF);
		#endif
		cpc_ShowTileMap (1);
		
		#ifdef MUSIC_ENDING
			AY_PLAY_MUSIC (MUSIC_ENDING)
		#endif
		espera_activa (500);
		#ifdef MUSIC_ENDING
			AY_STOP_SOUND ();
		#endif
		
		outer_game_loop = 0; 		// Exit outter game loop!
	}
}

void game_over (void) {
	_gp_gen = " GAME OVER! "; req ();

	#ifdef MUSIC_GOVER
		AY_PLAY_MUSIC (MUSIC_GOVER);
	#endif
	espera_activa (500);
	#ifdef MUSIC_GOVER
		AY_STOP_SOUND ();
	#endif

	// TODO: Continue

	outer_game_loop = 0;		// Exit outter game loop!
}

#if defined(TIMER_ENABLE) && defined(SHOW_TIMER_OVER)
	void time_over (void) {
		_x = 10; _y = 11; _gp_gen = (unsigned char *)(spacer); print_str ();
		_x = 10; _y = 12; _gp_gen = " TIME'S UP! "; print_str ();
		_x = 10; _y = 13; _gp_gen = (unsigned char *)(spacer); print_str ();
		
		cpc_UpdateNow (0);
		espera_activa (250);
	}
#endif

#ifdef PAUSE_ABORT
	void pause_screen (void) {
		_x = 10; _y = 11; _gp_gen = (unsigned char *)(spacer); print_str ();
		_x = 10; _y = 12; _gp_gen = "   PAUSED   "; print_str ();
		_x = 10; _y = 13; _gp_gen = (unsigned char *)(spacer); print_str ();
		
		cpc_UpdateNow (0);
	}
#endif
