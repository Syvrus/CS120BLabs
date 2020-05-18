/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
//LINK: https://www.youtube.com/watch?v=GiyGv8obnks
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

void set_PWM(double f){
	static double cf;
	if(f != cf){
		if(!f) TCCR3B &= 0x08;
		else TCCR3B |= 0x03;
		if(f < 0.954) OCR3A = 0xFFFF;
		else if(f > 31250) OCR3A = 0x0000;
		else OCR3A = (short)(8000000 / (128 * f)) - 1;
		TCNT3 = 0;
		cf = f;
	}
}

void PWM_on() {
	TCCR3A = (1 << COM3A0);
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
	set_PWM(0);
}

void PWM_off(){
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}

enum S{Start, wait, C, D, E}state;

unsigned char a = 0x00;
static double c4 = 261.63;
static double d4 = 293.66;
static double e4 = 329.63;

void Tick(){
	switch(state){
		case Start:
			state = wait;
			break;
		case wait:
			if(a == 0x01)
				state = C;
			else if(a == 0x02)
				state = D;
			else if(a == 0x04)
				state = E;
			else
				state = wait;
			break;
		case C:
			if(a == 0x01)
				state = C;
			else state = wait;
			break;
		case D:
			if(a == 0x02)
				state = D;
			else state = wait;
			break;
		case E:
			if(a == 0x04)
				state = E;
			else state = wait;
			break;
		default:
			break;
	}//Transiitons

	switch(state){
		case wait:
			set_PWM(0);
			break;
		case C:
			set_PWM(c4);
			break;
		case D:
			set_PWM(d4);
			break;
		case E:
			set_PWM(e4);
			break;
		default:
			break;
	}
}//actions

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;
	PORTA = 0xFF;
	DDRB = 0xFF;
	PORTB = 0x00;
	PWM_on();
	state = Start;
    /* Insert your solution below */
    while (1) {
	a = ~PINA & 0x07;
	Tick();
    }
    return 1;
}
