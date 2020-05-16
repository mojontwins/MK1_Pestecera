// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// Autodefs

// ¡No tocar!

#if defined ENABLE_ORTHOSHOOTERS
	#define ENABLE_SIMPLE_COCOS
#endif

#ifdef SOUND_NONE
	#define AY_PLAY_SOUND(a) ;
	#define AY_STOP_SOUND()  ;
	#define AY_PLAY_MUSIC(a) ;
#elif defined (SOUND_WYZ)
	#define AY_PLAY_SOUND(a) cpc_WyzStartEffect (1, a);
	#define AY_STOP_SOUND()  cpc_WyzSetPlayerOff ();
	#define AY_PLAY_MUSIC(a) wyz_play_compressed_song(a);
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

#define SW_SPRITES_ALL 		1 + MAX_ENEMS + MAX_BULLETS + MAX_COCOS

#define SP_PLAYER 			0
#define SP_ENEMS_BASE 		1
#define SP_BULLETS_BASE 	SP_ENEMS_BASE + MAX_ENEMS
#define SP_COCOS_BASE 		SP_BULLETS_BASE + MAX_BULLETS
