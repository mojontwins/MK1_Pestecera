; ******************************************************
; **       Librería de rutinas para Amstrad CPC       **
; **	   Raúl Simarro, 	  Artaburu 2007       **
; ******************************************************

; Cambio radical al tema de los tiles tocados marca ACME (Actualización de 
; Código Mojona Eructo) by na_th_an

; Ahora en lugar de haber una lista de tiles tocados, tenemos un bitfield. El
; bitfield se ubica a partir de `tiles_tocados` y ocupa 96 bytes, con 1 bit 
; para cada uno de las 768 casillas.

; Ahora no se recorrerá una lista de parejas X, Y, sino que debe recorrerse el
; bitfield y ejecutarse la rutina de actualización para cada bit a 1.

INCLUDE "CPCconfig.def"

XLIB cpc_UpdScr	

XREF tiles_tocados
XREF pantalla_juego
XREF posicion_inicial_superbuffer
XREF tiles

IF PASARPORDETRAS
	XREF behindtilemasks
ENDIF

.cpc_UpdScr
	ld  hl, tiles_tocados
	ld  (_tiles_tocados_ptr), hl

	ld  hl, pantalla_juego					; the nametable (aligned)
	ld  de, posicion_inicial_superbuffer	; frame buffer (aligned)

	ld  b, 24 								; 24 lines

.main_loop
	push bc

	call process_touched_byte
	call process_touched_byte
	call process_touched_byte
	call process_touched_byte

	; Next line in superbuffer
	ld  e, 0
	inc d
	inc d

	pop  bc
	djnz main_loop

	ret

._tiles_tocados_ptr
	defw 0

.process_touched_byte

	; Read byte from pointer
	
	ld bc, (_tiles_tocados_ptr)
	ld  a, (bc)
	inc bc
	ld  (_tiles_tocados_ptr), bc

	bit 0, a
	jr  z, bit0_skip
	call ucopyTile
.bit0_skip
	inc l 									; Next pos. in nametable
	inc e
	inc e 									; Next pos. in superbuffer

	bit 1, a
	jr  z, bit1_skip
	call ucopyTile
.bit1_skip
	inc l 									; Next pos. in nametable
	inc e
	inc e 									; Next pos. in superbuffer

	bit 2, a
	jr  z, bit2_skip
	call ucopyTile
.bit2_skip
	inc l 									; Next pos. in nametable
	inc e
	inc e 									; Next pos. in superbuffer

	bit 3, a
	jr  z, bit3_skip
	call ucopyTile
.bit3_skip
	inc l 									; Next pos. in nametable
	inc e
	inc e 									; Next pos. in superbuffer

	bit 4, a
	jr  z, bit4_skip
	call ucopyTile
.bit4_skip
	inc l 									; Next pos. in nametable
	inc e
	inc e 									; Next pos. in superbuffer

	bit 5, a
	jr  z, bit5_skip
	call ucopyTile
.bit5_skip
	inc l 									; Next pos. in nametable
	inc e
	inc e 									; Next pos. in superbuffer

	bit 6, a
	jr  z, bit6_skip
	call ucopyTile
.bit6_skip
	inc l 									; Next pos. in nametable
	inc e
	inc e 									; Next pos. in superbuffer

	bit 7, a
	jr  z, bit7_skip
	call ucopyTile
.bit7_skip
	inc hl 									; N.p. nametable (may of)
	inc e
	inc de 									; N.p. superbuffer (of)

	ret

.ucopyTile

	push hl
	push de
	;push bc
	push af

IF PASARPORDETRAS

	; Read tile from nametable, break if FG tile

	ld  a, (hl)
	exx
	ld  l, a
	ld  h, 0
	ld  bc, behindtilemasks
	add hl, bc
	ld  a, (hl)
	or  a
	exx
	jr  nz, skeep

ENDIF

	; Read which tile from nametabe, get pointer in HL
	ld  l, (hl)
	ld  h, 0

	add hl, hl
	add hl, hl
	add hl, hl
	add hl, hl
	ld  bc, tiles
	add hl, bc

.transferir_map_sbuffer_grey
	
	; Thanks Augusto Ruiz, Syx, Fran Gallego for the hints

	; Address is D        E
	;            -------y yyxxxxxxx

	; Gray order is 0 1 3 2 6 7 5 4


	; First row 0: DE = -------0 00xxxxxx
	ldi 
	ldi

	;       row 1: DE = -------0 01xxxxxx, copy <-
	dec e
	set 6, e
	ld  a, (hl)
	ld  (de), a
	inc hl
	dec e
	ld  a, (hl)
	ld  (de), a
	inc hl

	;       row 3: DE = -------0 11xxxxxx,
	set 7, e
	ldi
	ldi

	;       row 2: DE = -------0 10xxxxxx, copy <-
	dec de
	res 6, e
	ld  a, (hl)
	ld  (de), a
	inc hl
	dec e
	ld  a, (hl)
	ld  (de), a
	inc hl

	;       row 6: DE = -------1 10xxxxxx
	set 0, d
	ldi 
	ldi

	;       row 7: DE = -------1 11xxxxxx, copy <-
	dec e
	set 6, e
	ld  a, (hl)
	ld  (de), a
	inc hl
	dec e
	ld  a, (hl)
	ld  (de), a
	inc hl

	;       row 5: DE = -------1 01xxxxxx
	res 7, e
	ldi
	ldi

	;       row 4: DE = -------1 00xxxxxx, copy <-
	dec e
	res 6, e
	ld  a, (hl)
	ld  (de), a
	inc hl
	dec e
	ld  a, (hl)
	ld  (de), a
	;inc hl

.skeep

	pop af
	;pop bc
	pop de
	pop hl

	ret
