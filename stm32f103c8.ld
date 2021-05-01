/*
STM32F103 has Flash memory beginning at 0x08000000
SRAM starts at 0x20000000

SRAM/ROM sizes vary - STM32F103C8T6 is 64k flash, 20K sram
*/

MEMORY
{
	rom (rx) : ORIGIN = 0x08000000, LENGTH = 64K
	ram (rwx) : ORIGIN = 0x20000000, LENGTH = 20K
}

/* Include the common ld script. */
INCLUDE cortex-m-generic.ld
