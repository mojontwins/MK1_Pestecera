// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// This is run once per tile print in the map renderer. you can change _t
// as fit.

#asm
		ld  a, (__t)
		or  a
		jr  nz, _ds_custom_packed_noalt

	._ds_custom_packed_alt
		call _rand
		ld  a, l
		and 15
		cp  1
		jr  z, _ds_custom_packed_alt_subst

		ld  a, (__t)
		jr  _ds_custom_packed_noalt

	._ds_custom_packed_alt_subst
		ld  a, 30
		ld  (__t), a

	._ds_custom_packed_noalt
#endasm
