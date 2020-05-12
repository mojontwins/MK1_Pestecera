 ; ******************************************************
; **       Librería de rutinas para Amstrad CPC       **
; **	   Raúl Simarro, 	  Artaburu 2009       **
; ******************************************************

XLIB cpc_PrintGphStrStdXY

LIB cpc_GetScrAddress0

LIB cpc_PrintGphStrStd0

XREF direcc_destino0s_m1
XREF color_uso

.cpc_PrintGphStrStdXY
;preparación datos impresión. El ancho y alto son fijos!
	ld ix,2
	add ix,sp
	

 	ld L,(ix+0)
	ld A,(ix+2)	;pantalla
	
	call cpc_GetScrAddress0   

	;destino
	
   	ld e,(ix+4)
	ld d,(ix+5)	;texto origen
	
	ld a,(ix+6) ;color
	ld (color_uso+1),a
    
 JP cpc_PrintGphStrStd0
 
 
 
