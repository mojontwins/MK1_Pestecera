; ******************************************************
; **       Librería de rutinas para Amstrad CPC       **
; **	   Raúl Simarro, 	  Artaburu 2007           **
; ******************************************************

XLIB cpc_WyzConfigurePlayer

LIB cpc_WyzPlayer
XREF INTERRUPCION

.cpc_WyzConfigurePlayer
	;LD HL,2
	;ADD HL,SP
	;LD A,(HL)
	LD a,l
	;LD HL,INTERRUPCION+cpc_WyzPlayer
	;AND (HL)
	LD (INTERRUPCION+cpc_WyzPlayer),A
	RET
