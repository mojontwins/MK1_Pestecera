// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// Printing functions

unsigned char attr (unsigned char x, unsigned char y) {
	// if (x >= 15 || y >= 10) return 0;
	// return map_attr [x + (y << 4) - y];
	
	#asm
			ld  hl, 4
			add hl, sp
			ld  c, (hl) 	// x

			dec hl
			dec hl
			ld  a, (hl) 	// y
			
			// If you put x in C and y in A you can call here
			
		._attr_2
			// A = y, C = x
			cp  10
			jr  c, _attr_1
			ld  hl, 0
			ret

		._attr_1
			ld  b, a 		// save y
			ld  a, c 		// x
			cp  15
			jr  c, _attr_1b
			ld  hl, 0
			ret

			// If you put x in C and y in B you can use this entry point for enemies

		._attr_1b
			ld  a, b 		// restore y
			sla a
			sla a
			sla a
			sla a
			sub b
			add c

			ld  d, 0
			ld  e, a
			ld  hl, _map_attr
			add hl, de
			ld  l, (hl)

		._attr_end
			ld  h, 0
	#endasm

}

unsigned char qtile (unsigned char x, unsigned char y) {
	// return map_buff [x + (y << 4) - y];
	
	#asm
			ld  hl, 4
			add hl, sp
			ld  c, (hl) 	// x
		
			dec hl
			dec hl
			ld  a, (hl) 	// y

			// If you put x in C and y in A you can call here
			
		.qtile_do	
			ld  b, a
			sla a
			sla a
			sla a
			sla a
			sub b
			add c

			ld  d, 0
			ld  e, a
			ld  hl, _map_buff
			add hl, de

			ld  l, (hl)
			ld  h, 0
	#endasm
}

#ifdef USE_AUTO_TILE_SHADOWS
	unsigned char attr_mk2 (void) {
		// x + 15 * y = x + (16 - 1) * y = x + 16 * y - y = x + (y << 4) - y.
		// if (cx1 < 0 || cy1 < 0 || cx1 > 14 || cy1 > 9) return 0;
		// return map_attr [cx1 + (cy1 << 4) - cy1];
		#asm
				ld  a, (_cx1)
				cp  15
				jr  nc, _attr_reset
	
				ld  a, (_cy1)
				cp  10
				jr  c, _attr_do
	
			._attr_reset
				ld  hl, 0
				ret
	
			._attr_do
				ld  a, (_cy1)
				ld  b, a
				sla a
				sla a
				sla a
				sla a
				sub b
				ld  b, a
				ld  a, (_cx1)
				add b
				ld  e, a
				ld  d, 0
				ld  hl, _map_attr
				add hl, de
				ld  a, (hl)
	
				ld  h, 0
				ld  l, a
				ret
		#endasm
	}
#endif

void _tile_address (void) {
	#asm
			ld  a, (__y)

			add a, a	; 2		4
			add a, a	; 4		4
			add a, a	; 8		4
			ld  h, 0	;		2
			ld  l, a 	;		4
			add hl, hl  ; 16	11
			add hl, hl  ; 32	11
			;					44 t-states

			; HL = _y * 32

			ld 	a, (__x)
			ld 	e, a 
			ld 	d, 0
			add hl, de

			; HL = _y * 32 + _x

			ld  de, _nametable
			add hl, de
			
			ex  de, hl

			; DE = buffer address
	#endasm
}

void draw_coloured_tile (void) {
	#ifdef USE_AUTO_TILE_SHADOWS		
		#asm
			// Undo screen coordinates -> buffer coordinates
				ld  a, (__x)
				sub VIEWPORT_X
				srl a
				ld  (_xx), a

				ld  a, (__y)
				sub VIEWPORT_Y
				srl a
				ld  (_yy), a
		#endasm

		// Nocast for tiles which never get shadowed
		nocast = !((attr (xx, yy) & 8) || (_t >= 16 && _t != 19));		

		// Precalc 
		#asm
				ld  a, (__t)
				sla a 
				sla a 
				add 64
				ld  (__ta), a
		#endasm

		// Precalc
		
		if (_t == 19) {
			t_alt = 192;
		} else {
			t_alt = 128 + _ta;
		}
		
		// cx1 = xx - 1; cy1 = yy ? yy - 1 : 0; a1 = (nocast && (attr_mk2 () & 8));
		#asm
			// cx1 = xx - 1; 
				ld  a, (_xx)
				dec a
				ld  (_cx1), a

			// cy1 = yy ? yy - 1 : 0;
				ld  a, (_yy)
				or  a
				jr  z, _dct_1_set_yy
				dec a
			._dct_1_set_yy
				ld  (_cy1), a

			// a1 = (nocast && (attr_mk2 () & 8));
				ld  a, (_nocast)
				or  a
				jr  z, _dct_a1_set

				call _attr_mk2
				ld  a, l
				and 8
				jr  z, _dct_a1_set

				ld  a, 1

			._dct_a1_set
				ld  (_a1), a
		#endasm			

		// cx1 = xx    ; cy1 = yy ? yy - 1 : 0; a2 = (nocast && (attr_mk2 () & 8));
		#asm
								// cx1 = xx; 
				ld  a, (_xx)					
				ld  (_cx1), a

			// cy1 = yy ? yy - 1 : 0;
				ld  a, (_yy)
				or  a
				jr  z, _dct_2_set_yy
				dec a
			._dct_2_set_yy
				ld  (_cy1), a

			// a2 = (nocast && (attr_mk2 () & 8))
				ld  a, (_nocast)
				or  a
				jr  z, _dct_a2_set

				call _attr_mk2
				ld  a, l
				and 8
				jr  z, _dct_a2_set

				ld  a, 1

			._dct_a2_set
				ld  (_a2), a
		#endasm

		// cx1 = xx - 1; cy1 = yy             ; a3 = (nocast && (attr_mk2 () & 8));
		#asm
				// cx1 = xx - 1; 
				ld  a, (_xx)
				dec a
				ld  (_cx1), a

			// cy1 = yy;
				ld  a, (_yy)					
				ld  (_cy1), a

			// a3 = (nocast && (attr_mk2 () & 8));
				ld  a, (_nocast)
				or  a
				jr  z, _dct_a3_set

				call _attr_mk2
				ld  a, l
				and 8
				jr  z, _dct_a3_set

				ld  a, 1

			._dct_a3_set
				ld  (_a3), a
		#endasm

		/*
		if (a1 || (a2 && a3)) { t1 = t_alt; }
			else { t1 = _ta; }
		++ _ta; ++ t_alt;
		*/
		#asm
				ld  a, (_a1)
				or  a
				jr  nz, _dct_1_shadow

				ld  a, (_a2)
				or  a
				jr  z, _dct_1_no_shadow

				ld  a, (_a3)
				or  a
				jr  z, _dct_1_no_shadow

			._dct_1_shadow
			// { t1 = t_alt; }
				ld  a, (_t_alt)
				ld  (_t1), a

				jr  _dct_1_increment
			
			._dct_1_no_shadow
			// else { t1 = _ta; }
				ld  a, (__ta)
				ld  (_t1), a

			._dct_1_increment
			// ++ _ta; ++ t_alt;
				ld  hl, __ta
				inc (hl)

				ld  hl, _t_alt
				inc (hl)
		#endasm 

		/*		
		if (a2) { t2 = t_alt; }
			else { t2 = _ta; }
		++ _ta; ++ t_alt;
		*/
		#asm
				ld  a, (_a2)
				or  a
				jr  z, _dct_2_no_shadow

			._dct_2_shadow
			// { t2 = t_alt; }
				ld  a, (_t_alt)
				ld  (_t2), a

				jr  _dct_2_increment
			
			._dct_2_no_shadow
			// else { t2 = _ta; }
				ld  a, (__ta)
				ld  (_t2), a

			._dct_2_increment
			// ++ _ta; ++ t_alt;
				ld  hl, __ta
				inc (hl)

				ld  hl, _t_alt
				inc (hl)
		#endasm 		

		/*
		if (a3) { t3 = t_alt; }
			else { t3 = _ta; }
		++ _ta; ++ t_alt;	
		*/

		#asm
				ld  a, (_a3)
				or  a
				jr  z, _dct_3_no_shadow

			._dct_3_shadow
			// { t3 = t_alt; }
				ld  a, (_t_alt)
				ld  (_t3), a

				jr  _dct_3_increment
			
			._dct_3_no_shadow
			// else { t3 = _ta; }
				ld  a, (__ta)
				ld  (_t3), a

			._dct_3_increment
			// ++ _ta; ++ t_alt;
				ld  hl, __ta
				inc (hl)

				ld  hl, _t_alt
				inc (hl)
		#endasm 

		// t4 = _ta;
		#asm
				ld  a, (__ta)
				ld  (_t4), a
		#endasm	

		// Paint tile
		// Paint t1, t2, t3, t4 @ (_x, _y) in tile buffer.
		#asm
			call __tile_address	; DE = buffer address
			ex  de, hl
			ld  a, (_t1)
			ld  (hl), a
			inc hl
			ld  a, (_t2)
			ld  (hl), a
			ld  bc, 31
			add hl, bc
			ld  a, (_t3)
			ld  (hl), a
			inc hl
			ld  a, (_t4)
			ld  (hl), a
		#endasm
	#else
		#asm
			/*
			_t = 64 + (_t << 2);
			gen_pt = tileset + ATTR_OFFSET + _t;
			sp_PrintAtInv (_y, _x, *gen_pt ++, _t ++);
			sp_PrintAtInv (_y, _x + 1, *gen_pt ++, _t ++);
			sp_PrintAtInv (_y + 1, _x, *gen_pt ++, _t ++);
			sp_PrintAtInv (_y + 1, _x + 1, *gen_pt, _t);
			*/
			// Calculate address in the display list

				call __tile_address	; DE = buffer address
				ex de, hl

				// Now write 4 chars.
				ld  a, (__t)
				sla a
				sla a 				// A = _t * 4
				add 64 				// A = _t * 4 + 64
				
				ld  (hl), a
				inc hl
				inc a
				ld  (hl), a
				ld  bc, 31
				add hl, bc
				inc a
				ld  (hl), a
				inc hl
				inc a
				ld  (hl), a
		#endasm
	#endif
}

void invalidate_tile (void) {
	// Add (_x, _y) -> (_x+1, _y+1) to the UpdTileTable
	#asm
			ld  a, (__x)
			ld  e, a
			ld  a, (__y)
			ld  d, a
			call cpc_UpdTileTable
			inc e
			call cpc_UpdTileTable
			dec e
			inc d
			call cpc_UpdTileTable
			inc e
			call cpc_UpdTileTable
	#endasm
}

void invalidate_viewport (void) {
	#asm
			ld  B, VIEWPORT_Y
			ld  C, VIEWPORT_X
			ld  D, VIEWPORT_Y+19
			ld  E, VIEWPORT_X+29
			call cpc_InvalidateRect
	#endasm
}

void draw_invalidate_coloured_tile_gamearea (void) {
	draw_coloured_tile_gamearea ();
	invalidate_tile ();
}

void draw_coloured_tile_gamearea (void) {
	_x = VIEWPORT_X + (_x << 1); _y = VIEWPORT_Y + (_y << 1); draw_coloured_tile ();
}

void draw_decorations (void) {
	// Point _gp_gen to where the decorations are and fire away!
	#asm
			ld  hl, (__gp_gen)

		._draw_decorations_loop
			ld  a, (hl)
			cp  0xff
			ret z

			ld  a, (hl)
			inc hl
			ld  c, a
			and 0x0f
			ld  (__y), a
			ld  a, c
			srl a
			srl a
			srl a
			srl a
			ld  (__x), a

			ld  a, (hl)
			inc hl
			ld  (__t), a

			push hl

			ld  b, 0
			ld  c, a
			ld  hl, _behs
			add hl, bc
			ld  a, (hl)
			ld  (__n), a

			call _update_tile

			pop hl
			jr  _draw_decorations_loop
	#endasm
}

unsigned char utaux = 0;
void update_tile (void) {

	/*
	utaux = (_y << 4) - _y + _x;
	map_attr [utaux] = _n;
	map_buff [utaux] = _t;
	draw_invalidate_coloured_tile_gamearea ();
	*/
	#asm
		ld  a, (__x)
		ld  c, a
		ld  a, (__y)
		ld  b, a
		sla a 
		sla a 
		sla a 
		sla a 
		sub b
		add c
		ld  b, 0
		ld  c, a
		ld  hl, _map_attr
		add hl, bc
		ld  a, (__n)
		ld  (hl), a
		ld  hl, _map_buff
		add hl, bc
		ld  a, (__t)
		ld  (hl), a

		call _draw_coloured_tile_gamearea

		ld  a, (_is_rendering)
		or  a
		ret nz

		call _invalidate_tile
	#endasm
	
	#ifdef ENABLE_TILANIMS
		// Detect tilanims
		if (_t >= ENABLE_TILANIMS) {
			_n = (_x << 4) | _y;
			tilanims_add ();	
		}
	#endif
}

void print_number2 (void) {
	rda = 16 + (_t / 10); rdb = 16 + (_t % 10);
	#asm
			call __tile_address	; DE = buffer address
			ld  a, (_rda)
			ld  (de), a
			inc de
			ld  a, (_rdb)
			ld  (de), a

			ld  a, (__x)
			ld  e, a
			ld  a, (__y)
			ld  d, a
			call cpc_UpdTileTable
			inc e
			call cpc_UpdTileTable
	#endasm
}

#ifndef DEACTIVATE_OBJECTS
	void draw_objs () {
		#if defined (ONLY_ONE_OBJECT) && defined (ACTIVATE_SCRIPTING)
			#if OBJECTS_ICON_X != 99
				if (p_objs) {
					// Make tile 17 flash
					/*
					sp_PrintAtInv (OBJECTS_ICON_Y, OBJECTS_ICON_X, 135, 132);
					sp_PrintAtInv (OBJECTS_ICON_Y, OBJECTS_ICON_X + 1, 135, 133);
					sp_PrintAtInv (OBJECTS_ICON_Y + 1, OBJECTS_ICON_X, 135, 134);
					sp_PrintAtInv (OBJECTS_ICON_Y + 1, OBJECTS_ICON_X + 1, 135, 135);
					*/
					#asm
							// Calculate address in the display list

							ld  a, OBJECTS_ICON_X
							ld  (__x), a
							ld  c, a
							ld  a, OBJECTS_ICON_Y
							ld  (__y), a
							
							call __tile_address	; DE = buffer address
							ex de, hl

							// Now write 4 chars.
							ld  a, 132
							
							ld  (hl), a
							inc hl
							inc a
							ld  (hl), a
							ld  bc, 31
							add hl, bc
							inc a
							ld  (hl), a
							inc hl
							inc a
							ld  (hl), a							

							call _invalidate_tile
					#endasm						
				} else {
					_x = OBJECTS_ICON_X; _y = OBJECTS_ICON_Y; _t = 17; 
					draw_coloured_tile ();
					invalidate_tile ();
				}
			#endif
				
			#if OBJECTS_X != 99
				_x = OBJECTS_X; _y = OBJECTS_Y; _t = flags [OBJECT_COUNT]; print_number2 ();
			#endif
		#else
			#if OBJECTS_X != 99
				_x = OBJECTS_X; _y = OBJECTS_Y; 
				#if defined REVERSE_OBJECTS_COUNT && defined PLAYER_NUM_OBJETOS
					_t = PLAYER_NUM_OBJETOS - p_objs;
				#else
					_t = p_objs; 
				#endif
				print_number2 ();
			#endif
		#endif
	}
#endif

void print_str (void) {
	#asm
			xor a 
			ld  (_rdn), a 		; Strlen

			call __tile_address	; DE = buffer address
			ld  hl, (__gp_gen)

		.print_str_loop
			ld  a, (hl)
			or  a
			jr  z, print_str_inv 
			
			sub 32
			ld  (de), a
			
			inc hl
			inc de 

			ld  a, (_rdn)
			inc a
			ld  (_rdn), a

			jr  print_str_loop

		.print_str_inv

			; Invalidate cells based upon strlen.
			ld  a, (__y)
			ld  b, a
			ld  d, a
			ld  a, (__x)
			ld  c, a
			ld  a, (_rdn)
			add c
			dec a
			ld  e, a
			call cpc_InvalidateRect
	#endasm
}

#if defined (COMPRESSED_LEVELS) || defined (SHOW_LEVEL_ON_SCREEN)
	void blackout_area (void) {
		#asm
			xor a 
			ld  hl, _nametable
			ld  (hl), a
			ld  de, _nametable+1
			ld  bc, 767
			ldir
		#endasm
	}
#endif

void clear_sprites (void) {
	#asm
	#endasm
	for (gpit = 0; gpit < SW_SPRITES_ALL; gpit ++) {
		sp_sw [gpit].sp0 = (int) (SPRFR_EMPTY);
	}
}

void pal_set (unsigned char *pal) {
	#if CPC_GFX_MODE == 0
		gpit = 16;
	#else
		gpit = 4;
	#endif
	while (gpit --) cpc_SetColour (gpit, pal[gpit]);
}
