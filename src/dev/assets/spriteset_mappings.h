// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// Spriteset mappings. 
// One entry per sprite face in the spriteset!

#define SW_SPRITES_ALL  16

unsigned char sm_cox [] = { 
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0
};

unsigned char sm_coy [] = { 
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0
};

void *sm_invfunc [] = {
	cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, 
	cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, 
	cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, 
	cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16
};

void *sm_updfunc [] = {
	cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b,
	cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b
	cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b
	cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b
};

void *sm_sprptr [] = {
	_sprites + 0x000, _sprites + 0x040, sprites + 0x080, sprites + 0x0C0,
	_sprites + 0x100, _sprites + 0x140, sprites + 0x180, sprites + 0x1C0,
	_sprites + 0x200, _sprites + 0x240, sprites + 0x280, sprites + 0x2C0,
	_sprites + 0x300, _sprites + 0x340, sprites + 0x380, sprites + 0x3C0
};
