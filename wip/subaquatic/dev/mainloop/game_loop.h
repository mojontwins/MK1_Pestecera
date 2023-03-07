// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// game_loop.h - Da game loop.

	#asm
		; Makes debugging easier
		._game_loop_init
	#endasm

	playing = 1;
	player_init ();

	#ifndef COMPRESSED_LEVELS		
		hotspots_init ();
	#endif

	#ifndef COMPRESSED_LEVELS		
		#if !defined DEACTIVATE_KEYS && MAX_CERROJOS > 0
			locks_init ();
		#endif
	#endif

	#if defined(PLAYER_STEPS_ON_ENEMIES) || defined (PLAYER_CAN_FIRE)
		#ifndef COMPRESSED_LEVELS
			enems_init ();
		#endif
	#endif	

	#ifndef COMPRESSED_LEVELS	
		n_pant = SCR_INICIO;
	#endif		

	maincounter = 0;

	#ifdef ACTIVATE_SCRIPTING		
		script_result = 0;
	#endif
	
	// Play music
	#ifdef COMPRESSED_LEVELS		
		AY_PLAY_MUSIC (levels [level].music_id);
	#else
		AY_PLAY_MUSIC (1);
	#endif		

	#ifdef ACTIVATE_SCRIPTING
		// Entering game
		run_script (2 * MAP_W * MAP_H);
	#endif
	#include "my/ci/entering_game.h"
	
	#ifdef PLAYER_STEPS_ON_ENEMIES 	
		#ifdef SHOW_TOTAL
		// Show total of enemies next to the killed amount.
		_x = KILLED_Y; _y = KILLED_X; _t = BADDIES_COUNT; print_number2 ();
		#endif
	#endif

	p_killme = success = half_life = 0;
		
	objs_old = keys_old = life_old = killed_old = 0xff;
	#ifdef MAX_AMMO 	
		ammo_old = 0xff;
	#endif
	#if defined(TIMER_ENABLE) && defined(PLAYER_SHOW_TIMER)
		timer_old = 0;
	#endif

	#ifdef PLAYER_CHECK_MAP_BOUNDARIES		
		#ifdef COMPRESSED_LEVELS
			x_pant = n_pant % level_data->map_w;
			y_pant = n_pant / level_data->map_w;
		#else
			x_pant = n_pant % MAP_W; y_pant = n_pant / MAP_W;
		#endif
	#endif

	#ifdef ENABLE_CHECKPOINTS
		if (sg_do_load) {
			mem_load ();
		}
	#endif		

	#ifdef MSC_MAXITEMS
		display_items ();
	#endif

	o_pant = 0xff;
	while (playing) {
		#asm
			; Makes debugging easier
			._game_loop_do
		#endasm

		p_kill_amt = 1;
		//pad0 = (joyfunc) (&keys);

		if (o_pant != n_pant) {
			#include "my/ci/before_entering_screen.h"
			draw_scr ();
			o_pant = n_pant;
		}

		#ifdef TIMER_ENABLE
			#if defined(TIMER_SCRIPT_0) && defined(ACTIVATE_SCRIPTING)
				if (timer_zero) {
					timer_zero = 0;
					#ifdef SHOW_TIMER_OVER
						clear_sprites ();
						time_over ();
					#endif
					run_script (2 * MAP_W * MAP_H + 3); 	// ON_TIMER_OFF	
				}	
			#endif

			#ifdef TIMER_KILL_0
				if (timer_zero) {
					#ifdef SHOW_TIMER_OVER
						#ifndef TIMER_SCRIPT_0
							clear_sprites ();
							time_over ();
						#endif
					#endif				
					timer_zero = 0;
					#ifdef TIMER_AUTO_RESET 			
						timer_t = TIMER_INITIAL;
					#endif
					
					#ifdef MODE_128K
						p_killme = 7;
					#else
						p_killme = 4;
					#endif

					#ifdef PLAYER_FLICKERS
						p_estado = EST_PARP;
						p_ct_estado = 50;
					#endif

					#if defined(TIMER_WARP_TO_X) && defined(TIMER_WARP_TO_Y)
						p_x = TIMER_WARP_TO_X << 10;
						p_y = TIMER_WARP_TO_Y << 10;
					#endif

					#ifdef TIMER_WARP_TO
						n_pant = TIMER_WARP_TO;
						draw_scr ();
					#endif
				}
			#endif

			// Timer
			if (timer_on) {
				timer_count ++;
				if (timer_count == timer_frames) {
					timer_count = 0;
					timer_t --;
					if (timer_t == 0) timer_zero = 1;
				}
			}
		#endif

		#include "mainloop/hud.h"

		maincounter ++;
		half_life = !half_life;
		
		// Move player
		player_move ();
		
		// Move enemies
		enems_move ();

		#ifdef ENABLE_SIMPLE_COCOS
			// Move simple cocos
			simple_coco_update ();
		#endif

		if (p_killme) {
			if (p_life) {
				player_kill (p_killme);
				#include "my/ci/on_player_killed.h"
			} else playing = 0;
		}

		#ifdef PLAYER_CAN_FIRE
			// Move bullets 			
			bullets_move ();
		#endif

		#ifdef ENABLE_TILANIMS
			tilanims_do ();
		#endif

		// Detect fire zone
		#if defined ACTIVATE_SCRIPTING && defined ENABLE_FIRE_ZONE
			if (f_zone_ac == 1) {
				if (gpx >= fzx1 && gpx <= fzx2 && gpy >= fzy1 && gpy <= fzy2) {
					run_fire_script ();
				}	
			}
		#endif

		// Render
		if (o_pant == n_pant) {
			cpc_UpdateNow (1);
		}

		#ifdef PLAYER_FLICKERS
			// Flickering
			if (p_estado == EST_PARP) {
				p_ct_estado --;
				if (p_ct_estado == 0)
					p_estado = EST_NORMAL; 
			}
		#endif			
		
		// Hotspot interaction.
		hotspots_do ();

		// Scripting related stuff
		
		#ifdef ACTIVATE_SCRIPTING
			// Select object
			#ifdef MSC_MAXITEMS				
				if (cpc_TestKey (KEY_AUX2)) {
					if (!key_z_pressed) {
						AY_PLAY_SOUND (0);
						flags [FLAG_SLOT_SELECTED] = (flags [FLAG_SLOT_SELECTED] + 1) % MSC_MAXITEMS;
						display_items ();
					}
					key_z_pressed = 1;
				} else {
					key_z_pressed = 0;
				}				
			#endif			

			#ifndef SCRIPTING_KEY_NONE
				#ifdef SCRIPTING_KEY_AUX1
					if (cpc_TestKey (KEY_AUX1))
				#endif
				#ifdef SCRIPTING_DOWN
					if (cpc_TestKey (KEY_DOWN))
				#endif
				#ifdef SCRIPTING_KEY_FIRE
					if (cpc_TestKey (KEY_BUTTON_A))
				#endif
				{
					// Any scripts to run in this screen?
					run_fire_script ();
				}
			#endif
		#endif

		#ifdef PAUSE_ABORT
			// Pause/Abort handling
			
			if (cpc_TestKey (KEY_ENTER)) {
				while (cpc_TestKey (KEY_ENTER));
				isr_player_on = 0;
				clear_sprites ();
				pause_screen ();
				while (!cpc_TestKey (KEY_ENTER));
				while (cpc_TestKey (KEY_ENTER));
				draw_scr ();
				isr_player_on = 1;
			}			
			if (cpc_TestKey (KEY_ESC)) {
				playing = 0;
			}
			
		#endif

		#ifdef DEBUG_KEYS
			if (cpc_TestKey (KEY_AUX1) && cpc_TestKey (KEY_AUX2)) {
				playing = 0; success = 1;
			}
		#endif

		// Flick the screen ?
		
		#include "mainloop/flick_screen.h"			

		// Win game condition
		
		if (0
			#ifdef ACTIVATE_SCRIPTING
				|| script_result == 1 || script_result > 2
			#endif
			#ifdef PLAYER_NUM_OBJETOS
				|| p_objs == PLAYER_NUM_OBJETOS
			#endif
			#ifdef SCR_FIN
				|| (n_pant == SCR_FIN
				#if defined PLAYER_FIN_X && defined PLAYER_FIN_Y				
					&& ((gpx + 8) >> 4) == PLAYER_FIN_X && ((gpy + 8) >> 4) == PLAYER_FIN_Y
				#endif
				)
			#endif
		) {
			success = 1;
			playing = 0;
		}
		
		// Game over condition
		#if defined ACTIVATE_SCRIPTING || (defined(TIMER_ENABLE) && defined(TIMER_GAMEOVER_0)) 
			if (0
				#ifdef ACTIVATE_SCRIPTING
					|| (script_result == 2)
				#endif
				#if defined(TIMER_ENABLE) && defined(TIMER_GAMEOVER_0)
					|| timer_zero
				#endif
			) {
				playing = 0;				
			}
		#endif

		#include "my/ci/extra_routines.h"
	}
	
	AY_STOP_SOUND ();

	#include "my/ci/after_game_loop.h"
