#ifndef HW7_H
#define HW7_H
#define MAX_TASK 5

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define savecontext()                           \
asm volatile   ( "push  r0               \n\t"    \
                 "in    r0, __SREG__     \n\t"    \
                 "cli                    \n\t"    \
                 "push  r0               \n\t"    \
                 "push  r1               \n\t"    \
                 "clr   r1               \n\t"    \
                 "push  r2               \n\t"    \
                 "push  r3               \n\t"    \
                 "push  r4               \n\t"    \
                 "push  r5               \n\t"    \
                 "push  r6               \n\t"    \
                 "push  r7               \n\t"    \
                 "push  r8               \n\t"    \
                 "push  r9               \n\t"    \
                 "push  r10              \n\t"    \
                 "push  r11              \n\t"    \
                 "push  r12              \n\t"    \
                 "push  r13              \n\t"    \
                 "push  r14              \n\t"    \
                 "push  r15              \n\t"    \
                 "push  r16              \n\t"    \
                 "push  r17              \n\t"    \
                 "push  r18              \n\t"    \
                 "push  r19              \n\t"    \
                 "push  r20              \n\t"    \
                 "push  r21              \n\t"    \
                 "push  r22              \n\t"    \
                 "push  r23              \n\t"    \
                 "push  r24              \n\t"    \
                 "push  r25              \n\t"    \
                 "push  r26              \n\t"    \
                 "push  r27              \n\t"    \
                 "push  r28              \n\t"    \
                 "push  r29              \n\t"    \
                 "push  r30              \n\t"    \
                 "push  r31              \n\t"    \
                 "lds  r26, currTCB      \n\t"    \
                 "lds  r27, currTCB+1    \n\t"    \
                 "in    r0, __SP_L__         \n\t"	\
                 "st    x+, r0           \n\t"	\
                 "in    r0, __SP___         \n\t"	\
                 "st    x+, r0           \n\t"	\
        );

#define restorecontext()					\
asm volatile (      "lds    r26, currTCB               \n\t"	\
                    "lds    r27, currTCB+1             \n\t"	\
                    "ld     r28, x+                    \n\t"	\
                    "out    __SP_L__, r28              \n\t"	\
                    "ld        r29, x+                 \n\t"	\
                    "out    __SP_H__, r29              \n\t"	\
                    "pop    r31                        \n\t"	\
                    "pop    r30                        \n\t"	\
                    "pop    r29                        \n\t"	\
                    "pop    r28                        \n\t"	\
                    "pop    r27                        \n\t"	\
                    "pop    r26                        \n\t"	\
                    "pop    r25                        \n\t"	\
                    "pop    r24                        \n\t"	\
                    "pop    r23                        \n\t"	\
                    "pop    r22                        \n\t"	\
                    "pop    r21                        \n\t"	\
                    "pop    r20                        \n\t"	\
                    "pop    r19                        \n\t"	\
                    "pop    r18                        \n\t"	\
                    "pop    r17                        \n\t"	\
                    "pop    r16                        \n\t"	\
                    "pop    r15                        \n\t"	\
                    "pop    r14                        \n\t"	\
                    "pop    r13                        \n\t"	\
                    "pop    r12                        \n\t"	\
                    "pop    r11                        \n\t"	\
                    "pop    r10                        \n\t"	\
                    "pop    r9                         \n\t"	\
                    "pop    r8                         \n\t"	\
                    "pop    r7                         \n\t"	\
                    "pop    r6                         \n\t"	\
                    "pop    r5                         \n\t"	\
                    "pop    r4                         \n\t"	\
                    "pop    r3                         \n\t"	\
                    "pop    r2                         \n\t"	\
                    "pop    r1                         \n\t"	\
                    "pop    r0                         \n\t"	\
                    "out    __SREG__, r0               \n\t"	\
                    "pop    r0                         \n\t"	\
                );	


typedef struct Task_Control {

	void (*taskptr)();
	int Task_ID;
	int status;
	int Priority;
	uint8_t* stack_ptr;
} Task_Control;

typedef struct Task_Control * TCBptr;


int ticklen;
int Task_Numbers;
int Current_Task;
unsigned botton;
volatile uint8_t *currTCB;
TCBptr TaskList[MAX_TASK];



void Task_1() {
	uint8_t cnt;
	while (1) {
		
		for ( cnt=0; cnt <= 0x0f; cnt++ )
		{
			PORTB = ~cnt;
			_delay_ms(300);
			sei();	
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


ISR(TIMER0_OVF_vect)    // gcc syntax

{

	Check_Switch();
	// SW0 -> Set Task1 Ready
	if (botton == 0b11111110) {
		TaskList[1]->status = 0;
		//currTCB = TaskList[1]->stack_ptr;
		//savecontext();
		UIKDispatcher();
		sei();
	}
	// SW1 -> Set Task2 Ready
	if (botton == 0b11111101) {
		TaskList[2]->status = 0;
		//currTCB = TaskList[2]->stack_ptr;
		//savecontext();
		UIKDispatcher();
		sei();
	}
	// SW2 -> Set Task3 Ready
	if (botton == 0b11111011) {
		TaskList[3]->status = 0;
		//currTCB = TaskList[3]->stack_ptr;
		//savecontext();
		UIKDispatcher();
		sei();
	}
	// SW3 -> Set Task4 Ready
	if (botton == 0b11110111) {
		TaskList[4]->status = 0;
		//currTCB = TaskList[4]->stack_ptr;
		//savecontext();	
		UIKDispatcher();
		sei();

	}
	// SW4 -> Set Task1 Block
	if (botton == 0b11101111) {
		TaskList[1]->status = 1;
		//currTCB = TaskList[1]->stack_ptr;
		//savecontext();
		UIKDispatcher();
		sei();
	}
	// SW5 -> Set Task2 Block
	if (botton == 0b11011111) {
		TaskList[2]->status = 1;
		//currTCB = TaskList[2]->stack_ptr;
		//savecontext();
		UIKDispatcher();
		sei();
	}
	// SW6 -> Set Task3 Block
	if (botton == 0b10111111) {
		TaskList[3]->status = 1;
		//currTCB = TaskList[3]->stack_ptr;
		//savecontext();
		UIKDispatcher();
		sei();
	}
	// SW7 -> Set Task4 Block
	if (botton == 0b01111111) {
		TaskList[4]->status = 1;
		//currTCB = TaskList[4]->stack_ptr;
		//savecontext();	
		UIKDispatcher();
		sei();

	}
	sei();
	botton = 0b11111111;
	
			
} // end ISR


#endif
