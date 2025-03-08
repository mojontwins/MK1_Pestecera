// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

flags[1] = 0; //variable para almacenar el número de cristales
flags[2] = 0; //variable para indicar si hemos conseguido los 10 cristales
flags[3] = 0; //variable para indicar si hemos hablado ya con el ulises

//MOSTRAMOS EL PRIMER TEXTO, ASÍ EXPLICAMOS DE QUÉ VA EL JUEGO
wyz_play_music (3);
blackout_area_inv();
textbox(0);
blackout_area_inv();
textbox(1);
blackout_area_inv();
textbox(2);
blackout_area_inv();
textbox(3);
wyz_play_music (1);