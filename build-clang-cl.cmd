@ECHO OFF
::
:: ** CL CLI reminder **
:: optimize size: /Os
:: optimize speed: /Ot
:: compile dynamic: /MD
:: compile static: /MT
::
:: Don't forget setargv_*.obj
::
set t="\"%date% %time%\""
clang-cl src\*.c src\executables\*.c src\etc\*.c src\images\*.c src\documents\*.c src\audio\*.c src\archives\*.c src\vdisk\*.c %1 %2 %3 -DTIMESTAMP=%t% /Zp /o "ff.exe"