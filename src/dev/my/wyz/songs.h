// MTE MK1 (la Churrera) v5.12
// Copyleft 2010-2014, 2020-2025 by the Mojon Twins

extern unsigned char *wyz_songs [0];

#asm
	._00_title_mus_bin
		BINARY "../mus/00_title.mus.bin"

	._01_ingame_mus_bin
		BINARY "../mus/01_ingame.mus.bin"

	._wyz_songs
		defw 	_00_title_mus_bin, _01_ingame_mus_bin
#endasm
