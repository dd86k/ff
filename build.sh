#!/bin/sh
# 
# dd custom build script for UNIX platforms
# Optimized for: clang
# 

# Script version
V=1.0

CC=clang
CFLAGS="-c -std=gnu99 -fshort-enums -fstrict-enums -fno-stack-protector -fpack-struct=1"

case $1 in
release)
	CFLAGS="$CFLAGS -O3"
	;;
clean)
	rm bin/*
	exit 0
	;;
help|--help|-h)
	echo "Usage:"
	echo "   build [OPTIONS]"
	echo
	echo " OPTIONS"
	echo "   release    Compile a release, optimized build"
	echo "   clean      Clean bin folder"
	echo "   help       This help screen"
	echo
	echo "By default, build.sh will compile the project normally."
	exit 0
	;;
esac

# Default
echo "*************************"
echo "*                       *"
echo "*  dd Build script $V  *"
echo "*                       *"
echo "*************************"
echo

if [ ! -d bin ]; then mkdir bin; fi
cd bin
for f in ../src/**/*.c ../src/*.c; do
	echo [$CC] $f
	$CC $CFLAGS $f
	if [ $? -gt 0 ]; then exit 1; fi
done
cd ..
echo [$CC] Linking...
$CC $CLAGS bin/*.o -off -lm
echo Done!
exit
