#include <avr/io.h>
#include <util/delay.h>



#define BIT(i) 	(1 << i)

#define ROW_MASK	0b00111100		// mask PD[2..5]
#define PORTD_MASK	0b11000000		// mask PD[6..7]
#define PORTB_MASK	0b00000011		// mask PB[0..1]



int main()
{	
	uint8_t MASK;
	uint8_t TEST;
	DDRB = 0xFF;
	PORTB = 0xFF;
	// 1 2 3 4 5 6 7 8
	// R R C R C C C R

	// 8 7 6 5 4 3 2 1
	// R C C C R C R R

	DDRA =  0b10001011;
	PORTA = 0b01110100;
	while (1) {
	    
	    if (PINA == 0b00110100) {
	        PORTB = 0x01;
		_delay_ms(2);
		PORTB = 0xFF;
	    }

	    if (PINA == 0b01010100) {
	        PORTB = 0x02;
		_delay_ms(2);
		PORTB = 0xFF;
	    }

	    if (PINA == 0b01100100) {
	        PORTB = 0x03;
		_delay_ms(2);
		PORTB = 0xFF;
	    }

	    if (PINA == 0b01110000) {
	        PORTB = 0x04;
		_delay_ms(2);
		PORTB = 0xFF;
	    }

	}
}
