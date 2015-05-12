/* RTOS Final Project - Priority Aging Scheduling
 * Author: Chihsiang Wang 101-64106
 * Description:
 * In this project, I will implement Priority Aging Scheduling. 
 * Which the Scheduler deals with 4 tasks, has different priority. 
 * In this Scheduling, it has ability to make sure all tasks can be executed and avoid starvation occurs. 
 * To simplified the algorithm, this is not a real RTOS system which perform every details(context switching, delay, some UIKAPI may not show here)
 * but only shows the method and perform it. 
 * For a better way to see how the system manage the task switch, every tick length will extends to 5 second
 * this can help to perfome the result better. 

 * Task Description:
 * Task 1: LED0 and LED1 will blink.	Priority: 1
 * Task 2: LED2 and LED3 will blink.	Priority: 2
 * Task 3: LEDs move from 0 to 7.		Priority: 3
 * Task 4: LED blink as 0x55.			Priority: 4

 * Algorithm:
 * Giving each TCB a int variable names 'Age', initialize it to be 0 when add task to scheduling.
 * The scheduler will search the best choice to execute: The Oldest, Highest Priority is the best.
 * When system start, the task 1 will be executed first, dont change the age.
 * Other tasks (2~4) will + 1 age. 
 * next tick, Task 2 will be execute: Task2~4 are same age:1, but task 2 has better priority.
 * Except currect task, others + 1 age -> T1:1, T2:1, T3:2, T4:2
 * Keep doing this, and we can see the age will change like:
 [T1:0] [T2:1] [T3:1] [T4:1]
 [T1:1] [T2:1] [T3:2] [T4:2]
 [T1:2] [T2:2] [T3:2] [T4:3]
 [T1:3] [T2:3] [T3:3] [T4:3]
 
 Now we can see every task are be able to execute in this method. 
 
 * Code Size:
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "Project.h"

// This is the real Scheduler, execute every 1/100 Second
ISR(TIMER1_COMPA_vect) {
	
	if (ms == 0) {
		
	
		int Going_to_task;

		// Get Next task ID -> call Dispatcher
		Going_to_task = UIKDispatcher();

		// Execute that task, if same as current one, do nothing
		if (Going_to_task != Current_Task) {
			UIKRun(Going_to_task);
		}

		// Re-enable interrupt
		sei();

	}
	
	ms ++;
	if (ms >= 5000)
		ms = 0;
}


int UIKDispatcher() {


	int i, best, oldest;

	best = 1;
	oldest = 0;
	
	for (i = 1; i < Task_Numbers; i++) {
		if (TaskList[i]->Age >= oldest) {
			oldest = TaskList[i]->Age;
		}
	}
	
	for (i = 1; i < Task_Numbers; i++) {
		// check which task is ready, and execute highest priority task
		if (TaskList[i]->status == 0 &&  TaskList[i]->Age == oldest && TaskList[i]->Priority <= TaskList[best]->Priority) {
			best = i;
		}
	}
	
	for (i = 0; i < Task_Numbers; i++) {
		if (i != best)
		TaskList[i]->Age = TaskList[i]->Age+1;
	}

	return best;
}

int main(void)
{
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
}
