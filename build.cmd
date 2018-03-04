@ECHO OFF
REM 
REM ff custom build script for Windows
REM Optimized for: clang-cl
REM 

REM Version
SET V=1.0

SET CC=clang-cl
SET CFLAGS=/Zp /TC -c /Gd /GR-
IF "%1"=="release" SET CFLAGS=%CFLAGS% /Ox
IF "%1"=="debug" (
	SET CFLAGS=%CFLAGS% /MDd
) ELSE (
	SET CFLAGS=%CFLAGS% /MD
)
SET _COMP=%CC% %CFLAGS% -o bin\

IF "%1"=="clean" goto :CLEAN
IF "%1"=="help" goto :HELP
IF "%1"=="/?" goto :HELP
IF "%1"=="-?" goto :HELP
IF "%1"=="-h" goto :HELP
IF "%1"=="--help" goto :HELP

REM Default build
echo *************************
echo *                       *
echo *  dd Build script %V%  *
echo *                       *
echo *************************
echo.
IF NOT EXIST bin MKDIR bin
FOR /D %%d in (src\*) DO (
	FOR /R %%f in (%%d\*.c) DO (
		echo [%CC%] %%f
		%_COMP% %%f
		IF ERRORLEVEL 1 GOTO :EOF
	)
)
FOR /R %%f in (src\*.c) DO (
	echo [%CC%] %%f
	%_COMP% %%f
	IF ERRORLEVEL 1 GOTO :EOF
)
echo [%CC%] Linking...
%CC% bin\*.obj -off.exe
IF ERRORLEVEL 1 GOTO :EOF
echo Done!
GOTO :EOF

:HELP
echo Usage:
echo   build [OPTIONS]
echo.
echo OPTIONS
echo   release    Compile a release, optimized build
echo   clean      Clean bin folder
echo   help       This help screen
echo.
echo By default, Build.cmd will compile the project normally.
GOTO :EOF

:CLEAN
DEL /S /Q bin > NUL
GOTO :EOF