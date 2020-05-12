; ******************************************************
; **       Librería de rutinas para Amstrad CPC       **
; **	   Raúl Simarro, 	  Artaburu 2007           **
; ******************************************************

XLIB cpc_WyzInitPlayer

LIB cpc_WyzPlayer
XREF TABLA_SONG
XREF TABLA_EFECTOS
XREF TABLA_PAUTAS
XREF TABLA_SONIDOS

.cpc_WyzInitPlayer

; la entrada indica las tablas de canciones, pautas, efectos,... sólo hay que inicializar esos datos 
; en la librería
	LD IX,2
	ADD IX,SP
	
	LD L,(IX+0)
	LD H,(IX+1)
	LD (cpc_WyzPlayer+TABLA_SONG),HL
	LD L,(IX+2)
	LD H,(IX+3)
	LD (cpc_WyzPlayer+TABLA_EFECTOS),HL
	LD L,(IX+4)
	LD H,(IX+5)
	LD (cpc_WyzPlayer+TABLA_PAUTAS),HL
	LD L,(IX+6)
	LD H,(IX+7)
	LD (cpc_WyzPlayer+TABLA_SONIDOS),HL	
	RET