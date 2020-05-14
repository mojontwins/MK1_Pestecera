// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// update_sprites.h - Updates sprites

/*
	for (enit = 0; enit < MAX_ENEMS; enit ++) {
		enoffsmasi = enoffs + enit;
		//enems_draw_current ();
	}

	if ( (p_estado & EST_PARP) == 0 || half_life == 0 ) {
		//sp_MoveSprAbs (sp_player, spritesClip, p_next_frame - p_current_frame, VIEWPORT_Y + (gpy >> 3), VIEWPORT_X + (gpx >> 3), gpx & 7, gpy & 7);
		
	} else {
		//sp_MoveSprAbs (sp_player, spritesClip, p_next_frame - p_current_frame, -2, -2, 0, 0);
		
	}

	#ifdef PLAYER_CAN_FIRE
		for (gpit = 0; gpit < MAX_BULLETS; gpit ++) {
			if (bullets_estado [gpit] == 1) {
				rdx = bullets_x [gpit]; rdy = bullets_y [gpit];
				//sp_MoveSprAbs (sp_bullets [gpit], spritesClip, 0, VIEWPORT_Y + (bullets_y [gpit] >> 3), VIEWPORT_X + (bullets_x [gpit] >> 3), bullets_x [gpit] & 7, bullets_y [gpit] & 7);
			} else {
				//sp_MoveSprAbs (sp_bullets [gpit], spritesClip, 0, -2, -2, 0, 0);
			}
		}
	#endif
		
	#ifdef ENABLE_SIMPLE_COCOS
		for (gpit = 0; gpit < MAX_ENEMS; gpit ++) {
			if (cocos_y [gpit] < 160) { 
				rdx = cocos_x [gpit]; rdy = cocos_y [gpit];
				//sp_MoveSprAbs (sp_cocos [gpit], spritesClip, 0, VIEWPORT_Y + (bullets_y [gpit] >> 3), VIEWPORT_X + (bullets_x [gpit] >> 3), bullets_x [gpit] & 7, bullets_y [gpit] & 7);
			} else {
				//sp_MoveSprAbs (sp_cocos [gpit], spritesClip, 0, -2, -2, 0, 0);
			}
		}
	#endif
*/

// SPR struct is 16 bytes wide. So iteration is simple
// if you write your code by hand ... 

#asm
	// Call the invalidate function for all sprites 

	/*
	for (gpit = 0; gpit < SW_SPRITES_ALL; gpit ++) {
		(sp_sw [gpit].invfunc) ((int) (&sp_sw [gpit]));
	}
	*/

		ld  b, 0
	._cpc_screen_update_inv_loop
		push bc
		// SW_SPRITES_ALL will be at very most = 16,
		// so we can multiply by 16 safely in 8 bits.
		ld  a, b
		sla a
		sla a
		sla a 
		sla a
		ld d, 0
		ld e, a
		ld  hl, _sp_sw
		add hl, de

		// Save paremeter
		ld  b, h
		ld  c, l

		// Push return address into stack
		ld  de, _cpc_screen_update_inv_ret
		push de

		// Push function pointer into stack
		// Offset 12 into the structure: invfunc
		ld  de, 12
		add hl, de
		ld  e, (hl)
		inc hl
		ld  d, (hl)
		push de

		// __fastcall__ expects parameter in HL
		ld  h, b
		ld  l, c

		// ret will pop the function pointer from the
		// stack and jp to it. Next ret will get to 
		// _cpc_screen_update_inv_ret
		ret

	._cpc_screen_update_inv_ret
		pop bc
		inc b
		ld  a, b
		cp  SW_SPRITES_ALL
		jr  nz, _cpc_screen_update_inv_loop

	._cpc_screen_update_upd_buffer
		call cpc_UpdScr 

	// Call the drawing function for all sprites

	/*
		for (gpjt = 0; gpjt < SW_SPRITES_ALL; gpjt ++) {
			gpit = spr_order [gpjt];
			(sp_sw [gpit].updfunc) ((int) (&sp_sw [gpit]));
		}
	*/	
		ld  b, SW_SPRITES_ALL
	._cpc_screen_update_upd_loop
		dec b
		push bc
		ld  a, b

		// SW_SPRITES_ALL will be at very most = 16,
		// so we can multiply by 16 safely in 8 bits.
		sla a
		sla a
		sla a 
		sla a
		ld d, 0
		ld e, a
		ld  hl, _sp_sw
		add hl, de

		// Save paremeter
		ld  b, h
		ld  c, l

		// Push return address into stack
		ld  de, _cpc_screen_update_upd_ret
		push de

		// Push function pointer into stack
		// Offset 12 into the structure: updfunc
		ld  de, 14
		add hl, de
		ld  e, (hl)
		inc hl
		ld  d, (hl)
		push de

		// __fastcall__ expects parameter in HL
		ld  h, b
		ld  l, c

		// ret will pop the function pointer from the
		// stack and jp to it. Next ret will get to 
		// _cpc_screen_update_inv_ret
		ret

	._cpc_screen_update_upd_ret
		pop bc
		xor a
		or  b
		jr  nz, _cpc_screen_update_upd_loop

	._cpc_screen_update_show
		call cpc_ShowTouchedTiles
		call cpc_ResetTouchedTiles

#endasm
