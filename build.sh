#!/bin/bash
GPP_COMPILER_PATH=$HOME/opt/cross/bin/i686-elf-g++
GCC_COMPILER_PATH=$HOME/opt/cross/bin/i686-elf-gcc
XORRISO_PATH=$HOME/opt/cross/bin/xorriso

function error_no_cc() {
    echo "Error: $1 missing - $2"
    echo "Error: Make sure you have build a cross compiler first!"
    echo "https://wiki.osdev.org/GCC_Cross-Compiler"
    exit 1;
}

if [ ! -f "$GPP_COMPILER_PATH" ]; then
    echo "Error: G++ Cross Compiler Missing!"
    error_no_cc "G++" "$GPP_COMPILER_PATH"
fi

if [ ! -f "$GCC_COMPILER_PATH" ]; then
    echo "Error: GCC Cross Compiler Missing!"
    error_no_cc "GCC" "$GCC_COMPILER_PATH"
fi

# if ! file_exists $XORRISO_PATH; then
if [ ! -f "$XORRISO_PATH" ]; then
    echo "Error: Xorriso path cannot be found!"
    echo "Build xorriso:"
    echo "Download: https://www.gnu.org/software/xorriso/xorriso-1.4.6.tar.gz"
    echo "cd cd xorriso-1.4.6"
    echo "touch xorriso/*.info"
    echo "./configure --target=\$TARGET --prefix=\$PREFIX"
    echo "make"
    echo "cp xorriso/xorriso ~/opt/cross/bin"
    exit 1;
fi

echo "Cleaning build directories."
if [ -d build ]; then
    rm -rf build
fi

if [ -d iso ]; then
    rm -rf iso
fi

echo "Creating build and iso directories."
if [ ! -d build ]; then
    mkdir build
fi

if [ ! -d iso ]; then
    mkdir iso
    echo "menuentry \"MyOS\" {
    multiboot /boot/kern
}" > iso/grub.cfg
fi

echo "Building the bootloader."
nasm -f elf boot.asm -o build/boot.o

echo "Building the kernel."
$GPP_COMPILER_PATH -c kernel.cpp -o build/kernel.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti

echo "Linking the kernel and bootloader."
$GCC_COMPILER_PATH build/boot.o build/kernel.o -T linker.ld -o build/kern -nostdlib -nodefaultlibs -lgcc

if [ -f build/kern ]; then
    echo "Generating ISO."
    grub-mkrescue build/kern -o iso/kern.iso --xorriso=$XORRISO_PATH
else
    if [ -d iso ]; then
        rm -rf iso
    fi
fi

echo "Cleaning build directory."
if [ -d build ]; then
    rm -rf build
fi
