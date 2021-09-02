echo "Setting environment variables for Powershell"
$env:Z88DK_PATH = 'c:\z88dk'
$env:Z80_OZFILES = $env:Z88DK_PATH + '\Lib\'
$env:ZCCCFG = $env:Z88DK_PATH + '\Lib\Config\'
$env:path = $env:Z88DK_PATH + ';' + $env:path
