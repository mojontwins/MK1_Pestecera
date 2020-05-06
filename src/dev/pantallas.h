// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// Pantallas.h
// Carga las pantallas fijas
// Copyleft 2010 The Mojon Twins

#ifndef MODE_128K
	extern unsigned char s_title [];
	extern unsigned char s_marco [];
	extern unsigned char s_ending [];

	#asm
		._s_title
			BINARY "../bin/title.bin"
		._s_marco
	#endasm
	#ifndef DIRECT_TO_PLAY
		#asm
				BINARY "../bin/marco.bin"
		#endasm
	#endif
	#asm
		._s_ending
			BINARY "../bin/ending.bin"
	#endasm
#endif

void blackout (void) {
	#asm
			ld  a, c0
		.bo_l1
			ld  h, a
			ld  l, 0
			ld  (hl), 0
			ld  d, a
			ld  l, 1
			ld  bc, 1535
			ldir

			add 8
			jr  nz, bo_l1
	#endasm
}
