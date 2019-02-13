/*
  Reading the internal temperature sensor with the A/D converter (AD10)
  and trigger LED at threshold
  
  Author: lklr
*/

#include"msp430g2553.h"

void tempInit()
{
    ADC10CTL0 = SREF_1 + REFON + ADC10ON + ADC10SHT_3 ; // ADC10 Control Register 0
    // SREF_1 -> select Reference, 1 -> V+ = Vref+, V- = Vss
    // ADC10SHT sample and hold time, 3 -> 16x ADC10CLKs

    ADC10CTL1 = INCH_10 + ADC10DIV_3; // ADC10 Control Register 1
    // INCH_10 -> Input Channel Select. 10 -> temperature sensor
    // ADC10DIV_3 -> Clock Divider /3
}

int tempOut()
{
    int t = 0;
    __delay_cycles(1000);            // wait for ref to settle
    ADC10CTL0 |= ENC + ADC10SC;      // enable conversion and start conversion
    while(ADC10CTL1 & BUSY);         // while busy converting
    t = ADC10MEM;                       // store in t
    ADC10CTL0 &= ~ENC;                     // disable adc conversion
    return(int) ((t * 27069L - 18169625L) >> 16); // convert and pass
}

int main(void)
{   
    volatile int temp;
    WDTCTL = WDTPW + WDTHOLD;
    temp=0;
    tempInit();
    P1SEL = 0x00;
    P1DIR |= 0x40;

    while(1)
    {
        __delay_cycles(500);  // wait and set breakpoint
        temp=tempOut();        // read temp
        __delay_cycles(500000); // wait and set breakpoint
        if (temp > 35)
        P1OUT ^= 0x40;
    }
    return 0;
}
