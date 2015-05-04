#ifndef HW7_H
#define HW7_H
#define MAX_TASK 5
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

typedef struct Task_Control {

	void (*taskptr)();
	int Task_ID;
	int status;
	int Priority;
} Task_Control;

typedef struct Task_Control * TCBptr;


int ticklen;
int Task_Numbers;
int Current_Task;
TCBptr TaskList[MAX_TASK];



void Task_1() {
	uint8_t cnt;
	while (1) {
		for ( cnt=0; cnt <= 0x0f; cnt++ )
		{
			PORTB = ~cnt;
			_delay_ms(500);

		}
		
	}
}

void Task_2() {
	uint8_t cnt;
	while (1) {
		for ( cnt=0x0f; cnt >= 0x00; cnt-- )
		{
			PORTB = ~cnt;
			_delay_ms(500);
		}
	}
}

void Task_3() {
	uint8_t cnt;
	while (1) {

		if (PORTB == 0x00)
			PORTB = 0xff;
		PORTB = PORTB << 1;
		_delay_ms(500);

	}
}

void Task_4() {
	uint8_t cnt = 0x55;
	PORTB = 0x00;
	while (1) {
		
		PORTB = 0x55;
		_delay_ms(500);
		PORTB = 0xFF;
		_delay_ms(500);
	}
}

void UIKIdle() {
	while (1) {

		PORTB = 0xFE;
		_delay_ms(300);
		PORTB = 0xFF;
		_delay_ms(500);

	}
}



ISR(TIMER0_OVF_vect)    // gcc syntax

{
	//UIKDispatcher();
	
	while (PINA != 0xFF) {

		TaskList[1]->status = 0;

	}
	
	
	while (PINA == 0xFF) {

		TaskList[1]->status = 1;

	
	}
				
} // end ISR

#endif
