// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

extern unsigned char *wyz_songs [0];

#asm
	._00_title_mus_bin
		BINARY "../mus/00_title.mus.bin"

	._01_ingame_mus_bin
		BINARY "../mus/01_ingame.mus.bin"

	._02_ingame_mus_bin
		BINARY "../mus/02_ingame.mus.bin"

	._03_intro_mus_bin
		BINARY "../mus/03_intro.mus.bin"

	._04_gameover_mus_bin
		BINARY "../mus/04_gameover.mus.bin"

	._wyz_songs
		defw 	_00_title_mus_bin, _01_ingame_mus_bin, _02_ingame_mus_bin, _03_intro_mus_bin, _04_gameover_mus_bin
		
#endasm
