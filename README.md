Memory to Memory DMA sample for the stm32f4 discovery, Should work with the stm32f4x MCU. 

This sample uses a the DMA2 Controller to perform a memory to memory DMA transfer. 
Then proceeds to indicate the stages of the DMA transfer with. 

BLUE -> Init
RED -> Started 
ORANGE -> Completed Validly


## Building
Ensure you have Make installed on your system and you can use the Makefile in the root directory to build by running 

`make clean && make`

This will give you a build directory with a `blink.elf` for debugging and `blink.bin` for flashing. 


### SWEEET!
