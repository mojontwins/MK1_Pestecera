// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

void blackout_area (void) {
	#asm
			xor a 
			ld  hl, _nametable
			ld  (hl), a
			ld  de, _nametable+1
			ld  bc, 767
			ldir
	#endasm
}