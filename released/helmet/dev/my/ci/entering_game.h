// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

#asm
		xor a
		ld  (_f_0), a
		ld  (_f_1), a
		inc a
		ld  (_f_3), a
		ld  a, 5
		ld  (_f_2), a
#endasm

pal_set (level_pal [level]);
c_is_classic = l_is_classic [level]; // Classic gameplay (set bombs & return)

// Level 4: no ammo
if (level == 4) p_ammo = 0;
