; MT MK3 OM v0.6 [Cheman]
; Copyleft 2017, 2019 by The Mojon Twins

; Tilemap configuration for CPCRSLIB.
; This tilemaps is defined over the whole screen
; using a tweaked 32x24 CRTC configuration.

	XLIB TileMapConf
	
	XREF _tileset

	XDEF _nametable

	XREF tiles
	XDEF pantalla_juego
	XDEF tiles_tocados
	XDEF tiles_tocados_ptr
	XDEF posiciones_pantalla
	XDEF posiciones_super_buffer
	
	XDEF posicion_inicial_area_visible
	XDEF posicion_inicial_superbuffer
	XDEF ancho_pantalla_bytes
	XDEF alto_pantalla_bytes
	XDEF ancho_pantalla_bytes_visible
	
	XDEF mascara1
	XDEF mascara2
	
	; Voy a definir como marcara de los sprites el color 
	; 1er numero: garbled bits AND $55
	; 2o  numero: garbled bits AND $AA

	; garbled bits: 4062 5173
	
	; 0: $00, $00
	; 1: $80, $40
	; 2: $04, $08
	; 3: $44, $88
	; 4: $10, $20
	; 5: $50, $A0
	; 6: $14, $28
	; 7: $54, $A8
	; 8: $01, $02
	; 9: $41, $82
	; 10: $05, $0A
	; 11: $45, $8A
	; 12: $11, $22
	; 13:
	; 14:
	; 15: $55, $AA
	
	defc mascara1 = $00;
	defc mascara2 = $00;
	
; VALORES QUE DEFINEN EL BUFFER Y LA PANTALLA
	
	defc tiles_tocados = $CE00

	defc _nametable = $100
	defc pantalla_juego= $100

	defc posicion_inicial_area_visible = $c000
	defc posicion_inicial_superbuffer = $9000
	
	defc T_WIDTH = 	32	;dimensiones de la pantalla en tiles
	defc T_HEIGHT = 24 
		
	defc ancho_pantalla_bytes = 2*T_WIDTH
	defc alto_pantalla_bytes = 8*T_HEIGHT
	defc ancho_pantalla_bytes_visible = 2*T_WIDTH

;El tama? del buffer es ancho_pantalla_bytes*alto_pantalla_bytes

.TileMapConf

.posiciones_pantalla
	;Posiciones en las que se dibujan los tiles
	defw posicion_inicial_area_visible+$40*0
	defw posicion_inicial_area_visible+$40*1  
	defw posicion_inicial_area_visible+$40*2
	defw posicion_inicial_area_visible+$40*3
	defw posicion_inicial_area_visible+$40*4
	defw posicion_inicial_area_visible+$40*5 
	defw posicion_inicial_area_visible+$40*6 
	defw posicion_inicial_area_visible+$40*7 
	
	defw posicion_inicial_area_visible+$40*8 
	defw posicion_inicial_area_visible+$40*9 
	defw posicion_inicial_area_visible+$40*10 
	defw posicion_inicial_area_visible+$40*11 
	defw posicion_inicial_area_visible+$40*12 
	defw posicion_inicial_area_visible+$40*13 
	defw posicion_inicial_area_visible+$40*14 
	defw posicion_inicial_area_visible+$40*15
	
	defw posicion_inicial_area_visible+$40*16
	defw posicion_inicial_area_visible+$40*17
	defw posicion_inicial_area_visible+$40*18
	defw posicion_inicial_area_visible+$40*19
	defw posicion_inicial_area_visible+$40*20
	defw posicion_inicial_area_visible+$40*21
	defw posicion_inicial_area_visible+$40*22
	defw posicion_inicial_area_visible+$40*23

.posiciones_super_buffer
	;muestra el inicio de cada linea (son 10 tiles de 8x16 de alto)
	defw posicion_inicial_superbuffer+8*ancho_pantalla_bytes*0
	defw posicion_inicial_superbuffer+8*ancho_pantalla_bytes*1
	defw posicion_inicial_superbuffer+8*ancho_pantalla_bytes*2
	defw posicion_inicial_superbuffer+8*ancho_pantalla_bytes*3
	defw posicion_inicial_superbuffer+8*ancho_pantalla_bytes*4
	defw posicion_inicial_superbuffer+8*ancho_pantalla_bytes*5
	defw posicion_inicial_superbuffer+8*ancho_pantalla_bytes*6
	defw posicion_inicial_superbuffer+8*ancho_pantalla_bytes*7

	defw posicion_inicial_superbuffer+8*ancho_pantalla_bytes*8
	defw posicion_inicial_superbuffer+8*ancho_pantalla_bytes*9
	defw posicion_inicial_superbuffer+8*ancho_pantalla_bytes*10
	defw posicion_inicial_superbuffer+8*ancho_pantalla_bytes*11
	defw posicion_inicial_superbuffer+8*ancho_pantalla_bytes*12
	defw posicion_inicial_superbuffer+8*ancho_pantalla_bytes*13
	defw posicion_inicial_superbuffer+8*ancho_pantalla_bytes*14
	defw posicion_inicial_superbuffer+8*ancho_pantalla_bytes*15

	defw posicion_inicial_superbuffer+8*ancho_pantalla_bytes*16
	defw posicion_inicial_superbuffer+8*ancho_pantalla_bytes*17
	defw posicion_inicial_superbuffer+8*ancho_pantalla_bytes*18
	defw posicion_inicial_superbuffer+8*ancho_pantalla_bytes*19
	defw posicion_inicial_superbuffer+8*ancho_pantalla_bytes*20
	defw posicion_inicial_superbuffer+8*ancho_pantalla_bytes*21
	defw posicion_inicial_superbuffer+8*ancho_pantalla_bytes*22
	defw posicion_inicial_superbuffer+8*ancho_pantalla_bytes*23
	
;Rutinas para transferir bloques independientes a la pantalla
