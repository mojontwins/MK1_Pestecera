// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// Hostage!

/*
// Clear tile from screen 
_x = cx1; _y = cy1; _t = 0; _n = 0; update_tile ();

// Clear tile from map
gpaux = COORDS (cx1, cy1); persist_tile ();

++ p_objs;
*/

#asm
	// Clear tile from screen 

		ld  a, (_cy1)
		ld  c, a 			// for gpaux calc.
		ld  (__y), a
		xor a
		ld  (__t), a
		ld  (__n), a

		// Calc gpaux

		ld  a, c
		sla a
		sla a
		sla a
		sla a
		sub c 				// A = (cy1 << 4) - cy1
		ld  c, a

		ld  a, (_cx1)
		ld  (__x), a

		add c 				// A = cx1 + (cy1 << 4) - cy1
		ld  (_gpaux), a

		call _update_tile

	// Clear tile from map
		call _persist_tile

		ld  hl, _f_2
		dec (hl)

	// Update screen

		#ifdef LANG_ES
			ld  hl, _nametable + 15
			ld  de, 0x000F
		#else
			ld  hl, _nametable + 14
			ld  de, 0x000E
		#endif
		ld  a, (_f_2)
		add 16
		ld  (hl), a 		// Draw tile

		// Ivalidate DE = YX
		call cpc_UpdTileTable 
#endasm

AY_PLAY_SOUND (SFX_ONE_OBJECT_GET);

