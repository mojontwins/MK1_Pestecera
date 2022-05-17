; Mojon Twins Minimal CRTC0.

        MODULE  cpc_crt0
        INCLUDE "zcc_opt.def"
        XREF    _main           ; main() is always external to crt0 code
        org     CRT_ORG_CODE
start:
        ld sp,$ffff
        jp    _main
