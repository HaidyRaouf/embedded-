/* Module:DC_MOTOR
 *
 * File Name:dc_motor.c
 *
 * Description: source file for dc motor driver
 *
 * Created on: Mar 20, 2022
 *
 * Author: Haidy Raouf
 *
 */

#include <avr/io.h>
#include "dc-motor.h"
#include "gpio.h"
#include "common_macros.h"

/*******************************************************************************
 *                         Function Definitions                                *
 *******************************************************************************/

void DcMotor_Init(void)
{
	/* Setup the direction for the two motor pins through the GPIO driver */
	GPIO_setupPinDirection(DC_MOTOR_PORT_ID ,DC_MOTOR_PIN_IN1,PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_PORT_ID ,DC_MOTOR_PIN_IN2 ,PIN_OUTPUT);

	DcMotor_Rotate(Stop);
}

void DcMotor_Rotate(DcMotor_State state)
{


	if (state == Stop)
	{
		// Stop the motor
		GPIO_writePin(DC_MOTOR_PORT_ID,DC_MOTOR_PIN_IN1,LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_PORT_ID,DC_MOTOR_PIN_IN2,LOGIC_LOW);

	}

	else if (state == Anti_Clockwise)
	{
		// Rotate the motor --> anti-clock wise
		GPIO_writePin(DC_MOTOR_PORT_ID,DC_MOTOR_PIN_IN1,LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_PORT_ID,DC_MOTOR_PIN_IN2,LOGIC_HIGH);
	}
	else if (state == Clockwise)
	{
		// Rotate the motor --> clock wise
		GPIO_writePin(DC_MOTOR_PORT_ID,DC_MOTOR_PIN_IN1,LOGIC_HIGH);
		GPIO_writePin(DC_MOTOR_PORT_ID,DC_MOTOR_PIN_IN2,LOGIC_LOW);
	}

}


