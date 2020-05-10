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
enum State {Start, In, I, D, R} state;
unsigned char tmpA, tmpC, i = 0;
void Tick(){
	switch(state){
		case Start:
			tmpC = 7;
			state = In;
			break;
		case In:
			if(tmpA == 1)
				state = I;
			else if(tmpA == 2)
				state = D;
			else if(tmpA == 3)
				state = R;
			else
				state = In;
			break;
		case I:
			if(tmpA == 0)
				state = In;
			else if(tmpA == 3)
				state = R;
			else{
				state = I;
				i++;
			}
			break;
		case D:
			if(tmpA == 0)
				state = In;
			else if(tmpA == 3)
				state = R;
			else{
				state = D;
				i++;
			}
			break;
		case R:
			if(tmpA == 0)
				state = In;
			else
				state = R;
			break;
		default:
			break;
	} //Transition

	switch(state){
		case Start:
			i = 7;
			break;
		case In:
			break;
		case I:
			if(tmpC < 9 && i % 10 == 0)
				tmpC++;
			break;
		case D:
			if(tmpC > 0 && i % 10 == 0)
				tmpC--;
			break;
		case R:
			tmpC = 0;
			break;
		default:
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
	state = Start;
	TimerSet(100);
	TimerOn();
    while (1) {
	    while(!TimerFlag);
	    TimerFlag = 0;
	    tmpA = ~PINA & 0x0F;
	    Tick();
	    PORTC = tmpC;
    }
    return 1;
}
