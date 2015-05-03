#ifndef HW7_H
#define HW7_H
#define MAX_TASK 5


typedef struct Task_Control {

	void (*taskptr)();
	int Task_ID;
	int status;
	int Priority;
	} Task_Control;

typedef struct Task_Control * TCBptr;


int ticklen;
int Task_Numbers;
TCBptr TaskList[MAX_TASK];



void Task_1() {
	while (1) {
		printf("ok1\n");
	}
}

void Task_2() {
	while (1) {
		printf("ok2\n");
	}
}

void Task_3() {
	while (1) {
		printf("ok3\n");
	}
}

void Task_4() {
	while (1) {
		printf("ok4\n");
	}
}

void UIKIdle() {
	while (1) {
		printf("IDLE\n");
	}
}

#endif