
extern unsigned char *arkos_songs [0];
extern unsigned char arkos_sfx_song [0];

#asm
	._00_title_bin
		BINARY "../mus/00_title_c.bin"

	._01_ingame_bin
		BINARY "../mus/01_ingame_c.bin"

	._arkos_sfx_song
		BINARY "../mus/sfx_c.bin"

	._arkos_songs
		defw 	_00_title_bin, _01_ingame_bin
#endasm
