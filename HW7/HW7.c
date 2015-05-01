/* RTOS Assignment 7 - UIKAPI
 * Author: Chihsiang Wang
 * Code Size: 3.82KB
 */
#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL

void UIKInitialize(UINT16 ticklen, UINT8 MaxTasks) {


}

UINT8 UIKAddTask (void (* task)(void), UNIT8 priority, /*stack*/ ) {
	

}

void UIKRun(UNIT8 taskid) {

}

void UIKSchedule(void) {

}

void UIKDelay() {


}

void UIKDispatcher(void) {

}

void UIKIdle() {

}

void UIKTickHandler() {

}

void UIKTickNum() {


}

void UIKTickLen(){

}

void UIKIntDepth() {

}

int main() {

	UINT16 ticklen;
	UINT8 MaxTasks = 255;
	
	UIKInitialize(ticklen, MaxTasks);


}