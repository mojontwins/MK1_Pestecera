// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

case 9:
	en_an_base_frame [enit] = GENERAL_ENEMS_BASE_CELL;
	en_ph_ctr [enit] = 0;
	malotes [enoffsmasi].y2 = 99;
	malotes [enoffsmasi].x &= 0xf0;
	malotes [enoffsmasi].y &= 0xf0;
	break;

case 8:
	en_an_base_frame [enit] = 99;
	en_an_state [enit] = 0;
	malotes [enoffsmasi].y = malotes [enoffsmasi].y1;
	break;
	