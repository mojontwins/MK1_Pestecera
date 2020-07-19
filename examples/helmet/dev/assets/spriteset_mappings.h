// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// Spriteset mappings. 
// One entry per sprite face in the spriteset!

unsigned char sm_cox [] = { 
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0 						// <= extra sprite faces added
};

unsigned char sm_coy [] = { 
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0 						// <= extra sprite faces added
};

void *sm_invfunc [] = {
	cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, 
	cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, 
	cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, 
	cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16,
	cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16 // <= extra sprite faces added
};

void *sm_updfunc [] = {
	cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b,
	cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b,
	cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b,
	cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b,
	cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b // <= extra sprite faces added
};

extern void *sm_sprptr [0]; 
#asm
	._sm_sprptr
		defw _sprites + 0x000, _sprites + 0x040, _sprites + 0x080, _sprites + 0x0C0
		defw _sprites + 0x100, _sprites + 0x140, _sprites + 0x180, _sprites + 0x1C0
		defw _sprites + 0x200, _sprites + 0x240, _sprites + 0x280, _sprites + 0x2C0
		defw _sprites + 0x300, _sprites + 0x340, _sprites + 0x380, _sprites + 0x3C0
		defw _sprites + 0x400, _sprites + 0x440 // <= extra sprite faces added
#endasm
