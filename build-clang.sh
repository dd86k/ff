t="`date +"%Y-%m-%d %H:%M:%S"`\""
clang src/*.c src/executables/*.c src/etc/*.c src/images/*.c src/documents/*.c src/audio/*.c src/archives/*.c src/vdisk/*.c $1 -std=c99 -fno-stack-protector -fshort-enums -fstrict-enums -fpack-struct=1 -O3 -off -DTIMESTAMP="\"$t"
# -DTIMESTAMP="$t"