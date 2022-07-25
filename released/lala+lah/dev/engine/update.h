// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// cpc_UpdateNow () - Updates the screen.

// SPR struct is 16 bytes wide. So iteration is simple
// if you write your code by hand ... 

void cpc_UpdateNow (unsigned char sprites) {
	if (sprites) {
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
		#endasm
	}

	#asm
		._cpc_screen_update_upd_buffer
			call cpc_UpdScr 
	#endasm

	if (sprites) {
		// Call the drawing function for all sprites

		#asm
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

			._cpc_screen_update_done
		#endasm
	}

	#ifdef MIN_FAPS_PER_FRAME
			#asm
			.ml_min_faps_loop
				ld  a, (isr_c2)
				cp  MIN_FAPS_PER_FRAME
				jr  c, ml_min_faps_loop

			.ml_min_faps_loop_end
				xor a
				ld  (isr_c2), a
			#endasm
	#endif

	#asm
			call cpc_ShowTouchedTiles
			call cpc_ResetTouchedTiles
	#endasm
}
