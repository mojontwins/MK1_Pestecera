// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// player_center_checks.h

// rdb contains behaviour at the center of the player

// estrujators have behaviour 2. Use this to crush player!
if ((rdb & 2) == 2) {
	p_vy = 0;

	#ifdef PLAYER_FLICKERS
		if (p_estado == EST_NORMAL)
	#endif		
	{
		p_killme = SFX_SPIKES;
	}
}
