
XLIB cpc_TblLookup

; enter:
;    de = table base
;     a = table byte index
;
; exit:
;     a = table entry

.cpc_TblLookup
   add a,e
   ld  e,a
   jr  nc, noinc
   inc d

.noinc
   ld  a, (de)
   ret
