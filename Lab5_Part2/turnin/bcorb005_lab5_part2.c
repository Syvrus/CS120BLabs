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
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum State {Start, WAIT, IP, IR, DP, DR, RP, RR} state;
unsigned char tmpA, tmpC;
void Tick(){
	switch(state){
		case Start:
			state = WAIT;
			break;
		case WAIT:
			if(tmpA == 1 && tmpC < 9)
				state = IP;
			else if(tmpA == 0x02 && tmpC > 0)
				state = DP;
			else if(tmpA == 3)
				state = RP;
			else
				state = WAIT;
			break;
		case IP:
			state = IR;
			break;
		case IR:
			if(tmpA == 0)
				state = WAIT;
			else if(tmpA == 3)
				state = RP;
			else
				state = IR;
			break;
		case DP:
			state = DR;
			break;
		case DR:
			if(tmpA == 0)
				state = WAIT;
			else if(tmpA == 3)
				state = RP;
			else
				state = DR;
			break;
		case RP:
			state = RR;
			break;
		case RR:
			if(tmpA == 0)
				state = WAIT;
			else
				state = RR;
			break;
		default:
			break;
	} //Transition

	switch(state){
		case Start:
			tmpC = 0;
			break;
		case WAIT:
			break;
		case IP:
			tmpC++;
			break;
		case IR:
			break;
		case DP:
			tmpC--;
			break;
		case DR:
			break;
		case RP:
			tmpC = 0;
			break;
		case RR:
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
	tmpC = 0;
    while (1) {
	tmpA = ~PINA & 0x03;
	Tick();
	PORTC = tmpC;
    }
    return 1;
}
