# Phantomas en el museo

Se trata de pasar lo que hay a MK1 y crear módulos reutilizables para plataformeros sin inercia.

Este juego tenía varias cosas puestas directamente sobre el mapa que tendré que recolocar:

## Objetos

|Tile|n_pant|X|Y
|---|---|---|---
|41|4|4|6
|42|30|10|2
|43|19|4|8
|44|14|12|4
|45|1|12|3

## El movimiento

Para programar desde 0 todo el movimiento primero hay que preparar el motor:

```c
	//#define PLAYER_HAS_JUMP 		
	//#define PLAYER_HAS_JETPAC 	
	//#define PLAYER_BOOTEE 		
	#define PLAYER_DISABLE_GRAVITY				// Disable gravity. Advanced.

	[...]
	#define PLAYER_DISABLE_DEFAULT_HENG 		// To disble default horizontal engine (keyrs)
```

## Script

El tema de los objetos se puede hacer de mil formas, por ejemplo usando hotspots custom. Pero vamos a hacerlo mediante scripting por eso de ser didácticos.


## Angel -> dudas y mierdas

He puesto el hotspot 3 que es el de recargar energía pero como el tile está ocupado por escenario, sale ese tile.

El enemigo 4 no es una plataforma, es malo, y cuando te pones encima luego no te puedes mover.

