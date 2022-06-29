## New stuff

Voy a hacer una historia para poder imprimir los sprites al pixel en modo 0. Originalmente había pensando en una LUT que invirtiera los pixels AB de un byte y los pusiera BA y hacer esto:

bytes: AB CD EF GH

1. AB -> BA, byte 1 = BA And 0x0F                    = 0A
2. CD -> DC, byte 2 = (BA And 0xF0) OR (DC And 0x0F) = BC
3. EF -> FE, byte 3 = (DC And 0xF0) OR (FE And 0x0F) = DE
4. GH -> HG, byte 4 = (FE And 0xF0) OR (HG And 0x0F) = FG
5.         , byte 5 = (HG And 0xF0)                  = H0

Y además hacer que la rutina que invalida celdas siempre invalide 3 a menos que x&3 = 0.

El tema es que he visto esta macro en CPCTelera y me da que esto va a ser más rápido que mirar en una LUT:

```s
    .macro cpctm_reverse_mode_0_pixels_of_A  TReg
       rlca            ;; [1] | Rotate A twice to the left to get bits ordered...
       rlca            ;; [1] | ... in the way we need for mixing, A = [23456701]
      
       ;; Mix TReg with A to get pixels reversed by reordering bits
       xor TReg        ;; [1] | TReg = [01234567]
       and #0b01010101 ;; [2] |    A = [23456701]
       xor TReg        ;; [1] |   A2 = [03254761]
       rrca            ;; [1] Rotate right to get pixels reversed A = [10325476]
    .endm
```

Sobre todo porque mirar en la LUT es esto, que gasta registro de 16 bits (DE):

```s
       (call ...)       ;; [5]
    .cpc_TblLookup
       add a,e          ;; [1]
       ld e,a           ;; [1]
       jr nc, noinc     ;; [2-3]
       inc d            ;; [1]

    .noinc
       ld a,(de)        ;; [2]
       ret              ;; [3]
```

Así que lo haré con la macro de forma inline y añadiré (otro) crédito más para el amigo Fran Gallego.

Para hacer las pruebas por el momento picaré solo los sprites 8x16 (4 bytes de ancho) `cpc_PutTrSp8x16TileMap2b`.

El problema que veo es que esta rutina está recibiendo coordenadas de byte (64 de ancho) y no de pixels (128). Esto tendré que cambiarlo en el código de MK1.

Voy a duplicar la función en `cpc_PutTrSp8x16TileMap2bPx`

## Primera prueba

Parece que medio funciona pero algo tengo que estar haciendo mal porque aparentemente estoy rotando al revés. Veamos:

* Si X es PAR, estamos alineados a byte, por lo que usamos la rutina de siempre.
* Si X es IMPAR, NO estamos alineados a byte. Hay que pintar en X/0 pero rotando.

Creo que está desplazando un byte el origen en los impares que no debería. O algo así. Reviso el setup de la rutina.

## Palos patrás

Soy tonto del culo. Los pixels no están ordenados como debieran así que la mezcla no es tan fácil :-D Más bien así... El byte representa los pixels AB así ABABABAB. Para quedarme con A es AND $AA, y para quedarme con B es AND $55.

Por tanto:

bytes: AB CD EF GH

1. AB -> BA, byte 1 = BA And 0x55                    = 0A
2. CD -> DC, byte 2 = (BA And 0xAA) OR (DC And 0x55) = BC
3. EF -> FE, byte 3 = (DC And 0xAA) OR (FE And 0x55) = DE
4. GH -> HG, byte 4 = (FE And 0xAA) OR (HG And 0x55) = FG
5.         , byte 5 = (HG And 0xAA)                  = H0

ET VOIE LA!

Ahora tengo que hacer las otras versiones de las rutinas para 4x8 y 8x23

;;;

# MODE 1 FTW!!

```
    ;; Rotate nibbles right x1

                    ; Want
                    ; A = 47650321

                    ; A = 76543210
    rrca            ; A = 07654321
    ld  c, a        ; A = 07654321 C = 07654321
    rrca
    rrca
    rrca            ;     x   x
    rrca            ; A = 43210765
    xor c           ; A = 4^7 3^6 2^5 1^4 0^3 7^2 6^1 5^0
    and $88         ; A = 4^7 0 0 0 0^3 0 0 0
    xor c           ; A = 47650321!


    ;; Rotate nibbles right x2

                    ; Want
                    ; A = 54761032

                    ; A = 76543210
    rrca 
    rrca            ; A = 10765432     xx__xx__
    ld  c, a        ; A = 10765432 C = 10765432
    rrca
    rrca
    rrca            ;     xx  xx
    rrca            ; A = 54321076
    xor c           ; A = 5^1 4^0 3^7 2^6 1^5 0^4 7^3 6^2
    and $CC         ; A = 5^1 4^0 0 0 1^5 0^4 0 0
    xor c           ; A = 54761032

    ;; Rotate nibbles right x3

                    ; Want
                    ; A = 65472103

                    ; A = 76543210
    rlca            ; A = 65432107     ___x___x
    ld  c, a        ; A = 65432107 C = 65432107
    rlca
    rlca
    rlca            ;        x   x   
    rlca            ; A = 21076543
    xor c           ; A = 2^6 1^5 0^4 7^3 6^2 5^1 4^0 3^7
    and $11         ; A = 0 0 0 7^3 0 0 0 3^7
    xor c           ; A = 65472103
    
```
