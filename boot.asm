; boot.asm: The bootloader to boot the operating system with grub.
[bits 32] ; We are in 32 bit mode
global start ; Start's the operating system, we call it in the linker script.
extern _kernel_main ; This is in the C++ file for the main loop.

section .mbHeader

align 0x4

; Setting up the Multiboot header - see GRUB docs for details.
MODULEALIGN equ 1<<0                    ; Align loaded modules on page boundaries.
MEMINFO     equ 1<<1                    ; Provide a memory map.
FLAGS       equ MODULEALIGN | MEMINFO   ; This is the Multiboot 'flag' field.
MAGIC       equ 0x1BADB002              ; 'Magic number' lets the bootloader find the header.
CHECKSUM    equ -(MAGIC + FLAGS)        ; Checksum required.

MultiBootHeader:
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

start:
    push ebx ; This loads the grub structure.
    call _kernel_main
