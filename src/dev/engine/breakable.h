// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// breakable.h

void break_wall (void) {
	gpaux = COORDS (_x, _y);
	if (brk_buff [gpaux] < BREAKABLE_WALLS_LIFE) {
		#ifdef BREAKABLE_WALLS_BREAKING
			_t = BREAKABLE_WALLS_BREAKING;
			_n = behs [_t]; 
			update_tile ();
		#endif
		gpit = SFX_BREAKABLE_HIT;			
		#include "my/ci/on_wall_hit.h"
	} else {
		_n = 0;
		#ifdef BREAKABLE_WALLS_BROKEN
			_t = BREAKABLE_WALLS_BROKEN;
		#else
			_t = 0; 
		#endif
		update_tile ();
		gpit = SFX_BREAKABLE_BREAK;
		#include "my/ci/on_wall_broken.h"
	}

	++ brk_buff [gpaux];
	AY_PLAY_SOUND (gpit);
}
