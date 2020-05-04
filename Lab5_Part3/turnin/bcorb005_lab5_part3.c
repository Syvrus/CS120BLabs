/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
//https://www.youtube.com/watch?v=pu5fUS6huBg
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
unsigned char tmpC, A0, tmpA, i = 0;
unsigned char s[5] = {0x00, 0xAB, 0x2D, 0x35, 0x55};
enum State{ Start, Press, Release } state;
void Tick(){
	A0 = tmpA & 0x01;
	switch(state){
		case Start:
			state = Release;
			break;
		case Press:
			if(A0)
				state = Press;
			else{
				if(i < 5)
					i++;
				else
					i = 0;
				state = Release;
			}
			break;
		case Release:
			if(A0)
				state = Press;
			else
				state = Release;
			break;
		default:
			break;
	}
	switch(state){
		case Release:
			PORTC = s[i];
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
