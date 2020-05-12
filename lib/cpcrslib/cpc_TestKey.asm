; ******************************************************
; **       Librería de rutinas para Amstrad CPC       **
; **	   Raúl Simarro, 	  Artaburu 2007       **
; ******************************************************

XLIB cpc_TestKey

LIB cpc_TestKeyboard
;XREF linea_a_buscar

LIB cpc_KeysData
XREF  tabla_teclas

.cpc_TestKey

	SLA L
	inc l
	ld h,0
	ld de,tabla_teclas+cpc_KeysData

	add hl,de
	
	ld a,(HL)
	;ld (cpc_TestKeyboard+linea_a_buscar+1),a		;cambia la línea a explorar
	;XOR A
	call cpc_TestKeyboard		; esta rutina lee la línea del teclado correspondiente 
	DEC hl						; pero sólo nos interesa una de las teclas.
	and (HL) ;para filtrar por el bit de la tecla (puede haber varias pulsadas)
	;xor a
	CP (hl)	;comprueba si el byte coincide
	ld h,0
	jp z,pulsado
	ld l,h
	ret
.pulsado
	ld l,1
	ret
	
	