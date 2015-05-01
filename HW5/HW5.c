/* RTOS Assignment 5 - LCD Dsiplay
 * Author: Chihsiang Wang
 * Description: PORTA - Control. PORTD - Data. LCD will display "HELLO WORLD!"
 * Code Size: 1347 bytes(1.3K)
 */

#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL



void WriteData(char ch) {

    PORTA = 0x00;
    _delay_ms(50);
    PORTA = 0x02;
    _delay_ms(50);
    PORTD = ch;
    _delay_ms(50);
    PORTA = 0x03;
    _delay_ms(50);
    PORTA = 0x00;
}

void Init() {
    // PORTA -> control, PORTD -> Data

    Execute_Cmd(0x30);
    _delay_ms(80);
    Execute_Cmd(0x30);
    _delay_ms(80);
    Execute_Cmd(0x30);
    _delay_ms(80);

    Execute_Cmd(0x38);	// Function Set
    Execute_Cmd(0x0F);	// Turn On Display
    Execute_Cmd(0x02);	// Clear Display
    Execute_Cmd(0x01);	// Return Home
    
   

    _delay_ms(80);
    
}


void Execute_Cmd(unsigned cmd) {
    _delay_ms(100);
    PORTA = 0x01;	
    PORTD = cmd;
    PORTA = 0x00;	// E high
    _delay_ms(100);
    PORTA = 0x01;
}

int main()
{
	_delay_ms(80); // Wait until VDD reach 4.5V
        DDRA = 0xFF;
        DDRD = 0xFF;
	Init();
        
        //PORTD = 0x80;
	WriteData('H');
	WriteData('E');
	WriteData('L');
	WriteData('L');
	WriteData('O');
        Execute_Cmd(0xC0);
	WriteData('W');
	WriteData('O');
	WriteData('R');
	WriteData('L');
	WriteData('D');
	WriteData('!');  
        while(1);	
}

