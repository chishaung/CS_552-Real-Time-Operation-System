/* RTOS Assignment 4 - The 4x4 KeyPad driver
 * Author: Chihsiang Wang
 * Description: If the user enter the right password, the LED will 'Dance' for you. If enter the wrong password, the LED will blink for warning.
 * Password: 83AC or 69BD or 120#
 * Code Size
 */

#include <avr/io.h>
#include <util/delay.h>

void Right_Password() {
	
	uint8_t inc = 0;
	for (int i = 0; i < 10; i++) {
		PORTB = 0xFE; 
		_delay_ms(50);
		PORTB = PORTB^inc;
		_delay_ms(50);
		inc+= 10;
	}
	PORTB = 0xFF;		
	
}

void Wrong_Password() {
	
	for (int i = 0; i < 5; i++) {
		PORTB = 0x00;
		_delay_ms(100);
		PORTB ^= 0xFF;
		_delay_ms(100);
		PORTB ^= 0xFF;
		_delay_ms(100);
	}	
	
}

void Set_LED() {
	DDRB = 0xFF;
	PORTB = 0xFF;
}

void Set_Col() {
	// Set Row as Input, Column as Output
	DDRA =  0b10001011;
	// Pullup
	PORTA = 0b01110100;
}

int Get_Col(){
	uint8_t TEST;
	int Col_Pressed = 0;
	
		// If Col 4 Pressed
		TEST = 0b01000000;		
		if (!(PINA & TEST)) 
			Col_Pressed = 4;

		// If Col 3 Pressed
		TEST = 0b00100000;
		if (!(PINA & TEST)) 
			Col_Pressed = 3;
		
		// If Col 2 Pressed
		TEST = 0b00010000;
		if (!(PINA & TEST)) 
			Col_Pressed = 2;

		// If Col 1 Pressed
		TEST = 0b00000100;
		if (!(PINA & TEST)) 
			Col_Pressed = 1;
		
	return Col_Pressed;
}

void Set_Row() {
	// Set Row as Input, Column as Output
	DDRA = 0b01110100; 
	// Pullup
	PORTA = 0b10001011;
}

int Get_Row(){
	uint8_t TEST;
	int Row_Pressed = 0;

	// If Row 1 Pressed
	TEST = 0b10000000;
	if (!(PINA & TEST)) 
		Row_Pressed = 1;

	// If Row 4 Pressed
	TEST = 0b00001000;
	if (!(PINA & TEST)) 
		Row_Pressed = 4;
	
	// If Row 3 Pressed
	TEST = 0b00000010;
	if (!(PINA & TEST)) 
		Row_Pressed = 3;

	// If Row 2 Pressed
	TEST = 0b00000001;
	if (!(PINA & TEST)) 
		Row_Pressed = 2;
	
	return Row_Pressed;
}

char Get_Key(int Col_Pressed, int Row_Pressed) {
	char key;
	if (Col_Pressed == 1) { 
		if (Row_Pressed == 1) 
			key = '1';	
		
		if (Row_Pressed == 2) 
			key = '4';
		
		if (Row_Pressed == 3) 
			key = '7';
		
		if (Row_Pressed == 4) 
			key = '*';
	}	
		
	else if (Col_Pressed == 2) {
		if (Row_Pressed == 1) 
			key = '2';
		
		if (Row_Pressed == 2) 
			key = '5';
		
		if (Row_Pressed == 3) 
			key = '8';
		
		if (Row_Pressed == 4) 
			key = '0';
	}
	
	else if (Col_Pressed == 3) {
		if (Row_Pressed == 1)
		key = '3';
		
		if (Row_Pressed == 2)
		key = '6';
		
		if (Row_Pressed == 3)
		key = '9';
		
		if (Row_Pressed == 4)
		key = '#';
	}
	
	else if (Col_Pressed == 4) {
		if (Row_Pressed == 1)
		key = 'A';
		
		if (Row_Pressed == 2)
		key = 'B';
		
		if (Row_Pressed == 3)
		key = 'C';
		
		if (Row_Pressed == 4)
		key = 'D';
	}
	
	else 
		key = '?';
		
	return key;
}

int main()
{
	int Col_Pressed = 0;
	int Row_Pressed = 0;
	char key = '?';
	char password[4];
	int i = 0;
	Set_LED();
	
	
	while (1) {
		Set_Col();
		Col_Pressed = Get_Col();
		

		
		Set_Row();
		Row_Pressed = Get_Row();
		

		
		key = Get_Key(Col_Pressed, Row_Pressed);
		if (i != 4 && key != '?') {
			
			if (PORTB == 0xFF)
			PORTB = ~0x01;
			else
			PORTB = PORTB << 1;
			
			password[i] = key;
			if (i != 4)
			i++;
			_delay_ms(200);
		}		
		
		if (i == 4) {
			//83AC or 69BD or 120#
			if (
			(password[0] == '8' && password[1] == '3' && password[2] == 'A' && password[3] == 'C') ||
			(password[0] == '6' && password[1] == '9' && password[2] == 'B' && password[3] == 'D') ||
			(password[0] == '1' && password[1] == '2' && password[2] == '0' && password[3] == '#')
			) {
				Right_Password();				
			}
		
			else {
				Wrong_Password();				
			}		
		_delay_ms(200);
		i = 0;
		PORTB = 0xFF;
		}		
		
		
		if (PORTB == 0xF0)
			PORTB = 0xFF;
		Col_Pressed = 0;
		Row_Pressed = 0;
		key = '?';
	}
}
