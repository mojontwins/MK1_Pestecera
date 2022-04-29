// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// Detect breakable platforms

if (at1 == 20) {
	_x = cx1; _y = cy1; break_wall ();
} 

// If we are stepping over TWO different platforms
if (cx1 != cx2 && at2 == 20) {
	_x = cx2; _y = cy1; break_wall ();
}
