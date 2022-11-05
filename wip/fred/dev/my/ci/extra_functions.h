// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

void shoot_create (void) {
	shoot_y = gpy + 4;
	shoot_x = p_facing ? gpx + 12 : gpx - 4;
	shoot_mx = p_facing ? 8 : -8;
}

void shoot_do (void) {
	/*
	if (shoot_y < 160) {
		shoot_x += shoot_mx;

		// Show sprite
		#asm
				ld  ix, (_sp_shoot)
				ld  iy, vpClipStruct

				ld  bc, 0

				ld  a, (_shoot_y)
				srl a
				srl a
				srl a
				add VIEWPORT_Y
				ld  h, a 

				ld  a, (_shoot_x)
				srl a
				srl a
				srl a
				add VIEWPORT_X
				ld  l, a 
				
				ld  a, (_shoot_x)
				and 7
				ld  d, a

				ld  a, (_shoot_y)
				and 7
				ld  e, a

				call SPMoveSprAbs
		#endasm

		// BG collision / out of screen
		if (
			shoot_x < 8 || shoot_x > 240 || 
			attr ((shoot_x + 4) >> 4, (shoot_y + 4) >> 4) & 8
		) shoot_y = 160;
	} else {
				// Show sprite
		#asm
				ld  ix, (_sp_shoot)
				ld  iy, vpClipStruct

				ld  bc, 0
				ld  hl, 0xDEDE
				ld  de, 0

				call SPMoveSprAbs
		#endasm
	}
	*/
}
