/*Module: PWM
 *File Name:pwm.h
 *Description:Header file for PWM Driver
 *Created on: Feb 25, 2022
 *Author:Haidy Raouf
 */

#ifndef PWM_H_
#define PWM_H_

#include "std_types.h"


/*******************************************************************************
 *                         Function Prototypes                                 *
 *******************************************************************************/


/***************************************************************************************************
 * Function Name:         Timer0_PWM_INIT
 *
 * Description:           The function responsible for trigger the Timer0 with the PWM Mode.
 *
 * Arguments:              duty_cycle: The required duty cycle percentage of the generated
 *                          PWM signal. Its value should be from 0 → 100
 *
 * Returns:               VOID
 ***************************************************************************************************/

void PWM_Timer0_Start(uint8 duty_cycle);



#endif /* PWM_H_ */
