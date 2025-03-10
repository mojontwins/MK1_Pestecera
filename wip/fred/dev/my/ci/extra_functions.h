// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

void shoot_create (void) {
	shoot_y = gpy + 4;
	shoot_x = p_facing ? gpx + 12 : gpx - 4;
	shoot_mx = p_facing ? 8 : -8;
}

void shoot_do (void) {
	
	if (shoot_y < 160) {
		shoot_x += shoot_mx;

		// Show sprite
		sp_sw [SP_EXTRA_BASE].cx = (shoot_x + VIEWPORT_X * 8) >> 2;
		sp_sw [SP_EXTRA_BASE].cy = (shoot_y + VIEWPORT_Y * 8);
		sp_sw [SP_EXTRA_BASE].sp0 = (int) (sprite_19_a);
		
		// BG collision / out of screen
		if (
			shoot_x < 8 || shoot_x > 240 || 
			attr ((shoot_x + 4) >> 4, (shoot_y + 4) >> 4) & 8
		) shoot_y = 160;
	} else {
		// Hide sprite
		sp_sw [SP_EXTRA_BASE].cx = (VIEWPORT_X * 8) >> 2;
		sp_sw [SP_EXTRA_BASE].cy = (VIEWPORT_Y * 8);
		sp_sw [SP_EXTRA_BASE].sp0 = (int) (SPRFR_EMPTY);
	}
	
}
