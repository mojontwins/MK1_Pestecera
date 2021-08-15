; ******************************************************
; **       Librería de rutinas para Amstrad CPC       **
; **	   Raúl Simarro, 	  Artaburu 2007           **
; ******************************************************

; [na_th_an] Modificada por Mojon Twins - eliminamos la "cabecera" de los sprites.
; [na_th_an] Gracias a Fran Gallego y al código de la CPCTelera, rescrito para usar LUTs
; [na_th_an] Esta nueva vesión de la rutina imprime al pixel en m0
; Necesita una LUT en $FE00

XLIB cpc_PutTrSp8x16TileMap2bPx

XREF tiles_tocados
XREF pantalla_juego		
XREF posiciones_super_buffer
XREF tiles
XREF ancho_pantalla_bytes 
XREF posicion_inicial_superbuffer

.cpc_PutTrSp8x16TileMap2bPx

	;según las coordenadas x,y que tenga el sprite, se dibuja en el buffer 
    ex de,hl	;4
    LD IXH,d	;9
    LD IXL,e	;9 

	;lo cambio para la rutina de multiplicar 
    ld  e, (ix+8)		; X - Cuidado ! va a pixel (0-127)
    ld  a, e 			; Save for later!
    srl e 				; X a bytes
    ld  h, (ix+9)		; Y

.pasa_bloque_a_sbuffer

.transferir_sprite
	ld d,0

	; Multiplico HL = H * 64, offset "Y"
	ld  l, 0
	srl h
	rr  l
	srl h
	rr  l
	
	add hl, de 		; sumo offset "X"

	ld de, posicion_inicial_superbuffer
	add hl,de

	;hl apunta a la posición en buffer (destino)
			
	ld e,(ix+0)
    ld d,(ix+1)	;HL apunta al sprite
	
.sp_buffer_mask
	ld ixh,16
	ex de,hl 		; de -> bg
	ld b, h
	ld c, l 		; bc -> sprite

	; Remember A = X in pixels
	and 1 		
	jr  nz, loop_alto_map_sbuffer_shifted 

.loop_alto_map_sbuffer
	ld h, $FE		; hl -> LUT

	; El ancho está desenrollado: Hay que procesar y copiar 4 bytes.

	ld a, (bc) 		; Get sprite
	ld l, a 		; copy to L to index LUT
	ld a, (de) 		; Get bg
	and (hl) 		; make a hole
	or l  			; draw pixels
	ld (de), a 		; save BG
	inc de
	inc bc

	ld a, (bc) 		; Get sprite
	ld l, a 		; copy to L to index LUT
	ld a, (de) 		; Get bg
	and (hl) 		; make a hole
	or l  			; draw pixels
	ld (de), a 		; save BG
	inc de
	inc bc

	ld a, (bc) 		; Get sprite
	ld l, a 		; copy to L to index LUT
	ld a, (de) 		; Get bg
	and (hl) 		; make a hole
	or l  			; draw pixels
	ld (de), a 		; save BG
	inc de
	inc bc

	ld a, (bc) 		; Get sprite
	ld l, a 		; copy to L to index LUT
	ld a, (de) 		; Get bg
	and (hl) 		; make a hole
	or l  			; draw pixels
	ld (de), a 		; save BG
	inc de
	inc bc
	
	;*************************************************		
		
	dec ixh
	ret z

	; de += 60 (next line in bg)
	ld hl, 60
	add hl, de
	ex de, hl

	jp loop_alto_map_sbuffer


.loop_alto_map_sbuffer_shifted 
	ld  h, $FE; 	; hl -> LUT

	; El ancho está desenrollado. Procesamos 4 bytes que copiamos en 5:
	; 1. AB -> BA, byte 1 = BA And 0x55                    = 0A
	; 2. CD -> DC, byte 2 = (BA And 0xAA) OR (DC And 0x55) = BC
	; 3. EF -> FE, byte 3 = (DC And 0xAA) OR (FE And 0x55) = DE
	; 4. GH -> HG, byte 4 = (FE And 0xAA) OR (HG And 0x55) = FG
	; 5.         , byte 5 = (HG And 0xAA)                  = H0

	;; Byte 1 :
	;; AB -> BA, byte 1 = BA And 0x55                    = 0A

	ld  a, (bc) 	; Get sprite byte AB

	;; swap pixels in byte
	ld  l, a
	rlca
	rlca
	xor l
	and $55 		; 01010101
	xor l
	rrca 			; A = BA
	ld  ixl, a 		; Save for next byte

	and $55

	ld l, a 		; copy to L to index LUT
	ld a, (de) 		; Get bg
	and (hl) 		; make a hole
	or l  			; draw pixels
	ld (de), a 		; save bg + masked sprite
	inc de
	inc bc

	;; Byte 2
	;; CD -> DC, byte 2 = (BA And 0xAA) OR (DC And 0x55) = BC

	ld  a, ixl 		; BA
	and $AA 		; B0
	ld  iyl, a 		; IYL = B0

	ld  a, (bc) 		; Get sprite byte CD
	
	;; swap pixels in byte
	ld  l, a
	rlca
	rlca
	xor l
	and $55 		; 01010101
	xor l
	rrca 			; A = DC
	ld  ixl, a 		; IXL = DC

	and $55 		; A = 0C
	or  iyl 		; A = BC

	ld l, a 		; copy to L to index LUT
	ld a, (de) 		; Get bg
	and (hl) 		; make a hole
	or l  			; draw pixels
	ld (de), a 		; save BG
	inc de
	inc bc

	;; Byte 3
	;; EF -> FE, byte 3 = (DC And 0xAA) OR (FE And 0x55) = DE

	ld  a, ixl 		; DC
	and $aa 		; D0
	ld  iyl, a 		; IYL = D0

	ld  a, (bc) 		; Get sprite byte EF
	
	;; swap pixels in byte
	ld  l, a
	rlca
	rlca
	xor l
	and $55 		; 01010101
	xor l
	rrca 			; A = FE

	ld  ixl, a 		; IXL = FE

	and $55 		; A = 0E
	or  iyl 		; A = DE

	ld l, a 		; copy to L to index LUT
	ld a, (de) 		; Get bg
	and (hl) 		; make a hole
	or l  			; draw pixels
	ld (de), a 		; save BG
	inc de
	inc bc

	;; Byte 4
	;; GH -> HG, byte 4 = (FE And 0xAA) OR (HG And 0x55) = FG

	ld  a, ixl 		; FE
	and $aa 		; F0
	ld  iyl, a 		; IYL = F0

	ld  a, (bc) 		; Get sprite byte GH
	
	;; swap pixels in byte
	ld  l, a
	rlca
	rlca
	xor l
	and $55 		; 01010101
	xor l
	rrca 			; A = HG

	ld  ixl, a 		; IXL = HG

	and $55 		; A = 0G
	or  iyl 		; A = FG

	ld l, a 		; copy to L to index LUT
	ld a, (de) 		; Get bg
	and (hl) 		; make a hole
	or l  			; draw pixels
	ld (de), a 		; save BG
	inc de
	inc bc

	;; Byte 5
	;; byte 5 = (HG And 0xAA) = H0
	
	ld  a, ixl 		; HG
	and $aa 		; H0

	ld l, a 		; copy to L to index LUT
	ld a, (de) 		; Get bg
	and (hl) 		; make a hole
	or l  			; draw pixels
	ld (de), a 		; save BG

	;*************************************************		
		
	dec ixh
	ret z

	; de += 60 (next line in bg)
	ld hl, 60
	add hl, de
	ex de, hl

	jp loop_alto_map_sbuffer_shifted

