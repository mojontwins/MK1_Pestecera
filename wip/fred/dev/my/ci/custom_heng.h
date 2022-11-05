// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// Modify p_vx

rda = cpc_TestKey (KEY_LEFT);
rdb = cpc_TestKey (KEY_RIGHT);

if ( !(rda || rdb) ) {
	if (possee) p_vx = 0;
	wall_h = 0;
	p_left_right = 0;
} else {
	if (p_on_rope) {
		if (p_left_right == 0) {
			if (p_facing) {
				// Facing right (left of rope)
				if (rda) {
					gpx -= 2; p_x -= 128;
					p_vx = -PLAYER_CONSTANT_VX;
					p_facing = 0;
					p_on_rope = 0;
				} else if (rdb) p_facing = 0;
			} else {
				// Facing left (right of rope)
				if (rdb) {
					gpx += 2; p_x += 128;
					p_vx = PLAYER_CONSTANT_VX;
					p_facing = 1;
					p_on_rope = 0;
				} else if (rda) p_facing = 1;
			}
		}
	} else if (possee) {
		if (rda) {
			p_vx = -PLAYER_CONSTANT_VX;
			p_facing = 0;
			p_left_right = DIRECTION_LEFT;
		}

		if (rdb) {
			p_vx = PLAYER_CONSTANT_VX;
			p_facing = 1;
			p_left_right = DIRECTION_RIGHT;
		}
	}
}
