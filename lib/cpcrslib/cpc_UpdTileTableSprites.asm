; ******************************************************
; **       Librería de rutinas para Amstrad CPC       **
; **	   Raúl Simarro, 	  Artaburu 2007           **
; ******************************************************

INCLUDE "CPCconfig.def"

; Cambio radical al tema de los tiles tocados marca ACME (Actualización de 
; Código Mojona Eructo) by na_th_an

; Ahora en lugar de haber una lista de tiles tocados, tenemos un bitfield. El
; bitfield se ubica a partir de `tiles_tocados` y ocupa 96 bytes, con 1 bit 
; para cada uno de las 768 casillas.

; Esta rutina `toca` una casilla (con amor). La he hecho compatible con lo
; que había, así que recibirá (x, y) en los registros E, D. Tendremos que 
; ubicar el byte en `tiles_tocados + y * 4 + x / 8` y levantar el bit `x & 7`.

XLIB cpc_UpdTileTableSprites		;marca un tile indicando las coordenadas del tile
LIB cpc_Bit2Mask, cpc_TblLookup
XREF tiles_tocados

IF PASARPORDETRAS
XREF pantalla_juego
XREF behindtilemasks
XREF copytile
ENDIF

.cpc_UpdTileTableSprites	
	; D = y
	; E = x
	push de

	IF PASARPORDETRAS
		push de

		; Max. Y es 24, puedo multiplicar por 8 en 8 bits
		ld  a, d
		sla a
		sla a
		sla a
		ld  h, 0
		ld  l, a
		add hl, hl
		add hl, hl 

		ld  d, 0 	; DE = X
		add hl, de

		ld  de, pantalla_juego
		add hl, de
		ld  a, (hl)

		ld  de, behindtilemasks
		call cpc_TblLookup 	; A = tile is FG

		ld  b, a 			; B = tile is FG

		pop de
	ENDIF

	push de
	ld  a, d 			; Y
	add a, a
	add a, a

	ld  l, a
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
	pop de

	IF PASARPORDETRAS
		; Aquí, si (HL & A) este tile está invalidado.
		; En ese caso, pinto el fondo y valido.
		ld  c, a
		and (hl)
		ld  a, c
		jr  z, DoValInv

		; Pintar fondo
		push de
		call copyTile
		pop de


		xor a
		or  b
		ld  a, c
		jr  z, DoValInv

		cpl
		and (hl)
		jr DoValInvDone
	ENDIF

	.DoValInv
	or  (hl) 			; A = bit mask | [tiles_tocados + x / 8 + y * 4]
	.DoValInvDone

	ld  (hl), a

	pop de

	ret
