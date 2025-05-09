MEMORY
{
    FLASH (rx)  : ORIGIN = 0x00000000, LENGTH = 1024K
    RAM (rwx)   : ORIGIN = 0x20000000, LENGTH = 4K
}
SECTIONS
{
    .text :
    {
        . = ALIGN(4);
        *(.vector_table*)
        *(.text*)
        . = ALIGN(4);
        *(.rodata*)
    } > FLASH
    
    __ldata__ = LOADADDR(.data);

    .data :
    {
        . = ALIGN(4);
        __data_start__ = .;
        *(.data*)
        __data_end__ = .;
    }> RAM AT > FLASH

    .bss :
    {
        . = ALIGN(4);
        __bss_start__ = .;
        *(.bss*)
        __bss_end__ = .;
    } > RAM

    __end__ = .;
    end = .;
   
}
