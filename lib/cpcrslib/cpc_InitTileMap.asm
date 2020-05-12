; ******************************************************
; **       Librería de rutinas para Amstrad CPC       **
; **	   Raúl Simarro, 	  Artaburu 2007           **
; ******************************************************

XLIB cpc_InitTileMap


XREF tiles

.cpc_InitTileMap

	;*LD IX,2
	;*ADD IX,SP
	
	;*LD L,(IX+0)
	;*LD H,(IX+1)
	LD (tiles),HL
	RET