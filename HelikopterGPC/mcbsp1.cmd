/*
 * Copyright (C) 2003 Texas Instruments Incorporated
 * All Rights Reserved
 */
/*
 *---------mcbsp1.cmd---------
 *
 */

MEMORY
{
	PMEM:	o = 00000000h	l = 00011000h
	BMEM:	o = 00011000h	l = 00030000h
}

SECTIONS
{    
    .text       >   PMEM
    .csldata	> 	PMEM
    .stack	>   PMEM
    .far	>   PMEM
    .switch	>   BMEM 
    .tables >   BMEM
    .data   >   BMEM
    .bss	>   BMEM
    .sysmem	>   BMEM
    .cinit	>   PMEM
    .const	>   BMEM
    .cio    >   BMEM 
}
