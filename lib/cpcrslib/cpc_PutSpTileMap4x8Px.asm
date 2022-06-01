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
; - Intenta "afinar" y marcar solo 1 de long en vez de 2
;   cuando sea posible.
; - Prescinde de bucles y otros cálculos al ser un caso muy concreto
; [na_th_an] Esta rutina funciona con X en pixels modo 0 (0-127) 

XLIB cpc_PutSpTileMap4x8Px

XREF tiles_tocados
XREF pantalla_juego
XREF posiciones_super_buffer
XREF tiles

LIB cpc_UpdTileTableClp

.cpc_PutSpTileMap4x8Px
    ex  de, hl
    ld  ixh, d
    ld  ixl, e

    ; Tendré que marcar 1, 2 o 4 cuadros dependiendo de las alineaciones.

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
    ; X está en bytes. Estará alineado a rejilla si & 3 == 0.
    ld a, e
    and 3
    ld iyl, a

    ; Y está en pixeles. Estará alineado si AND 7 == 0
    ld a, d
    and 7
    ld iyh, a

    ; Convertir a coordenadas de rejilla
    srl e
    srl e                   ; E = X / 4
    srl d
    srl d
    srl d                   ; D = Y / 8

    ; Marco el tile origen
    call cpc_UpdTileTableClp   ; Marca el tile en DE

    ; Marcar el tile de la derecha?
    ld a, iyl
    or a
    jr z, origin_next_row

    push de
    inc e
    call cpc_UpdTileTableClp   ; Marca el tile en DE
    pop de

origin_next_row:
    ; Marcar fila de abajo?
    ld a, iyh
    or a
    jr z, fin

    inc d
    call cpc_UpdTileTableClp   ; Marca el tile en DE

    ; Marcar el tile de la derecha?
    ld a, iyl
    or a
    jr z, fin

    inc e
    call cpc_UpdTileTableClp   ; Marca el tile en DE

fin:
    ret
