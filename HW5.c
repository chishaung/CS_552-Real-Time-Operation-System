/* RTOS Assignment 5 - LCD Dsiplay
 * Author: Chihsiang Wang
 * Description: PORTA - Control. PORTD - Data. LCD will display "HELLO WORLD!"
 * Code Size: 3.82KB
 */

#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL

void ReadData(char ch) {
    PORTA = 0x02;
    _delay_ms(50);
    PORTA = 0x03;
    _delay_ms(50);
    PORTD = ch;
    _delay_ms(50);
    PORTA = 0x02;
    _delay_ms(50);

}

void WriteData(char ch) {
    PORTD = 0x00;
    _delay_ms(50);
    PORTD = 0x01;
    _delay_ms(50);
    ReadData(ch);
    PORTD = 0x00;
    _delay_ms(50);
}

void Init() {
    // PORTA -> control, PORTD -> Data
    DDRA = 0xFF;
    DDRD = 0xFF;

    _delay_ms(80); // Wait until VDD reach 4.5V
    PORTA = 0x38;	// Function Set
    PORTA = 0x0F;	// Turn On Display
    PORTA = 0x01;	// Clear Display
    PORTA = 0x02;	// Return Home
}

int main()
{

	Init();
        PORTA = 0x00;
	WriteData('H');
	WriteData('E');
	WriteData('L');
	WriteData('L');
	WriteData('O');
	PORTA = 0x40;
	WriteData('W');
	WriteData('O');
	WriteData('R');
	WriteData('L');
	WriteData('D');
	WriteData('!');  	
}
