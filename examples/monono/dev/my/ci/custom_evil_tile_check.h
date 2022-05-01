// custom_evil_tile_check.h
// Detect collision, modify velocities and set hit.

if (p_vy > 0) {
	#asm
		// Detect attr 1 in 
		// (gpx + 4, gpy + 15) (gpx + 11, gpy + 15)

			ld  a, (_gpx)
			ld  b, a
			add 4
			srl a
			srl a
			srl a
			srl a
			ld  (_cx1), a
			
			ld  a, b
			add 11
			srl a
			srl a
			srl a
			srl a
			ld  (_cx2), a

			ld  a, (_gpy)
			ld  b, a
			add 15
			srl a
			srl a
			srl a
			srl a
			ld  (_cy1), a
			ld  (_cy2), a

			call _cm_two_points

			ld  a, (_at1)
			and 1
			jr  nz, custom_hit_do

			ld  a, (_at2)
			and 1
			jr  z, custom_hit_done

		.custom_hit_do
			ld  a, 1
			ld  (_hit), a

		.custom_hit_done

	#endasm
}