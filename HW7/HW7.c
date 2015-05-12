/* RTOS Assignment 7 - UIKAPI
 * RTOS Assignment 8 - Semaphore Control
 * Author: Chihsiang Wang
 * Description: 
 * This code is the implememnt of the Assignment 7 & 8. 
 * It implement the UIKAPI, which using Stk500 switches to control the tasks.
 * For the Assignment 8, I added Semaphore Control Function, this implement by Stk500 Switches. 
 * SW0 ~ SW3: Set task 1~4 to be ready
 * SW4 ~ SW7: Set task 1~4 to be Hold
 * Code Size: 3.82KB
 */
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "HW7.h"
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
                 "in    r0, __SP_H__         \n\t"	\
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




// This is the real Scheduler, execute every 1/100 Second 
ISR(TIMER1_COMPA_vect) {

    int Going_to_task;
    
    // save context
    currTCB = TaskList[Current_Task]->stack_ptr;
    savecontext();

    Check_Switch();
    Change_Switch();
    // Get Next task ID -> call Dispatcher
    Going_to_task = UIKDispatcher();

    // Execute that task, if same as current one, do nothing
    if (Going_to_task != Current_Task) {
        UIKRun(Going_to_task);
    }  

    currTCB = TaskList[Current_Task]->stack_ptr;
    restorecontext();

    // Re-enable interrupt
    sei();

    //asm volatile ("reti");
}

void Init_timer1 () {
    // Setup timer - timer 1 for 16 bits
    TCCR1B = (1 << WGM12);
    // enable CTC interrupt
    TIMSK |= 1 << OCIE1A;
    OCR1A = ticklen;
    TCCR1B |= (1 << CS10);
}

void Init_timer0 () {
    TCCR0 = (1<<CS02)|(1<<CS00);  // Timer clock = Sysclk/1024 (TCCR0 = 0x05)
    TIFR  = 1<<TOV0;              // Clear TOV0, any pending interrupts
    TIMSK = 1<<TOIE0;             // Enable Timer0 Overflow interrupt
    MCUCR = (1<<ISC01) | (1<<ISC00);
}

void UIKInitialize() {

    SetupLED();
    //Init_timer0();
    Init_timer1();
    //UIKTickHandler();
    Task_Numbers = 0;

}

void UIKAddTask (void (* task)(void), int Task_Priority) {
	
	int Task_ID;
	int Loc = Task_Numbers;

	if (Task_Numbers < MAX_TASK) {
		TaskList[Loc]->taskptr = task;
		TaskList[Loc]->Task_ID = Loc;
		TaskList[Loc]->status = 1;	// 0 for ready, 1 for blocking
		TaskList[Loc]->Priority = Task_Priority;
		TaskList[Loc]->Sem = UIKSemCreate();
		//TaskList[Loc]->Init = 0;
		Task_Numbers++;
		
	}

	else {
		printf("Already reached Max number of Tasks.\n");
	}


}

void createTaskList(TCBptr *TaskList) {
    int i;
    for (i = 0; i < MAX_TASK; i++) {
        TaskList[i] = (Task_Control*)malloc(sizeof(Task_Control));
    }
}

void UIKRun(int taskid) {
	Current_Task = taskid;
	//currTCB = TaskList[Current_Task]->stack_ptr;
        //restorecontext();
	(TaskList[taskid] -> taskptr) ();
}

void UIKScheduler() {

    UIKAddTask(UIKIdle, 255);
    UIKAddTask(Task_1, 1);
    UIKAddTask(Task_2, 2);
    UIKAddTask(Task_3, 3);
    UIKAddTask(Task_4, 4);

    // Execute Idle Task
    TaskList[0]->status = 0; // Idle task will never be blocked
    Current_Task = 0;	 // Running Idle task	
    UIKRun(0);
}




int UIKDispatcher() {


    int i, best;

    best = 0;
    for (i = 0; i < Task_Numbers; i++) {
	// check which task is ready, and execute highest priority task
	if (TaskList[i]->Sem->value == 0 && TaskList[i]->Priority <= TaskList[best]->Priority) {
	    best = i;
	}
    }

    return best;
}



void UIKTickHandler() {
    Init_timer1();
}

int UIKTickNum() {
    return ticknum;
}


UIKSem* UIKSemCreate() {
    UIKSem* Sem;
    Sem = (UIKSem*)malloc(sizeof(UIKSem));
    Sem->value = 0;
    return Sem;
}

// Wait
void UIKSemPend(UIKSem* Sem) {
    Sem->value = 1;
}

// Signal
void SemPost(UIKSem* Sem) {
    Sem->value = 0;
}

void SetupLED() {
    // PORTA for input
    DDRA = 0x00;

    // PORTB for output
    DDRB = 0xFF;                

    // Initialize PORTB -> off all LEDs
    PORTB = 0xFF;
}

void Check_Switch() {
    botton = PINA;
}




int main() {

	// Disable interrupt
	cli();

	// Initialize everything here
	UIKInitialize();
	
	// Allocate Memory Space for each Tasks
	createTaskList(TaskList);

	// Add all tasks into task queue, and execute Idle task	
	UIKScheduler();

	// enable global interrupt from here
	sei();

	// Start Rtos
	//while(1);
	

}
