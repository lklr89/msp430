/*
  Control Launchpad LEDs with button S2
       Author: lklr
*/
#include"msp430g2553.h"

int main(void) {
  volatile int i;

  // stop watchdog timer
  WDTCTL = WDTPW | WDTHOLD;
  
  // use P1 as digital IO
  P1SEL = 0x00;
  
  // activate BIT0 and BIT6 as output 
  P1DIR |= 0x41; // =BIT6 (0x40) AND BIT0 (0x01)
  
  // set BIT3 (button S2) 0 -> input
  P1DIR &= ~BIT3;
  
  // activate Pull-up for button 
  P1REN |= BIT3;
  
  // set BIT0 and BIT6 to 0 
  P1OUT &= ~(0x41);
  
  // initialize BIT3 (button S2) to 1 
  P1OUT |= BIT3;

  while(1)
  {
    if (!(P1IN & BIT3))
    {
      // toggle bit 0 of P1
      P1OUT ^= 0x40;
      // delay for a while
      for (i = 0; i < 32000; i++);
      // toggle bit 6 of P1
      P1OUT ^= 0x01;
      while(!(P1IN & BIT3));
    }
  }
}
