; ******************************************************
; **       Librería de rutinas para Amstrad CPC       **
; **	   Raúl Simarro, 	  Artaburu 2007       **
; ******************************************************

XLIB cpc_SuperbufferAddress		;calcula la posición en el superbuffer según las coordenadas	
								;del sprite y lo actualiza

XREF tiles_tocados
XREF pantalla_juego					;datos de la pantalla, cada byte indica un tile
XREF posiciones_super_buffer
XREF tiles
XREF ancho_pantalla_bytes 
XREF posicion_inicial_superbuffer

.cpc_SuperbufferAddress
   ; ld ix,2
   ; add ix,sp

   ; ld l,(ix+0)
   ; ld h,(ix+1)	;HL apunta al sprite
      
    push hl
    pop ix
    
  ;lo cambio para la rutina de multiplicar 
    ld a,(ix+8)
    ld e,(ix+9)
 	include "multiplication1.asm"
 		


	ld b,0
	ld c,a
	add hl,bc
	ld de,posicion_inicial_superbuffer
	add hl,de
	;hl apunta a la posición en buffer (destino)
    ld (ix+4),l
    ld (ix+5),h
    ret
    
    ;defb 'm','m','x'