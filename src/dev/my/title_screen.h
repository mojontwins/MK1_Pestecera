// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// You can change this function as fit

void title_screen (void) {
	blackout ();
	
	#ifdef MODE_128K
		get_resource (TITLE_BIN, BASE_SUPERBUFF);
		AY_PLAY_MUSIC (0);
	#else		
		#asm
			ld hl, _s_title
			ld de, BASE_SUPERBUFF
			call depack
		#endasm
	#endif
			
	cpc_ShowTileMap (1);

	// Do a simple 0 start/1 redefine menu
	while (1) {
		if (cpc_TestKey (KEY_AUX3)) { _gp_gen = def_keys; break; }
		if (cpc_TestKey (KEY_AUX4)) { _gp_gen = def_keys_joy; break; }
	}	

	// Copy keys to extern 
	#asm
		._copy_keys_to_extern
			ld  hl, (__gp_gen)
			ld  de, cpc_KeysData + 12
			ld  bc, 12
			ldir
	#endasm
}
