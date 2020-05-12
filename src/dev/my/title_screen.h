// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// You can change this function. To set level to anything different than 0.

{
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

	select_joyfunc ();
}
