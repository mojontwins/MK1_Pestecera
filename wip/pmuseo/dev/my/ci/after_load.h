// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

blackout ();

#ifdef MODE_128K
    // Resource 2 = ending
    get_resource (CREDITOS_BIN, BASE_SUPERBUFF);
#else
    unpack ((unsigned int) (s_creditos), BASE_SUPERBUFF);
#endif
cpc_ShowTileMap (1);
AY_PLAY_MUSIC (6);

espera_activa (400);

#ifdef MODE_128K
    // Resource 2 = ending
    get_resource (INTRO_BIN, BASE_SUPERBUFF);
#else
    unpack ((unsigned int) (s_intro), BASE_SUPERBUFF);
#endif
cpc_ShowTileMap (1);


espera_activa (400);
AY_STOP_SOUND ();