# ff, simple binary file scanner

ff aims to be a simple, fast, generic, and understandable binary file scanner.

Warning: This tool is not memory safe and will not work on big-endian (MSB)
platforms.

```
$ ff ff ff.exe
PE32+ Windows Console Executable for x86-64, LARGE_ADDRESS_AWARE
ELF64LE System V Shared object for x86-64 machines

$ ff ff.exe -m
PE32+ Windows Console Executable for x86-64 machines, LARGE_ADDRESS_AWARE
Number of sections     : 0h
Timestamp              : 5AA58AC4h
Pointer to Symbol Table: 0h
Number of symbols      : 0h
Size of Optional Header: F0h
Characteristics        : 22h

$ ff * -sm
Manuel - Gas Gas Gas.flac: FLAC audio, 44100 Hz, 16-bit, 2 channels
cv.wav: WAVE audio (G.729) 8000 Hz, 0 kbps, 0-bit, 1 channels
2002ado.wad: PWAD, 894 entries at C7A7FDh

$ ff /dev/null
Character device

> ff NUL
Character device
```

For a list of files ff(1) picks up, visit
[File List](https://git.dd86k.space/dd86k/ff/wiki/File%20Detection%20List)
(Gitbucket).

# Compiling

There is currently no Makefile at the moment.

It's usually best to use `build-clang.cmd` on Windows and `build-clang.sh` on
Linux, as you can add additional arguments easily. Reminder that you should add
`-O3` (or `/Ot` for cl).

However, if you want to define your own arguments:

You **MUST**:
- Byte-align structs
  - cl, clang-cl: `/Zp`
  - clang, gcc: `-fpack-struct=1`

## File Globbing on Windows

If you wish to include file globbing, throw in `setargv.obj` alongside the
build script. This object file is included with your Visual Studio install.
Don't forget to use the proper target architecture.

# License

This project is licensed under the CC0 1.0 Universal Public Domain Dedication
license.