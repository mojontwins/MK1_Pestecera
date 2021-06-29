// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// Modify p_vy
// Don't forget to use the veng_selector if VENG_SELECTOR is defined.

// Linear Platformer Engine v0.1. Vertical axis
// Needs constants defined in `extra_vars.h`.

if (p_saltando) {

} else {
	p_vy = PLAYER_LINEAR_GRAVITY*64;
}
