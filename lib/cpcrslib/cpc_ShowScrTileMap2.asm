; ******************************************************
; **       Librería de rutinas para Amstrad CPC       **
; **	   Raúl Simarro, 	  Artaburu 2007       **
; ******************************************************

XLIB cpc_ShowTileMap2	;	para una pantalla de 64x160 bytes. Superbuffer 8192bytes
								;   los tiles son de 2x8 bytes

XREF tiles
XREF pantalla_juego					;datos de la pantalla, cada byte indica un tile
XREF posiciones_super_buffer		
XREF posicion_inicial_area_visible
XREF posicion_inicial_superbuffer
XREF ancho_pantalla_bytes

XREF alto_pantalla_bytes
XREF posiciones_pantalla


XREF tiles_ocultos_ancho0
XREF tiles_ocultos_alto0

XDEF posicion_inicio_pantalla_visible 
XDEF posicion_inicio_pantalla_visible_sb
XDEF posicion_inicio_pantalla_visible2

XREF cpc_PutSp
XDEF papa
XDEF creascanes

LIB cpc_ShowTileMap



.cpc_ShowTileMap2
	ld b,ancho_pantalla_bytes-4*(tiles_ocultos_ancho0)	;;nuevo ancho
	ld c,alto_pantalla_bytes-16*(tiles_ocultos_alto0)			;;nuevo alto
.posicion_inicio_pantalla_visible	
	ld hl,0000
	
	
.posicion_inicio_pantalla_visible_sb
	ld hl,0000
.papa		; código de Xilen Wars
	di
	ld	(auxsp),sp
	ld	sp,tablascan
	ld	a,alto_pantalla_bytes-16*(tiles_ocultos_alto0)	;16 alto
.ppv0
	pop	de		; va recogiendo de la pila!!
.inicio_salto_ldi	
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi
	ldi	
.CONT_salto_ldi	
	ld	de,4*tiles_ocultos_ancho0
	add	hl,de
	dec a
	jp nz, ppv0
	ld	sp,(auxsp)
	ei
	ret

.auxsp	defw	0	



.creascanes	
	ld	ix,tablascan
.posicion_inicio_pantalla_visible2
	ld	hl,0000
	ld	b, alto_pantalla_bytes/8-2*tiles_ocultos_alto0 ; 20	; num de filas. 
.cts0	
	push	bc
	push	hl
	ld	b,8
	ld	de,2048
.cts1	
	ld	(ix+0),l
	inc	ix
	ld	(ix+0),h
	inc	ix
	add	hl,de
	djnz	cts1
	pop	hl
	ld	bc,80
	add	hl,bc
	pop	bc
	djnz	cts0
;	jp prepara_salto_ldi
.prepara_salto_ldi		; para el ancho visible de la pantalla
	ld hl,ancho_pantalla_bytes-4*tiles_ocultos_ancho0
	ld de,inicio_salto_ldi 
	add hl,hl
	add hl,de
	ld (hl),$c3
	inc hl
	ld de,CONT_salto_ldi
	ld (hl),e
	inc hl
	ld (hl),d
	ret

.tablascan	defs 20*16  