// CHAC CHAC, engine for tile-based configurable, 3-tile tall crushers.

/*
	This MTE MK1v5 plugin works in ZX, Pestecera and Tostadera
	To use, do this:

	* Make a `plugins` folder in `dev` and copy this file.
	* Add this to `my/ci/extra_vars.h`:

	#include "plugins/plugin_chac_chacs.h"	

	Now configure your chac-chacs. These crushers are 3 tile tall and have
	`CHAC_CHAC_MAX_STATES` different states. On state 0, they wait for 
	`chac_chac_initial_times` (based on the type 0..N). On state S>0,
	they wait for `chac_chac_times [S]`.

	Crushers are painted when they change states using the tiles in 
	`chac_chac_t1`, `chac_chac_t2` and `chac_chac_t3`, vertically, from
	top to bottom.

	Then add the hooks.

	* In `my/ci/entering_screen.h`:

	you have to create the chac-chacs for the current screen. First of all,
	don't forget to do this:

	make chac_chac_idx = 0;

	Figure out a way to store your chac-chacs and then call this function
	to add each:

	_x = ...; _y = ...; _t = ...; chac_chacs_add ();

	* In `my/ci/extra_routines.h` call `chac_chacs_do ();`. 
*/

	#define CHAC_CHAC_MAX_STATES 6

	unsigned char chac_chac_initial_times [] = {
		20, 30, 55
	};

	unsigned char chac_chac_times [] = {
		0, 1, 1, 50, 9, 10
	};

	unsigned char chac_chac_t1 [] = {
		20, 21, 22, 22, 22, 21
	};

	unsigned char chac_chac_t2 [] = {
		23, 23, 21, 22, 21, 23
	};

	unsigned char chac_chac_t3 [] = {
		23, 23, 23, 21, 23, 23
	};

	#define CHAC_CHAC_MAX 4
	
	unsigned char chac_chac_idx;					// Index / # of chac chacs on screen
	unsigned char chac_chac_x [CHAC_CHAC_MAX]; 
	unsigned char chac_chac_y [CHAC_CHAC_MAX];  	// x, y coordinates
	unsigned char chac_chac_state [CHAC_CHAC_MAX]; 	// Current state (0..CHAC_CHAC_MAX_STATES-1)
	unsigned char chac_chac_idle [CHAC_CHAC_MAX]; 	// Time to wait in state 0
	unsigned char chac_chac_ct [CHAC_CHAC_MAX]; 	// Frame counter, wait N frames

	void chac_chacs_add (void) {
		chac_chac_x [chac_chac_idx] = _x;
		chac_chac_y [chac_chac_idx] = _y;
		chac_chac_state [chac_chac_idx] = CHAC_CHAC_MAX_STATES - 1;
		chac_chac_idle [chac_chac_idx] = chac_chac_initial_times [_t];
		chac_chac_ct [chac_chac_idx] = 0;

		chac_chac_idx ++;
	}

	void chac_chacs_do (void) {
		for (gpit = 0; gpit < chac_chac_idx; gpit ++) {
			if (chac_chac_ct [gpit]) {
				chac_chac_ct [gpit] --;
			} else {
				rda = ++ chac_chac_state [gpit];
				if (rda == CHAC_CHAC_MAX_STATES) {
					chac_chac_state [gpit] = 0;
					chac_chac_ct [gpit] = chac_chac_idle [gpit];
					rda = 0;
				} else {
					chac_chac_ct [gpit] = chac_chac_times [rda];
				}

				// Paint
				rdx = chac_chac_x [gpit]; rdy = chac_chac_y [gpit];
				_x = rdx; _y = rdy;     _t = chac_chac_t1 [rda]; _n = behs [_t]; update_tile ();
				_x = rdx; _y = rdy + 1; _t = chac_chac_t2 [rda]; _n = behs [_t]; update_tile ();
				_x = rdx; _y = rdy + 2; _t = chac_chac_t3 [rda]; _n = behs [_t]; update_tile ();
			}
		}		
	}
