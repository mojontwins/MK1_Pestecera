@echo off

set base=0x8400
set basesfx=0x8E00

if [%1]==[justassemble] goto :assemble

echo Convirtiendo . . .
..\utils\AKSToBIN.exe -a %base% 00_title.aks 00_title.bin 
..\utils\AKSToBIN.exe -a %base% 01_ingame.aks 01_ingame.bin 
..\utils\AKSToBIN.exe -s -a %basesfx% sfx.aks sfx.bin

echo Comprimiendo . . .
..\utils\apack.exe 00_title.bin 00_title_c.bin > nul
..\utils\apack.exe 01_ingame.bin 01_ingame_c.bin > nul
..\utils\apack.exe sfx.bin sfx_c.bin > nul

