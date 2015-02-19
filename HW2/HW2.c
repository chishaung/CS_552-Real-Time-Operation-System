
#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>


uint8_t cnt;                    // global variable

void init_Ex1(void)
  {

   DDRB  = 0xFF;                 // Set Port B as output
   //TCCR0 = (1<<CS02)|(1<<CS00);  // Timer clock = Sysclk/1024 (TCCR0 = 0x05)
   TCCR1B = (0x0004)/3;
   TIFR  = 1<<TOV1;              // Clear TOV0, any pending interrupts
   TIMSK = (1<<TOIE0) | (1<<TOIE1);             // Enable Timer0 Overflow interrupt

  } // END init_Ex1 


// void interrupt [TIMER0_OVF_vect] ISR_TOV0 (void)   IAR syntax


 ISR(TIMER1_OVF_vect)    // gcc syntax 

  {
   
   cnt++;
   PORTB = ~cnt;     // Toggle pins on Port B

  } // end ISR


int main(void)
{
    cnt = 0x00;
    init_Ex1();
    sei();

    while (1);
   
    return(0);

}  // END main
