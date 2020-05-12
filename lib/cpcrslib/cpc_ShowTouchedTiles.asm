; ******************************************************
; **       Librería de rutinas para Amstrad CPC       **
; **	   Raúl Simarro, 	  Artaburu 2007           **
; ******************************************************

; [na_th_an] Modificada por Mojon Twins - ajustamos a la geometría de 32 columnas

XLIB cpc_ShowTouchedTiles

XREF tiles_tocados
XREF tiles_tocados_ptr
XREF pantalla_juego				; Buffer pantalla
XREF posiciones_super_buffer
XREF posiciones_pantalla

XREF posicion_inicial_area_visible
XREF posicion_inicial_superbuffer
XREF ancho_pantalla_bytes
XREF alto_pantalla_bytes

.cpc_ShowTouchedTiles
	; Recorre la lista de tiles tocados.
	; Copia esos tiles del superbuffer a la pantalla.

	; Marcar el final de la lista!
	;ld  hl, (tiles_tocados_ptr)
	;ld  (hl), $ff

	LD IX,tiles_tocados

.bucle_cpc_ShowTouchedTiles	
	LD E,(IX+0)					; Lee un byte de la lista (X)

	LD A,$FF
	CP E
	RET Z 						; Si es $FF, terminamos.

	LD D,(IX+1)					; La lista contiene pares (x,y) (Y)
	INC IX
	INC IX 						; Avanzamos al siguiente par.

.posicionar_superbuffer
	; Superbuffer is 64 bytes per row*8
	; Position is sb + 512*D + 2*E
	
	sla d 						; need this later
	sla e
	ld  hl, posicion_inicial_superbuffer
	add hl, de
	; HL -> posición en superbuffer


.posicionar_pantalla
	; Buscamos la dirección de pantalla

	PUSH HL 					; Guardamos HL.

	LD C,D						; Remember, D = Y*2
	LD B,0 						; BC = Y*2
	LD HL,posiciones_pantalla
	ADD HL,BC

	LD C,(HL)
	INC HL
	LD B,(HL)	 				; BC -> fila de tiles en pantalla

	LD L,e
	LD H,0						; HL = X*2
	ADD HL,BC 					; HL -> posición en pantalla
	;4+7+10+11+7+7+6+4+7+11
	
.transf_bloque_sb_pantalla
	POP DE 						; Sacamos posición en superbuffer a DE

	; Unrolled
	ex de, hl 					; de->pantalla, hl->buffer

	ldi
	ldi
	ld  bc, 62
	add hl, bc
	ex  de, hl
	ld  bc, $07fe
	add hl, bc
	ex  de, hl

	ldi
	ldi
	ld  bc, 62
	add hl, bc
	ex  de, hl
	ld  bc, $07fe
	add hl, bc
	ex  de, hl

	ldi
	ldi
	ld  bc, 62
	add hl, bc
	ex  de, hl
	ld  bc, $07fe
	add hl, bc
	ex  de, hl
	; 16+16+10+11+4+10+11+4=82

	ldi
	ldi
	ld  bc, 62
	add hl, bc
	ex  de, hl
	ld  bc, $07fe
	add hl, bc
	ex  de, hl

	ldi
	ldi
	ld  bc, 62
	add hl, bc
	ex  de, hl
	ld  bc, $07fe
	add hl, bc
	ex  de, hl

	ldi
	ldi
	ld  bc, 62
	add hl, bc
	ex  de, hl
	ld  bc, $07fe
	add hl, bc
	ex  de, hl

	ldi
	ldi
	ld  bc, 62
	add hl, bc
	ex  de, hl
	ld  bc, $07fe
	add hl, bc
	ex  de, hl

	ldi
	ldi

	jp bucle_cpc_ShowTouchedTiles
