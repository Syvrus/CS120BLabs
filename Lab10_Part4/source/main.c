/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
//Link: 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum ThreeLEDsSM{ l1, l2, l3 } l;
enum BlinkingLEDSM{ b1, b2 } b;
enum CombineLEDsSM{ c1, c2 } c;
enum Freq{ w, i, d } f;

unsigned char lT = 0x00, lB = 0x00, a;
static double fT = 0x03;
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
			if(a == 0x04)
				PORTB = lT | lB | 0x01;
				PORTB = lT | lB;
			break;
		case c2:
			PORTB = lT | lB;
			break;
		default:
			break;
	}//Actions
}
void fc(){
	switch(f){
		case w:
			if(a == 1){
				if(fT < 5)
					fT++;
				f = i;
			}
			else if(a == 2){
				if(fT > 1)
					fT--;
				f = d;
			}
			else f = w;
			break;
		case i:
			if(a == 1){
				if(fT < 10)
					fT++;
				f = i;
			}
			else if(a == 2){
				if(fT > 1)
					fT--;
				f = d;
			}
			else f = w;
			break;
		case d:
			if(a == 1){
				if(fT < 10)
					fT++;
				f = i;
			}
			else if(a == 2){
				if(fT > 1)
					fT--;
				f = d;
			}
			else f = w;
			break;
		default:
			f = w;
			break;
	}//Transitions
	switch(f){
		case i:
		case d:
			break;
		case w:
			break;
		default:
			break;
	}//Actions
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00, PORTA = 0xFF;
	DDRB = 0xFF, PORTB = 0x00;

	unsigned long lP = 300, bP = 1000;
	unsigned ff = fT;
	TimerOn();
	TimerSet(2);
    /* Insert your solution below */
    while (1) {
	a = ~PINA;
	if(lP >= 300){
		tL();
		lP = 0;
	}
	if(bP >= 1000){
		bL();
		bP = 0;
	}
	fc();
	cL();
	while(!TimerFlag){};
	TimerFlag = 0;

	ff += 2*fT;
	lP += 2;
	bP += 2;
    }
    return 1;
}
