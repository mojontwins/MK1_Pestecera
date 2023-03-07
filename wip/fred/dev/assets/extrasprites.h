// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// Extrasprites.h
// Contiene sprites extra para el modo de matar enemigos de la churrera
// S�lo se incluir� (tras los sprites) si se define PLAYER_STEPS_ON_ENEMIES
// Copyleft 2010 The Mojon Twins

// Frames extra por si se pueden eliminar los enemigos:

#if defined(PLAYER_CAN_FIRE) || defined(PLAYER_STEPS_ON_ENEMIES) || defined(ENABLE_PURSUERS) || defined (MODE_128K)
	extern unsigned char sprite_17_a []; 
#endif

extern unsigned char sprite_18_a []; 

#if defined(PLAYER_CAN_FIRE) || defined (MODE_128K) || defined ENABLE_SIMPLE_COCOS
	extern unsigned char sprite_19_a [];
	extern unsigned char sprite_19_b [];
#endif

#if defined(PLAYER_CAN_FIRE) || defined(PLAYER_STEPS_ON_ENEMIES) || defined(ENABLE_PURSUERS) || defined (MODE_128K)
	#asm
		._sprite_17_a
			BINARY "../bin/sprites_extra.bin"
	#endasm
#endif

#asm
	._sprite_18_a
		defs 96, 0
#endasm

#if defined(PLAYER_CAN_FIRE) || defined (MODE_128K) || defined ENABLE_SIMPLE_COCOS
	#asm
		._sprite_19_a
			BINARY "../bin/sprites_bullet.bin"
	#endasm
#endif

#define SPRFR_EXPL  sprite_17_a
#define SPRFR_EMPTY sprite_18_a
