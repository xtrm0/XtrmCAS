@echo off
rem Do not edit! This batch file is created by CASIO fx-9860G SDK.


if exist XTRMCAS.G1A  del XTRMCAS.G1A

cd debug
if exist FXADDINror.bin  del FXADDINror.bin
"C:\CASIOSDK\OS\SH\Bin\Hmake.exe" Addin.mak
cd ..
if not exist debug\FXADDINror.bin  goto error

"C:\CASIOSDK\Tools\MakeAddinHeader363.exe" "C:\Users\Xtrm0\Documents\CASIO\fx-9860G SDK\XtrmCAS"
if not exist XTRMCAS.G1A  goto error
echo Build has completed.
goto end

:error
echo Build was not successful.

:end

