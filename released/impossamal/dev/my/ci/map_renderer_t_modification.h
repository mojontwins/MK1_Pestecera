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

// Note that this ONLY CHANGES THE TILE # BEING DRAWN, 
// the original beh is written to the array