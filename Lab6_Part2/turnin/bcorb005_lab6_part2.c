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
unsigned i = 0;

enum State{Start, Ascend, Descend, PauseP, PauseR} state;

unsigned tmpA, tmpC;

void Tick(){
	switch(state){
		case Start:
			state = Ascend;
			break;
		case Ascend:
			if(tmpA == 1)
				state = PauseP;
			else
			if(i == 2){
				state = Descend;
				//i = 0;
			}else
				state = Ascend;
			break;
		case Descend:
			if(tmpA == 1)
				state = PauseP;
			else
			if(i == 0){
				state = Ascend;
				//i = 0;
			}
			else{
				state = Descend;
			}
			break;
		case PauseP:
			if(tmpA == 1){
				state = PauseP;	
			}else
				state = PauseR;
			break;
		case PauseR:
			if(tmpA == 1){
				i = 0;
				state = Ascend;
			}else{
				state = PauseR;
			}
			break;
		default:
			break;
	}

	switch(state){
		case Start:
			break;
		case Ascend:
			if(i < 3){
				tmpC = s[i];
				if(tmpA == 0)
					i++;
			}
			break;
		case Descend:
			if(i > 0){
				tmpC = s[i];
				if(tmpA == 0)
					i--;
			}
			break;
		case PauseP:
		case PauseR:
			tmpC = s[i];
			break;
		default:
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;
	PORTA = 0xFF;
	DDRC = 0xFF;
	PORTC = 0x00;
	tmpC = 0x00;
	TimerSet(300);
	TimerOn();
	tmpC = 0x00;
    /* Insert your solution below */
    while (1) {
        while(!TimerFlag);
	TimerFlag = 0;
	tmpA = ~PINA & 0x01;
	Tick();
	PORTC = tmpC;
    }
    return 1;
}
