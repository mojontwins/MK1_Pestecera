@echo off

if [%1]==[help] goto :help

set game=helmet
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
..\..\..\src\utils\mapcnvbin.exe ..\map\mapa0.map ..\bin\mapa0.bin 1 24 15 10 15 fixmappy packed > nul
..\..\..\src\utils\mapcnvbin.exe ..\map\mapa1.map ..\bin\mapa1.bin 1 24 15 10 15 fixmappy packed > nul
..\..\..\src\utils\mapcnvbin.exe ..\map\mapa2.map ..\bin\mapa2.bin 1 24 15 10 15 fixmappy packed > nul
..\..\..\src\utils\apultra.exe ..\bin\mapa0.bin ..\bin\mapa0c.bin
..\..\..\src\utils\apultra.exe ..\bin\mapa1.bin ..\bin\mapa1c.bin
..\..\..\src\utils\apultra.exe ..\bin\mapa2.bin ..\bin\mapa2c.bin

echo Convirtiendo enemigos/hotspots
..\..\..\src\utils\ene2bin_mk1.exe ..\enems\enems0.ene ..\bin\enems_hotspots0.bin 2
..\..\..\src\utils\ene2bin_mk1.exe ..\enems\enems1.ene ..\bin\enems_hotspots1.bin 2
..\..\..\src\utils\ene2bin_mk1.exe ..\enems\enems2.ene ..\bin\enems_hotspots2.bin 2
..\..\..\src\utils\ene2bin_mk1.exe ..\enems\enems3.ene ..\bin\enems_hotspots3.bin 2
..\..\..\src\utils\ene2bin_mk1.exe ..\enems\enems4.ene ..\bin\enems_hotspots4.bin 2
..\..\..\src\utils\apultra.exe ..\bin\enems_hotspots0.bin ..\bin\enems_hotspots0c.bin
..\..\..\src\utils\apultra.exe ..\bin\enems_hotspots1.bin ..\bin\enems_hotspots1c.bin
..\..\..\src\utils\apultra.exe ..\bin\enems_hotspots2.bin ..\bin\enems_hotspots2c.bin
..\..\..\src\utils\apultra.exe ..\bin\enems_hotspots3.bin ..\bin\enems_hotspots3c.bin
..\..\..\src\utils\apultra.exe ..\bin\enems_hotspots4.bin ..\bin\enems_hotspots4c.bin

echo Convirtiendo behs
..\..\..\src\utils\behs2bin.exe ..\gfx\behs0_1.txt ..\bin\behs0_1.bin >nul
..\..\..\src\utils\apultra.exe ..\bin\behs0_1.bin ..\bin\behs0_1c.bin >nul


if [%1]==[nogfx] goto :compile

echo Importando GFX
..\..\..\src\utils\mkts_om.exe platform=cpc cpcmode=%cpc_gfx_mode% pal=..\gfx\pal.png mode=chars greyordered in=..\gfx\font.png out=..\bin\font.bin silent > nul
..\..\..\src\utils\mkts_om.exe platform=cpc cpcmode=%cpc_gfx_mode% pal=..\gfx\pal.png mode=strait2x2 greyordered in=..\gfx\work.png out=..\bin\work.bin silent > nul

..\..\..\src\utils\mkts_om.exe platform=cpc cpcmode=%cpc_gfx_mode% pal=..\gfx\pal.png mode=sprites in=..\gfx\sprites.png out=..\bin\sprites.bin max=18 mappings=assets\spriteset_mappings.h pixelperfectm0  silent > nul

..\..\..\src\utils\mkts_om.exe platform=cpc cpcmode=%cpc_gfx_mode% pal=..\gfx\pal.png mode=sprites in=..\gfx\sprites_extra.png out=..\bin\sprites_extra.bin silent > nul
..\..\..\src\utils\mkts_om.exe platform=cpc cpcmode=%cpc_gfx_mode% pal=..\gfx\pal.png mode=sprites in=..\gfx\sprites_bullet.png out=..\bin\sprites_bullet.bin metasize=1,1 silent > nul

..\..\..\src\utils\png2scr.exe ..\gfx\title.png ..\gfx\title.scr > nul

..\..\..\src\utils\mkts_om.exe platform=cpc cpcmode=%cpc_gfx_mode% pal=..\gfx\pal.png mode=superbuffer in=..\gfx\marco.png out=..\bin\marco.bin silent > nul
..\..\..\src\utils\mkts_om.exe platform=cpc cpcmode=%cpc_gfx_mode% pal=..\gfx\pal.png mode=superbuffer in=..\gfx\ending.png out=..\bin\ending.bin silent > nul
..\..\..\src\utils\mkts_om.exe platform=cpc cpcmode=%cpc_gfx_mode% pal=..\gfx\pal.png mode=superbuffer in=..\gfx\title.png out=..\bin\title.bin silent > nul
..\..\..\src\utils\apultra.exe ..\bin\title.bin ..\bin\titlec.bin > nul
..\..\..\src\utils\apultra.exe ..\bin\marco.bin ..\bin\marcoc.bin > nul
..\..\..\src\utils\apultra.exe ..\bin\ending.bin ..\bin\endingc.bin > nul

..\..\..\src\utils\mkts_om.exe platform=cpc mode=pals in=..\gfx\pal.png prefix=my_inks out=assets\pal.h silent > nul
..\..\..\src\utils\mkts_om.exe platform=cpc mode=pals in=..\gfx\pal_b.png prefix=my_inks_2 out=assets\pal_b.h silent > nul
..\..\..\src\utils\mkts_om.exe platform=cpc mode=pals in=..\gfx\pal_c.png prefix=my_inks_3 out=assets\pal_c.h silent > nul
..\..\..\src\utils\mkts_om.exe platform=cpc mode=pals in=..\gfx\pal_d.png prefix=my_inks_4 out=assets\pal_d.h silent > nul

if [%1]==[justassets] goto :end

:compile
echo Generating LUTs
..\..\..\src\utils\pasmo.exe assets\cpc_TrPixLutM%cpc_gfx_mode%.asm assets\trpixlut.bin
..\..\..\src\utils\apultra.exe assets\trpixlut.bin assets\trpixlutc.bin
..\..\..\src\utils\wyzTrackerParser.exe ..\mus\instrumentos.asm assets\instrumentos.h
echo Compilando guego
zcc +cpc -m -vn -O3 -unsigned -crt0=crt.asm -zorg=1024 -lcpcrslib_fg -DCPC_GFX_MODE=%cpc_gfx_mode% -o %game%.bin tilemap_conf.asm mk1.c > nul
rem zcc +cpc -a -vn -O3 -unsigned -zorg=1024 -lcpcrslib -DCPC_GFX_MODE=%cpc_gfx_mode% -o %game%.asm tilemap_conf.asm mk1.c > nul
..\..\..\src\utils\printsize.exe %game%.bin
..\..\..\src\utils\printsize.exe scripts.bin

echo Construyendo Snapshot %game%.sna
del %game%.sna > nul 2> nul
..\..\..\src\utils\cpctbin2sna.exe %game%.bin 0x400 -pc 0x400 -o %game%.sna

if [%2]==[andtape] goto :tape
if [%1]==[justcompile] goto :end

:clean
:tape
echo Construyendo cinta
..\..\..\src\utils\mkts_om.exe platform=cpc cpcmode=%cpc_gfx_mode% pal=..\gfx\pal_loading.png mode=scr in=..\gfx\loading.png out=..\bin\loading.bin silent > nul
del ..\bin\loading.c.bin >nul 2>nul
..\..\..\src\utils\zx7.exe ..\bin\loading.bin ..\bin\loading.c.bin > nul
..\..\..\src\utils\mkts_om.exe platform=cpc cpcmode=1 pal=..\gfx\pal_preloading.png mode=scr in=..\gfx\preloading.png out=..\bin\preloading.bin silent > nul
del ..\bin\preloading.c.bin >nul 2>nul
..\..\..\src\utils\zx7.exe ..\bin\preloading.bin ..\bin\preloading.c.bin > nul
del ..\bin\%game%.c.bin >nul 2>nul
..\..\..\src\utils\zx7.exe %game%.bin ..\bin\%game%.c.bin > nul

..\..\..\src\utils\imanol.exe in=loader\loadercpc.asm-orig out=loader\loadercpc.asm ^
	pscrc_size=?..\bin\preloading.c.bin ^
	scrc_size=?..\bin\loading.c.bin ^
	mainbin_size=?..\bin\%game%.c.bin ^
	preloading_palette=!..\gfx\pal_preloading.png ^
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
..\..\..\src\utils\cpc2cdt.exe -r PSCR -m raw1full -rl 740 -p 2000 ..\bin\preloading.c.bin %game%.cdt
..\..\..\src\utils\cpc2cdt.exe -r SCR -m raw1full -rl 740 -p 2000 ..\bin\loading.c.bin %game%.cdt
..\..\..\src\utils\cpc2cdt.exe -r MAIN -m raw1full -rl 740 -p 2000 ..\bin\%game%.c.bin %game%.cdt

goto :end 

:help
echo "compile.bat help|justcompile|clean|justscripts|justassets|nogfx"

:end
echo Hecho!
