// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

if (cpc_TestKey(KEY_BUTTON_A) && p_disparando == 0) {			
	p_disparando = 1;
	if (
		shoot_y >= 160 &&
		p_on_rope == 0
	) shoot_create ();
} else p_disparando = 0;

shoot_do ();
