// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// Autodefs

// ¡No tocar!

#asm
		defc viewport_x = VIEWPORT_X
		defc viewport_y = VIEWPORT_Y
		XDEF viewport_x
		XDEF viewport_y
#endasm

#if defined ENABLE_ORTHOSHOOTERS
	#define ENABLE_SIMPLE_COCOS
#endif

#ifdef SOUND_NONE
	#define AY_INIT()        ;
	#define AY_PLAY_SOUND(a) ;
	#define AY_STOP_SOUND()  ;
	#define AY_PLAY_MUSIC(a) ;
#elif defined SOUND_WYZ
	#define AY_INIT()        wyz_init ();
	#define AY_PLAY_SOUND(a) wyz_play_sound (a);
	#define AY_STOP_SOUND()  wyz_stop_sound ();
	#define AY_PLAY_MUSIC(a) wyz_play_music (a);
#endif

// Configure number of blocks and reserve a pool for sprites

#ifndef PLAYER_CAN_FIRE
	#ifdef MAX_BULLETS
		#undef MAX_BULLETS
	#endif
	#define MAX_BULLETS 0
#endif

#ifdef ENABLE_SIMPLE_COCOS
	#define MAX_COCOS MAX_ENEMS
#else
	#define MAX_COCOS 0
#endif

#define SW_SPRITES_ALL 		1 + MAX_ENEMS + MAX_BULLETS + MAX_COCOS + EXTRA_SPRITES

#define SP_PLAYER 			0
#define SP_ENEMS_BASE 		1
#define SP_BULLETS_BASE 	SP_ENEMS_BASE + MAX_ENEMS
#define SP_COCOS_BASE 		SP_BULLETS_BASE + MAX_BULLETS
#define SP_EXTRA_BASE 		SP_COCOS_BASE + MAX_COCOS

// Automagically calculate this byte
#if CPC_GFX_MODE == 0
	// PIXEL 0  PIXEL 1
	// 3 2 1 0  3 2 1 0
	// 1 5 3 7  0 4 2 6
	#define BLACK_COLOUR_BYTE ((BLACK_PEN>>3)&1)|(((BLACK_PEN>>3)&1)<<1)\
								|(((BLACK_PEN>>1)&1)<<2)|(((BLACK_PEN>>1)&1)<<3)\
								|(((BLACK_PEN>>2)&1)<<4)|(((BLACK_PEN>>2)&1)<<5)\
								|((BLACK_PEN&1)<<6)|((BLACK_PEN&1)<<7)
#else
	// P_0 P_1 P_2 P_3
	// 1 0 1 0 1 0 1 0
	// 3 7 2 6 1 5 0 4
	#define BLACK_COLOUR_BYTE (BLACK_PEN>>1)|((BLACK_PEN>>1)<<1)\
								|((BLACK_PEN>>1)<<2)|((BLACK_PEN>>1)<<3)\
								|((BLACK_PEN&1)<<4)|((BLACK_PEN&1)<<5)\
								|((BLACK_PEN&1)<<6)|((BLACK_PEN&1)<<7)
#endif

