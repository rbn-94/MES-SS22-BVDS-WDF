/*----------------------------------------------------------------------
   C6713_DSK_DUETT.CMD : DSK6713 command file for DUETT board                                               
  ----------------------------------------------------------------------*/
/* these two steps must be done for each project manually*/
/* set in "Compiler -> target version C671x" -mv6710 */
/* set in "Compiler -> preprocessor -> define symbols -d" _debug;CHIP_6713 */

/* the required libraries are:
   csl6713.lib; rts6700.lib; dsk6713bsl.lib   */

/* history tracking, changes:
   US :  8-05-2006  : version 1.0 tested without EMIF 
   US : 26-07-2006  : now with EMIF
   US :  8-Aug-2006 : renamed from C6x_DSK.CMD to C6713_DSK_DUETT.CMD
*/
/*----------------------------------------------------------------------*/

-l csl6713.lib
-l rts6700.lib
-l dsk6713bsl.lib

-stack 0x4000
MEMORY
{
  IVECS:      org =         0h, len =      0x220
  IRAM:       org = 0x00000220, len = 0x0002FDE0 /*internal memory*/ 
  /*IRAM:       org = 0x00000220, len = 0x00040000*/ /*internal memory*/ 
  SDRAM:      org = 0x80000000  len = 0x01000000 /*external memory*/ 
  FLASH:      org = 0x90000000, len = 0x00020000 /*flash memory*/
}

/* now correct 26-07-06:
DSK6713 settings */
SECTIONS
{                
  .EXT_RAM :> SDRAM
  .vectors :> IVECS
  .text	   :> IRAM
  .bss     :> IRAM
  .cinit   :> IRAM
  .stack   :> IRAM
  .sysmem  :> IRAM
  .const   :> IRAM
  .switch  :> IRAM
  .far     :> IRAM
  .cio     :> IRAM 
  .lindata :> IRAM  
  .circdata :> IRAM  
}
