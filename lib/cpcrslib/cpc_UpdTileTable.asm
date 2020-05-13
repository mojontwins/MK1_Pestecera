; ******************************************************
; **       Librería de rutinas para Amstrad CPC       **
; **	   Raúl Simarro, 	  Artaburu 2007           **
; ******************************************************

; Cambio radical al tema de los tiles tocados marca ACME (Actualización de 
; Código Mojona Eructo) by na_th_an

; Ahora en lugar de haber una lista de tiles tocados, tenemos un bitfield. El
; bitfield se ubica a partir de `tiles_tocados` y ocupa 96 bytes, con 1 bit 
; para cada uno de las 768 casillas.

; Esta rutina `toca` una casilla (con amor). La he hecho compatible con lo
; que había, así que recibirá (x, y) en los registros E, D. Tendremos que 
; ubicar el byte en `tiles_tocados + y * 4 + x / 8` y levantar el bit `x & 7`.

XLIB cpc_UpdTileTable		;marca un tile indicando las coordenadas del tile
LIB cpc_Bit2Mask, cpc_TblLookup
XREF tiles_tocados

.cpc_UpdTileTable	
	; D = y
	; E = x

	ld  a, d
	sla a
	sla a 				; y = 0-23, 23*4 fits in a byte.
	ld  b, a 			; B = y * 4

	ld  a, e
	srl a
	srl a
	srl a 				; x / 8

	add b 				; A = x / 8 + y * 4

	ld  hl, tiles_tocados
	ld  b, 0
	ld  c, a 			; BC = x / 8 + y * 4
	add hl, bc 			; HL = tiles_tocados + x / 8 + y * 4

	ld  a, e 			; A = x
	ld  de, cpc_Bit2Mask
	call cpc_TblLookup	; A = bit mask

	or  (hl) 			; A = bit mask | [tiles_tocados + x / 8 + y * 4]
	ld  (hl), a

	ret
