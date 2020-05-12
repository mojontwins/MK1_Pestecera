; ******************************************************
; **       Librería de rutinas para Amstrad CPC       **
; **	   Raúl Simarro, 	  Artaburu 2009       **
; ******************************************************

XLIB cpc_PutTiles		;pone un byte en la posición de la pantalla indicada

XREF pantalla_juego
XREF ancho_pantalla_bytes


XDEF captura

.cpc_PutTiles

	ld ix,2
	add ix,sp
	
	ld l,(ix+0)	
	ld h,(ix+1)	
	
	ld c,(ix+2)	;h
	;ld b,(ix+4)	;w

	ld e,(ix+6)	;y
	ld d,(ix+8)	;x	
	
	
	;lee el rectángulo y lo mueve al buffer
	
	.bucle_alto
	ld b,(ix+4)
	.bucle_ancho
	push de
	ld a,(hl)
	ld (tmp),a
	;e+c
	ld a,c
	add e
	ld e,a
	;d+b
	ld a,b
	add d
	push hl
	call captura
	ld a,(tmp)
	ld (hl),a
	pop hl
	inc hl		
	pop de	
	djnz bucle_ancho	
	
	dec c
	jp nz,bucle_alto
	ret

	;e=y
	;a=x
.tmp defb 0
	
.captura
		push bc
		dec a
		dec e
		include "multiplication2.asm"
		pop bc
		ld e,a
		ld d,0
		add hl,de		;SUMA X A LA DISTANCIA Y*ANCHO
		ld de,pantalla_juego
		add hl,de

		ret