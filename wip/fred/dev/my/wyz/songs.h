// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

extern unsigned char *wyz_songs [0];

#asm
	._00_title_mus_bin
		BINARY "../mus/00_title.mus.bin"

	._01_ingame_mus_bin
		BINARY "../mus/01_ingame.mus.bin"

	._02_start_mus_bin
		BINARY "../mus/02_start.mus.bin"

	._03_gover_mus_bin
		BINARY "../mus/03_gover.mus.bin"

	._04_ending_mus_bin
		BINARY "../mus/04_ending.mus.bin"

	._wyz_songs
		defw 	_00_title_mus_bin, _01_ingame_mus_bin
#endasm
