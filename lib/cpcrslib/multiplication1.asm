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


;ld  a, e 	; 		1
;add a, a	; 2		1
;add a, a	; 4		1
;add a, a	; 8		1
;ld  h, 0	;		2
;ld  l, a 	;		1
;add hl, hl  ; 16	3
;add hl, hl  ; 32	3
;add hl, hl  ; 64	3
;					16

ld  l, 0 		;   2
ld  h, e 		;   1
srl h 			;   2
rr  l 			;   2
srl h 			;   2
rr  l 			;   2
				;	11


; Multiplication by generic is slower

;       ld    h, ancho_pantalla_bytes
;       LD    L, 0
;       LD    D, L 
;       LD    B, 8
;MULT:  ADD   HL, HL
;       JR    NC, NOADD
;       ADD   HL, DE
;NOADD: DJNZ  MULT	
