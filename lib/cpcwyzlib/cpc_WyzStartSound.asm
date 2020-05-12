; ******************************************************
; **       Librería de rutinas para Amstrad CPC       **
; **	   Raúl Simarro, 	  Artaburu 2007           **
; ******************************************************

XLIB cpc_WyzStartSound	;No se suele usar directamente. No lo meto en librería.

XREF INICIA_SONIDO_WYZ

.cpc_WyzStartSound
	LD HL,2
	ADD HL,SP
	LD A,(HL)
	JP INICIA_SONIDO_WYZ