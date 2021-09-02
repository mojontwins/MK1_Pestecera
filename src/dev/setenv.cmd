@echo off
echo Setting environment for PowerShell
$env:Z88DK_PATH = "c:\z88dk"
$env:Z80_OZFILES = $env:Z88DK_PATH + "\Lib\"
$env:ZCCCFG = $Env:Z88DK_PATH + "\Lib\Config\"
$env:path = $Env:Z88DK_PATH + ";" + $env:path
