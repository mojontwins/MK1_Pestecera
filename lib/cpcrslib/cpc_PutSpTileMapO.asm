; ******************************************************
; **       Librería de rutinas para Amstrad CPC       **
; **	   Raúl Simarro, 	  Artaburu 2007       **
; ******************************************************

XLIB cpc_PutSpTileMapO		;se encarga de actualizar los tiles que toca el sprite 

XREF tiles_tocados
XREF pantalla_juego					;datos de la pantalla, cada byte indica un tile
XREF posiciones_super_buffer
XREF tiles
XREF solo_coordenadas 

XREF bit_ancho
XREF bit_alto

LIB cpc_PutSpTileMap
LIB cpc_UpdTileTable



.cpc_PutSpTileMapO

    ex de,hl	;4
	LD IXH,d	;9
    LD IXL,e	;9   
    ld e,(ix+0)
    ld d,(ix+1)
    
    LD A,(de)
    ld (bit_ancho+1),a
    
    inc de
    LD A,(de)
	ld (bit_alto+1),a
	ld e,(ix+10)
    ld d,(ix+11)
    jp solo_coordenadas    
    
 