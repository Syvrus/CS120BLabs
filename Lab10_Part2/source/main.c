/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
//Link: https://www.youtube.com/watch?v=FadJCCttnMY
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum ThreeLEDsSM{ l1, l2, l3 } l;
enum BlinkingLEDSM{ b1, b2 } b;
enum CombineLEDsSM{ c1, c2 } c;

unsigned char lT = 0x00, lB = 0x00;

void tL(){
	switch(l){
		case l1:
			l = l2;
			break;
		case l2:
			l = l3;
			break;
		case l3:
			l = l1;
			break;
		default:
			l = l1;
			break;
	}//Transitions

	switch(l){
		case l1:
			lT = 0x01;
			break;
		case l2:
			lT = 0x02;
			break;
		case l3:
			lT = 0x04;
			break;
		default:
			break;
	}//Actions
}
void bL(){
	switch(b){
		case b1:
			b = b2;
			break;
		case b2:
			b = b1;
			break;
		default:
			b = b1;
			break;
	}//Transitions
	switch(b){
		case b1:
			lB = 0x08;
			break;
		case b2:
			lB = 0x00;
			break;
		default:
			break;
	}//Actions
}
void cL(){
	switch(c){
		case c1:
			c = c2;
			break;
		case c2:
			c = c1;
			break;
		default:
			c = c1;
			break;
	}//Transitions
	switch(c){
		case c1:
			PORTB = lT | lB;
			break;
		case c2:
			PORTB = lT | lB;
			break;
		default:
			break;
	}//Actions
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF, PORTB = 0x00;

	unsigned long lP = 300, bP = 1000;

	TimerOn();
	TimerSet(100);
    /* Insert your solution below */
    while (1) {
	if(lP >= 300){
		tL();
		lP = 0;
	}
	if(bP >= 1000){
		bL();
		bP = 0;
	}
	cL();
	while(!TimerFlag){};
	TimerFlag = 0;

	lP += 100;
	bP += 100;
    }
    return 1;
}
