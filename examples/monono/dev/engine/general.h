// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// enengine.h

#ifndef BB_SIZE
	#ifdef SMALL_COLLISION
		#define BB_SIZE 8
	#else
		#define BB_SIZE 12
	#endif
#endif

unsigned char collide (void) {
	/*
	#ifdef SMALL_COLLISION
		return (gpx + 8 >= cx2 && gpx <= cx2 + 8 && gpy + 8 >= cy2 && gpy <= cy2 + 8);
	#else
		return (gpx + 12 >= cx2 && gpx <= cx2 + 12 && gpy + 12 >= cy2 && gpy <= cy2 + 12);
	#endif
	*/
	#asm
			ld  hl, 0

		// gpx + 8 >= cx2
			ld  a, (_cx2)
			ld  c, a 
			ld  a, (_gpx)
			add BB_SIZE
			cp  c
			ret c 

		// gpx <= cx2 + 8 -> cx + 8 >= gpx
			ld  a, (_gpx)
			ld  c, a 
			ld  a, (_cx2)
			add BB_SIZE
			cp  c 
			ret c

		// gpy + 8 >= cy2
			ld  a, (_cy2)
			ld  c, a 
			ld  a, (_gpy)
			add BB_SIZE
			cp  c
			ret c 

		// gpy <= cy2 + 8 -> cy + 8 >= gpy
			ld  a, (_gpy)
			ld  c, a 
			ld  a, (_cy2)
			add BB_SIZE
			cp  c 
			ret c

			ld  l, 1
	#endasm
}

unsigned char cm_two_points (void) {
	/*
	if (cx1 > 14 || cy1 > 9) at1 = 0; 
	else at1 = map_attr [cx1 + (cy1 << 4) - cy1];

	if (cx2 > 14 || cy2 > 9) at2 = 0; 
	else at2 = map_attr [cx2 + (cy2 << 4) - cy2];
	*/
	#asm
			ld  a, (_cx1)
			cp  15
			jr  nc, _cm_two_points_at1_reset

			ld  a, (_cy1)
			cp  10
			jr  c, _cm_two_points_at1_do

		._cm_two_points_at1_reset
			xor a
			jr  _cm_two_points_at1_done

		._cm_two_points_at1_do
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

		._cm_two_points_at1_done
			ld (_at1), a

			ld  a, (_cx2)
			cp  15
			jr  nc, _cm_two_points_at2_reset

			ld  a, (_cy2)
			cp  10
			jr  c, _cm_two_points_at2_do

		._cm_two_points_at2_reset
			xor a
			jr  _cm_two_points_at2_done

		._cm_two_points_at2_do
			ld  a, (_cy2)
			ld  b, a
			sla a
			sla a
			sla a
			sla a
			sub b
			ld  b, a
			ld  a, (_cx2)
			add b
			ld  e, a
			ld  d, 0
			ld  hl, _map_attr
			add hl, de
			ld  a, (hl)

		._cm_two_points_at2_done
			ld (_at2), a
	#endasm
}

unsigned char rand (void) {
	#asm
		.rand16
			ld	hl, _seed
			ld	a, (hl)
			ld	e, a
			inc	hl
			ld	a, (hl)
			ld	d, a
			
			;; Ahora DE = [SEED]
						
			ld	a,	d
			ld	h,	e
			ld	l,	253
			or	a
			sbc	hl,	de
			sbc	a, 	0
			sbc	hl,	de
			ld	d, 	0
			sbc	a, 	d
			ld	e,	a
			sbc	hl,	de
			jr	nc,	nextrand
			inc	hl
		.nextrand
			ld	d,	h
			ld	e,	l
			ld	hl, _seed
			ld	a,	e
			ld	(hl), a
			inc	hl
			ld	a,	d
			ld	(hl), a
			
			;; Ahora [SEED] = HL
		
			ld  l, e
			ret
	#endasm
}

unsigned int abs (signed int n) {
	if (n < 0)
		return (unsigned int) (-n);
	else 
		return (unsigned int) n;
}
