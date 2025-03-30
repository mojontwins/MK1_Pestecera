// MTE MK1 (la Churrera) v5.12
// Copyleft 2010-2014, 2020-2025 by the Mojon Twins

// player_center_checks.h

// rdb contains behaviour at the center of the player

// Se usa para el evil tile en este juego
if ((rdb & 1) == 1) {
	#ifdef PLAYER_FLICKERS
		if (p_estado == EST_NORMAL && half_life)
	#endif		
	{
		p_killme = SFX_SPIKES;
	}
}
