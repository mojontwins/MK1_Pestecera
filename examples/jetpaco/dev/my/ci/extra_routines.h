// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

if (gm == GM_ESTRUJATORS_LEVEL) chac_chacs_do ();

if (jumo_y < 160) {
	if(jumo_ct) {
		sp_sw [SP_EXTRA_BASE].sp0 = (int) (spr_jumo + (jumo_fr << 4));
		jumo_fr ++; if (jumo_fr == 4) jumo_y = 160;
	}
	jumo_ct = 1 - jumo_ct;
} else sp_sw [SP_EXTRA_BASE].sp0 = (int) (SPRFR_EMPTY);