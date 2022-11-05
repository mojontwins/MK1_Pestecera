// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

case 9:
	if (en_ph_ctr [enit]) {
		-- en_ph_ctr [enit];
		
		if (_en_mx < 0 && _en_x == 0) _en_mx = PHANTOM_V;
		if (_en_mx > 0 && _en_x == 224) _en_mx = -PHANTOM_V;
		if (_en_my < 0 && _en_y == 0) _en_my = PHANTOM_V;
		if (_en_my > 0 && _en_y == 144) _en_my = -PHANTOM_V;

		_en_x += _en_mx;
		_en_y += _en_my;
	} else {
		rda = rand () & 3;
		_en_mx = dx [rda]; _en_my = dy [rda];
		en_ph_ctr [enit] = (1 + (rand () & 3)) << 3;
	}

	active = 1;
	break;

case 8:
	if (en_an_state [enit]) {
		// Animation
		en_an_next_frame [enit] = drop_animation [en_an_state [enit]];

		en_an_count [enit] = (en_an_count [enit] + 1) & 3;
		if (en_an_count [enit] == 0) {
			++ en_an_state [enit]; if (en_an_state [enit] == 4) {
				en_an_state [enit] = 0;
				_en_y = _en_y1 - _en_my;
				en_an_next_frame [enit] = sprite_18_a;
			}
		}
	} else {
		// Fall
		en_an_next_frame [enit] = drop_animation [0];

		_en_y += _en_my;
		if (_en_y == _en_y2) {
			en_an_state [enit] = 1;
			en_an_count [enit] = 0;
		}
	}

	active = 1;
	break;
	