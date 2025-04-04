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

if (!possee && !p_gotten) {			
	gpit = p_facing ? 3 : 7;
} else {
	gpit = p_facing ? 0 : 4;
	if (p_vx == 0) {
		++ gpit;
	} else {
		rda = ((gpx + 4) >> 3) & 3;
		if (rda == 3) rda = 1;
		gpit += rda;
	}
	
}

gpit += player_sprite_offset; // 0 for paco, 16 for puri

sp_sw [SP_PLAYER].sp0 = (int) (sm_sprptr [gpit]);