// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// Modify p_vx

if (p_saltando) {

} else if (possee) {

	#ifdef IS_CPC
		if (cpc_TestKey (KEY_LEFT))
	#else
		if ((pad0 & sp_LEFT) == 0)
	#endif
	{
		p_vx = -PLAYER_LINEAR_VX*64;
	} else

	#ifdef IS_CPC
		if (cpc_TestKey (KEY_RIGHT))
	#else
		if ((pad0 & sp_RIGHT) == 0)
	#endif
	{
		p_vx = PLAYER_LINEAR_VX*64;
	} else {
		p_vx = 0;
	}
} else p_vx = 0;