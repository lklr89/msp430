/*
  Using 1 timer interrupt and 1 port (button) interrupt to control LEDs
  Author: lklr
*/

#include"msp430g2553.h"

int main() 
{
  // Setup buttons and LEDs..  
  WDTCTL = WDTPW | WDTHOLD;
  P1SEL = 0x00;
  P1DIR &= 0x00;
  P1OUT &= 0x00;

  P1DIR |= 0x41;
  P1DIR &= ~BIT3;
  P1REN |= BIT3;
  P1OUT &= ~(0x41);
  P1OUT |= BIT3;

  /*---------------
    TIMER INTERRUPT
  ----------------*/
  CCTL0 = CCIE; // CCTL0 = TACCTL0 = Timer A capture/compare control register 0 
                // CCIE = capture/compare interrupt enable
  TACTL = TASSEL_2 + MC_1 + ID_3; // TACTL = Timer A Control Register
                                  // TASSEL_2 Timer A clock source select -> SMCLK (Subsystem Master Clock) ~1,1MHz
                                  // MC_1 = Timer A Mode Control = count up
                                  // ID_3 = Timer A Input Divider = 8
  CCR0 = 65535; // Timer A capture/compare counting state
                // Interrupt frequency = 1,1 MHz / 8 / 65535 = 2,098 Hz

  /*----------------
    PORT INTERRUPT
  -----------------*/
  P1IE |= BIT3; // Interrupt Enable on P1.3 
  P1IES |= BIT3; // Interrupt Edge Select: Interrupt on HiLo edge on P1.3 
  P1IFG &= ~BIT3; // initialize Interrupt flag for P1.3 (to 0)

  // activate Global Interrupts
  _EINT();

  // activate Low Power Mode 0 
  _BIS_SR(CPUOFF + GIE); // deactiviate CPU , Global Interrupt Enable
  while(1);
}

volatile int count = 0;

/*----------------
    TIMER ISR
----------------*/
#pragma vector = TIMER0_A0_VECTOR // Start-address is µc-specific! (interrupt vector table)
__interrupt void ISR_TIMERA(void)
{
  count++;
  if (count == 10)
  {
    P1OUT ^= 0x40;
    count = 0;
  }
}

/*----------------
     PORT ISR
-----------------*/
#pragma vector = PORT1_VECTOR // Start-address is µc-specific! (interrupt vector table)
__interrupt void ISR_PORT1(void) 
{
  volatile int i;
  P1OUT ^= 0x40;
  for (i = 0; i < 32767; i++);
  P1OUT ^= 0x01;
  P1IFG &= ~BIT3;
}
