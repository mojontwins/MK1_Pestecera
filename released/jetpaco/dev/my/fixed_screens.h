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

		// Switch palette
		pal_set (my_inks_ending);

		#ifdef MODE_128K
			// Resource 2 = ending
			get_resource (ENDING_BIN, BASE_SUPERBUFF);
		#else
			unpack ((unsigned int) (s_ending), BASE_SUPERBUFF);
		#endif
		
		_x = 4; _y = 12; _gp_gen = "FUEL TANKS REPLENISHED"; print_str ();
		_x = 3; _y = 14; _gp_gen = "ON TO THE NEXT ADVENTURE"; print_str ();

		show_buffer_and_tiles ();
		
		#ifdef MUSIC_ENDING
			AY_PLAY_MUSIC (MUSIC_ENDING)
		#endif
		espera_activa (22222);
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

	// Show continue option if we got past the 1st level
	if (gm) {
		#ifdef LANG_ES
			_x = 10; _y = 11; _gp_gen = " CONTINUAR?"; print_str ();
			         _y = 12; _gp_gen = "   1   SI   "; print_str ();
			         _y = 13; _gp_gen = "   2   NO   "; print_str ();
		#else
			_x = 10; _y = 11; _gp_gen = " CONTINUE? "; print_str ();
			         _y = 12; _gp_gen = "   1   YES  "; print_str ();
			         _y = 13; _gp_gen = "   2   NO   "; print_str ();
		#endif

		cpc_UpdateNow (0);

		while (!cpc_TestKey (KEY_AUX3)) {
			if (cpc_TestKey (KEY_AUX4)) {
				outer_game_loop = 0;		// Exit outter game loop!
				break;
			}
		}

		// Otherwise just repeat the level!
	}
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
