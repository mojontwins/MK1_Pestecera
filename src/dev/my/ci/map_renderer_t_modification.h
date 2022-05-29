// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// This is run once per tile print in the map renderer. you can change _t
// as fit.

#asm
		// is in A as well
		or  a 
		jr  nz, mrtm_skip1

		ld  hl, _map_buff 
		add hl, bc 
		ld  de, 16
		sbc hl, de
		cp  7
		jr  nz, mrtm_skip1

		ld  a, 23
		ld  (__t), 23

	.mrtm_skip1	
#endasm