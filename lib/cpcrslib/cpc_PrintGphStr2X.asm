; ******************************************************
; **       Librería de rutinas para Amstrad CPC       **
; **	   Raúl Simarro, 	  Artaburu 2007       **
; ******************************************************

XLIB cpc_PrintGphStr2X


LIB cpc_PrintGphStr0
XREF direcc_destino0

.cpc_PrintGphStr2X
;preparación datos impresión. El ancho y alto son fijos!
	ld ix,2
	add ix,sp
	
	ld l,(ix+0)
	ld h,(ix+1)	;destino
	;ld (cpc_PrintGphStr0+direcc_destino0),hl
	
   	ld e,(ix+2)
	ld d,(ix+3)	;texto origen
	ld a,1
 JP cpc_PrintGphStr0