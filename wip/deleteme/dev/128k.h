// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// 128K stuff

void SetRAMBank(void) {
#asm
	.SetRAMBank
			ld	a, 16
			or	b
			ld	bc, $7ffd
			out (C), a
#endasm
}
