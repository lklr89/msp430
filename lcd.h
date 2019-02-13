/*  8bitlcd.h
 *  Created on: 12-Nov-2013
 *  Author: Manpreet
 */
#ifndef lcd_h
#define lcd_h lcd_h
 
#define DR          P2OUT = P2OUT | BIT0        // define RS high
#define CWR         P2OUT = P2OUT &(~BIT0) // define RS low
#define READ        P2OUT = P2OUT | BIT1    // define Read signal R/W = 1 for reading
#define WRITE       P2OUT = P2OUT &(~BIT1)     // define Write signal R/W = 0 for writing
#define ENABLE_HIGH P2OUT = P2OUT | BIT2        // define Enable high signal
#define ENABLE_LOW  P2OUT = P2OUT &(~BIT2)     // define Enable Low signal

unsigned int i;
unsigned int j;

void delay(unsigned int k);
void data_write(void);
void data_read(void);
void check_busy(void);
void send_command(unsigned char cmd);
void send_data(unsigned char data);
void send_string(char *s);
void send_int(int i);
void lcd_init(void);

#endif
