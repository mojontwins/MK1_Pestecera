; ******************************************************
; **       Librería de rutinas para Amstrad CPC       **
; **	   Raúl Simarro, 	  Artaburu 2007       **
; ******************************************************

XLIB cpc_TouchTileXY		;marca un tile indicando las coordenadas del tile

XREF tiles
XREF tiles_tocados

LIB cpc_UpdTileTable


.cpc_TouchTileXY
;entran las coordenadas x,y y se marca el tile para redibujarlo en pantalla
;la coordenada x se divide entre 4 y da el tile
;la coordenada y se divide entre 16 y da el tile
	ld hl,2
    add hl,sp			; ¿Es la forma de pasar parámetros? ¿Se pasan en SP+2? ¿en la pila?			
	ld D,(hl)
	inc hl
	inc hl
	ld E,(hl)
JP cpc_UpdTileTable
