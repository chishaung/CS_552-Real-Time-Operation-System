/* RTOS Assignment 4 - The 4x4 KeyPad driver
 * Author: Chihsiang Wang
 * Description: If the user enter the right password, the LED will 'Dance' for you. If enter the wrong password, the LED will blink for warning.
 * Password: 83AC or 69BD or 120#
 * Code Size: 3.82KB
 */

#include <avr/io.h>
#include <util/delay.h>
#define Display
#define F_CPU 16000000UL

void WriteData(char ch) {
	PORTD = ch;
	PORTA = 0x02;
	_delay_ms(1);
	PORTA = 0x03;
	_delay_ms(1);
	PORTA = 0x02;
	_delay_ms(100);
}

void Init() {
	// PORTA -> control, PORTD -> Data
	_delay_ms(80); // Wait until VDD reach 4.5V
	PORTD = 0x0F;
	PORTA = 0x30;
	_delay_ms(5);
	PORTA = 0x30;
	_delay_ms(5);
	PORTA = 0x30;
	_delay_ms(5);
	PORTA = 0x03;
	PORTA = 0x02;
	PORTA = 0x30;
	PORTA = 0x30;
}

int main()
{
	Init();
	WriteData('A');

	
}
