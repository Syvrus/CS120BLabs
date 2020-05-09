/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <../header/timer.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
unsigned char s[3] = {0x01, 0x02, 0x04};
unsigned char i = 0, tmpC;

enum State{Start, On}state;

void Tick(){
	switch(state){
		case Start:
			state = On;
			break;
		case On:
			state = On;
			break;
		default:
			break;
	}
	switch(state){
		case Start:
			break;
		case On:
			if(i < 2){
				tmpC = s[i];
				i++;
			}
			else{
				tmpC = s[i];
				i = 0;
			}
			break;
		default:
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRC = 0xFF;
	PORTC = 0x00;
	TimerSet(1000);
	TimerOn();
	tmpC = 0x00;
    /* Insert your solution below */
    while (1) {
        while(!TimerFlag);
	TimerFlag = 0;
	Tick();
	PORTC = tmpC;
    }
    return 1;
}
