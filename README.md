# ff, simple binary file scanner

ff aims to be a simple, fast, generic, and understandable binary file scanner.

```
$ ff *.exe -s
putty.exe: PE32+ Windows GUI Executable for x86-64 machines, LARGE_ADDRESS_AWARE
FuckingClippy.exe: PE32 Windows GUI .NET Executable for x86 machines, LARGE_ADDRESS_AWARE

$ ff 1542980533119.png -m
Portable Network Graphics image, 1160 x 1402 pixels, 32-bit RGBA
Default compression, Default filtering, No interlacing

$ ff bul-bul0000138.pdf
PDF-1.7 document

$ ff "XI - Blue Zenith Solo (EpreTroll).mid"
MIDI: Multiple tracks, 4 tracks at 96 ticks/quarter-note
```

# Compiling

There is currently no Makefile at the moment.

It's usually best to use `build-clang-cl.cmd` on Windows and `build-clang.sh` on Linux, as you can add additional arguments easily. Reminder that you should use `/Ot` on Widnows (cl) and `-O3` on Linux.

However, if you want to define your own arguments:

You **MUST**:
- Byte-align structs
  - cl, clang-cl: `/Zp`
  - clang, gcc: `-fpack-struct=1`

## Windows Notes

### File Globbing

If you wish to include file globbing, throw in `setargv.obj` alongside the build script. This object file is included with your Visual Studio install. Don't forget to use the proper target architecture.