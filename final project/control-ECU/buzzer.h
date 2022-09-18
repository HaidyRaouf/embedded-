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
#include "avr/io.h"
#include "gpio.h"
#include "avr/delay.h"

/*******************************************************************************
 *                         Definitions                                         *
 *******************************************************************************/
#define BUZZER_PORT		PORTC_ID
#define BUZZER_PIN		PIN3_ID

/*******************************************************************************
 *                         Function Prototypes                                 *
 *******************************************************************************/

/***************************************************************************************************
 * [Function Name]:         Buzzer_init
 *
 * [Description]:           The Function is used for initializing the buzzer
 *
 * [Arguments]:             VOID
 *
 * [Returns]:               VOID
 ***************************************************************************************************/
void Buzzer_init(void);

/***************************************************************************************************
 * [Function Name]:         Buzzer_ON
 *
 * [Description]:           The Function is used for activating the buzzer
 *
 * [Arguments]:             VOID
 *
 * [Returns]:               VOID
 ***************************************************************************************************/
void Buzzer_ON(void);

/***************************************************************************************************
 * [Function Name]:         Buzzer_OFF
 *
 * [Description]:           The Function is used for Deactivating the buzzer
 *
 * [Arguments]:             VOID
 *
 * [Returns]:               VOID
 ***************************************************************************************************/
void Buzzer_OFF();
