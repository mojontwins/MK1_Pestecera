// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// Note that _en_t has bit 4 raised, so:
if (_en_t == 0x16) {	
	// Fanties give you a key
	++ p_keys;
	AY_PLAY_SOUND (SFX_KEY_GET);
}
