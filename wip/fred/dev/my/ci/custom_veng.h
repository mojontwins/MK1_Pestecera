// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// Modify p_vy
// Don't forget to use the veng_selector if VENG_SELECTOR is defined.

// Tile rope detection

p_tile_rope = attr ((gpx + 8) >> 4, (gpy + 8) >> 4) & 32;

if (p_on_rope == 0)  {
	if (possee || (p_tile_rope == 0)) p_rope_ready = 1;

	// Enter rope logic
	if (p_rope_ready && p_tile_rope && possee == 0) {
		rdx = gpx & 0x0f; rdy = gpx & 0xf0;

		// Enter from the left
		if (rdx > 11) {
			gpx = rdy + 16; p_x = gpx << FIXBITS;
			p_vx = p_vy = 0;
			p_facing = 1; 
			p_on_rope = 1;
			goto gravity_done;
		}

		// Enter from the right
		if (rdx < 4) {
			gpx = rdy; p_x = gpx << FIXBITS;
			p_facing = 0;
			p_vx = p_vy = 0;
			p_on_rope = 1;
			goto gravity_done;
		}
	}

	// Do gravity

	#asm
			; Signed comparisons are hard
			; p_vy <= PLAYER_MAX_VY_CAYENDO - PLAYER_G

			; We are going to take a shortcut.
			; If p_vy < 0, just add PLAYER_G.
			; If p_vy > 0, we can use unsigned comparition anyway.

			ld  hl, (_p_vy)
			bit 7, h
			jr  nz, _player_gravity_add 	; < 0

			ld  de, PLAYER_MAX_VY_CAYENDO - PLAYER_G
			or  a
			push hl
			sbc hl, de
			pop hl
			jr  nc, _player_gravity_maximum

		._player_gravity_add
			ld  de, PLAYER_G
			add hl, de
			jr  _player_gravity_vy_set

		._player_gravity_maximum
			ld  hl, PLAYER_MAX_VY_CAYENDO

		._player_gravity_vy_set
			ld  (_p_vy), hl

		._player_gravity_done
			ld  a, (_p_gotten)
			or  a
			jr  z, _player_gravity_p_gotten_done

			xor a
			ld  (_p_vy), a

		._player_gravity_p_gotten_done
	#endasm

	gravity_done:

	if (cpc_TestKey (KEY_UP)) {
		if (possee & p_jump_pressed == 0) p_vy = -PLAYER_CONSTANT_JUMP_VY;
		p_jump_pressed = 1;
	} else p_jump_pressed = 0;

} else {
	p_vy = 0;
	p_rope_ready = 0;
	if (cpc_TestKey (KEY_UP)) p_vy = -PLAYER_CONSTANT_VY;
	if (cpc_TestKey (KEY_DOWN)) p_vy = PLAYER_CONSTANT_VY;
}

