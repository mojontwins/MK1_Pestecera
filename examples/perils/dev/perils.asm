;* * * * *  Small-C/Plus z88dk * * * * *
;  Version: 20100416.1
;
;	Reconstructed for z80 Module Assembler
;
;	Module compile time: Wed Apr 06 16:42:41 2022



	MODULE	mk1.c


	INCLUDE "z80_crt0.hdr"


	XREF _nametable
	LIB cpc_KeysData
	LIB cpc_UpdTileTable
	LIB cpc_InvalidateRect
	._def_keys
	defw $4404 ; LEFT O
	defw $4308 ; RIGHT P
	defw $4808 ; UP Q
	defw $4820 ; DOWN A
	defw $4580 ; BUTTON_A SPACE
	defw $4808 ; BUTTON_B Q
	defw $4204 ; KEY_ENTER
	defw $4804 ; KEY_ESC
	defw $4440 ; KEY_AUX1 M
	defw $4880 ; KEY_AUX2 Z
	defw $4801 ; KEY_AUX3 1
	defw $4802 ; KEY_AUX4 2
;	SECTION	text

._behs
	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	8

	defm	""
	defb	8

	defm	""
	defb	8

	defm	""
	defb	8

	defm	""
	defb	0

	defm	""
	defb	8

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	1

	defm	""
	defb	8

	defm	""
	defb	10

	defm	""
	defb	10

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

;	SECTION	code


	defc viewport_x = 1
	defc viewport_y = 3
	XDEF viewport_x
	XDEF viewport_y
	.vpClipStruct defb 3, 3 + 20, 1, 1 + 30
	.fsClipStruct defb 0, 24, 0, 32
	._spacer
	defb 32,32,32,32,32,32,32,32,32,32,32,32,0
;	SECTION	text

._warp_to_level
	defm	""
	defb	0

;	SECTION	code


	._def_keys_joy
	defw 0x4904, 0x4908, 0x4901, 0x4902, 0x4910, 0x4920
	defw 0x4004, 0x4804, 0x4880, 0x4780, 0x4801, 0x4802
	.HLshr6_A
	sla h
	sla h
	ld a, l
	rlca
	rlca
	and 0x03
	or h
	ret
	.Ashl16_HL
	ld l, 0
	ld h, a
	srl h
	rr l
	srl h
	rr l
	ret
	.withSign
	bit 7, a
	ret z
	ld a, $C0
	or h
	ld h, a
	ret
	; aPPack decompressor
	; original source by dwedit
	; very slightly adapted by utopian
	; optimized by Metalbrain
	;hl = source
	;de = dest
	.depack ld ixl,128
	.apbranch1 ldi
	.aploop0 ld ixh,1 ;LWM = 0
	.aploop call ap_getbit
	jr nc,apbranch1
	call ap_getbit
	jr nc,apbranch2
	ld b,0
	call ap_getbit
	jr nc,apbranch3
	ld c,16 ;get an offset
	.apget4bits call ap_getbit
	rl c
	jr nc,apget4bits
	jr nz,apbranch4
	ld a,b
	.apwritebyte ld (de),a ;write a 0
	inc de
	jr aploop0
	.apbranch4 and a
	ex de,hl ;write a previous byte (1-15 away from dest)
	sbc hl,bc
	ld a,(hl)
	add hl,bc
	ex de,hl
	jr apwritebyte
	.apbranch3 ld c,(hl) ;use 7 bit offset, length = 2 or 3
	inc hl
	rr c
	ret z ;if a zero is encountered here, it is EOF
	ld a,2
	adc a,b
	push hl
	ld iyh,b
	ld iyl,c
	ld h,d
	ld l,e
	sbc hl,bc
	ld c,a
	jr ap_finishup2
	.apbranch2 call ap_getgamma ;use a gamma code * 256 for offset, another gamma code for length
	dec c
	ld a,c
	sub ixh
	jr z,ap_r0_gamma ;if gamma code is 2, use old r0 offset,
	dec a
	;do I even need this code?
	;bc=bc*256+(hl), lazy 16bit way
	ld b,a
	ld c,(hl)
	inc hl
	ld iyh,b
	ld iyl,c
	push bc
	call ap_getgamma
	ex (sp),hl ;bc = len, hl=offs
	push de
	ex de,hl
	ld a,4
	cp d
	jr nc,apskip2
	inc bc
	or a
	.apskip2 ld hl,127
	sbc hl,de
	jr c,apskip3
	inc bc
	inc bc
	.apskip3 pop hl ;bc = len, de = offs, hl=junk
	push hl
	or a
	.ap_finishup sbc hl,de
	pop de ;hl=dest-offs, bc=len, de = dest
	.ap_finishup2 ldir
	pop hl
	ld ixh,b
	jr aploop
	.ap_r0_gamma call ap_getgamma ;and a new gamma code for length
	push hl
	push de
	ex de,hl
	ld d,iyh
	ld e,iyl
	jr ap_finishup
	.ap_getbit ld a,ixl
	add a,a
	ld ixl,a
	ret nz
	ld a,(hl)
	inc hl
	rla
	ld ixl,a
	ret
	.ap_getgamma ld bc,1
	.ap_getgammaloop call ap_getbit
	rl c
	rl b
	call ap_getbit
	jr c,ap_getgammaloop
	ret

._unpack
	ld	hl,4	;const
	call	l_gintsp	;
	ld	(_ram_address),hl
	pop	bc
	pop	hl
	push	hl
	push	bc
	ld	(_ram_destination),hl
	ld hl, (_ram_address)
	ld de, (_ram_destination)
	call depack
	ret


	._s_title
	BINARY "../bin/titlec.bin"
	._s_marco
	._s_ending
	BINARY "../bin/endingc.bin"

._blackout
	ld	hl,240 % 256	;const
	ld	a,l
	ld	(_rda),a
	ld a, 0xc0
	.bo_l1
	ld h, a
	ld l, 0
	ld b, a
	ld a, (_rda)
	ld (hl), a
	ld a, b
	ld d, a
	ld e, 1
	ld bc, 0x5ff
	ldir
	add 8
	jr nz, bo_l1
	ret


;	SECTION	text

._my_inks
	defm	""
	defb	10

	defm	""
	defb	20

	defm	""
	defb	30

	defm	""
	defb	11

	defm	""
	defb	11

	defm	""
	defb	11

	defm	""
	defb	11

	defm	""
	defb	11

	defm	""
	defb	11

	defm	""
	defb	11

	defm	""
	defb	11

	defm	""
	defb	11

	defm	""
	defb	11

	defm	""
	defb	11

	defm	""
	defb	11

	defm	""
	defb	11

;	SECTION	code


;	SECTION	text

._mapa
	defm	""
	defb	18

	defm	""
	defb	16

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	3

	defm	"3330"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	"f"
	defb	0

	defm	""
	defb	1

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	5

	defm	"UU"
	defb	0

	defm	"31"
	defb	3

	defm	"3"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	"`"
	defb	0

	defm	"@"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	4

	defm	""
	defb	0

	defm	""
	defb	16

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	"UUUP"
	defb	3

	defm	"3330"
	defb	0

	defm	""
	defb	5

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	1

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	14

	defm	"!"
	defb	17

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	0

	defm	""
	defb	192

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	192

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	12

	defm	""
	defb	188

	defm	""
	defb	11

	defm	""
	defb	192

	defm	""
	defb	0

	defm	""
	defb	5

	defm	"UUP"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	"UUUUUP"
	defb	0

	defm	""
	defb	0

	defm	"UUUUP"
	defb	0

	defm	"UPUU"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	6

	defm	"eUUUUUUU"
	defb	5

	defm	"UUUUUU"
	defb	1

	defm	""
	defb	17

	defm	""
	defb	1

	defm	"!"
	defb	17

	defm	""
	defb	0

	defm	"@"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	1

	defm	""
	defb	16

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	"3333"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	"f"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	16

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	5

	defm	"UUP"
	defb	3

	defm	"3"
	defb	0

	defm	"30"
	defb	0

	defm	""
	defb	0

	defm	"`"
	defb	0

	defm	""
	defb	6

	defm	"`"
	defb	0

	defm	""
	defb	0

	defm	"f"
	defb	2

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	224

	defm	""
	defb	21

	defm	"UUU"
	defb	0

	defm	""
	defb	16

	defm	"332@"
	defb	0

	defm	"P"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	192

	defm	""
	defb	0

	defm	""
	defb	176

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	203

	defm	""
	defb	176

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	5

	defm	"UUUU"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	5

	defm	"UUU"
	defb	176

	defm	""
	defb	0

	defm	"UP"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	4

	defm	""
	defb	0

	defm	"UUUUUUP"
	defb	0

	defm	"UUUUUP"
	defb	5

	defm	"U"
	defb	5

	defm	"UQ"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	"UUUUUUUP"
	defb	17

	defm	"!"
	defb	17

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	18

	defm	""
	defb	16

	defm	""
	defb	0

	defm	"'wwq`"
	defb	0

	defm	""
	defb	16

	defm	""
	defb	0

	defm	""
	defb	4

	defm	""
	defb	0

	defm	""
	defb	0

	defm	"f"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	25

	defm	""
	defb	208

	defm	""
	defb	0

	defm	""
	defb	1

	defm	""
	defb	3

	defm	"330"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	"a"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	"f"
	defb	1

	defm	""
	defb	169

	defm	""
	defb	144

	defm	""
	defb	0

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	16

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	"@"
	defb	0

	defm	" "
	defb	154

	defm	""
	defb	157

	defm	""
	defb	3

	defm	"3330M"
	defb	221

	defm	""
	defb	221

	defm	""
	defb	221

	defm	""
	defb	221

	defm	""
	defb	221

	defm	""
	defb	209

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	16

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	1

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	"3333$"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	1

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	15

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	1

	defm	""
	defb	3

	defm	""
	defb	17

	defm	""
	defb	0

	defm	""
	defb	0

	defm	"332"
	defb	1

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	224

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	16

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	16

	defm	" "
	defb	3

	defm	"3331"
	defb	16

	defm	"3333"
	defb	16

	defm	""
	defb	4

	defm	"`"
	defb	1

	defm	""
	defb	3

	defm	"30"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	2

	defm	""
	defb	29

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	1

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	1

	defm	""
	defb	17

	defm	"!"
	defb	17

	defm	""
	defb	16

	defm	""
	defb	0

	defm	"A"
	defb	0

	defm	""
	defb	0

	defm	"f"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	1

	defm	""
	defb	153

	defm	""
	defb	208

	defm	""
	defb	0

	defm	""
	defb	21

	defm	"UUU"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	16

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	16

	defm	""
	defb	153

	defm	""
	defb	208

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	4

	defm	""
	defb	132

	defm	"D"
	defb	132

	defm	"D"
	defb	132

	defm	"A"
	defb	0

	defm	"f"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	"f"
	defb	0

	defm	""
	defb	1

	defm	""
	defb	10

	defm	""
	defb	9

	defm	""
	defb	157

	defm	""
	defb	16

	defm	"33"
	defb	17

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	16

	defm	""
	defb	6

	defm	""
	defb	0

	defm	""
	defb	1

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	1

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	1

	defm	""
	defb	3

	defm	"1"
	defb	17

	defm	" 333"
	defb	5

	defm	"UUUQ`"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	16

	defm	""
	defb	0

	defm	""
	defb	0

	defm	" "
	defb	17

	defm	""
	defb	0

	defm	"3333"
	defb	16

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	" "
	defb	0

	defm	"@"
	defb	1

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	16

	defm	""
	defb	0

	defm	""
	defb	1

	defm	""
	defb	1

	defm	""
	defb	3

	defm	"33"
	defb	16

	defm	"3"
	defb	1

	defm	""
	defb	1

	defm	""
	defb	3

	defm	""
	defb	16

	defm	"31"
	defb	0

	defm	"`"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	"@"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	4

	defm	""
	defb	2

	defm	""
	defb	0

	defm	""
	defb	9

	defm	""
	defb	169

	defm	""
	defb	16

	defm	"33"
	defb	0

	defm	""
	defb	10

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	16

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	12

	defm	""
	defb	12

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	16

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	145

	defm	""
	defb	3

	defm	"337q"
	defb	3

	defm	"30"
	defb	0

	defm	"33"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	208

	defm	""
	defb	208

	defm	""
	defb	0

	defm	""
	defb	1

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	10

	defm	""
	defb	16

	defm	"0"
	defb	3

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	16

	defm	"33"
	defb	0

	defm	""
	defb	3

	defm	"3"
	defb	16

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	1

	defm	""
	defb	3

	defm	"33"
	defb	0

	defm	"32"
	defb	0

	defm	""
	defb	3

	defm	""
	defb	0

	defm	"3"
	defb	193

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	17

	defm	""
	defb	16

	defm	"3"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	12

	defm	""
	defb	16

	defm	""
	defb	16

	defm	"0"
	defb	3

	defm	"333032"
	defb	16

	defm	"0"
	defb	16

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	3

	defm	"330"
	defb	0

	defm	""
	defb	3

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	1

	defm	"U"
	defb	3

	defm	"3"
	defb	1

	defm	""
	defb	3

	defm	"1"
	defb	16

	defm	""
	defb	3

	defm	"331"
	defb	0

	defm	"f"
	defb	0

	defm	""
	defb	16

	defm	"33"
	defb	0

	defm	""
	defb	0

	defm	"33"
	defb	16

	defm	""
	defb	16

	defm	""
	defb	0

	defm	"3331"
	defb	16

	defm	""
	defb	13

	defm	""
	defb	153

	defm	""
	defb	153

	defm	""
	defb	153

	defm	""
	defb	153

	defm	""
	defb	153

	defm	""
	defb	153

	defm	""
	defb	16

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	6

	defm	"`"
	defb	0

	defm	""
	defb	0

	defm	"`"
	defb	16

	defm	""
	defb	0

	defm	""
	defb	160

	defm	""
	defb	146

	defm	""
	defb	3

	defm	"330"
	defb	1

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	6

	defm	"`"
	defb	0

	defm	""
	defb	176

	defm	""
	defb	176

	defm	""
	defb	0

	defm	""
	defb	1

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	9

	defm	""
	defb	16

	defm	"1"
	defb	3

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	16

	defm	"33"
	defb	0

	defm	""
	defb	3

	defm	"30"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	10

	defm	""
	defb	10

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	16

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	1

	defm	""
	defb	3

	defm	"330"
	defb	1

	defm	""
	defb	3

	defm	"30"
	defb	0

	defm	"30"
	defb	28

	defm	""
	defb	3

	defm	"3"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	16

	defm	""
	defb	16

	defm	"1"
	defb	3

	defm	"333"
	defb	0

	defm	"3331"
	defb	30

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	3

	defm	"0"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	12

	defm	""
	defb	177

	defm	""
	defb	1

	defm	""
	defb	192

	defm	"33"
	defb	16

	defm	"33r"
	defb	3

	defm	""
	defb	0

	defm	""
	defb	3

	defm	"1"
	defb	0

	defm	"@"
	defb	0

	defm	"333"
	defb	0

	defm	""
	defb	0

	defm	"0"
	defb	0

	defm	" ! 33"
	defb	0

	defm	"3 3333"
	defb	16

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	3

	defm	"30"
	defb	0

	defm	""
	defb	3

	defm	"31 "
	defb	0

	defm	""
	defb	0

	defm	""
	defb	1

	defm	""
	defb	3

	defm	"330"
	defb	1

	defm	""
	defb	3

	defm	"30"
	defb	0

	defm	"33"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	1

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	16

	defm	""
	defb	3

	defm	"33"
	defb	0

	defm	""
	defb	27

	defm	""
	defb	3

	defm	"3"
	defb	0

	defm	""
	defb	3

	defm	"30"
	defb	215

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	16

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	1

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	3

	defm	"0"
	defb	1

	defm	""
	defb	0

	defm	""
	defb	3

	defm	"0"
	defb	0

	defm	"3"
	defb	0

	defm	""
	defb	10

	defm	""
	defb	173

	defm	"}G"
	defb	0

	defm	""
	defb	7

	defm	""
	defb	208

	defm	""
	defb	1

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	" 3303333"
	defb	16

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	3

	defm	"330"
	defb	0

	defm	""
	defb	3

	defm	"32"
	defb	2

	defm	""
	defb	3

	defm	"3333"
	defb	1

	defm	""
	defb	3

	defm	"3332"
	defb	6

	defm	""
	defb	0

	defm	""
	defb	0

	defm	"333"
	defb	0

	defm	""
	defb	3

	defm	"3<"
	defb	16

	defm	""
	defb	18

	defm	""
	defb	3

	defm	"0"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	16

	defm	"30"
	defb	3

	defm	";"
	defb	16

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	"30"
	defb	0

	defm	"33"
	defb	1

	defm	""
	defb	1

	defm	""
	defb	3

	defm	"33331"
	defb	0

	defm	""
	defb	3

	defm	"30"
	defb	1

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	1

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	"!"
	defb	3

	defm	"33"
	defb	0

	defm	""
	defb	17

	defm	""
	defb	3

	defm	"3"
	defb	0

	defm	""
	defb	3

	defm	"30p"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	16

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	1

	defm	"wr"
	defb	3

	defm	"0"
	defb	1

	defm	""
	defb	17

	defm	""
	defb	3

	defm	"0"
	defb	0

	defm	"3"
	defb	17

	defm	""
	defb	9

	defm	""
	defb	215

	defm	""
	defb	7

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	"p"
	defb	2

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	16

	defm	""
	defb	0

	defm	""
	defb	0

	defm	"1"
	defb	0

	defm	""
	defb	16

	defm	"33"
	defb	0

	defm	""
	defb	3

	defm	"30"
	defb	0

	defm	""
	defb	157

	defm	""
	defb	157

	defm	""
	defb	208

	defm	""
	defb	0

	defm	""
	defb	218

	defm	""
	defb	0

	defm	""
	defb	1

	defm	""
	defb	3

	defm	"3333"
	defb	17

	defm	""
	defb	3

	defm	"3331"
	defb	224

	defm	""
	defb	0

	defm	""
	defb	0

	defm	"333"
	defb	0

	defm	""
	defb	0

	defm	"33"
	defb	16

	defm	""
	defb	16

	defm	"31"
	defb	17

	defm	""
	defb	17

	defm	""
	defb	17

	defm	" 31"
	defb	3

	defm	"3"
	defb	16

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	1

	defm	""
	defb	16

	defm	"30"
	defb	0

	defm	""
	defb	3

	defm	"3"
	defb	17

	defm	""
	defb	1

	defm	""
	defb	0

	defm	"33331"
	defb	2

	defm	""
	defb	3

	defm	"31"
	defb	17

	defm	""
	defb	0

	defm	""
	defb	224

	defm	""
	defb	0

	defm	"333"
	defb	0

	defm	"033"
	defb	16

	defm	""
	defb	16

	defm	"33333"
	defb	16

	defm	""
	defb	0

	defm	""
	defb	16

	defm	"33"
	defb	0

	defm	""
	defb	3

	defm	"30"
	defb	0

	defm	""
	defb	169

	defm	""
	defb	170

	defm	""
	defb	157

	defm	""
	defb	13

	defm	""
	defb	144

	defm	""
	defb	0

	defm	""
	defb	16

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	1

	defm	""
	defb	3

	defm	"330"
	defb	1

	defm	"www{ww"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	1

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	16

	defm	"3"
	defb	17

	defm	"!"
	defb	0

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	18

	defm	""
	defb	17

	defm	""
	defb	18

	defm	""
	defb	17

	defm	""
	defb	16

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	" "
	defb	0

	defm	""
	defb	0

	defm	""
	defb	3

	defm	"3"
	defb	224

	defm	"30"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	"333"
	defb	3

	defm	"31"
	defb	3

	defm	" "
	defb	16

	defm	"33333"
	defb	16

	defm	"2www"
	defb	22

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	7

	defm	"wwwq"
	defb	3

	defm	"31"
	defb	1

	defm	""
	defb	18

	defm	""
	defb	17

	defm	""
	defb	18

	defm	""
	defb	17

	defm	""
	defb	16

	defm	"2"
	defb	1

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	17

	defm	"!"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	18

	defm	""
	defb	17

	defm	""
	defb	3

	defm	"3"
	defb	16

	defm	" "
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	3

	defm	""
	defb	16

	defm	"3333"
	defb	16

	defm	""
	defb	14

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	"3"
	defb	2

	defm	" "
	defb	0

	defm	""
	defb	0

	defm	""
	defb	1

	defm	""
	defb	3

	defm	"330"
	defb	1

	defm	""
	defb	3

	defm	"30"
	defb	0

	defm	"33"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	160

	defm	""
	defb	10

	defm	""
	defb	160

	defm	""
	defb	170

	defm	""
	defb	0

	defm	""
	defb	1

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	16

	defm	"3"
	defb	18

	defm	""
	defb	17

	defm	""
	defb	0

	defm	""
	defb	17

	defm	"!"
	defb	17

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	16

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	16

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	17

	defm	""
	defb	3

	defm	"0"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	1

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	1

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	"30"
	defb	3

	defm	"33333 "
	defb	0

	defm	""
	defb	0

	defm	""
	defb	3

	defm	"33033"
	defb	0

	defm	"1"
	defb	1

	defm	"wwww"
	defb	16

	defm	"1"
	defb	1

	defm	""
	defb	17

	defm	""
	defb	18

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	17

	defm	""
	defb	17

	defm	"!"
	defb	17

	defm	""
	defb	17

	defm	""
	defb	3

	defm	"3"
	defb	16

	defm	""
	defb	17

	defm	""
	defb	17

	defm	"!"
	defb	17

	defm	""
	defb	17

	defm	""
	defb	3

	defm	""
	defb	16

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	16

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	1

	defm	"!"
	defb	17

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	16

	defm	"3"
	defb	17

	defm	""
	defb	1

	defm	""
	defb	3

	defm	"33331"
	defb	3

	defm	"3331"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	4

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	192

	defm	""
	defb	1

	defm	""
	defb	16

	defm	""
	defb	0

	defm	""
	defb	17

	defm	""
	defb	16

	defm	"333"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	"3"
	defb	0

	defm	"0"
	defb	6

	defm	"@"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	4

	defm	"`"
	defb	0

	defm	""
	defb	16

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	1

	defm	""
	defb	0

	defm	"3>"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	3

	defm	"0"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	"fff"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	1

	defm	""
	defb	5

	defm	"U"
	defb	0

	defm	""
	defb	23

	defm	"wUU"
	defb	0

	defm	""
	defb	11

	defm	""
	defb	187

	defm	""
	defb	203

	defm	"{"
	defb	199

	defm	"wp"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	1

	defm	""
	defb	3

	defm	"33332"
	defb	3

	defm	"3331"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	"3"
	defb	0

	defm	"30330"
	defb	16

	defm	""
	defb	16

	defm	""
	defb	0

	defm	""
	defb	0

	defm	"0"
	defb	0

	defm	""
	defb	0

	defm	" 33"
	defb	0

	defm	"3"
	defb	16

	defm	"`"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	3

	defm	"3"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	1

	defm	""
	defb	1

	defm	""
	defb	3

	defm	"33331"
	defb	5

	defm	"P33Q"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	"ww"
	defb	188

	defm	""
	defb	0

	defm	"333"
	defb	16

	defm	""
	defb	16

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	"3"
	defb	16

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	"3"
	defb	0

	defm	""
	defb	0

	defm	"l"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	"F"
	defb	0

	defm	""
	defb	16

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	1

	defm	""
	defb	224

	defm	"330"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	3

	defm	"0"
	defb	1

	defm	""
	defb	0

	defm	""
	defb	6

	defm	"LD"
	defb	180

	defm	"`"
	defb	0

	defm	""
	defb	1

	defm	""
	defb	7

	defm	"w"
	defb	0

	defm	""
	defb	16

	defm	"33"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	192

	defm	""
	defb	0

	defm	""
	defb	0

	defm	"3"
	defb	0

	defm	"0"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	" "
	defb	0

	defm	""
	defb	0

	defm	""
	defb	1

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	16

	defm	""
	defb	1

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	16

	defm	"!"
	defb	18

	defm	""
	defb	16

	defm	"1"
	defb	18

	defm	""
	defb	17

	defm	""
	defb	16

	defm	"33"
	defb	224

	defm	"3."
	defb	0

	defm	""
	defb	0

	defm	""
	defb	2

	defm	""
	defb	0

	defm	""
	defb	3

	defm	"3"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	2

	defm	""
	defb	1

	defm	""
	defb	3

	defm	"33331"
	defb	3

	defm	"3331"
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	"3"
	defb	0

	defm	"30333"
	defb	16

	defm	"!"
	defb	17

	defm	""
	defb	17

	defm	"!"
	defb	16

	defm	"3"
	defb	16

	defm	""
	defb	17

	defm	""
	defb	16

	defm	"3"
	defb	17

	defm	""
	defb	16

	defm	""
	defb	0

	defm	"`"
	defb	1

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	17

	defm	""
	defb	3

	defm	"31"
;	SECTION	code


;	SECTION	text

._cerrojos
	defb	5
	defb	6
	defb	3
	defb	0

;	SECTION	code

	XDEF tiles
	._tileset
	.tiles
	._font
	BINARY "../bin/font.bin"
	._tspatterns
	BINARY "../bin/work.bin"
;	SECTION	text

._malotes
	defb	64
	defb	16
	defb	64
	defb	16
	defb	64
	defb	128
	defb	0
	defb	4
	defb	3
	defb	208
	defb	16
	defb	208
	defb	16
	defb	96
	defb	16
	defb	-2
	defb	0
	defb	0
	defb	192
	defb	0
	defb	192
	defb	0
	defb	112
	defb	0
	defb	-2
	defb	0
	defb	0
	defb	128
	defb	0
	defb	128
	defb	0
	defb	128
	defb	64
	defb	0
	defb	1
	defb	2
	defb	144
	defb	16
	defb	144
	defb	16
	defb	176
	defb	96
	defb	2
	defb	2
	defb	2
	defb	48
	defb	64
	defb	48
	defb	64
	defb	48
	defb	128
	defb	0
	defb	1
	defb	4
	defb	16
	defb	32
	defb	16
	defb	32
	defb	96
	defb	32
	defb	2
	defb	0
	defb	1
	defb	144
	defb	96
	defb	144
	defb	96
	defb	144
	defb	0
	defb	0
	defb	-1
	defb	3
	defb	176
	defb	0
	defb	176
	defb	0
	defb	176
	defb	80
	defb	0
	defb	1
	defb	2
	defb	96
	defb	112
	defb	96
	defb	112
	defb	48
	defb	112
	defb	-1
	defb	0
	defb	3
	defb	48
	defb	0
	defb	48
	defb	0
	defb	48
	defb	32
	defb	0
	defb	1
	defb	1
	defb	208
	defb	0
	defb	208
	defb	0
	defb	208
	defb	64
	defb	0
	defb	2
	defb	1
	defb	64
	defb	0
	defb	64
	defb	0
	defb	64
	defb	80
	defb	0
	defb	1
	defb	1
	defb	96
	defb	0
	defb	96
	defb	0
	defb	96
	defb	64
	defb	0
	defb	1
	defb	1
	defb	160
	defb	0
	defb	160
	defb	0
	defb	208
	defb	80
	defb	2
	defb	2
	defb	2
	defb	80
	defb	112
	defb	80
	defb	112
	defb	16
	defb	112
	defb	-2
	defb	0
	defb	2
	defb	96
	defb	0
	defb	96
	defb	0
	defb	0
	defb	0
	defb	-1
	defb	0
	defb	2
	defb	224
	defb	0
	defb	224
	defb	0
	defb	224
	defb	48
	defb	0
	defb	1
	defb	2
	defb	192
	defb	48
	defb	192
	defb	48
	defb	128
	defb	48
	defb	-1
	defb	0
	defb	4
	defb	160
	defb	16
	defb	160
	defb	16
	defb	160
	defb	96
	defb	0
	defb	2
	defb	1
	defb	16
	defb	96
	defb	16
	defb	96
	defb	80
	defb	128
	defb	4
	defb	4
	defb	2
	defb	16
	defb	80
	defb	16
	defb	80
	defb	96
	defb	48
	defb	1
	defb	-1
	defb	1
	defb	16
	defb	16
	defb	16
	defb	16
	defb	96
	defb	16
	defb	2
	defb	0
	defb	2
	defb	160
	defb	0
	defb	160
	defb	0
	defb	160
	defb	144
	defb	0
	defb	2
	defb	3
	defb	48
	defb	32
	defb	48
	defb	32
	defb	144
	defb	32
	defb	2
	defb	0
	defb	3
	defb	112
	defb	48
	defb	112
	defb	48
	defb	112
	defb	128
	defb	0
	defb	1
	defb	2
	defb	160
	defb	96
	defb	160
	defb	96
	defb	160
	defb	0
	defb	0
	defb	-2
	defb	3
	defb	96
	defb	128
	defb	96
	defb	128
	defb	96
	defb	16
	defb	0
	defb	-2
	defb	4
	defb	144
	defb	16
	defb	144
	defb	16
	defb	176
	defb	112
	defb	2
	defb	2
	defb	3
	defb	112
	defb	48
	defb	112
	defb	48
	defb	32
	defb	16
	defb	-2
	defb	-2
	defb	1
	defb	64
	defb	128
	defb	64
	defb	128
	defb	208
	defb	128
	defb	1
	defb	0
	defb	4
	defb	208
	defb	112
	defb	208
	defb	112
	defb	112
	defb	112
	defb	-1
	defb	0
	defb	1
	defb	64
	defb	16
	defb	64
	defb	16
	defb	96
	defb	16
	defb	1
	defb	0
	defb	3
	defb	16
	defb	128
	defb	16
	defb	128
	defb	160
	defb	128
	defb	1
	defb	0
	defb	4
	defb	48
	defb	112
	defb	48
	defb	112
	defb	48
	defb	64
	defb	0
	defb	-1
	defb	4
	defb	80
	defb	48
	defb	80
	defb	48
	defb	160
	defb	96
	defb	2
	defb	2
	defb	2
	defb	208
	defb	112
	defb	208
	defb	112
	defb	128
	defb	112
	defb	-1
	defb	0
	defb	3
	defb	208
	defb	80
	defb	208
	defb	80
	defb	208
	defb	16
	defb	0
	defb	-1
	defb	2
	defb	16
	defb	16
	defb	16
	defb	16
	defb	96
	defb	128
	defb	4
	defb	4
	defb	3
	defb	64
	defb	0
	defb	64
	defb	0
	defb	112
	defb	48
	defb	2
	defb	2
	defb	1
	defb	16
	defb	64
	defb	16
	defb	64
	defb	80
	defb	112
	defb	1
	defb	1
	defb	2
	defb	208
	defb	16
	defb	208
	defb	16
	defb	192
	defb	128
	defb	-2
	defb	2
	defb	3
	defb	16
	defb	0
	defb	16
	defb	0
	defb	112
	defb	32
	defb	1
	defb	1
	defb	2
	defb	208
	defb	0
	defb	208
	defb	0
	defb	176
	defb	48
	defb	-2
	defb	2
	defb	3
	defb	64
	defb	64
	defb	64
	defb	64
	defb	96
	defb	0
	defb	1
	defb	-1
	defb	1
	defb	160
	defb	112
	defb	160
	defb	112
	defb	160
	defb	64
	defb	0
	defb	-1
	defb	4
	defb	144
	defb	80
	defb	144
	defb	80
	defb	32
	defb	80
	defb	-1
	defb	0
	defb	4
	defb	64
	defb	0
	defb	64
	defb	0
	defb	176
	defb	16
	defb	1
	defb	1
	defb	0
	defb	192
	defb	48
	defb	192
	defb	48
	defb	80
	defb	48
	defb	-1
	defb	0
	defb	4
	defb	112
	defb	32
	defb	112
	defb	32
	defb	176
	defb	32
	defb	1
	defb	0
	defb	3
	defb	64
	defb	80
	defb	64
	defb	80
	defb	192
	defb	112
	defb	2
	defb	2
	defb	2
	defb	192
	defb	48
	defb	192
	defb	48
	defb	32
	defb	48
	defb	-1
	defb	0
	defb	4
	defb	16
	defb	32
	defb	16
	defb	32
	defb	128
	defb	32
	defb	1
	defb	0
	defb	1
	defb	16
	defb	64
	defb	16
	defb	64
	defb	112
	defb	112
	defb	2
	defb	2
	defb	2
	defb	208
	defb	64
	defb	208
	defb	64
	defb	128
	defb	64
	defb	-1
	defb	0
	defb	2
	defb	48
	defb	16
	defb	48
	defb	16
	defb	48
	defb	80
	defb	0
	defb	2
	defb	1
	defb	64
	defb	32
	defb	64
	defb	32
	defb	64
	defb	80
	defb	0
	defb	2
	defb	3
	defb	16
	defb	112
	defb	16
	defb	112
	defb	112
	defb	112
	defb	1
	defb	0
	defb	1
	defb	192
	defb	128
	defb	192
	defb	128
	defb	192
	defb	16
	defb	0
	defb	-1
	defb	4
	defb	112
	defb	48
	defb	112
	defb	48
	defb	16
	defb	48
	defb	-2
	defb	0
	defb	3
	defb	176
	defb	48
	defb	176
	defb	48
	defb	32
	defb	48
	defb	-1
	defb	0
	defb	1
	defb	176
	defb	64
	defb	176
	defb	64
	defb	48
	defb	64
	defb	-1
	defb	0
	defb	1
	defb	16
	defb	0
	defb	16
	defb	0
	defb	192
	defb	32
	defb	2
	defb	2
	defb	2
	defb	32
	defb	112
	defb	32
	defb	112
	defb	192
	defb	112
	defb	2
	defb	0
	defb	4
	defb	192
	defb	32
	defb	192
	defb	32
	defb	48
	defb	32
	defb	-2
	defb	0
	defb	4
	defb	176
	defb	80
	defb	176
	defb	80
	defb	48
	defb	80
	defb	-1
	defb	0
	defb	1
	defb	208
	defb	80
	defb	208
	defb	80
	defb	32
	defb	80
	defb	-1
	defb	0
	defb	4
	defb	64
	defb	64
	defb	64
	defb	64
	defb	176
	defb	64
	defb	1
	defb	0
	defb	2
	defb	16
	defb	0
	defb	16
	defb	0
	defb	0
	defb	144
	defb	-3
	defb	3
	defb	0
	defb	16
	defb	48
	defb	16
	defb	48
	defb	208
	defb	48
	defb	1
	defb	0
	defb	4
	defb	96
	defb	64
	defb	96
	defb	64
	defb	96
	defb	128
	defb	0
	defb	1
	defb	1
	defb	208
	defb	80
	defb	208
	defb	80
	defb	128
	defb	128
	defb	-2
	defb	2
	defb	3
	defb	96
	defb	32
	defb	96
	defb	32
	defb	96
	defb	96
	defb	0
	defb	2
	defb	6
	defb	128
	defb	80
	defb	128
	defb	80
	defb	224
	defb	80
	defb	2
	defb	0
	defb	4
	defb	96
	defb	112
	defb	96
	defb	112
	defb	32
	defb	112
	defb	-1
	defb	0
	defb	3
	defb	112
	defb	16
	defb	112
	defb	16
	defb	112
	defb	80
	defb	0
	defb	1
	defb	2
	defb	48
	defb	96
	defb	48
	defb	96
	defb	48
	defb	0
	defb	0
	defb	-2
	defb	1
	defb	176
	defb	48
	defb	176
	defb	48
	defb	176
	defb	128
	defb	0
	defb	2
	defb	3
	defb	160
	defb	32
	defb	160
	defb	32
	defb	192
	defb	80
	defb	2
	defb	2
	defb	1
	defb	96
	defb	48
	defb	96
	defb	48
	defb	96
	defb	0
	defb	0
	defb	-1
	defb	2
	defb	144
	defb	144
	defb	144
	defb	144
	defb	48
	defb	144
	defb	-1
	defb	0
	defb	3
	defb	32
	defb	80
	defb	32
	defb	80
	defb	32
	defb	16
	defb	0
	defb	-2
	defb	1
	defb	192
	defb	80
	defb	192
	defb	80
	defb	192
	defb	32
	defb	0
	defb	-2
	defb	2
	defb	112
	defb	80
	defb	112
	defb	80
	defb	112
	defb	32
	defb	0
	defb	-1
	defb	3
	defb	208
	defb	48
	defb	208
	defb	48
	defb	32
	defb	48
	defb	-1
	defb	0
	defb	4
	defb	64
	defb	32
	defb	64
	defb	32
	defb	192
	defb	32
	defb	1
	defb	0
	defb	2
	defb	80
	defb	96
	defb	80
	defb	96
	defb	112
	defb	96
	defb	1
	defb	0
	defb	1
	defb	112
	defb	16
	defb	112
	defb	16
	defb	16
	defb	80
	defb	-2
	defb	2
	defb	3
	defb	176
	defb	64
	defb	176
	defb	64
	defb	176
	defb	96
	defb	0
	defb	1
	defb	1
	defb	208
	defb	80
	defb	208
	defb	80
	defb	208
	defb	128
	defb	0
	defb	1
	defb	1

;	SECTION	code

;	SECTION	text

._hotspots
	defb	22
	defb	2
	defb	0
	defb	120
	defb	2
	defb	0
	defb	113
	defb	1
	defb	0
	defb	216
	defb	1
	defb	0
	defb	81
	defb	1
	defb	0
	defb	24
	defb	1
	defb	0
	defb	98
	defb	1
	defb	0
	defb	115
	defb	1
	defb	0
	defb	69
	defb	1
	defb	0
	defb	129
	defb	2
	defb	0
	defb	209
	defb	2
	defb	0
	defb	18
	defb	1
	defb	0
	defb	200
	defb	1
	defb	0
	defb	100
	defb	1
	defb	0
	defb	148
	defb	1
	defb	0
	defb	34
	defb	1
	defb	0
	defb	66
	defb	1
	defb	0
	defb	209
	defb	1
	defb	0
	defb	19
	defb	1
	defb	0
	defb	113
	defb	1
	defb	0
	defb	133
	defb	1
	defb	0
	defb	35
	defb	1
	defb	0
	defb	70
	defb	1
	defb	0
	defb	87
	defb	1
	defb	0
	defb	129
	defb	1
	defb	0
	defb	87
	defb	1
	defb	0
	defb	114
	defb	1
	defb	0
	defb	100
	defb	1
	defb	0
	defb	129
	defb	1
	defb	0
	defb	212
	defb	1
	defb	0

;	SECTION	code

	._sprites
	BINARY "../bin/sprites.bin"
	._sprite_17_a
	BINARY "../bin/sprites_extra.bin"
	._sprite_18_a
	defs 96, 0
;	SECTION	text

._sm_cox
	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

;	SECTION	code


;	SECTION	text

._sm_coy
	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

;	SECTION	code


;	SECTION	text

._sm_invfunc
	defw	cpc_PutSpTileMap8x16
	defw	cpc_PutSpTileMap8x16
	defw	cpc_PutSpTileMap8x16
	defw	cpc_PutSpTileMap8x16
	defw	cpc_PutSpTileMap8x16
	defw	cpc_PutSpTileMap8x16
	defw	cpc_PutSpTileMap8x16
	defw	cpc_PutSpTileMap8x16
	defw	cpc_PutSpTileMap8x16
	defw	cpc_PutSpTileMap8x16
	defw	cpc_PutSpTileMap8x16
	defw	cpc_PutSpTileMap8x16
	defw	cpc_PutSpTileMap8x16
	defw	cpc_PutSpTileMap8x16
	defw	cpc_PutSpTileMap8x16
	defw	cpc_PutSpTileMap8x16

;	SECTION	code

;	SECTION	text

._sm_updfunc
	defw	cpc_PutTrSp8x16TileMap2b
	defw	cpc_PutTrSp8x16TileMap2b
	defw	cpc_PutTrSp8x16TileMap2b
	defw	cpc_PutTrSp8x16TileMap2b
	defw	cpc_PutTrSp8x16TileMap2b
	defw	cpc_PutTrSp8x16TileMap2b
	defw	cpc_PutTrSp8x16TileMap2b
	defw	cpc_PutTrSp8x16TileMap2b
	defw	cpc_PutTrSp8x16TileMap2b
	defw	cpc_PutTrSp8x16TileMap2b
	defw	cpc_PutTrSp8x16TileMap2b
	defw	cpc_PutTrSp8x16TileMap2b
	defw	cpc_PutTrSp8x16TileMap2b
	defw	cpc_PutTrSp8x16TileMap2b
	defw	cpc_PutTrSp8x16TileMap2b
	defw	cpc_PutTrSp8x16TileMap2b

;	SECTION	code

	._sm_sprptr
	defw _sprites + 0x0000, _sprites + 0x0040, _sprites + 0x0080, _sprites + 0x00C0
	defw _sprites + 0x0100, _sprites + 0x0140, _sprites + 0x0180, _sprites + 0x01C0
	defw _sprites + 0x0200, _sprites + 0x0240, _sprites + 0x0280, _sprites + 0x02C0
	defw _sprites + 0x0300, _sprites + 0x0340, _sprites + 0x0380, _sprites + 0x03C0
	; LUT for transparent pixels in sprites
	; taken from CPCTelera
	._trpixlutc
	BINARY "assets/trpixlutc.bin"

._attr
	ld hl, 4
	add hl, sp
	ld c, (hl)
	dec hl
	dec hl
	ld a, (hl)
	._attr_2
	cp 10
	jr c, _attr_1
	ld hl, 0
	ret
	._attr_1
	ld b, a
	ld a, c
	cp 15
	jr c, _attr_1b
	ld hl, 0
	ret
	._attr_1b
	ld a, b
	sla a
	sla a
	sla a
	sla a
	sub b
	add c
	ld d, 0
	ld e, a
	ld hl, _map_attr
	add hl, de
	ld l, (hl)
	._attr_end
	ld h, 0
	ret



._qtile
	ld hl, 4
	add hl, sp
	ld c, (hl)
	dec hl
	dec hl
	ld a, (hl)
	.qtile_do
	ld b, a
	sla a
	sla a
	sla a
	sla a
	sub b
	add c
	ld d, 0
	ld e, a
	ld hl, _map_buff
	add hl, de
	ld l, (hl)
	ld h, 0
	ret



._attr_mk2
	ld a, (_cx1)
	cp 15
	jr nc, _attr_reset
	ld a, (_cy1)
	cp 10
	jr c, _attr_do
	._attr_reset
	ld hl, 0
	ret
	._attr_do
	ld a, (_cy1)
	ld b, a
	sla a
	sla a
	sla a
	sla a
	sub b
	ld b, a
	ld a, (_cx1)
	add b
	ld e, a
	ld d, 0
	ld hl, _map_attr
	add hl, de
	ld a, (hl)
	ld h, 0
	ld l, a
	ret
	ret



.__tile_address
	ld a, (__y)
	add a, a ; 2 4
	add a, a ; 4 4
	add a, a ; 8 4
	ld h, 0 ; 2
	ld l, a ; 4
	add hl, hl ; 16 11
	add hl, hl ; 32 11
	; 44 t-states
	; HL = _y * 32
	ld a, (__x)
	ld e, a
	ld d, 0
	add hl, de
	; HL = _y * 32 + _x
	ld de, _nametable
	add hl, de
	ex de, hl
	; DE = buffer address
	ret



._draw_coloured_tile
	ld a, (__x)
	sub 1
	srl a
	ld (_xx), a
	ld a, (__y)
	sub 3
	srl a
	ld (_yy), a
	ld	hl,(_xx)
	ld	h,0
	push	hl
	ld	hl,(_yy)
	ld	h,0
	push	hl
	call	_attr
	pop	bc
	pop	bc
	ld	de,8	;const
	call	l_and
	ld	a,h
	or	l
	jp	nz,i_14
	ld	a,(__t)
	cp	#(16 % 256)
	jr	z,i_15_uge
	jp	c,i_15
.i_15_uge
	ld	a,(__t)
	cp	#(19 % 256)
	jp	z,i_15
	ld	hl,1	;const
	jr	i_16
.i_15
	ld	hl,0	;const
.i_16
	ld	a,h
	or	l
	jp	nz,i_14
	jr	i_17
.i_14
	ld	hl,1	;const
.i_17
	call	l_lneg
	ld	hl,0	;const
	rl	l
	ld	a,l
	ld	(_nocast),a
	ld a, (__t)
	sla a
	sla a
	add 64
	ld (__ta), a
	ld	a,(__t)
	cp	#(19 % 256)
	jp	nz,i_18
	ld	hl,192 % 256	;const
	ld	a,l
	ld	(_t_alt),a
	jp	i_19
.i_18
	ld	hl,(__ta)
	ld	h,0
	ld	de,128
	add	hl,de
	ld	h,0
	ld	a,l
	ld	(_t_alt),a
.i_19
	ld a, (_xx)
	dec a
	ld (_cx1), a
	ld a, (_yy)
	or a
	jr z, _dct_1_set_yy
	dec a
	._dct_1_set_yy
	ld (_cy1), a
	ld a, (_nocast)
	or a
	jr z, _dct_a1_set
	call _attr_mk2
	ld a, l
	and 8
	jr z, _dct_a1_set
	ld a, 1
	._dct_a1_set
	ld (_a1), a
	ld a, (_xx)
	ld (_cx1), a
	ld a, (_yy)
	or a
	jr z, _dct_2_set_yy
	dec a
	._dct_2_set_yy
	ld (_cy1), a
	ld a, (_nocast)
	or a
	jr z, _dct_a2_set
	call _attr_mk2
	ld a, l
	and 8
	jr z, _dct_a2_set
	ld a, 1
	._dct_a2_set
	ld (_a2), a
	ld a, (_xx)
	dec a
	ld (_cx1), a
	ld a, (_yy)
	ld (_cy1), a
	ld a, (_nocast)
	or a
	jr z, _dct_a3_set
	call _attr_mk2
	ld a, l
	and 8
	jr z, _dct_a3_set
	ld a, 1
	._dct_a3_set
	ld (_a3), a
	ld a, (_a1)
	or a
	jr nz, _dct_1_shadow
	ld a, (_a2)
	or a
	jr z, _dct_1_no_shadow
	ld a, (_a3)
	or a
	jr z, _dct_1_no_shadow
	._dct_1_shadow
	ld a, (_t_alt)
	ld (_t1), a
	jr _dct_1_increment
	._dct_1_no_shadow
	ld a, (__ta)
	ld (_t1), a
	._dct_1_increment
	ld hl, __ta
	inc (hl)
	ld hl, _t_alt
	inc (hl)
	ld a, (_a2)
	or a
	jr z, _dct_2_no_shadow
	._dct_2_shadow
	ld a, (_t_alt)
	ld (_t2), a
	jr _dct_2_increment
	._dct_2_no_shadow
	ld a, (__ta)
	ld (_t2), a
	._dct_2_increment
	ld hl, __ta
	inc (hl)
	ld hl, _t_alt
	inc (hl)
	ld a, (_a3)
	or a
	jr z, _dct_3_no_shadow
	._dct_3_shadow
	ld a, (_t_alt)
	ld (_t3), a
	jr _dct_3_increment
	._dct_3_no_shadow
	ld a, (__ta)
	ld (_t3), a
	._dct_3_increment
	ld hl, __ta
	inc (hl)
	ld hl, _t_alt
	inc (hl)
	ld a, (__ta)
	ld (_t4), a
	call __tile_address ; DE = buffer address
	ex de, hl
	ld a, (_t1)
	ld (hl), a
	inc hl
	ld a, (_t2)
	ld (hl), a
	ld bc, 31
	add hl, bc
	ld a, (_t3)
	ld (hl), a
	inc hl
	ld a, (_t4)
	ld (hl), a
	ret



._invalidate_tile
	ld a, (__x)
	ld e, a
	ld a, (__y)
	ld d, a
	call cpc_UpdTileTable
	inc e
	call cpc_UpdTileTable
	dec e
	inc d
	call cpc_UpdTileTable
	inc e
	call cpc_UpdTileTable
	ret



._invalidate_viewport
	ld B, 3
	ld C, 1
	ld D, 3+19
	ld E, 1+29
	call cpc_InvalidateRect
	ret



._draw_invalidate_coloured_tile_g
	call	_draw_coloured_tile_gamearea
	call	_invalidate_tile
	ret



._draw_coloured_tile_gamearea
	ld	a,(__x)
	ld	e,a
	ld	d,0
	ld	l,#(1 % 256)
	call	l_asl
	ld	de,1
	add	hl,de
	ld	h,0
	ld	a,l
	ld	(__x),a
	ld	a,(__y)
	ld	e,a
	ld	d,0
	ld	l,#(1 % 256)
	call	l_asl
	ld	de,3
	add	hl,de
	ld	h,0
	ld	a,l
	ld	(__y),a
	call	_draw_coloured_tile
	ret



._draw_decorations
	ld hl, (__gp_gen)
	._draw_decorations_loop
	ld a, (hl)
	cp 0xff
	ret z
	ld a, (hl)
	inc hl
	ld c, a
	and 0x0f
	ld (__y), a
	ld a, c
	srl a
	srl a
	srl a
	srl a
	ld (__x), a
	ld a, (hl)
	inc hl
	ld (__t), a
	push hl
	ld b, 0
	ld c, a
	ld hl, _behs
	add hl, bc
	ld a, (hl)
	ld (__n), a
	call _update_tile
	pop hl
	jr _draw_decorations_loop
	ret


;	SECTION	text

._utaux
	defm	""
	defb	0

;	SECTION	code



._update_tile
	ld a, (__x)
	ld c, a
	ld a, (__y)
	ld b, a
	sla a
	sla a
	sla a
	sla a
	sub b
	add c
	ld b, 0
	ld c, a
	ld hl, _map_attr
	add hl, bc
	ld a, (__n)
	ld (hl), a
	ld hl, _map_buff
	add hl, bc
	ld a, (__t)
	ld (hl), a
	call _draw_coloured_tile_gamearea
	ld a, (_is_rendering)
	or a
	ret nz
	call _invalidate_tile
	ret



._print_number2
	ld	a,(__t)
	ld	e,a
	ld	d,0
	ld	hl,10	;const
	call	l_div_u
	ld	de,16
	add	hl,de
	ld	h,0
	ld	a,l
	ld	(_rda),a
	ld	a,(__t)
	ld	e,a
	ld	d,0
	ld	hl,10	;const
	call	l_div_u
	ex	de,hl
	ld	de,16
	add	hl,de
	ld	h,0
	ld	a,l
	ld	(_rdb),a
	call __tile_address ; DE = buffer address
	ld a, (_rda)
	ld (de), a
	inc de
	ld a, (_rdb)
	ld (de), a
	ld a, (__x)
	ld e, a
	ld a, (__y)
	ld d, a
	call cpc_UpdTileTable
	inc e
	call cpc_UpdTileTable
	ret



._print_str
	xor a
	ld (_rdn), a ; Strlen
	call __tile_address ; DE = buffer address
	ld hl, (__gp_gen)
	.print_str_loop
	ld a, (hl)
	or a
	jr z, print_str_inv
	sub 32
	ld (de), a
	inc hl
	inc de
	ld a, (_rdn)
	inc a
	ld (_rdn), a
	jr print_str_loop
	.print_str_inv
	; Invalidate cells based upon strlen.
	ld a, (__y)
	ld b, a
	ld d, a
	ld a, (__x)
	ld c, a
	ld a, (_rdn)
	add c
	dec a
	ld e, a
	call cpc_InvalidateRect
	ret



._clear_sprites
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_gpit),a
	jp	i_23
.i_21
	ld	hl,_gpit
	ld	a,(hl)
	inc	(hl)
.i_23
	ld	a,(_gpit)
	cp	#(4 % 256)
	jp	z,i_22
	jp	nc,i_22
	ld	hl,_sp_sw
	push	hl
	ld	hl,(_gpit)
	ld	h,0
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	pop	de
	add	hl,de
	push	hl
	ld	hl,_sprite_18_a
	call	l_pint_pop
	jp	i_21
.i_22
	ret



._pal_set
	ld	hl,4 % 256	;const
	ld	a,l
	ld	(_gpit),a
.i_24
	ld	hl,_gpit
	ld	a,(hl)
	dec	(hl)
	ld	l,a
	and	a
	jp	z,i_25
	ld	hl,(_gpit)
	ld	h,0
	push	hl
	ld	hl,4	;const
	add	hl,sp
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	push	de
	ld	hl,(_gpit)
	ld	h,0
	pop	de
	add	hl,de
	ld	l,(hl)
	ld	h,0
	push	hl
	call	cpc_SetColour
	pop	bc
	pop	bc
	jp	i_24
.i_25
	ret



._cpc_UpdateNow
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	a,l
	and	a
	jp	z,i_26
	ld b, 0
	._cpc_screen_update_inv_loop
	push bc
	ld a, b
	sla a
	sla a
	sla a
	sla a
	ld d, 0
	ld e, a
	ld hl, _sp_sw
	add hl, de
	ld b, h
	ld c, l
	ld de, _cpc_screen_update_inv_ret
	push de
	ld de, 12
	add hl, de
	ld e, (hl)
	inc hl
	ld d, (hl)
	push de
	ld h, b
	ld l, c
	ret
	._cpc_screen_update_inv_ret
	pop bc
	inc b
	ld a, b
	cp 1 + 3 + 0 + 0
	jr nz, _cpc_screen_update_inv_loop
.i_26
	._cpc_screen_update_upd_buffer
	call cpc_UpdScr
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	a,l
	and	a
	jp	z,i_27
	ld b, 1 + 3 + 0 + 0
	._cpc_screen_update_upd_loop
	dec b
	push bc
	ld a, b
	sla a
	sla a
	sla a
	sla a
	ld d, 0
	ld e, a
	ld hl, _sp_sw
	add hl, de
	ld b, h
	ld c, l
	ld de, _cpc_screen_update_upd_ret
	push de
	ld de, 14
	add hl, de
	ld e, (hl)
	inc hl
	ld d, (hl)
	push de
	ld h, b
	ld l, c
	ret
	._cpc_screen_update_upd_ret
	pop bc
	xor a
	or b
	jr nz, _cpc_screen_update_upd_loop
	._cpc_screen_update_done
.i_27
	call cpc_ShowTouchedTiles
	call cpc_ResetTouchedTiles
	ret



._collide
	ld hl, 0
	ld a, (_cx2)
	ld c, a
	ld a, (_gpx)
	add 8
	cp c
	ret c
	ld a, (_gpx)
	ld c, a
	ld a, (_cx2)
	add 8
	cp c
	ret c
	ld a, (_cy2)
	ld c, a
	ld a, (_gpy)
	add 8
	cp c
	ret c
	ld a, (_gpy)
	ld c, a
	ld a, (_cy2)
	add 8
	cp c
	ret c
	ld l, 1
	ret



._cm_two_points
	ld a, (_cx1)
	cp 15
	jr nc, _cm_two_points_at1_reset
	ld a, (_cy1)
	cp 10
	jr c, _cm_two_points_at1_do
	._cm_two_points_at1_reset
	xor a
	jr _cm_two_points_at1_done
	._cm_two_points_at1_do
	ld a, (_cy1)
	ld b, a
	sla a
	sla a
	sla a
	sla a
	sub b
	ld b, a
	ld a, (_cx1)
	add b
	ld e, a
	ld d, 0
	ld hl, _map_attr
	add hl, de
	ld a, (hl)
	._cm_two_points_at1_done
	ld (_at1), a
	ld a, (_cx2)
	cp 15
	jr nc, _cm_two_points_at2_reset
	ld a, (_cy2)
	cp 10
	jr c, _cm_two_points_at2_do
	._cm_two_points_at2_reset
	xor a
	jr _cm_two_points_at2_done
	._cm_two_points_at2_do
	ld a, (_cy2)
	ld b, a
	sla a
	sla a
	sla a
	sla a
	sub b
	ld b, a
	ld a, (_cx2)
	add b
	ld e, a
	ld d, 0
	ld hl, _map_attr
	add hl, de
	ld a, (hl)
	._cm_two_points_at2_done
	ld (_at2), a
	ret



._rand
	.rand16
	ld hl, _seed
	ld a, (hl)
	ld e, a
	inc hl
	ld a, (hl)
	ld d, a
	;; Ahora DE = [SEED]
	ld a, d
	ld h, e
	ld l, 253
	or a
	sbc hl, de
	sbc a, 0
	sbc hl, de
	ld d, 0
	sbc a, d
	ld e, a
	sbc hl, de
	jr nc, nextrand
	inc hl
	.nextrand
	ld d, h
	ld e, l
	ld hl, _seed
	ld a, e
	ld (hl), a
	inc hl
	ld a, d
	ld (hl), a
	;; Ahora [SEED] = HL
	ld l, e
	ret
	ret



._abs
	pop	bc
	pop	hl
	push	hl
	push	bc
	xor	a
	or	h
	jp	p,i_28
	pop	bc
	pop	hl
	push	hl
	push	bc
	call	l_neg
	ret


.i_28
	pop	bc
	pop	hl
	push	hl
	push	bc
	ret


.i_29
	ret



._game_ending
	call	_blackout
	ld	hl,_s_ending
	push	hl
	ld	hl,36864	;const
	push	hl
	call	_unpack
	pop	bc
	pop	bc
	ld	hl,1	;const
	call	cpc_ShowTileMap
	ld	hl,0	;const
	call	_wyz_play_music
	ld	hl,500	;const
	push	hl
	call	_espera_activa
	pop	bc
	call	_wyz_stop_sound
	ret



._game_over
	ld	a,#(10 % 256 % 256)
	ld	(__x),a
	ld	a,#(11 % 256 % 256)
	ld	(__y),a
	ld	hl,_spacer
	ld	(__gp_gen),hl
	call	_print_str
	ld	a,#(10 % 256 % 256)
	ld	(__x),a
	ld	a,#(12 % 256 % 256)
	ld	(__y),a
	ld	hl,i_1+0
	ld	(__gp_gen),hl
	call	_print_str
	ld	a,#(10 % 256 % 256)
	ld	(__x),a
	ld	a,#(13 % 256 % 256)
	ld	(__y),a
	ld	hl,_spacer
	ld	(__gp_gen),hl
	call	_print_str
	ld	hl,0	;const
	push	hl
	call	_cpc_UpdateNow
	pop	bc
	ld	hl,500	;const
	push	hl
	call	_espera_activa
	pop	bc
	ret



._addsign
	ld	hl,4	;const
	call	l_gintsp	;
	xor	a
	or	h
	jp	m,i_30
	pop	bc
	pop	hl
	push	hl
	push	bc
	ret


.i_30
	pop	bc
	pop	hl
	push	hl
	push	bc
	call	l_neg
	ret


.i_31
	ret



._espera_activa
.i_32
	call	cpc_AnyKeyPressed
	ld	a,h
	or	l
	jp	nz,i_32
.i_33
.i_36
	halt
	halt
	halt
	halt
	halt
	halt
	call	cpc_AnyKeyPressed
	ld	a,h
	or	l
	jp	nz,i_35
.i_37
.i_34
	pop	de
	pop	hl
	dec	hl
	push	hl
	push	de
	ld	a,h
	or	l
	jp	nz,i_36
.i_35
	ret



._locks_init
	ld b, 1
	ld hl, _cerrojos + 3
	ld de, 4
	ld a, 1
	.init_cerrojos_loop
	ld (hl), a
	add hl, de
	djnz init_cerrojos_loop
	ret



._process_tile
	.push_boxes
	ld a, (_x0)
	ld c, a
	ld a, (_y0)
	call qtile_do
	ld a, l
	cp 14
	jp nz, push_boxes_end
	ld a, (_x1)
	ld c, a
	ld a, (_y1)
	ld b, a
	call _attr_1b
	xor a
	or l
	jp nz, push_boxes_end
	ld a, (_x1)
	cp 15
	jp nc, push_boxes_end
	ld a, (_y1)
	cp 10
	jp nc, push_boxes_end
	ld a, (_x0)
	ld (__x), a
	ld a, (_y0)
	ld (__y), a
	xor a
	ld (__t), a
	ld (__n), a
	call _update_tile
	ld a, (_x1)
	ld (__x), a
	ld a, (_y1)
	ld (__y), a
	ld a, 14
	ld (__t), a
	ld a, 10
	ld (__n), a
	call _update_tile
	ld	hl,3	;const
	call	_wyz_play_sound
	.push_boxes_end
	.open_lock
	ld a, (_x0)
	ld c, a
	ld a, (_y0)
	call qtile_do
	ld a, l
	cp 15
	jp nz, open_lock_end
	ld a, (_p_keys)
	or a
	jr z, open_lock_end
	ld b, 1
	ld hl, _cerrojos
	.clear_cerrojo_loop
	ld c, (hl)
	inc hl
	ld d, (hl)
	inc hl
	ld e, (hl)
	inc hl
	ld a, (_n_pant)
	cp c
	jr nz, clear_cerrojo_loop_continue
	ld a, (_x0)
	cp d
	jr nz, clear_cerrojo_loop_continue
	ld a, (_y0)
	cp e
	jr nz, clear_cerrojo_loop_continue
	xor a
	ld (hl), a
	jr clear_cerrojo_end
	.clear_cerrojo_loop_continue
	inc hl
	djnz clear_cerrojo_loop
	.clear_cerrojo_end
	ld a, (_x0)
	ld (__x), a
	ld a, (_y0)
	ld (__y), a
	xor a
	ld (__t), a
	ld (__n), a
	call _update_tile
	ld hl, _p_keys
	dec (hl)
	ld	hl,3	;const
	call	_wyz_play_sound
	.open_lock_end
	ret



._draw_scr_background
	ld	hl,_mapa
	push	hl
	ld	hl,(_n_pant)
	ld	h,0
	ld	de,75
	call	l_mult
	pop	de
	add	hl,de
	ld	(_map_pointer),hl
	ld	hl,(_n_pant)
	ld	h,0
	ld	(_seed),hl
	ld	a,#(1 % 256 % 256)
	ld	(__x),a
	ld	a,#(3 % 256 % 256)
	ld	(__y),a
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_gpit),a
	jp	i_40
.i_38
	ld	hl,(_gpit)
	ld	h,0
	inc	hl
	ld	a,l
	ld	(_gpit),a
.i_40
	ld	a,(_gpit)
	ld	e,a
	ld	d,0
	ld	hl,150	;const
	call	l_ult
	jp	nc,i_39
	ld a, (_gpit)
	and 1
	jr nz, _draw_scr_packed_existing
	._draw_scr_packed_new
	ld hl, (_map_pointer)
	ld a, (hl)
	ld (_gpc), a
	inc hl
	ld (_map_pointer), hl
	srl a
	srl a
	srl a
	srl a
	jr _draw_scr_packed_done
	._draw_scr_packed_existing
	ld a, (_gpc)
	and 15
	._draw_scr_packed_done
	ld (__t), a
	ld b, 0
	ld c, a
	ld hl, _behs
	add hl, bc
	ld a, (hl)
	ld bc, (_gpit)
	ld b, 0
	ld hl, _map_attr
	add hl, bc
	ld (hl), a
	ld a, (__t)
	or a
	jr nz, _draw_scr_packed_noalt
	._draw_scr_packed_alt
	call _rand
	ld a, l
	and 15
	cp 1
	jr z, _draw_scr_packed_alt_subst
	ld a, (__t)
	jr _draw_scr_packed_noalt
	._draw_scr_packed_alt_subst
	ld a, 19
	ld (__t), a
	._draw_scr_packed_noalt
	ld hl, _map_buff
	add hl, bc
	ld (hl), a
	call	_draw_coloured_tile
	ld a, (__x)
	add 2
	cp 30 + 1
	jr c, _advance_worm_no_inc_y
	ld a, (__y)
	add 2
	ld (__y), a
	ld a, 1
	._advance_worm_no_inc_y
	ld (__x), a
	jp	i_38
.i_39
	ret



._draw_scr
	call	cpc_ResetTouchedTiles
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_is_rendering),a
	call	_draw_scr_background
	call	_enems_load
	ld a, 240
	ld (_hotspot_y), a
	ld a, (_n_pant)
	ld b, a
	sla a
	add b
	ld c, a
	ld b, 0
	ld hl, _hotspots
	add hl, bc
	ld a, (hl)
	ld b, a
	srl a
	srl a
	srl a
	srl a
	ld (__x), a
	ld a, b
	and 15
	ld (__y), a
	inc hl
	ld b, (hl)
	inc hl
	ld c, (hl)
	xor a
	or b
	jr z, _hotspots_setup_done
	xor a
	or c
	jr z, _hotspots_setup_done
	._hotspots_setup_do
	ld a, (__x)
	ld e, a
	sla a
	sla a
	sla a
	sla a
	ld (_hotspot_x), a
	ld a, (__y)
	ld d, a
	sla a
	sla a
	sla a
	sla a
	ld (_hotspot_y), a
	sub d
	add e
	ld e, a
	ld d, 0
	ld hl, _map_buff
	add hl, de
	ld a, (hl)
	ld (_orig_tile), a
	ld a, b
	cp 3
	jp nz, _hotspots_setup_set
	._hotspots_setup_set_refill
	xor a
	._hotspots_setup_set
	add 16
	ld (__t), a
	call _draw_coloured_tile_gamearea
	._hotspots_setup_done
	ld hl, _cerrojos
	ld b, 1
	._open_locks_loop
	push bc
	ld a, (_n_pant)
	ld c, a
	ld b, (hl)
	inc hl
	ld d, (hl)
	inc hl
	ld e, (hl)
	inc hl
	ld a, (hl)
	inc hl
	or a
	jr nz, _open_locks_done
	ld a, b
	cp c
	jr nz, _open_locks_done
	._open_locks_do
	ld a, d
	ld (__x), a
	ld a, e
	ld (__y), a
	sla a
	sla a
	sla a
	sla a
	sub e
	add d
	ld b, 0
	ld c, a
	xor a
	push hl
	ld hl, _map_attr
	add hl, bc
	ld (hl), a
	ld hl, _map_buff
	add hl, bc
	ld (hl), a
	ld (__t), a
	call _draw_coloured_tile_gamearea
	pop hl
	._open_locks_done
	pop bc
	dec b
	jr nz, _open_locks_loop
	call	_invalidate_viewport
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_is_rendering),a
	ret



._mons_col_sc_x
	._mons_col_sc_x_lineal
	ld de, 0x000f
	ld hl, 0x000f
	._mons_col_sc_x_compare
	ld a, (__en_mx)
	and 0x80
	ld a, (__en_x)
	jr z, _mons_col_sc_x_horz_positive
	._mons_col_sc_x_horz_negative_ze
	add d
	jr _mons_col_sc_x_horz_set
	._mons_col_sc_x_horz_positive
	add e
	._mons_col_sc_x_horz_set
	srl a
	srl a
	srl a
	srl a
	ld (_cx1), a
	ld (_cx2), a
	ld a, (__en_y)
	add h
	srl a
	srl a
	srl a
	srl a
	ld (_cy1), a
	ld a, (__en_y)
	add l
	srl a
	srl a
	srl a
	srl a
	ld (_cy2), a
	call	_cm_two_points
	ld	a,(_at1)
	and	a
	jp	nz,i_41
	ld	a,(_at2)
	and	a
	jp	nz,i_41
	ld	hl,0	;const
	jr	i_42
.i_41
	ld	hl,1	;const
.i_42
	ld	h,0
	ret



._mons_col_sc_y
	._mons_col_sc_y_lineal
	ld de, 0x000f
	ld hl, 0x000f
	._mons_col_sc_y_compare
	ld a, (__en_my)
	and 0x80
	ld a, (__en_y)
	jr z, _mons_col_sc_y_vert_positive
	._mons_col_sc_y_vert_negative_ze
	add h
	jr _mons_col_sc_y_vert_set
	._mons_col_sc_y_vert_positive
	add l
	._mons_col_sc_y_vert_set
	srl a
	srl a
	srl a
	srl a
	ld (_cy1), a
	ld (_cy2), a
	ld a, (__en_x)
	add d
	srl a
	srl a
	srl a
	srl a
	ld (_cx1), a
	ld a, (__en_x)
	add e
	srl a
	srl a
	srl a
	srl a
	ld (_cx2), a
	call	_cm_two_points
	ld	a,(_at1)
	and	a
	jp	nz,i_43
	ld	a,(_at2)
	and	a
	jp	nz,i_43
	ld	hl,0	;const
	jr	i_44
.i_43
	ld	hl,1	;const
.i_44
	ld	h,0
	ret



._player_init
	ld	a,#(16 % 256 % 256)
	ld	(_gpx),a
	ld	e,a
	ld	d,0
	ld	l,#(6 % 256)
	call	l_asl
	ld	(_p_x),hl
	ld	a,#(64 % 256 % 256)
	ld	(_gpy),a
	ld	e,a
	ld	d,0
	ld	l,#(6 % 256)
	call	l_asl
	ld	(_p_y),hl
	ld	hl,0	;const
	ld	(_p_vy),hl
	ld	(_p_vx),hl
	ld	a,#(1 % 256 % 256)
	ld	(_p_cont_salto),a
	ld	a,#(0 % 256 % 256)
	ld	(_p_saltando),a
	ld	a,#(0 % 256 % 256)
	ld	(_p_frame),a
	ld	a,#(0 % 256 % 256)
	ld	(_p_subframe),a
	ld	a,#(1 % 256 % 256)
	ld	(_p_facing),a
	ld	a,#(0 % 256 % 256)
	ld	(_p_estado),a
	ld	a,#(0 % 256 % 256)
	ld	(_p_ct_estado),a
	ld	a,#(20 % 256 % 256)
	ld	(_p_life),a
	ld	a,#(0 % 256 % 256)
	ld	(_p_objs),a
	ld	a,#(0 % 256 % 256)
	ld	(_p_keys),a
	ld	a,#(0 % 256 % 256)
	ld	(_p_killed),a
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_p_disparando),a
	ret



._player_calc_bounding_box
	ld a, (_gpx)
	add 4
	srl a
	srl a
	srl a
	srl a
	ld (_ptx1), a
	ld a, (_gpx)
	add 11
	srl a
	srl a
	srl a
	srl a
	ld (_ptx2), a
	ld a, (_gpy)
	add 8
	srl a
	srl a
	srl a
	srl a
	ld (_pty1), a
	ld a, (_gpy)
	add 15
	srl a
	srl a
	srl a
	srl a
	ld (_pty2), a
	ret



._player_move
	; Signed comparisons are hard
	; p_vy <= 512 - 32
	; We are going to take a shortcut.
	; If p_vy < 0, just add 32.
	; If p_vy > 0, we can use unsigned comparition anyway.
	ld hl, (_p_vy)
	bit 7, h
	jr nz, _player_gravity_add ; < 0
	ld de, 512 - 32
	or a
	push hl
	sbc hl, de
	pop hl
	jr nc, _player_gravity_maximum
	._player_gravity_add
	ld de, 32
	add hl, de
	jr _player_gravity_vy_set
	._player_gravity_maximum
	ld hl, 512
	._player_gravity_vy_set
	ld (_p_vy), hl
	._player_gravity_done
	ld a, (_p_gotten)
	or a
	jr z, _player_gravity_p_gotten_done
	xor a
	ld (_p_vy), a
	._player_gravity_p_gotten_done
	ld	de,(_p_y)
	ld	hl,(_p_vy)
	add	hl,de
	ld	(_p_y),hl
	ld	a,(_p_gotten)
	and	a
	jp	z,i_45
	ld	de,(_p_y)
	ld	hl,(_ptgmy)
	add	hl,de
	ld	(_p_y),hl
.i_45
	ld	hl,(_p_y)
	xor	a
	or	h
	jp	p,i_46
	ld	hl,0	;const
	ld	(_p_y),hl
.i_46
	ld	hl,(_p_y)
	ld	de,9216	;const
	ex	de,hl
	call	l_gt
	jp	nc,i_47
	ld	hl,9216	;const
	ld	(_p_y),hl
.i_47
	ld hl, (_p_y)
	call HLshr6_A
	ld (_gpy), a
	call	_player_calc_bounding_box
	ld	a,#(0 % 256 % 256)
	ld	(_hit_v),a
	ld	a,(_ptx1)
	ld	(_cx1),a
	ld	hl,(_ptx2)
	ld	h,0
	ld	a,l
	ld	(_cx2),a
	ld	de,(_p_vy)
	ld	hl,(_ptgmy)
	add	hl,de
	xor	a
	or	h
	jp	p,i_48
	ld	hl,(_pty1)
	ld	h,0
	ld	a,l
	ld	(_cy2),a
	ld	(_cy1),a
	call	_cm_two_points
	ld	hl,_at1
	ld	a,(hl)
	and	#(8 % 256)
	jp	nz,i_50
	ld	hl,_at2
	ld	a,(hl)
	and	#(8 % 256)
	jp	z,i_49
.i_50
	ld	hl,0	;const
	ld	(_p_vy),hl
	ld a, (_pty1)
	inc a
	sla a
	sla a
	sla a
	sla a
	sub 8
	ld (_gpy), a
	ld a, (_gpy)
	call Ashl16_HL
	ld (_p_y), hl
.i_49
.i_48
	ld	de,(_p_vy)
	ld	hl,(_ptgmy)
	add	hl,de
	xor	a
	or	h
	jp	m,i_52
	or	l
	jp	z,i_52
	ld	hl,(_pty2)
	ld	h,0
	ld	a,l
	ld	(_cy2),a
	ld	(_cy1),a
	call	_cm_two_points
	ld	hl,_at1
	ld	a,(hl)
	and	#(8 % 256)
	jp	nz,i_54
	ld	hl,_at2
	ld	a,(hl)
	and	#(8 % 256)
	jp	nz,i_54
	ld	hl,(_gpy)
	ld	h,0
	dec	hl
	ld	de,15	;const
	call	l_and
	ld	de,8	;const
	ex	de,hl
	call	l_ult
	jp	nc,i_55
	ld	hl,_at1
	ld	a,(hl)
	and	#(4 % 256)
	jp	nz,i_56
	ld	hl,_at2
	ld	a,(hl)
	and	#(4 % 256)
	jp	z,i_55
.i_56
	ld	hl,1	;const
	jr	i_58
.i_55
	ld	hl,0	;const
.i_58
	ld	a,h
	or	l
	jp	nz,i_54
	jr	i_59
.i_54
	ld	hl,1	;const
.i_59
	ld	a,h
	or	l
	jp	z,i_53
	ld	hl,0	;const
	ld	(_p_vy),hl
	ld a, (_pty2)
	dec a
	sla a
	sla a
	sla a
	sla a
	ld (_gpy), a
	ld a, (_gpy)
	call Ashl16_HL
	ld (_p_y), hl
.i_53
.i_52
	ld a, (_p_vy)
	ld c, a
	ld a, (_p_vy + 1)
	or c
	jr z, evil_tile_check_vert_done
	ld a, (_at1)
	and 1
	ld c, a
	ld a, (_at2)
	and 1
	or c
	ld (_hit_v), a
	.evil_tile_check_vert_done
	ld a, (_gpx)
	srl a
	srl a
	srl a
	srl a
	ld (_gpxx), a
	ld a, (_gpy)
	srl a
	srl a
	srl a
	srl a
	ld (_gpyy), a
	ld	hl,(_gpy)
	ld	h,0
	ld	bc,16
	add	hl,bc
	ex	de,hl
	ld	l,#(4 % 256)
	call	l_asr_u
	ld	h,0
	ld	a,l
	ld	(_cy2),a
	ld	(_cy1),a
	ld	a,(_ptx1)
	ld	(_cx1),a
	ld	hl,(_ptx2)
	ld	h,0
	ld	a,l
	ld	(_cx2),a
	call	_cm_two_points
	ld	hl,_at1
	ld	a,(hl)
	and	#(12 % 256)
	jp	nz,i_60
	ld	hl,_at2
	ld	a,(hl)
	and	#(12 % 256)
	jp	z,i_62
.i_60
	ld	a,(_gpy)
	ld	e,a
	ld	d,0
	ld	hl,15	;const
	call	l_and
	ld	de,8	;const
	ex	de,hl
	call	l_ult
	jp	nc,i_62
	ld	hl,1	;const
	jr	i_63
.i_62
	ld	hl,0	;const
.i_63
	ld	a,l
	ld	(_possee),a
	ld	hl,4	;const
	call	cpc_TestKey
	ld	h,0
	ld	a,l
	ld	(_rda),a
	and	a
	jp	z,i_64
	ld	a,(_p_saltando)
	and	a
	jp	nz,i_65
	ld	a,(_possee)
	and	a
	jp	nz,i_67
	ld	a,(_p_gotten)
	and	a
	jp	nz,i_67
	ld	a,(_hit_v)
	and	a
	jp	z,i_66
.i_67
	ld	a,#(1 % 256 % 256)
	ld	(_p_saltando),a
	ld	a,#(0 % 256 % 256)
	ld	(_p_cont_salto),a
	ld	hl,12	;const
	call	_wyz_play_sound
.i_66
	jp	i_69
.i_65
	ld	hl,(_p_vy)
	push	hl
	ld	a,(_p_cont_salto)
	ld	e,a
	ld	d,0
	ld	l,#(1 % 256)
	call	l_asr_u
	ld	de,128
	ex	de,hl
	and	a
	sbc	hl,de
	pop	de
	ex	de,hl
	and	a
	sbc	hl,de
	ld	(_p_vy),hl
	ld	de,65216	;const
	ex	de,hl
	call	l_lt
	jp	nc,i_70
	ld	hl,65216	;const
	ld	(_p_vy),hl
.i_70
	ld	hl,(_p_cont_salto)
	ld	h,0
	inc	hl
	ld	a,l
	ld	(_p_cont_salto),a
	cp	#(9 % 256)
	jp	nz,i_71
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_p_saltando),a
.i_71
.i_69
	jp	i_72
.i_64
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_p_saltando),a
.i_72
	ld	hl,0	;const
	call	cpc_TestKey
	ld	a,h	
	or	l
	jp	nz,i_74
	inc	hl
	call	cpc_TestKey
	ld	a,h
	or	l
	jp	nz,i_74
	jr	i_75
.i_74
	ld	hl,1	;const
.i_75
	call	l_lneg
	jp	nc,i_73
	ld	hl,(_p_vx)
	xor	a
	or	h
	jp	m,i_76
	or	l
	jp	z,i_76
	ld	hl,(_p_vx)
	ld	bc,-32
	add	hl,bc
	ld	(_p_vx),hl
	xor	a
	or	h
	jp	p,i_77
	ld	hl,0	;const
	ld	(_p_vx),hl
.i_77
	jp	i_78
.i_76
	ld	hl,(_p_vx)
	xor	a
	or	h
	jp	p,i_79
	ld	hl,(_p_vx)
	ld	bc,32
	add	hl,bc
	ld	(_p_vx),hl
	xor	a
	or	h
	jp	m,i_80
	or	l
	jp	z,i_80
	ld	hl,0	;const
	ld	(_p_vx),hl
.i_80
.i_79
.i_78
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_wall_h),a
.i_73
	ld	hl,0	;const
	call	cpc_TestKey
	ld	a,h
	or	l
	jp	z,i_81
	ld	hl,(_p_vx)
	ld	de,65344	;const
	ex	de,hl
	call	l_gt
	jp	nc,i_82
	ld	a,#(0 % 256 % 256)
	ld	(_p_facing),a
	ld	hl,(_p_vx)
	ld	bc,-24
	add	hl,bc
	ld	(_p_vx),hl
.i_82
.i_81
	ld	hl,1	;const
	call	cpc_TestKey
	ld	a,h
	or	l
	jp	z,i_83
	ld	hl,(_p_vx)
	ld	de,192	;const
	ex	de,hl
	call	l_lt
	jp	nc,i_84
	ld	hl,(_p_vx)
	ld	bc,24
	add	hl,bc
	ld	(_p_vx),hl
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_p_facing),a
.i_84
.i_83
	ld	de,(_p_x)
	ld	hl,(_p_vx)
	add	hl,de
	ld	(_p_x),hl
	ex	de,hl
	ld	hl,(_ptgmx)
	add	hl,de
	ld	(_p_x),hl
	xor	a
	or	h
	jp	p,i_85
	ld	hl,0	;const
	ld	(_p_x),hl
.i_85
	ld	hl,(_p_x)
	ld	de,14336	;const
	ex	de,hl
	call	l_gt
	jp	nc,i_86
	ld	hl,14336	;const
	ld	(_p_x),hl
.i_86
	ld a, (_gpx)
	ld (_gpox), a
	ld hl, (_p_x)
	call HLshr6_A
	ld (_gpx), a
	call	_player_calc_bounding_box
	ld	a,#(0 % 256 % 256)
	ld	(_hit_h),a
	ld	a,(_pty1)
	ld	(_cy1),a
	ld	hl,(_pty2)
	ld	h,0
	ld	a,l
	ld	(_cy2),a
	ld	de,(_p_vx)
	ld	hl,(_ptgmx)
	add	hl,de
	xor	a
	or	h
	jp	p,i_87
	ld	hl,(_ptx1)
	ld	h,0
	ld	a,l
	ld	(_cx2),a
	ld	(_cx1),a
	call	_cm_two_points
	ld	hl,_at1
	ld	a,(hl)
	and	#(8 % 256)
	jp	nz,i_89
	ld	hl,_at2
	ld	a,(hl)
	and	#(8 % 256)
	jp	z,i_88
.i_89
	ld	hl,0	;const
	ld	(_p_vx),hl
	ld a, (_ptx1)
	inc a
	sla a
	sla a
	sla a
	sla a
	sub 4
	ld (_gpx), a
	ld a, (_gpx)
	call Ashl16_HL
	ld (_p_x), hl
	ld a, 3
	ld (_wall_h), a
	jp	i_91
.i_88
	ld a, (_at1)
	and 1
	ld c, a
	ld a, (_at2)
	and 1
	or c
	ld (_hit_h), a
.i_91
.i_87
	ld	de,(_p_vx)
	ld	hl,(_ptgmx)
	add	hl,de
	xor	a
	or	h
	jp	m,i_92
	or	l
	jp	z,i_92
	ld	hl,(_ptx2)
	ld	h,0
	ld	a,l
	ld	(_cx2),a
	ld	(_cx1),a
	call	_cm_two_points
	ld	hl,_at1
	ld	a,(hl)
	and	#(8 % 256)
	jp	nz,i_94
	ld	hl,_at2
	ld	a,(hl)
	and	#(8 % 256)
	jp	z,i_93
.i_94
	ld	hl,0	;const
	ld	(_p_vx),hl
	ld a, (_ptx1)
	sla a
	sla a
	sla a
	sla a
	add 4
	ld (_gpx), a
	ld a, (_gpx)
	call Ashl16_HL
	ld (_p_x), hl
	ld a, 4
	ld (_wall_h), a
	jp	i_96
.i_93
	ld a, (_at1)
	and 1
	ld c, a
	ld a, (_at2)
	and 1
	or c
	ld (_hit_h), a
.i_96
.i_92
	ld a, (_gpx)
	add 8
	srl a
	srl a
	srl a
	srl a
	ld (_p_tx), a
	ld (_cx1), a
	ld c, a
	ld a, (_gpy)
	add 8
	srl a
	srl a
	srl a
	srl a
	ld (_p_ty), a
	ld (_cy1), a
	call _attr_2
	ld a, l
	ld (_rdb), a
	ld	hl,_rdb
	ld	a,(hl)
	rlca
	jp	nc,i_97
.i_97
	ld	a,(_wall_h)
	ld	e,a
	ld	d,0
	ld	hl,3	;const
	call	l_eq
	jp	nc,i_98
	ld a, (_gpx)
	add 3
	srl a
	srl a
	srl a
	srl a
	ld (_cx1), a
	ld c, a
	ld a, (_cy1)
	call _attr_2
	ld a, l
	cp 10
	jr nz, p_int_left_no
	ld a, (_cy1)
	ld (_y0), a
	ld (_y1), a
	ld a, (_cx1)
	ld (_x0), a
	dec a
	ld (_x1), a
	call _process_tile
	.p_int_left_no
	jp	i_99
.i_98
	ld	a,(_wall_h)
	ld	e,a
	ld	d,0
	ld	hl,4	;const
	call	l_eq
	jp	nc,i_100
	ld a, (_gpx)
	add 12
	srl a
	srl a
	srl a
	srl a
	ld (_cx1), a
	ld c, a
	ld a, (_cy1)
	call _attr_2
	ld a, l
	cp 10
	jr nz, p_int_right_no
	ld a, (_cy1)
	ld (_y0), a
	ld (_y1), a
	ld a, (_cx1)
	ld (_x0), a
	inc a
	ld (_x1), a
	call _process_tile
	.p_int_right_no
.i_100
.i_99
	ld	a,#(0 % 256 % 256)
	ld	(_hit),a
	ld	a,(_hit_v)
	and	a
	jp	z,i_101
	ld	a,#(1 % 256 % 256)
	ld	(_hit),a
	ld	hl,(_p_vy)
	call	l_neg
	push	hl
	ld	hl,192	;const
	push	hl
	call	_addsign
	pop	bc
	pop	bc
	ld	(_p_vy),hl
	jp	i_102
.i_101
	ld	a,(_hit_h)
	and	a
	jp	z,i_103
	ld	a,#(1 % 256 % 256)
	ld	(_hit),a
	ld	hl,(_p_vx)
	call	l_neg
	push	hl
	ld	hl,192	;const
	push	hl
	call	_addsign
	pop	bc
	pop	bc
	ld	(_p_vx),hl
.i_103
.i_102
	ld	a,(_hit)
	and	a
	jp	z,i_104
	ld	a,(_p_estado)
	and	a
	jp	nz,i_105
	ld	hl,13 % 256	;const
	ld	a,l
	ld	(_p_killme),a
.i_105
.i_104
	ld	hl,(_possee)
	ld	h,0
	call	l_lneg
	jp	nc,i_107
	ld	hl,(_p_gotten)
	ld	h,0
	call	l_lneg
	jr	c,i_108_i_107
.i_107
	jp	i_106
.i_108_i_107
	ld	a,(_p_facing)
	and	a
	jp	z,i_109
	ld	hl,3	;const
	jp	i_110
.i_109
	ld	hl,7	;const
.i_110
	ld	h,0
	ld	a,l
	ld	(_gpit),a
	jp	i_111
.i_106
	ld	a,(_p_facing)
	and	a
	jp	z,i_112
	ld	hl,0	;const
	jp	i_113
.i_112
	ld	hl,4	;const
.i_113
	ld	a,l
	ld	(_gpit),a
	ld	hl,(_p_vx)
	ld	a,h
	or	l
	jp	nz,i_114
	ld	hl,(_gpit)
	ld	h,0
	inc	hl
	ld	a,l
	ld	(_gpit),a
	jp	i_115
.i_114
	ld	hl,(_gpx)
	ld	h,0
	ld	bc,4
	add	hl,bc
	ex	de,hl
	ld	l,#(3 % 256)
	call	l_asr_u
	ld	de,3	;const
	call	l_and
	ld	h,0
	ld	a,l
	ld	(_rda),a
	cp	#(3 % 256)
	jp	nz,i_116
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_rda),a
.i_116
	ld	de,(_gpit)
	ld	d,0
	ld	hl,(_rda)
	ld	h,d
	add	hl,de
	ld	h,0
	ld	a,l
	ld	(_gpit),a
.i_115
.i_111
	ld	hl,_sp_sw
	push	hl
	ld	hl,_sm_sprptr
	push	hl
	ld	hl,(_gpit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	call	l_gint	;
	call	l_pint_pop
	ld	hl,_sp_sw+8
	push	hl
	ld	hl,(_gpx)
	ld	h,0
	ld	bc,8
	add	hl,bc
	push	hl
	ld	hl,_sp_sw+6
	call	l_gchar
	pop	de
	add	hl,de
	ex	de,hl
	ld	l,#(2 % 256)
	call	l_asr_u
	pop	de
	ld	a,l
	ld	(de),a
	ld	hl,_sp_sw+9
	push	hl
	ld	hl,(_gpy)
	ld	h,0
	ld	bc,24
	add	hl,bc
	push	hl
	ld	hl,_sp_sw+7
	call	l_gchar
	pop	de
	add	hl,de
	pop	de
	ld	a,l
	ld	(de),a
	ld	hl,_p_estado
	ld	a,(hl)
	and	#(2 % 256)
	jp	z,i_118
	ld	a,(_half_life)
	and	a
	jr	nz,i_119_i_118
.i_118
	jp	i_117
.i_119_i_118
	ld	hl,_sp_sw
	push	hl
	ld	hl,_sprite_18_a
	call	l_pint_pop
.i_117
	ret



._player_deplete
	ld	de,(_p_life)
	ld	d,0
	ld	hl,(_p_kill_amt)
	ld	h,d
	call	l_ugt
	jp	nc,i_120
	ld	de,(_p_life)
	ld	d,0
	ld	hl,(_p_kill_amt)
	ld	h,d
	ex	de,hl
	and	a
	sbc	hl,de
	jp	i_121
.i_120
	ld	hl,0	;const
.i_121
	ld	h,0
	ld	a,l
	ld	(_p_life),a
	ret



._player_kill
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_p_killme),a
	call	_player_deplete
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	_wyz_play_sound
	ld	a,#(2 % 256 % 256)
	ld	(_p_estado),a
	ld	hl,50 % 256	;const
	ld	a,l
	ld	(_p_ct_estado),a
	ret



._enems_init
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_enit),a
.i_122
	ld	a,(_enit)
	cp	#(72 % 256)
	jp	z,i_123
	jp	nc,i_123
	ld	hl,_malotes
	push	hl
	ld	hl,(_enit)
	ld	h,0
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	pop	de
	add	hl,de
	ld	bc,8
	add	hl,bc
	push	hl
	ld	hl,_malotes
	push	hl
	ld	hl,(_enit)
	ld	h,0
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	pop	de
	add	hl,de
	ld	bc,8
	add	hl,bc
	call	l_gchar
	ld	de,239	;const
	call	l_and
	pop	de
	ld	a,l
	ld	(de),a
	ld	hl,_enit
	ld	a,(hl)
	inc	(hl)
	ld	l,a
	ld	h,0
	jp	i_122
.i_123
	ret



._enems_load
	ld	hl,(_n_pant)
	ld	h,0
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	ld	a,l
	ld	(_enoffs),a
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_enit),a
	jp	i_126
.i_124
	ld	hl,(_enit)
	ld	h,0
	inc	hl
	ld	a,l
	ld	(_enit),a
.i_126
	ld	a,(_enit)
	ld	e,a
	ld	d,0
	ld	hl,3	;const
	call	l_ult
	jp	nc,i_125
	ld bc, (_enit)
	ld b, 0
	ld hl, _en_an_frame
	add hl, bc
	xor a
	ld (hl), a
	ld hl, _en_an_state
	add hl, bc
	ld (hl), a
	ld hl, _en_an_count
	add hl, bc
	ld a, 3
	ld (hl), a
	ld a, (_enit)
	ld c, a
	ld a, (_enoffs)
	add c
	ld (_enoffsmasi), a
	ld	hl,_en_an_next_frame
	push	hl
	ld	hl,(_enit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	push	hl
	ld	hl,_sprite_18_a
	call	l_pint_pop
	ld	hl,_malotes
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	pop	de
	add	hl,de
	ld	bc,8
	add	hl,bc
	call	l_gchar
	ld	de,31	;const
	call	l_and
	ld	h,0
	ld	a,l
	ld	(_rdt),a
	and	a
	jp	z,i_127
	ld	hl,(_rdt)
	ld	h,0
.i_130
	ld	a,l
	cp	#(1% 256)
	jp	z,i_131
	cp	#(2% 256)
	jp	z,i_132
	cp	#(3% 256)
	jp	z,i_133
	cp	#(4% 256)
	jp	z,i_134
	jp	i_135
.i_131
.i_132
.i_133
.i_134
	ld	de,_en_an_base_frame
	ld	hl,(_enit)
	ld	h,0
	add	hl,de
	push	hl
	ld	hl,_malotes
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	pop	de
	add	hl,de
	ld	bc,8
	add	hl,bc
	call	l_gchar
	dec	hl
	add	hl,hl
	ld	de,8
	add	hl,de
	pop	de
	ld	a,l
	ld	(de),a
	jp	i_129
.i_135
	ld	de,_en_an_base_frame
	ld	hl,(_enit)
	ld	h,0
	add	hl,de
	ld	(hl),#(255 % 256 % 256)
	ld	l,(hl)
	ld	h,0
.i_129
	jp	i_136
.i_127
	ld	de,_en_an_base_frame
	ld	hl,(_enit)
	ld	h,0
	add	hl,de
	ld	(hl),#(255 % 256 % 256)
.i_136
	ld	hl,(_enit)
	ld	h,0
	ld	de,1
	add	hl,de
	ld	h,0
	ld	a,l
	ld	(_rda),a
	ld	de,_en_an_base_frame
	ld	hl,(_enit)
	ld	h,0
	add	hl,de
	ld	e,(hl)
	ld	d,0
	ld	hl,255	;const
	call	l_ne
	ld	hl,0	;const
	rl	l
	ld	a,l
	ld	(_rdb),a
	ld	a,h
	or	l
	jp	z,i_137
	ld	hl,_sp_sw
	push	hl
	ld	hl,(_rda)
	ld	h,0
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,6
	add	hl,bc
	push	hl
	ld	de,_sm_cox
	ld	hl,(_rdb)
	ld	h,0
	add	hl,de
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,_sp_sw
	push	hl
	ld	hl,(_rda)
	ld	h,0
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,7
	add	hl,bc
	push	hl
	ld	de,_sm_coy
	ld	hl,(_rdb)
	ld	h,0
	add	hl,de
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,_sp_sw
	push	hl
	ld	hl,(_rda)
	ld	h,0
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,12
	add	hl,bc
	push	hl
	ld	hl,_sm_invfunc
	push	hl
	ld	hl,(_rdb)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	call	l_gint	;
	call	l_pint_pop
	ld	hl,_sp_sw
	push	hl
	ld	hl,(_rda)
	ld	h,0
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,14
	add	hl,bc
	push	hl
	ld	hl,_sm_updfunc
	push	hl
	ld	hl,(_rdb)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	call	l_gint	;
	call	l_pint_pop
	ld	hl,_en_an_next_frame
	push	hl
	ld	hl,(_enit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	push	hl
	ld	hl,_sm_sprptr
	push	hl
	ld	hl,(_rdb)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	call	l_gint	;
	call	l_pint_pop
	jp	i_138
.i_137
	ld	hl,_en_an_next_frame
	push	hl
	ld	hl,(_enit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	push	hl
	ld	hl,_sprite_18_a
	call	l_pint_pop
.i_138
	jp	i_124
.i_125
	ret



._enems_kill
	ld a, (__en_t)
	cp 7
	jr z, enems_kill_noflag
	or 16
	ld (__en_t), a
	.enems_kill_noflag
	ld hl, (_p_killed)
	inc (hl)
	ret



._enems_move
	ld	hl,0	;const
	ld	(_ptgmy),hl
	ld	(_ptgmx),hl
	ld	h,0
	ld	a,l
	ld	(_p_gotten),a
	ld	(_tocado),a
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_enit),a
	jp	i_141
.i_139
	ld	hl,_enit
	ld	a,(hl)
	inc	(hl)
.i_141
	ld	a,(_enit)
	ld	e,a
	ld	d,0
	ld	hl,3	;const
	call	l_ult
	jp	nc,i_140
	xor a
	ld (_active), a
	ld a, (_enit)
	ld c, a
	ld a, (_enoffs)
	add c
	ld (_enoffsmasi), a
	ld hl, (_enoffsmasi)
	ld h, 0
	ld d, h
	ld e, l
	add hl, hl
	add hl, hl
	add hl, hl
	add hl, de
	ld de, _malotes
	add hl, de
	ld (__baddies_pointer), hl
	ld a, (hl)
	ld (__en_x), a
	inc hl
	ld a, (hl)
	ld (__en_y), a
	inc hl
	ld a, (hl)
	ld (__en_x1), a
	inc hl
	ld a, (hl)
	ld (__en_y1), a
	inc hl
	ld a, (hl)
	ld (__en_x2), a
	inc hl
	ld a, (hl)
	ld (__en_y2), a
	inc hl
	ld a, (hl)
	ld (__en_mx), a
	inc hl
	ld a, (hl)
	ld (__en_my), a
	inc hl
	ld a, (hl)
	ld (__en_t), a
	and 0x1f
	ld (_rdt), a
	ld	de,_en_an_state
	ld	hl,(_enit)
	ld	h,0
	add	hl,de
	ld	a,(hl)
	cp	#(4 % 256)
	jp	nz,i_142
	ld	de,_en_an_count
	ld	hl,(_enit)
	ld	h,0
	add	hl,de
	dec	(hl)
	ld	de,_en_an_count
	ld	hl,(_enit)
	ld	h,0
	add	hl,de
	ld	a,(hl)
	and	a
	jp	nz,i_143
	ld	de,_en_an_state
	ld	hl,(_enit)
	ld	h,0
	add	hl,de
	ld	(hl),#(0 % 256 % 256)
	ld	hl,_en_an_next_frame
	push	hl
	ld	hl,(_enit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	push	hl
	ld	hl,_sprite_18_a
	call	l_pint_pop
	jp	i_139
.i_143
.i_142
	ld	hl,(_gpx)
	ld	h,0
	ld	bc,12
	add	hl,bc
	ex	de,hl
	ld	hl,(__en_x)
	ld	h,0
	call	l_uge
	jp	nc,i_144
	ld	hl,(_gpx)
	ld	h,0
	push	hl
	ld	hl,(__en_x)
	ld	h,0
	ld	bc,12
	add	hl,bc
	pop	de
	call	l_ule
	jp	nc,i_144
	ld	hl,1	;const
	jr	i_145
.i_144
	ld	hl,0	;const
.i_145
	ld	a,l
	ld	(_pregotten),a
	ld	hl,(_rdt)
	ld	h,0
.i_148
	ld	a,l
	cp	#(1% 256)
	jp	z,i_149
	cp	#(2% 256)
	jp	z,i_150
	cp	#(3% 256)
	jp	z,i_151
	cp	#(4% 256)
	jp	z,i_152
	jp	i_147
.i_149
.i_150
.i_151
.i_152
	ld a, 1
	ld (_active), a
	ld a, (__en_mx)
	ld c, a
	ld a, (__en_x)
	add a, c
	ld (__en_x), a
	ld c, a
	ld a, (__en_x1)
	cp c
	jr z, _enems_lm_change_axis_x
	ld a, (__en_x2)
	cp c
	jr z, _enems_lm_change_axis_x
	call _mons_col_sc_x_lineal
	xor a
	or l
	jr z, _enems_lm_change_axis_x_done
	._enems_lm_change_axis_x
	ld a, (__en_mx)
	neg
	ld (__en_mx), a
	._enems_lm_change_axis_x_done
	ld a, (__en_my)
	ld c, a
	ld a, (__en_y)
	add a, c
	ld (__en_y), a
	ld c, a
	ld a, (__en_y1)
	cp c
	jr z, _enems_lm_change_axis_y
	ld a, (__en_y2)
	cp c
	jr z, _enems_lm_change_axis_y
	call _mons_col_sc_y_lineal
	xor a
	or l
	jr z, _enems_lm_change_axis_y_done
	._enems_lm_change_axis_y
	ld a, (__en_my)
	neg
	ld (__en_my), a
	._enems_lm_change_axis_y_done
.i_147
	ld	a,(_active)
	and	a
	jp	z,i_153
	ld	de,_en_an_base_frame
	ld	hl,(_enit)
	ld	h,0
	add	hl,de
	ld	e,(hl)
	ld	d,0
	ld	hl,99	;const
	call	l_ne
	jp	nc,i_154
	ld bc, (_enit)
	ld b, 0
	ld hl, _en_an_count
	add hl, bc
	ld a, (hl)
	inc a
	ld (hl), a
	cp 4
	jr nz, _enems_move_update_frame_done
	xor a
	ld (hl), a
	ld hl, _en_an_frame
	add hl, bc
	ld a, (hl)
	xor 1
	ld (hl), a
	ld hl, _en_an_base_frame
	add hl, bc
	ld d, (hl)
	add d ; A = en_an_base_frame [enit] + en_an_frame [enit]]
	sla c ; Index 16 bits; it never overflows.
	ld hl, _en_an_next_frame
	add hl, bc
	ex de, hl ; DE -> en_an_next_frame [enit]
	sla a
	ld c, a
	ld b, 0
	ld hl, _sm_sprptr
	add hl, bc ; HL -> enem_cells [en_an_base_frame [enit] + en_an_frame [enit]]
	ldi
	ldi ; Copy 16 bit
	._enems_move_update_frame_done
.i_154
	ld	hl,__en_t
	call	l_gchar
	ld	de,4	;const
	call	l_eq
	jp	nc,i_155
	ld	a,(_pregotten)
	and	a
	jp	z,i_156
	ld	hl,__en_mx
	call	l_gchar
	ld	a,h
	or	l
	jp	z,i_157
	ld	hl,(_gpy)
	ld	h,0
	ld	bc,17
	add	hl,bc
	ex	de,hl
	ld	hl,(__en_y)
	ld	h,0
	call	l_uge
	jp	nc,i_159
	ld	hl,(_gpy)
	ld	h,0
	ld	bc,8
	add	hl,bc
	ex	de,hl
	ld	hl,(__en_y)
	ld	h,0
	call	l_ule
	jr	c,i_160_i_159
.i_159
	jp	i_158
.i_160_i_159
	ld	a,#(1 % 256 % 256)
	ld	(_p_gotten),a
	ld	hl,__en_mx
	call	l_gchar
	ex	de,hl
	ld	l,#(6 % 256)
	call	l_asl
	ld	(_ptgmx),hl
	ld	hl,(__en_y)
	ld	h,0
	ld	bc,-16
	add	hl,bc
	ld	h,0
	ld	a,l
	ld	(_gpy),a
	ld	e,a
	ld	d,0
	ld	l,#(6 % 256)
	call	l_asl
	ld	(_p_y),hl
.i_158
.i_157
	ld	hl,__en_my
	call	l_gchar
	ld	de,0	;const
	ex	de,hl
	call	l_lt
	jp	nc,i_162
	ld	hl,(_gpy)
	ld	h,0
	ld	bc,18
	add	hl,bc
	ex	de,hl
	ld	hl,(__en_y)
	ld	h,0
	call	l_uge
	jp	nc,i_162
	ld	hl,(_gpy)
	ld	h,0
	ld	bc,8
	add	hl,bc
	ex	de,hl
	ld	hl,(__en_y)
	ld	h,0
	call	l_ule
	jp	c,i_164
.i_162
	jr	i_162_i_163
.i_163
	ld	a,h
	or	l
	jp	nz,i_164
.i_162_i_163
	ld	hl,__en_my
	call	l_gchar
	ld	de,0	;const
	ex	de,hl
	call	l_gt
	jp	nc,i_165
	ld	hl,(_gpy)
	ld	h,0
	ld	bc,17
	add	hl,bc
	push	hl
	ld	hl,__en_my
	call	l_gchar
	pop	de
	add	hl,de
	ex	de,hl
	ld	hl,(__en_y)
	ld	h,0
	call	l_uge
	jp	nc,i_165
	ld	hl,(_gpy)
	ld	h,0
	ld	bc,8
	add	hl,bc
	ex	de,hl
	ld	hl,(__en_y)
	ld	h,0
	call	l_ule
	jp	nc,i_165
	ld	hl,1	;const
	jr	i_166
.i_165
	ld	hl,0	;const
.i_166
	ld	a,h
	or	l
	jp	nz,i_164
	jr	i_167
.i_164
	ld	hl,1	;const
.i_167
	ld	a,h
	or	l
	jp	z,i_161
	ld	a,#(1 % 256 % 256)
	ld	(_p_gotten),a
	ld	hl,__en_my
	call	l_gchar
	ex	de,hl
	ld	l,#(6 % 256)
	call	l_asl
	ld	(_ptgmy),hl
	ld	hl,(__en_y)
	ld	h,0
	ld	bc,-16
	add	hl,bc
	ld	h,0
	ld	a,l
	ld	(_gpy),a
	ld	e,a
	ld	d,0
	ld	l,#(6 % 256)
	call	l_asl
	ld	(_p_y),hl
.i_161
.i_156
	jp	i_168
.i_155
	ld	a,(__en_x)
	ld	(_cx2),a
	ld	a,(__en_y)
	ld	(_cy2),a
	ld	hl,(_tocado)
	ld	h,0
	call	l_lneg
	jp	nc,i_170
	call	_collide
	ld	a,h
	or	l
	jp	z,i_170
	ld	a,(_p_estado)
	cp	#(0 % 256)
	jr	z,i_171_i_170
.i_170
	jp	i_169
.i_171_i_170
	ld	hl,(_gpy)
	ld	h,0
	push	hl
	ld	hl,(__en_y)
	ld	h,0
	dec	hl
	dec	hl
	pop	de
	call	l_ult
	jp	nc,i_173
	ld	hl,(_p_vy)
	ld	de,0	;const
	ex	de,hl
	call	l_ge
	jp	nc,i_173
	ld	a,(_rdt)
	cp	#(0 % 256)
	jr	z,i_173_uge
	jp	c,i_173
.i_173_uge
	jr	i_174_i_173
.i_173
	jp	i_172
.i_174_i_173
	ld	hl,6	;const
	call	_wyz_play_sound
	ld	de,_en_an_state
	ld	hl,(_enit)
	ld	h,0
	add	hl,de
	ld	(hl),#(4 % 256 % 256)
	ld	de,_en_an_count
	ld	hl,(_enit)
	ld	h,0
	add	hl,de
	ld	(hl),#(12 % 256 % 256)
	ld	hl,_en_an_next_frame
	push	hl
	ld	hl,(_enit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	push	hl
	ld	hl,_sprite_17_a
	call	l_pint_pop
	ld	hl,65280	;const
	ld	(_p_vy),hl
	call	_enems_kill
	jp	i_175
.i_172
	ld	a,#(1 % 256 % 256)
	ld	(_tocado),a
	ld	hl,14 % 256	;const
	ld	a,l
	ld	(_p_killme),a
.i_175
.i_169
.i_168
.i_176
.i_153
	ld	hl,(_enit)
	ld	h,0
	ld	de,1
	add	hl,de
	ld	h,0
	ld	a,l
	ld	(_rda),a
	ld	de,_en_an_sprid
	ld	hl,(_enit)
	ld	h,0
	add	hl,de
	ld	a,(hl)
	ld	(_rdt),a
	ld	hl,_sp_sw
	push	hl
	ld	hl,(_rda)
	ld	h,0
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,8
	add	hl,bc
	push	hl
	ld	hl,(__en_x)
	ld	h,0
	ld	bc,8
	add	hl,bc
	push	hl
	ld	hl,_sp_sw
	push	hl
	ld	hl,(_rda)
	ld	h,0
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,6
	add	hl,bc
	call	l_gchar
	pop	de
	add	hl,de
	ex	de,hl
	ld	l,#(2 % 256)
	call	l_asr_u
	pop	de
	ld	a,l
	ld	(de),a
	ld	hl,_sp_sw
	push	hl
	ld	hl,(_rda)
	ld	h,0
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,9
	add	hl,bc
	push	hl
	ld	hl,(__en_y)
	ld	h,0
	ld	bc,24
	add	hl,bc
	push	hl
	ld	hl,_sp_sw
	push	hl
	ld	hl,(_rda)
	ld	h,0
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,7
	add	hl,bc
	call	l_gchar
	pop	de
	add	hl,de
	pop	de
	ld	a,l
	ld	(de),a
	ld	a,(_rdt)
	cp	#(255 % 256)
	jp	z,i_177
	ld	hl,_sp_sw
	push	hl
	ld	hl,(_rda)
	ld	h,0
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	pop	de
	add	hl,de
	push	hl
	ld	hl,_en_an_next_frame
	push	hl
	ld	hl,(_enit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	call	l_gint	;
	call	l_pint_pop
	jp	i_178
.i_177
	ld	hl,_sp_sw
	push	hl
	ld	hl,(_rda)
	ld	h,0
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	pop	de
	add	hl,de
	push	hl
	ld	hl,_sprite_18_a
	call	l_pint_pop
.i_178
	ld hl, (__baddies_pointer)
	ld a, (__en_x)
	ld (hl), a
	inc hl
	ld a, (__en_y)
	ld (hl), a
	inc hl
	ld a, (__en_x1)
	ld (hl), a
	inc hl
	ld a, (__en_y1)
	ld (hl), a
	inc hl
	ld a, (__en_x2)
	ld (hl), a
	inc hl
	ld a, (__en_y2)
	ld (hl), a
	inc hl
	ld a, (__en_mx)
	ld (hl), a
	inc hl
	ld a, (__en_my)
	ld (hl), a
	inc hl
	ld a, (__en_t)
	ld (hl), a
	inc hl
	jp	i_139
.i_140
	ret



._hotspots_init
	ld b, 4 * 6
	ld hl, _hotspots + 2
	ld de, 3
	ld a, 1
	.init_hotspots_loop
	ld (hl), a
	add hl, de
	djnz init_hotspots_loop
	ret



._hotspots_do
	ld	hl,_hotspots
	push	hl
	ld	hl,(_n_pant)
	ld	h,0
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	pop	de
	add	hl,de
	inc	hl
	inc	hl
	ld	l,(hl)
	ld	a,l
	and	a
	jp	nz,i_179
	ret


.i_179
	ld	a,(_hotspot_x)
	ld	(_cx2),a
	ld	hl,(_hotspot_y)
	ld	h,0
	ld	a,l
	ld	(_cy2),a
	call	_collide
	ld	a,h
	or	l
	jp	z,i_180
	ld	a,#(1 % 256 % 256)
	ld	(_hotspot_destroy),a
	ld	hl,_hotspots
	push	hl
	ld	hl,(_n_pant)
	ld	h,0
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	pop	de
	add	hl,de
	inc	hl
	ld	l,(hl)
	ld	h,0
.i_183
	ld	a,l
	cp	#(2% 256)
	jp	z,i_184
	cp	#(3% 256)
	jp	z,i_185
	jp	i_182
.i_184
	ld	hl,_p_keys
	ld	a,(hl)
	inc	(hl)
	ld	hl,10	;const
	call	_wyz_play_sound
	jp	i_182
.i_185
	ld	hl,(_p_life)
	ld	h,0
	inc	hl
	ld	h,0
	ld	a,l
	ld	(_p_life),a
	cp	#(20 % 256)
	jp	z,i_186
	jp	c,i_186
	ld	hl,20 % 256	;const
	ld	a,l
	ld	(_p_life),a
.i_186
	ld	hl,11	;const
	call	_wyz_play_sound
.i_182
	ld	a,(_hotspot_destroy)
	and	a
	jp	z,i_187
	ld	hl,_hotspots
	push	hl
	ld	hl,(_n_pant)
	ld	h,0
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	pop	de
	add	hl,de
	inc	hl
	inc	hl
	ld	(hl),#(0 % 256 % 256)
	ld	a,(_hotspot_x)
	ld	e,a
	ld	d,0
	ld	l,#(4 % 256)
	call	l_asr_u
	ld	h,0
	ld	a,l
	ld	(__x),a
	ld	a,(_hotspot_y)
	ld	e,a
	ld	d,0
	ld	l,#(4 % 256)
	call	l_asr_u
	ld	a,l
	ld	(__y),a
	ld	hl,(_orig_tile)
	ld	h,0
	ld	a,l
	ld	(__t),a
	call	_draw_invalidate_coloured_tile_g
	ld	hl,240 % 256	;const
	ld	a,l
	ld	(_hotspot_y),a
.i_187
.i_180
	ret


	.EFECTO0
	defb 0x25, 0x1C, 0x00
	defb 0x3A, 0x0F, 0x00
	defb 0x2D, 0x0F, 0x00
	defb 0xE2, 0x0F, 0x00
	defb 0xBC, 0x0F, 0x00
	defb 0x96, 0x0D, 0x00
	defb 0x4B, 0x0D, 0x00
	defb 0x32, 0x0D, 0x00
	defb 0x3A, 0x0D, 0x00
	defb 0x2D, 0x0D, 0x00
	defb 0xE2, 0x0D, 0x00
	defb 0xBC, 0x0D, 0x00
	defb 0x96, 0x0D, 0x00
	defb 0x4B, 0x0D, 0x00
	defb 0x32, 0x0D, 0x00
	defb 0x3A, 0x0D, 0x00
	defb 0x2D, 0x0C, 0x00
	defb 0xE2, 0x0C, 0x00
	defb 0xBC, 0x0C, 0x00
	defb 0x96, 0x0B, 0x00
	defb 0x4B, 0x0B, 0x00
	defb 0x32, 0x0B, 0x00
	defb 0x3A, 0x0B, 0x00
	defb 0x2D, 0x0B, 0x00
	defb 0xE2, 0x0B, 0x00
	defb 0xBC, 0x0B, 0x00
	defb 0x96, 0x0B, 0x00
	defb 0x4B, 0x0A, 0x00
	defb 0x32, 0x0A, 0x00
	defb 0x3A, 0x0A, 0x00
	defb 0x2D, 0x09, 0x00
	defb 0xE2, 0x09, 0x00
	defb 0xBC, 0x08, 0x00
	defb 0x96, 0x08, 0x00
	defb 0x4B, 0x08, 0x00
	defb 0x32, 0x07, 0x00
	defb 0x3A, 0x07, 0x00
	defb 0x2D, 0x06, 0x00
	defb 0xE2, 0x06, 0x00
	defb 0xBC, 0x06, 0x00
	defb 0x96, 0x05, 0x00
	defb 0x4B, 0x05, 0x00
	defb 0x32, 0x05, 0x00
	defb 0x3A, 0x04, 0x00
	defb 0x2D, 0x04, 0x00
	defb 0xE2, 0x03, 0x00
	defb 0xBC, 0x03, 0x00
	defb 0x96, 0x03, 0x00
	defb 0x4B, 0x03, 0x00
	defb 0x32, 0x02, 0x00
	defb 0x3A, 0x01, 0x00
	defb 0x2D, 0x01, 0x00
	defb 0xE2, 0x01, 0x00
	defb 0xBC, 0x01, 0x00
	defb 0xFF
	.EFECTO1
	defb 0xC3, 0x0E, 0x00
	defb 0x5F, 0x0F, 0x00
	defb 0xA6, 0x0F, 0x00
	defb 0xE8, 0x1B, 0x00
	defb 0x80, 0x2B, 0x00
	defb 0xFF
	.EFECTO2
	defb 0x1F, 0x0B, 0x00
	defb 0x5A, 0x0F, 0x00
	defb 0x3C, 0x0F, 0x00
	defb 0x1E, 0x0A, 0x00
	defb 0x2D, 0x0A, 0x00
	defb 0x5A, 0x05, 0x00
	defb 0x3C, 0x05, 0x00
	defb 0x1E, 0x04, 0x00
	defb 0x2D, 0x02, 0x00
	defb 0xB4, 0x01, 0x00
	defb 0xFF
	.EFECTO3
	defb 0xE8, 0x1B, 0x00
	defb 0x5F, 0x0F, 0x00
	defb 0xA6, 0x0F, 0x00
	defb 0x00, 0x00, 0x00
	defb 0x80, 0x0F, 0x00
	defb 0xFF
	.EFECTO4
	defb 0x1F, 0x0B, 0x00
	defb 0xAF, 0x0F, 0x00
	defb 0x8A, 0x0F, 0x00
	defb 0x71, 0x0F, 0x00
	defb 0x64, 0x0F, 0x00
	defb 0x3E, 0x0C, 0x00
	defb 0x25, 0x0C, 0x00
	defb 0x25, 0x0C, 0x00
	defb 0x25, 0x0C, 0x00
	defb 0x25, 0x0A, 0x00
	defb 0x4B, 0x0A, 0x00
	defb 0x4B, 0x0A, 0x00
	defb 0x4B, 0x0A, 0x00
	defb 0x3E, 0x08, 0x00
	defb 0x3E, 0x08, 0x00
	defb 0x3E, 0x08, 0x00
	defb 0x71, 0x08, 0x00
	defb 0x3E, 0x07, 0x00
	defb 0x25, 0x05, 0x00
	defb 0x25, 0x02, 0x00
	defb 0xFF
	.EFECTO5
	defb 0x1F, 0x0B, 0x00
	defb 0x5A, 0x0F, 0x00
	defb 0x3C, 0x0F, 0x00
	defb 0x1E, 0x0A, 0x00
	defb 0x2D, 0x0A, 0x00
	defb 0x5A, 0x05, 0x00
	defb 0x3C, 0x05, 0x00
	defb 0x1E, 0x04, 0x00
	defb 0x2D, 0x02, 0x00
	defb 0xB4, 0x01, 0x00
	defb 0xFF
	.EFECTO6
	defb 0xE8, 0x1B, 0x00
	defb 0x5F, 0x0F, 0x00
	defb 0xE2, 0x0F, 0x00
	defb 0x56, 0x0F, 0x00
	defb 0xF6, 0x0F, 0x00
	defb 0x14, 0x0E, 0x00
	defb 0x64, 0x0E, 0x00
	defb 0x62, 0x0D, 0x00
	defb 0xD0, 0x0D, 0x00
	defb 0xF1, 0x0C, 0x00
	defb 0xFF
	.EFECTO7
	defb 0xC3, 0x0E, 0x00
	defb 0x5F, 0x0F, 0x00
	defb 0xA6, 0x0F, 0x00
	defb 0xE8, 0x1B, 0x00
	defb 0x80, 0x2B, 0x00
	defb 0xFF
	.EFECTO8
	defb 0x1F, 0x0B, 0x00
	defb 0x5A, 0x0F, 0x00
	defb 0x3C, 0x0F, 0x00
	defb 0x1E, 0x0A, 0x00
	defb 0x2D, 0x0A, 0x00
	defb 0x5A, 0x05, 0x00
	defb 0x3C, 0x05, 0x00
	defb 0x1E, 0x04, 0x00
	defb 0x2D, 0x02, 0x00
	defb 0xB4, 0x01, 0x00
	defb 0xFF
	.EFECTO9
	defb 0xE8, 0x1B, 0x00
	defb 0x5F, 0x0F, 0x00
	defb 0xA6, 0x0F, 0x00
	defb 0x00, 0x00, 0x00
	defb 0x80, 0x0F, 0x00
	defb 0xFF
	.EFECTO10
	defb 0x1F, 0x0B, 0x00
	defb 0x5A, 0x0F, 0x00
	defb 0x3C, 0x0F, 0x00
	defb 0x1E, 0x0A, 0x00
	defb 0x2D, 0x0A, 0x00
	defb 0x5A, 0x05, 0x00
	defb 0x3C, 0x05, 0x00
	defb 0x1E, 0x04, 0x00
	defb 0x2D, 0x02, 0x00
	defb 0xB4, 0x01, 0x00
	defb 0xFF
	.EFECTO11
	defb 0x1A, 0x0E, 0x00
	defb 0xB4, 0x0E, 0x00
	defb 0xB4, 0x0E, 0x00
	defb 0xB4, 0x0E, 0x00
	defb 0xB4, 0x0E, 0x00
	defb 0xB4, 0x0E, 0x00
	defb 0xB4, 0x0E, 0x00
	defb 0xB4, 0x0E, 0x00
	defb 0xB4, 0x0E, 0x00
	defb 0xA0, 0x0E, 0x00
	defb 0xA0, 0x0E, 0x00
	defb 0xA0, 0x0E, 0x00
	defb 0xA0, 0x0E, 0x00
	defb 0xA0, 0x0E, 0x00
	defb 0xA0, 0x0E, 0x00
	defb 0xA0, 0x0E, 0x00
	defb 0x87, 0x0E, 0x00
	defb 0x87, 0x0E, 0x00
	defb 0x87, 0x0E, 0x00
	defb 0x87, 0x0E, 0x00
	defb 0x87, 0x0E, 0x00
	defb 0x87, 0x0E, 0x00
	defb 0x87, 0x0E, 0x00
	defb 0x87, 0x0E, 0x00
	defb 0x87, 0x0E, 0x00
	defb 0x78, 0x0E, 0x00
	defb 0x78, 0x0E, 0x00
	defb 0x78, 0x0D, 0x00
	defb 0x78, 0x0D, 0x00
	defb 0x78, 0x0D, 0x00
	defb 0x78, 0x0D, 0x00
	defb 0x78, 0x0D, 0x00
	defb 0x78, 0x0D, 0x00
	defb 0x78, 0x0C, 0x00
	defb 0x78, 0x09, 0x00
	defb 0x78, 0x06, 0x00
	defb 0x78, 0x05, 0x00
	defb 0xFF
	.EFECTO12
	defb 0xE8, 0x1B, 0x00
	defb 0xB4, 0x0F, 0x00
	defb 0xA0, 0x0E, 0x00
	defb 0x90, 0x0D, 0x00
	defb 0x87, 0x0D, 0x00
	defb 0x78, 0x0C, 0x00
	defb 0x6C, 0x0B, 0x00
	defb 0x60, 0x0A, 0x00
	defb 0x5A, 0x09, 0x00
	defb 0xFF
	.EFECTO13
	defb 0xE8, 0x1B, 0x00
	defb 0x5F, 0x0F, 0x00
	defb 0xA6, 0x0F, 0x00
	defb 0x00, 0x00, 0x00
	defb 0x80, 0x0F, 0x00
	defb 0xFF
	.EFECTO14
	defb 0xE8, 0x1B, 0x00
	defb 0x5F, 0x0F, 0x00
	defb 0xA6, 0x0F, 0x00
	defb 0x00, 0x00, 0x00
	defb 0x80, 0x0F, 0x00
	defb 0xFF
	; Tabla de instrumentos
	.TABLA_PAUTAS
	defw PAUTA_0,PAUTA_1,PAUTA_2,PAUTA_3,PAUTA_4,PAUTA_5
	; Tabla de efectos
	.TABLA_SONIDOS
	defw SONIDO0,SONIDO1,SONIDO2,SONIDO3
	;Pautas (instrumentos)
	;Instrumento 'Piano'
	.PAUTA_0
	defb 47,0,15,0,13,0,11,0,4,0,129
	;Instrumento 'PICC'
	.PAUTA_1
	defb 76,0,13,0,12,0,11,0,10,0,8,0,7,0,5,0,1,0,129
	;Instrumento 'Flauta vol bajo'
	.PAUTA_2
	defb 12,0,9,0,7,0,9,0,11,0,9,0,10,0,10,0,8,0,10,0,129
	;Instrumento 'Flauta'
	.PAUTA_3
	defb 10,0,12,0,13,0,13,0,13,0,12,0,11,0,11,0,11,0,10,0,10,0,10,0,10,0,10,0,9,0,9,0,9,0,9,0,9,0,138
	;Instrumento 'Picc vol 2'
	.PAUTA_4
	defb 71,0,6,0,7,0,6,0,5,0,129
	;Instrumento 'Eco'
	.PAUTA_5
	defb 6,0,8,0,9,0,8,0,7,0,6,0,129
	;Efectos
	;Efecto 'bass drum'
	.SONIDO0
	defb 209,62,0,186,92,0,255
	;Efecto 'drum'
	.SONIDO1
	defb 139,46,0,232,43,8,255
	;Efecto 'hithat'
	.SONIDO2
	defb 0,11,1,0,6,1,255
	;Efecto 'bass drum vol 2'
	.SONIDO3
	defb 186,58,0,0,102,0,162,131,0,255
	;Frecuencias para las notas
	._00_title_mus_bin
	BINARY "../mus/00_title.mus.bin"
	._01_ingame_mus_bin
	BINARY "../mus/01_ingame.mus.bin"
	._wyz_songs
	defw _00_title_mus_bin, _01_ingame_mus_bin

._wyz_init
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_isr_player_on),a
	call WYZPLAYER_INIT
	ret



._wyz_play_music
	push	hl
	ld	hl,_wyz_songs
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	push	de
	ld	hl,34816	;const
	push	hl
	call	_unpack
	pop	bc
	pop	bc
	ld a, 0
	call CARGA_CANCION
	ld a, 1
	ld (_isr_player_on), a
	pop	bc
	ret



._wyz_play_sound
	push	hl
	; Sound number is in L
	ld a, l
	ld b, 1
	call INICIA_EFECTO
	pop	bc
	ret



._wyz_stop_sound
	call PLAYER_OFF
	xor a
	ld (_isr_player_on), a
	ret


	; 1 PSG proPLAYER V 0.47c - WYZ 19.03.2016
	; (WYZTracker 2.0 o superior)
	.WYZPLAYER_INIT
	CALL PLAYER_OFF
	LD DE, 0x0020 ; No. BYTES RESERVADOS POR CANAL
	LD HL, 0xDF80 ;* RESERVAR MEMORIA PARA BUFFER DE SONIDO!!!!!
	LD (CANAL_A), HL
	ADD HL, DE
	LD (CANAL_B), HL
	ADD HL, DE
	LD (CANAL_C), HL
	ADD HL, DE
	LD (CANAL_P), HL
	RET
	.INICIO
	.WYZ_PLAYER_ISR
	CALL ROUT
	LD HL,PSG_REG
	LD DE,PSG_REG_SEC
	LD BC,14
	LDIR
	CALL REPRODUCE_SONIDO
	CALL PLAY
	JP REPRODUCE_EFECTO
	; REPRODUCE UN SONIDO POR EL CANAL ESPECIFICADO
	; IN
	; A = NUMERO DE SONIDO
	; B = CANAL
	.INICIA_SONIDO
	LD HL, TABLA_SONIDOS
	CALL EXT_WORD
	LD (PUNTERO_SONIDO), DE
	LD HL, INTERR
	SET 2, (HL)
	; na_th_an :: Percussion channel is fixed to 1
	;LD A, 1
	;LD HL, TABLA_DATOS_CANAL_SFX
	;CALL EXT_WORD
	;LD (SONIDO_REGS), DE
	RET
	; REPRODUCE UN FX POR EL CANAL ESPECIFICADO
	; IN
	; A = NUMERO DE SONIDO
	; B = CANAL
	.INICIA_EFECTO
	LD HL, TABLA_EFECTOS
	CALL EXT_WORD
	LD (PUNTERO_EFECTO), DE
	LD HL, INTERR
	SET 3, (HL)
	LD A, B
	LD HL, TABLA_DATOS_CANAL_SFX
	CALL EXT_WORD
	LD (EFECTO_REGS), DE
	RET
	;REPRODUCE EFECTOS DE SONIDO
	.REPRODUCE_SONIDO
	LD HL, INTERR
	BIT 2,(HL) ;ESTA ACTIVADO EL EFECTO?
	RET Z
	LD HL, (SONIDO_REGS)
	PUSH HL
	POP IX
	LD HL, (PUNTERO_SONIDO)
	CALL REPRODUCE_SONIDO_O_EFECTO
	OR A
	JR Z, REPRODUCE_SONIDO_LIMPIA_BIT
	LD (PUNTERO_SONIDO), HL
	RET
	.REPRODUCE_SONIDO_LIMPIA_BIT
	LD HL, INTERR
	RES 2, (HL)
	RET
	.REPRODUCE_EFECTO
	LD HL, INTERR
	BIT 3, (HL)
	RET Z
	LD HL, (EFECTO_REGS)
	PUSH HL
	POP IX
	LD HL, (PUNTERO_EFECTO)
	CALL REPRODUCE_SONIDO_O_EFECTO
	OR A
	JR Z, REPRODUCE_EFECTO_LIMPIA_BIT
	LD (PUNTERO_EFECTO), HL
	RET
	.REPRODUCE_EFECTO_LIMPIA_BIT
	LD HL, INTERR
	RES 3, (HL)
	RET
	.REPRODUCE_SONIDO_O_EFECTO
	LD A,(HL)
	CP 0xFF
	JR Z,FIN_SONIDO
	LD E, (IX+0) ; IX+0 -> SFX_L LO
	LD D, (IX+1) ; IX+1 -> SFX_L HI
	LD (DE),A
	INC HL
	LD A,(HL)
	RRCA
	RRCA
	RRCA
	RRCA
	AND 00001111B
	LD E, (IX+2) ; IX+2 -> SFX_H LO
	LD D, (IX+3) ; IX+3 -> SFX_H HI
	LD (DE),A
	LD A,(HL)
	AND 00001111B
	LD E, (IX+4) ; IX+4 -> SFX_V LO
	LD D, (IX+5) ; IX+5 -> SFX_V HI
	LD (DE),A
	INC HL
	LD A,(HL)
	LD B,A
	BIT 7,A ;09.08.13 BIT MAS SIGINIFICATIVO ACTIVA ENVOLVENTES
	JR Z,NO_ENVOLVENTES_SONIDO
	LD A,0x12
	LD (DE),A
	INC HL
	LD A,(HL)
	LD (PSG_REG_SEC+11),A
	INC HL
	LD A,(HL)
	LD (PSG_REG_SEC+12),A
	INC HL
	LD A,(HL)
	CP 1
	JR Z,NO_ENVOLVENTES_SONIDO ;NO ESCRIBE LA ENVOLVENTE SI SU VALOR ES 1
	LD (PSG_REG_SEC+13),A
	.NO_ENVOLVENTES_SONIDO
	LD A,B
	AND 0x7F ; RES 7,A ; AND A
	JR Z,NO_RUIDO
	LD (PSG_REG_SEC+6),A
	LD A, (IX+6) ; IX+6 -> SFX_MIX
	JR SI_RUIDO
	.NO_RUIDO XOR A
	LD (PSG_REG_SEC+6),A
	LD A,10111000B
	.SI_RUIDO LD (PSG_REG_SEC+7),A
	INC HL
	LD A, 1
	RET
	.FIN_SONIDO
	LD A,(ENVOLVENTE_BACK) ;NO RESTAURA LA ENVOLVENTE SI ES 0
	AND A
	JR Z,FIN_NOPLAYER
	;xor a ; ***
	LD (PSG_REG_SEC+13),A ;08.13 RESTAURA LA ENVOLVENTE TRAS EL SFX
	.FIN_NOPLAYER
	LD A,10111000B
	LD (PSG_REG_SEC+7),A
	XOR A
	RET
	;VUELCA BUFFER DE SONIDO AL PSG
	.ROUT
	LD A,(PSG_REG+13)
	AND A ;ES CERO?
	JR Z,NO_BACKUP_ENVOLVENTE
	LD (ENVOLVENTE_BACK),A ;08.13 / GUARDA LA ENVOLVENTE EN EL BACKUP
	XOR A
	.NO_BACKUP_ENVOLVENTE
	;VUELCA BUFFER DE SONIDO AL PSG
	LD HL,PSG_REG_SEC
	.LOUT
	CALL WRITEPSGHL
	INC A
	CP 13
	JR NZ,LOUT
	LD A,(HL)
	AND A
	RET Z
	LD A,13
	CALL WRITEPSGHL
	XOR A
	LD (PSG_REG+13),A
	LD (PSG_REG_SEC+13),A
	RET
	;; A = REGISTER
	;; (HL) = VALUE
	.WRITEPSGHL
	LD B,0xF4
	OUT (C),A
	LD BC,0xF6C0
	OUT (C),C
	DEFB 0xED
	DEFB 0x71
	LD B,0xF5
	OUTI
	LD BC,0xF680
	OUT (C),C
	DEFB 0xED
	DEFB 0x71
	RET
	;PLAYER OFF
	.PLAYER_OFF
	XOR A ;***** IMPORTANTE SI NO HAY MUSICA ****
	LD (INTERR),A
	;LD (FADE),A ;solo si hay fade out
	.CLEAR_PSG_BUFFER
	LD HL,PSG_REG
	LD DE,PSG_REG+1
	LD BC,14
	LD (HL),A
	LDIR
	LD A,10111000B ; **** POR SI ACASO ****
	LD (PSG_REG+7),A
	LD HL,PSG_REG
	LD DE,PSG_REG_SEC
	LD BC,14
	LDIR
	JP ROUT
	;CARGA UNA CANCION
	;.IN(A)=Nº DE CANCION
	.CARGA_CANCION
	LD HL,INTERR ;CARGA CANCION
	SET 1,(HL) ;REPRODUCE CANCION
	LD HL,SONG
	LD (HL),A ;Nº A
	;DECODIFICAR
	;IN-> INTERR 0 ON
	; SONG
	;CARGA CANCION SI/NO
	.DECODE_SONG
	LD A,(SONG)
	;LEE CABECERA DE LA CANCION
	;BYTE 0=TEMPO
	LD HL,TABLA_SONG
	CALL EXT_WORD
	LD A,(DE)
	LD (TEMPO),A
	DEC A
	LD (TTEMPO),A
	;HEADER BYTE 1
	;[-|-|-|-| 3-1 | 0 ]
	;[-|-|-|-|FX CHN|LOOP]
	INC DE ;LOOP 1=ON/0=OFF?
	LD A,(DE)
	BIT 0,A
	JR Z,NPTJP0
	LD HL,INTERR
	SET 4,(HL)
	;SELECCION DEL CANAL DE EFECTOS DE RITMO
	.NPTJP0
	AND 00000110B
	RRA
	;LD (SELECT_CANAL_P),A
	PUSH DE
	; na_th_an :: Percussion channel is fixed to 1
	;LD HL, TABLA_DATOS_CANAL_SFX
	;CALL EXT_WORD
	;LD (SONIDO_REGS), DE
	POP HL
	INC HL ;2 BYTES RESERVADOS
	INC HL
	INC HL
	;BUSCA Y GUARDA INICIO DE LOS CANALES EN EL MODULO MUS (OPTIMIZAR****************)
	;AÑADE OFFSET DEL LOOP
	PUSH HL ;IX INICIO OFFSETS LOOP POR CANAL
	POP IX
	LD DE,0x0008 ;HASTA INICIO DEL CANAL A
	ADD HL,DE
	LD (PUNTERO_P_DECA),HL ;GUARDA PUNTERO INICIO CANAL
	LD E,(IX+0)
	LD D,(IX+1)
	ADD HL,DE
	LD (PUNTERO_L_DECA),HL ;GUARDA PUNTERO INICIO LOOP
	CALL BGICMODBC1
	LD (PUNTERO_P_DECB),HL
	LD E,(IX+2)
	LD D,(IX+3)
	ADD HL,DE
	LD (PUNTERO_L_DECB),HL
	CALL BGICMODBC1
	LD (PUNTERO_P_DECC),HL
	LD E,(IX+4)
	LD D,(IX+5)
	ADD HL,DE
	LD (PUNTERO_L_DECC),HL
	CALL BGICMODBC1
	LD (PUNTERO_P_DECP),HL
	LD E,(IX+6)
	LD D,(IX+7)
	ADD HL,DE
	LD (PUNTERO_L_DECP),HL
	;LEE DATOS DE LAS NOTAS
	;[|][|||||] LONGITUD\NOTA
	.INIT_DECODER
	LD DE,(CANAL_A)
	LD (PUNTERO_A),DE
	LD HL,(PUNTERO_P_DECA)
	CALL DECODE_CANAL ;CANAL A
	LD (PUNTERO_DECA),HL
	LD DE,(CANAL_B)
	LD (PUNTERO_B),DE
	LD HL,(PUNTERO_P_DECB)
	CALL DECODE_CANAL ;CANAL B
	LD (PUNTERO_DECB),HL
	LD DE,(CANAL_C)
	LD (PUNTERO_C),DE
	LD HL,(PUNTERO_P_DECC)
	CALL DECODE_CANAL ;CANAL C
	LD (PUNTERO_DECC),HL
	LD DE,(CANAL_P)
	LD (PUNTERO_P),DE
	LD HL,(PUNTERO_P_DECP)
	CALL DECODE_CANAL ;CANAL P
	LD (PUNTERO_DECP),HL
	RET
	;BUSCA INICIO DEL CANAL
	.BGICMODBC1
	LD E,0x3F ;CODIGO INSTRUMENTO 0
	.BGICMODBC2
	XOR A ;BUSCA EL BYTE 0
	LD B,0xFF ;EL MODULO DEBE TENER UNA LONGITUD MENOR DE 0xFF00 ... o_O!
	CPIR
	DEC HL
	DEC HL
	LD A,E ;ES EL INSTRUMENTO 0??
	CP (HL)
	INC HL
	INC HL
	JR Z,BGICMODBC2
	DEC HL
	DEC HL
	DEC HL
	LD A,E ;ES VOLUMEN 0??
	CP (HL)
	INC HL
	INC HL
	INC HL
	JR Z,BGICMODBC2
	RET
	;DECODIFICA NOTAS DE UN CANAL
	;IN (DE)=DIRECCION DESTINO
	;NOTA=0 FIN CANAL
	;NOTA=1 SILENCIO
	;NOTA=2 PUNTILLO
	;NOTA=3 COMANDO I
	.DECODE_CANAL
	LD A,(HL)
	AND A ;FIN DEL CANAL?
	JR Z,FIN_DEC_CANAL
	CALL GETLEN
	CP 00000001B ;ES SILENCIO?
	JR NZ,NO_SILENCIO
	OR 0x40 ; SET 6,A
	JR NO_MODIFICA
	.NO_SILENCIO
	CP 00111110B ;ES PUNTILLO?
	JR NZ,NO_PUNTILLO
	OR A
	RRC B
	XOR A
	JR NO_MODIFICA
	.NO_PUNTILLO
	CP 00111111B ;ES COMANDO?
	JR NZ,NO_MODIFICA
	BIT 0,B ;COMADO=INSTRUMENTO?
	JR Z,NO_INSTRUMENTO
	LD A,11000001B ;CODIGO DE INSTRUMENTO
	LD (DE),A
	INC HL
	INC DE
	LDI ;Nº DE INSTRUMENTO
	; LD A,(HL)
	; LD (DE),A
	; INC DE
	; INC HL
	LDI ;VOLUMEN RELATIVO DEL INSTRUMENTO
	; LD A,(HL)
	; LD (DE),A
	; INC DE
	; INC HL
	JR DECODE_CANAL
	.NO_INSTRUMENTO
	BIT 2,B
	JR Z,NO_ENVOLVENTE
	LD A,11000100B ;CODIGO ENVOLVENTE
	LD (DE),A
	INC DE
	INC HL
	LDI
	; LD A,(HL)
	; LD (DE),A
	; INC DE
	; INC HL
	JR DECODE_CANAL
	.NO_ENVOLVENTE
	BIT 1,B
	JR Z,NO_MODIFICA
	LD A,11000010B ;CODIGO EFECTO
	LD (DE),A
	INC HL
	INC DE
	LD A,(HL)
	CALL GETLEN
	.NO_MODIFICA
	LD (DE),A
	INC DE
	XOR A
	DJNZ NO_MODIFICA
	OR 0x81 ; SET 7,A ; SET 0,A
	LD (DE),A
	INC DE
	INC HL
	RET ;** JR DECODE_CANAL
	.FIN_DEC_CANAL
	OR 0x80 ; SET 7,A
	LD (DE),A
	INC DE
	RET
	.GETLEN
	LD B,A
	AND 00111111B
	PUSH AF
	LD A,B
	AND 11000000B
	RLCA
	RLCA
	INC A
	LD B,A
	LD A,10000000B
	.DCBC0
	RLCA
	DJNZ DCBC0
	LD B,A
	POP AF
	RET
	;PLAY _______________________________
	.PLAY
	LD HL,INTERR ;PLAY BIT 1 ON?
	BIT 1,(HL)
	RET Z
	;TEMPO
	LD HL,TTEMPO ;CONTADOR TEMPO
	INC (HL)
	LD A,(TEMPO)
	CP (HL)
	JR NZ,PAUTAS
	LD (HL),0
	;INTERPRETA
	LD IY,PSG_REG
	LD IX,PUNTERO_A
	LD BC,PSG_REG+8
	CALL LOCALIZA_NOTA
	LD IY,PSG_REG+2
	LD IX,PUNTERO_B
	LD BC,PSG_REG+9
	CALL LOCALIZA_NOTA
	LD IY,PSG_REG+4
	LD IX,PUNTERO_C
	LD BC,PSG_REG+10
	CALL LOCALIZA_NOTA
	LD IX,PUNTERO_P ;EL CANAL DE EFECTOS ENMASCARA OTRO CANAL
	CALL LOCALIZA_EFECTO
	;PAUTAS
	.PAUTAS
	LD IY,PSG_REG+0
	LD IX,PUNTERO_P_A
	LD HL,PSG_REG+8
	CALL PAUTA ;PAUTA CANAL A
	LD IY,PSG_REG+2
	LD IX,PUNTERO_P_B
	LD HL,PSG_REG+9
	CALL PAUTA ;PAUTA CANAL B
	LD IY,PSG_REG+4
	LD IX,PUNTERO_P_C
	LD HL,PSG_REG+10
	JP PAUTA ;PAUTA CANAL C
	;LOCALIZA NOTA CANAL A
	;IN (PUNTERO_A)
	;LOCALIZA NOTA CANAL A
	;IN (PUNTERO_A)
	.LOCALIZA_NOTA
	LD L,(IX+PUNTERO_A-PUNTERO_A) ;HL=(PUNTERO_A_C_B)
	LD H,(IX+PUNTERO_A-PUNTERO_A+1)
	LD A,(HL)
	AND 11000000B ;COMANDO?
	CP 11000000B
	JR NZ,LNJP0
	;BIT(0)=INSTRUMENTO
	.COMANDOS
	LD A,(HL)
	BIT 0,A ;INSTRUMENTO
	JR Z,COM_EFECTO
	INC HL
	LD A,(HL) ;Nº DE PAUTA
	INC HL
	LD E,(HL)
	PUSH HL ;;TEMPO ******************
	LD HL,TEMPO
	BIT 5,E
	JR Z,NO_DEC_TEMPO
	DEC (HL)
	.NO_DEC_TEMPO
	BIT 6,E
	JR Z,NO_INC_TEMPO
	INC (HL)
	.NO_INC_TEMPO
	RES 5,E ;SIEMPRE RESETEA LOS BITS DE TEMPO
	RES 6,E
	POP HL
	LD (IX+VOL_INST_A-PUNTERO_A),E ;REGISTRO DEL VOLUMEN RELATIVO
	INC HL
	LD (IX+PUNTERO_A-PUNTERO_A),L
	LD (IX+PUNTERO_A-PUNTERO_A+1),H
	LD HL,TABLA_PAUTAS
	CALL EXT_WORD
	LD (IX+PUNTERO_P_A0-PUNTERO_A),E
	LD (IX+PUNTERO_P_A0-PUNTERO_A+1),D
	LD (IX+PUNTERO_P_A-PUNTERO_A),E
	LD (IX+PUNTERO_P_A-PUNTERO_A+1),D
	LD L,C
	LD H,B
	RES 4,(HL) ;APAGA EFECTO ENVOLVENTE
	XOR A
	LD (PSG_REG_SEC+13),A
	LD (PSG_REG+13),A
	;LD (ENVOLVENTE_BACK),A ;08.13 / RESETEA EL BACKUP DE LA ENVOLVENTE
	JR LOCALIZA_NOTA
	.COM_EFECTO
	BIT 1,A ;EFECTO DE SONIDO
	JR Z,COM_ENVOLVENTE
	INC HL
	LD A,(HL)
	INC HL
	LD (IX+PUNTERO_A-PUNTERO_A),L
	LD (IX+PUNTERO_A-PUNTERO_A+1),H
	JP INICIA_SONIDO
	.COM_ENVOLVENTE
	BIT 2,A
	RET Z ;IGNORA - ERROR
	INC HL
	LD A,(HL) ;CARGA CODIGO DE ENVOLVENTE
	LD (ENVOLVENTE),A
	INC HL
	LD (IX+PUNTERO_A-PUNTERO_A),L
	LD (IX+PUNTERO_A-PUNTERO_A+1),H
	LD L,C
	LD H,B
	LD (HL),00010000B ;ENCIENDE EFECTO ENVOLVENTE
	JR LOCALIZA_NOTA
	.LNJP0
	LD A,(HL)
	INC HL
	BIT 7,A
	JR Z,NO_FIN_CANAL_A ;
	BIT 0,A
	JR Z,FIN_CANAL_A
	.FIN_NOTA_A
	LD E,(IX+CANAL_A-PUNTERO_A)
	LD D,(IX+CANAL_A-PUNTERO_A+1) ;PUNTERO BUFFER AL INICIO
	LD (IX+PUNTERO_A-PUNTERO_A),E
	LD (IX+PUNTERO_A-PUNTERO_A+1),D
	LD L,(IX+PUNTERO_DECA-PUNTERO_A) ;CARGA PUNTERO DECODER
	LD H,(IX+PUNTERO_DECA-PUNTERO_A+1)
	PUSH BC
	CALL DECODE_CANAL ;DECODIFICA CANAL
	POP BC
	LD (IX+PUNTERO_DECA-PUNTERO_A),L ;GUARDA PUNTERO DECODER
	LD (IX+PUNTERO_DECA-PUNTERO_A+1),H
	JP LOCALIZA_NOTA
	.FIN_CANAL_A
	LD HL,INTERR ;LOOP?
	BIT 4,(HL)
	JR NZ,FCA_CONT
	POP AF
	JP PLAYER_OFF
	.FCA_CONT
	LD L,(IX+PUNTERO_L_DECA-PUNTERO_A) ;CARGA PUNTERO INICIAL DECODER
	LD H,(IX+PUNTERO_L_DECA-PUNTERO_A+1)
	LD (IX+PUNTERO_DECA-PUNTERO_A),L
	LD (IX+PUNTERO_DECA-PUNTERO_A+1),H
	JR FIN_NOTA_A
	.NO_FIN_CANAL_A
	LD (IX+PUNTERO_A-PUNTERO_A),L ;(PUNTERO_A_B_C)=HL GUARDA PUNTERO
	LD (IX+PUNTERO_A-PUNTERO_A+1),H
	AND A ;NO REPRODUCE NOTA SI NOTA=0
	JR Z,FIN_RUTINA
	BIT 6,A ;SILENCIO?
	JR Z,NO_SILENCIO_A
	LD A,(BC)
	AND 00010000B
	JR NZ,SILENCIO_ENVOLVENTE
	XOR A
	LD (BC),A ;RESET VOLUMEN DEL CORRESPODIENTE CHIP
	LD (IY+0),A
	LD (IY+1),A
	RET
	.SILENCIO_ENVOLVENTE
	LD A,0xFF
	LD (PSG_REG+11),A
	LD (PSG_REG+12),A
	XOR A
	LD (PSG_REG+13),A
	LD (IY+0),A
	LD (IY+1),A
	RET
	.NO_SILENCIO_A
	LD (IX+REG_NOTA_A-PUNTERO_A),A ;REGISTRO DE LA NOTA DEL CANAL
	CALL NOTA ;REPRODUCE NOTA
	LD L,(IX+PUNTERO_P_A0-PUNTERO_A) ;HL=(PUNTERO_P_A0) RESETEA PAUTA
	LD H,(IX+PUNTERO_P_A0-PUNTERO_A+1)
	LD (IX+PUNTERO_P_A-PUNTERO_A),L ;(PUNTERO_P_A)=HL
	LD (IX+PUNTERO_P_A-PUNTERO_A+1),H
	.FIN_RUTINA
	RET
	;LOCALIZA EFECTO
	;IN HL=(PUNTERO_P)
	.LOCALIZA_EFECTO
	LD L,(IX+0) ;HL=(PUNTERO_P)
	LD H,(IX+1)
	LD A,(HL)
	CP 11000010B
	JR NZ,LEJP0
	INC HL
	LD A,(HL)
	INC HL
	LD (IX+00),L
	LD (IX+01),H
	JP INICIA_SONIDO
	.LEJP0
	INC HL
	BIT 7,A
	JR Z,NO_FIN_CANAL_P ;
	BIT 0,A
	JR Z,FIN_CANAL_P
	.FIN_NOTA_P
	LD DE,(CANAL_P)
	LD (IX+0),E
	LD (IX+1),D
	LD HL,(PUNTERO_DECP) ;CARGA PUNTERO DECODER
	PUSH BC
	CALL DECODE_CANAL ;DECODIFICA CANAL
	POP BC
	LD (PUNTERO_DECP),HL ;GUARDA PUNTERO DECODER
	JP LOCALIZA_EFECTO
	.FIN_CANAL_P
	LD HL,(PUNTERO_L_DECP) ;CARGA PUNTERO INICIAL DECODER
	LD (PUNTERO_DECP),HL
	JR FIN_NOTA_P
	.NO_FIN_CANAL_P
	LD (IX+0),L ;(PUNTERO_A_B_C)=HL GUARDA PUNTERO
	LD (IX+1),H
	RET
	; PAUTA DE LOS 3 CANALES
	; .IN(IX):PUNTERO DE LA PAUTA
	; (HL):REGISTRO DE VOLUMEN
	; (IY):REGISTROS DE FRECUENCIA
	; FORMATO PAUTA
	; 7 6 5 4 3-0 3-0
	; BYTE 1 [LOOP|OCT-1|OCT+1|ORNMT|VOL] - BYTE 2 [ | | | |PITCH/NOTA]
	.PAUTA
	BIT 4,(HL) ;SI LA ENVOLVENTE ESTA ACTIVADA NO ACTUA PAUTA
	RET NZ
	LD A,(IY+0)
	LD B,(IY+1)
	OR B
	RET Z
	PUSH HL
	.PCAJP4
	LD L,(IX+0)
	LD H,(IX+1)
	LD A,(HL)
	BIT 7,A ;LOOP / EL RESTO DE BITS NO AFECTAN
	JR Z,PCAJP0
	AND 00011111B ;MÁXIMO LOOP PAUTA (0,32)X2!!!-> PARA ORNAMENTOS
	RLCA ;X2
	LD D,0
	LD E,A
	SBC HL,DE
	LD A,(HL)
	.PCAJP0
	BIT 6,A ;OCTAVA -1
	JR Z,PCAJP1
	LD E,(IY+0)
	LD D,(IY+1)
	AND A
	RRC D
	RR E
	LD (IY+0),E
	LD (IY+1),D
	JR PCAJP2
	.PCAJP1
	BIT 5,A ;OCTAVA +1
	JR Z,PCAJP2
	LD E,(IY+0)
	LD D,(IY+1)
	AND A
	RLC E
	RL D
	LD (IY+0),E
	LD (IY+1),D
	.PCAJP2
	LD A,(HL)
	BIT 4,A
	JR NZ,PCAJP6 ;ORNAMENTOS SELECCIONADOS
	INC HL ;______________________ FUNCION PITCH DE FRECUENCIA__________________
	PUSH HL
	LD E,A
	LD A,(HL) ;PITCH DE FRECUENCIA
	LD L,A
	AND A
	LD A,E
	JR Z,ORNMJP1
	LD A,(IY+0) ;SI LA FRECUENCIA ES 0 NO HAY PITCH
	ADD A,(IY+1)
	AND A
	LD A,E
	JR Z,ORNMJP1
	BIT 7,L
	JR Z,ORNNEG
	LD H,0xFF
	JR PCAJP3
	.ORNNEG
	LD H,0
	.PCAJP3
	LD E,(IY+0)
	LD D,(IY+1)
	ADC HL,DE
	LD (IY+0),L
	LD (IY+1),H
	JR ORNMJP1
	.PCAJP6
	INC HL ;______________________ FUNCION ORNAMENTOS__________________
	PUSH HL
	PUSH AF
	LD A,(IX+REG_NOTA_A-PUNTERO_P_A) ;RECUPERA REGISTRO DE NOTA EN EL CANAL
	LD E,(HL) ;
	ADC E ;+- NOTA
	CALL TABLA_NOTAS
	POP AF
	.ORNMJP1
	POP HL
	INC HL
	LD (IX+0),L
	LD (IX+1),H
	.PCAJP5
	POP HL
	LD B,(IX+VOL_INST_A-PUNTERO_P_A) ;VOLUMEN RELATIVO
	ADD B
	JP P,PCAJP7
	LD A,1 ;NO SE EXTIGUE EL VOLUMEN
	.PCAJP7
	AND 00001111B ;VOLUMEN FINAL MODULADO
	LD (HL),A
	RET
	;NOTA - REPRODUCE UNA NOTA
	;IN (A)=CODIGO DE LA NOTA
	; (IY)=REGISTROS DE FRECUENCIA
	.NOTA
	LD L,C
	LD H,B
	BIT 4,(HL)
	LD B,A
	JR NZ,EVOLVENTES
	LD A,B
	.TABLA_NOTAS
	LD HL,DATOS_NOTAS ;BUSCA FRECUENCIA
	CALL EXT_WORD
	LD (IY+0),E
	LD (IY+1),D
	RET
	;IN (A)=CODIGO DE LA ENVOLVENTE
	; (IY)=REGISTRO DE FRECUENCIA
	.EVOLVENTES
	LD HL,DATOS_NOTAS
	;SUB 12
	RLCA ;X2
	LD D,0
	LD E,A
	ADD HL,DE
	LD E,(HL)
	INC HL
	LD D,(HL)
	PUSH DE
	LD A,(ENVOLVENTE) ;FRECUENCIA DEL CANAL ON/OFF
	RRA
	JR NC,FRECUENCIA_OFF
	LD (IY+0),E
	LD (IY+1),D
	JR CONT_ENV
	.FRECUENCIA_OFF
	LD DE,0x0000
	LD (IY+0),E
	LD (IY+1),D
	;CALCULO DEL RATIO (OCTAVA ARRIBA)
	.CONT_ENV
	POP DE
	PUSH AF
	PUSH BC
	AND 00000011B
	LD B,A
	;INC B
	;AND A ;1/2
	RR D
	RR E
	.CRTBC0
	;AND A ;1/4 - 1/8 - 1/16
	RR D
	RR E
	DJNZ CRTBC0
	LD A,E
	LD (PSG_REG+11),A
	LD A,D
	AND 00000011B
	LD (PSG_REG+12),A
	POP BC
	POP AF ;SELECCION FORMA DE ENVOLVENTE
	RRA
	AND 00000110B ;0x08,0x0A,0x0C,0x0E
	ADD 8
	LD (PSG_REG+13),A
	LD (ENVOLVENTE_BACK),A
	RET
	;EXTRAE UN WORD DE UNA TABLA
	;.IN(HL)=DIRECCION TABLA
	; (A)= POSICION
	;OUT(DE)=WORD
	.EXT_WORD
	LD D,0
	RLCA
	LD E,A
	ADD HL,DE
	LD E,(HL)
	INC HL
	LD D,(HL)
	RET
	;TABLA DE DATOS DEL SELECTOR DEL CANAL DE EFECTOS DE RITMO
	.TABLA_DATOS_CANAL_SFX
	defw SELECT_CANAL_A,SELECT_CANAL_B,SELECT_CANAL_C
	;BYTE 0:SFX_L
	;BYTE 1:SFX_H
	;BYTE 2:SFX_V
	;BYTE 3:SFX_MIX
	.SELECT_CANAL_A
	defw PSG_REG_SEC+0, PSG_REG_SEC+1, PSG_REG_SEC+8
	defb 10110001B
	.SELECT_CANAL_B
	defw PSG_REG_SEC+2, PSG_REG_SEC+3, PSG_REG_SEC+9
	defb 10101010B
	.SELECT_CANAL_C
	defw PSG_REG_SEC+4, PSG_REG_SEC+5, PSG_REG_SEC+10
	defb 10011100B
	;_______________________________
	.INTERR
	defb 0 ;INTERRUPTORES 1=ON 0=OFF
	;BIT 0=CARGA CANCION ON/OFF
	;BIT 1=PLAYER ON/OFF
	;BIT 2=EFECTOS ON/OFF
	;BIT 3=SFX ON/OFF
	;BIT 4=LOOP
	;MUSICA **** EL ORDEN DE LAS VARIABLES ES FIJO ******
	.SONG defb 0 ;DBNº DE CANCION
	.TEMPO defb 0 ;DB TEMPO
	.TTEMPO defb 0 ;DB CONTADOR TEMPO
	.PUNTERO_A defw 0 ;DW PUNTERO DEL CANAL A
	.PUNTERO_B defw 0 ;DW PUNTERO DEL CANAL B
	.PUNTERO_C defw 0 ;DW PUNTERO DEL CANAL C
	.CANAL_A defw 0 ;DW DIRECION DE INICIO DE LA MUSICA A
	.CANAL_B defw 0 ;DW DIRECION DE INICIO DE LA MUSICA B
	.CANAL_C defw 0 ;DW DIRECION DE INICIO DE LA MUSICA C
	.PUNTERO_P_A defw 0 ;DW PUNTERO PAUTA CANAL A
	.PUNTERO_P_B defw 0 ;DW PUNTERO PAUTA CANAL B
	.PUNTERO_P_C defw 0 ;DW PUNTERO PAUTA CANAL C
	.PUNTERO_P_A0 defw 0 ;DW INI PUNTERO PAUTA CANAL A
	.PUNTERO_P_B0 defw 0 ;DW INI PUNTERO PAUTA CANAL B
	.PUNTERO_P_C0 defw 0 ;DW INI PUNTERO PAUTA CANAL C
	.PUNTERO_P_DECA defw 0 ;DW PUNTERO DE INICIO DEL DECODER CANAL A
	.PUNTERO_P_DECB defw 0 ;DW PUNTERO DE INICIO DEL DECODER CANAL B
	.PUNTERO_P_DECC defw 0 ;DW PUNTERO DE INICIO DEL DECODER CANAL C
	.PUNTERO_DECA defw 0 ;DW PUNTERO DECODER CANAL A
	.PUNTERO_DECB defw 0 ;DW PUNTERO DECODER CANAL B
	.PUNTERO_DECC defw 0 ;DW PUNTERO DECODER CANAL C
	.PUNTERO_EFECTO defw 0 ;DW PUNTERO DEL SONIDO QUE SE REPRODUCE
	.REG_NOTA_A defb 0 ;DB REGISTRO DE LA NOTA EN EL CANAL A
	.VOL_INST_A defb 0 ;DB VOLUMEN RELATIVO DEL INSTRUMENTO DEL CANAL A
	.REG_NOTA_B defb 0 ;DB REGISTRO DE LA NOTA EN EL CANAL B
	.VOL_INST_B defb 0 ;DB VOLUMEN RELATIVO DEL INSTRUMENTO DEL CANAL B ;VACIO
	.REG_NOTA_C defb 0 ;DB REGISTRO DE LA NOTA EN EL CANAL C
	.VOL_INST_C defb 0 ;DB VOLUMEN RELATIVO DEL INSTRUMENTO DEL CANAL C
	.PUNTERO_L_DECA defw 0 ;DW PUNTERO DE INICIO DEL LOOP DEL DECODER CANAL A
	.PUNTERO_L_DECB defw 0 ;DW PUNTERO DE INICIO DEL LOOP DEL DECODER CANAL B
	.PUNTERO_L_DECC defw 0 ;DW PUNTERO DE INICIO DEL LOOP DEL DECODER CANAL C
	;CANAL DE EFECTOS DE RITMO - ENMASCARA OTRO CANAL
	.PUNTERO_P defw 0 ;DW PUNTERO DEL CANAL EFECTOS
	.CANAL_P defw 0 ;DW DIRECION DE INICIO DE LOS EFECTOS
	.PUNTERO_P_DECP defw 0 ;DW PUNTERO DE INICIO DEL DECODER CANAL P
	.PUNTERO_DECP defw 0 ;DW PUNTERO DECODER CANAL P
	.PUNTERO_L_DECP defw 0 ;DW PUNTERO DE INICIO DEL LOOP DEL DECODER CANAL P
	;SELECT_CANAL_P defb INTERR+0x36 ;DB SELECCION DE CANAL DE EFECTOS DE RITMO
	.SFX_L defw 0 ;DW DIRECCION BUFFER EFECTOS DE RITMO REGISTRO BAJO
	.SFX_H defw 0 ;DW DIRECCION BUFFER EFECTOS DE RITMO REGISTRO ALTO
	.SFX_V defw 0 ;DW DIRECCION BUFFER EFECTOS DE RITMO REGISTRO VOLUMEN
	.SFX_MIX defw 0 ;DW DIRECCION BUFFER EFECTOS DE RITMO REGISTRO MIXER
	;EFECTOS DE SONIDO
	.N_SONIDO defb 0 ;DB : NUMERO DE SONIDO
	.PUNTERO_SONIDO defw 0 ;DW : PUNTERO DEL SONIDO QUE SE REPRODUCE
	.EFECTO_REGS defw 0
	.SONIDO_REGS defw SELECT_CANAL_B ; na_th_an :: Percussion channel is fixed to 1
	;DB (13) BUFFERs DE REGISTROS DEL PSG
	.PSG_REG defs 16
	.PSG_REG_SEC defs 16
	.ENVOLVENTE
	defb 0 ;DB : FORMA DE LA ENVOLVENTE
	;BIT 0 : FRECUENCIA CANAL ON/OFF
	;BIT 1-2 : RATIO
	;BIT 3-3 : FORMA
	.ENVOLVENTE_BACK defb 0 ;.defb BACKUP DE LA FORMA DE LA ENVOLENTE
	.DATOS_NOTAS
	defw 0x0000, 0x0000
	defw 964,910,859,811,766,722,682,644,608,573
	defw 541,511,482,455,430,405,383,361,341,322
	defw 304,287,271,255,241,228,215,203,191,180
	defw 170,161,152,143,135,128,121,114,107,101
	defw 96,90,85,81,76,72,68,64,60,57
	defw 54,51,48,45,43,40,38,36,34,32
	.TABLA_SONG
	defw 0x8800
	.TABLA_EFECTOS
	defw EFECTO0, EFECTO1, EFECTO2, EFECTO3, EFECTO4, EFECTO5, EFECTO6, EFECTO7
	defw EFECTO8, EFECTO9, EFECTO10, EFECTO11, EFECTO12, EFECTO13, EFECTO14

._title_screen
	call	_blackout
	ld	hl,_s_title
	push	hl
	ld	hl,36864	;const
	push	hl
	call	_unpack
	pop	bc
	pop	bc
	ld	hl,1	;const
	call	cpc_ShowTileMap
	ld	hl,0	;const
	call	_wyz_play_music
.i_188
	ld	hl,10	;const
	call	cpc_TestKey
	ld	a,h
	or	l
	jp	z,i_190
	ld	hl,_def_keys
	ld	(__gp_gen),hl
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_is_joystick),a
	jp	i_189
.i_190
	ld	hl,11	;const
	call	cpc_TestKey
	ld	a,h
	or	l
	jp	z,i_191
	ld	hl,_def_keys_joy
	ld	(__gp_gen),hl
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_is_joystick),a
	jp	i_189
.i_191
	jp	i_188
.i_189
	call	_wyz_stop_sound
	._copy_keys_to_extern
	ld hl, (__gp_gen)
	ld de, cpc_KeysData + 12
	ld bc, 24
	ldir
	ret



._main
	call	_wyz_init
	di
	ld hl, 0xC000
	xor a
	ld (hl), a
	ld de, 0xC001
	ld bc, 0x3DFF
	ldir
	ld a, 195
	ld (0x38), a
	ld hl, _isr
	ld (0x39), hl
	jp isr_done
	._isr
	push af
	ld a, (isr_c1)
	inc a
	cp 6
	jr c, _skip_player
	ld a, (isr_c2)
	inc a
	ld (isr_c2), a
	ld a, (_isr_player_on)
	or a
	jr z, _skip_player
	push hl
	push de
	push bc
	push ix
	push iy
	call WYZ_PLAYER_ISR
	pop iy
	pop ix
	pop bc
	pop de
	pop hl
	xor a
	._skip_player
	ld (isr_c1), a
	pop af
	ei
	ret
	.isr_c1
	defb 0
	.isr_c2
	defb 0
	.isr_done
	ld a, 0x54
	ld bc, 0x7F11
	out (c), c
	out (c), a
	ld	hl,_trpixlutc
	push	hl
	ld	hl,65024	;const
	push	hl
	call	_unpack
	pop	bc
	pop	bc
	call	_blackout
	ld	hl,_my_inks
	push	hl
	call	_pal_set
	pop	bc
	ld	hl,1	;const
	call	cpc_SetMode
	; Horizontal chars (32), CRTC REG #1
	ld b, 0xbc
	ld c, 1 ; REG = 1
	out (c), c
	inc b
	ld c, 32 ; VALUE = 32
	out (c), c
	; Horizontal pos (42), CRTC REG #2
	ld b, 0xbc
	ld c, 2 ; REG = 2
	out (c), c
	inc b
	ld c, 42 ; VALUE = 42
	out (c), c
	; Vertical chars (24), CRTC REG #6
	ld b, 0xbc
	ld c, 6 ; REG = 6
	out (c), c
	inc b
	ld c, 24 ; VALUE = 24
	out (c), c
	ld	hl,_sp_sw+6
	push	hl
	ld	hl,(_sm_cox)
	ld	h,0
	pop	de
	ld	a,l
	ld	(de),a
	ld	hl,_sp_sw+7
	push	hl
	ld	hl,(_sm_coy)
	ld	h,0
	ld	a,l
	call	l_sxt
	pop	de
	ld	a,l
	ld	(de),a
	ld	de,_sp_sw+12
	ld	hl,(_sm_invfunc)
	call	l_pint
	ld	de,_sp_sw+14
	ld	hl,(_sm_updfunc)
	call	l_pint
	ld	hl,_sp_sw
	push	hl
	inc	hl
	inc	hl
	ex	de,hl
	ld	hl,(_sm_sprptr)
	call	l_pint
	call	l_pint_pop
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_gpit),a
	jp	i_194
.i_192
	ld	hl,_gpit
	ld	a,(hl)
	inc	(hl)
.i_194
	ld	a,(_gpit)
	cp	#(4 % 256)
	jp	z,i_193
	jp	nc,i_193
	ld	hl,_sp_sw
	push	hl
	ld	hl,(_gpit)
	ld	h,0
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,12
	add	hl,bc
	push	hl
	ld	hl,cpc_PutSpTileMap4x8
	call	l_pint_pop
	ld	hl,_sp_sw
	push	hl
	ld	hl,(_gpit)
	ld	h,0
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,14
	add	hl,bc
	push	hl
	ld	hl,cpc_PutTrSp4x8TileMap2b
	call	l_pint_pop
	jp	i_192
.i_193
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_gpit),a
	jp	i_197
.i_195
	ld	hl,(_gpit)
	ld	h,0
	inc	hl
	ld	a,l
	ld	(_gpit),a
.i_197
	ld	a,(_gpit)
	cp	#(4 % 256)
	jp	z,i_196
	jp	nc,i_196
	ld	de,_spr_on
	ld	hl,(_gpit)
	ld	h,0
	add	hl,de
	ld	(hl),#(0 % 256 % 256)
	ld	hl,_sp_sw
	push	hl
	ld	hl,(_gpit)
	ld	h,0
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,10
	add	hl,bc
	ld	(hl),#(2 % 256 % 256)
	ld	hl,_sp_sw
	push	hl
	ld	hl,(_gpit)
	ld	h,0
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,11
	add	hl,bc
	ld	(hl),#(24 % 256 % 256)
	ld	l,(hl)
	ld	h,0
	jp	i_195
.i_196
	ei
.i_198
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_level),a
	call	_title_screen
	; Makes debugging easier
	._game_loop_init
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_playing),a
	call	_player_init
	call	_hotspots_init
	call	_locks_init
	call	_enems_init
	ld	a,#(20 % 256 % 256)
	ld	(_n_pant),a
	ld	a,#(0 % 256 % 256)
	ld	(_maincounter),a
	ld	hl,1	;const
	call	_wyz_play_music
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_half_life),a
	ld	(_success),a
	ld	a,l
	ld	(_p_killme),a
	ld	hl,255 % 256	;const
	ld	a,l
	ld	(_killed_old),a
	ld	(_life_old),a
	ld	h,0
	ld	a,l
	ld	(_keys_old),a
	ld	(_objs_old),a
	ld	hl,255 % 256	;const
	ld	a,l
	ld	(_o_pant),a
.i_200
	ld	hl,(_playing)
	ld	a,l
	and	a
	jp	z,i_201
	; Makes debugging easier
	._game_loop_do
	ld	a,#(1 % 256 % 256)
	ld	(_p_kill_amt),a
	ld	de,(_o_pant)
	ld	d,0
	ld	hl,(_n_pant)
	ld	h,d
	call	l_ne
	jp	nc,i_202
	call	_draw_scr
	ld	a,((_n_pant))
	ld	(_o_pant),a
.i_202
	ld	de,(_p_life)
	ld	d,0
	ld	hl,(_life_old)
	ld	h,d
	call	l_ne
	jp	nc,i_203
	ld	a,#(4 % 256 % 256)
	ld	(__x),a
	ld	a,#(1 % 256 % 256)
	ld	(__y),a
	ld	hl,(_p_life)
	ld	h,0
	ld	a,l
	ld	(__t),a
	call	_print_number2
	ld	a,((_p_life))
	ld	(_life_old),a
.i_203
	ld	de,(_p_keys)
	ld	d,0
	ld	hl,(_keys_old)
	ld	h,d
	call	l_ne
	jp	nc,i_204
	ld	a,#(10 % 256 % 256)
	ld	(__x),a
	ld	a,#(1 % 256 % 256)
	ld	(__y),a
	ld	hl,(_p_keys)
	ld	h,0
	ld	a,l
	ld	(__t),a
	call	_print_number2
	ld	a,((_p_keys))
	ld	(_keys_old),a
.i_204
	ld	de,(_p_killed)
	ld	d,0
	ld	hl,(_killed_old)
	ld	h,d
	call	l_ne
	jp	nc,i_205
	ld	a,#(16 % 256 % 256)
	ld	(__x),a
	ld	a,#(1 % 256 % 256)
	ld	(__y),a
	ld	hl,(_p_killed)
	ld	h,0
	ld	a,l
	ld	(__t),a
	call	_print_number2
	ld	a,((_p_killed))
	ld	(_killed_old),a
.i_205
	ld	hl,_maincounter
	ld	a,(hl)
	inc	(hl)
	ld	hl,(_half_life)
	ld	h,0
	call	l_lneg
	ld	hl,0	;const
	rl	l
	ld	a,l
	ld	(_half_life),a
	call	_player_move
	call	_enems_move
	ld	a,(_p_killme)
	and	a
	jp	z,i_206
	ld	a,(_p_life)
	and	a
	jp	z,i_207
	ld	hl,(_p_killme)
	ld	h,0
	push	hl
	call	_player_kill
	pop	bc
	jp	i_208
.i_207
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_playing),a
.i_208
.i_206
	ld	de,(_o_pant)
	ld	d,0
	ld	hl,(_n_pant)
	ld	h,d
	call	l_eq
	jp	nc,i_209
	ld	hl,1	;const
	push	hl
	call	_cpc_UpdateNow
	pop	bc
.i_209
	ld	a,(_p_estado)
	cp	#(2 % 256)
	jp	nz,i_210
	ld	hl,_p_ct_estado
	ld	a,(hl)
	dec	(hl)
	ld	a,(_p_ct_estado)
	and	a
	jp	nz,i_211
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_p_estado),a
.i_211
.i_210
	call	_hotspots_do
	ld	a,(_gpx)
	cp	#(0 % 256)
	jp	nz,i_213
	ld	hl,(_p_vx)
	ld	de,0	;const
	ex	de,hl
	call	l_lt
	jr	c,i_214_i_213
.i_213
	jp	i_212
.i_214_i_213
	ld	hl,(_n_pant)
	ld	h,0
	dec	hl
	ld	a,l
	ld	(_n_pant),a
	ld	a,#(224 % 256 % 256)
	ld	(_gpx),a
	ld	hl,14336	;const
	ld	(_p_x),hl
.i_212
	ld	a,(_gpx)
	cp	#(224 % 256)
	jp	nz,i_216
	ld	hl,(_p_vx)
	ld	de,0	;const
	ex	de,hl
	call	l_gt
	jr	c,i_217_i_216
.i_216
	jp	i_215
.i_217_i_216
	ld	a,(_n_pant)
	inc	a
	ld	(_n_pant),a
	ld	hl,0	;const
	ld	(_p_x),hl
	ld	h,0
	ld	a,l
	ld	(_gpx),a
.i_215
	ld	a,(_gpy)
	cp	#(0 % 256)
	jp	nz,i_219
	ld	hl,(_p_vy)
	ld	de,0	;const
	ex	de,hl
	call	l_lt
	jp	nc,i_219
	ld	a,(_n_pant)
	cp	#(4 % 256)
	jr	z,i_219_uge
	jp	c,i_219
.i_219_uge
	jr	i_220_i_219
.i_219
	jp	i_218
.i_220_i_219
	ld	hl,(_n_pant)
	ld	h,0
	ld	bc,-4
	add	hl,bc
	ld	h,0
	ld	a,l
	ld	(_n_pant),a
	ld	a,#(144 % 256 % 256)
	ld	(_gpy),a
	ld	hl,9216	;const
	ld	(_p_y),hl
.i_218
	ld	a,(_gpy)
	cp	#(144 % 256)
	jr	z,i_222_uge
	jp	c,i_222
.i_222_uge
	ld	hl,(_p_vy)
	ld	de,0	;const
	ex	de,hl
	call	l_gt
	jr	c,i_223_i_222
.i_222
	jp	i_221
.i_223_i_222
	ld	a,(_n_pant)
	cp	#(20 % 256)
	jp	z,i_224
	jp	nc,i_224
	ld	hl,_n_pant
	ld	a,4 % 256
	add	(hl)
	ld	(hl),a
	ld	hl,0	;const
	ld	(_p_y),hl
	ld	a,l
	ld	(_gpy),a
	ld	hl,(_p_vy)
	ld	de,256	;const
	ex	de,hl
	call	l_gt
	jp	nc,i_225
	ld	hl,256	;const
	ld	(_p_vy),hl
.i_225
.i_224
.i_221
	jp	i_226
	ld	a,#(1 % 256 % 256)
	ld	(_success),a
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_playing),a
.i_226
	jp	i_200
.i_201
	call	_wyz_stop_sound
	ld	hl,(_success)
	ld	a,l
	and	a
	jp	z,i_227
	call	_game_ending
	jp	i_228
.i_227
	call	_game_over
.i_228
	call	_clear_sprites
	ld	hl,_my_inks
	push	hl
	call	_pal_set
	pop	bc
	jp	i_198
.i_199
	ret


;	SECTION	text

.i_1
	defm	" GAME OVER! "
	defb	0

;	SECTION	code



; --- Start of Static Variables ---

;	SECTION	bss

.__en_t	defs	1
.__en_x	defs	1
.__en_y	defs	1
._isr_player_on	defs	1
._gpen_cx	defs	1
._gpen_cy	defs	1
.__en_x1	defs	1
.__en_x2	defs	1
.__en_y1	defs	1
.__en_y2	defs	1
._hotspot_x	defs	1
._hotspot_y	defs	1
._half_life	defs	1
._map_pointer	defs	2
.__en_mx	defs	1
.__en_my	defs	1
._flags	defs	32
._p_facing	defs	1
._p_frame	defs	1
._pregotten	defs	1
._hit_h	defs	1
._gen_pt_alt	defs	2
._p_kill_amt	defs	1
._hit_v	defs	1
._killed_old	defs	1
._gpaux	defs	1
._active	defs	1
._p_ct_estado	defs	1
._a1	defs	2
._a2	defs	2
._a3	defs	2
._level	defs	1
._c1	defs	1
._c2	defs	1
._c3	defs	1
._c4	defs	1
._t_alt	defs	1
._hotspot_destroy	defs	1
._t1	defs	1
._t2	defs	1
._t3	defs	1
._t4	defs	1
._x0	defs	1
._y0	defs	1
._x1	defs	1
._y1	defs	1
.__n	defs	1
.__t	defs	1
.__x	defs	1
.__y	defs	1
._life_old	defs	1
._xx	defs	1
._yy	defs	1
.__gp_gen	defs	2
._gen_pt	defs	2
._t_seconds	defs	2
._ptgmx	defs	2
._ptgmy	defs	2
._enoffs	defs	1
._p_estado	defs	1
._p_killed	defs	1
._p_ammo	defs	1
._gpen_x	defs	1
._gpen_y	defs	1
._pad0	defs	1
._p_killme	defs	1
._n_pant	defs	1
._p_cont_salto	defs	1
._enspit	defs	1
._o_pant	defs	1
._p_life	defs	1
._enit	defs	1
._p_fuel	defs	1
._p_objs	defs	1
._p_gotten	defs	1
._gpcx	defs	1
._gpcy	defs	1
._gpit	defs	1
._p_keys	defs	1
._gpjt	defs	1
._playing	defs	1
._gpox	defs	1
._seed	defs	2
._p_tx	defs	1
._p_ty	defs	1
._asm_int_2	defs	2
._p_vx	defs	2
._p_vy	defs	2
._gpxx	defs	1
._gpyy	defs	1
._objs_old	defs	1
._maincounter	defs	1
._ptx1	defs	1
._ptx2	defs	1
._pty1	defs	1
._pty2	defs	1
._asm_number	defs	1
._is_joystick	defs	1
._at1	defs	1
._at2	defs	1
.__en_life	defs	1
._nocast	defs	1
._cx1	defs	1
._cx2	defs	1
._cy1	defs	1
._cy2	defs	1
._p_subframe	defs	1
.__ta	defs	1
._gpc	defs	1
._gpd	defs	1
._hit	defs	1
._gpt	defs	1
._rda	defs	1
._rdb	defs	1
._rdc	defs	1
._gpx	defs	1
._gpy	defs	1
._p_x	defs	2
._p_y	defs	2
._rdd	defs	1
._itj	defs	2
._rdn	defs	1
._keys_old	defs	1
._rdt	defs	1
._rdx	defs	1
._rdy	defs	1
._wall_h	defs	1
._enoffsmasi	defs	1
._wall_v	defs	1
._tocado	defs	1
._is_rendering	defs	1
._slevel	defs	1
._asm_int	defs	2
._p_facing_h	defs	1
.__baddies_pointer	defs	2
._p_facing_v	defs	1
._p_saltando	defs	1
._possee	defs	1
._orig_tile	defs	1
._success	defs	1
._ram_destination	defs	2
._p_disparando	defs	1
._ram_address	defs	2
;	SECTION	code



; --- Start of Scope Defns ---

	XDEF	__en_t
	XDEF	__en_x
	XDEF	__en_y
	XDEF	_isr_player_on
	XDEF	_hotspots
	XDEF	_mons_col_sc_x
	XDEF	_mons_col_sc_y
	XDEF	_draw_scr
	XDEF	_prepare_level
	XDEF	_spr_next
	defc	_spr_next	=	58944
	XDEF	_wyz_play_music
	XDEF	_trpixlutc
	LIB	cpc_PrintGphStrXY
	XDEF	_sm_invfunc
	LIB	cpc_PrintGphStrStdXY
	XDEF	_blackout_area
	LIB	cpc_PutTiles
	XDEF	_sprites
	XDEF	_gpen_cx
	XDEF	_tilanims_do
	XDEF	_gpen_cy
	XDEF	__en_x1
	XDEF	__en_x2
	XDEF	__en_y1
	XDEF	_def_keys
	XDEF	_cortina
	XDEF	__en_y2
	LIB	cpc_PrintGphStrM12X
	XDEF	_sg_submenu
	XDEF	_enems_kill
	XDEF	_enems_load
	XDEF	_en_an_base_frame
	defc	_en_an_base_frame	=	54784
	XDEF	_enems_init
	XREF	_draw_objs
	XDEF	_wyz_play_sound
	XDEF	_hotspot_x
	XDEF	_hotspot_y
	XDEF	_half_life
	XDEF	_map_pointer
	LIB	cpc_ShowScrTileMap
	XDEF	__en_mx
	XDEF	__en_my
	LIB	cpc_SetMode
	LIB	cpc_ClrScr
	LIB	cpc_SetModo
	LIB	cpc_PutMaskSpriteTileMap2b
	LIB	cpc_PutTrSpriteTileMap2b
	XDEF	_en_an_state
	defc	_en_an_state	=	54796
	XDEF	_enems_move
	LIB	cpc_SetInkGphStr
	XDEF	_flags
	XDEF	_en_an_sprid
	defc	_en_an_sprid	=	54793
	XDEF	_p_facing
	XDEF	_invalidate_tile
	XDEF	_p_frame
	XDEF	_enems_pursuers_init
	LIB	cpc_ShowTouchedTiles2
	LIB	cpc_SetTile
	XDEF	_malotes
	LIB	cpc_CollSp
	LIB	cpc_PutMaskSp4x16
	XDEF	_tilanims_add
	XDEF	_pregotten
	XDEF	_hit_h
	XDEF	_blackout
	XDEF	_map_buff
	defc	_map_buff	=	50838
	LIB	cpc_PrintGphStrStd
	XDEF	_gen_pt_alt
	XDEF	_p_kill_amt
	XDEF	_hit_v
	XDEF	_killed_old
	XDEF	_attr_mk2
	XDEF	_gpaux
	XDEF	_time_over
	XDEF	_map_attr
	defc	_map_attr	=	50688
	XDEF	_pal_set
	XDEF	_invalidate_viewport
	XDEF	_active
	XDEF	_p_ct_estado
	LIB	cpc_ShowTileMap
	XDEF	_a1
	XDEF	_a2
	XDEF	_a3
	XDEF	_level
	XDEF	_c1
	LIB	cpc_PutTile2x8
	XDEF	_c2
	XDEF	_c3
	XDEF	_c4
	XDEF	_limit
	XDEF	_t_alt
	LIB	cpc_ShowScrTileMap2
	LIB	cpc_Uncrunch
	XDEF	_hotspot_destroy
	XDEF	_cpc_UpdateNow
	XDEF	_hotspots_init
	XDEF	_t1
	XDEF	_t2
	XDEF	_t3
	XDEF	_t4
	XDEF	_x0
	XDEF	_espera_activa
	XDEF	_y0
	XDEF	_x1
	XDEF	_y1
	LIB	cpc_SpRLM1
	XDEF	_get_resource
	XDEF	__n
	XDEF	_title_screen
	XDEF	_player_kill
	XDEF	__t
	XDEF	_player_init
	XDEF	_wyz_init
	XDEF	_player_hidden
	XDEF	__x
	XDEF	__y
	LIB	cpc_PrintGphStrXY2X
	XDEF	_life_old
	LIB	cpc_SpRRM1
	XDEF	_sm_sprptr
	LIB	cpc_PrintGphStrXYM1
	XDEF	_tape_load
	LIB	cpc_PutSpriteXOR
	XDEF	_run_fire_script
	LIB	cpc_TestKey
	LIB	cpc_PutSprite
	XDEF	_player_move
	LIB	cpc_PutSpTileMap4x8
	XDEF	_xx
	XDEF	_yy
	XDEF	__gp_gen
	LIB	cpc_PutSpTileMap
	LIB	cpc_InitTileMap
	XDEF	_gen_pt
	XDEF	_tilanims_reset
	XDEF	_enems_draw_current
	XDEF	_s_marco
	LIB	cpc_PutSpTileMap8x16Px
	LIB	cpc_PutSpTileMap8x24Px
	XDEF	_addsign
	XDEF	_t_seconds
	XDEF	_tape_save
	XDEF	_sp_sw
	defc	_sp_sw	=	58880
	XDEF	_cm_two_points
	LIB	cpc_TouchTileXY
	LIB	cpc_SetTouchTileXY
	XDEF	_ptgmx
	XDEF	_ptgmy
	XDEF	_qtile
	XDEF	_mem_load
	XDEF	_sprite_17_a
	XDEF	_warp_to_level
	XDEF	_sprite_18_a
	XDEF	_spr_x
	defc	_spr_x	=	58956
	XDEF	_spr_y
	defc	_spr_y	=	58960
	XDEF	_beep_fx
	XDEF	_mem_save
	XDEF	_enoffs
	XDEF	_safe_byte
	defc	_safe_byte	=	51199
	LIB	cpc_PutSpTr
	LIB	cpc_DisableFirmware
	LIB	cpc_EnableFirmware
	XDEF	_locks_init
	XDEF	_utaux
	XDEF	_behs
	XDEF	_en_an_rawv
	defc	_en_an_rawv	=	54829
	XDEF	_draw_invalidate_coloured_tile_g
	XDEF	_p_estado
	XDEF	_bullets_fire
	XDEF	_p_killed
	XDEF	_p_ammo
	XDEF	_gpen_x
	XDEF	_gpen_y
	LIB	cpc_PrintGphStrXYM12X
	LIB	cpc_SetInk
	XDEF	_pad0
	XDEF	__tile_address
	XDEF	_p_killme
	XDEF	_n_pant
	XDEF	_def_keys_joy
	LIB	cpc_SetBorder
	LIB	cpc_RLI
	XDEF	_bullets_init
	LIB	cpc_RRI
	LIB	cpc_GetSp
	XDEF	_p_cont_salto
	XDEF	_enspit
	XDEF	_o_pant
	XDEF	_p_life
	XDEF	_enit
	LIB	cpc_SpUpdX
	LIB	cpc_SpUpdY
	LIB	cpc_PutTile4x16
	XDEF	_print_number2
	XDEF	_pause_screen
	XDEF	_p_fuel
	XDEF	_mapa
	XDEF	_main
	XDEF	_draw_coloured_tile
	XDEF	_attr
	LIB	cpc_ResetTouchedTiles
	LIB	cpc_ShowTouchedTiles
	XDEF	_p_objs
	XDEF	_p_gotten
	XDEF	_gpcx
	XDEF	_gpcy
	XDEF	_s_title
	XDEF	_gpit
	LIB	cpc_PutMaskSp2x8
	XDEF	_p_keys
	XDEF	_en_an_vx
	defc	_en_an_vx	=	54811
	XDEF	_en_an_vy
	defc	_en_an_vy	=	54817
	LIB	cpc_ScanKeyboard
	XDEF	_bullets_move
	XDEF	_player_calc_bounding_box
	XDEF	_gpjt
	LIB	cpc_SetColour
	XDEF	_playing
	XDEF	_sm_updfunc
	XDEF	_gpox
	XDEF	_rand
	XDEF	_seed
	XDEF	_p_tx
	XDEF	_p_ty
	XDEF	_print_str
	XDEF	_asm_int_2
	LIB	cpc_DeleteKeys
	XDEF	_player_deplete
	XDEF	_p_vx
	XDEF	_p_vy
	XDEF	_gpxx
	XDEF	_gpyy
	XDEF	_objs_old
	XDEF	_maincounter
	XDEF	_ptx1
	XDEF	_ptx2
	XDEF	_pty1
	XDEF	_pty2
	XDEF	_asm_number
	LIB	cpc_PutMaskSpTileMap2b
	LIB	cpc_PutTrSpTileMap2b
	LIB	cpc_PutORSpTileMap2b
	LIB	cpc_PutSpTileMap2b
	LIB	cpc_PutCpSpTileMap2b
	LIB	cpc_PutTrSp4x8TileMap2b
	LIB	cpc_UpdScr
	LIB	cpc_PutTrSp8x16TileMap2b
	LIB	cpc_PutTrSp8x24TileMap2b
	XDEF	_is_joystick
	XDEF	_break_wall
	XDEF	_update_tile
	XDEF	_cerrojos
	XDEF	_en_an_next_frame
	defc	_en_an_next_frame	=	54844
	LIB	cpc_ScrollLeft0
	XDEF	_my_inks
	XDEF	_at1
	XDEF	_at2
	LIB	cpc_AnyKeyPressed
	XDEF	_step
	XDEF	__en_life
	XDEF	_nocast
	XDEF	_draw_coloured_tile_gamearea
	XDEF	_cx1
	XDEF	_cx2
	LIB	cpc_AssignKey
	XDEF	_cy1
	XDEF	_cy2
	XDEF	_draw_decorations
	XDEF	_p_subframe
	LIB	cpc_TouchTiles
	XDEF	_en_an_dead_row
	defc	_en_an_dead_row	=	54826
	LIB	cpc_PutSpTileMap4x8Px
	XDEF	_abs
	LIB	cpc_ScrollRight0
	XDEF	__ta
	LIB	cpc_PrintGphStr
	XDEF	_game_ending
	XDEF	_s_ending
	XDEF	_bullets_update
	LIB	cpc_UnExo
	XDEF	_gpc
	XDEF	_gpd
	LIB	cpc_SetInkGphStrM1
	XDEF	_en_an_x
	defc	_en_an_x	=	54799
	XDEF	_en_an_y
	defc	_en_an_y	=	54805
	XDEF	_hit
	XDEF	_hotspots_do
	LIB	cpc_UpdateTileMap
	XDEF	_gpt
	XDEF	_rda
	XDEF	_rdb
	XDEF	_rdc
	XDEF	_gpx
	XDEF	_gpy
	XDEF	_p_x
	XDEF	_p_y
	XDEF	_cocos_mx
	defc	_cocos_mx	=	54838
	XDEF	_cocos_my
	defc	_cocos_my	=	54841
	XDEF	_rdd
	XDEF	_itj
	XDEF	_rdn
	XDEF	_keys_old
	LIB	cpc_TestKeyF
	XDEF	_rdt
	XDEF	_rdx
	XDEF	_rdy
	XDEF	_sm_cox
	XDEF	_sm_coy
	LIB	cpc_PutTrSp4x8TileMap2bPx
	LIB	cpc_PutTrSp8x16TileMap2bPx
	LIB	cpc_PutTrSp8x24TileMap2bPx
	XDEF	_process_tile
	XDEF	_tileset
	LIB	cpc_PutSpTileMap8x16
	LIB	cpc_PutSpTileMap8x24
	XDEF	_wyz_stop_sound
	LIB	cpc_ReadTile
	LIB	cpc_PutMaskSprite
	XDEF	_wall_h
	LIB	cpc_PutSpTileMapO
	XDEF	_enoffsmasi
	LIB	cpc_PutSp
	XDEF	_spacer
	LIB	cpc_UpdScrAddresses
	XDEF	_wall_v
	XDEF	_tocado
	XDEF	_en_an_alive
	defc	_en_an_alive	=	54823
	XDEF	_is_rendering
	XDEF	_cocos_x
	defc	_cocos_x	=	54832
	XDEF	_SetRAMBank
	XDEF	_cocos_y
	defc	_cocos_y	=	54835
	XDEF	_simple_coco_init
	XDEF	_slevel
	XDEF	_asm_int
	XDEF	_p_facing_h
	XDEF	__baddies_pointer
	XDEF	_p_facing_v
	LIB	cpc_TouchTileSpXY
	XDEF	_p_saltando
	LIB	cpc_SuperbufferAddress
	LIB	cpc_GetScrAddress
	XDEF	_wyz_songs
	XDEF	_possee
	LIB	cpc_PutMaskSp
	XDEF	_collide
	XDEF	_orig_tile
	XDEF	_en_an_frame
	defc	_en_an_frame	=	54787
	XDEF	_success
	LIB	cpc_RedefineKey
	XDEF	_simple_coco_shoot
	XDEF	_ram_destination
	XDEF	_en_an_count
	defc	_en_an_count	=	54790
	XDEF	_select_joyfunc
	LIB	cpc_GetTiles
	XDEF	_unpack
	XDEF	_clear_sprites
	XDEF	_spr_on
	defc	_spr_on	=	58952
	XDEF	_p_disparando
	LIB	cpc_PutSpXOR
	LIB	cpc_PrintStr
	XDEF	_distance
	XDEF	_draw_scr_background
	XDEF	_simple_coco_update
	LIB	cpc_PrintGphStr2X
	XDEF	_game_over
	LIB	cpc_PrintGphStrM1
	XDEF	_ram_address


; --- End of Scope Defns ---


; --- End of Compilation ---
