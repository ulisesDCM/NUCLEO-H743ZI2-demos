/* 
		NUCLEO-H743ZI2 User LEDs
		
		User LD1: 	a green user LED is connected to the STM32 I/O PB0 (SB120 ON and SB119
								OFF) or PA5 (SB119 ON and SB120 OFF) 
		
		User LD2:		User LD2: a blue user LED is connected to PB7.
		
		User LD3:		User LD3: a red user LED is connected to PB14.
		
*/
#include "stm32h7xx.h"
#include "RTL.h"

OS_TID taskID1;
OS_TID taskID2;

typedef enum
{
	GREEN = GPIO_ODR_OD0_Pos,
	BLUE = GPIO_ODR_OD7_Pos,
	RED = GPIO_ODR_OD14_Pos
}eUSER_LED;

static void init_led_gpio(void)
{
	SET_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOBEN);	//Enable GPIOB peripheral clock
	
	// OUTPUT MODE
	MODIFY_REG(GPIOB->MODER, 
						(GPIO_MODER_MODE0 | GPIO_MODER_MODE7 | GPIO_MODER_MODE14), 
						(GPIO_MODER_MODE0_0 | GPIO_MODER_MODE7_0 | GPIO_MODER_MODE14_0)
	);
	
	//PUSH-PULL
	CLEAR_BIT(GPIOB->OTYPER, GPIO_OTYPER_OT0);
	CLEAR_BIT(GPIOB->OTYPER, GPIO_OTYPER_OT7);
	CLEAR_BIT(GPIOB->OTYPER, GPIO_OTYPER_OT14);
	
	//Turn off all LEDs
	CLEAR_BIT(GPIOB->ODR, GPIO_ODR_OD0 );
	CLEAR_BIT(GPIOB->ODR, GPIO_ODR_OD7 );
	CLEAR_BIT(GPIOB->ODR, GPIO_ODR_OD14 );	
}

static void toogle_led(eUSER_LED led)
{
	int state = READ_BIT(GPIOB->ODR, (1<<led)) >> led;
	state = !state & 1;
	MODIFY_REG(GPIOB->ODR, (1<<led), (state<<led));
}	

__task void toogle_green_led(void)
{
	while(1)
	{
		int i=0;
		toogle_led(GREEN);
		for(i=0;i<1000000;i++);	//Delay
	}
}

__task void toogle_red_led(void)
{
	while(1)
	{
		int i=0;
		toogle_led(RED);
		for(i=0;i<1000000;i++);	//Delay
	}
}

__task void init(void)
{
	taskID1 = os_tsk_create(toogle_green_led, 0);
	taskID2 = os_tsk_create(toogle_red_led, 0);
	
	os_tsk_delete_self();
}

int main(void)
{
	init_led_gpio();	//Initialize GPIOB
	os_sys_init(init);		//Initialize RTX and create temporary task init.
}
