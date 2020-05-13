; ******************************************************
; **       Librería de rutinas para Amstrad CPC       **
; **	   Raúl Simarro, 	  Artaburu 2007       **
; ******************************************************

XLIB cpc_ResetTouchedTiles

XREF tiles_tocados
XREF tiles_tocados_ptr
 
.cpc_ResetTouchedTiles

; [na_th_an] El código original ponía una marca al principio
; Yo voy a usar inserción directa en una lista indexada, así que
; lo hago diferentemente:

;	LD HL,tiles_tocados
;	LD (HL),$FF
;	RET

	ld  hl, tiles_tocados
	ld  (tiles_tocados_ptr), hl
	ld  (hl), $ff
	ret 

