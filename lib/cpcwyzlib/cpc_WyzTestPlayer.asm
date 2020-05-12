; ******************************************************
; **       Librería de rutinas para Amstrad CPC       **
; **	   Raúl Simarro, 	  Artaburu 2007           **
; ******************************************************

XLIB cpc_WyzTestPlayer

LIB cpc_WyzPlayer
XREF INTERRUPCION

.cpc_WyzTestPlayer
	LD HL,INTERRUPCION+cpc_WyzPlayer
	LD A,(HL)
	LD L,A
	LD H,0
	RET