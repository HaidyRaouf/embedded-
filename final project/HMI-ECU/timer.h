/* Module:TIMER
 *
 * File Name:timer.h
 *
 * Description:Header file for Full Timer0 and Timer2 Driver
 *
 * Created on: Mar 20, 2022
 *
 * Author: Haidy Raouf
 *
 */


#ifndef TIMERS_H_
#define TIMERS_H_

#include "std_types.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include "avr/io.h" /* To use the IO Ports Registers */

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}Timer_prescaler;

typedef enum
{
	NORMAL,PWM,CTC,FAST_PWM
}Timer_Mode;


typedef enum
{
	DISCONNECTED,RESERVED_TIMER,NON_INVERTING,INVERTING
}Timer_OutputMode;

/************** structs **************/

typedef struct
{
	Timer_prescaler prescaler;
	Timer_Mode mode;
	Timer_OutputMode outputMode;
	uint8 value;             // initial value
	uint8 compValue;        // compare value
}TIMER_ConfigType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 ******************************************************************************/

/**************************** For TIMER0 **************************************/

/*******************************************************************************
 * [Function Name]:         ISR(TIMER0_OVF)
 *
 * [Description]:           The Function activate Interrupt for TIMER0 overflow
 *                          mode.
 *
 * [Returns]:               VOID
 ******************************************************************************/
void ISR(TIMER0_OVF);

/*******************************************************************************
 * [Function Name]:         ISR(TIMER0_COMP)
 *
 * [Description]:           The Function activate Interrupt for TIMER0 compare
 *                          mode.
 *
 * [Returns]:               VOID
 ******************************************************************************/
void ISR(TIMER0_COMP);

/*******************************************************************************
 * [Function Name]:         TIMER0_init
 *
 * [Description]:           The Function is used to Initialize TIMER0
 *
 * [Arguments]:             Pointer to structure TIMER_ConfigType
 *
 * [Returns]:               VOID
 ******************************************************************************/
void TIMER0_init(TIMER_ConfigType *Config_Ptr);

/*******************************************************************************
 * [Function Name]:         TIMER0_stop
 *
 * [Description]:           The Function is used to Stop TIMER0
 *
 * [Arguments]:             VOID
 *
 * [Returns]:               VOID
 ******************************************************************************/
void TIMER0_stop();

/******************************************************************************/

/**************************** For TIMER2 **************************************/

/*******************************************************************************
 * [Function Name]:         ISR(TIMER2_OVF)
 *
 * [Description]:           The Function activate Interrupt for TIMER2 overflow
 *                          mode.
 *
 * [Returns]:               VOID
 ******************************************************************************/
void ISR(TIMER2_OVF);

/*******************************************************************************
 * [Function Name]:         ISR(TIMER2_COMP)
 *
 * [Description]:           The Function activate Interrupt for TIMER2 compare
 *                          mode.
 *
 * [Returns]:               VOID
 ******************************************************************************/
void ISR(TIMER2_COMP);

/*******************************************************************************
 * [Function Name]:         TIMER2_init
 *
 * [Description]:           The Function is used to Initialize TIMER2
 *
 * [Arguments]:             Pointer to structure TIMER_ConfigType
 *
 * [Returns]:               VOID
 ******************************************************************************/
void TIMER2_init(TIMER_ConfigType *Config_Ptr);

/*******************************************************************************
 * [Function Name]:         TIMER2_stop
 *
 * [Description]:           The Function is used to Stop TIMER2
 *
 * [Arguments]:             VOID
 *
 * [Returns]:               VOID
 ******************************************************************************/
void TIMER2_stop();


/*******************************************************************************
 *                         Call-back  Functions Prototypes                     *
 ******************************************************************************/
void TIMER0_OVF_setCallBack(void(*a_ptr)(void));
void TIMER2_OVF_setCallBack(void(*a_ptr)(void));
void TIMER0_COMP_setCallBack(void(*a_ptr)(void));
void TIMER2_COMP_setCallBack(void(*a_ptr)(void));

#endif /* TIMERS_H_ */
