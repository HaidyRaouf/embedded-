/******************************************************************************
 *
 * File Name: project.c
 *
 * Description: application file for mini project 4
 *
 * Author: Haidy Raouf
 *
 * Created on: Mar 3, 2022
 *
 *******************************************************************************/
#include "ultrasonic.h"
#include "gpio.h"
#include <avr/io.h> /*to use SREG*/
#include "common_macros.h"
#include "lcd.h"
extern uint8 g_edgeCount;
int main(void)
{
	uint16 distance=0;
	Ultrasonic_init();
	LCD_init();
	LCD_displayStringRowColumn(0, 1,"Distance=    cm");
	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);
	while (1)
		{
		if(g_edgeCount == 2)
				{
					Icu_DeInit(); /* Disable ICU Driver */
					g_edgeCount = 0;
					distance=Ultrasonic_readDistance();
					LCD_moveCursor(0,11);
					LCD_integerToString(distance);

				}


		}
}
