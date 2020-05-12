; ******************************************************
; **       Librería de rutinas para Amstrad CPC       **
; **	   Raúl Simarro, 	  Artaburu 2007       **
; ******************************************************

XLIB cpc_ShowTouchedTiles2		;OK GENERICO

XREF tiles_tocados
XREF pantalla_juego					;datos de la pantalla, cada byte indica un tile
XREF posiciones_super_buffer
XREF posiciones_pantalla


XREF posicion_inicial_area_visible
XREF posicion_inicial_superbuffer
XREF ancho_pantalla_bytes
XREF alto_pantalla_bytes

XREF tiles_ocultos_ancho0
XREF tiles_ocultos_ancho1
XREF tiles_ocultos_alto0
XREF tiles_ocultos_alto1



.cpc_ShowTouchedTiles2
;recoge los tiles tocados y los envía desde el superbuffer a la pantalla

	LD IX,tiles_tocados
.bucle_cpc_ShowTouchedTiles	
	LD E,(IX+0)	;x

	LD A,$FF
	CP E
	RET Z		;RETORNA SI NO HAY MÁS DATOS EN LA LISTA
	
;; Comprueba si el tile está dentro del cuadrado visible
;; x>tiles_ocultos_ancho0 && x<tiles_ocultos_ancho1
;; y>tiles_ocultos_alto0 && y<tiles_ocultos_alto1
	LD D,(IX+1)	;y
	ld a,tiles_ocultos_ancho0-1
	cp e
	jp p,contkaka	;;dentro de area visible	e<a
	ld a,tiles_ocultos_ancho1
	cp e
	jp m,contkaka	;;dentro de area visible   e>=a
	ld a,tiles_ocultos_alto0-1
	cp d
	jp p,contkaka	;;dentro de area visible	e>a
	ld a,tiles_ocultos_alto1
	cp d
	jp m,contkaka	;;dentro de area visible   e<=a	
	
	; Si está en area visible, se actualiza la tabla
	
	

	
	
	INC IX
	INC IX
.posicionar_superbuffer
;con la coordenada y nos situamos en la posición vertical y con x nos movemos a su sitio definitivo
	;LD A,D
	SLA d
	LD C,d	;x2
	LD B,0
	LD HL,posiciones_super_buffer
	ADD HL,BC
	LD C,(HL)
	INC HL
	LD B,(HL)	
	
	;LD A,E
	SLA e
	LD L,e
	LD H,0
	ADD HL,BC
	;HL apunta a la posición correspondiente en superbuffer

	
.posicionar_pantalla
;con la coordenada y nos situamos en la posición vertical y con x nos movemos a su sitio definitivo
	PUSH HL


	;LD A,D
	;SLA D
	LD C,D	;x2
	LD B,0
	LD HL,posiciones_pantalla
	ADD HL,BC
	LD C,(HL)
	INC HL
	LD B,(HL)	
	;LD A,E
	;SLA e
	LD L,e
	LD H,0	
	ADD HL,BC
	;HL apunta a la posición correspondiente en superbuffer
	
.transf_bloque_sb_pantalla
	POP DE
	
	;ex de,hl
		;defb $fD
   		;LD H,8		;ALTO, SE PUEDE TRABAJAR CON HX DIRECTAMENTE
   		ld a,8
		;ld b,7
	.loop_alto_2
	   .ancho0
	   ex de,hl
	.loop_ancho_2		
		ldi
		ldi		
	   dec a
	   JP z,bucle_cpc_ShowTouchedTiles
		LD BC,ancho_pantalla_bytes-2 ;->hay que actualizar desplazamiento (desp+2)
		ADD HL,BC
		EX DE,HL
		LD bC,$07fe			;&07f6 
		ADD HL,BC
		jp nc,loop_alto_2 ;yep ;loop_alto_2 ;sig_linea_2zz		;si no desborda va a la siguiente linea
		ld bc,$c050
		add HL,BC
.yep		
		;EX DE,HL
		jp loop_alto_2	
.contkaka		
	INC IX
	INC IX
	jp bucle_cpc_ShowTouchedTiles