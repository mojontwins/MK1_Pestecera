; ******************************************************
; **       Librería de rutinas para Amstrad CPC       **
; **	   Raúl Simarro, 	  Artaburu 2007, 2010     **
; ******************************************************

; Simplificado y adaptado a 32x24 por na_th_an

	XLIB cpc_ShowTileMap

	XREF tiles
	XREF pantalla_juego		
	XREF posiciones_super_buffer		
	XREF posicion_inicial_area_visible
	XREF posicion_inicial_superbuffer
	XREF ancho_pantalla_bytes
	XREF ancho_pantalla_bytes_visible
	XREF alto_pantalla_bytes
	XREF posiciones_pantalla

.cpc_ShowTileMap
	; HL = 1 si solo tengo que volcar superbuffer
	ld 	a, l
	or  a
	jp  nz, soloCopia

	xor a
	ld (contador_tiles),a

	; Número de tiles en pantalla	
	ld hl, 768
	ld (contador_tiles2), hl

	; Render de la pantalla en el superbuffer
	ld hl, pantalla_juego
	call transferir_pantalla_a_superbuffer

.soloCopia
	; Copia del superbuffer a la pantalla
	ld 	hl, (posiciones_pantalla)
	ld 	de, posicion_inicial_superbuffer
	ld 	b,	ancho_pantalla_bytes_visible
	ld 	c,	alto_pantalla_bytes

	; Salta a la rutina que vuelca el superbuffer
	jp 	cpc_PutSp	

; -----------------------------
; Pantalla tiles -> Superbuffer
; -----------------------------
.transferir_pantalla_a_superbuffer
	
	; Transfiero HL -> IX
	PUSH HL
	POP	IX								; IX apunta a pantalla_juego
	LD	DE,	(posiciones_super_buffer)	; DE apunta a superbuffer

.bucle_dibujado_fondo
	; Calcular en HL la posición del tile que hay que pintar
	LD 	L,	(IX+0)
	LD  H,	0
	ADD HL,	HL							;x2
	ADD HL,	HL							;x4
	ADD HL,	HL							;x8
	ADD HL,	HL							;x16
	LD BC,	tiles
	ADD HL,	BC							; HL -> tile a transferir
	
	EX 	DE,HL 							; DE -> tile a transferir
										; HL -> superbuffer
	PUSH HL

	call transferir_map_sbuffer			; DE origen HL destino
	
	ld 	HL, (contador_tiles2)
	dec HL
	LD 	(contador_tiles2), HL
	LD 	A, H
	OR 	L

	pop HL
	ret z 								; Si se ha contado 768, fin

	INC IX								; Siguiente tile

	EX  DE,HL 							; DE -> superbuffer
										; HL -> tile a transferir

	LD A,(contador_tiles)
	CP ancho_pantalla_bytes/2-1 
	JP Z,incremento2					; Siguiente linea ?

	INC A
	LD (contador_tiles),A

	INC DE
	INC DE								; para pasar a la siguiente posición
	
	JP bucle_dibujado_fondo

.incremento2
	XOR A
	LD 	(contador_tiles),A 				; Resetear el contador de tiles
	LD 	BC, 7*ancho_pantalla_bytes+2 	; No entiendo esta cuenta, pero ok.
	EX 	DE,	HL
	ADD HL,	BC	
	EX 	DE,	HL
	JP bucle_dibujado_fondo

.contador_tiles 
	defb 0	
.contador_tiles2 
	defw 0	

.transferir_map_sbuffer	
	ld bc,ancho_pantalla_bytes-1 ;63
		
	defb $fD
   	LD H,8		;ALTO, SE PUEDE TRABAJAR CON HX DIRECTAMENTE

.loop_alto_map_sbuffer
.loop_ancho_map_sbuffer		
	ld A,(DE)
	ld (HL),A
	inc de
	inc hl
	ld A,(DE)
	ld (HL),A
	inc de

	defb $fD
	dec h
	ret z

	add HL,BC	
	jp loop_alto_map_sbuffer


; -----------------------
; Superbuffer -> Pantalla
; -----------------------

.cpc_PutSp	

	; 192 lineas
	ld 	b, 192

.loop_alto_2
	push bc 		; Guarda índice bucle externo
	;ld 	b, 64 		; B <- copiar 64 bytes

	; Copiamos una linea de bytes del superbuffer:
	push hl 		; Salvamos al principio de la linea
;.loop_ancho_2		
;	ld 	A,(DE)		; Lee un byte del superbuffer
;	ld 	(hl),a 		; Lo copia a la pantalla
;	inc de 
;	inc hl
;	djnz loop_ancho_2
	ld bc, 64
	ex de, hl
	ldir
	ex de, hl
	
	; Recuperamos el puntero al principio de la linea
	; Avanzamos a la linea siguiente, secuencialmente

	; Eso implica cambiar de "octavo" las siete primeras veces,
	; y de "linea" la octava.

	pop hl
	ld 	A, H
	add $08
	ld 	H, A 		; Sumarle $08 al MSB es cambiar de octavo.

	; $C0->$C8->$D0->$D8->$E0->$E8->$F0->$F8 --> $100, carry y saturación

	sub $C0
	jp 	nc,sig_linea_2

	ld 	bc,$c040	;; <--- Cambiamos aquí para la geometría diferente
					;; Era $c050 (80 bytes), ahora es $c040 (64 bytes).
	add HL,BC	
	
	.sig_linea_2

	pop BC 			; Recuperamos el índice externo
	djnz loop_alto_2

	ret
