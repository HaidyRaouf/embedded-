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
#include "timer.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include "avr/io.h" /* To use the IO Ports Registers */
#include "gpio.h"
#include "avr/interrupt.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*Timer0_ovf_Ptr)(void) = NULL_PTR;
static volatile void (*Timer0_comp_Ptr)(void) = NULL_PTR;
static volatile void (*Timer2_ovf_Ptr)(void) = NULL_PTR;
static volatile void (*Timer2_comp_Ptr)(void) = NULL_PTR;

/*******************************************************************************
 *                        Interrupt Service Routines                           *
 ******************************************************************************/
ISR(TIMER0_OVF)
{
	if(Timer0_ovf_Ptr != NULL_PTR)
	{
		/* Call the Call Back function in the application */
		(*Timer0_ovf_Ptr)();
	}
}


ISR(TIMER2_OVF)
{
	if(Timer2_ovf_Ptr != NULL_PTR)
	{
		/* Call the Call Back function in the application */
		(*Timer2_ovf_Ptr)();
	}
}

ISR(TIMER0_COMP)
{
	if(Timer0_comp_Ptr != NULL_PTR)
	{
		/* Call the Call Back function in the application */
		(*Timer0_comp_Ptr)();
	}
}


ISR(TIMER2_COMP)
{
	if(Timer2_comp_Ptr != NULL_PTR)
	{
		/* Call the Call Back function in the application */
		(*Timer2_comp_Ptr)();
	}
}

/*******************************************************************************
 *                         Call-back  Functions Definitions                    *
 ******************************************************************************/
void TIMER0_OVF_setCallBack(void(*a_ptr)(void))
{
	Timer0_ovf_Ptr= a_ptr;
}

void TIMER2_OVF_setCallBack(void(*a_ptr)(void))
{
	Timer2_ovf_Ptr= a_ptr;
}
void TIMER0_COMP_setCallBack(void(*a_ptr)(void))
{
	Timer0_comp_Ptr= a_ptr;
}



void TIMER2_COMP_setCallBack(void(*a_ptr)(void))
{
	Timer2_comp_Ptr= a_ptr;
}


/*******************************************************************************
 *                         Function Definitions                                *
 *******************************************************************************/



void TIMER0_init(TIMER_ConfigType *Config_Ptr)
{
	if ((Config_Ptr) -> mode == NORMAL)
	{
		/* To choose pre-scale */
		TCCR0 = (TCCR0 & 0xF8) | (Config_Ptr -> prescaler);
		/* Normal Mode */
		CLEAR_BIT(TCCR0,WGM00);
		CLEAR_BIT(TCCR0,WGM01);
		/* To choose the initial value */
		TCNT0= Config_Ptr -> value;
		/* To enable Interrupt */
		TIMSK = (1<<TOIE0);
	}
	else if (Config_Ptr -> mode == PWM)
	{
		/* To choose pre-scale */
				TCCR0 = (TCCR0 & 0xF8) | (Config_Ptr -> prescaler);
		/* PWM Mode */
		CLEAR_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		/* To choose the initial value */
		TCNT0= Config_Ptr -> value;

		/* To choose in Compare Output Mode for PWM:
		 *  Normal port operation, OC0 disconnected.
		 *  Reserved
		 *  Clear OC0 on compare match when up-counting. Set OC0 on compare
            match when downcounting.
		 *  Set OC0 on compare match when up-counting. Clear OC0 on compare
            match when downcounting.
		 */
		TCCR0 = (TCCR0 & 0xCF) | ((Config_Ptr -> outputMode)<<4);

		/* To enable Interrupt */
		TIMSK = (1<<TOIE0);
	}
	else if (Config_Ptr -> mode == CTC)
	{
		/* To choose pre-scale */
				TCCR0 = (TCCR0 & 0xF8) | (Config_Ptr -> prescaler);
		/* COMPARE Mode */
		SET_BIT(TCCR0,WGM01);
		/* To choose the initial value */
		TCNT0= Config_Ptr -> value;

		/* To choose in Compare Output Mode for non-PWM Mode:
		 *
		 *  Normal port operation, OC0 disconnected.
		 *
		 *  Toggle OC0 on compare match

		 *  Clear OC0 on compare match

		 *  Set OC0 on compare match
		 */
		TCCR0 = (TCCR0 & 0xCF) | ((Config_Ptr -> outputMode)<<4);

		/* To choose compare value */
		OCR0= Config_Ptr -> compValue;

		/* To enable Interrupt */
		TIMSK = (1<<TOIE0);
	}
}

void TIMER0_stop()
{
	/* Stop the Timer */
	TCCR0 = 0;
}


void TIMER2_init(TIMER_ConfigType *Config_Ptr)
{
	if (Config_Ptr -> mode == NORMAL)
	{
		/* To choose pre-scale */
				TCCR2 = (TCCR2 & 0xF8) | (Config_Ptr -> prescaler);
		/* Normal Mode */
		CLEAR_BIT(TCCR2,WGM20);
		CLEAR_BIT(TCCR2,WGM21);
		/* To choose the initial value */
		TCNT2= Config_Ptr -> value;
		/* To enable Interrupt */
		TIMSK = (1<<TOIE2);
	}
	else if (Config_Ptr -> mode == PWM)
	{
		/* To choose pre-scale */
				TCCR2 = (TCCR2 & 0xF8) | (Config_Ptr -> prescaler);
		/* PWM Mode */
		CLEAR_BIT(TCCR2,WGM20);
		SET_BIT(TCCR2,WGM21);
		/* To choose the initial value */
		TCNT2= Config_Ptr -> value;

		/* To choose in Compare Output Mode for PWM:
		 *  Normal port operation, OC0 disconnected.
		 *
		 *  Reserved

		 *  Clear OC0 on compare match when up-counting. Set OC0 on compare
            match when downcounting.

		 *  Set OC0 on compare match when up-counting. Clear OC0 on compare
            match when downcounting.
		 */
		TCCR2 = (TCCR2 & 0xCF) | ((Config_Ptr -> outputMode)<<4);

		/* To enable Interrupt */
		TIMSK = (1<<TOIE2);
	}
	else if (Config_Ptr -> mode == CTC)
	{
		/* COMPARE Mode */
		SET_BIT(TCCR2,WGM21);
		/* To choose pre-scale */
		TCCR2 = (TCCR2 & 0xF8) | (Config_Ptr -> prescaler);
		/* To choose the initial value */
		TCNT2= Config_Ptr -> value;

		/* To choose in Compare Output Mode for non-PWM Mode:
		 *
		 *  Normal port operation, OC0 disconnected.
		 *
		 *  Toggle OC0 on compare match

		 *  Clear OC0 on compare match

		 *  Set OC0 on compare match
		 */
		TCCR2 = (TCCR2 & 0xCF) | ((Config_Ptr -> outputMode)<<4);

		/* To choose compare value */
		OCR2= Config_Ptr -> compValue;

		/* To enable Interrupt */
		TIMSK = (1<<TOIE2);
	}
}

void TIMER2_stop(void)
{
	/* Stop the Timer */
	TCCR2=0;
}

