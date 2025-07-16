/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Zacck Osiemo <coderv63@gmail.com>
 * @brief          : Main program body
 *****************************************************************************
 **/

#include <stdint.h>
#include "stm32f4xx.h"

#define BUFFER_SIZE 32 
uint32_t srcBuffer[BUFFER_SIZE]; 
uint32_t destBuffer[BUFFER_SIZE] = {0};



void _init() {
	//dummy
}
void init_indicators(); 



int main(void)
{
	init_indicators();

	//INIT  SRC Buffer
	for(uint32_t i = 0; i < BUFFER_SIZE; i++) 
	{
		srcBuffer[i] = i + 1;
	}

	//INIT DMA stream 
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;
	//disable the stream
	DMA2_Stream0->CR = 0;
	while (DMA2_Stream0->CR & DMA_SxCR_EN);

	DMA2_Stream0->CR |= (0x2 << DMA_SxCR_DIR_Pos);
	DMA2_Stream0->CR |= (0x2 << DMA_SxCR_MSIZE_Pos);
	DMA2_Stream0->CR |= (0x2 << DMA_SxCR_PSIZE_Pos);
	DMA2_Stream0->CR |= (0x1 << DMA_SxCR_PL_Pos);
	DMA2_Stream0->CR |= DMA_SxCR_MINC;
	DMA2_Stream0->CR |= DMA_SxCR_PINC;
	DMA2_Stream0->CR |= DMA_SxCR_TCIE;
	DMA2_Stream0->PAR = (uint32_t)srcBuffer; 
	DMA2_Stream0->M0AR = (uint32_t)destBuffer; 
	DMA2_Stream0->NDTR = BUFFER_SIZE; 

	NVIC_EnableIRQ(DMA2_Stream0_IRQn);

	GPIOD->BSRR |= GPIO_BSRR_BS_15;

	//clear any pending statuses & Start the transfer
	DMA2->LIFCR = DMA_LIFCR_CTCIF0;
	DMA2_Stream0->CR |= DMA_SxCR_EN; 








	
	
    /* Loop forever */
	for(;;);
}

void DMA2_Stream0_IRQHandler(void)
{
	if(DMA2->LISR  & DMA_LISR_TCIF0) {
		GPIOD->BSRR |= GPIO_BSRR_BS_14;
		DMA2->LIFCR = DMA_LIFCR_CTCIF0;
		DMA2_Stream0->CR &= ~DMA_SxCR_EN;

		if(destBuffer[20] == srcBuffer[20]) {
			GPIOD->BSRR |= GPIO_BSRR_BS_13;
		}
	}
}



void init_indicators() 
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

	//BLUE
	GPIOD->MODER |= GPIO_MODER_MODER15_0;
	GPIOD->MODER &= ~GPIO_MODER_MODER15_1;
	GPIOD->OTYPER &= ~GPIO_OTYPER_OT_15;
	GPIOD->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR15_0;
	GPIOD->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR15_1;
	GPIOD->PUPDR &= ~GPIO_PUPDR_PUPDR15_0;
	GPIOD->PUPDR &= ~GPIO_PUPDR_PUPDR15_1;


	//RED
	GPIOD->MODER |= GPIO_MODER_MODER14_0;
	GPIOD->MODER &= ~GPIO_MODER_MODER14_1;
	GPIOD->OTYPER &= ~GPIO_OTYPER_OT_14;
	GPIOD->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR14_0;
	GPIOD->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR14_1;
	GPIOD->PUPDR &= ~GPIO_PUPDR_PUPDR14_0;
	GPIOD->PUPDR &= ~GPIO_PUPDR_PUPDR14_1;

	//ORANGE
	GPIOD->MODER |= GPIO_MODER_MODER13_0;
	GPIOD->MODER &= ~GPIO_MODER_MODER13_1;
	GPIOD->OTYPER &= ~GPIO_OTYPER_OT_13;
	GPIOD->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR13_0;
	GPIOD->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR13_1;
	GPIOD->PUPDR &= ~GPIO_PUPDR_PUPDR13_0;
	GPIOD->PUPDR &= ~GPIO_PUPDR_PUPDR13_1;


}

