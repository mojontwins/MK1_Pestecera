// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

extern unsigned char trpixlutc [0];

#asm
	; LUT for transparent pixels in sprites
	; taken from CPCTelera
	._trpixlutc
		BINARY "assets/trpixlutc.bin"
#endasm
