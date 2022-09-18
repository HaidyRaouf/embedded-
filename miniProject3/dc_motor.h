/* Module:DC_MOTOR
 * File Name:dc_motor.h
 * Description: header file for dc motor driver
 * Created on: Feb 25, 2022
 * Author: Haidy Raouf
 */




#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	Stop,Clockwise,Anti_Clockwise
}DcMotor_State;

/*******************************************************************************
 *                         Definitions                                         *
 *******************************************************************************/
#define DC_MOTOR_PORT_ID            PORTB_ID

#define DC_MOTOR_PIN_IN1            PIN0_ID
#define DC_MOTOR_PIN_IN2            PIN1_ID
#define DC_MOTOR_PIN_IN3
#define DC_MOTOR_PIN_IN4

#define DC_MOTOR_PIN_EN1            PIN3_ID
#define DC_MOTOR_PIN_EN2

/*******************************************************************************
 *                         Function Prototypes                                 *
 *******************************************************************************/

/***************************************************************************************************
 * Function Name:         DcMotor_Init
 *
 * Description:           The Function responsible for setup the direction for the two motor pins using GPIO drivers.
 *
 * Arguments:             VOID
 *
 * Returns:               VOID
 ***************************************************************************************************/


void DcMotor_Init(void);

/***************************************************************************************************
 * Function Name:         DcMotor_Rotate
 *
 * Description:           The function is responsible for rotating the dc motor CW, A-CW or stop based on the state input state value .
 *
 * Arguments:              unsigned char state used to determine the state ( should be CW, A-CW or stop).
 * 						   unsigned char speed used to determine decimal value for the required motor speed, it should be from 0 -> 100
 *
 * Returns:                VOID
 ***************************************************************************************************/


void DcMotor_Rotate(DcMotor_State state,uint8 speed);




#endif /* DC_MOTOR_H_ */
