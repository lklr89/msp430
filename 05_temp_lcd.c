/*
 Measuring temperature with integrated ptc and display values on LCD screen (16x2)
 Author: lklr
*/

#include <stdlib.h>
#include <msp430g2553.h>
#include "lcd.h"
#include "adc_temperature.h"
 
void main(void)
{
 	WDTCTL = WDTPW + WDTHOLD;

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
