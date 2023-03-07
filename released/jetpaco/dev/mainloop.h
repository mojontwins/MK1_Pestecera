// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// mainloop.h
// Churrera copyleft 2011 by The Mojon Twins.

void main (void) {

	// CPC initialization
	
	AY_INIT ();

	#asm
		di

		ld  hl, 0xC000
		xor a
		ld  (hl), a
		ld  de, 0xC001
		ld  bc, 0x3DFF
		ldir

		ld  a, 195
		ld  (0x38), a
		ld  hl, _isr
		ld  (0x39), hl
		jp  isr_done

	._isr
		push af 
		
		ld  a, (isr_c1)
		inc a
		cp  6
		jr  c, _skip_player

		ld  a, (isr_c2)
		inc a
		ld  (isr_c2), a
		
		#ifdef SOUND_WYZ
			ld  a, (_isr_player_on)
			or  a
			jr  z, _skip_player

			push hl
			push de
			push bc
			push ix
			push iy

			call WYZ_PLAYER_ISR

			pop iy
			pop ix
			pop bc
			pop de 
			pop hl
	#endif

			xor a

	._skip_player
			ld  (isr_c1), a	
		
		pop af
		ei
		ret

	.isr_c1 
		defb 0
	.isr_c2
		defb 0

	.isr_done
	#endasm
	
	// Border 0

	#asm
		ld 	a, 0x54
		ld  bc, 0x7F11
		out (c), c
		out (c), a
	#endasm

	#ifndef OR_SPRITES
		// Decompress LUT in place

		unpack ((unsigned int) (trpixlutc), BASE_LUT);
	#endif

	blackout ();
	
	pal_set (my_inks);
	
	// Set mode

	cpc_SetMode (CPC_GFX_MODE);

	// Set tweaked mode 
	// (thanks Augusto Ruiz for the code & explanations!)
	
	#asm
		; Horizontal chars (32), CRTC REG #1
		ld    b, 0xbc
		ld    c, 1			; REG = 1
		out   (c), c
		inc   b
		ld    c, 32			; VALUE = 32
		out   (c), c

		; Horizontal pos (42), CRTC REG #2
		ld    b, 0xbc
		ld    c, 2			; REG = 2
		out   (c), c
		inc   b
		ld    c, 42			; VALUE = 42
		out   (c), c

		; Vertical chars (24), CRTC REG #6
		ld    b, 0xbc
		ld    c, 6			; REG = 6
		out   (c), c
		inc   b
		ld    c, 24			; VALUE = 24
		out   (c), c
	#endasm

	// Sprite creation

	// Player 

	sp_sw [SP_PLAYER].cox = sm_cox [0];
	sp_sw [SP_PLAYER].coy = sm_coy [0];
	sp_sw [SP_PLAYER].invfunc = sm_invfunc [0];
	sp_sw [SP_PLAYER].updfunc = sm_updfunc [0];
	sp_sw [SP_PLAYER].sp0 = sp_sw [SP_PLAYER].sp1 = (unsigned int) (sm_sprptr [0]);

	// Enemies 

	for (gpit = SP_ENEMS_BASE; gpit < SP_ENEMS_BASE + MAX_ENEMS; gpit ++) {
		sp_sw [gpit].invfunc = cpc_PutSpTileMap4x8;
		sp_sw [gpit].updfunc = cpc_PutTrSp4x8TileMap2b;
	}

	// Bullets are 4x8

	#ifdef PLAYER_CAN_FIRE
		for (gpit = SP_BULLETS_BASE; gpit < SP_BULLETS_BASE + MAX_BULLETS; gpit ++) {
			sp_sw [gpit].cox = 0;
			sp_sw [gpit].coy = 0;
			sp_sw [gpit].invfunc =cpc_PutSpTileMap4x8;
			sp_sw [gpit].updfunc = cpc_PutTrSp4x8TileMap2b;
			sp_sw [gpit].sp0 = sp_sw [SP_PLAYER].sp1 = (unsigned int) (sprite_19_a);
		}
	#endif

	// Cocos are 4x8

	#ifdef ENABLE_SIMPLE_COCOS
		for (gpit = SP_COCOS_BASE; gpit < SP_COCOS_BASE + MAX_ENEMS; gpit ++) {
			sp_sw [gpit].cox = 0;
			sp_sw [gpit].coy = 0;
			sp_sw [gpit].invfunc =cpc_PutSpTileMap4x8;
			sp_sw [gpit].updfunc = cpc_PutTrSp4x8TileMap2b;
			sp_sw [gpit].sp0 = sp_sw [SP_PLAYER].sp1 = (unsigned int) (sprite_19_a);
		}
	#endif

	// Turn off all sprites
	for (gpit = 0; gpit < SW_SPRITES_ALL; ++ gpit) {
		spr_on [gpit] = 0;
		sp_sw [gpit].ox = (VIEWPORT_X*8) >> 2;
		sp_sw [gpit].oy = VIEWPORT_Y*8;
	}

	#include "my/ci/after_load.h"

	#asm
		ei
	#endasm

	while (1) {
		#ifdef ACTIVATE_SCRIPTING
			main_script_offset = (int) (main_script);
		#endif

		level = 0;

		// Here the title screen		
	
		title_screen ();
		
		#ifdef ENABLE_CHECKPOINTS
			sg_submenu ();
		#endif

		#include "my/ci/before_game.h"

		#ifdef COMPRESSED_LEVELS
			#ifdef ENABLE_CHECKPOINTS
				if (sg_do_load) level = sg_level; else level = 0;
			#endif

			#ifndef REFILL_ME
				p_life = PLAYER_LIFE;
			#endif

			#ifdef ACTIVATE_SCRIPTING
				script_result = 0;
			#else
				warp_to_level = 0;
			#endif

			while (1) 
		#endif
		
		{
			#ifdef COMPRESSED_LEVELS
				#include "my/level_screen.h"
			
				prepare_level ();			
			#endif
					
			#ifndef DIRECT_TO_PLAY
				
				#ifdef MODE_128K
					// Resource 1 = marco.bin
					get_resource (MARCO_BIN, BASE_SUPERBUFF);
				#else		
					unpack ((unsigned int) (s_marco), BASE_SUPERBUFF);				
				#endif
				cpc_ShowTileMap (1);						

			#endif

			// Let's do it.
			#include "mainloop/game_loop.h"

			#ifdef COMPRESSED_LEVELS
				if (success) {
					
					zone_clear ();

					#ifdef ACTIVATE_SCRIPTING
						if (script_result != 3)
					#else
						if (warp_to_level == 0)
					#endif
					++ level;
					
					if (level >= MAX_LEVELS 
						#ifdef ACTIVATE_SCRIPTING
							|| script_result == 4
						#endif
					) {
						game_ending ();
						break;
					}
				} else {
					#if defined(TIMER_ENABLE) && defined(TIMER_GAMEOVER_0) && defined(SHOW_TIMER_OVER)
						if (timer_zero) time_over (); else game_over ();
					#else
						game_over ();
					#endif
					#include "my/ci/after_game_over.h"
					
					AY_STOP_SOUND ();
					break;
				}
			#else
				if (success) {
					game_ending (); 
				} else {
					game_over ();
					#include "my/ci/after_game_over.h"
				}
			#endif
		}
		
		clear_sprites ();

		#include "my/ci/after_game.h"
	}
}
