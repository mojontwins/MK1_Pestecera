; Multiplication by 32.
; HL = 32 * E

;ld  l, e 	; 		4
;ld  h, 0	; 		2
;
;add hl, hl ; 2		11
;add hl, hl ; 4		11
;add hl, hl ; 8		11
;add hl, hl ; 16	11
;add hl, hl ; 32	11
;					61 t-states

; Restricted optimization.
; e is 24 at maximum. 
; I can first multiply * 8 in 8 bits math, then * 4 in 16 bits.

ld  a, e 	; 		1
add a, a	; 2		1
add a, a	; 4		1
add a, a	; 8		1
ld  h, 0	;		2
ld  l, a 	;		1
add hl, hl  ; 16	3
add hl, hl  ; 32	3
;					13

; Multiplication by generic is slower

;		ld    h, ancho_pantalla_bytes/2
;		LD    L, 0
;		LD    D, L 
;		LD    B, 8
;MULT:  ADD   HL, HL
;       JR    NC, NOADD
;       ADD   HL, DE
;NOADD: DJNZ  MULT	
