// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// Modify A before it is written to map_buff & map_attr & painted

	#asm
			ld  c, a
			ld  a, (_tile_offset)
			add c
	#endasm
