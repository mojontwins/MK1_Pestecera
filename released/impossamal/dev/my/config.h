// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// Config.h

// ============================================================================
// I. General configuration
// ============================================================================

#define USE_ZX0							// Einar Sauka's ZX0 rather than ol' aplib

//#define SOUND_NONE
#define SOUND_WYZ
#define WYZ_FX_CHANNEL 				1		// Where to play sound effects

// Music indexes, comment if not applicable
#define MUSIC_TITLE 				0
#define MUSIC_INGAME 				1
//#define MUSIC_GOVER 				2
//#define MUSIC_ENDING 				3
//#define MUSIC_SCLEAR 				4

//#define VENG_SELECTOR 					// Very advanced!
//#define USE_MAP_CUSTOM_DECODER
#define GENERAL_ENEMS_BASE_CELL 	8 		// Don't touch this unless you know what you are doing
//#define MIN_FAPS_PER_FRAME 		2		// frame cap, *limits* to 50/N fps.

#define BLACK_PEN 					1		// Which palette entry is black

#define PIXELPERFECT 						// If you use mode 0, don't forget the pixelperfectm0
											// parameter to mkts when converting the main spriteset

//#define OR_SPRITES 						// This removes the compressed LUT from the binary
											// and saves some bytes if you are using GnG M0 mode

#define EXTRA_SPRITES 				0 		// If you want to add extra software sprite entities, 
											// add them there. Your sprites will be defined as
											// sp_sw [SP_EXTRA_BASE] onwards.

// In this section we define map dimensions, initial and authomatic ending conditions, etc.

#define MAP_W						25		//
#define MAP_H						1		// Map dimensions in screens
#define SCR_INICIO					0		// Initial screen
#define PLAYER_INI_X				1		//
#define PLAYER_INI_Y				5		// Initial tile coordinates
//#define SCR_FIN 					99		// Last screen. 99 = deactivated.
//#define PLAYER_FIN_X				99		//
//#define PLAYER_FIN_Y				99		// Player tile coordinates to finish game
//#define PLAYER_NUM_OBJETOS			25		// Objects to get to finish game
#define PLAYER_LIFE 				10		// Max and starting life gauge.
#define PLAYER_REFILL				2		// Life recharge
//#define PLAYER_DONT_LIMIT_LIFE				// PLAYER_LIFE isn't max.
//#define COMPRESSED_LEVELS 				// use levels.h instead of mapa.h and enems.h (!)
//#define PER_LEVEL_SPRITESET 				// use a different spriteset for each level in 48K
//#define PER_LEVEL_TILESET 				// use a different tileset for each level
//#define MAX_LEVELS				4		// # of compressed levels
//#define REFILL_ME 						// If defined, refill player on each level

// ============================================================================
// II. Engine type
// ============================================================================

// This section is used to define the game engine behaviour. Many directives are related,
// and others are mutually exclusive. I think this will be pretty obvious when you look at them. 

// Right now the shooting engine is only compatible with the side-view engine.

// Bounding box size
// -----------------
											// Comment both for normal 16x16 bounding box
#define BOUNDING_BOX_8_BOTTOM				// 8x8 aligned to bottom center in 16x16
//#define BOUNDING_BOX_8_CENTERED			// 8x8 aligned to center in 16x16
//#define BOUNDING_BOX_12X2_CENTERED 		// 8x2 aligned to center in 16x16
#define SMALL_COLLISION 					// 8x8 centered collision instead of 12x12

// General directives:
// -------------------

//#define PLAYER_CHECK_MAP_BOUNDARIES		// If defined, you can't exit the map.
#define DIRECT_TO_PLAY					// If defined, title screen is also the game frame.
//#define DEACTIVATE_KEYS 					// If defined, keys are not present.
//#define DEACTIVATE_OBJECTS				// If defined, objects are not present.
//#define DEACTIVATE_REFILLS				// If defined, life refills are not present.
//#define ONLY_ONE_OBJECT					// If defined, only one object can be carried at a time.
#define OBJECT_COUNT				1		// Defines which FLAG will be used to store the object count.
#define REVERSE_OBJECTS_COUNT 			// Counts from PLAYER_NUM_OBJETOS to 0
//#define DEACTIVATE_EVIL_TILE				// If defined, no killing tiles (behaviour 1) are detected.
//#define CUSTOM_EVIL_TILE_CHECK			// 
//#define PLAYER_BOUNCES						// If defined, collisions make player bounce
//#define FULL_BOUNCE 						// If defined, evil tile bounces equal MAX_VX, otherwise v/2
//#define SLOW_DRAIN						// Works with bounces. Drain is 4 times slower
//#define PLAYER_FLICKERS 					// If defined, collisions make player flicker instead.
//#define MAP_BOTTOM_KILLS					// If defined, exiting the map bottomwise kills.
#define WALLS_STOP_ENEMIES					// If defined, enemies react to the scenary
//#define EVERYTHING_IS_A_WALL				// If defined, any tile <> type 0 is a wall, otherwise just 8.
//#define BODY_COUNT_ON 			2		// If defined, count enemies on flag #
//#define DISABLE_PLATFORMS 				// Disables platforms in side-view
//#define CUSTOM_LOCK_CLEAR 				// use `custom_lock_clear.h` to remove a lock from screen

#define DIE_AND_RESPAWN 					// Remember last safe spot & respawn there
#define SAFE_SPOT_ON_ENTERING 			// Comment to have safe spot on landing instead

// Extra enemy types
// -----------------

//#define ENABLE_PURSUERS					// If defined, type 7 enemies are active
//#define DEATH_COUNT_AND 			7
//#define DEATH_COUNT_ADD 			11 		// Frames to wait = ADD + (rand & AND)
//#define PURSUERS_MAX_V 			4		// 1, 2, 4.
//#define PURSUERS_BASE_CELL		3		// If defined, type 7 enemies are always #
//#define PURSUERS_DONT_SPAWN_IN_OBSTACLE 	// Move an obstacle to stop spawning

//#define ENABLE_FANTIES					// If defined, Fanties are enabled!
//#define FANTIES_BASE_CELL 		2		// Base sprite cell (0, 1, 2 or 3)
//#define FANTIES_SIGHT_DISTANCE	64 		// Used in our type 6 enemies.
//#define FANTIES_MAX_V 			256 	// Flying enemies max speed (also for custom type 6 if you want)
//#define FANTIES_A 				16		// Flying enemies acceleration.
//#define FANTIES_LIFE_GAUGE		10		// Amount of shots needed to kill flying enemies.
//#define FANTIES_TYPE_HOMING				// Unset for simple fanties.

//#define ENABLE_ORTHOSHOOTERS				// If defined, orthoshooters are active
//#define ORTHOSHOOTERS_FREQ 		(rand()&15)
//#define ORTHOSHOOTERS_BASE_CELL 	0 		// 99 means DONT SHOW!

// Cocos
// -----

//#define COCOS_V 					8		// pixels per frame

// Pushable tile
// -------------

//#define PLAYER_PUSH_BOXES					// If defined, tile #14 is pushable. Must be type 10.
//#define FIRE_TO_PUSH						// If defined, you have to press FIRE+direction to push.
//#define ENABLE_PUSHED_SCRIPTING			// If defined, nice goodies (below) are activated:
//#define MOVED_TILE_FLAG			1		// Current tile "overwritten" with block is stored here.
//#define MOVED_X_FLAG				2		// X after pushing is stored here.
//#define MOVED_Y_FLAG				3		// Y after pushing is stored here.
//#define PUSHING_ACTION					// If defined, pushing a tile runs PRESS_FIRE script

// Shooting behaviour
// ------------------

//#define PLAYER_CAN_FIRE 					// If defined, shooting engine is enabled.
//#define PLAYER_CAN_FIRE_FLAG		1		// If defined, player can only fire when flag # is 1
//#define PLAYER_BULLET_SPEED 		8		// Pixels/frame. 
//#define MAX_BULLETS 				3		// Max number of bullets on screen. Be careful!.
//#define PLAYER_BULLET_Y_OFFSET	6		// vertical offset from the player's top.
//#define PLAYER_BULLET_X_OFFSET	0		// vertical offset from the player's left/right.
//#define ENEMIES_LIFE_GAUGE		4		// Amount of shots needed to kill enemies.
//#define LIMITED_BULLETS 					// If defined, bullets die after N frames
//#define LB_FRAMES 				4		// If defined, defines the # of frames bullets live (fixed)
//#define LB_FRAMES_FLAG			2		// If defined, defines which flag determines the # of frames

//#define RESPAWN_ON_ENTER					// Enemies respawn when entering screen
//#define FIRE_MIN_KILLABLE			3		// If defined, only enemies >= N can be killed.
//#define CAN_FIRE_UP 						// If defined, player can fire upwards and diagonal.
//#define MAX_AMMO					99		// If defined, ammo is not infinite!
//#define AMMO_REFILL 				50		// ammo refill, using tile 20 (hotspot #4)
//#define INITIAL_AMMO				0		// If defined, ammo = X when entering game.

#define BREAKABLE_WALLS 					// Breakable walls
#define BREAKABLE_WALLS_LIFE		1		// N+1 = Amount of hits to break wall
#define BREAKABLE_WALLS_BROKEN 		0 		// Use this tile for a broken wall, 0 if not def.
#define BREAKABLE_WALLS_BREAKING 	23 		// Use this tile while the wall is breaking (if defined)

// Scripting
// ---------

//#define ACTIVATE_SCRIPTING				// Activates msc scripting and flag related stuff.
//#define MAX_FLAGS 					32
//#define SCRIPTING_DOWN					// Use DOWN as the action key.
//#define SCRIPTING_KEY_AUX1				// Use AUX1 as the action key instead.
//#define SCRIPTING_KEY_FIRE				// User FIRE as the action key instead.
//#define SCRIPTING_KEY_NONE 				// No action key. 
//#define ENABLE_EXTERN_CODE				// Enables custom code to be run from the script using EXTERN n
//#define ENABLE_FIRE_ZONE					// Allows to define a zone which auto-triggers "FIRE"

// Timer
// -----

#define TIMER_ENABLE						// Enable timer
#define TIMER_INITIAL 				50		// For unscripted games, initial value.
#define TIMER_REFILL				10		// Timer refill, using tile 21 (hotspot #5)
//#define TIMER_LAPSE				32		// # of frames between decrements
//#define TIMER_START						// If defined, start timer from the beginning
//#define TIMER_SCRIPT_0					// If defined, timer = 0 runs "ON_TIMER_OFF" in the script
#define TIMER_GAMEOVER_0					// If defined, timer = 0 causes "game over"
//#define TIMER_KILL_0						// If defined, timer = 0 causes "one life less".
//#define TIMER_WARP_TO 0					// If defined, warp to screen X after "one life less".
//#define TIMER_WARP_TO_X			1		//
//#define TIMER_WARP_TO_Y			1		// "warp to" coordinates.
//#define TIMER_AUTO_RESET					// If defined, timer resets after "one life less"
//#define SHOW_TIMER_OVER					// If defined, "TIME OVER" shows when time is up.

// Save state
// ----------
//#define ENABLE_CHECKPOINTS				// Enable checkpoints
//#define CP_RESET_WHEN_DYING				// Move player to checkpoint when player dies.
//#define CP_RESET_ALSO_FLAGS				// and also restore its flags / values

// Top view:
// ---------

//#define PLAYER_GENITAL				// Enable top view.
//#define TOP_OVER_SIDE 					// UP/DOWN has priority over LEFT/RIGHT
//#define PLAYER_BOUNCE_WITH_WALLS			// Bounce when hitting a wall. Only really useful in MOGGY_STYLE mode

// Side view:
// ----------

//#define PLAYER_HAS_JUMP 					// If defined, player is able to jump.
//#define BOTH_KEYS_JUMP 						// If jump and no fire, use UP or FIRE to jump (only with keyboard)
//#define PLAYER_HAS_JETPAC 				// If defined, player can thrust a vertical jetpac
#define PLAYER_BOOTEE 					// Always jumping engine. Don't forget to disable "HAS_JUMP" and "HAS_JETPAC"!!!
//#define PLAYER_VKEYS 						// Use with VENG_SELECTOR. Advanced.
//#define PLAYER_DISABLE_GRAVITY			// Disable gravity. Advanced.

//#define PLAYER_STEPS_ON_ENEMIES			// If defined, stepping on enemies kills them
//#define PLAYER_CAN_STEP_ON_FLAG	1		// If defined, player can only kill when flag # is "1"
//#define PLAYER_MIN_KILLABLE		3		// Only kill enemies with id >= PLAYER_MIN_KILLABLE

//#define PLAYER_DISABLE_DEFAULT_HENG 		// To disble default horizontal engine (side/genital)
//#define PLAYER_DISABLE_DEFAULT_VENG 		// To disble default horizontal engine (genital)

// Configure keyboard

// How keys work (in sideview)
// - If player can't fire, BUTTON_A will JUMP.
// - If player can fire, and USE_TWO_BUTTONS is DEFINED, BUTTON_A will FIRE, BUTTON_B will JUMP
// - If player can fire, and USE_TWO_BUTTONS is DEFINED, BUTTON_A will FIRE, ÛP will JUMP

// To define different keys, the first two hex digits are the COLUMN, the next the ROW
// (Adapt. from cpctelera docs @ https://lronaldo.github.io/cpctelera/files/keyboard/keyboard-txt.html)
/*
=========================================================================================================
|     |                                       column                                                    |
|     |-------------------------------------------------------------------------------------------------|
| row |     40      |     41     |  42   | 43  | 44  | 45   |     46       | 47  |   48     |    49     |
|=====|=============|============|=======|=====|=====|======|==============|=====|==========|===========|
| 80  | f.          | f0         | Ctrl  | > , | < . | Space| V            | X   | Z        | Del       |
| 40  | Enter       | f2         | ` \   | ? / | M   | N    | B            | C   | Caps Lock| Unused    |
| 20  | f3          | f1         | Shift | * : | K   | J    | F Joy1_Fire1 | D   | A        | Joy0_Fire1|
| 10  | f6          | f5         | f4    | + ; | L   | H    | G Joy1_Fire2 | S   | Tab      | Joy0_Fire2|
| 08  | f9          | f8         | } ]   | P   | I   | Y    | T Joy1_Right | W   | Q        | Joy0_Right|
| 04  | Cursor Down | f7         | Return| | @ | O   | U    | R Joy1_Left  | E   | Esc      | Joy0_Left |
| 02  | Cursor Right| Copy       | { [   | = - | ) 9 | ' 7  | % 5 Joy1_Down| # 3 | " 2      | Joy0_Down |
| 01  | Cursor Up   | Cursor Left| Clr   | £ ^ | _ 0 | ( 8  | & 6 Joy1_Up  | $ 4 | ! 1      | Joy0_Up   |
=========================================================================================================
*/

//#define USE_TWO_BUTTONS					// Alternate keyboard scheme for two-buttons games

extern unsigned char def_keys [0];
#asm
	._def_keys
		/*
		defw $4820 		; LEFT     A
		defw $4720 		; RIGHT    D
		defw $4708 		; UP       W
		defw $4710 		; DOWN     S

		defw $4440 		; BUTTON_A M
		defw $4540 		; BUTTON_B N
		*/

		defw $4404 		; LEFT     O
		defw $4308 		; RIGHT    P
		defw $4808 		; UP       Q
		defw $4820 		; DOWN     A

		defw $4580 		; BUTTON_A SPACE
		defw $4808 		; BUTTON_B Q

		defw $4204		; KEY_ENTER
		defw $4804		; KEY_ESC	

		defw $4440		; KEY_AUX1 M
		defw $4880 		; KEY_AUX2 Z
		defw $4801 		; KEY_AUX3 1	// Those are used in the menus!
		defw $4802 		; KEY_AUX4 2
#endasm

// ============================================================================
// III. Screen configuration
// ============================================================================

// This sections defines how stuff is rendered, where to show counters, etcetera
// Set to 99 so it doesn't show even if it should!!

#define VIEWPORT_X					1		//
#define VIEWPORT_Y					3		// Viewport character coordinates
#define LIFE_X						5		//
#define LIFE_Y						1		// Life gauge counter character coordinates
#define OBJECTS_X					16		//
#define OBJECTS_Y					1		// Objects counter character coordinates
#define OBJECTS_ICON_X				99		// 
#define OBJECTS_ICON_Y				99		// Objects icon character coordinates (use with ONLY_ONE_OBJECT)
#define KEYS_X						22		//
#define KEYS_Y						1		// Keys counter character coordinates
#define KILLED_X					99		//
#define KILLED_Y					99		// Kills counter character coordinates
#define AMMO_X						99		// 
#define AMMO_Y						99		// Ammo counter character coordinates
#define TIMER_X 					29		//
#define TIMER_Y 					1		// Timer counter coordinates

// Text

//#define LINE_OF_TEXT				1		// If defined, scripts can show text @ Y = #
//#define LINE_OF_TEXT_X			1		// X coordinate.
//#define LINE_OF_TEXT_ATTR			71		// Attribute
//#define LINE_OF_TEXT_NO_AUTOERASE			// Do it yourself

// Graphic FX, uncomment which applies...

//#define USE_AUTO_SHADOWS					// Automatic shadows made of darker attributes
//#define USE_AUTO_TILE_SHADOWS 			// Automatic shadows using specially defined tiles 32-47.
#define UNPACKED_MAP						// Full, uncompressed maps. Shadows settings are ignored.
#define PACKED_MAP_ALT_TILE 		19		// If defined, in 16 tiles mode, alt tile (default 19)

#define PLAYER_CUSTOM_ANIMATION 			// Code your own animation in my/custom_animation.h

//#define ENABLE_TILANIMS			32		// If defined, animated tiles are enabled.
											// the value especifies first animated tile pair.
											// Use 99 to disable autodetection in map data and handle
											// creation yourself!
//#define TILANIMS_MOVE_ONE 				// @Update one per frame
#define TILANIMS_MOVE_ALL 					// Update all per frame

//#define PAUSE_ABORT						// Add h=PAUSE, y=ABORT
//#define GET_X_MORE						// Shows "get X more" when getting an object

// ============================================================================
// IV. Player movement configuration
// ============================================================================

// This section is used to define which constants are used in the gravity/acceleration engine.
// If a side-view engine is configured, we have to define vertical and horizontal constants
// separately. If a top-view engine is configured instead, the horizontal values are also
// applied to the vertical component, vertical values are ignored.

// IV.1. Vertical movement. Only for side-view.

#define PLAYER_MAX_VY_CAYENDO		512 		// Max falling speed 
#define PLAYER_G					32		// Gravity acceleration 

#define PLAYER_VY_INICIAL_SALTO		64 		// Initial junp velocity 
#define PLAYER_MAX_VY_SALTANDO		320 	// Max jump velocity 
#define PLAYER_INCR_SALTO			64		// acceleration while JUMP is pressed 

#define PLAYER_INCR_JETPAC			32		// Vertical jetpac gauge
#define PLAYER_MAX_VY_JETPAC		256 	// Max vertical jetpac speed

// IV.2. Horizontal (side view) or general (top view) movement.

#define PLAYER_MAX_VX				192 	// Max velocity (192/64 = 3 p?xels/frame)
#define PLAYER_AX					24		// Acceleration (24/64 = 0,375 p?xels/frame^2)
#define PLAYER_RX					32		// Friction (32/64 = 0,5 p?xels/frame^2)

// ============================================================================
// V. Tile behaviour
// ============================================================================

// Defines the behaviour for each tile. Remember that if keys are activated, tile #15 is a bolt
// and, therefore, it should be made a full obstacle!

// 0 = Walkable (no action)
// 1 = Walkable and kills.
// 2 = Walkable and hides.
// 4 = Platform (only stops player if falling on it)
// 8 = Full obstacle (blocks player from all directions)
// 10 = special obstacle (pushing blocks OR locks!)
// 16 = Breakable (#ifdef BREAKABLE_WALLS)
// 128 = C.I. launcher tile, launches my/ci/on_special_tile.h on touch
// You can add the numbers to get combined behaviours
// Save for 10 (special), but that's obvious, innit?
#ifndef COMPRESSED_LEVELS
unsigned char behs [] = {
	0, 8, 8, 0, 1, 8, 0, 1, 1, 1, 1, 8, 8, 8,8,10,
	0, 0, 0, 8, 8, 8, 24, 24, 8, 8, 8, 8, 8, 8, 8, 8,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
#endif
