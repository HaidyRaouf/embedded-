/*******************************************************************************
 *  [FILE NAME]: MAIN.c
 *
 *  [Author]: Haidy Raouf
 *
 *  [DATE CREATED]: Mar 21, 2022
 *
 *  [DESCRIPTION]: Application file for MC2
 *******************************************************************************/
#include "avr/delay.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include "timer.h"
#include "uart.h"
#include "eeprom.h"
#include "buzzer.h"
#include "i2c.h"
#include "dc-motor.h"
#include "avr/io.h" /* To use the UART Registers */
#define F_CPU 8000000UL



/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
uint8 tick=0;
uint8 sec=0;
uint8 value=0;
uint8 state=0;
uint16 address = 0x0000;        // Address which EEPROM is going to read //
TIMER_ConfigType Config_Ptr={F_CPU_256,CTC,DISCONNECTED,255,0};

void timerCallBack()
{
	tick++;
	if(tick < 122)
	{
		tick=0;
		sec++;
	}
}

void AppConfig()
{
	UART_configType Config_ptr={a8_BitData,One_Stop_Bit,NO_Parity};
	UART_init(UART_BAUD_RATE,&Config_ptr);


	TIMER0_init(&Config_Ptr);
	TIMER0_OVF_setCallBack(timerCallBack);
	DcMotor_Init();
	Buzzer_init();
}

void Motor_Delay()
{
	/*8000000 / 256 = 255 Hz
      compare value will be 7813 to produce an interrupt every 1 second
	 */
	sec=0;
	/* if the door is being opened (wait for 15 seconds ) */
	DcMotor_Rotate(Clockwise);
	while(sec < 15);
	sec = 0;
	/* let the door be opened for 3 seconds */
	DcMotor_Rotate(Stop);
	while(sec < 3);
	sec = 0;

	/* door is locking for 15 seconds */
	DcMotor_Rotate(Anti_Clockwise);
	while(sec < 15);

	DcMotor_Rotate(Stop);
	TIMER0_stop();
	state = 0;
}



int main()
{
	/* Enable Global Interrupt */
	SREG|=(1<<7);
	AppConfig();
	uint8 password[5],i=0;
	I2C_ConfigType ptr={F_CPU_1};
	TWI_init(&ptr);

	while(1)
	{
		/* Receive state from MC1 */
		state = UART_recieveByte();
		if(state == 'E');
		{
			/* read value of address 0x0000 from EEPROM */
			EEPROM_readByte(0x0000, &value);
			_delay_ms(10);
			UART_sendByte(value);  /* send value back to MC1 */
			state=0;
		}
		/* To receive saved Password from MC1: */
		if(state == 'S')
		{
			for(i=0;i<5;i++)
			{
				EEPROM_writeByte(++address, password[i]);
				_delay_ms(10);
			}
			state=0;
			address=0x0000;
		}
		/* if password entered correctly reset everything */
		if(state == 'R')
		{
			/* read password from EEPROM */
			EEPROM_readByte(address, UART_recieveByte());
			_delay_ms(10);
			state=0;
		}
		/* To send the saved Password to MC1 */
		if(state == '#')
		{
			for(i=0;i<5;i++)
			{
				EEPROM_writeByte(++address, &password[i]);
				_delay_ms(100);
			}
			for(i=0;i<5;i++)
			{
				/* send the saved password to MC1 */
				UART_sendByte(password[i]);
			}
			state=0;
		}
		/* To Open door: */
		if(state == 'O')
		{
			Motor_Delay();
		}
		/* To activate Buzzer */
		if(state == 'B')
		{
            sec++;
			Buzzer_ON();
			while(sec < 60);    // wait 1 minute //
			TIMER0_stop();
			Buzzer_OFF();      // disable buzzer //
			sec = 0;
			state = 0;
		}
	}
}
