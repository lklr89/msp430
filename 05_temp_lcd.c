/* LCD_own.c
* Created on: 21-MAR-2018
* Author: leo
* Temperaturmessung mit MSP430 integriertem ptc + Anzeige auf LCD Screen.
*/
#include <stdlib.h>
#include <msp430g2553.h>
#include "lcd.h"
#include "adc_temperature.h"
 
void main(void)
{
 	WDTCTL = WDTPW + WDTHOLD; // stop watchdog timer

	volatile int temp;
	unsigned char buffer[5];

	tempInit();
	P1SEL = 0x00;
	P1DIR |= 0x40;

	lcd_init();
	send_strint("Temperatur: ");
	send_command(0xC0);
	while(1)
	{
		delay(100);
		temp = tempOut();
		itoa(temp,buffer,10);
		delay(100);
		send_command(0xC0);
		send_string(buffer);
		send_string(" *C");

	}
}
