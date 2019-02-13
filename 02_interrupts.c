#include"msp430g2553.h"

volatile int count = 0;

int main() {

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
  CCTL0 = CCIE; // CCTL0 = TACCTL0 = Timer A capture/compare control 0
                // CCIE = capture/compare interrupt enable
  TACTL = TASSEL_2 + MC_1 + ID_3; // TACTL = Timer A Control Register
                                  // TASSEL_2 Timer A clock source select -> SMCLK (Subsystem Master Clock) ~1,1MHz
                                  // MC_1 = Timer A Mode Control = aufwärts zählen
                                  // ID_3 = Timer A Input Divider = 8
  CCR0 = 65535; // Timer A capture/compare Zählwert
                // Interrupt Frequenz = 1,1 MHz / 8 / 65535 = 2,098 Hz

  /*----------------
    PORT INTERRUPT
  -----------------*/
  P1IE |= BIT3; // Interrupt Enable: Interrupt auf P1.3 ermöglichen
  P1IES |= BIT3; // Interrupt Edge Select: Interrupt auf HiLo Signal-Flanke bei P1.3 ansetzen
  P1IFG &= ~BIT3; // Interrupt flag für P1.3 auf 0 initialisieren

  // Global Interrupts aktivieren
  _EINT();

  // Low Power Modus 0 aktivieren -
  _BIS_SR(CPUOFF + GIE); // CPU deaktivieren, Global Interrupt Enable
  while(1);
}

/*----------------
    TIMER ISR
----------------*/
#pragma vector = TIMER0_A0_VECTOR
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
#pragma vector = PORT1_VECTOR // Startadresse "0xFFE4 Port 1" der ISR festgelegt, µc-spezifisch!
__interrupt void ISR_PORT1(void) // Interrupt Funktion
{
  volatile int i;
  P1OUT ^= 0x40;
  for (i = 0; i < 32767; i++);
  P1OUT ^= 0x01;
  P1IFG &= ~BIT3;
}
