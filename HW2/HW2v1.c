// CS 552 Real Time Operation System
// Chihsiang Wang 101-64106
// Assignment 1


#include <inttypes.h>
#include <avr/io.h>
#include <avr/pgmspace.h>



void delay(unsigned int dly) {

    int i;
    for (i = dly; i != 0; i--);
	
}

void timer0_init() {

    TCCR0 |= (1 << CS00);
    TCNT0 = 0;
}

int main (void) {

    uint8_t cnt;
    DDRB = 0xff; // output
    DDRD = 0x00; // input 
    unsigned int time;
    uint8_t i;
    double timer = 0;
    unsigned Temp;

    while(1) {
	
	PORTB = 0xff;

	while (PIND != 0xff) {
            timer++;
	    if (PIND != 0xff)
	    Temp = PIND;
 	}

	delay(16000U);

	while (timer > 0) {
            PORTB = Temp;
	    timer--;
        }
	}
	PORTB = 0xff;
	timer = 0;
    
	 


return 0;
}
