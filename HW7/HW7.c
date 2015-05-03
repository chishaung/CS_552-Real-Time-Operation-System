/* RTOS Assignment 7 - UIKAPI
 * Author: Chihsiang Wang
 * Description: There are 4+1 tasks (1 for Idle task) will be execute in the RTOS
 * Code Size: 3.82KB
 */
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "HW7.h"
#define F_CPU 16000000UL






void UIKInitialize() {
	SetupLED();
	sei();
	TCCR0 = (1<<CS02)|(1<<CS00);  // Timer clock = Sysclk/1024 (TCCR0 = 0x05)
	TIFR  = 1<<TOV0;              // Clear TOV0, any pending interrupts
	TIMSK = 1<<TOIE0;             // Enable Timer0 Overflow interrupt
	Task_Numbers = 0;
	ticklen = 1;

}

void UIKAddTask (void (* task)(void), int Task_Priority) {
	
	int Task_ID;
	int Loc = Task_Numbers;

	if (Task_Numbers < MAX_TASK) {
		TaskList[Loc]->taskptr = task;
		TaskList[Loc]->Task_ID = Loc;
		TaskList[Loc]->status = 1;	// 0 for running, 1 for blocking
		TaskList[Loc]->Priority = Task_Priority;
		Task_Numbers++;
	}

	else {
		printf("Already reached Max number of Tasks.\n");
	}


}

void createTaskList(TCBptr *TaskList) {
	int i = 0;
	for (int i = 0; i < MAX_TASK; i++) {
		TaskList[i] = (Task_Control*)malloc(sizeof(Task_Control));
	}

}

void UIKRun(int taskid) {

	(TaskList[taskid] -> taskptr) ();
	
}

void UIKScheduler() {

	UIKAddTask(UIKIdle, 10);
	UIKAddTask(Task_1, 1);
	UIKAddTask(Task_2, 1);
	UIKAddTask(Task_3, 1);
	UIKAddTask(Task_4, 1);

	// Execute Idle Task
	TaskList[0]->status = 0;
	//UIKRun(0);
	
	while (1) {
		UIKDispatcher();
	}
	
}

void UIKDelay() {



}

void UIKDispatcher() {
	for (int i = 0; i < MAX_TASK; i++) {
		if (TaskList[i]->status == 0) {
			UIKRun(i);
		}
	}
}



void UIKTickHandler() {

}

void UIKTickNum() {


}

void UIKTickLen(){

}

void UIKIntDepth() {

}

void SetupLED() {
	DDRA = 0x00;
	DDRB = 0xFF;                 // Set Port B as output

	PORTB = 0xFF;

}

int main() {

	// Initialize everything here
	UIKInitialize();
	
	// Allocate Memory Space for each Tasks
	createTaskList(TaskList);

	// Decide which task is running. If nothing running, execute IDLE task.
	UIKScheduler();



}
