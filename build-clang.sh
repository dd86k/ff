#T="\"`date +"%Y-%m-%d %H:%M:%S"`\""
clang src/*.c src/executables/*.c src/etc/*.c src/images/*.c src/documents/*.c src/audio/*.c src/archives/*.c src/vdisk/*.c $1 $2 $3 -std=gnu99 -fno-stack-protector -fshort-enums -fstrict-enums -fpack-struct=1 -lm -off
#-DTIMESTAMP="$T"