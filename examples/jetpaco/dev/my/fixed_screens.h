// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

void game_ending (void) {
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
}

void game_over (void) {
	_x = 10; _y = 11; _gp_gen = (unsigned char *) (spacer); print_str ();
	_x = 10; _y = 12; _gp_gen = " GAME OVER! "; print_str ();
	_x = 10; _y = 13; _gp_gen = (unsigned char *) (spacer); print_str ();
	
	cpc_UpdateNow (0);

	#ifdef MUSIC_GOVER
		AY_PLAY_MUSIC (MUSIC_GOVER);
	#endif
	espera_activa (500);
	#ifdef MUSIC_GOVER
		AY_STOP_SOUND ();
	#endif
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

#if defined COMPRESSED_LEVELS || defined ENABLE_ZONE_CLEAR
	void zone_clear (void) {
		_x = 10; _y = 11; _gp_gen = (unsigned char *)(spacer); print_str ();
		_x = 10; _y = 12; _gp_gen = " ZONE CLEAR "; print_str ();
		_x = 10; _y = 13; _gp_gen = (unsigned char *)(spacer); print_str ();
		
		cpc_UpdateNow (0);
		#ifdef MUSIC_SCLEAR
			AY_PLAY_MUSIC (MUSIC_SCLEAR);
		#endif
		espera_activa (250);
		#ifdef MUSIC_SCLEAR
			AY_STOP_SOUND ();
		#endif		
	}
#endif
