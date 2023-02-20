	/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
#include <stdint.h>
#include "stm32h743xx.h"

static int mcu_pwr_init(void);
static int mcu_flash_init(void);
static int mcu_rcc_init(void);
static void mcu_error(void);

int main(void)
{
	int mcu_status = 0;
	uint32_t x,y,res;


//	Initialize the power supply
	mcu_status = mcu_pwr_init();
	if(!mcu_status)
	{
		mcu_error();
	}

//	Initialize the Flash memory
	mcu_status = mcu_flash_init();
	if(!mcu_status)
	{
		mcu_error();
	}

//	Initialize the Clock management.
	mcu_status = mcu_rcc_init();
	if(!mcu_status)
	{
		mcu_error();
	}


    /* Loop forever */
	for(;;);
}

static int mcu_pwr_init(void)
{
	int ret = 0;
	return ret;
}

static int mcu_flash_init(void)
{
	int ret = 0;
	return ret;
}

static int mcu_rcc_init(void)
{
	int ret = 0;
	return ret;
}

static void mcu_error(void)
{
	while(1);
}
