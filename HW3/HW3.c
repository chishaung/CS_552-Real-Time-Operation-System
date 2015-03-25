/*
 * Count from 0 to 0xff, output to leds ~cnt.
 */

#include <inttypes.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

int i;
uint8_t counter = 0xf0;
unsigned msec;
unsigned sec;

void init_Ex1(void)
  {

   DDRB  = 0xFF;                 // Set Port B as output
   TCCR0 = (1<<CS02)|(1<<CS00);  // Timer clock = Sysclk/1024 (TCCR0 = 0x05)
   TIFR  = 1<<TOV0;              // Clear TOV0, any pending interrupts
   TIMSK = 1<<TOIE0;             // Enable Timer0 Overflow interrupt

  } // END init_Ex1 

void delay (unsigned int dly)
  {
  
   for(i = dly; i != 0; i--) ;
  }

 ISR(TIMER0_OVF_vect)    // gcc syntax 

  {
	msec++;
	if (msec == 5) {
	    sec++;
	    msec = 0;
	    PORTB = PORTB ^ counter;
	}
	

  } // end ISR

int main(void)
{
    
    uint8_t cnt;
    init_Ex1();
    sei();

    DDRB = 0xff;                /* enable port b for output */

    while (1)
    for ( cnt=0; cnt <= 0xff; cnt++ )
      {
        PORTB = ~cnt;
        delay(65000U);
      }
   
    return(0);

}  // END main
 

