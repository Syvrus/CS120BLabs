/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
//LINK: https://www.youtube.com/watch?v=kZ_A7hxqiLk 
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include "../header/timer.h"

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

enum S{Start, OFF, P, C, D, E, F, G, A, B, H}state;
unsigned char i = 0;
unsigned char c = 0;
unsigned char a = 0x00;
char n[21] = {C, D, C, F, E, C, D, C, G, F, C, H, A, F, E, D, H, A, F, G, F}; 
char h[21] = {60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60};
static double c4 = 261.63;
static double d4 = 293.66;
static double e4 = 329.63;
static double f4 = 349.23;
static double g4 = 392.00;
static double a4 = 440.00;
static double b4 = 493.88;
static double c5 = 523.25;

void Tick(){
	switch(state){
		case Start:
			state = OFF;
			break;
		case OFF:
			if(a == 0x01)
				state = n[c];
			else state = OFF;
			break;
		case P:
			if(i>=h[c]){
				c++;
				i = 0;
				state = n[c];
			}else{
				i++;
				state = P;
			}
			break;
		case C:
			state = P;
			break;
		case D:
			state = P;
			break;
		case E:
                        state = P;
                        break;
		case F:
			state = P;
                        break;
		case G:
			state = P;
                        break;
		case A:
			state = P;
                        break;
		case B:
			state = P;
                        break;
		case H:
			state = P;
                        break;
		default:
			state = OFF;
			break;
	}//Transiitons

	switch(state){
		case OFF:
			c = 0;
			i = 0;
			set_PWM(0);
			break;
		case P:
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
		case F:
			set_PWM(f4);
			break;
		case G:
			set_PWM(g4);
			break;
		case A:
			set_PWM(a4);
			break;
		case B:
			set_PWM(b4);
			break;
		case H:
			set_PWM(c5);
			break;
		default:
			set_PWM(0);
			break;
	}//actions
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;
	PORTA = 0xFF;
	DDRB = 0xFF;
	PORTB = 0x00;
	TimerSet(10);
	TimerOn();
	PWM_on();
	state = Start;
    /* Insert your solution below */
    while (1) {
	a = ~PINA & 0x01;
	Tick();
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}
