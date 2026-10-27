// MTE MK1 (la Churrera) v5.12
// Copyleft 2010-2014, 2020-2025 by the Mojon Twins

extern unsigned char *wyz_songs [0];

#asm
	.title_mus_bin
		BINARY "../mus/title.mus.bin"

	.ingame_a_mus_bin
		BINARY "../mus/ingame_a.mus.bin"

	.ingame_b_mus_bin
		BINARY "../mus/ingame_b.mus.bin"

	.ingame_c_mus_bin
		BINARY "../mus/ingame_c.mus.bin"

	.gover_mus_bin
		BINARY "../mus/gover.mus.bin"

	.ending_1_mus_bin
		BINARY "../mus/ending_1.mus.bin"

	.intro_mus_bin
		BINARY "../mus/intro.mus.bin"

	._wyz_songs
		defw 	title_mus_bin, ingame_a_mus_bin, ingame_b_mus_bin, ingame_c_mus_bin, gover_mus_bin, ending_1_mus_bin, intro_mus_bin
#endasm
