/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "MK64F12.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */


void delay(void);

void polling_implemenation(void);
void interrupt_implementation(void);

int main (){

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitDebugConsole();

	interrupt_implementation();
	polling_implementation();
}

int polling_implementation(void)
{
	PORT_SetPinMux(PORTB, 22, kPORT_MuxAsGpio );				// red led mux
	PORT_SetPinMux(PORTC, 6, kPORT_MuxAsGpio );				// red led mux

	gpio_pin_config_t led_config ={
		kGPIO_DigitalOutput,
		1, };

	gpio_pin_config_t button_config ={
		kGPIO_DigitalInput,
		0, };

	GPIO_PinInit( GPIOB , 22 , &led_config);
	GPIO_PinInit( GPIOC , 6 , &button_config);

	PRINTF("Polling method .. \r\n");
	while (1)
	{
		uint8_t button_status = GPIO_PinRead(GPIOC,6);
		if ( button_status == 0  ){
			GPIO_PinWrite(GPIOB,22, 0);
		}
		else{
			GPIO_PinWrite(GPIOB,22, 1);
		}
		//		delay();
		PRINTF("%x.. \r\n", button_status );
	}
}

void interrupt_implementation(){

	/* PORT_SetPinMux( PORTE , 26 , kPORT_MuxAsGpio ); */					/// errror execution
	PORT_SetPinMux( PORTB , 21 , kPORT_MuxAsGpio );  					/// errror execution

	gpio_pin_config_t led_config ={
		kGPIO_DigitalOutput,
		1, };

	gpio_pin_config_t button_config ={
		kGPIO_DigitalInput,
		0, };

	GPIO_PinInit( GPIOB , 21 , &led_config);
	GPIO_PinInit( GPIOA , 4 , &button_config);
	PRINTF("\r\nInterupt method initialized .. \r\n");

	PORT_SetPinInterruptConfig ( PORTA, 4 , kPORT_InterruptRisingEdge );
}

void PORTA_IRQHandler(void){
	
}

void delay(void)
{
	volatile uint32_t i = 0;
	for (i = 0; i < 800000; ++i)
	{
		__asm("NOP"); /* delay */
	}
	for (i = 0; i < 800000; ++i)
	{
		__asm("NOP"); /* delay */
	}
	for (i = 0; i < 800000; ++i)
	{
		__asm("NOP"); /* delay */
	}
}

