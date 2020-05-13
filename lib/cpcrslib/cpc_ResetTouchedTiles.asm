; ******************************************************
; **       Librería de rutinas para Amstrad CPC       **
; **	   Raúl Simarro, 	  Artaburu 2007           **
; ******************************************************

; Cambio radical al tema de los tiles tocados marca ACME (Actualización de 
; Código Mojona Eructo) by na_th_an

; Ahora en lugar de haber una lista de tiles tocados, tenemos un bitfield. El
; bitfield se ubica a partir de `tiles_tocados` y ocupa 96 bytes, con 1 bit 
; para cada uno de las 768 casillas.

; Esta rutina pone el bitfield a 0

XLIB cpc_ResetTouchedTiles
XREF tiles_tocados
 
.cpc_ResetTouchedTiles

	ld  hl, tiles_tocados
	ld  de, tiles_tocados + 1
	ld  bc, 95
	ld  (hl), 0
	ldir

	ret 
