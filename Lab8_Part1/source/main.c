/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
//LINK: https://www.youtube.com/watch?v=hFihchTNQRw
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

void ADC_init(){
	ADCSRA = (1<<ADEN) | (1<<ADSC) | (1<<ADATE);
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; 
	PORTA = 0xFF;
	DDRB = 0xFF;
	PORTB = 0x00;
	DDRD = 0xFF;
	PORTD = 0x00;
	unsigned short a;
	unsigned char tmpB, tmpD;
	ADC_init();
    /* Insert your solution below */
    while (1) {
	a = ADC;
	tmpB = (char)a;
	tmpD = (char)(a>>8);

	PORTB = tmpB;
	PORTD = tmpD;
    }
    return 1;
}
