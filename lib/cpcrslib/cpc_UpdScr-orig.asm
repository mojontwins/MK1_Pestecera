; ******************************************************
; **       Librería de rutinas para Amstrad CPC       **
; **	   Raúl Simarro, 	  Artaburu 2007       **
; ******************************************************



XLIB cpc_UpdScr	

XREF tiles_tocados
XREF pantalla_juego
XREF posiciones_super_buffer
XREF tiles

XREF ancho_pantalla_bytes

.cpc_UpdScr
	;lee la tabla de tiles tocados 
	; y va restaurando cada uno en su sitio.

	LD IX,tiles_tocados
.bucle_cpc_UpdScr	
	LD E,(IX+0)
	LD A,$FF
	CP E
	RET Z		;RETORNA SI NO HAY MÁS DATOS EN LA LISTA
	LD D,(IX+1)
	INC IX
	INC IX

.posicionar_superbuffer 

	LD c,D
	SLA c
	
	LD B,0
	LD HL,posiciones_super_buffer
	ADD HL,BC
	LD C,(HL)
	INC HL
	LD B,(HL)	; BC -> Inicio linea en superbuffer
	
	LD l,E
	SLA l
	LD H,0		; HL -> Columna en bytes
	
	ADD HL,BC 	; HL -> Posición en superbuffer

	push hl 	; Lo guardamos.
	
.posicionar_tile	

	; D = Y; E = X.

	;ld a,e
	;ld e,d

	;include "multiplication2.asm"

	ld l, d
	ld h, 0
	add hl, hl
	add hl, hl
	add hl, hl
	add hl, hl
	add hl, hl

	; Aquí HL = Y * 32

	LD D,0

	; DE = X

	ADD HL,DE

	; Aquí HL = Y * 32 + X
	
	LD DE,pantalla_juego
	ADD HL,DE

	; Aquí HL apunta al tile correcto dentro
	; del nametable (pantalla_juego)
	
	LD L,(HL)
	LD H,0

	; Aquí HL contiene el número de tile en esa pos.

	ADD HL,HL
	ADD HL,HL
	ADD HL,HL
	ADD HL,HL	;X16
	LD DE,tiles
	ADD HL,DE

	; Aquí HL apunta a los gráficos del tile.
	
	pop de 		; Recuperamos la posición en el superbuffer
				; Que almacenamos antes.

	; HL -> Gráfico del tile
	; DE -> Superbuffer

.transferir_map_sbuffer	
	ld bc,ancho_pantalla_bytes-2 ;63
	ldi
	ldi
	ex de,hl
	ld c,ancho_pantalla_bytes-2
	add HL,BC	
		ex de,hl
	ldi
	ldi
	ex de,hl
	ld c,ancho_pantalla_bytes-2
	add HL,BC	
		ex de,hl
	ldi
	ldi
	ex de,hl
	ld c,ancho_pantalla_bytes-2
	add HL,BC	
		ex de,hl
	ldi
	ldi
	ex de,hl
	ld c,ancho_pantalla_bytes-2
	add HL,BC	
		ex de,hl
	ldi
	ldi
	ex de,hl
	ld c,ancho_pantalla_bytes-2
	add HL,BC	
		ex de,hl
	ldi
	ldi
	ex de,hl
	ld c,ancho_pantalla_bytes-2
	add HL,BC	
		ex de,hl
	ldi
	ldi
	ex de,hl
	ld c,ancho_pantalla_bytes-2
	add HL,BC	
		ex de,hl
	ldi
	ldi

jp bucle_cpc_UpdScr

