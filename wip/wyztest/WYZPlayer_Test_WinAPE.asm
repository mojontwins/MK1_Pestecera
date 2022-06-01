ORG #4000
RUN MAIN

MAIN:
    DI
    CALL    PLAYER_OFF
    LD      A,0             	;REPRODUCIR LA CANCION Num 0
    CALL    CARGA_CANCION
    EI

LOOP:
    CALL    INICIO
    HALT
    HALT
    HALT
    HALT
    HALT
    HALT
    JP      LOOP

BUFFER_DEC:
DEFB #80

TABLA_SONG:
DEFW      SONG_0 ;SONG_1

;codigo del player
READ "WYZProPlay47cCPC.ASM"

;archivo de instrumentos
READ "lala.mus.asm"
SONG_0:
INCBIN  "lala.mus" ;
