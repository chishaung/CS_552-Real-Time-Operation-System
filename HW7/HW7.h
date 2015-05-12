#ifndef HW7_H
#define HW7_H
#define MAX_TASK 5

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


typedef struct _UIKSem {
    uint8_t value;
} UIKSem;

typedef struct Task_Control {

	void (*taskptr)();
	int Task_ID;
	int status;
	int Priority;
	uint8_t* stack_ptr;
	int init;		// If already Init, set to 1.
	UIKSem* Sem;

} Task_Control;

typedef struct Task_Control * TCBptr;





int ticknum = 0;
int Task_Numbers;
int Current_Task;
unsigned botton;
TCBptr TaskList[MAX_TASK];
uint16_t ticklen = 10000;
volatile uint8_t *currTCB;

void savecontext() __attribute__((naked));
void restorecontext() __attribute__((naked));
ISR(TIMER1_COMPA_vect) __attribute__((naked));
UIKSem* UIKSemCreate();
void UIKSemPend();	// wait
void SemPost();		// signal

void Task_1() {
	uint8_t cnt;
	while (1) {

		PORTB = ~0x01;
		_delay_ms(500);
		PORTB = ~0x02;
		_delay_ms(500);
		sei();
	}
}

void Task_2() {
	uint8_t cnt;
	while (1) {

		for ( cnt=0x0f; cnt >= 0x00; cnt-- )
		{
			PORTB = ~cnt;
			_delay_ms(500);
			sei();
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
		sei();
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
		sei();
	}
}

void UIKIdle() {
    while (1) {	
	PORTB = 0xFE;
	_delay_ms(300);
	PORTB = 0xFF;
	_delay_ms(500);
	sei();
    }
}

// Actually this is the Sem controller
void Change_Switch() {
    // SW0 -> Set Task1 Ready
    if (botton == 0b11111110) {
	TaskList[1]->status = 0;
	SemPost(TaskList[1]->Sem);
    }

    // SW1 -> Set Task2 Ready
    if (botton == 0b11111101) {
	TaskList[2]->status = 0;
	SemPost(TaskList[2]->Sem);
    }

    // SW2 -> Set Task3 Ready
    if (botton == 0b11111011) {
	TaskList[3]->status = 0;
	SemPost(TaskList[3]->Sem);
    }

    // SW3 -> Set Task4 Ready
    if (botton == 0b11110111) {
	TaskList[4]->status = 0;
	//TaskList[4]->Sem->value = 0;
	SemPost(TaskList[4]->Sem);
    }

    // SW4 -> Set Task1 Block
    if (botton == 0b11101111) {
	TaskList[1]->status = 1;
	//TaskList[1]->Sem->value = 1;
	UIKSemPend(TaskList[1]->Sem);
    }

    // SW5 -> Set Task2 Block
    if (botton == 0b11011111) {
	TaskList[2]->status = 1;
	UIKSemPend(TaskList[2]->Sem);
    }

    // SW6 -> Set Task3 Block
    if (botton == 0b10111111) {
        TaskList[3]->status = 1;
	UIKSemPend(TaskList[3]->Sem);
    }

    // SW7 -> Set Task4 Block
    if (botton == 0b01111111) {
	TaskList[4]->status = 1;
	UIKSemPend(TaskList[4]->Sem);
    }
}


#endif
