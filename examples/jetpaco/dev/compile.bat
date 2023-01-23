@echo off

if [%1]==[help] goto :help

set game=jet_paco
set cpc_gfx_mode=0

if [%1]==[justcompile] goto :compile
if [%1]==[clean] goto :clean

cd ..\script
if not exist %game%.spt goto :noscript
echo Compilando script
..\..\..\src\utils\msc3_mk1.exe %game%.spt 30 > nul
copy msc.h ..\dev\my > nul
copy msc-config.h ..\dev\my > nul
copy scripts.bin ..\dev\ > nul
:noscript
cd ..\dev

if [%1]==[justscripts] goto :compile

echo Convirtiendo mapa
..\..\..\src\utils\mapcnv.exe ..\map\mapa.map assets\mapa.h 7 15 15 10 99 packed > nul

echo Convirtiendo enemigos/hotspots
..\..\..\src\utils\ene2h.exe ..\enems\enems.ene assets\enems.h

if [%1]==[nogfx] goto :compile

echo Importando GFX
..\..\..\src\utils\mkts_om.exe platform=cpc cpcmode=%cpc_gfx_mode% pal=..\gfx\pal.png mode=chars greyordered in=..\gfx\font.png out=..\bin\font.bin silent > nul
..\..\..\src\utils\mkts_om.exe platform=cpc cpcmode=%cpc_gfx_mode% pal=..\gfx\pal.png mode=strait2x2 greyordered in=..\gfx\work.png out=..\bin\work.bin silent > nul

..\..\..\src\utils\mkts_om.exe platform=cpc cpcmode=%cpc_gfx_mode% pal=..\gfx\pal.png mode=sprites in=..\gfx\sprites.png out=..\bin\sprites.bin mappings=assets\spriteset_mappings.h pixelperfectm0 silent > nul

..\..\..\src\utils\mkts_om.exe platform=cpc cpcmode=%cpc_gfx_mode% pal=..\gfx\pal.png mode=sprites in=..\gfx\sprites_extra.png out=..\bin\sprites_extra.bin silent > nul
..\..\..\src\utils\mkts_om.exe platform=cpc cpcmode=%cpc_gfx_mode% pal=..\gfx\pal.png mode=sprites in=..\gfx\sprites_bullet.png out=..\bin\sprites_bullet.bin metasize=1,1 silent > nul
..\..\..\src\utils\mkts_om.exe platform=cpc cpcmode=%cpc_gfx_mode% pal=..\gfx\pal.png mode=sprites in=..\gfx\sprites_humo.png out=..\bin\sprites_humo.bin metasize=1,1 silent > nul

..\..\..\src\utils\mkts_om.exe platform=cpc cpcmode=%cpc_gfx_mode% pal=..\gfx\pal.png mode=superbuffer in=..\gfx\marco.png out=..\bin\marco.bin silent > nul
..\..\..\src\utils\mkts_om.exe platform=cpc cpcmode=%cpc_gfx_mode% pal=..\gfx\pal_ending.png mode=superbuffer in=..\gfx\ending.png out=..\bin\ending.bin silent > nul
..\..\..\src\utils\mkts_om.exe platform=cpc cpcmode=%cpc_gfx_mode% pal=..\gfx\pal.png mode=superbuffer in=..\gfx\title.png out=..\bin\title.bin silent > nul
..\..\..\src\utils\mkts_om.exe platform=cpc cpcmode=%cpc_gfx_mode% pal=..\gfx\pal.png mode=superbuffer in=..\gfx\cuts.png out=..\bin\cuts.bin silent > nul

del ..\bin\*c.bin >nul
..\..\..\src\utils\zx0.exe ..\bin\title.bin ..\bin\titlec.bin > nul
..\..\..\src\utils\zx0.exe ..\bin\marco.bin ..\bin\marcoc.bin > nul
..\..\..\src\utils\zx0.exe ..\bin\ending.bin ..\bin\endingc.bin > nul
..\..\..\src\utils\zx0.exe ..\bin\cuts.bin ..\bin\cutsc.bin > nul

..\..\..\src\utils\mkts_om.exe platform=cpc mode=pals in=..\gfx\pal.png prefix=my_inks out=assets\pal.h silent > nul
..\..\..\src\utils\mkts_om.exe platform=cpc mode=pals in=..\gfx\pal1.png prefix=my_inks1 out=assets\pal1.h silent > nul
..\..\..\src\utils\mkts_om.exe platform=cpc mode=pals in=..\gfx\pal2.png prefix=my_inks2 out=assets\pal2.h silent > nul
..\..\..\src\utils\mkts_om.exe platform=cpc mode=pals in=..\gfx\pal_ending.png prefix=my_inks_ending out=assets\pal_ending.h silent > nul

if [%1]==[justassets] goto :end

:compile
echo Generating LUTs
..\..\..\src\utils\pasmo.exe assets\cpc_TrPixLutM%cpc_gfx_mode%.asm assets\trpixlut.bin
del assets\trpixlutc.bin
..\..\..\src\utils\zx0.exe assets\trpixlut.bin assets\trpixlutc.bin > nul
..\..\..\src\utils\wyzTrackerParser.exe ..\mus\instrumentos.asm my\wyz\instrumentos.h
echo Compilando guego
del %game%.bin > nul
zcc +cpc -m -vn -O3 -unsigned -crt0=crt.asm  -zorg=1024 -lcpcrslib_fg -DCPC_GFX_MODE=%cpc_gfx_mode% -o %game%.bin tilemap_conf.asm mk1.c > nul
..\..\..\src\utils\printsize.exe %game%.bin
..\..\..\src\utils\printsize.exe scripts.bin

echo Construyendo Snapshot %game%.sna
del %game%.sna > nul
..\..\..\src\utils\cpctbin2sna.exe %game%.bin 0x400 -pc 0x400 -o %game%.sna


if [%2]==[andtape] goto :tape
if [%1]==[justcompile] goto :end

:clean
:tape
echo Construyendo cinta
..\..\..\src\utils\mkts_om.exe platform=cpc cpcmode=%cpc_gfx_mode% pal=..\gfx\pal_loading.png mode=scr in=..\gfx\loading.png out=..\bin\loading.bin silent > nul
del ..\bin\loading.c.bin >nul 2>nul
..\..\..\src\utils\zx7.exe ..\bin\loading.bin ..\bin\loading.c.bin > nul
del ..\bin\%game%.c.bin >nul 2>nul
..\..\..\src\utils\zx7.exe %game%.bin ..\bin\%game%.c.bin > nul

..\..\..\src\utils\imanol.exe in=loader\loadercpc.asm-orig out=loader\loadercpc.asm ^
	scrc_size=?..\bin\loading.c.bin ^
	mainbin_size=?..\bin\%game%.c.bin ^
	loading_palette=!..\gfx\pal_loading.png ^
	loader_mode=%cpc_gfx_mode% > nul
..\..\..\src\utils\pasmo.exe loader\loadercpc.asm ..\bin\loader.bin  > nul

..\..\..\src\utils\imanol.exe in=loader\preloadercpc.asm-orig out=loader\preloadercpc.asm ^
	loader_size=?..\bin\loader.bin ^
	loader_mode=%cpc_gfx_mode% > nul
..\..\..\src\utils\pasmo.exe loader\preloadercpc.asm ..\bin\preloader.bin  > nul

del %game%.cdt > nul
..\..\..\src\utils\cpc2cdt.exe -r %game% -m cpc -l 1024 -x 1024 -p 2000 ..\bin\preloader.bin %game%.cdt
..\..\..\src\utils\cpc2cdt.exe -r LOADER -m raw1full -rl 740 -p 2000 ..\bin\loader.bin %game%.cdt
..\..\..\src\utils\cpc2cdt.exe -r SCR -m raw1full -rl 740 -p 2000 ..\bin\loading.c.bin %game%.cdt
..\..\..\src\utils\cpc2cdt.exe -r MAIN -m raw1full -rl 740 -p 2000 ..\bin\%game%.c.bin %game%.cdt

goto :end 

:help
echo "compile.bat help|justcompile|clean|justscripts|justassets|nogfx"

:end
echo Hecho!
