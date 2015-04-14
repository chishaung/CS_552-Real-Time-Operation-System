#include <avr/io.h>
#include <util/delay.h>



#define BIT(i) 	(1 << i)

#define ROW_MASK	0b00111100		// mask PD[2..5]
#define PORTD_MASK	0b11000000		// mask PD[6..7]
#define PORTB_MASK	0b00000011		// mask PB[0..1]



int main()
{	
	uint8_t COL_MASK;
	uint8_t TEST;
	DDRB = 0xFF;
	PORTB = 0xFF;
	
	// 1 2 3 4 5 6 7 8
	// R R C R C C C R

	// 8 7 6 5 4 3 2 1
	// R C C C R C R R
	
	// Set Row as Input, Column as Output
	DDRA =  0b10001011;
	// Pullup
	PORTA = 0b01110100;


	while (1) {

	    // If Row 2 Pressed
	    TEST = 0b01000000;
	    
	    if (!(PINA & TEST)) {
		PORTA = 0b01000000;
		// Col
		if (bit_is_set(PINA, 1)){
	            PORTB = ~0x12;
		    _delay_ms(2);
		    PORTB = 0xFF;
		}
		

		if (bit_is_set(PINA, 3)){
	            PORTB = ~0x22;
		    _delay_ms(2);
		    PORTB = 0xFF;
		}

	    }
PORTA = 0b01110100;
	    
	    // If Row 2 Pressed
	    TEST = 0b00100000;
	    
	    if (!(PINA & TEST)) {

	        PORTB = ~0x02;
		_delay_ms(2);
		PORTB = 0xFF;
	    }
	    
	    // If Row 2 Pressed
	    TEST = 0b00010000;
	
	    if (!(PINA & TEST)) {
 
	        PORTB = ~0x04;
		_delay_ms(2);
		PORTB = 0xFF;
	    }

            // If Row 2 Pressed
	    TEST = 0b00000100;
	    
	    if (!(PINA & TEST)) {

	        PORTB = ~0x08;
		_delay_ms(2);
		PORTB = 0xFF;
	    }
	}
}
