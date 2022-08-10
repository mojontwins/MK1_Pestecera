# Jet Paco Extended

Vamos a ponerle más cosas a Jet Paco. Por lo pronto, la fase B de las versiones de NES y SG-1000 debidamente apañada. Lo haremos por el método que seguimos en Lala Lah, esto es, no haciendo un multi-nivel al uso, sino pegando enemigos y pantallas debajo de los que ya hay para tener un nivel el doble de grande, y luego saltando adonde conviene antes de empezar el juego según la fase que haya que jugar. Idem para seleccionar tiles, hotspots, etc. 

Los tiles y hotspots se pintan con un offset según la inyección de código en `my/ci/on_map_tile_decoded.h` y `my/ci/hotspots_setup_t_modification.h`, que nos vienen bien para esta mierda. Échale un ojal a `my/ci/before_game.h` y `my/ci/extra_vars.h` para coscarte.

Ahora hay que meter más cosas.

## Propellers

En la versión de SG-1000 se añade propellers a la fase B, codificados con el tile 16, que está fuera de tileset porque en esta versión estamos en modo packed.

Que podría poner un custom renderer 53... Pues sí. Pero vamos a hacerlo de otra forma.

El conversor (que he modificado) me chiva los tiles fuera de rango, que son los propellers. Esta es la lista que saca:

```
	$ ..\..\..\src\utils\mapcnv.exe ..\map\mapa.map assets\mapa.h 7 10 15 10 15 packed
	Warning! out of bounds tile 16 @ 40 (6, 3) -> wrote 0
	Warning! out of bounds tile 16 @ 40 (4, 5) -> wrote 0
	Warning! out of bounds tile 16 @ 40 (2, 7) -> wrote 0
	Warning! out of bounds tile 16 @ 44 (1, 9) -> wrote 0
	Warning! out of bounds tile 16 @ 44 (5, 9) -> wrote 0
	Warning! out of bounds tile 16 @ 55 (12, 9) -> wrote 0
	Warning! out of bounds tile 16 @ 57 (3, 9) -> wrote 0
	Warning! out of bounds tile 16 @ 61 (9, 9) -> wrote 0
	Warning! out of bounds tile 16 @ 63 (4, 9) -> wrote 0
	Warning! out of bounds tile 16 @ 67 (3, 9) -> wrote 0
```

Como son muy pocos creo que no se me va a caer un dedo por armar unos arrays a mano para esto. Los propellers funcionaban convirtiendo los behs de los tiles 0 que tenían arriba, hasta llegar a uno con beh no 0, a un beh especial. Puedo usar el 128 y aprovechar toda la infraestructura que ya trae MK1 en `my/ci/on_special_tile.h` para hacer flotar a Paco / Puri.

Para mover los propellers haré algo así como los tiles animados, que no sé cómo de mierder estarán en MK1. Aprovecharé para apañarlo bien. Pensaba guardar directamente gpit para los propellers (y*15+x), pero si tengo que animar lo suyo es guardar x, y.

Los tiles animados (`ENABLE_TILANIMS`) se añaden automáticamente mientras se pinta el mapa por arte de comparar el tile con `ENABLE_TILANIMS`. Esto me parece gastar mucho tiempo porque yo no voy a usar esto. Quizá es hora de añadir algo para desactivar este comportamiento y vamos a manejar los tiles animados por nuestra borza. O no: si ponemos `ENABLE_TILANIMS` a 99 haremos que el comportamiento sea este.

```c
	// Añadiendo a my/ci/extra_vars.h
	
	#define PROPELLERS_MAX 10
	unsigned char prop_n_pant [] = {40, 40, 40, 44, 44, 55, 57, 61, 63, 67};
	unsigned char prop_x      [] = { 6,  4,  2,  1,  5, 12,  3,  9,  4,  3};
	unsigned char prop_y      [] = { 3,  5,  7,  9,  9,  9,  9,  9,  9,  9};

	#define PLAYER_AY_FLOAT 	64
	#define PLAYER_VY_FLOAT_MAX 512
```

Tendré que procesar esta información para cada pantalla en `entering_screen.h`, que se ejecuta cuando `map_buff` y `map_attr` están debidamente llenos, algo así (que pasaré a ensamble).

```c
	// my/ci/entering_screen.h

	if (gm == 1) {
		for (gpit = 0; gpit < PROPELLERS_MAX; gpit ++) {
			if (n_pant == prop_n_pant [gpit]) {
				_x = prop_x [gpit]; _y = prop_y [gpit];

				// "paint" behs over propeller as 128 until we hit a non-zero
				rda = _x | ((_y << 4) - _y);

				while (rda >= 15) {
					rda -= 15;
					if (map_attr [rda]) break; else map_attr [rda] = 128;
				}

				// Add tilanim
				_n = _y | (_x << 4); _t = 30; 	// tilanims are tiles 30-31
				tilanims_add ();
			}
		}
	}
```

Pasar a ensamble no por velocidad, porque es al entrar a la pantalla y tampoco nadie se va a andar fijando. Es por tamaño.

Con eso y esto, entiendo que deberían funcionar:

```c
	// my/ci/on_special_tile.h

	// Propel!
	p_vy -= PLAYER_AY_FLOAT;
	if (p_vy < -PLAYER_VY_FLOAT_MAX) p_vy = -PLAYER_VY_FLOAT_MAX;
```

He tenido que añadir código a `tilanims.h` para que los actualice todos pero no estoy NADA contento con esto, creo que podría hacerlo mejor y más optimizado si pasara de tilanims y programase mi propia mierda. Lo terminaré haciendo, pero antes quiero ver que al menos funciona.

## Paco / Puri

TODO

## Más fases

La idea ronda de meter una tercera fase. En el juego original se reaprovechaban tiles de las dos anteriores, mezclándolos. Podría hacerlo si meto mapeo de tiles. Podría probar el concepto con lo que tengo, estableciendo un array al mapeo de tiles, que para la fase uno contenga valores 0-15 y para la segunda valores 32-47. Para cada tile, en lugar de sumar el offset, habría que acceder con "_t" al array correspondiente y obtener el valor de ahí.

Cuando tenga esto funcionando meter la tercera fase será cuestión de hacer un nuevo array.

Y esto es super interesante para otros juegos (MK1v4 lo implementa de fábrica, esto sería por custom). ¡Y lo he hecho en 5 minutos!

```c
	// extra_vars.h

	// Mapped tilesets

	unsigned char gm_ts_0 [] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	unsigned char gm_ts_1 [] = { 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47};
	unsigned char *gm_ts_list [] = {gm_ts_0, gm_ts_1};

	unsigned char *gm_ts;
```

```c
	// before_game.h

	gm_ts = gm_ts_list [gm];
```

```c
	// on_map_tile_decoded.h

	#asm
		// Mapped tilesets. Current tile would be gm_ts [A]

			ld  hl, _gm_ts
			ld  e, (hl)
			inc hl
			ld  d, (hl) 			; DE -> *gm_ts

			ld  l, a 
			ld  h, 0
			add hl, de 
			ld  a, (hl)
	#endasm
```


## Estrujadores

Después de un millón de dimes y diretes debidos a padrastros, vamos a implementar los estrujadores. Antes que nada, los guardaré en arrays como hice con los ventiladores propellers, utilizando para ello los mensajes de error del conversor de mapas:

```
	Warning! out of bounds tile 24 @ 70 (7, 2) -> wrote 0
	Warning! out of bounds tile 25 @ 74 (1, 4) -> wrote 0
	Warning! out of bounds tile 24 @ 73 (2, 5) -> wrote 0
	Warning! out of bounds tile 25 @ 73 (5, 5) -> wrote 0
	Warning! out of bounds tile 26 @ 75 (14, 5) -> wrote 0
	Warning! out of bounds tile 26 @ 76 (0, 5) -> wrote 0
	Warning! out of bounds tile 25 @ 71 (3, 6) -> wrote 0
	Warning! out of bounds tile 25 @ 71 (9, 6) -> wrote 0
	Warning! out of bounds tile 24 @ 82 (3, 0) -> wrote 0
	Warning! out of bounds tile 24 @ 77 (5, 6) -> wrote 0
	Warning! out of bounds tile 25 @ 77 (9, 6) -> wrote 0
	Warning! out of bounds tile 24 @ 85 (3, 2) -> wrote 0
	Warning! out of bounds tile 24 @ 85 (4, 2) -> wrote 0
	Warning! out of bounds tile 24 @ 88 (6, 3) -> wrote 0
	Warning! out of bounds tile 25 @ 88 (9, 3) -> wrote 0
	Warning! out of bounds tile 25 @ 84 (9, 6) -> wrote 0
	Warning! out of bounds tile 25 @ 84 (13, 6) -> wrote 0
	Warning! out of bounds tile 25 @ 91 (11, 1) -> wrote 0
	Warning! out of bounds tile 24 @ 92 (4, 1) -> wrote 0
	Warning! out of bounds tile 25 @ 92 (5, 1) -> wrote 0
	Warning! out of bounds tile 25 @ 91 (11, 5) -> wrote 0
	Warning! out of bounds tile 26 @ 92 (6, 5) -> wrote 0
	Warning! out of bounds tile 25 @ 94 (5, 5) -> wrote 0
	Warning! out of bounds tile 24 @ 93 (13, 6) -> wrote 0
	Warning! out of bounds tile 24 @ 99 (3, 1) -> wrote 0
	Warning! out of bounds tile 25 @ 99 (4, 1) -> wrote 0
	Warning! out of bounds tile 24 @ 98 (13, 2) -> wrote 0
	Warning! out of bounds tile 24 @ 101 (3, 3) -> wrote 0
	Warning! out of bounds tile 24 @ 102 (9, 3) -> wrote 0
	Warning! out of bounds tile 24 @ 102 (12, 3) -> wrote 0
	Warning! out of bounds tile 26 @ 98 (3, 6) -> wrote 0
	Warning! out of bounds tile 24 @ 98 (13, 6) -> wrote 0
	Warning! out of bounds tile 25 @ 103 (6, 6) -> wrote 0
	Warning! out of bounds tile 25 @ 103 (8, 6) -> wrote 0
```

Estoy pensando que una buena ampliación para el conversor es que, si se añade cierto parámetro, estos warnings te los saque en un formato reutilizable, en tres listas de números (np, x, y) que luego se puedan meter en el código. Mejor así:

```c
	// Errors as arrays
	unsigned char _np [] = { 40,  40,  40,  44,  44,  55,  57,  61,  63,  67,  70,  74,  73,  73,  75,  76,  71,  71,  82,  77,  77,  85,  85,  88,  88,  84,  84,  91,  92,  92,  91,  92,  94,  93,  99,  99,  98, 101, 102, 102,  98,  98, 103, 103, };
	unsigned char _t [] = { 16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  24,  25,  24,  25,  26,  26,  25,  25,  24,  24,  25,  24,  24,  24,  25,  25,  25,  25,  24,  25,  25,  26,  25,  24,  24,  25,  24,  24,  24,  24,  26,  24,  25,  25, };
	unsigned char _x [] = {  6,   4,   2,   1,   5,  12,   3,   9,   4,   3,   7,   1,   2,   5,  14,   0,   3,   9,   3,   5,   9,   3,   4,   6,   9,   9,  13,  11,   4,   5,  11,   6,   5,  13,   3,   4,  13,   3,   9,  12,   3,  13,   6,   8, };
	unsigned char _y [] = {  3,   5,   7,   9,   9,   9,   9,   9,   9,   9,   2,   4,   5,   5,   5,   5,   6,   6,   0,   6,   6,   2,   2,   3,   3,   6,   6,   1,   1,   1,   5,   5,   5,   6,   1,   1,   2,   3,   3,   3,   6,   6,   6,   6, };
```

Sólo me tengo que quedar con los >= 24 de esos arrays para construir esto:

```c 
	#define ESTRUJATORS_MAX 34
	unsigned char estr_n_pant [] = { 
		 70,  74,  73,  73,  75,  76,  71,  71,  
		 82,  77,  77,  85,  85,  88,  88,  84,  
		 84,  91,  92,  92,  91,  92,  94,  93,  
		 99,  99,  98, 101, 102, 102,  98,  98, 
		103, 103 
	};
	unsigned char estr_t []      = {
		  0,   1,   0,   1,   2,   2,   1,   1,
		  0,   0,   1,   0,   0,   0,   1,   1,
		  1,   1,   0,   1,   1,   2,   1,   0,
		  0,   1,   0,   0,   0,   0,   2,   0,
		  1,   1 
	};
 	unsigned char estr_x []      = {
 		  7,   1,   2,   5,  14,   0,   3,   9,
 		  3,   5,   9,   3,   4,   6,   9,   9, 
 		 13,  11,   4,   5,  11,   6,   5,  13,
 		  3,   4,  13,   3,   9,  12,   3,  13,
 		  6,   8
 	};
	unsigned char estr_y []      = {  
		  2,   4,   5,   5,   5,   5,   6,   6,
		  0,   6,   6,   2,   2,   3,   3,   6, 
		  6,   1,   1,   1,   5,   5,   5,   6, 
		  1,   1,   2,   3,   3,   3,   6,   6, 
		  6,   6
	};
```

A lo que añadimos estos parámetros que definen a los estrujadores. ¿Hago un plugin con esto? Seh. Estos valores de configuración son para 50 fps (los usaré en una futura versión tostadera). Los chac chacs tienen N estados, y para cada estado se pintan con tres tiles t1, t2, t3. Cada estado durará lo que dig `chac_chac_times` y se pintará con `chac_chac_t1`, `chac_chac_t2` y `chac_chac_t3` uno encima del otro. Nosotros tenemos los tiles 20, 21 y 22 con los distintos trozos que se usan para dibujar el estrujador en cada uno de sus seis estados.

```c
	#define CHAC_CHAC_MAX_STATES

	const unsigned char chac_chac_initial_times [] = {
		25, 50, 100
	};

	const unsigned char chac_chac_times [] = {
		0, 1, 1, 100, 16, 16
	};

	const unsigned char chac_chac_t1 [] = {
		20, 21, 22, 22, 22, 21
	};

	const unsigned char chac_chac_t2 [] = {
		 0,  0, 21, 22, 21,  0
	};

	const unsigned char chac_chac_t3 [] = {
		 0,  0,  0, 21,  0,  0
	};
```

Ajustados a CPC a 25 faps sería algo así:

```c
	#define CHAC_CHAC_MAX_STATES

	const unsigned char chac_chac_initial_times [] = {
		12, 25, 50
	};

	const unsigned char chac_chac_times [] = {
		0, 1, 1, 50, 8, 8
	};

	const unsigned char chac_chac_t1 [] = {
		20, 21, 22, 22, 22, 21
	};

	const unsigned char chac_chac_t2 [] = {
		 0,  0, 21, 22, 21,  0
	};

	const unsigned char chac_chac_t3 [] = {
		 0,  0,  0, 21,  0,  0
	};
```

Veamos, los `chac_chac_initial_times` son el tiempo para el estado 0 de cada tipo de chac-chac, o estrujador, que en este juego serán los tipos 0, 1 y 2.

Los arrays `estr_?` digamos que son el "store". Aparte hace falta un set de arrays para los que están en la pantalla, que se deberían rellenar en `entering_screen.h`. Estos arrays y variables serían:

```c
	#define CHAC_CHAC_MAX 4
	unsigned char chac_chac_idx;					// Index / # of chac chacs on screen
	unsigned char chac_chac_x [CHAC_CHAC_MAX]; 
	unsigned char chac_chac_y [CHAC_CHAC_MAX];  	// x, y coordinates
	unsigned char chac_chac_state [CHAC_CHAC_MAX]; 	// Current state (0..CHAC_CHAC_MAX_STATES-1)
	unsigned char chac_chac_idle [CHAC_CHAC_MAX]; 	// Time to wait in state 0
	unsigned char chac_chac_ct [CHAC_CHAC_MAX]; 	// Frame counter, wait N frames
```

En la inicialización se rellenan `chac_chac_x` y `chac_chac_y`, se ponen los `chac_chac_state` a `CHAC_CHAC_MAX_STATES - 1`, se rellenan los `chac_chac_idle` y se ponen los `chac_chac_ct` a 0 y listo.

Durante el juego, se decrementan los `chac_chac_ct`. Al llegar a 0 se incrementa el estado y se asigna el `chac_chac_times` correspondiente a `chac_chac_ct` excepto si el estado es 0, en cuyo caso se establece a `chac_chac_idle`. Se manda pintar el `chac_chac` en el estado que sea.

Estaba pensando en hacerlo en ensamble pero es que si lo hago en C me vale para tostar pan luego, así que por ahora lo voy a hacer en C a ver y luego ya si eso ya.

Lo he montado todo como un plugin que habrá que enganchar debidamente. El plugin es totalmente agnóstico de cómo se almacenen los chac chacs, así podré por ejemplo meterlos en el mapa directamente en otras implementaciones. Lo único que necesita es que se llame a `chac_chacs_add` con `_x, _y` indicando donde crearlo y `_t` indicando el tipo. Hay que acordarse de poner `chac_chac_idx` a 0 cada vez, ofc.

Por tanto, mi enganche en `entering_screen.h` podría ser algo así como (para `gm == 2`, of course):

```c
	for (gpit = 0; gpit < ESTRUJATORS_MAX; gpit ++) {
		if (n_pant == estr_n_pant) {
			_x = estr_x [gpit]; _y = estr_y [gpit]; _t = estr_t [gpit];
			chac_chacs_add ();
		}
	}
```

Y en `extra_routines.h` sólo tendría que llamar (para `gm == 2`):

```c
	chac_chacs_do ();
```

## Niveles en secuencia

Hacer niveles custom en MK1v4 es mucho más fácil que en v5. Vamos a ver qué formas tenemos de engañar al chamán. A grandes rasgos, y esquemáticamente, esto es el bucle de MK1v5:

* Pantalla de título
* `my/ci/before_game.h`
* `game_loop.h`
* `if (success) game_ending (); else game_over ();`
* `my/ci/after_game.h`

Con esto podríamos montar algo así:

- En `before_game.h` se pone `gm` a 0 y se abre un loop. Al principio de este loop se preparan las cosas del nivel.
- Entonces ocurre el bucle de juego, que se acaba al morir (`success == 0` o al terminar la fase `success == 1`).
- En `game_ending` mostramos "stage clear" e incrementamos `gm`. Cuando valga 3, mostramos la pantalla final y hacemos un `break`, que saldría del bucle que abrimos en `before_game`.
- En `game_over` mostramos "game over" y permitimos continuar. Si NO continuamos, hacemos un `break`, que saldría del bucle que abrimos en `before_game`. 
- En `after_game.h` se cierra el bucle (con un confusísimo `}` )

¡MENOS MAL QUE LO HE DOCUMENTADO!

