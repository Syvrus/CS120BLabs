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
//Demo Video Link: https://www.youtube.com/watch?v=4q5Ak5OsOfY
unsigned char tmpC, A0, tmpA;
enum State{ Start, BLANK, s0P, s0R, s1P, s1R, s2P, s2R, s3P, s3R } state;
void Tick(){
	A0 = tmpA & 0x01;
	switch(state){
		case Start:
			state = BLANK;
			break;
		case BLANK:
			if(A0 == 0x01)
				state = s0P;
			else
				state = BLANK;
			break;
		case s0P:
			state = s0R;
			break;
		case s0R:
			if(A0 == 0x01)
				state = s1P;
			else
				state = s0R;
			break;
		case s1P:
			state = s1R;
			break;
		case s1R:
			if(A0 == 0x01)
				state = s2P;
			else
				state = s1R;
			break;
		case s2P:
			state = s2R;
			break;
		case s2R:
			if(A0 == 0x01)
				state = s3P;
			else
				state = s2R;
			break;
		case s3P:
			state = s3R;
			break;
		case s3R:
			if(A0 == 0x01)
				state = BLANK;
			else
				state = s3R;
			break;
		default:
			break;
	}
	switch(state){
		case Start:
			PORTC = 0x00;
			break;
		case BLANK:
			PORTC = 0x00;
			break;
		case s0P:
		case s0R:
			PORTC = 0xAB;
			break;
		case s1P:
		case s1R:
			PORTC = 0x2D;
			break;
		case s2P:
		case s2R:
			PORTC = 0x35;
			break;
		case s3P:
		case s3R:
			PORTC = 0x55;
			break;
		default:
			break;
	}
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	tmpC = 0x00; state = Start;
    /* Insert your solution below */
    while (1) {
	tmpA = ~PINA;
	Tick();
	//PORTC = tmpC;
    }
    return 1;
}
