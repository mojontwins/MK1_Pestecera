// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// Modify A before it is written to map_buff & map_attr & painted

	#asm
		// Mapped tilesets. Curren tile would be gm_ts [A]

			ld  hl, _gm_ts
			ld  e, (hl)
			inc hl
			ld  d, (hl) 			// DE -> *gm_ts

			ld  l, a 
			ld  h, 0
			add hl, de 
			ld  a, (hl)
	#endasm
