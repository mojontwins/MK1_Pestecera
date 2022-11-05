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

if (p_on_rope) {
	rda = 4 + ((gpy >> 3) & 1);
} else if (possee == 0 || p_vx == 0) {
	rda = 0;
} else {
	rda = (gpx >> 4) & 3;
} 

spr_sw [SP_PLAYER].sp0 = (int) (sm_sprptr [custom_animation [(p_facing ? 0 : 6) + rda]]);