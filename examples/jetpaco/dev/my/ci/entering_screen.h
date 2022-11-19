// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// Setup special stuff...
// *TODO*: Inline assembly this / replace default tilanims with custom implementation

switch (gm) {
	case GM_PROPELLERS_LEVEL:
		for (gpit = 0; gpit < PROPELLERS_MAX; gpit ++) {
			if (n_pant == prop_n_pant [gpit]) {
				_x = prop_x [gpit]; _y = prop_y [gpit];

				// "paint" behs over propeller as 128 until we hit a non-zero
				rda = _x + ((_y << 4) - _y);

				while (rda >= 15) {
					rda -= 15;
					if (map_attr [rda]) break; else map_attr [rda] = 128;
				}

				// Add tilanim
				_n = _y | (_x << 4); _t = 30; 	// tilanims are tiles 30-31
				tilanims_add ();
			}
		}
		break;

	case GM_ESTRUJATORS_LEVEL:
		chac_chac_idx = 0;
		for (gpit = 0; gpit < ESTRUJATORS_MAX; gpit ++) {
			if (n_pant == estr_n_pant [gpit]) {
				_x = estr_x [gpit]; _y = estr_y [gpit]; _t = estr_t [gpit];
				chac_chacs_add ();
			}
		}

		break;
}