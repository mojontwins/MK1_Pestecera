; ******************************************************
; **       Librería de rutinas para Amstrad CPC       **
; **	   Raúl Simarro, 	  Artaburu 2007       **
; ******************************************************

XLIB cpc_PrintGphStrM1


LIB cpc_PrintGphStr0M1
XREF direcc_destino0_m1

.cpc_PrintGphStrM1
;preparación datos impresión. El ancho y alto son fijos!
	ld ix,2
	add ix,sp
	
	ld l,(ix+0)
	ld h,(ix+1)	;destino
	
	
   	ld e,(ix+2)
	ld d,(ix+3)	;texto origen
	xor a

 JP cpc_PrintGphStr0M1