#include <avr/io.h>
int main()
{
unsigned int i, dly;

//high nibble for output(columns) low for input(rows);
DDRA = 0x10001011;
//DDRA = 0x01110100;

//enable internal pullups for PB0-PB3
PORTA= 0x0F;

//Port B for indication only
DDRB=0xFF;
//SFIOR = 0 << PUD;
PORTB=0xff;

unsigned Mask = DDRA;

void delay (unsigned int dly)
{
for(i = dly; i != 0; i--) ;
}

while (1) //loop key check forever
	{


		//first column
		PORTA =0b10111111;
		//check for rows and send key number to portD
		//instead sending key number to PORTD you can use
		// any function that serves pressed button
		
		// Not work
		// 00000111
		if (bit_is_set(PINA, 7)) {
		PORTB=0x01;
		delay(55000U);
		PORTB = 0xff;
		}
		// 00000011
		if (bit_is_set(PINA, 3)) {
		PORTB=0x02;
		delay(55000U);
		PORTB = 0xff;
		}
		// Not work
		if (bit_is_set(PINA, 2)) {
		PORTB=0x03;
		delay(65000U);
		PORTB = 0xff;
		}
		// Not work
		// 00000100
		if (bit_is_set(PINA, 4)) {
		PORTB=0x04;
		delay(65000U);
		PORTB = 0xff;
		}
/*

		//second column
		PORTA =0b11101111;
		// D
		if (!bit_is_set(PINA, 7)) PORTB=0x03;
		// Not work
		if (!bit_is_set(PINA, 3)) PORTB=0x04;
		// C
		if (!bit_is_set(PINA, 1)) PORTB=5;
		// B
		if (!bit_is_set(PINA, 0)) PORTB=6;


		//third column
		PORTA =0b00000000;
		// #
		if (!bit_is_set(PINA, 3)) PORTB=0x55;
		// Not work
		if (!bit_is_set(PINA, 2)) PORTB=0x55;
		// 9 
		if (!bit_is_set(PINA, 1)) PORTB=0x55;
		// 6
		if (!bit_is_set(PINA, 0)) PORTB=0x55;


		//fourth column
		PORTA =0b00000000;
		// 0
		if (!bit_is_set(PINA, 3)) PORTB=13;
		// 8
		if (!bit_is_set(PINA, 2)) PORTB=14;
		// Not work
		if (!bit_is_set(PINA, 1)) PORTB=15;
		// 5
		if (!bit_is_set(PINA, 0)) PORTB=16;
*/
	}
}
