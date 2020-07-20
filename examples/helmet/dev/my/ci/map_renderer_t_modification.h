// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// This is run once per tile print in the map renderer. you can change _t
// as fit.

#asm
		ld  a, (__t)
		or  a
		jr  nz, _ds_custom_packed_noalt

		// Alt tile #2

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

		// Hostages, tile == 13?
		cp  13
		jr  nz, _ds_custom_end

		// On level 1?
		ld  a, (_level)
		dec a
		jr  nz, _ds_custom_end

		// Clear behs
		ld  a, 128
		ld  hl, _map_attr
		add hl, bc
		ld  (hl), a

		ld  a, 21
		ld  (__t), a

	._ds_custom_end
#endasm
