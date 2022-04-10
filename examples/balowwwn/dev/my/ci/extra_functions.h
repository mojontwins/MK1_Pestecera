// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

void break_vertical (void) {
	// Called from obstacle_up and obstacle_down
	_y = cy1;

	if (at1 & 16) {
		_x = cx1; break_wall ();
	}

	if (at2 & 16) {
		_x = cx2; break_wall ();
	}
}

void break_horizontal (void) {
	// Called from obstacle_left and obstacle_right
	_x = cx1;

	if (at1 & 16) {
		_x = cy1; break_wall ();
	}

	if (at2 & 16) {
		_x = cy2; break_wall ();
	}
}
