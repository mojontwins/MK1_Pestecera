// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// player.h

#ifndef BOUNCE_EXPRESSION_Y
	#define BOUNCE_EXPRESSION_Y (-(p_vy >> 1))
#endif
#ifndef BOUNCE_EXPRESSION_X
	#define BOUNCE_EXPRESSION_X (-(p_vx >> 1))
#endif

void player_init (void) {
	// Inicializa player con los valores iniciales
	// (de ahí lo de inicializar).
		
	#ifndef COMPRESSED_LEVELS
		gpx = PLAYER_INI_X << 4; p_x = gpx << 6;
		gpy = PLAYER_INI_Y << 4; p_y = gpy << 6;
	#endif	

	p_vy = 0;
	p_vx = 0;
	p_cont_salto = 1;
	p_saltando = 0;
	p_frame = 0;
	p_subframe = 0;
	
	#ifdef PLAYER_GENITAL
		p_facing = FACING_DOWN;
		p_facing_v = p_facing_h = 0xff;
	#else
		p_facing = 1;
	#endif	
	
	p_estado = 	EST_NORMAL;
	p_ct_estado = 0;
	
	#if !defined(COMPRESSED_LEVELS) || defined(REFILL_ME)	
		p_life = 		PLAYER_LIFE;
	#endif
	
	p_objs =	0;
	p_keys = 0;
	p_killed = 0;
	p_disparando = 0;

	#ifdef MAX_AMMO
		#ifdef INITIAL_AMMO
			p_ammo = INITIAL_AMMO;
		#else
			p_ammo = MAX_AMMO;
		#endif
	#endif	

	#ifdef TIMER_ENABLE
		timer_count = 0;
		timer_zero = 0;
		#ifdef TIMER_LAPSE
			timer_frames = TIMER_LAPSE;
		#endif
		#ifdef TIMER_INITIAL
			timer_t = TIMER_INITIAL;
		#endif
		#ifdef TIMER_START
			timer_on = 1;
		#else
			timer_on = 0;
		#endif
	#endif
}

void player_calc_bounding_box (void) {
	#if defined (BOUNDING_BOX_8_BOTTOM)
		#asm
			ld  a, (_gpx)
			add 4
			srl a
			srl a
			srl a
			srl a
			ld  (_ptx1), a
			ld  a, (_gpx)
			add 11
			srl a
			srl a
			srl a
			srl a
			ld  (_ptx2), a
			ld  a, (_gpy)
			add 8
			srl a
			srl a
			srl a
			srl a
			ld  (_pty1), a
			ld  a, (_gpy)
			add 15
			#ifndef PLAYER_GENITAL
				ld  c, a
			#endif
			srl a
			srl a
			srl a
			srl a
			ld  (_pty2), a
			#ifndef PLAYER_GENITAL
				ld  a, c 
				inc a
				srl a
				srl a
				srl a
				srl a
				ld  (_pty2b), a
			#endif
		#endasm
	#elif defined (BOUNDING_BOX_8_CENTERED)
		#asm
			ld  a, (_gpx)
			add 4
			srl a
			srl a
			srl a
			srl a
			ld  (_ptx1), a
			ld  a, (_gpx)
			add 11
			srl a
			srl a
			srl a
			srl a
			ld  (_ptx2), a
			ld  a, (_gpy)
			add 4
			srl a
			srl a
			srl a
			srl a
			ld  (_pty1), a
			ld  a, (_gpy)
			add 11
			#ifndef PLAYER_GENITAL
				ld  c, a
			#endif
			srl a
			srl a
			srl a
			srl a
			ld  (_pty2), a
			#ifndef PLAYER_GENITAL
				ld  a, c 
				inc a
				srl a
				srl a
				srl a
				srl a
				ld  (_pty2b), a
			#endif
		#endasm
	#elif defined (BOUNDING_BOX_12X2_CENTERED)
		#asm
			ld  a, (_gpx)
			add 2
			srl a
			srl a
			srl a
			srl a
			ld  (_ptx1), a
			ld  a, (_gpx)
			add 13
			srl a
			srl a
			srl a
			srl a
			ld  (_ptx2), a
			ld  a, (_gpy)
			add 7
			srl a
			srl a
			srl a
			srl a
			ld  (_pty1), a
			ld  a, (_gpy)
			add 8
			#ifndef PLAYER_GENITAL
				ld  c, a
			#endif
			srl a
			srl a
			srl a
			srl a
			ld  (_pty2), a
			#ifndef PLAYER_GENITAL
				ld  a, c 
				inc a
				srl a
				srl a
				srl a
				srl a
				ld  (_pty2b), a
			#endif
		#endasm
	#else
		#asm
			ld  a, (_gpx)
			srl a
			srl a
			srl a
			srl a
			ld  (_ptx1), a
			ld  a, (_gpx)
			add 15
			srl a
			srl a
			srl a
			srl a
			ld  (_ptx2), a
			ld  a, (_gpy)
			srl a
			srl a
			srl a
			srl a
			ld  (_pty1), a
			ld  a, (_gpy)
			add 15
			#ifndef PLAYER_GENITAL
				ld  c, a
			#endif
			srl a
			srl a
			srl a
			srl a
			ld  (_pty2), a
			#ifndef PLAYER_GENITAL
				ld  a, c 
				inc a
				srl a
				srl a
				srl a
				srl a
				ld  (_pty2b), a
			#endif
		#endasm
	#endif
}

unsigned char player_move (void) {	
		
	// ***************************************************************************
	//  MOVEMENT IN THE VERTICAL AXIS
	// ***************************************************************************

	#if !defined PLAYER_GENITAL || defined VENG_SELECTOR

		#if !defined PLAYER_DISABLE_GRAVITY
			#if defined VENG_SELECTOR && defined PLAYER_VKEYS
				if (veng_selector != VENG_KEYS)
			#endif
			{
				// Do gravity
				
				#asm
						; Signed comparisons are hard
						; p_vy <= PLAYER_MAX_VY_CAYENDO - PLAYER_G

						; We are going to take a shortcut.
						; If p_vy < 0, just add PLAYER_G.
						; If p_vy > 0, we can use unsigned comparison anyway.

						ld  hl, (_p_vy)
						bit 7, h
						jr  nz, _player_gravity_add 	; < 0

						ld  de, PLAYER_MAX_VY_CAYENDO - PLAYER_G
						or  a
						push hl
						sbc hl, de
						pop hl
						jr  nc, _player_gravity_maximum

					._player_gravity_add
						ld  de, PLAYER_G
						add hl, de
						jr  _player_gravity_vy_set

					._player_gravity_maximum
						ld  hl, PLAYER_MAX_VY_CAYENDO

					._player_gravity_vy_set
						ld  (_p_vy), hl

					._player_gravity_done

					#ifdef PLAYER_CUMULATIVE_JUMP
						ld  a, (_p_saltando)
						or  a
						jr  nz, _player_gravity_p_gotten_done
					#endif

						ld  a, (_p_gotten)
						or  a
						jr  z, _player_gravity_p_gotten_done

						ld  hl, 0
						ld  (_p_vy), hl

					._player_gravity_p_gotten_done
				#endasm
			}	
		#endif
	#endif

	#if defined PLAYER_GENITAL || (defined VENG_SELECTOR && defined PLAYER_VKEYS)

		#if defined (VENG_SELECTOR)
			if (veng_selector == VENG_KEYS )
		#endif
		{
			// Pad do

			if ( ! (cpc_TestKey (KEY_UP) || cpc_TestKey (KEY_DOWN))) {
				p_facing_v = 0xff;
				wall_v = 0;
				if (p_vy > 0) {
					p_vy -= PLAYER_RX;
					if (p_vy < 0) p_vy = 0;
				} else if (p_vy < 0) {
					p_vy += PLAYER_RX;
					if (p_vy > 0) p_vy = 0;
				}
			}

			if (cpc_TestKey (KEY_UP)) {
				p_facing_v = FACING_UP;
				if (p_vy > -PLAYER_MAX_VX) p_vy -= PLAYER_AX;
			}

			if (cpc_TestKey (KEY_DOWN)) {
				p_facing_v = FACING_DOWN;
				if (p_vy < PLAYER_MAX_VX) p_vy += PLAYER_AX;
			}
		}
	#endif

	#ifdef PLAYER_HAS_JETPAC
		#ifdef VENG_SELECTOR
			if (veng_selector == VENG_JETPAC)
		#endif
		{
			if (cpc_TestKey (KEY_UP)) {
				p_vy -= PLAYER_INCR_JETPAC;
				if (p_vy < -PLAYER_MAX_VY_JETPAC) p_vy = -PLAYER_MAX_VY_JETPAC;

				#include "my/ci/on_jetpac_boost.h"

				p_jetpac_on = 1;
			} else p_jetpac_on = 0;
		}
	#endif

	#include "my/ci/custom_veng.h"

	p_y += p_vy;
	
	#if !defined (PLAYER_GENITAL)
		if (p_gotten) p_y += ptgmy;
	#endif

	// Safe
		
	if (p_y < 0) p_y = 0;
	if (p_y > 9216) p_y = 9216;

	// gpy = p_y >> 6;
	#asm
			ld  hl, (_p_y)
			call HLshr6_A
			ld  (_gpy), a
	#endasm

	// Collision, may set possee, hit_v
	possee = 0;

	// Velocity positive (going downwards)
	player_calc_bounding_box ();

	hit_v = 0;
	cx1 = ptx1; cx2 = ptx2;
	#if defined (PLAYER_GENITAL)
		if (p_vy < 0)
	#else	
		if (p_vy + ptgmy < 0) 
	#endif
	{
		cy1 = cy2 = pty1;
		cm_two_points ();

		if ((at1 & 8) || (at2 & 8)) {
			#include "my/ci/bg_collision/obstacle_up.h"

			#ifdef PLAYER_BOUNCE_WITH_WALLS
				p_vy = BOUNCE_EXPRESSION_Y;
			#else
				p_vy = 0;
			#endif

			/*
			#if defined (BOUNDING_BOX_8_BOTTOM)			
				gpy = ((pty1 + 1) << 4) - 8;
			#elif defined (BOUNDING_BOX_8_CENTERED)
				gpy = ((pty1 + 1) << 4) - 4;
			#elif defined (BOUNDING_BOX_12X2_CENTERED)
				gpy = ((pty1 + 1) << 4) - 7;
			#elif defined (BOUNDING_BOX_TINY_BOTTOM)
				gpy = ((pty1 + 1) << 4) - 14;
			#else
				gpy = ((pty1 + 1) << 4);
			#endif
			*/

			// KISS mod
			#asm
					ld  a, (_pty1)
					inc a 
					sla a
					sla a
					sla a
					sla a
				#ifdef BOUNDING_BOX_8_BOTTOM
					sub 8
				#elif defined BOUNDING_BOX_8_CENTERED
					sub 4
				#elif defined BOUNDING_BOX_12X2_CENTERED
					sub 7
				#elif defined BOUNDING_BOX_TINY_BOTTOM
					sub 14
				#endif
					ld  (_gpy), a
			#endasm

			//p_y = gpy << 6;
			#asm
					ld  a, (_gpy)
					call Ashl16_HL
					ld  (_p_y), hl
			#endasm

			#if defined PLAYER_GENITAL || defined LOCKS_CHECK_VERTICAL
				wall_v = WTOP;
			#endif
		}
	}
	
	#if defined (PLAYER_GENITAL)
		if (p_vy > 0)
	#else	
		if (p_vy + ptgmy >= 0)
	#endif
	{
		#ifdef PLAYER_GENITAL
		cy1 = cy2 = pty2;
		#else
			cy1 = cy2 = pty2b;
		#endif
		cm_two_points ();

		#ifdef PLAYER_GENITAL
			if ((at1 & 8) || (at2 & 8))
		#else
			// Greed Optimization tip! Remove this line and uncomment the next one:
			// (As long as you don't have type 8 blocks over type 4 blocks in your game, the short line is fine)
			if ((at1 & 8) || (at2 & 8) || ((gpy & 15) < 8 && ((at1 & 4) || (at2 & 4))))
			//if (((gpy - 1) & 15) < 7 && ((at1 & 12) || (at2 & 12))) {
		#endif			
		{
			#include "my/ci/bg_collision/obstacle_down.h"

			#ifdef PLAYER_BOUNCE_WITH_WALLS
				p_vy = BOUNCE_EXPRESSION_Y;
			#else
				#ifdef PLAYER_CUMULATIVE_JUMP
					if (p_saltando == 0)
				#endif				
				p_vy = 0;
			#endif
				
			/*
			#if defined (BOUNDING_BOX_8_BOTTOM) || defined (BOUNDING_BOX_TINY_BOTTOM)
				gpy = (pty2 - 1) << 4;
			#elif defined (BOUNDING_BOX_12X2_CENTERED)
				gpy = ((pty2 - 1) << 4) + 7;
			#elif defined (BOUNDING_BOX_8_CENTERED)				
				gpy = ((pty2 - 1) << 4) + 4;
			#else
				gpy = (pty2 - 1) << 4;				
			#endif
			*/

			// KISS mod
			#asm
				#ifdef PLAYER_GENITAL
					ld  a, (_pty2)
				#else
						ld  a, (_pty2b)
				#endif
					dec a 
					sla a
					sla a
					sla a
					sla a
				#ifdef BOUNDING_BOX_12X2_CENTERED
					add 7
				#elif defined BOUNDING_BOX_8_CENTERED
					add 4
				#endif
					ld  (_gpy), a
			#endasm

			//p_y = gpy << 6;
			#asm
					ld  a, (_gpy)
					call Ashl16_HL
					ld  (_p_y), hl
			#endasm
			
			// Finally

			#if defined PLAYER_GENITAL || defined LOCKS_CHECK_VERTICAL
				wall_v = WBOTTOM;
			#endif

			#ifndef PLAYER_GENITAL
				#ifdef DIE_AND_RESPAWN
					if (
						#ifdef SAFE_SPOT_ON_ENTERING
							safe_n_pant != n_pant
						#else
							was_possee == 0
						#endif
					) {
						safe_n_pant = n_pant;
						safe_gpx = gpx; safe_gpy = gpy;						
					}
				#endif
				possee = 1;
			#endif
		}
	}

	#if defined DIE_AND_RESPAWN && !defined PLAYER_GENITAL
		was_possee = possee;
	#endif

	#ifndef PLAYER_GENITAL
		cy1 = cy2 = pty2;
	#endif

	#ifndef DEACTIVATE_EVIL_TILE
		#ifndef CUSTOM_EVIL_TILE_CHECK
			// if (p_vy) hit_v = ((at1 & 1) || (at2 & 1));
			#asm
					ld  a, (_p_vy)
					ld  c, a
					ld  a, (_p_vy + 1)
					or  c
					jr  z, evil_tile_check_vert_done

					ld  a, (_at1)
					and 1
					ld  c, a
					ld  a, (_at2) 
					and 1 
					or  c 

					ld  (_hit_v), a
				.evil_tile_check_vert_done
			#endasm
		#endif
	#endif
	
	/*
	gpxx = gpx >> 4;
	gpyy = gpy >> 4;
	*/
	#asm
			ld  a, (_gpx)
			srl a
			srl a
			srl a
			srl a
			ld  (_gpxx), a
			ld  a, (_gpy)
			srl a
			srl a
			srl a
			srl a
			ld  (_gpyy), a
	#endasm

	/*
	#ifndef PLAYER_GENITAL
		cy1 = cy2 = (gpy + 16) >> 4;
		cx1 = ptx1; cx2 = ptx2;
		cm_two_points ();
		possee |= ((at1 & 12) || (at2 & 12)) && (gpy & 15) < 8;
	#endif
	*/

	// Jump

	#ifdef PLAYER_HAS_JUMP
		#ifdef VENG_SELECTOR
			if (veng_selector == VENG_JUMP)
		#endif
		{
			#if defined (PLAYER_CAN_FIRE) && !defined (USE_TWO_BUTTONS)
				rda = cpc_TestKey (KEY_UP);
			#elif defined (PLAYER_CAN_FIRE) && defined (USE_TWO_BUTTONS)				
				rda = cpc_TestKey (KEY_BUTTON_B);
			#else
				#if defined BOTH_KEYS_JUMP
					rda = cpc_TestKey (KEY_BUTTON_A) || cpc_TestKey (KEY_UP);
				#else 
					rda = cpc_TestKey (KEY_BUTTON_A);
				#endif
			#endif

			if (rda) {
				#ifdef PLAYER_CUMULATIVE_JUMP
					if (p_vy >= 0) {
						if (possee || p_gotten || hit_v) {
							p_vy = -p_vy - (p_saltando ? PLAYER_INCR_SALTO : PLAYER_VY_INICIAL_SALTO + PLAYER_G);
							if (p_vy < -PLAYER_MAX_VY_SALTANDO) p_vy = -PLAYER_MAX_VY_SALTANDO;
							p_saltando = 1;
	
							AY_PLAY_SOUND (SFX_JUMP);
						}
					}
				#else
					if (p_saltando == 0) {
						if (possee || p_gotten || hit_v) {
							p_saltando = 1;
							p_cont_salto = 0;
							AY_PLAY_SOUND (SFX_JUMP);
						}
					} else {
						p_vy -= (PLAYER_VY_INICIAL_SALTO + PLAYER_INCR_SALTO - (p_cont_salto >> 1));
						if (p_vy < -PLAYER_MAX_VY_SALTANDO) p_vy = -PLAYER_MAX_VY_SALTANDO;
						++ p_cont_salto;
						if (p_cont_salto == 9) p_saltando = 0;
					}
				#endif
			} else p_saltando = 0;
		}
	#endif

	// Bootee engine

	#ifdef PLAYER_BOOTEE
		#ifdef VENG_SELECTOR
			if (veng_selector == VENG_BOOTEE)
		#endif
		{
			if ( p_saltando == 0 && (possee || p_gotten || hit_v) ) {
				p_saltando = 1;
				p_cont_salto = 0;
				AY_PLAY_SOUND (SFX_JUMP);
			}
			
			if (p_saltando ) {
				p_vy -= (PLAYER_VY_INICIAL_SALTO + PLAYER_INCR_SALTO - (p_cont_salto>>1));
				if (p_vy < -PLAYER_MAX_VY_SALTANDO) p_vy = -PLAYER_MAX_VY_SALTANDO;
				++ p_cont_salto;
				if (p_cont_salto == 8)
					p_saltando = 0;
			}
		}
	#endif	

	// ***************************************************************************
	//  MOVEMENT IN THE HORIZONTAL AXIS
	// ***************************************************************************

	#ifndef PLAYER_DISABLE_DEFAULT_HENG
		if ( ! (cpc_TestKey (KEY_LEFT) || cpc_TestKey (KEY_RIGHT))) {
			#ifdef PLAYER_GENITAL		
				p_facing_h = 0xff;
			#endif
			if (p_vx > 0) {
				p_vx -= PLAYER_RX;
				if (p_vx < 0) p_vx = 0;
			} else if (p_vx < 0) {
				p_vx += PLAYER_RX;
				if (p_vx > 0) p_vx = 0;
			}
			wall_h = 0;
		}

		if (cpc_TestKey (KEY_LEFT)) {
			#ifdef PLAYER_GENITAL
				p_facing_h = FACING_LEFT;
			#endif
			if (p_vx > -PLAYER_MAX_VX) {
				#ifndef PLAYER_GENITAL			
					p_facing = 0;
				#endif
				p_vx -= PLAYER_AX;
			}
		}

		if (cpc_TestKey (KEY_RIGHT)) {
			#ifdef PLAYER_GENITAL	
				p_facing_h = FACING_RIGHT;
			#endif
			if (p_vx < PLAYER_MAX_VX) {
				p_vx += PLAYER_AX;
				#ifndef PLAYER_GENITAL						
					p_facing = 1;
				#endif
			}
		}
	#endif

	#include "my/ci/custom_heng.h"

	p_x = p_x + p_vx;
	#ifndef PLAYER_GENITAL
		p_x += ptgmx;
	#endif
	
	// Safe
	
	if (p_x < 0) p_x = 0;
	if (p_x > 14336) p_x = 14336;

	/*
	gpox = gpx;
	gpx = p_x >> 6;
	*/
	#asm
			ld  a, (_gpx)
			ld  (_gpox), a 
			ld  hl, (_p_x)
			call HLshr6_A
			ld  (_gpx), a	
	#endasm
		
	// Collision. May set hit_h
	player_calc_bounding_box ();

	hit_h = 0;
	cy1 = pty1; cy2 = pty2;

	#if defined (PLAYER_GENITAL)
		if (p_vx < 0)
	#else	
		if (p_vx + ptgmx < 0)
	#endif
	{
		cx1 = cx2 = ptx1;
		cm_two_points ();

		if ((at1 & 8) || (at2 & 8)) {
			#include "my/ci/bg_collision/obstacle_left.h"

			#ifdef PLAYER_BOUNCE_WITH_WALLS
				p_vx = BOUNCE_EXPRESSION_X;
			#else
				p_vx = 0;
			#endif

			/*
			#if defined (BOUNDING_BOX_8_BOTTOM) || defined (BOUNDING_BOX_8_CENTERED) || defined (BOUNDING_BOX_TINY_BOTTOM)				
				gpx = ((ptx1 + 1) << 4) - 4;
			#elif defined (BOUNDING_BOX_12X2_CENTERED)	
				gpx = ((ptx1 + 1) << 4) - 2;
			#else
				gpx = ((ptx1 + 1) << 4);
			#endif
			*/

			// KISS mod

			#asm
					ld  a, (_ptx1)
					inc a 
					sla a 
					sla a 
					sla a 
					sla a 
				#if defined BOUNDING_BOX_8_BOTTOM || defined BOUNDING_BOX_8_CENTERED || defined BOUNDING_BOX_TINY_BOTTOM
					sub 4
				#elif defined BOUNDING_BOX_12X2_CENTERED
					sub 2
				#endif
					ld  (_gpx), a
			#endasm

			/*
			p_x = gpx << 6;
			wall_h = WLEFT;
			*/
			#asm
					ld  a, (_gpx)
					call Ashl16_HL
					ld  (_p_x), hl
					ld  a, WLEFT
					ld  (_wall_h), a
			#endasm
		}
		#ifndef DEACTIVATE_EVIL_TILE
			#ifndef CUSTOM_EVIL_TILE_CHECK
				else {
					// hit_h = ((at1 & 1) || (at2 & 1));
					#asm
							ld  a, (_at1)
							and 1
							ld  c, a
							ld  a, (_at2)
							and 1
							or  c 
							ld  (_hit_h), a
					#endasm
				}
			#endif
		#endif
	}

	#if defined (PLAYER_GENITAL)
		if (p_vx > 0)
	#else	
		if (p_vx + ptgmx > 0)
	#endif
	{
		cx1 = cx2 = ptx2; 
		cm_two_points ();

		if ((at1 & 8) || (at2 & 8)) {
			#include "my/ci/bg_collision/obstacle_right.h"

			#ifdef PLAYER_BOUNCE_WITH_WALLS
				p_vx = BOUNCE_EXPRESSION_X;
			#else
				p_vx = 0;
			#endif

			/*
			#if defined (BOUNDING_BOX_8_BOTTOM) || defined (BOUNDING_BOX_8_CENTERED) || defined (BOUNDING_BOX_TINY_BOTTOM)				
				gpx = (ptx1 << 4) + 4;
			#elif defined (BOUNDING_BOX_12X2_CENTERED)	
				gpx = (ptx1 << 4) + 2;
			#else
				gpx = (ptx1 << 4);
			#endif
			*/

			// KISS mod

			#asm
					ld  a, (_ptx1)
					sla a 
					sla a 
					sla a 
					sla a 
				#if defined BOUNDING_BOX_8_BOTTOM || defined BOUNDING_BOX_8_CENTERED || defined BOUNDING_BOX_TINY_BOTTOM
					add 4
				#elif defined BOUNDING_BOX_12X2_CENTERED
					add 2
				#endif
					ld  (_gpx), a
			#endasm


			/*		
			p_x = gpx << 6;
			wall_h = WRIGHT;
			*/
			#asm
					ld  a, (_gpx)
					call Ashl16_HL
					ld  (_p_x), hl
					ld  a, WRIGHT
					ld  (_wall_h), a
			#endasm
		}
		#ifndef DEACTIVATE_EVIL_TILE
			else {
				// hit_h = ((at1 & 1) || (at2 & 1));
				#asm
						ld  a, (_at1)
						and 1
						ld  c, a
						ld  a, (_at2)
						and 1
						or  c 
						ld  (_hit_h), a
				#endasm
			}
		#endif

	}

	// Priority to decide facing

	#ifdef PLAYER_GENITAL
		#ifdef TOP_OVER_SIDE
			/*
			if (p_facing_v != 0xff) {
				p_facing = p_facing_v;
			} else if (p_facing_h != 0xff) {
				p_facing = p_facing_h;
			}
			*/
			#asm
				.genital_decide_facing
					ld  a, (_p_facing_v)
					cp  0xff
					jr  z, genital_decide_facing_h
				.genital_decide_facing_v
					ld  (_p_facing), a
					jr  genital_decide_facing_done
				.genital_decide_facing_h
					ld  a, (_p_facing_h)
					cp  0xff
					jr  z, genital_decide_facing_done
					ld  (_p_facing), a
				.genital_decide_facing_done
			#endasm
		#else
			/*
			if (p_facing_h != 0xff) {
				p_facing = p_facing_h;
			} else if (p_facing_v != 0xff) {
				p_facing = p_facing_v;
			}
			*/
			#asm
				.genital_decide_facing
					ld  a, (_p_facing_h)
					cp  0xff
					jr  z, genital_decide_facing_v
				.genital_decide_facing_h
					ld  (_p_facing), a
					jr  genital_decide_facing_done
				.genital_decide_facing_v
					ld  a, (_p_facing_v)
					cp  0xff
					jr  z, genital_decide_facing_done
					ld  (_p_facing), a
				.genital_decide_facing_done
			#endasm	
		#endif	
	#endif

	/*
	cx1 = p_tx = (gpx + 8) >> 4;
	cy1 = p_ty = (gpy + 8) >> 4;

	rdb = attr (cx1, cy1);
	*/
	#asm
			ld  a, (_gpx)
			add 8
			srl a
			srl a
			srl a
			srl a
			ld  (_p_tx), a 
			ld  (_cx1), a
			ld  c, a

			ld  a, (_gpy)
			add 8
			srl a
			srl a
			srl a
			srl a
			ld  (_p_ty), a 
			ld  (_cy1), a

			call _attr_2
			ld  a, l
			ld  (_rdb), a
	#endasm

	// Special tiles
	if (rdb & 128) {
		#include "my/ci/on_special_tile.h"
	}

	#if defined (PLAYER_PUSH_BOXES) || !defined (DEACTIVATE_KEYS)
		#if defined PLAYER_GENITAL || defined LOCKS_CHECK_VERTICAL
			if (wall_v == WTOP) {
				// interact up			
				/*	
				#if defined (BOUNDING_BOX_8_BOTTOM) || defined (BOUNDING_BOX_12X2_CENTERED)
					cy1 = (gpy + 6) >> 4;
				#elif defined (BOUNDING_BOX_8_CENTERED)
					cy1 = (gpy + 3) >> 4;
				#else
					cy1 = (gpy - 1) >> 3;		
				#endif

				if (attr (cx1, cy1) == 10) {
					x0 = x1 = cx1; y0 = cy1; y1 = cy1 - 1;
					process_tile ();
				}
				*/

				// KISS mod

				#asm
						ld  a, (_gpy)
					#if defined (BOUNDING_BOX_8_BOTTOM) || defined (BOUNDING_BOX_12X2_CENTERED)
						add 6
					#elif defined (BOUNDING_BOX_8_CENTERED)
						add 3
					#else
						dec a 
					#endif
						srl a
						srl a
						srl a
						srl a
						ld  (_cy1), a
				
						ld  a, (_cx1)
						ld  c, a
						ld  a, (_cy1)
						call _attr_2 
						ld  a, l 
						cp  10
						jr  nz, p_int_up_no

						ld  a, (_cx1)
						ld  (_x0), a
						ld  (_x1), a
						ld  a, (_cy1)
						ld  (_y0), a 
						dec a 
						ld  (_y1), a 
						call _process_tile
					.p_int_up_no
				#endasm

			} else if (wall_v == WBOTTOM) {
				// interact down
				/*
				#if defined (BOUNDING_BOX_8_BOTTOM)
					cy1 = (gpy + 16) >> 4;
				#elif defined (BOUNDING_BOX_12X2_CENTERED)
					cy1 = (gpy + 9) >> 4;
				#elif defined (BOUNDING_BOX_8_CENTERED)
					cy1 = (gpy + 12) >> 4;
				#else
					cy1 = (gpy + 16) >> 4;				
				#endif		
			
				if (attr (cx1, cy1) == 10) {
					x0 = x1 = cx1; y0 = cy1; y1 = cy1 + 1;
					process_tile ();
				}
				*/

				// KISS mod
				#asm
						ld  a, (_gpy)
					#if defined (BOUNDING_BOX_12X2_CENTERED)
						add 9
					#elif defined (BOUNDING_BOX_8_CENTERED)
						add 12
					#else
						add 16
					#endif
						srl a
						srl a
						srl a
						srl a
						ld  (_cy1), a

						ld  a, (_cx1)
						ld  c, a
						ld  a, (_cy1)
						call _attr_2 
						ld  a, l 
						cp  10
						jr  nz, p_int_down_no

						ld  a, (_cx1)
						ld  (_x0), a
						ld  (_x1), a
						ld  a, (_cy1)
						ld  (_y0), a 
						inc a 
						ld  (_y1), a 
						call _process_tile		
					.p_int_down_no	
				#endasm
			} else
		#endif	
		
		if (wall_h == WLEFT) {		
			// interact left
			/*
			#if defined (BOUNDING_BOX_8_BOTTOM) || defined (BOUNDING_BOX_8_CENTERED)
				cx1 = (gpx + 3) >> 4;
			#elif defined (BOUNDING_BOX_12X2_CENTERED)
				cx1 = (gpx + 1) >> 4;
			#else
				cx1 = (gpx - 1) >> 4;		
			#endif		

			if (attr (cx1, cy1) == 10) {
				y0 = y1 = cy1; x0 = cx1; x1 = cx1 - 1;
				process_tile ();
			}
			*/

			// KISS mod
			#asm
					ld  a, (_gpx)
				#if defined (BOUNDING_BOX_8_BOTTOM) || defined (BOUNDING_BOX_8_CENTERED)
					add 3
				#elif defined (BOUNDING_BOX_12X2_CENTERED)
					inc a
				#else
					dec a
				#endif
					srl a
					srl a
					srl a
					srl a
					ld  (_cx1), a				

					// ld  a, (_cx1)
					ld  c, a
					ld  a, (_cy1)
					call _attr_2 
					ld  a, l 
					cp  10
					jr  nz, p_int_left_no
	
					ld  a, (_cy1)
					ld  (_y0), a
					ld  (_y1), a
					ld  a, (_cx1)
					ld  (_x0), a 
					dec a 
					ld  (_x1), a 
					call _process_tile
				.p_int_left_no
			#endasm
		} else if (wall_h == WRIGHT) {
			// interact right
			/*
			#if defined (BOUNDING_BOX_8_BOTTOM) || defined (BOUNDING_BOX_8_CENTERED)
				cx1 = (gpx + 12) >> 4;
			#elif defined (BOUNDING_BOX_12X2_CENTERED)
				cx1 = (gpx + 14) >>4;
			#else
				cx1 = (gpx + 16) >> 4;		
			#endif		
			if (attr (cx1, cy1) == 10) {
				y0 = y1 = cy1; x0 = cx1; x1 = cx1 + 1;
				process_tile ();
			}
			*/

			#asm
					ld  a, (_gpx)
				#if defined (BOUNDING_BOX_8_BOTTOM) || defined (BOUNDING_BOX_8_CENTERED)
					add 12
				#elif defined (BOUNDING_BOX_12X2_CENTERED)
					add 14
				#else
					add 16
				#endif
					srl a
					srl a
					srl a
					srl a
					ld  (_cx1), a				
					
					// ld  a, (_cx1)
					ld  c, a
					ld  a, (_cy1)
					call _attr_2 
					ld  a, l 
					cp  10
					jr  nz, p_int_right_no

					ld  a, (_cy1)
					ld  (_y0), a
					ld  (_y1), a
					ld  a, (_cx1)
					ld  (_x0), a 
					inc a 
					ld  (_x1), a 
					call _process_tile
				.p_int_right_no
			#endasm
		}
	#endif

	#ifdef PLAYER_CAN_FIRE
		// Disparos
		if (cpc_TestKey (KEY_BUTTON_A) && p_disparando == 0) {			
			p_disparando = 1;
			#ifdef FIRE_TO_PUSH	
				//if (pushed_any == 0)
			#endif
				bullets_fire ();
			#ifdef FIRE_TO_PUSH	
				//else pushed_any = 0;
			#endif
		}
		
		if (cpc_TestKey (KEY_BUTTON_A) == 0) 
			p_disparando = 0;

	#endif

	#ifndef DEACTIVATE_EVIL_TILE
		hit = 0;
		#ifdef CUSTOM_EVIL_TILE_CHECK
			#include "my/ci/custom_evil_tile_check.h"
		#else
		// Tiles que te matan. 
		// hit_v tiene preferencia sobre hit_h
		if (hit_v) {
			hit = 1;
			p_vy = addsign (-p_vy, PLAYER_MAX_VX);
		} else if (hit_h) {
			hit = 1;
			p_vx = addsign (-p_vx, PLAYER_MAX_VX);
		}
		#endif
		
		if (hit) {
			#ifdef PLAYER_FLICKERS
				if (p_estado == EST_NORMAL)
			#endif		
			{
				p_killme = SFX_SPIKES;
			}
		}
	#endif

	// Select animation frame 

	#ifdef PLAYER_CUSTOM_ANIMATION
		#include "my/custom_animation.h"
	#elif defined PLAYER_GENITAL
		
		if (p_vx || p_vy) {
			++ p_subframe;
			if (p_subframe == 4) {
				p_subframe = 0;
				p_frame = !p_frame;
			}
		}
				
		sp_sw [SP_PLAYER].sp0 = (int) (sm_sprptr [p_facing + p_frame]);
	#elif defined PLAYER_BOOTEE		
		gpit = p_facing << 2;
		if (p_vy < 0) {
			++ gpit; 
		} else {
			gpit += 2;
		}
		
		sp_sw [SP_PLAYER].sp0 = (int) (sm_sprptr [gpit]);
	#else
			
		if (!possee && !p_gotten) {			
			gpit = p_facing ? 3 : 7;
		} else {
			gpit = p_facing ? 0 : 4;
			if (p_vx == 0) {
				++ gpit;
			} else {
				rda = ((gpx + 4) >> 3) & 3;
				if (rda == 3) rda = 1;
				gpit += rda;
			}
			
		}
		
		sp_sw [SP_PLAYER].sp0 = (int) (sm_sprptr [gpit]);
	#endif

	/*
	#if defined PIXELPERFECT 
		#if CPC_GFX_MODE == 0
			sp_sw [SP_PLAYER].cx = (gpx + VIEWPORT_X*8 + sp_sw [SP_PLAYER].cox) >> 1;
		#elif CPC_GFX_MODE == 1
			sp_sw [SP_PLAYER].cx = (gpx + VIEWPORT_X*8 + sp_sw [SP_PLAYER].cox);
		#endif
	#else
		sp_sw [SP_PLAYER].cx = (gpx + VIEWPORT_X*8 + sp_sw [SP_PLAYER].cox) >> 2;
	#endif
	sp_sw [SP_PLAYER].cy = (gpy + VIEWPORT_Y*8 + sp_sw [SP_PLAYER].coy);

	if ( (p_estado & EST_PARP) && half_life ) sp_sw [SP_PLAYER].sp0 = (int) (SPRFR_EMPTY);
	*/
	#asm
		._player_spr_setup
			// We know SP_PLAYER is the first sprite. If you change it, recycle 
			// the original C code above, 'cause this assembly routine uses a couple
			// of shortcuts.

			// cx is offset 8, cox is offset 6
			// sp_sw [0].cx = (gpx + VIEWPORT_X*8 + sp_sw [SP_PLAYER].cox) >> MODE_SHIFT;

			ld  a, (_gpx)
			ld  c, a
			ld  a, (_sp_sw + 6)
			add VIEWPORT_X * 8
			add c

		#ifdef PIXELPERFECT
			#if CPC_GFX_MODE == 0
				// Shift right 1
					srl a
			#else
				// Leave as is
			#endif
		#else
			// Shift right 2
				srl a
				srl a
		#endif
			ld  (_sp_sw + 8), a		

			// cy is offset 9, coy is offset 7
			// sp_sw [rda].cy = (gpy + VIEWPORT_Y * 8 + sp_sw [rda].coy);

			ld  a, (_gpy)
			ld  c, a
			ld  a, (_sp_sw + 7)
			add VIEWPORT_Y * 8
			add c
			ld  (_sp_sw + 9), a

			// if ( (p_estado & EST_PARP) && half_life ) sp_sw [0].sp0 = _sprite_18_a;

			ld  a, (_p_estado)
			and EST_PARP
			jr  z, _player_spr_setup_done

			ld  a, (_half_life)
			or  a 
			jr  z, _player_spr_setup_done

			ld  hl, _sprite_18_a
			ld  (_sp_sw), hl

		._player_spr_setup_done
	#endasm
}

void player_deplete (void) {
	p_life = (p_life > p_kill_amt) ? p_life - p_kill_amt : 0;
}

void player_kill (unsigned char sound) {
	p_killme = 0;

	player_deplete ();

	AY_PLAY_SOUND (sound);
	
	#ifdef CP_RESET_WHEN_DYING
		#ifdef CP_RESET_ALSO_FLAGS
			mem_load ();
		#else
			n_pant = sg_pool [MAX_FLAGS];
			p_x = sg_pool [MAX_FLAGS + 1] << 10;
			p_y = sg_pool [MAX_FLAGS + 2] << 10;
		#endif	
		o_pant = 0xff; // Reload
	#endif

	#ifdef PLAYER_FLICKERS
		p_estado = EST_PARP;
		p_ct_estado = 50;
	#endif

	#ifdef DIE_AND_RESPAWN
		#asm
				ld  a, (_safe_n_pant)
				ld  (_n_pant), a 

				ld  a, (_safe_gpx)
				ld  (_gpx), a				
				call Ashl16_HL
				ld  (_p_x), hl

				ld  a, (_safe_gpy)
				ld  (_gpy), a
				call Ashl16_HL
				ld  (_p_y), hl

				ld  hl, 0
				ld  (_p_vx), hl 
				ld  (_p_vy), hl				
		#endasm
		#include "my/ci/on_player_respawned.h"
	#endif
}
