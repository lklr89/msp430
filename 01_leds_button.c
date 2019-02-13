/*
  test.c

  Created on: 20.04.2017
       Author: lklr
*/
#include"msp430g2553.h"

int main(void) {
  volatile int i;

  // stop watchdog timer
  WDTCTL = WDTPW | WDTHOLD;
  // P1 as digital IO
  P1SEL = 0x00;
  // set up bit 0 of P1 as output
  P1DIR |= 0x41; // =BIT6 (0x40) AND BIT0 (0x01)
  // set BIT3 (Button S2) 0 -> input
  P1DIR &= ~BIT3;
  // activate Pull-up 
  P1REN |= BIT3;
  // set BIT0 and BIT6 to 0 
  P1OUT &= ~(0x41);
  // initialize BIT3 to 1 
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
