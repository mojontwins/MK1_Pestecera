// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// Autodefs

// ¡No tocar!

#if defined ENABLE_ORTHOSHOOTERS
	#define ENABLE_SIMPLE_COCOS
#endif

#ifndef MAX_BULLETS
	#define MAX_BULLETS 3
#endif

#ifdef SOUND_NONE
	#define AY_PLAY_SOUND(a) ;
	#define AY_STOP_SOUND()  ;
	#define AY_PLAY_MUSIC(a) ;
#elif defined (SOUND_WYZ)
	#define AY_PLAY_SOUND(a) ;
	#define AY_STOP_SOUND()  ;
	#define AY_PLAY_MUSIC(a) ;
#endif

// Configure number of blocks and reserve a pool for sprites

#define SP_PLAYER 			0
#define SP_ENEMS_BASE 		1

#ifdef PLAYER_CAN_FIRE
	#define SP_BULLETS_BASE 	SP_ENEMS_BASE + MAX_ENEMS
	#ifdef ENABLE_SIMPLE_COCOS
		#define MAX_PROJECTILES (MAX_BULLETS + MAX_ENEMS)
		#define SP_COCOS_BASE 	SP_BULLETS_BASE + MAX_BULLETS
	#else
		#define MAX_PROJECTILES MAX_BULLETS
	#endif
#else
	#ifdef ENABLE_SIMPLE_COCOS
		#define MAX_PROJECTILES MAX_ENEMS
		#define SP_COCOS_BASE 	SP_ENEMS_BASE + MAX_ENEMS
	#else
		#define MAX_PROJECTILES 0
	#endif
#endif

#define SW_SPRITES_ALL 4 + MAX_PROJECTILES
