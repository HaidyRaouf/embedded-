 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Haidy Raouf
 *
 * Created on: Mar 20, 2022
 *
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"
#define UART_BAUD_RATE     9600

typedef enum{
	a5_BitData, a6_BitData, a7_BitData, a8_BitData, a9_BitData = 7
}UART_DataSize;

typedef enum{
	NO_Parity, Reserved, Even_Parity, Odd_Parity
}UART_ParityType;

typedef enum{
	One_Stop_Bit, Two_Stop_Bit
}UART_StopBit;

typedef struct{
	uint32 baud_rate;
	UART_ParityType parityType;
	UART_StopBit stopBit;
	UART_DataSize dataSize;
}UART_configType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(uint32 baud_rate, UART_configType *config_ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
