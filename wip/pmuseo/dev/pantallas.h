// MTE MK1 (la Churrera) v5.12
// Copyleft 2010-2014, 2020-2025 by the Mojon Twins

// Pantallas.h
// Carga las pantallas fijas
// Copyleft 2010 The Mojon Twins

#ifndef MODE_128K
	extern unsigned char s_title [];
	extern unsigned char s_marco [];
	extern unsigned char s_ending [];
	extern unsigned char s_intro [];
	extern unsigned char s_creditos [];


	#asm
		._s_title
			BINARY "../bin/titlec.bin"
		._s_marco
	#endasm
	#ifndef DIRECT_TO_PLAY
		#asm
				BINARY "../bin/marcoc.bin"
		#endasm
	#endif
	#asm
		._s_ending
			BINARY "../bin/endingc.bin"
	#endasm
	#asm
		._s_intro
			BINARY "../bin/introc.bin"
	#endasm
	#asm
		._s_creditos
			BINARY "../bin/creditosc.bin"
	#endasm
#endif

void blackout (void) {
	rda = BLACK_COLOUR_BYTE;
	#asm
			ld  a, 0xc0
		.bo_l1
			ld  h, a
			ld  l, 0
			ld  b, a
			ld  a, (_rda)
			ld  (hl), a
			ld  a, b
			ld  d, a
			ld  e, 1
			ld  bc, 0x5ff
			ldir

			add 8
			jr  nz, bo_l1
	#endasm
}

void show_buffer_and_tiles (void) {
	cpc_UpdScr ();
	cpc_ShowTileMap (1);
	cpc_ResetTouchedTiles ();
}
