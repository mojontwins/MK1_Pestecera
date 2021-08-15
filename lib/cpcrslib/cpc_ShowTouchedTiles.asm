; ******************************************************
; **       Librería de rutinas para Amstrad CPC       **
; **	   Raúl Simarro, 	  Artaburu 2007           **
; ******************************************************

; Cambio radical al tema de los tiles tocados marca ACME (Actualización de 
; Código Mojona Eructo) by na_th_an

; Ahora en lugar de haber una lista de tiles tocados, tenemos un bitfield. El
; bitfield se ubica a partir de `tiles_tocados` y ocupa 96 bytes, con 1 bit 
; para cada uno de las 768 casillas.

; Ahora no se recorrerá una lista de parejas X, Y, sino que debe recorrerse el
; bitfield y ejecutarse la rutina de actualización para cada bit a 1.

INCLUDE "CPCconfig.def"

XLIB cpc_ShowTouchedTiles

XREF tiles_tocados

XREF posiciones_super_buffer
XREF posiciones_pantalla

XREF posicion_inicial_area_visible
XREF posicion_inicial_superbuffer
XREF ancho_pantalla_bytes
XREF alto_pantalla_bytes

IF PASARPORDETRAS
	XREF behindtilemasks
	XREF tiles
	XREF pantalla_juego				; Buffer pantalla
ENDIF

.cpc_ShowTouchedTiles

IF PASARPORDETRAS
	ld  ix, pantalla_juego
ENDIF

	ld  hl,tiles_tocados
	ld  b, 96
	ld  de, 0 			; (x, y) = (0, 0)

.bucle_cpc_ShowTouchedTiles	
	; Unrolled
	ld  a, (hl)
	or  a
	jr  nz, process

	ld  a, e
	add 8
	ld  e, a

IF PASARPORDETRAS
	push bc
	ld  bc,8
	add ix, bc
	pop bc
ENDIF

	jr skipall

.process

	push bc
	push hl

	; A contains a bitfield

	bit 0, a
	call checkbit

	bit 1, a
	call checkbit

	bit 2, a
	call checkbit

	bit 3, a
	call checkbit

	bit 4, a
	call checkbit

	bit 5, a
	call checkbit

	bit 6, a
	call checkbit

	bit 7, a
	call checkbit

	pop hl
	pop bc

.skipall
	ld  a, e
	cp  32
	jr  nz, noincd

	inc d
	ld  e, 0

.noincd
	inc hl

	djnz bucle_cpc_ShowTouchedTiles
	ret

.checkbit
	jp  z, checkbit_done

.copyTile
	; copia el tile en (x, y) = E, D.

	push af
	push de

.posicionar_superbuffer
	; Superbuffer is 64 bytes per row*8
	; Position is sb + 512*D + 2*E
	
	sla d 						; need this later
	sla e
	ld  hl, posicion_inicial_superbuffer
	add hl, de
	; HL -> posición en superbuffer


	PUSH HL 					; Guardamos HL.

.posicionar_pantalla
	; Buscamos la dirección de pantalla

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
	
.transf_bloque_sb_pantalla
	POP DE 						; Sacamos posición en superbuffer a DE

	; Unrolled
	ex de, hl 					; de->pantalla, hl->buffer

IF PASARPORDETRAS
	exx
	ld  l, (ix + 0)
	ld  h, 0
	ld  bc, behindtilemasks
	add hl, bc
	ld  a, (hl)
	exx
	or  a
	jr  z, copycell

.copybgtile
	ld  l, (ix + 0)
	ld  h, 0
	add hl, hl
	add hl, hl
	add hl, hl
	add hl, hl
	ld  bc, tiles
	add hl, bc

	; Tiles are grey zigzag so . . .
	; Gray order is 0 1 3 2 6 7 5 4
	
	; 0, forwards
	;    76543210 76543210
	; DE --000--- --------

	ldi
	ld  a, (hl)
	ld  (de), a
	inc hl 

	; 1, backwards
	;    76543210 76543210
	; DE --001--- --------

	set 3, d
	ld  a, (hl)
	ld  (de), a
	inc hl
	dec e
	ld  a, (hl)
	ld  (de), a
	inc hl

	; 3, forwards
	;    76543210 76543210
	; DE --011--- --------

	set 4, d
	ldi
	ld  a, (hl)
	ld  (de), a
	inc hl

	; 2, backwards
	;    76543210 76543210
	; DE --010--- --------

	res 3, d
	ld  a, (hl)
	ld  (de), a
	inc hl
	dec e
	ld  a, (hl)
	ld  (de), a
	inc hl

	; 6, forwards
	;    76543210 76543210
	; DE --110--- --------

	set 5, d
	ldi
	ld  a, (hl)
	ld  (de), a
	inc hl

	; 7, backwards
	;    76543210 76543210
	; DE --111--- --------

	set 3, d
	ld  a, (hl)
	ld  (de), a
	inc hl
	dec e
	ld  a, (hl)
	ld  (de), a
	inc hl

	; 5, forwards
	;    76543210 76543210
	; DE --101--- --------

	res 4, d
	ldi
	ld  a, (hl)
	ld  (de), a
	inc hl

	; 4, backwards
	;    76543210 76543210
	; DE --100--- --------

	res 3, d
	ld  a, (hl)
	ld  (de), a
	inc hl
	dec e
	ld  a, (hl)
	ld  (de), a
	


	jr copycell_done

.copycell
ENDIF

	; Copy buffer to screen grey zig zag
	; Gray order is 0 1 3 2 6 7 5 4
	
	; 0, forwards
	;    76543210 76543210
	; HL -------0 00------
	; DE --000--- --------

	ldi
	ld  a, (hl)
	ld  (de), a

	; 1, backwards
	;    76543210 76543210
	; HL -------0 01------
	; DE --001--- --------

	set 6, l
	set 3, d
	ldd
	ld  a, (hl)
	ld  (de), a

	; 3, forwards
	;    76543210 76543210
	; HL -------0 11------
	; DE --011--- --------

	set 7, l
	set 4, d
	ldi
	ld  a, (hl)
	ld  (de), a

	; 2, backwards
	;    76543210 76543210
	; HL -------0 10------
	; DE --010--- --------

	res 6, l
	res 3, d
	ldd
	ld  a, (hl)
	ld  (de), a

	; 6, forwards
	;    76543210 76543210
	; HL -------1 10------
	; DE --110--- --------

	set 0, h
	set 5, d
	ldi
	ld  a, (hl)
	ld  (de), a

	; 7, backwards
	;    76543210 76543210
	; HL -------1 11------
	; DE --111--- --------

	set 6, l
	set 3, d
	ldd
	ld  a, (hl)
	ld  (de), a

	; 5, forwards
	;    76543210 76543210
	; HL -------1 01------
	; DE --101--- --------

	res 7, l
	res 4, d
	ldi
	ld  a, (hl)
	ld  (de), a

	; 4, backwards
	;    76543210 76543210
	; HL -------1 00------
	; DE --100--- --------

	res 6, l
	res 3, d
	ldd
	ld  a, (hl)
	ld  (de), a


.copycell_done

	pop de
	pop af

.checkbit_done
	inc e
	inc ix
	ret
