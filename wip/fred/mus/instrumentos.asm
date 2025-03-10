
; Tabla de instrumentos
TABLA_PAUTAS: DW PAUTA_0,PAUTA_1,PAUTA_2,PAUTA_3,PAUTA_4,PAUTA_5,0,PAUTA_7,PAUTA_8,PAUTA_9,PAUTA_10,PAUTA_11,PAUTA_12,PAUTA_13,PAUTA_14,PAUTA_15,PAUTA_16

; Tabla de efectos
TABLA_SONIDOS: DW 0,0,0,0,0,0,0,0,0,SONIDO9

;Pautas (instrumentos)
;Instrumento 'Piano'
PAUTA_0:	DB	6,0,5,0,4,0,3,0,129
;Instrumento 'Piano Reverb'
PAUTA_1:	DB	10,0,11,0,10,0,9,0,8,0,8,0,8,0,8,0,8,0,8,0,7,0,7,0,7,0,7,0,136
;Instrumento 'Fade In FX'
PAUTA_2:	DB	2,0,3,0,4,8,4,-1,5,-4,5,20,5,-24,4,4,132
;Instrumento 'Guitar 1'
PAUTA_3:	DB	13,0,13,0,11,0,11,0,9,0,8,1,8,1,8,-1,7,-1,7,0,7,0,134
;Instrumento 'Guitar 2'
PAUTA_4:	DB	10,0,10,0,9,0,8,0,6,0,5,1,5,0,5,0,5,-1,5,0,5,0,134
;Instrumento 'Eco guitar'
PAUTA_5:	DB	7,0,7,0,7,0,6,0,6,0,6,0,6,0,6,0,5,0,5,0,5,0,5,0,5,0,4,0,4,0,4,0,4,0,3,0,0,0,129
;Instrumento 'Solo Guitar'
PAUTA_7:	DB	76,0,11,0,11,0,11,0,10,0,9,1,9,0,9,-1,9,0,9,0,9,-1,9,0,9,1,9,0,9,0,138
;Instrumento 'Eco Solo Guitar'
PAUTA_8:	DB	70,0,6,0,6,0,5,0,5,0,5,0,5,0,5,0,4,0,4,0,4,0,4,0,4,0,4,0,3,0,3,0,3,0,3,0,3,0,3,0,2,0,2,0,2,0,1,0,129
;Instrumento 'Slap Bass'
PAUTA_9:	DB	47,2,14,4,13,-4,12,3,11,-5,10,0,129
;Instrumento 'Robo'
PAUTA_10:	DB	13,-1,13,-1,29,11,28,3,28,6,28,7,27,3,27,4,27,15,26,11,26,8,26,6,9,0,25,5,25,7,131
;Instrumento 'Chip'
PAUTA_11:	DB	76,0,13,0,46,0,13,0,12,0,11,0,129
;Instrumento 'Clipclop'
PAUTA_12:	DB	12,0,11,0,10,0,9,0,9,0,9,0,9,0,9,0,8,0,8,0,8,0,8,0,8,0,138
;Instrumento 'Eco'
PAUTA_13:	DB	9,0,8,0,7,0,6,0,129
;Instrumento 'Harmonica'
PAUTA_14:	DB	44,0,13,0,14,0,13,0,12,0,11,0,129
;Instrumento 'Onda'
PAUTA_15:	DB	71,0,7,0,8,0,9,0,8,0,7,0,6,0,3,0,129
;Instrumento 'Teeth'
PAUTA_16:	DB	73,0,10,0,42,0,9,0,8,0,7,0,7,0,7,0,7,0,6,0,6,0,6,0,6,0,136

;Efectos
;Efecto 'Mute'
SONIDO9:	DB	0,0,0,255

;Frecuencias para las notas
DATOS_NOTAS: DW 0,0
DW 964,910,859,811,766,722,682,644,608,573
DW 541,511,482,455,430,405,383,361,341,322
DW 304,287,271,255,241,228,215,203,191,180
DW 170,161,152,143,135,128,121,114,107,101
DW 96,90,85,81,76,72,68,64,60,57
DW 54,51,48,45,43,40,38,36,34,32
