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

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRC = 0xFF;
	PORTC = 0x00;
	TimerSet(1000);
	TimerOn();
	unsigned char tmpC = 0x00;
    /* Insert your solution below */
    while (1) {
        tmpC = s[i];
        PORTC = tmpC;
        while(!TimerFlag);
	TimerFlag = 0;
	if(i < 2)
		i++;
	else i = 0;
    }
    return 1;
}
