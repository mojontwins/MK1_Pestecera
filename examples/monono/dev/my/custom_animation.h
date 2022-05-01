// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// custom_animation.h

// If you define PLAYER_CUSTOM_ANIMATION you have to add code here
// You should end up giving a value to spr_sw [SP_PLAYER].sp0
// (cast to int)

// You can use the array sm_sprptr [] which contains pointers to the
// frames in your spriteset.

// i.e. 
// spr_sw [SP_PLAYER].sp0 = (int) (sm_sprptr [0]);

/*
if (p_killme) {
	gpit = 3;
} else if (possee || p_gotten) {
	if (p_vx == 0) gpit = 1;
	else {
		gpit = ((gpx + 4) >> 3) & 3; if (gpit == 3) gpit = 1;
	}
} else if (p_vy < 0) {
	gpit = 2;
} else if (p_vy >= (PLAYER_MAX_VY_SALTANDO/6)) {
	gpit = 0;
} else gpit = 1;

gpit += (p_facing ? 0 : 4);
*/

#asm
	// 1.- Check if player was hit

	._pca_hit
		ld  a, (_p_killme)
		or  a
		jr  z, _pca_possee
		ld  c, 3
		jr  _pca_add_facing


	// 2.- Check if player is on foot

	._pca_possee
		ld  a, (_possee)
		or  a
		jr  nz, _pca_possee_do

		ld  a, (_p_gotten)
		or  a
		jr  z, _pca_ascending

	._pca_possee_do
		// PVX is 16 bits, we just need to check if it's zero or not
		ld  a, (_p_vx)
		ld  hl, _p_vx + 1
		or  (hl)		
		
		jr  z, _pca_possee_walking

		ld  c, 1 
		jr  _pca_add_facing
	._pca_possee_walking

		// gpit = ((gpx + 4) >> 3) & 3; if (gpit == 3) gpit = 1;
		ld  a, (_gpx)
		add 4
		srl a 
		srl a 
		srl a 
		and 3

		ld  c, a 

		cp  3
		jr  nz, _pca_add_facing

		ld  c, 1
		jr  _pca_add_facing

	// 3.- Check if player is ascending

	._pca_ascending
		// (p_vy < 0)
		// p_vy is 16 bits, just check the MSB's bit 7	
		ld  a, (_p_vy + 1)
		bit 7, a 
		jr  z, _pca_floating

		ld  c, 2
		jr  _pca_add_facing

	._pca_floating
		// (p_vy >= (PLAYER_MAX_VY_SALTANDO/6))
		// p_vy is 16 bits and positive. We can do straight unsigned 16 bits comparison
		ld  hl, (_p_vy)
		ld  de, 85 // PLAYER_MAX_VY_SALTANDO/6
		or  a
		sbc hl, de 
		jr  c, _pca_descending

		ld  c, 0
		jr  _pca_add_facing

	._pca_descending
		ld  c, 1

	._pca_add_facing
		// (p_facing ? 0 : 4)
		ld  a, (_p_facing)
		or  a 
		jr  z, _pca_add_facing_do

		ld  a, c
		jr  _pca_done 

	._pca_add_facing_do
		ld  a, 4 
		add c

	._pca_done

		ld  (_gpit), a
#endasm

sp_sw [SP_PLAYER].sp0 = (int) (sm_sprptr [gpit]);
