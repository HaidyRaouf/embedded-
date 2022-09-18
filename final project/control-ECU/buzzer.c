/******************************************************************************
 *
 * Module: BUZZER
 *
 * File Name: buzzer.h
 *
 * Description: Header file for the buzzer driver
 *
 * Created on: Mar 20, 2022
 *
 * Author: Haidy Raouf
 *
 *******************************************************************************/
#include "buzzer.h"
#include "avr/io.h"
#include "gpio.h"
#include "avr/delay.h"

/*******************************************************************************
 *                         Function Definitions                                *
 *******************************************************************************/

void Buzzer_init(void)
{
	/* setup buzzer pin direction as output pin */
	GPIO_setupPinDirection(BUZZER_PORT,BUZZER_PIN, PIN_OUTPUT);
}

void Buzzer_ON(void)
{
	/* Activate Buzzer */
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_HIGH);
}

void Buzzer_OFF()
{
	/* Disable Buzzer */
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_LOW);
}
