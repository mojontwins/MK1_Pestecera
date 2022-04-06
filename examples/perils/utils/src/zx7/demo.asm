; -----------------------------------------------------------------------------
; ZX7 demo by Einar Saukas
; -----------------------------------------------------------------------------

DZX7_STANDARD   EQU  65000              ; "Standard" routine compiled at this address
DZX7_TURBO      EQU  65100              ; "Turbo" routine compiled at this address
DZX7_MEGA       EQU  65200              ; "Mega" routine compiled at this address

; -----------------------------------------------------------------------------
        org     50000

        di
start:
        ld      hl, 51200               ; source address (first compressed image)
        ld      de, 16384               ; target address (screen area)
loop:
        ld      a, $f7
        in      a, ($fe)                ; read keys 1-5
        or      $e0
key1:
        cp      $fe                     ; pressed key 1?
        jr      nz, key2
        call    DZX7_STANDARD           ; decompress screen using Standard version
        jr      next
key2:
        cp      $fd                     ; pressed key 2?
        jr      nz, key3
        call    DZX7_TURBO              ; decompress screen using Turbo version
        jr      next
key3:
        cp      $fb                     ; pressed key 3?
        jr      nz, loop
        call    DZX7_MEGA               ; decompress screen using Mega version
next:
        ld      hl, start+2             ; update source address to next image
        ld      a, (hl)
        add     a, $0c
        cp      $ec
        jr      c, skip
        ld      a, $c8
skip:
        ld      (hl), a
        jr      start                   ; repeat ad infinitum

; -----------------------------------------------------------------------------
