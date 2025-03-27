// MTE MK1 (la Churrera) v5.12
// Copyleft 2010-2014, 2020-2025 by the Mojon Twins

extern unsigned char tileset [0];
#asm
		XDEF tiles
	._tileset
	.tiles
	._font
		BINARY "../bin/font.bin" 	// 1024 bytes for 64 patterns
	._tspatterns
		BINARY "../bin/work.bin"   // 3072 bytes for 192 patterns
#endasm
