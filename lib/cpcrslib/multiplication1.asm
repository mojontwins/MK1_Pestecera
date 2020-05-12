; Multiplication by 64
; HL = 64 * E

;ld  l, e
;ld  h, 0

;add hl, hl ; 2
;add hl, hl ; 4
;add hl, hl ; 8
;add hl, hl ; 16
;add hl, hl ; 32
;add hl, hl ; 64


ld  a, e 	; 		4
add a, a	; 2		4
add a, a	; 4		4
add a, a	; 8		4
ld  h, 0	;		2
ld  l, a 	;		4
add hl, hl  ; 16	11
add hl, hl  ; 32	11
add hl, hl  ; 64	11
;					55 t-states

; Multiplication by generic is slower

;       ld    h, ancho_pantalla_bytes
;       LD    L, 0
;       LD    D, L 
;       LD    B, 8
;MULT:  ADD   HL, HL
;       JR    NC, NOADD
;       ADD   HL, DE
;NOADD: DJNZ  MULT	
