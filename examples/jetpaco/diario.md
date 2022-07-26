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



