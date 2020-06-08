/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
//Video: https://www.youtube.com/watch?v=4stj86Br9WA
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include "timer.h"
#include "keypad.h"
#include "scheduler.h"
#include "bit.h"
//Share variables go here


//End shared variables
//volatile unsigned TimerFlag = 0;
enum keypad_STATES {start} keypad_state;

int keypadTick(int keypad_state){
	unsigned char x = GetKeypadKey();
	switch(keypad_state){
		case start:
		keypad_state = start;
                break;	
	
		default:
		keypad_state = start;
		break;
	}

	switch(x) {
		case '\0':PORTB = 0x00; break;
		case '1': PORTB = 0x01; break;
		case '2': PORTB = 0x02; break;
		case '3': PORTB = 0x03; break;
		case 'A': PORTB = 0x0A; break;
		case '4': PORTB = 0x04; break;
		case '5': PORTB = 0x05; break;
		case '6': PORTB = 0x06; break;
		case 'B': PORTB = 0x0B; break;
		case '7': PORTB = 0x07; break;
		case '8': PORTB = 0x08; break;
		case '9': PORTB = 0x09; break;
		case 'C': PORTB = 0x0C; break;
		case '*': PORTB = 0x0E; break;
		case '0': PORTB = 0x00; break;
		case '#': PORTB = 0x0F; break;
		case 'D': PORTB = 0x0D; break;
		default: PORTB = 0x1B; break;
	}
	return keypad_state;
}
 
int main(void) {
	DDRB = 0xFF; PORTB = 0x00;
	DDRA = 0xF0; PORTA = 0x0F;
	
	static task t;
	task *tasks[] = {&t};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);
	
	//Task
	t.state = start;
	t.period = 50;
	t.elapsedTime = t.period;
	t.TickFct = &keypadTick;
	
	TimerSet(50);
	TimerOn();
	
	unsigned short i;
	/* Replace with your application code */
	while (1) {
		for(i = 0; i < numTasks; i++){
			if(tasks[i]->elapsedTime == tasks[i]->period){
				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
				tasks[i]->elapsedTime = 0;
			}
			tasks[i]->elapsedTime += 50;
		}
		//PORTB = 0xFF;
		keypadTick(start);
		while(!TimerFlag);
		TimerFlag = 0;
	}
	return 0;
}
