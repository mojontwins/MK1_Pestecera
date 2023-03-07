// MTE MK1 (la Churrera) v5.10
// Copyleft 2010-2014, 2020-2022 by the Mojon Twins

// Spriteset mappings. 
// One entry per sprite face in the spriteset!

#define SWsprites_ALL  16

unsigned char sm_cox [] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

unsigned char sm_coy [] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void *sm_invfunc [] = {
	cpc_PutSpTileMap8x16Px, cpc_PutSpTileMap8x16Px, cpc_PutSpTileMap8x16Px, cpc_PutSpTileMap8x16Px, 
	cpc_PutSpTileMap8x16Px, cpc_PutSpTileMap8x16Px, cpc_PutSpTileMap8x16Px, cpc_PutSpTileMap8x16Px, 
	cpc_PutSpTileMap8x16Px, cpc_PutSpTileMap8x16Px, cpc_PutSpTileMap8x16Px, cpc_PutSpTileMap8x16Px, 
	cpc_PutSpTileMap8x16Px, cpc_PutSpTileMap8x16Px, cpc_PutSpTileMap8x16Px, cpc_PutSpTileMap8x16Px
};

void *sm_updfunc [] = {
	cpc_PutTrSp8x16TileMap2bPx, cpc_PutTrSp8x16TileMap2bPx, cpc_PutTrSp8x16TileMap2bPx, cpc_PutTrSp8x16TileMap2bPx, 
	cpc_PutTrSp8x16TileMap2bPx, cpc_PutTrSp8x16TileMap2bPx, cpc_PutTrSp8x16TileMap2bPx, cpc_PutTrSp8x16TileMap2bPx, 
	cpc_PutTrSp8x16TileMap2bPx, cpc_PutTrSp8x16TileMap2bPx, cpc_PutTrSp8x16TileMap2bPx, cpc_PutTrSp8x16TileMap2bPx, 
	cpc_PutTrSp8x16TileMap2bPx, cpc_PutTrSp8x16TileMap2bPx, cpc_PutTrSp8x16TileMap2bPx, cpc_PutTrSp8x16TileMap2bPx
};

extern void *sm_sprptr [0];
#asm
	._sm_sprptr
		defw _sprites + 0x0000, _sprites + 0x0040, _sprites + 0x0080, _sprites + 0x00C0
		defw _sprites + 0x0100, _sprites + 0x0140, _sprites + 0x0180, _sprites + 0x01C0
		defw _sprites + 0x0200, _sprites + 0x0240, _sprites + 0x0280, _sprites + 0x02C0
		defw _sprites + 0x0300, _sprites + 0x0340, _sprites + 0x0380, _sprites + 0x03C0
#endasm

// A list of MK1v4-friendly macros
#define SPRITE_00 (_sprites + 0x0000)
#define SPRITE_01 (_sprites + 0x0040)
#define SPRITE_02 (_sprites + 0x0080)
#define SPRITE_03 (_sprites + 0x00C0)
#define SPRITE_04 (_sprites + 0x0100)
#define SPRITE_05 (_sprites + 0x0140)
#define SPRITE_06 (_sprites + 0x0180)
#define SPRITE_07 (_sprites + 0x01C0)
#define SPRITE_08 (_sprites + 0x0200)
#define SPRITE_09 (_sprites + 0x0240)
#define SPRITE_0A (_sprites + 0x0280)
#define SPRITE_0B (_sprites + 0x02C0)
#define SPRITE_0C (_sprites + 0x0300)
#define SPRITE_0D (_sprites + 0x0340)
#define SPRITE_0E (_sprites + 0x0380)
#define SPRITE_0F (_sprites + 0x03C0)

