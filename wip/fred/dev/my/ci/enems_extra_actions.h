// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

if (_en_t == 3 && _en_mx > 0) {
	//en_an_next_frame [enit] = enem_cells [6 + en_an_frame [enit]];
	en_an_next_frame [enit] = sm_sprptr [GENERAL_ENEMS_BASE_CELL + 6 + en_an_frame [enit]];
}


//if (shoot_x + 4 >= _en_x && shoot_x + 4 <= _en_x + 15 && shoot_y + 4 >= _en_y && shoot_y + 4 <= _en_y + 15)
if (shoot_x + 4 >= _en_x && shoot_x <= _en_x + 11 && shoot_y + 4 >= _en_y && shoot_y <= _en_y + 11) {
	if (_en_t == 9) {
		_en_my = 0;
		if (_en_x < gpx) _en_mx = -PHANTOM_V; else _en_mx = PHANTOM_V;
	} else if (_en_t < 3) {
		AY_PLAY_SOUND (SFX_KILL_ENEMY_STEP);										
		en_an_state [enit] = GENERAL_DYING;
		en_an_count [enit] = 12;
		en_an_next_frame [enit] = sprite_17_a;
		enems_kill ();
	}

	if (_en_t != 3) shoot_y = 160;
}
