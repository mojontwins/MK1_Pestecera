// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

extern unsigned char *wyz_songs [0];

#asm
	.title_mus_bin
		BINARY "../mus/title.mus.bin"

	.ingame_mus_bin
		BINARY "../mus/ingame.mus.bin"

	.gover_mus_bin
		BINARY "../mus/gover.mus.bin"

	._wyz_songs
		defw 	title_mus_bin, ingame_mus_bin, gover_mus_bin
#endasm
