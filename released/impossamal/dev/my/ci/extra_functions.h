// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

void break_horizontal (void) {		
	if (at1 & 16) {
		_x = cx1; _y = cy1; break_wall ();
	} 
	if (cy1 != cy2 && (at2 & 16)) {
		_x = cx1; _y = cy2; break_wall ();
	}
}

void break_vertical (void) {			
	if (at1 & 16) {
		_y = cy1; _x = cx1; break_wall ();
	} 
	if (cx1 != cx2 && (at2 & 16)) {
		_y = cy1; _x = cx2; break_wall ();
	}	
}

#define BLACK_CHAR 28
void recuadrius_param (void) {  
	for (gpit = 0; gpit < 10; gpit ++) {
		for (rdx = gpit; rdx < 30 - gpit; rdx ++) {
			#asm
					// sp_PrintAtInv (VIEWPORT_Y + gpit, VIEWPORT_X + rdx, 71, 0);
					ld  a, (_gpit)
					add VIEWPORT_Y
					ld  (__y), a
					ld  a, (_rdx)
					add VIEWPORT_X
					ld  (__x), a
					call __tile_address	; DE = buffer address

					ld  a, (_gpit)
					and 1
					ld  a, BLACK_CHAR 
					jr  z, rpskip1
					ld  a, (_rda)
				.rpskip1
					
					ld  (de), a
					ld  a, (__x)
					ld  e, a
					ld  a, (__y)
					ld  d, a
					call cpc_UpdTileTable
				

				// sp_PrintAtInv (VIEWPORT_Y + 19 - gpit, VIEWPORT_X + rdx, 71, 0);
					ld  a, (_gpit)
					ld  c, a
					ld  a, VIEWPORT_Y+19
					sub c
					ld  (__y), a
					ld  a, (_rdx)
					add VIEWPORT_X
					ld  (__x), a
					call __tile_address	; DE = buffer address

					ld  a, (_gpit)
					and 1 
					ld  a, BLACK_CHAR 
					jr  z, rpskip2
					ld  a, (_rda)
				.rpskip2

					ld  (de), a
					ld  a, (__x)
					ld  e, a
					ld  a, (__y)
					ld  d, a
					call cpc_UpdTileTable
			#endasm

			if (rdx < 19 - gpit) {
				#asm
						// sp_PrintAtInv (VIEWPORT_Y + rdx, VIEWPORT_X + gpit, 71, 0);
						ld  a, (_rdx)
						add VIEWPORT_Y
						ld  (__y), a
						ld  a, (_gpit)
						add VIEWPORT_X
						ld  (__x), a
						call __tile_address	; DE = buffer address

						ld  a, (_gpit)
						and 1 
						ld  a, BLACK_CHAR 
						jr  z, rpskip3
						ld  a, (_rda)
					.rpskip3
						ld  (de), a
						ld  a, (__x)
						ld  e, a
						ld  a, (__y)
						ld  d, a
						call cpc_UpdTileTable

						// sp_PrintAtInv (VIEWPORT_Y + rdx, VIEWPORT_X + 29 - gpit, 71, 0);
						ld  a, (_rdx)
						add VIEWPORT_Y
						ld  (__y), a
						ld  a, (_gpit)
						ld  c, a
						ld  a, VIEWPORT_X+29
						sub c						
						ld  (__x), a
						call __tile_address	; DE = buffer address

						ld  a, (_gpit)
						and 1 
						ld  a, BLACK_CHAR 
						jr  z, rpskip4
						ld  a, (_rda)
					.rpskip4
						ld  (de), a
						ld  a, (__x)
						ld  e, a
						ld  a, (__y)
						ld  d, a
						call cpc_UpdTileTable
				#endasm		
			}			
		}

		cpc_UpdateNow (0);
	}
}

void recuadrius_plus (void) {
	// Recuadrius ping
	rda = 0;
	recuadrius_param ();

	// Recuadrius pong
	rda = BLACK_CHAR;
	recuadrius_param ();
}

void blackout_area_inv (void) {
	#asm
			ld  a, BLACK_CHAR
			ld  hl, _nametable
			ld  (hl), a
			ld  de, _nametable+1
			ld  bc, 767
			ldir
	#endasm
	invalidate_viewport ();
	cpc_UpdateNow (0);
}
