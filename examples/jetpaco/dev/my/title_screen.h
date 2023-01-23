// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// You can change this function as fit

void title_screen (void) {
	blackout ();
	
	#ifdef MODE_128K
		get_resource (TITLE_BIN, BASE_SUPERBUFF);
	#else		
		unpack ((unsigned int) (s_title), BASE_SUPERBUFF);
	#endif
	
	_x = 10; _y = 7; _gp_gen = "SUPER SPECIAL"; print_str ();
	_x = 11; _y = 8; _gp_gen = "SPACE AGENT"; print_str ();

	_x = 17; _y = 13; _gp_gen = "1. POQA"; print_str ();
	         _y = 14; _gp_gen = "2. JOYSTICK"; print_str ();

	_x = 5; _y = 19; _gp_gen = "@ 2023 THE MOJON TWINS"; print_str ();
	_x = 7; _y = 20; _gp_gen = "MOJONTWINS.ITCH.IO"; print_str ();

	show_buffer_and_tiles ();

	#ifdef MUSIC_TITLE
		AY_PLAY_MUSIC (MUSIC_TITLE)
	#endif

	AY_PLAY_MUSIC (0);
	while (1) {
		if (cpc_TestKey (KEY_AUX3)) { _gp_gen = def_keys; break; }
		if (cpc_TestKey (KEY_AUX4)) { _gp_gen = def_keys_joy; break; }
	}	
	AY_STOP_SOUND ();

	// Copy keys to extern 
	#asm
		._copy_keys_to_extern
			ld  hl, (__gp_gen)
			ld  de, cpc_KeysData + 12
			ld  bc, 24
			ldir
	#endasm
}
