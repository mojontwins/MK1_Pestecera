; ******************************************************
; **       Librería de rutinas para Amstrad CPC       **
; **	   Raúl Simarro, 	  Artaburu 2007           **
; ******************************************************

; [na_th_an] Modificada por Mojon Twins - eliminamos la "cabecera" de los sprites.
; [na_th_an] Gracias a Fran Gallego y al código de la CPCTelera, rescrito para usar LUTs
; [na_th_an] Esta nueva vesión de la rutina imprime al pixel en m0
; Necesita una LUT en $FE00

XLIB cpc_PutTrSp8x24TileMap2bGPx

XREF tiles_tocados
XREF pantalla_juego	
XREF posiciones_super_buffer
XREF tiles
XREF ancho_pantalla_bytes 
XREF posicion_inicial_superbuffer

.cpc_PutTrSp8x24TileMap2bGPx

	;según las coordenadas x,y que tenga el sprite, se dibuja en el buffer 
    ex de,hl	;4
    LD IXH,d	;9
    LD IXL,e	;9 

	;lo cambio para la rutina de multiplicar 
    ld e,(ix+8)		;x
    ld  a, e 			; Save for later!
    srl e 				; X a bytes    
    ld h,(ix+9)		;y

.pasa_bloque_a_sbuffer

.transferir_sprite
	ld d,0

	; Multiplico HL = H * 64, offset "Y"
	ld  l, 0
	srl h
	rr  l
	srl h
	rr  l
	
	add hl,de 		; sumo offset "X"

	ld de,posicion_inicial_superbuffer
	add hl,de

	;hl apunta a la posición en buffer (destino)
			
	ld e,(ix+0)
    ld d,(ix+1)	;HL apunta al sprite

.sp_buffer_mask
	ld ixh,24

	; Remember A = X in pixels
	and 1 		
	jr  nz, loop_alto_map_sbuffer_shifted 

.loop_alto_map_sbuffer
	; El ancho está desenrollado: Hay que procesar y copiar 4 bytes.

	ld a, (de) 		; Get sprite
	or (hl) 		; Get bg + draw pixels
	ld (hl), a 		; save BG+sprite
	inc de
	inc hl

	ld a, (de) 		; Get sprite
	or (hl) 		; Get bg + draw pixels
	ld (hl), a 		; save BG+sprite
	inc de
	inc hl

	ld a, (de) 		; Get sprite
	or (hl) 		; Get bg + draw pixels
	ld (hl), a 		; save BG+sprite
	inc de
	inc hl

	ld a, (de) 		; Get sprite
	or (hl) 		; Get bg + draw pixels
	ld (hl), a 		; save BG+sprite
	inc de
	
	;*************************************************		
		
	dec ixh
	ret z

	; de += 61 (next line in bg)
	ld bc, 61
	add hl, bc
	jp loop_alto_map_sbuffer


.loop_alto_map_sbuffer_shifted 
	; El ancho está desenrollado. Procesamos 4 bytes que copiamos en 5:
	; 1. AB -> BA, byte 1 = BA And 0x55                    = 0A
	; 2. CD -> DC, byte 2 = (BA And 0xAA) OR (DC And 0x55) = BC
	; 3. EF -> FE, byte 3 = (DC And 0xAA) OR (FE And 0x55) = DE
	; 4. GH -> HG, byte 4 = (FE And 0xAA) OR (HG And 0x55) = FG
	; 5.         , byte 5 = (HG And 0xAA)                  = H0

	;; Byte 1 :
	;; AB -> BA, byte 1 = BA And 0x55                    = 0A

	ld  a, (de) 	; Get sprite byte AB

	;; swap pixels in byte
	ld  c, a
	rlca
	rlca
	xor c
	and $55 		; 01010101
	xor c
	rrca 			; A = BA
	ld  c, a 		; Save for next byte

	and $55 		; A = 0A

	or (hl) 		; Get bg + draw pixels
	ld (hl), a 		; save bg + masked sprite
	inc de
	inc hl

	;; Byte 2
	;; CD -> DC, byte 2 = (BA And 0xAA) OR (DC And 0x55) = BC

	ld  a, c 		; BA
	and $AA 		; B0
	ld  b, a 		; B = B0

	ld  a, (de) 	; Get sprite byte CD
	
	;; swap pixels in byte
	ld  c, a
	rlca
	rlca
	xor c
	and $55 		; 01010101
	xor c
	rrca 			; A = DC
	ld  c, a 		; C = DC

	and $55 		; A = 0C
	or  b 			; A = BC

	or (hl) 		; Get bg + draw pixels
	ld (hl), a 		; save BG
	inc de
	inc hl

	;; Byte 3
	;; EF -> FE, byte 3 = (DC And 0xAA) OR (FE And 0x55) = DE

	ld  a, c 		; DC
	and $aa 		; D0
	ld  b, a 		; IYL = D0

	ld  a, (de) 	; Get sprite byte EF
	
	;; swap pixels in byte
	ld  c, a
	rlca
	rlca
	xor c
	and $55 		; 01010101
	xor c
	rrca 			; A = FE

	ld  c, a 		; C = FE

	and $55 		; A = 0E
	or  b 			; A = DE

	or (hl) 		; Get bg + draw pixels
	ld (hl), a 		; save BG
	inc de
	inc hl

	;; Byte 4
	;; GH -> HG, byte 4 = (FE And 0xAA) OR (HG And 0x55) = FG

	ld  a, c 		; FE
	and $aa 		; F0
	ld  b, a 		; IYL = F0

	ld  a, (de) 		; Get sprite byte GH
	
	;; swap pixels in byte
	ld  c, a
	rlca
	rlca
	xor c
	and $55 		; 01010101
	xor c
	rrca 			; A = HG

	ld  c, a 		; C = HG

	and $55 		; A = 0G
	or  b 			; A = FG

	or (hl) 		; Get bg + draw pixels
	ld (hl), a 		; save BG
	inc de
	inc hl

	;; Byte 5
	;; byte 5 = (HG And 0xAA) = H0
	
	ld  a, c 		; HG
	and $aa 		; H0

	or (hl) 		; Get bg + draw pixels
	ld (hl), a 		; save BG

	;*************************************************		
		
	dec ixh
	ret z

	; de += 60 (next line in bg)
	ld bc, 60
	add hl, bc

	jp loop_alto_map_sbuffer_shifted
