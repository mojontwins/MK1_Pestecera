// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// TODO : setup a sprite for the shoot

sp_sw [SP_EXTRA_BASE].cox = 0;
sp_sw [SP_EXTRA_BASE].coy = 0;
sp_sw [SP_EXTRA_BASE].invfunc = cpc_PutSpTileMap4x8;
sp_sw [SP_EXTRA_BASE].updfunc = cpc_PutTrSp4x8TileMap2b;
sp_sw [SP_EXTRA_BASE].sp0 = sp_sw [SP_PLAYER].sp1 = (unsigned int) (sprite_19_a);
