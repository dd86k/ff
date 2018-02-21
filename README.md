# ff, simple binary file scanner

ff is a rewrite of dfile in C.

![ff in action](https://dd86k.github.io/imgs/ff0.png)

What's better?
- Lots of fixes
- ~10x smaller executable size
- Simply faster

# Compiling

You **MUST**:
- Byte-align structs
  - cl, clang-cl: `/Zp`
  - clang, gcc: `-fpack-struct=1`

You **COULD**:
- Use one of the build scripts
  - They usually includes the `TIMESTAMP` macro
    - Windows: `%DATE% %TIME%`
    - Linux: (To be defined)

## Windows Notes

### File Globbing

If you wish to include globbing, throw in `setargv.obj` alongside the build script. This object file is included with your Visual Studio install. Don't forget to use the proper target architecture.