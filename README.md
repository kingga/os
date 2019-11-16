# OS Experiment
This is me just trialing OS development for fun.

## Current Errors
When building with `call _kernel_main` commented out in `boot.asm` I get the following error:

```
Cleaning build directories.
Creating build and iso directories.
Building the bootloader.
Building the kernel.
Linking the kernel and bootloader.
~/opt/cross/lib/gcc/i686-elf/9.2.0/../../../../i686-elf/bin/ld: build/kernel.o: in function `kernel_main()':
kernel.cpp:(.text+0x34): undefined reference to `operator new(unsigned long)'
collect2: error: ld returned 1 exit status
Cleaning build directory.
```

When I uncomment `_kernel_main` as it is in this repository I get this error:

```
Cleaning build directories.
Creating build and iso directories.
Building the bootloader.
Building the kernel.
Linking the kernel and bootloader.
~/opt/cross/lib/gcc/i686-elf/9.2.0/../../../../i686-elf/bin/ld: build/boot.o: in function `start':
boot.asm:(.mbHeader+0xe): undefined reference to `_kernel_main'
```

## Links
- [Tutorial Followed - CPlusPlus.com](http://www.cplusplus.com/articles/zv07M4Gy/)
- [Cross-Compiler Tutorial - OSDev.org](https://wiki.osdev.org/GCC_Cross-Compiler)

**NOTE:** See [build.sh](build.sh) for more information on setup.
