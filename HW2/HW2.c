
#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>



unsigned int counter = 0;
unsigned Temp;
int control;

void init_Ex1(void)
  {

   DDRD = 0x00; // input
   DDRB = 0xFF; // Set Port B as output
   TCCR0 = (1<<CS02)|(1<<CS00); // Timer clock = Sysclk/1024 (TCCR0 = 0x05)
   TIFR = 1<<TOV0; // Clear TOV0, any pending interrupts
   TIMSK = 1<<TOIE0; // Enable Timer0 Overflow interrupt
   counter = 0;
   control = 0;

  } // END init_Ex1 


// void interrupt [TIMER0_OVF_vect] ISR_TOV0 (void)   IAR syntax


 ISR(TIMER0_OVF_vect)    // gcc syntax 

  {
   
   if (control == 1)
	counter++;
   if (control == 2)
	counter--; 

  } // end ISR


int main(void)
{
    init_Ex1();
    sei();


    while(1) {

        PORTB = 0xff;
        counter = 0;
        control = 0;

        while (PIND != 0xff) {
            control = 1;
            if (PIND != 0xff)
                Temp = PIND;

        }


        if (control == 1) {
            control = 2;
            while (counter > 0) {
                PORTB = Temp;
            }
        }
    }
   
    return(0);

}  // END main
