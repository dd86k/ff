@ECHO OFF
set t="\"%date% %time%\""
clang-cl src\*.c src\executables\*.c src\etc\*.c src\images\*.c src\documents\*.c src\audio\*.c src\archives\*.c src\vdisk\*.c %1 %2 %3 -DTIMESTAMP=%t% /Zp /o "ff.exe"