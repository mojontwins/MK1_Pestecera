// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// This is run once per tile print in the map renderer. you can change _t
// as fit.

// If you add code, add this as well, at the end of this file:
/*
	#asm
			ld  a, (__t)
	#endasm
*/
// or somewhat make sure _t is into the A register as well

#asm
		// A = _t at this point!
		or  a 
		jr  nz, _MRTM_skip1

		ld  hl, _map_buff
		add hl, bc 
		ld  de, 15
		sbc hl, de 	// No need to reset carry
		ld  a, (hl)
		cp  7
		jr  nz, _MRTM_skip1

		ld  a, 23
		ld  (__t), a

	._MRTM_skip1
#endasm