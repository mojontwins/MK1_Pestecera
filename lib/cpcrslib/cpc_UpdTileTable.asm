; ******************************************************
; **       Librería de rutinas para Amstrad CPC       **
; **	   Raúl Simarro, 	  Artaburu 2007           **
; ******************************************************

; [na_th_an] He cambiado esto radicalmente...
; Originalmente, el código de Artaburu comprobaba que no hubiera
; duplicados. Para mi caso de uso no es necesario, ya que busco
; la velocidad constante más rápida. Así me ahorro comprobaciones.




XLIB cpc_UpdTileTable		;marca un tile indicando las coordenadas del tile

XREF tiles_tocados
XREF tiles_tocados_ptr


.cpc_UpdTileTable	

	; d = Y
	; e = X

	; Primero E, luego D

	ld  hl, (tiles_tocados_ptr)
	ld  (hl), e
	inc hl
	ld  (hl), d
	inc hl
	ld  (hl), $ff
	ld  (tiles_tocados_ptr), hl

	RET
