/* 
		NUCLEO-H743ZI2 User LEDs
			User LD1: 	a green user LED is connected to the STM32 I/O PB0 (SB120 ON and SB119
									OFF) or PA5 (SB119 ON and SB120 OFF) 
			User LD2:		User LD2: a blue user LED is connected to PB7.
			User LD3:		User LD3: a red user LED is connected to PB14.
			
			
		Mixing Assembly Language and C Code:		
			Calling functions and Passing Arguments
			When a function calls a subroutine, it places the return address in the link register LR. 
			The arguments (if any) are passed in registers r0 through r3, starting with r0. 
			If there are more than four arguments, or they are too large to fit in 32-bit registers, 
			they are passed on the stack.
			
		Temporary storage
			Registers r0 through r3 can be used for temporary storage if 
			they were not used for arguments, or if the argument value is no longer needed.
		
		Preserved Registers
			Registers r4 through r11 must be preserved by a subroutine. 
			If any must be used, they must be saved first and restored before returning. 
			This is typically done by pushing them to and popping them from the stack.

		Returning from Functions
			Because the return address has been stored in the link register, the BX LR 
			instruction will reload the pc with the return address value from the LR. 
			If the function returns a value, it will be passed through register r0

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

__asm void my_strcpy(const char *src, char *dest)
{
loop
		LDRB r2,[r0]	;Load in r2 the value pointed by r0 (src)
		ADDS r0, #1		;Increment the pointer r0 (src) by 1
		STRB r2, [r1] ;Store in the pointed byte (dest) the value of R2
		ADDS r1,#1		;Increment the dest pointer.
		CMP r2, #0		;Compare if the string is over
		BNE loop 			;Check the equal flag and if not zero, then jump to label
	BX	lr					;Return from function call
}

__asm void my_capitalize(char *str)
{
again
	LDRB r1,[r0];
	CMP r1,#'a'-1
	BLS skip
	
	CMP r1,#'z'
	BHI skip
	
	SUBS r1, #32
	STRB r1,[r0]
skip
	ADDS r0,r0,#1
	CMP r1,#0
	BNE again
	BX lr
}

int main(void)
{
	//init_led_gpio();	//Initialize GPIOB
	//os_sys_init(init);		//Initialize RTX and create temporary task init.
	
	const char source[] = "ulises";
	char dest[20] = {0};
	
	my_strcpy(source, dest);
	my_capitalize(dest);
	
	while(1);
	
}
