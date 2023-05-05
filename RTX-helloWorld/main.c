/* 
		NUCLEO-H743ZI2 User LEDs
		
		User LD1: 	a green user LED is connected to the STM32 I/O PB0 (SB120 ON and SB119
								OFF) or PA5 (SB119 ON and SB120 OFF) 
		
		User LD2:		User LD2: a blue user LED is connected to PB7.
		
		User LD3:		User LD3: a red user LED is connected to PB14.
		
*/
#include "stm32h7xx.h"

static void init_led_gpio(void)
{
	int i=0;
	
	RCC->AHB4RSTR |= RCC_AHB4RSTR_GPIOBRST;		  //Reset GPIOB
	for(i=0; i<10000;i++);	//Some delay until the GPIOB resets.
	RCC->AHB4RSTR &= ~RCC_AHB4RSTR_GPIOBRST;		//Reset GPIOB
		
	RCC->AHB4ENR |= RCC_AHB4ENR_GPIOBEN;	//Enabling GPIOB peripheral clock
	
	// Configure GPIOB
	
	// OUTPUT MODE
	GPIOB->MODER = 0;
	GPIOB->MODER |= (GPIO_MODER_MODE0_0 | GPIO_MODER_MODE7_0 | GPIO_MODER_MODE14_0);
	
	//PUSH-PULL
	GPIOB->OTYPER = 0;
	
	//Set the GPIO State
	GPIOB->ODR |= (GPIO_ODR_OD0 | GPIO_ODR_OD7 | GPIO_ODR_OD14);
}

int main(void)
{
	init_led_gpio();
	
	while(1)
	{		
	}

}
