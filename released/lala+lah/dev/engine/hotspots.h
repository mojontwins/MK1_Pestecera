// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// hotspots.h

#ifndef COMPRESSED_LEVELS
	void hotspots_init (void) {
		/*
		gpit = 0; while (gpit < MAP_W * MAP_H) {
			hotspots [gpit].act = 1; ++ gpit;
		}
		*/
		#asm
				// iterate MAP_W*MAP_H times
				// start with _hotspots + 2
				// set to 1, increment pointer by 3
				ld  b, MAP_W * MAP_H
				ld  hl, _hotspots + 2
				ld  de, 3
				ld  a, 1
			.init_hotspots_loop
				ld  (hl), a
				add hl, de
				djnz init_hotspots_loop
		#endasm		
	}
#endif

void hotspots_do (void) {
	if (hotspots [n_pant].act == 0) return;

	cx2 = hotspot_x; cy2 = hotspot_y; if (collide ()) {
		// Deactivate hotspot
		hotspot_destroy = 1;
			
		switch (hotspots [n_pant].tipo) {
			#ifndef DEACTIVATE_OBJECTS					   
				case 1:
					#ifdef ONLY_ONE_OBJECT
						if (p_objs == 0) {
							p_objs ++;
							AY_PLAY_SOUND (SFX_ONE_OBJECT_GET);
						} else {
							AY_PLAY_SOUND (SFX_ONE_OBJECT_WRONG);
							hotspot_destroy = 0;
							hotspot_y = 240;
						}
					#else
						++ p_objs;
						#ifdef OBJECT_COUNT
							flags [OBJECT_COUNT] = p_objs;
						#endif

						AY_PLAY_SOUND (SFX_OBJECT_GET);
						
						#if defined GET_X_MORE && defined PLAYER_NUM_OBJETOS
							if (PLAYER_NUM_OBJETOS > p_objs) {
								_x = 10; _y = 11; _gp_gen = spacer; print_str ();
								getxmore [5] = '0' + PLAYER_NUM_OBJETOS - p_objs;
								_x = 10; _y = 12; _gp_gen = getxmore; print_str ();
								_x = 10; _y = 13; _gp_gen = spacer; print_str ();
								cpc_ShowTileMap (0);
								espera_activa (100);
								draw_scr_background ();
							}
						#endif							
					#endif
					break;
			#endif

			#ifndef DEACTIVATE_KEYS
				case 2:
					p_keys ++;
					AY_PLAY_SOUND (SFX_KEY_GET);
					break;
			#endif

			#ifndef DEACTIVATE_REFILLS
				case 3:
					p_life += PLAYER_REFILL;
					#ifndef PLAYER_DONT_LIMIT_LIFE
						if (p_life > PLAYER_LIFE)
					#endif
						p_life = PLAYER_LIFE;
					AY_PLAY_SOUND (SFX_REFILL_GET);
					
					break;
			#endif

			#ifdef MAX_AMMO
				case 4:
					if (MAX_AMMO - p_ammo > AMMO_REFILL)
						p_ammo += AMMO_REFILL;
					else
						p_ammo = MAX_AMMO;
					AY_PLAY_SOUND (SFX_REFILL_GET);
					break;
			#endif

			#ifdef TIMER_ENABLE
				case 5:
					if (99 - timer_t > TIMER_REFILL)
						timer_t += TIMER_REFILL;
					else
						timer_t = 99;
					AY_PLAY_SOUND (SFX_REFILL_GET);
					break;
			#endif

			#ifdef ENABLE_CHECKPOINTS
				case 6:
					mem_save ();
					AY_PLAY_SOUND (SFX_START);
					break;						
			#endif

			#include "my/ci/hotspots_custom.h"
		}
			
		if (hotspot_destroy) {
			hotspots [n_pant].act = 0;
			_x = hotspot_x >> 4; _y = hotspot_y >> 4; _t = orig_tile;
			draw_invalidate_coloured_tile_gamearea ();
			hotspot_y = 240;
		}
	}
}
