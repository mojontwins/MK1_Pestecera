; ******************************************************
; **       Librería de rutinas para Amstrad CPC       **
; **	   Raúl Simarro, 	  Artaburu 2007       **
; ******************************************************

XLIB cpc_DeleteKeys

;borra la tabla de las teclas para poder redefinirlas todas

LIB cpc_KeysData
XREF  tabla_teclas

.cpc_DeleteKeys
LD HL,cpc_KeysData+tabla_teclas
LD DE,cpc_KeysData+tabla_teclas+1
LD BC, 24
LD (HL),$FF
LDIR
RET
