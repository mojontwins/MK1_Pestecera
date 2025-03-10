// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

#asm
	.vpClipStruct defb VIEWPORT_Y, VIEWPORT_Y + 20, VIEWPORT_X, VIEWPORT_X + 30
	.fsClipStruct defb 0, 24, 0, 32
#endasm	

unsigned char pad0;
#ifdef USE_TWO_BUTTONS
	unsigned char isJoy;
#endif

#define KEY_M 0x047f
#define KEY_H 0x10bf
#define KEY_Y 0x10df
#define KEY_Z 0x02fe

// Safe stuff in non paged RAM

unsigned char safe_byte @ 0xC7FF;

// Globales muy globalizadas

#define KEY_LEFT 		0
#define KEY_RIGHT		1
#define KEY_UP  		2
#define KEY_DOWN 		3
#define KEY_BUTTON_A	4
#define KEY_BUTTON_B	5
#define KEY_ENTER		6
#define KEY_ESC			7
#define KEY_AUX1		8
#define KEY_AUX2		9
#define KEY_AUX3 		10
#define KEY_AUX4 		11

typedef struct sprite {
	unsigned int sp0;			// 0
	unsigned int sp1; 			// 2
	unsigned int coord0;
	signed char cox, coy;		// 6 7
	unsigned char cx, cy; 		// 8 9
	unsigned char ox, oy;		// 10 11
	void *invfunc;				// 12
	void *updfunc;				// 14
} SPR;

SPR sp_sw [SW_SPRITES_ALL] 					@ BASE_SPRITES;
unsigned char *spr_next [SW_SPRITES_ALL] 	@ BASE_SPRITES + (SW_SPRITES_ALL)*16;
unsigned char spr_on [SW_SPRITES_ALL]		@ BASE_SPRITES + (SW_SPRITES_ALL)*18;
unsigned char spr_x [SW_SPRITES_ALL]		@ BASE_SPRITES + (SW_SPRITES_ALL)*19;
unsigned char spr_y [SW_SPRITES_ALL]		@ BASE_SPRITES + (SW_SPRITES_ALL)*20;

unsigned char enoffs;

// Aux

char asm_number;
unsigned int asm_int;
unsigned int asm_int_2;
unsigned int seed;
unsigned char half_life;

#define EST_NORMAL 			0
#define EST_PARP 			2
#define EST_MUR 			4
#define sgni(n)				(n < 0 ? -1 : 1)
#define saturate(n)			(n < 0 ? 0 : n)
#define WTOP 				1
#define WBOTTOM 			2
#define WLEFT 				3
#define WRIGHT 				4
#define COORDS(x,y)			((x)+(y<<4)-(y))

// Vertical engine selector 
// for advanced masters of the universe
// with a picha or toto very gordo

#define VENG_KEYS			1
#define VENG_JUMP 			2
#define VENG_BOOTEE			3
#define VENG_JETPAC 		4

#define TYPE_6_IDLE 		0
#define TYPE_6_PURSUING		1
#define TYPE_6_RETREATING	2
#define GENERAL_DYING 		4

#define FACING_RIGHT 		0
#define FACING_LEFT			2
#define FACING_UP 			4
#define FACING_DOWN 		6

#ifdef VENG_SELECTOR 
	unsigned char veng_selector;
#endif

// player
signed int p_x, p_y;
signed int p_vx, p_vy;
unsigned char p_saltando, p_cont_salto;
unsigned char p_frame, p_subframe, p_facing;
unsigned char p_estado;
unsigned char p_ct_estado;
unsigned char p_gotten, pregotten;
unsigned char p_life, p_objs, p_keys;
unsigned char p_fuel;
unsigned char p_killed;
unsigned char p_disparando;
unsigned char p_facing_v, p_facing_h;
unsigned char p_ammo;
unsigned char p_killme;
unsigned char p_kill_amt;
unsigned char p_tx, p_ty;
#ifdef PLAYER_HAS_JETPAC
	unsigned char p_jetpac_on;
#endif
signed int ptgmx, ptgmy;

const unsigned char *spacer = "            ";

unsigned char enit, enspit;

// Locate those arrays @ BASE_ARRAYS
unsigned char en_an_base_frame [MAX_ENEMS]		@ BASE_ARRAYS;
unsigned char en_an_frame [MAX_ENEMS] 			@ BASE_ARRAYS + MAX_ENEMS;
unsigned char en_an_count [MAX_ENEMS]			@ BASE_ARRAYS + MAX_ENEMS * 2;
unsigned char en_an_sprid [MAX_ENEMS] 			@ BASE_ARRAYS + MAX_ENEMS * 3;
unsigned char en_an_state [MAX_ENEMS] 			@ BASE_ARRAYS + MAX_ENEMS * 4;
signed int    en_an_x [MAX_ENEMS]				@ BASE_ARRAYS + MAX_ENEMS * 5;
signed int    en_an_y [MAX_ENEMS] 				@ BASE_ARRAYS + MAX_ENEMS * 7;			
signed int    en_an_vx [MAX_ENEMS]				@ BASE_ARRAYS + MAX_ENEMS * 9;
signed int    en_an_vy [MAX_ENEMS]				@ BASE_ARRAYS + MAX_ENEMS * 11;
unsigned char en_an_alive [MAX_ENEMS] 			@ BASE_ARRAYS + MAX_ENEMS * 13;
unsigned char en_an_dead_row [MAX_ENEMS] 		@ BASE_ARRAYS + MAX_ENEMS * 14;
unsigned char en_an_rawv [MAX_ENEMS]			@ BASE_ARRAYS + MAX_ENEMS * 15;
unsigned char cocos_x [MAX_ENEMS]				@ BASE_ARRAYS + MAX_ENEMS * 16;
unsigned char cocos_y [MAX_ENEMS]				@ BASE_ARRAYS + MAX_ENEMS * 17;
signed char   cocos_mx [MAX_ENEMS]				@ BASE_ARRAYS + MAX_ENEMS * 18;
signed char   cocos_my [MAX_ENEMS]				@ BASE_ARRAYS + MAX_ENEMS * 19;
unsigned char *en_an_next_frame [MAX_ENEMS] 	@ BASE_ARRAYS + MAX_ENEMS * 20;
#if MAX_BULLETS > 0
	unsigned char bullets_x [MAX_BULLETS]			@ BASE_ARRAYS + MAX_ENEMS * 22;
	unsigned char bullets_y [MAX_BULLETS] 			@ BASE_ARRAYS + MAX_ENEMS * 22 + MAX_BULLETS;
	signed char   bullets_mx [MAX_BULLETS]			@ BASE_ARRAYS + MAX_ENEMS * 22 + MAX_BULLETS * 2;
	signed char   bullets_my [MAX_BULLETS]			@ BASE_ARRAYS + MAX_ENEMS * 22 + MAX_BULLETS * 3;
	unsigned char bullets_estado [MAX_BULLETS]		@ BASE_ARRAYS + MAX_ENEMS * 22 + MAX_BULLETS * 4;
	unsigned char bullets_life [MAX_BULLETS]		@ BASE_ARRAYS + MAX_ENEMS * 22 + MAX_BULLETS * 5;
#endif

#ifdef PLAYER_CAN_FIRE
	unsigned char _b_estado;
	unsigned char b_it, bspr_it, _b_x, _b_y;
	signed char _b_mx, _b_my;
#endif

#if defined (ENABLE_FANTIES)
	signed int _en_an_x, _en_an_y, _en_an_vx, _en_an_vy;
#endif

unsigned char _en_x, _en_y;
unsigned char _en_x1, _en_y1, _en_x2, _en_y2;
signed char _en_mx, _en_my;
signed char _en_t;
signed char _en_life;

unsigned char *_baddies_pointer;

#if defined PLAYER_CAN_FIRE || defined ENABLE_PURSUERS
	unsigned char _en_cx, _en_cy;
#endif


// atributos de la pantalla: Contiene informaci�n
// sobre qu� tipo de tile hay en cada casilla
unsigned char map_attr [150]					@ BASE_ROOM_BUFFERS;
unsigned char map_buff [150]					@ BASE_ROOM_BUFFERS + 150;
// Breakable walls/etc
#ifdef BREAKABLE_WALLS
	unsigned char brk_buff [150] 				@ BASE_ROOM_BUFFERS + 300;
#endif

// posici�n del objeto (hotspot). Para no objeto,
// se colocan a 240,240, que est� siempre fuera de pantalla.
unsigned char hotspot_x;
unsigned char hotspot_y;
unsigned char hotspot_destroy;
unsigned char orig_tile;	// Tile que hab�a originalmente bajo el objeto

// Flags para scripting
#ifndef MAX_FLAGS
	#define MAX_FLAGS 16
#endif
unsigned char flags[MAX_FLAGS];

// Globalized
unsigned char o_pant;
unsigned char n_pant;
unsigned char is_rendering;
unsigned char level, slevel;
#ifndef ACTIVATE_SCRIPTING
	unsigned char warp_to_level = 0;
#endif
unsigned char maincounter;

// Fire zone
#ifdef ENABLE_FIRE_ZONE
	unsigned char fzx1, fzy1, fzx2, fzy2, f_zone_ac;
#endif

// Timer
#ifdef TIMER_ENABLE
	unsigned char timer_on;
	unsigned char timer_t;
	unsigned char timer_frames;
	unsigned char timer_count;
	unsigned char timer_zero;
#endif

#if defined(ACTIVATE_SCRIPTING) && defined(ENABLE_PUSHED_SCRIPTING)
	unsigned char just_pushed;
#endif

// Engine globals (for speed) & size!

unsigned char gpx, gpox, gpy, gpd, gpc, gpt;
unsigned char gpxx, gpyy, gpcx, gpcy;
unsigned char possee, hit_v, hit_h, hit, wall_h, wall_v;
unsigned char gpen_x, gpen_y, gpen_cx, gpen_cy, gpaux;
unsigned char tocado, active;
unsigned char gpit, gpjt;
unsigned char enoffsmasi;
unsigned char *map_pointer;
#ifdef PLAYER_CAN_FIRE
	unsigned char blx, bly;
#endif
unsigned char rdx, rdy, rda, rdb, rdc, rdd, rdn, rdt;

// More stuff

#ifdef MSC_MAXITEMS
	unsigned char key_z_pressed = 0;
#endif

int itj;
unsigned char objs_old, keys_old, life_old, killed_old;

#ifdef MAX_AMMO
	unsigned char ammo_old;
#endif

#if defined TIMER_ENABLE && TIMER_X != 99
	unsigned char timer_old;
#endif

#ifdef COMPRESSED_LEVELS
	unsigned char *level_str = "LEVEL 0X";
#endif

#ifdef GET_X_MORE
	unsigned char *getxmore = " GET X MORE ";
#endif

unsigned char *gen_pt;
unsigned char playing;

unsigned char success;
#ifdef PLAYER_CHECK_MAP_BOUNDARIES
	unsigned char x_pant, y_pant;
#endif

unsigned char _x, _y, _n, _t;
unsigned char cx1, cy1, cx2, cy2, at1, at2;
unsigned char x0, y0, x1, y1;
unsigned char ptx1, pty1, ptx2, pty2;
unsigned char *_gp_gen;

#ifdef ENABLE_TILANIMS
	unsigned char tait;
	unsigned char max_tilanims;
	unsigned char tacount;
	unsigned char tilanims_xy [MAX_TILANIMS];
	unsigned char tilanims_ft [MAX_TILANIMS];
#endif

#if defined USE_AUTO_TILE_SHADOWS || defined USE_AUTO_SHADOWS || defined ENABLE_TILANIMS
	unsigned char xx, yy;
#endif

#if defined USE_AUTO_TILE_SHADOWS || defined USE_AUTO_SHADOWS
	unsigned char c1, c2, c3, c4;
	unsigned char t1, t2, t3, t4;
	unsigned char nocast, _ta;
#endif

#ifdef USE_AUTO_TILE_SHADOWS
	unsigned a1, a2, a3;
	unsigned char *gen_pt_alt;
	unsigned char t_alt;
#endif

#if defined ENABLE_SIMPLE_COCOS
	// UP RIGHT DOWN LEFT
	const signed char _dx [] = { 0, COCOS_V, 0, -COCOS_V };
	const signed char _dy [] = { -COCOS_V, 0, COCOS_V, 0 };
#endif

#ifdef MODE_128K
	unsigned char song_playing = 0;
#endif

unsigned char def_keys_joy [] = {
	0x4904, 0x4908, 0x4901, 0x4902, 0x4920, 0x4910,
	0x4004, 0x4804, 0x4880, 0x4780, 0x4801, 0x4802
};

unsigned char isr_player_on;
