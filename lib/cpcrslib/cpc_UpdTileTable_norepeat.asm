; ******************************************************
; **       Librería de rutinas para Amstrad CPC       **
; **	   Raúl Simarro, 	  Artaburu 2007       **
; ******************************************************

XLIB cpc_UpdTileTable		;marca un tile indicando las coordenadas del tile

XREF tiles_tocados

XREF tiles_ocultos_ancho0
XREF tiles_ocultos_ancho1
XREF tiles_ocultos_alto0
XREF tiles_ocultos_alto1
XREF oculto

.cpc_UpdTileTable	

	; d = Y
	; e = X

	LD HL,tiles_tocados
	;incorporo el tile en su sitio, guardo x e y
.bucle_recorrido_tiles_tocados
	LD A,(HL)
	CP $FF	
	JP Z,incorporar_tile	;Solo se incorpora al llegar a un hueco
	CP E
	JP Z, comprobar_segundo_byte	
	INC HL
	INC HL
	JP bucle_recorrido_tiles_tocados
.comprobar_segundo_byte
	INC HL
	LD A,(HL)
	CP D
	RET Z	;los dos bytes son iguales, es el mismo tile. No se añade
	INC HL
	JP bucle_recorrido_tiles_tocados
.incorporar_tile
	LD (HL),E	
	INC HL
	LD (HL),D
	INC HL
	LD (HL),$FF	;End of data
.contkaka	
	RET
