// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// Tile was pushed from (x0, y0) -> (x1, y1).

// First detect if the tile overlaps an enemy (simple)
for (enit = 0; enit < 3; ++ enit) {
	enoffsmasi = enoffs + enit;
	
	#asm
			ld 	hl, (_enoffsmasi)
			ld  h, 0

		#ifdef PLAYER_CAN_FIRE
			add hl, hl 				// x2
			ld  d, h
			ld  e, l 				// DE = x2
			add hl, hl 				// x4
			add hl, hl 				// x8

			add hl, de 				// HL = x8 + x2 = x10
		#else
			ld  d, h
			ld  e, l 				// DE = x1
			add hl, hl 				// x2
			add hl, hl 				// x4
			add hl, hl 				// x8

			add hl, de 				// HL = x8 + x1 = x9
		#endif

			ld  de, _malotes
			add hl, de

			ld  (__baddies_pointer), hl 		// Save address for later

			ld  a, (hl)
			ld  (__en_x), a
			inc hl 

			ld  a, (hl)
			ld  (__en_y), a

			ld  bc, 6
			add hl, bc
			ld  a, (hl)
			ld  (__en_t), a

		// Skip for rays
			cp  3
			jp  c, _on_tile_pushed_continue

		// Overlaps?
		// if (((_en_x + 8) >> 4) == x0 && 
		//     ((_en_y + 8) >> 4) == y0
		// )

			ld  a, (__en_x)
			add 8
			srl a 
			srl a
			srl a
			srl a
			ld  c, a
			ld  a, (_x1)
			cp  c
			jp  nz, _on_tile_pushed_continue

			ld  a, (__en_y)
			add 8
			srl a 
			srl a
			srl a
			srl a
			ld  c, a
			ld  a, (_y1)
			cp  c
			jp  nz, _on_tile_pushed_continue

		// If we got here, pushed tile overlaps the enemy.
		// We have to push the enemy 16 pixels in the right direction.

			ld  a, (_x0)
			ld  c, a
			ld  a, (_x1)
			cp  c
			jr  z, _on_tile_pushed_vertically

		._on_tile_pushed_horizontally
			// Moved horizontally. Left or right?
			jr  nc, _on_tile_pushed_right 	// C set   if A (_x1) <  C (_x0)
											// C reset if A (_x1) >= C (_x0)
		
		._on_tile_pushed_left
			ld  a, (__en_x)
			sub 16
			ld  (__en_x), a
			jr  _on_tile_pushed_done

		._on_tile_pushed_right
			ld  a, (__en_x)
			add 16
			ld  (__en_x), a
			jr  _on_tile_pushed_done

		._on_tile_pushed_vertically
			// Mover vertically. Up or down?
			ld  a, (_y0)
			ld  c, a
			ld  a, (_y1)
			cp  c

			jr  nc, _on_tile_pushed_down 	// C set   if A (_y1) <  C (_y0)
											// C reset if A (_y1) >= C (_y0)

		._on_tile_pushed_up
			ld  a, (__en_y)
			sub 16
			ld  (__en_y), a
			jr  _on_tile_pushed_done

		._on_tile_pushed_down
			ld  a, (__en_y)
			add 16
			ld  (__en_y), a
			
		._on_tile_pushed_done

		// At this point, enemy has been pushed. If it's been pushed out
		// of screen or to a solid tile, kill the enemy.

		// Out of screen simple test
			ld  a, (__en_x)
			cp  240
			jr  nc, _on_tile_pushed_kill_enemy 	// C reset if A (__en_x) >= 240

			ld  a, (__en_y)
			cp  160
			jr  nc, _on_tile_pushed_kill_enemy 	// C reset if A (__en_y) >= 160
			
		// Check tile. Beh != 0 -> kill
		// COORD -> (rdy << 4) + rdx - rdy;
			and 0xf0		
			ld  c, a 		// C -> (rdy << 4)

			srl a
			srl a
			srl a
			srl a
			ld  b, a

			ld  a, (__en_x)
			srl a
			srl a
			srl a
			srl a
			add c 
			sub b

			ld  d, 0
			ld  e, a
			ld  hl, _map_attr
			add hl, de
			ld  a, (hl)
			or  a

			jr  nz, _on_tile_pushed_kill_enemy

		// Don't kill. Update arrays
			ld  hl, (__baddies_pointer) 		// Restore pointer

			ld  a, (__en_x)
			ld  (hl), a
			inc hl

			ld  a, (__en_y)
			ld  (hl), a
			inc hl

			jr  _on_tile_pushed_continue

		._on_tile_pushed_kill_enemy

	#endasm

	en_an_state [enit] = GENERAL_DYING;
	en_an_count [enit] = 12;
	en_an_next_frame [enit] = sprite_17_a;

	AY_PLAY_SOUND (SFX_KILL_ENEMY_SHOOT);
								
	#ifdef ENABLE_PURSUERS
		enems_pursuers_init ();
	#endif

	enems_kill ();

	#asm
		._on_tile_pushed_continue
	#endasm
}