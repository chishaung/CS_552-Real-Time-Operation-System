/*
 * IncFile1.h
 *
 * Created: 2015/5/12 上午 02:01:18
 *  Author: Shaung
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_
#define MAX_TASK 5


typedef struct Task_Control {

	void (*taskptr)();
	int Task_ID;
	int status;
	int Priority;
	int Age;

} Task_Control;
typedef struct Task_Control * TCBptr;

int ms;
int sec;
int Task_Number;
int Current_Task;
int Task_Numbers;
TCBptr TaskList[MAX_TASK];
volatile uint8_t *currTCB;
//uint16_t ticklen = 2000000;


void Task_1() {
	while (1) {

		PORTB = ~0x01;
		_delay_ms(100);
		PORTB = ~0x00;
		_delay_ms(100);
		sei();
	}
}

void Task_2() {
	while (1) {

		PORTB = ~0x02;
		_delay_ms(100);
		PORTB = ~0x00;
		_delay_ms(100);
		sei();
	}
}

void Task_3() {
	/*
	uint8_t cnt;
	while (1) {

		if (PORTB == 0x00)
		PORTB = 0xff;
		PORTB = PORTB << 1;
		_delay_ms(100);
		sei();
	}*/	while (1) {
		PORTB = ~0x04;
		_delay_ms(100);
		PORTB = ~0x00;
		_delay_ms(100);
		sei();
	}
}

void Task_4() {
	while (1) {
		
		PORTB = ~0x08;
		_delay_ms(100);
		PORTB = ~0x00;
		_delay_ms(100);
		sei();
	}
}

void UIKIdle() {
	while (1) {
		PORTB = 0xFE;
		_delay_ms(300);
		PORTB = 0xFF;
		_delay_ms(300);
		sei();
	}
}



void SetupLED() {
	// PORTA for input
	DDRA = 0x00;

	// PORTB for output
	DDRB = 0xFF;

	// Initialize PORTB -> off all LEDs
	PORTB = 0xFF;
}



void createTaskList(TCBptr *TaskList) {
	int i;
	for (i = 0; i < MAX_TASK; i++) {
		TaskList[i] = (Task_Control*)malloc(sizeof(Task_Control));
	}
}

void UIKRun(int taskid) {
	Current_Task = taskid;
	int i;


 
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

void UIKAddTask (void (* task)(void), int Task_Priority) {
	
	int Task_ID;
	int Loc = Task_Numbers;

	if (Task_Numbers < MAX_TASK) {
		TaskList[Loc]->taskptr = task;
		TaskList[Loc]->Task_ID = Loc;
		TaskList[Loc]->status = 0;	// 0 for ready, 1 for blocking
		TaskList[Loc]->Priority = Task_Priority;
		TaskList[Loc]->Age = 0;
		Task_Numbers++;
		
	}

	else {
		printf("Already reached Max number of Tasks.\n");
	}


}

void UIKInitialize() {

	SetupLED();
	Init_timer1();
	Task_Numbers = 0;

}

void Init_timer1 () {
	// Setup timer - timer 1 for 16 bits
	TCCR1B = (1 << WGM12);
	// enable CTC interrupt
	TIMSK |= 1 << OCIE1A;
	OCR1A = 10000;
	TCCR1B |= (1 << CS10);
}





#endif /* INCFILE1_H_ */
