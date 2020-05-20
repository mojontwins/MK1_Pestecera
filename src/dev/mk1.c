// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// mk1.c
//#define DEBUG_KEYS
#include <cpcrslib.h>
#include <cpcwyzlib.h>

// We are using some stuff from splib2 directly.
#asm
		XREF _nametable
		LIB cpc_KeysData
		LIB cpc_UpdTileTable
		LIB cpc_InvalidateRect
#endasm

// DON'T touch these
#define FIXBITS 			6	
#define MAX_ENEMS 			3			

#include "my/config.h"
#include "autodefs.h"
#include "prototypes.h"

#define BASE_ROOM_BUFFERS	0xC000 + 0x600
#define BASE_DIRTY_CELLS 	0xC800 + 0x600
#define BASE_ARRAYS 		0xD000 + 0x600
#define BASE_SPRITES 		0xE000 + 0x600
#define BASE_LUT			0xF800 + 0x600
#define BASE_WYZ 			0xFF80				// Decode buffers

#define BASE_SUPERBUFF  	0x9000

// Cosas del juego:

#include "definitions.h"

#ifdef ACTIVATE_SCRIPTING
	#include "my/msc-config.h"
#endif

#ifdef MODE_128K
	#include "128k.h"
	#include "assets/librarian.h"
#endif

#include "assets/ay_fx_numbers.h"
#include "aplib.h"
#include "pantallas.h"
#include "assets/pal.h"

#ifdef COMPRESSED_LEVELS
	#include "assets/levels.h"
	#include "assets/extrasprites.h"
	#include "my/levelset.h"
#else
	#include "assets/mapa.h"
	#include "assets/tileset.h"
	#include "assets/enems.h"
	#include "assets/sprites.h"
	#include "assets/extrasprites.h"
#endif
#include "assets/spriteset_mappings.h"
#include "assets/trpixlut.h"

#include "my/ci/extra_vars.h"

#include "printer.h"
#include "my/ci/extra_functions.h"

#ifdef ACTIVATE_SCRIPTING
	#ifdef ENABLE_EXTERN_CODE
		#include "my/extern.h"
	#endif
	#include "my/msc.h"
#endif

#include "engine/general.h"
#ifdef BREAKABLE_WALLS
	#include "engine/breakable.h"
#endif
#ifdef PLAYER_CAN_FIRE
	#include "engine/bullets.h"
#endif
#ifdef ENABLE_SIMPLE_COCOS
	#include "engine/simple_cocos.h"
#endif
#ifdef COMPRESSED_LEVELS
	#include "engine/c_levels.h"
#endif
#include "engine.h"
#include "engine/player.h"
#include "engine/enengine.h"
#include "engine/hotspots.h"

#ifdef ENABLE_CHECKPOINTS
	#include "savegame.h"
#endif

#include "my/title_screen.h"
#include "mainloop.h"
