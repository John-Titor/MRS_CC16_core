/*
 * Linker file for the S32K144 as used in the CC16.
 */

MEMORY
{
    /* Flash - immutable */
    bootrom              : ORIGIN = 0x00000000, LENGTH = 0x0000f000
    eeprom_readonly      : ORIGIN = 0x0000f000, LENGTH = 0x00000200
    flash_calibration    : ORIGIN = 0x0000f200, LENGTH = 0x00000e00

    /* Flash - writable */
    application_header   : ORIGIN = 0x00010000, LENGTH = 0x00001000
    vector_table         : ORIGIN = 0x00011000, LENGTH = 0x00000400
    flash_config         : ORIGIN = 0x00011400, LENGTH = 0x00000010
    application_flash    : ORIGIN = 0x00011410, LENGTH = 0x0006bbf0

    /* FlexRAM */
    flexram              : ORIGIN = 0x14000000, LENGTH = 0x00001000

    /* SRAM */
    sram_l               : ORIGIN = 0x1fff8000, LENGTH = 0x00008000
    sram_h               : ORIGIN = 0x20000000, LENGTH = 0x00007000
}

SECTIONS
{
    .application_header :
    {
        KEEP(*(.application_header))
    } > application_header

    .vector_table :
    {
        KEEP(*(.exception_vectors))
        KEEP(*(.interrupt_vectors))
    } > vector_table

    __application_start = .;
    .flash_config :
    {
        KEEP(*(.flash_config))
    } > flash_config

    .text :
    {
        *(.text)
        *(.text*)
        *(.rodata*)
    } > application_flash

    .preinit_array ALIGN(4) :
    {
        __preinit_array_start = .;
        KEEP(*(.preinit_array))
        __preinit_array_end = .;
    } > application_flash

    .init_array ALIGN(4) : 
    {
        __init_array_start = .;
        KEEP(*(.init_array))
        __init_array_end = .;
    } > application_flash

    .fini_array ALIGN(4) :
    {
        __fini_array_start = .;
        KEEP(*(.fini_array))
        __fini_array_end = .;
    } > application_flash

    .data ALIGN(4) :
    {
        __data_start = .;
        *(.data)
        *(.data*)
        . = ALIGN(4);
        __data_end = .;
    } > sram_h AT > application_flash
    __data_load = LOADADDR(.data);
    . = ALIGN(256);
    __application_end = .;
    __application_size = __application_end - __application_start;

    .bss ALIGN(4) (NOLOAD) :
    {
        __bss_start = .;
        *(.bss)
        *(.bss*)
        . = ALIGN(4);
        __bss_end = .;
        *(.noinit)
        *(.noinit*)
    } > sram_h

    . = ALIGN(4);
    __heap_start = .;
    __stacktop = ORIGIN(sram_h) + LENGTH(sram_h);
}