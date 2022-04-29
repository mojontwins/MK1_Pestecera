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


if (p_killme) {
	gpit = 3;
} else if (possee || p_gotten) {
	if (p_vx == 0) gpit = 0;
	else {
		gpit = ((gpx + 4) >> 3) & 3;
		if (gpit == 3) gpit = 1;
	}
} else if (p_vy < 0) {
	gpit = 2;
} else if (p_vy >= (PLAYER_MAX_VY_SALTANDO/6)) {
	gpit = 0;
} else gpit = 1;

gpit += (p_facing ? 0 : 4);

sp_sw [SP_PLAYER].sp0 = (int) (sm_sprptr [gpit]);
