// CS 552 Real Time Operation System
// Chihsiang Wang 101-64106
// Assignment 1


#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>


unsigned int counter = 0;
int load;
unsigned Temp;

void init_Ex1(void)
{

	DDRD = 0x00;				  // input
	DDRB  = 0xFF;                 // Set Port B as output
	TCCR0 = (1<<CS02)|(1<<CS00);  // Timer clock = Sysclk/1024 (TCCR0 = 0x05)
	TIFR  = 1<<TOV0;              // Clear TOV0, any pending interrupts
	TIMSK = 1<<TOIE0;             // Enable Timer0 Overflow interrupt

} // END init_Ex1


// void interrupt [TIMER0_OVF_vect] ISR_TOV0 (void)   IAR syntax


ISR(TIMER0_OVF_vect)    // gcc syntax

{	
	counter++;
		
} // end ISR

int main (void) {
	
	
	unsigned int counter2;
	
	init_Ex1();
	sei();
	counter = 0;
	
	while(1) {
		PORTB = 0xff;
		
		counter = 0;
		counter2 = 0;
		while (PIND != 0xff) {
			if (PIND != 0xff)
			Temp = PIND;
		}
		counter2 = counter;
		counter = 0;
		

		while (counter2 == counter) {
		PORTB = Temp;
	
		}		
					
	}
	


	return 0;
}
