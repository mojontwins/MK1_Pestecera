// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

#define PLAYER_CONSTANT_VX 			128
#define PLAYER_CONSTANT_VY 			128
#define PLAYER_CONSTANT_JUMP_VY		256

#define DIRECTION_LEFT 				1
#define DIRECTION_RIGHT 			2

// Custom animation

unsigned char custom_animation [] = {
	// Looking right (offset 0)
	0, 1, 2, 3, 4,
	// Looking left (offset 5)
	5, 6, 7, 16, 17
};

// Drop animation

extern void *drop_animation [0];
#asm
	._drop_animation
		defw _sprites + 0x0480, _sprites + 0x04C0, _sprites + 0x0500, _sprites + 0x0540
#endasm


// Rope

unsigned char p_on_rope = 0;
unsigned char p_jump_pressed;
unsigned char p_left_right; 
unsigned char p_tile_rope, p_rope_ready;

// Phantoms

#define PHANTOM_V					2
signed char dx [] = { 0, PHANTOM_V, 0, -PHANTOM_V };
signed char dy [] = { -PHANTOM_V, 0, PHANTOM_V, 0 };
unsigned char en_ph_ctr [3];

// Rather simple shoot

unsigned char shoot_x, shoot_y, shoot_mx;
//struct sp_SS *sp_shoot;

// Import explosion sprite graphic
extern unsigned char sprite_17_a [0];
#asm
	._sprite_17_a
		BINARY "../bin/sprites_extra.bin"
#endasm

// Import shoot sprite graphic
extern unsigned char sprite_19_a [0];
#asm
	._sprite_19_a
		BINARY "../bin/sprites_bullet.bin"
#endasm
