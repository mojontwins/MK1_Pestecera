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

; Si CHURRERA_CLIPPING, se comprueba que el rectángulo que se quiere marcar
; esté en el area de juego.

INCLUDE "CPCconfig.def"

XLIB cpc_UpdTileTable		; marca un tile indicando las coordenadas del tile
XDEF cpc_UpdTileTableClp	; con clipping (si se activa)

LIB cpc_Bit2Mask, cpc_TblLookup
XREF tiles_tocados

IF CHURRERA_CLIPPING
	XREF viewport_x, viewport_y
ENDIF 

.cpc_UpdTileTableClp	
	; D = y
	; E = x

	IF CHURRERA_CLIPPING

		ld  a, d
		cp  viewport_y
		ret c 				; Y < viewport_Y

		cp  viewport_y+20
		ret nc 				; Y >= viewport_y+20

		ld  a, e
		cp  viewport_x
		ret c 				; A < viewport_x

		cp  viewport_x+30
		ret nc 				; A >= viewport_x+30
		
	ENDIF

.cpc_UpdTileTable
	ld  b, d
	ld  c, e

	sla d 				; Y * 2
	sla d 				; Y * 4

	ld  l, d
	ld  h, 0 			; HL = Y*4

	ld  a, e 			; X
	and $07				; A = X & 7 (bit mask)

	srl e
	srl e
	srl e 				; E = X\8

	ld  d, 0 			; DE = X\8
	add hl, de 			; HL = X\8 + Y*4

	ld  de, tiles_tocados
	add hl, de

	ld  de, cpc_Bit2Mask
	call cpc_TblLookup	; A = bit mask

	or  (hl) 			; A = bit mask | [tiles_tocados + x / 8 + y * 4]
	ld  (hl), a

	ld  d, b
	ld  e, c

	ret
