// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// deactivate RESPAWN_ON_ENTER and write your own routine here!

// Back to life!
if ((malotes [enoffsmasi].t & 0xF) != 6) {
	malotes [enoffsmasi].t &= 0xEF;		
	malotes [enoffsmasi].life = ENEMIES_LIFE_GAUGE;
}
