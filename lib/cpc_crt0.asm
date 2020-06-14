;       CRT0 for the Amstrad CPC family
;
;       Stefano Bodrato 8/6/2000
;
;       $Id: cpc_crt0.asm,v 1.17 2012/03/05 20:44:41 stefano Exp $
;

        MODULE  cpc_crt0
        INCLUDE "zcc_opt.def"
        XREF    _main           ; main() is always external to crt0 code
        org     myzorg
start:
        ld sp,$ffff
        jp    _main
