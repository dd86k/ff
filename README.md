# ff, simple binary file scanner

ff aims to be a simple, fast, and easy-to-understand binary file scanner.

![ff screenshot](https://dd86k.github.io/imgs/ff0.png)

# Compiling

The Makefile is **not** ready.

To compile ff:

You **MUST**:
- Byte-align structs
  - cl, clang-cl: `/Zp`
  - clang, gcc: `-fpack-struct=1`

You **COULD**:
- Use one of the build scripts
  - They usually includes the `TIMESTAMP` macro
    - Windows: `%DATE% %TIME%`
    - Linux: (To be defined)
  - They require clang to be installed

## Windows Notes

### File Globbing

If you wish to include globbing, throw in `setargv.obj` alongside the build script. This object file is included with your Visual Studio install. Don't forget to use the proper target architecture.