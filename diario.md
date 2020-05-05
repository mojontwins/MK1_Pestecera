20200426
========

A ver si poco a poco voy venciendo la desidia que me embarga. Vamos a empezar este proyecto tan bonito de portar la Churrera V5 a CPC. 

Lo he estado pensando mucho y voy a portar esto con algo sencillo y que tenga pocos visos de fallar: Lala Prologue. Lo primero es hacer acopio de material. Lo segundo será conseguir importar todos los assets (cambiando la importación de los gráficos al modo pestecé). Lo tercero será construir el juego sin sonido. Y por último integrar WYZ Player.

Para convertir LALA, que es en modo 1, tendré que añadir soporte para este en `mkts_om`.

20200505
========

Ya hice la conversión en modo 1 (la cual no sé si funcionará correctamente, pero tengo que seguir adelante). También he pasado todo el set gráfico de Lala Prologue a CPC en modo 1. No sé si las historias que hice en CPCRSLIB funcionarán en modo 1, pero deberían. 

El tema del modo 1 es que para simplificar estoy haciendo sprites de 3 colores, y el color 0 es el transparente. En este juego he puesto rojo oscuro como color 0 porque es el color que no se usa en los sprites.

Vamos a sustituir todos los conversores gráficos en compile.bat para obtener todos los tiestos que necesito en el formato de CPC.

## Tileset

Tengo que recortar un charset y un tileset:

```
	..\utils\mkts_om.exe platform=cpc cpcmode=1 pal=..\gfx\pal.png mode=chars in=..\gfx\font.png out=..\bin\font.bin silent
	..\utils\mkts_om.exe platform=cpc cpcmode=1 pal=..\gfx\pal.png mode=strait2x2 in=..\gfx\work.png out=..\bin\work.bin silent
```

## Spriteset

Haremos como en Spectrum aunque no tengan máscaras: los sets serán, por convención, de 8 cells de ancho. Como estamos en Modo 1, tendremos 128x32 píxels. En modo 0 serán 64x32 (o más si hay sprites extra).

```
	..\utils\mkts_om.exe platform=cpc cpcmode=1 pal=..\gfx\pal.png mode=sprites in=..\gfx\sprites.png out=..\bin\sprites.bin silent
```

Y los sprites extra:

```
	..\utils\mkts_om.exe platform=cpc cpcmode=1 pal=..\gfx\pal.png mode=sprites in=..\gfx\sprites_extra.png out=..\bin\sprites_extra.bin silent > nul
	..\utils\mkts_om.exe platform=cpc cpcmode=1 pal=..\gfx\pal.png mode=sprites in=..\gfx\sprites_bullet.png out=..\bin\sprites_bullet.bin metasize=1,1 silent > nul
```

## Pantallas fijas

