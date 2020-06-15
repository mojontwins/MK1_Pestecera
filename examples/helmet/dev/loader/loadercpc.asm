org $a300

; Ints off

	di

; Set mode 

	ld     bc, $7f00
	ld     a, $8C + 0
	out    (c), a

; all blacks

	call blackenpal

; Load screen scrc.bin

	ld     ix, $6400
	ld     de, 4801
	ld     a, $ff
	call   topoload	

; Decompress

	ld     hl, $6400
	ld     de, $c000
	call   depack

; Set palette

	call   setPal

; Load main block gamec.bin

	ld     ix, 28103
	ld     de, 13625
	ld     a, $ff
	call   topoload

; Decompress

	ld     hl, 28103
	ld     de, $400
	call   depack

; all blacks

	call blackenpal

; Run

	jp     $400

blackenpal:
	ld     de, 15	
	ld     b, $7f

loopBlackPal:

	out    (c), e    ; Select index
	ld     a, 20
	or     $40
	out    (c), a    ; Set colour
	dec    e
	jp     p, loopBlackPal

	ret

setPal:

; Set palette adapted from cpctelera

	ld     de, 15	
	ld     hl, palette
	add    hl, de
	ld     b, $7f

loopPal:

	out    (c), e    ; Select index
	ld     a, (hl)
	or     $40
	out    (c), a    ; Set colour
	dec    hl
	dec    e
	jp     p, loopPal

	ret

palette:
	defb 28, 20, 18, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11

;; Modified Topo soft loader
;;
;; Multi-colour bars in the border, aka "Spanish" style Spectrum variant loader.
;;
;; This loader uses standard Spectrum ROM timings. In fact it is essentially a CPC version of the
;; Spectrum ROM loader itself.
;;
;;
;; Loader form on cassette:
;; Pilot tone (min 256 pulses)
;; Sync pulse
;; 1 byte sync byte (on spectrum 0 for header and &ff for data)
;; n bytes of data (defined by DE register)
;; 1 byte parity checksum
;;
;; Original had the following bugs:
;; 1. bit 7 of R register had to be 1, otherwise it could change ram/rom configuration while loading
;; 2. flags were not returned, so you didn't know if the data was read incorrectly or not
;;
;; It also had extra code that was unnecessary:
;; 1. turning cassette motor on/off was complex, when in previous instructions they had turned it on anyway.
;; 2. code for changing border colour presumably on a read error. but didn't seem to be used.
;;
;;
;; Entry conditions:
;;
;; IX = start
;; DE = length (D must not be &ff)
;; A = sync byte expected
;;
;; Interrupts must be disabled
;;
;; Exit Conditions:
;; Alternative register set is corrupted. 
;;
;; carry clear - load ok
;; carry set, zero set - time up
;; carry set, zero reset - if esc pressed
;;
;; Use 2CDT to write Spectrum ROM blocks to a CDT. Note that at this time it will only write a sync byte of &ff.

topoload:

inc     d					;; reset the zero flag (D cannot hold &ff)
ex      af,af'				;; A register holds sync byte. 
dec     d					;; restore D

exx
;; we need B' to be so we can write to gate-array i/o port for colour change when loading

ld      bc,&7f00+&10		;; Gate-Array + border
out 	(c),c				;; select pen index to change while loading (&10 is border)
ld c,&54					;; set to black
out (c),c
exx

ld      bc,&f40e			;; select AY register 14 (for reading keyboard)
out     (c),c

ld      bc,&f600+&c0+&10	;; "AY write register" and enable tape motor
out     (c),c

ld      c,&10				;; "AY inactive" and enable tape motor (register is latched into AY)
out     (c),c

ld      bc,&f792			;; set PPI port A to read (so we can read keyboard data)
out     (c),c				;; this will also write 0 to port C and port A on CPC.

ld      bc,&f600+&40+&10+&8	;; tape motor enable, "AY read register", select keyboard row 8
							;; (keys on this row: z, caps lock, a, tab, q, esc, 2, 1)
							;; we are only interested in ESC
out     (c),c

;; make an initial read of cassette input
ld      a,&f5			;; PPI port B
in      a,(&00)			;; read port (tape read etc)
and     &80				;; isolate tape read data

ld      c,a
cp      a				;; set the zero flag
l8107: 
ret nz 					;; returns if esc key is pressed (was RET NZ)
l8108: 
call    l817b
jr      nc,l8107

;; the wait is meant to be almost one second
ld      hl,&415
l8110: 
djnz    l8110
dec     hl
ld      a,h
or      l
jr      nz,l8110
;; continue if only two edges are found within this allowed time period
call    l8177
jr      nc,l8107

;; only accept leader signal
l811c: 
ld      b,&9c
call    l8177
jr      nc,l8107
ld      a,&b9
cp      b
jr      nc,l8108
inc     h
jr      nz,l811c

;; on/off parts of sync pulse
l812b: 
ld      b,&c9
call    l817b
jr      nc,l8107
ld      a,b
cp      &d1
jr      nc,l812b
l8137: 
call    l817b
ret     nc

ld      h,&00			;; parity matching byte (checksum)
ld      b,&b0			;; timing constant for flag byte and data
jr      l815d

l8145: 
ex      af,af'			;; fetch the flags
jr      nz,l814d		;; jump if we are handling first byte
;; L = data byte read from cassette
;; store to RAM
ld      (ix+&00),l
jr      l8157

l814d: 
rr      c				;; keep carry in safe place
						;; NOTE: Bit 7 is cassette read previous state
						;; We need to do a right shift so that cassette read moves into bit 6,
						;; our stored carry then goes into bit 7
xor     l				;; check sync byte is as we expect
ret     nz

ld      a,c				;; restore carry flag now
rla     				;; bit 7 goes into carry restoring it, bit 6 goes back to bit 7 to restore tape input value
ld      c,a
inc     de			;; increase counter to compensate for it's decrease
jr      l8159

l8157: 
inc     ix			;; increase destination
l8159: 
dec     de			;; decrease counter
ex      af,af'		;; save the flags

ld      b,&b2		;; timing constant
l815d: 
ld      l,&01		;; marker bit (defines number of bits to read, and finally becomes value read)
l815f: 
call    l8177
ret     nc

ld      a,&c3		;; compare the length against approx 2,400T states, resetting the carry flag for a '0' and setting it for a '1'
cp      b
rl      l			;; include the new bit in the register
ld      b,&b0		;; set timing constant for next bit
jr      nc,l815f

;; L = data byte read
;; combine with checksum
ld      a,h
xor     l
ld      h,a

;; DE = count
ld      a,d
or      e
jr      nz,l8145

exx
ld c,&54						;; make border black
out (c),c
exx

ld      bc,&f782				;; set PPI port A for output
out     (c),c
ld      bc,&f600				;; tape motor off, "AY inactive"
out     (c),c

;; H = checksum byte
;; H = 0 means checksum ok
ld      a,h
cp      &01
;; return with carry flag set if the result is good
;; carry clear otherwise
ret     


;;------------------------------------------------------------
l8177: 
call    l817b			;; in effect call ld-edge-1 twice returning in between if there is an error
ret     nc

;; wait 358T states before entering sampling loop
l817b: 
ld      a,&16			;; [2]
l817d: 
dec     a				;; [1]
jr      nz,l817d		;; ([3]+[1])*&15+[2]

and     a
l8181: 
inc     b				;; count each pass
ret     z				;; return carry reset and zero set if time up.

;; read keyboard
ld      a,&f4			;; PPI port A 
in      a,(00h)			;; read port and read keyboard through AY register 14
and     &04				;; isolate state of bit 2 (ESC key)
						;; bit will be 0 if key is pressed
xor     &04				;; has key been pressed? 
ret     nz				;; quit (carry reset, zero reset)

ld      a,&f5			;; PPI port B
in      a,(&00)			;; read port (tape read etc)
xor     c
and     &80				;; isolate tape read
jr      z,l8181
ld      a,c				;; effectively toggle bit 7 of C
cpl     				;; which is the tape read state we want to see next
ld      c,a

exx     				;; swap to alternative register set so that we can change colour
;; this sets colour and gives us the multi colour border
ld 		a,r				;; get R register
and &1f					;; ensure it is in range of colour value
or &40					;; bit 7 = 0, bit 6 = 1
out (c),a				;; write colour value
nop						;; this is to ensure the number of cycles is the same
						;; compared to the replaced instructions
						;; (timings from toposoft loader)
exx     
scf     
ret     

; aPPack decompressor
; original source by dwedit
; very slightly adapted by utopian
; optimized by Metalbrain

;hl = source
;de = dest

depack:		ld	ixl,128
apbranch1:	ldi
aploop0:	ld	ixh,1		;LWM = 0
aploop:		call 	ap_getbit
		jr 	nc,apbranch1
		call 	ap_getbit
		jr 	nc,apbranch2
		ld 	b,0
		call 	ap_getbit
		jr 	nc,apbranch3
		ld	c,16		;get an offset
apget4bits:	call 	ap_getbit
		rl 	c
		jr	nc,apget4bits
		jr 	nz,apbranch4
		ld 	a,b
apwritebyte:	ld 	(de),a		;write a 0
		inc 	de
		jr	aploop0
apbranch4:	and	a
		ex 	de,hl 		;write a previous byte (1-15 away from dest)
		sbc 	hl,bc
		ld 	a,(hl)
		add	hl,bc
		ex 	de,hl
		jr	apwritebyte
apbranch3:	ld 	c,(hl)		;use 7 bit offset, length = 2 or 3
		inc 	hl
		rr 	c
		ret 	z		;if a zero is encountered here, it is EOF
		ld	a,2
		adc	a,b
		push 	hl
		ld	iyh,b
		ld	iyl,c
		ld 	h,d
		ld 	l,e
		sbc 	hl,bc
		ld 	c,a
		jr	ap_finishup2
apbranch2:	call 	ap_getgamma	;use a gamma code * 256 for offset, another gamma code for length
		dec 	c
		ld	a,c
		sub	ixh
		jr 	z,ap_r0_gamma		;if gamma code is 2, use old r0 offset,
		dec 	a
		;do I even need this code?
		;bc=bc*256+(hl), lazy 16bit way
		ld 	b,a
		ld 	c,(hl)
		inc 	hl
		ld	iyh,b
		ld	iyl,c

		push 	bc
		
		call 	ap_getgamma

		ex 	(sp),hl		;bc = len, hl=offs
		push 	de
		ex 	de,hl

		ld	a,4
		cp	d
		jr 	nc,apskip2
		inc 	bc
		or	a
apskip2:	ld 	hl,127
		sbc 	hl,de
		jr 	c,apskip3
		inc 	bc
		inc 	bc
apskip3:		pop 	hl		;bc = len, de = offs, hl=junk
		push 	hl
		or 	a
ap_finishup:	sbc 	hl,de
		pop 	de		;hl=dest-offs, bc=len, de = dest
ap_finishup2:	ldir
		pop 	hl
		ld	ixh,b
		jr 	aploop

ap_r0_gamma:	call 	ap_getgamma		;and a new gamma code for length
		push 	hl
		push 	de
		ex	de,hl

		ld	d,iyh
		ld	e,iyl
		jr 	ap_finishup


ap_getbit:	ld	a,ixl
		add	a,a
		ld	ixl,a
		ret	nz
		ld	a,(hl)
		inc	hl
		rla
		ld	ixl,a
		ret

ap_getgamma:	ld 	bc,1
ap_getgammaloop:	call 	ap_getbit
		rl 	c
		rl 	b
		call 	ap_getbit
		jr 	c,ap_getgammaloop
		ret
