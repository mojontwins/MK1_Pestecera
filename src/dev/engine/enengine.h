// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// enengine.h

#ifdef ENABLE_PURSUERS
	void enems_pursuers_init (void) {
		en_an_alive [enit] = 0;
		en_an_dead_row [enit] = DEATH_COUNT_ADD + (rand () & DEATH_COUNT_AND);
	}
#endif

#ifndef COMPRESSED_LEVELS
	#if defined(PLAYER_STEPS_ON_ENEMIES) || defined (PLAYER_CAN_FIRE)
		void enems_init (void) {
			enit = 0;
			while (enit < MAP_W * MAP_H * MAX_ENEMS) {
				malotes [enit].t = malotes [enit].t & 15;	
				#ifdef PLAYER_CAN_FIRE
					malotes [enit].life = ENEMIES_LIFE_GAUGE;
				#endif
				enit ++;
			}
		}
	#endif
#endif

void enems_load (void) {
	// Movemos y cambiamos a los enemigos según el tipo que tengan
	enoffs = n_pant * MAX_ENEMS;
	
	for (enit = 0; enit < MAX_ENEMS; ++ enit) {
		en_an_frame [enit] = 0;
		en_an_state [enit] = 0;
		en_an_count [enit] = 3;
		enoffsmasi = enoffs + enit;

		#ifdef RESPAWN_ON_ENTER
			// Back to life!
			malotes [enoffsmasi].t &= 0xEF;		
			#ifdef PLAYER_CAN_FIRE
				#if defined (COMPRESSED_LEVELS) && defined (MODE_128K)
					malotes [enoffsmasi].life = level_data.enems_life;
				#else
					malotes [enoffsmasi].life = ENEMIES_LIFE_GAUGE;
				#endif
			#endif
		#endif

		#include "my/ci/enems_custom_respawn.h"

		en_an_next_frame [enit] = SPRFR_EMPTY;

		rdt = malotes [enoffsmasi].t & 0x1f; 
		if (rdt) {
			switch (rdt) {
				case 1:
				case 2:
				case 3:
				case 4:
					en_an_base_frame [enit] = GENERAL_ENEMS_BASE_CELL + ((malotes [enoffsmasi].t - 1) << 1);
					break;

				#ifdef ENABLE_ORTHOSHOOTERS
					case 5:					
						#if ORTHOSHOOTERS_BASE_CELL==99
							en_an_base_frame [enit] = ORTHOSHOOTERS_BASE_CELL;
						#else
							en_an_base_frame [enit] = GENERAL_ENEMS_BASE_CELL + (ORTHOSHOOTERS_BASE_CELL << 1);
						#endif
						en_an_state [enit] = malotes [enoffsmasi].t >> 6;
						break;
				#endif

				#ifdef ENABLE_FANTIES
					case 6:
						en_an_base_frame [enit] = GENERAL_ENEMS_BASE_CELL + (FANTIES_BASE_CELL << 1);
						en_an_x [enit] = malotes [enoffsmasi].x1 << 6;
						en_an_y [enit] = malotes [enoffsmasi].y1 << 6;
						en_an_vx [enit] = en_an_vy [enit] = 0;

						#ifdef PLAYER_CAN_FIRE
							malotes [enoffsmasi].life = FANTIES_LIFE_GAUGE;	
						#endif
						#ifdef FANTIES_TYPE_HOMING
							en_an_state [enit] = TYPE_6_IDLE;
						#endif
						break;				
				#endif

				#ifdef ENABLE_PURSUERS
					case 7:
						enems_pursuers_init ();
						en_an_base_frame [enit] = 0;
						break;
				#endif

					#include "my/ci/enems_load.h"

				default:
					en_an_base_frame [enit] = 0xff;
			}
		} else {
			en_an_base_frame [enit] = 0xff;
		}

		// Sprite creation

		rda = SP_ENEMS_BASE + enit;
		if (rdb = en_an_base_frame [enit] != 0xff) { 
			sp_sw [rda].cox = sm_cox [rdb];
			sp_sw [rda].coy = sm_coy [rdb];
			sp_sw [rda].invfunc = sm_invfunc [rdb];
			sp_sw [rda].updfunc = sm_updfunc [rdb];
			en_an_next_frame [enit] = sm_sprptr [rdb];
		} else {
			en_an_next_frame [enit] = SPRFR_EMPTY;
		}

		#ifdef ENABLE_PURSUERS
			if (rdt == 7) en_an_next_frame [enit] = SPRFR_EMPTY;
		#endif

		#include "my/ci/enems_extra_mods.h"
	}
}

void enems_kill (void) {
	if (_en_t != 7) _en_t |= 16;
	++ p_killed;

	#ifdef BODY_COUNT_ON
		flags [BODY_COUNT_ON] = p_killed;
	#endif

	#include "my/ci/on_enems_killed.h"

	#ifdef ACTIVATE_SCRIPTING					
		run_script (2 * MAP_W * MAP_H + 5); 	// PLAYER_KILLS_ENEMY
	#endif
}

void enems_move (void) {
	tocado = p_gotten = ptgmx = ptgmy = 0;

	for (enit = 0; enit < MAX_ENEMS; enit ++) {
		active = 0;
		enoffsmasi = enoffs + enit;

		// Copy array values to temporary variables as fast as possible
		
		#asm
				// Those values are stored in this order:
				// x, y, x1, y1, x2, y2, mx, my, t[, life]
				// Point HL to baddies [enoffsmasi]. The struct is 9 or 10 bytes long
				// so this is baddies + enoffsmasi*(9|10) depending on PLAYER_CAN_FIRE
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
				inc hl 

				ld  a, (hl)
				ld  (__en_x1), a
				inc hl 

				ld  a, (hl)
				ld  (__en_y1), a
				inc hl 

				ld  a, (hl)
				ld  (__en_x2), a
				inc hl 

				ld  a, (hl)
				ld  (__en_y2), a
				inc hl 

				ld  a, (hl)
				ld  (__en_mx), a
				inc hl 

				ld  a, (hl)
				ld  (__en_my), a
				inc hl 

				ld  a, (hl)
				ld  (__en_t), a
				and 0x1f
				ld  (_rdt), a

			#ifdef PLAYER_CAN_FIRE
				inc hl 

				ld  a, (hl)
				ld  (__en_life), a
			#endif
		#endasm

		#if defined PLAYER_CAN_FIRE || defined ENABLE_PURSUERS
			_en_cx = _en_x; _en_cy = _en_y;
		#endif
		
		if (en_an_state [enit] == GENERAL_DYING) {
			-- en_an_count [enit];
			if (en_an_count [enit] == 0) {
				en_an_state [enit] = 0;
				en_an_next_frame [enit] = SPRFR_EMPTY;
				continue;
			}
		}
		
		#ifndef PLAYER_GENITAL
			#if defined (BOUNDING_BOX_8_CENTERED) || defined (BOUNDING_BOX_8_BOTTOM)
				pregotten = (gpx + 12 >= _en_x && gpx <= _en_x + 12);
			#else
				pregotten = (gpx + 15 >= _en_x && gpx <= _en_x + 15);
			#endif
		#endif

		switch (rdt) {
			case 1:
			case 2:
			case 3:
			case 4:
			#ifdef ENABLE_ORTHOSHOOTERS
				case 5:
			#endif
				#include "engine/enem_mods/enem_type_lineal.h"
				#ifdef ENABLE_ORTHOSHOOTERS
					if (rdt == 5) {
						#include "engine/enem_mods/enem_type_orthoshooters.h"
					}
				#endif
				break;

			#ifdef ENABLE_FANTIES
				case 6:	
					#include "engine/enem_mods/enem_type_fanties.h"
					break;
			#endif
			#ifdef ENABLE_PURSUERS
				case 7:
					#include "engine/enem_mods/enem_type_pursuers_asm.h"
					break;	
			#endif
			#include "my/ci/enems_move.h"
			/*
			default:
				if (en_an_state [enit] != GENERAL_DYING) en_an_next_frame [enit] = sprite_18_a;
			*/
		}
		
		if (active) {			
			// Animate
			if (en_an_base_frame [enit] != 99) {
				/*
				en_an_count [enit] ++; 
				if (en_an_count [enit] == 4) {
					en_an_count [enit] = 0;
					en_an_frame [enit] = !en_an_frame [enit];					
					en_an_next_frame [enit] = sm_sprptr [en_an_base_frame [enit] + en_an_frame [enit]];
				}
				*/
				
				#asm
						ld  bc, (_enit)
						ld  b, 0

						ld  hl, _en_an_count
						add hl, bc
						ld  a, (hl)
						inc a
						ld  (hl), a

						cp  4
						jr  nz, _enems_move_update_frame_done

						xor a
						ld  (hl), a

						ld  hl, _en_an_frame
						add hl, bc
						ld  a, (hl)
						xor 1
						ld  (hl), a
						
						ld  hl, _en_an_base_frame
						add hl, bc
						ld  d, (hl)
						add d 							; A = en_an_base_frame [enit] + en_an_frame [enit]]

						sla c 							; Index 16 bits; it never overflows.
						ld  hl, _en_an_next_frame
						add hl, bc
						ex de, hl 						; DE -> en_an_next_frame [enit]

						sla a
						ld  c, a
						ld  b, 0

						ld  hl, _sm_sprptr
						add hl, bc 						; HL -> enem_cells [en_an_base_frame [enit] + en_an_frame [enit]]

						ldi
						ldi 							; Copy 16 bit
					._enems_move_update_frame_done
				#endasm
				
			}
			
			// Collide with player
			
			#if !defined PLAYER_GENITAL && !defined DISABLE_PLATFORMS
				// Platforms
				if (_en_t == 4) {
					if (pregotten) {

						// Horizontal moving platforms
						if (_en_mx) {
							if (gpy + 17 >= _en_y && gpy + 8 <= _en_y) {
								p_gotten = 1;
								ptgmx = _en_mx << 6;
								gpy = (_en_y - 16); p_y = gpy << 6;
							}
						}

						// Vertical moving platforms
						if (
							(_en_my < 0 && gpy + 18 >= _en_y && gpy + 8 <= _en_y) ||
							(_en_my > 0 && gpy + 17 + _en_my >= _en_y && gpy + 8 <= _en_y)
						) {
							p_gotten = 1;
							ptgmy = _en_my << 6;
							gpy = (_en_y - 16); p_y = gpy << 6;						
						}

					}
				} else
			#endif
			{
				#include "my/ci/custom_enems_player_collision.h"
			
				cx2 = _en_x; cy2 = _en_y;
				if (!tocado && collide () && p_estado == EST_NORMAL) {
					#ifdef PLAYER_STEPS_ON_ENEMIES
					// Step over enemy		
						#ifdef PLAYER_CAN_STEP_ON_FLAG
							if (flags [PLAYER_CAN_STEP_ON_FLAG] != 0 && 
								gpy < _en_y - 2 && p_vy >= 0 && rdt >= PLAYER_MIN_KILLABLE)
						#else
							if (gpy < _en_y - 2 && p_vy >= 0 && rdt >= PLAYER_MIN_KILLABLE)
						#endif				
						{
							AY_PLAY_SOUND (SFX_KILL_ENEMY_STEP);										
							en_an_state [enit] = GENERAL_DYING;
							en_an_count [enit] = 12;
							en_an_next_frame [enit] = sprite_17_a;
							p_vy = -256;
						
							enems_kill ();
						} else
					#endif
					{
						tocado = 1;
						#if defined(SLOW_DRAIN) && defined(PLAYER_BOUNCES)
							if (!lasttimehit || ((maincounter & 3) == 0)) {
									p_killme = SFX_ENEMY_HIT;
							}
						#else
								p_killme = SFX_ENEMY_HIT;
						#endif					
						
						#ifdef PLAYER_BOUNCES
							#ifdef ENABLE_FANTIES
								if (_en_t == 6) {
									p_vx = en_an_vx [enit] + en_an_vx [enit];
									p_vy = en_an_vy [enit] + en_an_vy [enit];	
								} else
							#endif
							
							#ifndef PLAYER_GENITAL	
								{
									p_vx = addsign (_en_mx, PLAYER_MAX_VX);
									p_vy = addsign (_en_my, PLAYER_MAX_VX);
								}
							#else
								{
									if (_en_mx) {
										p_vx = addsign (gpx - _en_x, abs (_en_mx) << 8);
									}
									if (_en_my) {
										p_vy = addsign (gpy - _en_y, abs (_en_my) << 8);
									}
								}
							#endif
						#endif

						#include "my/ci/on_enems_collision.h"
					}
				}
			}
			player_enem_collision_done:
			
			#ifdef PLAYER_CAN_FIRE
				// Collide with bullets
				#ifdef FIRE_MIN_KILLABLE
					if (rdt >= FIRE_MIN_KILLABLE)
				#endif				
				{
					for (gpjt = 0; gpjt < MAX_BULLETS; gpjt ++) {
						if (bullets_estado [gpjt] == 1) {
							blx = bullets_x [gpjt] + 3; 
							bly = bullets_y [gpjt] + 3;
							if (blx >= _en_x && blx <= _en_x + 15 && bly >= _en_y && bly <= _en_y + 15) {
								#ifdef ENABLE_FANTIES
									if (_en_t == 6) {
										en_an_vx [enit] += addsign (bullets_mx [gpjt], 128);
									}
								#endif
								_en_x = _en_cx;
								_en_y = _en_cy;
								en_an_next_frame [enit] = sprite_17_a;
								bullets_estado [gpjt] = 0;
								#if !defined PLAYER_GENITAL && !defined DISABLE_PLATFORMS							
									if (_en_t != 4) -- _en_life;
								#else
									-- _en_life;
								#endif
								
								if (_en_life == 0) {
									en_an_state [enit] = GENERAL_DYING;
									en_an_count [enit] = 12;
									AY_PLAY_SOUND (SFX_KILL_ENEMY_SHOOT);
									
									#ifdef ENABLE_PURSUERS
										enems_pursuers_init ();
									#endif

									enems_kill ();					
								}

								AY_PLAY_SOUND (SFX_HIT_ENEMY);
							}
						}
					}

				}
			#endif

			#include "my/ci/enems_extra_actions.h"
		} 

		rda = SP_ENEMS_BASE + enit; rdt = en_an_sprid [enit];
		sp_sw [rda].cx = (_en_x + VIEWPORT_X * 8 + sp_sw [rda].cox) >> 2;
		sp_sw [rda].cy = (_en_y + VIEWPORT_Y * 8 + sp_sw [rda].coy);
		if (rdt != 0xff) sp_sw [rda].sp0 = (int) (en_an_next_frame [enit]);
		else sp_sw [rda].sp0 = (int) (SPRFR_EMPTY);

		#asm		
				// Those values are stored in this order:
				// x, y, x1, y1, x2, y2, mx, my, t[, life]

				ld  hl, (__baddies_pointer) 		// Restore pointer

				ld  a, (__en_x)
				ld  (hl), a
				inc hl

				ld  a, (__en_y)
				ld  (hl), a
				inc hl

				ld  a, (__en_x1)
				ld  (hl), a
				inc hl

				ld  a, (__en_y1)
				ld  (hl), a
				inc hl

				ld  a, (__en_x2)
				ld  (hl), a
				inc hl

				ld  a, (__en_y2)
				ld  (hl), a
				inc hl

				ld  a, (__en_mx)
				ld  (hl), a
				inc hl

				ld  a, (__en_my)
				ld  (hl), a
				inc hl

				ld  a, (__en_t)
				ld  (hl), a
				inc hl

			#ifdef PLAYER_CAN_FIRE
				ld  a, (__en_life)
				ld  (hl), a
			#endif
		#endasm	
	}

	#if defined(SLOW_DRAIN) && defined(PLAYER_BOUNCES)
		lasttimehit = tocado;
	#endif
}
