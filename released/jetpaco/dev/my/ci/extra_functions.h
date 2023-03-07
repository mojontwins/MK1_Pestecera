// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

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

void spawn_jumo (void) {
	if (jumo_y >= 160) {
		jumo_x = (gpx + VIEWPORT_X * 8 + 4) >> 2;
		jumo_y = gpy + VIEWPORT_Y * 8 + 8;
		jumo_fr = jumo_ct = 0;
		sp_sw [SP_EXTRA_BASE].cx = jumo_x;
		sp_sw [SP_EXTRA_BASE].cy = jumo_y;
	}
}