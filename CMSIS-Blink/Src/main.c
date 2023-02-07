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

//	Initialize the Clock magnament
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
/*	1. When the system is powered on, the POR monitors VDD supply. Once VDD is above the
 * POR threshold level, the voltage regulator is enabled in the default supply
 * configuration:
 * 		The Voltage converter output level is set at 1.0 V in accordance with the VOS3
 * 		level configured in PWRD3 domain control register (PWR_D3CR).
 *
 * 	2. The system is kept in reset mode as long as VCORE is not correct.
 *
 * 	3. Once VCORE is correct, the system is taken out of reset and the HSI oscillator is
 * 	enabled.
 *
 * 	4. Once the oscillator is stable, the system is initialized: Flash memory and option bytes
 * 	are loaded and the CPU starts in limited run mode (Run*).
 *
 * 	5. The software shall then initialize the system including supply configuration
 * 	programming in PWR control register 3 (PWR_CR3). Once the supply configuration
 * 	has been configured, the ACTVOSRDY bit in PWR control status register 1
 * 	(PWR_CSR1) shall be checked to guarantee valid voltage levels:
 *
 * 		a) As long as ACTVOSRDY indicates that voltage levels are invalid, the system is in
 * 		Run* mode, write accesses to the RAMs are not permitted and VOS shall not be
 * 		changed.
 *
 * 		b)Once ACTVOSRDY indicates that voltage levels are valid, the system is in normal
 * 		Run mode, write accesses to RAMs are allowed and VOS can be changed.
 * */
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
