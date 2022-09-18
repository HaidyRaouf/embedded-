/*******************************************************************************
 *  [FILE NAME]: Main.c
 *
 *  [Author]: Haidy Raouf
 *
 *  [DATE CREATED]: Mar 21, 2022
 *
 *  [DESCRIPTION]: Application file for MC1
 *******************************************************************************/

#include "avr/delay.h"
#include "avr/io.h" /* To use the UART Registers */
#include "common_macros.h" /* To use the macros like SET_BIT */
#include "main.h"
#include "lcd.h"
#include "keypad.h"
#include "timer.h"
#include "uart.h"
#define F_CPU 8000000UL
#define PASSWORD_SIZE 5


/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
uint8 password[PASSWORD_SIZE];          // array for the pass //
uint8 first_time= 0;                 // pass for the first time //
uint8 checkpass[PASSWORD_SIZE];         // array for the copy of the password //
uint8 warning = 0;                   // for incorrect password attempts //
uint8 re_enter= 0;                   // for number of re-enterd password attempts //
uint8 passCount=0;                  // counts password //
uint8 reset =0;                      // Resets password //
uint8 option = 0;                    // for option menu //
uint8 tick=0;                      // for timer tick //
uint8 sec=0;
uint8 i = 0;
uint8 flag = 0;

/******************************************************************************/

TIMER_ConfigType Config_Ptr={F_CPU_256,CTC,DISCONNECTED,255,0};
void timerCallBack(void)
{
	tick++;
		if(tick < 122)
		{
			tick=0;
			sec++;
		}
}
void Menu()
{
	LCD_clearScreen();
	/*show Options available */
	LCD_displayStringRowColumn(0, 0, "+: Open Door");
	LCD_displayStringRowColumn(1, 0, "-: Change Pass");
	_delay_ms(500);
}
void get_password()
{
	for(i=0;i<PASSWORD_SIZE;i++)
	{
		if (KEYPAD_getPressedKey() < 10)
		{
			password[i]= KEYPAD_getPressedKey();
			LCD_displayCharacter('*');     /* display '*' for every entered number */
			_delay_ms(500);
			passCount++;
		}
	}
}
void reset_changes()
{
	LCD_clearScreen();
	first_time = passCount = re_enter = reset = flag = i = option = warning = 0;
}
void check_password()
{
	for(i = 0; i < PASSWORD_SIZE; i++)
	{
		if(checkpass[i] != password[i] )
		{
			reset_changes();
			LCD_displayString("Incorrect Password");
			_delay_ms(5000);
			LCD_clearScreen();
			first_time=0;
			re_enter=1;
			LCD_displayStringRowColumn(0, 0, "please Enter Password");
			LCD_moveCursor(1,0);
			get_password();
			warning++;
			/* if the password was wrong 3 times in a row */
			if (warning == 3)
			{
				wrong_password();
			}

		}
		/* if the two passwords match, save password */
		else
		{
			LCD_clearScreen();
			LCD_displayString("Correct Password");
			_delay_ms(500);
			LCD_clearScreen();
			flag = 1;                    /* To proceed to next option */
		}
	}
}

void change_password()
{
	LCD_clearScreen();
	LCD_displayString("please enter the old Password: ");
	LCD_moveCursor(1, 0);
	passCount=0;
	while (passCount < 5)
	{
		get_password();

		for(i = 0; i < PASSWORD_SIZE; i++)
		{
			/*sending signal to MC2 to save the sent data*/
			if(i == 0)
			{
				UART_sendByte('#');        /* '#' referenced to SAVE */
			}
		}
		/* Check received password */
		if (checkpass[i] != UART_recieveByte())
		{
			LCD_clearScreen();
			LCD_displayString("Wrong Password");
			warning++;
			_delay_ms(2000);
		}
		/* if the password entered correctly reset everything */
		if(i == 5)
		{
			reset_changes();
			UART_sendByte('R');     /* 'R' referenced to RESET */
			UART_sendByte(0xFF);    /*send the new value of re_enter*/
			_delay_ms(10);
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0, "Enter new Pass");
			LCD_moveCursor(1, 0);
			while (passCount < 5)
			{
				get_password();
			}
			LCD_clearScreen();
			if (re_enter == 1)
			{
				LCD_clearScreen();
				LCD_displayStringRowColumn(0, 0, "Enter again");
				for (i=0;i<PASSWORD_SIZE;i++)
				{
					checkpass[i]=password[i];
					password[i]=0;
				}
				i=0;
			}
			/* check the second and last attempt */
			if(re_enter == 2)
			{
				check_password();
			}


		}
		/* if the user entered password wrong 3 times in a row */
		if (warning == 3)
		{
			/* Enable Buzzer */
			UART_sendByte('B');     /* 'B' referenced to BUZZER */
			while (warning == 3)
			{
				LCD_displayStringRowColumn(0, 0, "WARNING!!");
				LCD_clearScreen();
			}
			LCD_displayStringRowColumn(1, 0, "Calling Security");
			TIMER0_init(&Config_Ptr);             /* start Timer0 */
			while(sec < 60);            /* Wait for one minute */
			TIMER0_stop();                    /* Disable TIMER0 */
			sec = 0;
			/* reset options variables only */
			option = i = warning = passCount=0;
		}
	}
}

void AppConfig()
{
	LCD_init();
	UART_configType Config_ptr={a8_BitData,One_Stop_Bit,NO_Parity};
	UART_init(UART_BAUD_RATE,&Config_ptr);

	TIMER0_init(&Config_Ptr);
	TIMER0_OVF_setCallBack(timerCallBack);
}


void open_door()
{
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "the Password entered is Correct");
	_delay_ms(3000);
	UART_sendByte('O');     /* 'O' referenced to OPEN DOOR */
	UART_sendByte('#');     /* send signal to MC2 to open the door */
	LCD_displayStringRowColumn(1, 0, "Opening the Door... ");

	sec=0;
	while(sec < 15);    /* wait for 15 seconds */
	LCD_displayStringRowColumn(1, 0, "Closing the Door... ");
	sec=0;
	while(sec < 15);    /* wait 15 seconds */
	sec=0;
	LCD_clearScreen();
	LCD_displayString("Press 'Enter' to return to Options" );
	while (option == '+' || option == '-')
	{
		if(KEYPAD_getPressedKey() == 13)
		{
			/* reset options variables only */
			option = i = warning = passCount = 0;
		}
	}
}

void wrong_password()
{
	/* Enable Buzzer */
	UART_sendByte('B');     /* 'B' referenced to BUZZER */
	while (warning == 3)
	{
		LCD_displayStringRowColumn(0, 0, "WARNING!!");
		LCD_clearScreen();
	}
	LCD_displayStringRowColumn(1, 0, "Calling Security");
	TIMER0_init(&Config_Ptr);             /* start Timer0 */
	while(sec < 60);            /* Wait for one minute */
	TIMER0_stop();                    /* Disable TIMER0 */
	sec = 0;
	option = i = warning = passCount=0;
}
int main()
{
	SREG |= (1<<7);     // Enable I-bit //

	AppConfig();
	UART_sendByte('E');   /* Send signal to MC2 to get re_enter value from EEPROM */
	re_enter=UART_recieveByte();
	/* if it is not equal to 2 then user didn't register password yet */
	if(re_enter !=2)
	{
		re_enter=0;
	}

	while (1)
	{
		if (first_time == 0 )
		{
			LCD_displayStringRowColumn(0, 0, "please Enter Password:");

			LCD_moveCursor(1, 0);
			while (passCount < 5)
			{
				get_password();
			}
		}
		LCD_clearScreen();
		first_time++;
		if (re_enter == 0)
		{
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0, "please Enter the Password again:");
			LCD_moveCursor(1, 0);                 /* Go to second row */
			passCount=0;
		}
		if(re_enter < 2)
		{
			re_enter++;
		}
		/* check the first re-entered attempt to save it to a new variable */
		if (re_enter == 1)
		{
			for (i=0;i<PASSWORD_SIZE;i++)
			{
				checkpass[i]=password[i];
				password[i]=0;
			}
			i=0;
		}
		/* check the second attempt */
		if(re_enter == 2)
		{
			check_password();
		}
		if(flag == 1)
		{
			first_time = 1;
			/* To send the correct password to MC2: */
			for(i=0;i<PASSWORD_SIZE;i++)
			{
				/*send a signal to MC2 to save the next sent data*/
				if(i == 0){
					UART_sendByte('S');        /* 'S' referenced to SAVE */
				}
				UART_sendByte(password[i]);        /*send password to MC2 to save it in EEPROM*/
			}
			LCD_clearScreen();
			LCD_displayString("the Password is Saved correctly");     /* show that the password is saved */
			_delay_ms(2000);                         /* show message for 2 seconds */
		}
		while (re_enter ==2 )
		{
			Menu();
			option = KEYPAD_getPressedKey();
			_delay_ms(1000);
			switch (option)
			{
			case '-':
				change_password();
				break;
			case'+':
				LCD_clearScreen();
				LCD_displayString("Enter Password");
				LCD_moveCursor(1, 0);

				passCount=0,i=0;
				while (passCount < 5)
				{
					get_password();
				}

				for(i = 0; i < PASSWORD_SIZE; i++)
				{
					/* get password from EEPROM and check it */
					if(i == 0)
					{
						UART_sendByte('#');
					}


				}
				/* Check received password */
				if (checkpass[i] != UART_recieveByte())
				{
					LCD_clearScreen();
					LCD_displayString("Wrong Password");
					warning++;
					_delay_ms(2000);
					LCD_clearScreen();
					first_time=0;
					re_enter=1;
					LCD_displayStringRowColumn(0, 0, "Enter Password");
					LCD_moveCursor(1,0);
					get_password();
				}

				/* if the entered password is correct, open the door */
				if(i == 5)
				{
					open_door();
				}
				/* if user entered password wrong 3 times in a row */
				if (warning == 3)
				{
					wrong_password();
				}

				break;
			default:
				LCD_clearScreen();
				LCD_displayString("Invalid Option");
				break;

			}
		}
	}
}


