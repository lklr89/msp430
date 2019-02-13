/*
  test.c

  Created on: 20.04.2017
       Author: leo
*/
#include"msp430g2553.h"

int main(void) {
  volatile int i;

  // stop watchdog timer
  WDTCTL = WDTPW | WDTHOLD;
  // P1 als digitalen IO
  P1SEL = 0x00;
  // set up bit 0 of P1 as output
  P1DIR |= 0x41; //=BIT6 (0x40) UND BIT0 (0x01)
  //BIT3 (Taster S2) auf 0 setzen -> input
  P1DIR &= ~BIT3;
  //Pull-up aktivieren
  P1REN |= BIT3;
  // BIT0 und BIT6 auf 0 initialisieren
  P1OUT &= ~(0x41);
  // BIT3 auf 1 initialisieren
  P1OUT |= BIT3;


  // loop forever
  while(1)
  {
    if (!(P1IN & BIT3))
    {
      // toggle bit 0 of P1
      P1OUT ^= 0x40;
      // delay for a while
      for (i = 0; i < 32000; i++);
      P1OUT ^= 0x01;
      while(!(P1IN & BIT3));
    }
  }
}
