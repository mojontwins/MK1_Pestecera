; ******************************************************
; **       Librería de rutinas para Amstrad CPC       **
; **	   Raúl Simarro, 	  Artaburu 2007           **
; ******************************************************

XLIB cpc_WyzSetTempo

LIB cpc_WyzPlayer
XREF direcc_tempo

.cpc_WyzSetTempo
	ld a,l
	ld (direcc_tempo+cpc_WyzPlayer+1),a
	ret
