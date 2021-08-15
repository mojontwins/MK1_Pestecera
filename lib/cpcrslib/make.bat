@echo off

if [%1]==[fg] goto fgmake

echo Building normal version
copy CPCconfig_normal.def CPCconfig.def >nul
z80asm -v -xcpcrslib.lib @cpcrslib.lst
goto copystuff

:fgmake
echo Building FG version
copy CPCconfig_fg.def CPCconfig.def >nul
z80asm -v -xcpcrslib_fg.lib @cpcrslib.lst

:copystuff
copy *.lib c:\z88dk\lib\clibs
copy cpcrslib.h c:\z88dk\include
