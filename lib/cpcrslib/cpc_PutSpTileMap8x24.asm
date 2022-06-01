; ******************************************************
; **       Librería de rutinas para Amstrad CPC       **
; **       Raúl Simarro,      Artaburu 2007           **
; ******************************************************

; [na_th_an] Nueva versión reescrita por Mojon Twins 
; - eliminamos la "cabecera" de los sprites.
; - la función marca por separado los tiles "anteriores" (ox,oy)
;   y los tiles "actuales" (cx, cy).
; - Intenta "podar" los casos en los que los rectángulos 
;   sean iguales.
; - Intenta "afinar" y marcar solo 2/3 de long. en vez de 3/4
;   cuando sea posible.
; - Prescinde de bucles y otros cálculos al ser un caso muy concreto

XLIB cpc_PutSpTileMap8x24

XREF tiles_tocados
XREF pantalla_juego
XREF posiciones_super_buffer
XREF tiles

LIB cpc_UpdTileTableClp

.cpc_PutSpTileMap8x24
    ex  de, hl
    ld  ixh, d
    ld  ixl, e

    ; Tendré que marcar 6, 8, 9 o 12 cuadros dependiendo de las alineaciones.

    ld e, (ix + 10) ; ox
    ld d, (ix + 11) ; oy

    ; Marcar OX, OY

    call do_update

    ld e, (ix + 8) ; cx
    ld d, (ix + 9) ; cy

    ; Copiamos (cx,cy) -> (ox,oy)

    ld (ix + 10), e
    ld (ix + 11), d

    ; Marcar CX, CY

do_update:
    ; X está en bytes. Estará alineado a rejilla si es par.
    ld a, e
    and 1
    ld iyl, a

    ; Y está en pixeles. Estará alineado si AND 7 == 0
    ld a, d
    and 7
    ld iyh, a

    ; Convertir a coordenadas de rejilla
    srl e                   ; E = X / 2
    srl d
    srl d
    srl d                   ; D = Y / 8

    push de                 ; Lo guardamos

    ; Marco el tile origen
    call cpc_UpdTileTableClp   ; Marca el tile en DE

    ; Y el de su derecha
    inc e
    call cpc_UpdTileTableClp   ; Marca el tile en DE

    ; Marcar el siguiente?
    ld a, iyl
    or a
    jr z, origin_next_row

    inc e
    call cpc_UpdTileTableClp   ; Marca el tile en DE

origin_next_row:
    pop de                  ; Recuperamos   
    inc d                   ; Y = Y + 1
    push de                 ; Guardamos

    ; Marco el primer tile
    call cpc_UpdTileTableClp   ; Marca el tile en DE

    ; Y el de su derecha
    inc e
    call cpc_UpdTileTableClp   ; Marca el tile en DE

    ; Marcar el siguiente?
    ld a, iyl
    or a
    jr z, origin_next_row2

    inc e
    call cpc_UpdTileTableClp   ; Marca el tile en DE

origin_next_row2:
    pop de                  ; Recuperamos   
    inc d                   ; Y = Y + 1
    push de                 ; Guardamos

    ; Marco el primer tile
    call cpc_UpdTileTableClp   ; Marca el tile en DE

    ; Y el de su derecha
    inc e
    call cpc_UpdTileTableClp   ; Marca el tile en DE

    ; Marcar el siguiente?
    ld a, iyl
    or a
    jr z, origin_last_row

    inc e
    call cpc_UpdTileTableClp   ; Marca el tile en DE    

origin_last_row:
    pop de                  ; Recuperamos   

    ; Marcar esta fila?
    ld a, iyh
    or a
    jr z, fin

    inc d                   ; Y = Y + 1

    ; Marco el primer tile
    call cpc_UpdTileTableClp   ; Marca el tile en DE

    ; Y el de su derecha
    inc e
    call cpc_UpdTileTableClp   ; Marca el tile en DE

    ; Marcar el siguiente?
    ld a, iyl
    or a
    jr z, fin

    inc e
    call cpc_UpdTileTableClp   ; Marca el tile en DE

fin:
    ret
