/*	Author: bcorb005
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
enum States{ Start, INIT, INCREMENT, DECREMENT, BOTH, RESET, WAIT } state;	
unsigned char temp, A1, A2;
void Tick(){
switch(state){//Transi3ons
	A1 = PINA & 0x01;
	A2 = PINA & 0x02;
	case Start:
		state = INIT;
		break;
 	case INIT:
		if(!A1 && !A2)
			state = INIT;
		if(A1 && !A2)
			state = INCREMENT;
		if(!A1 && A2)
			state = DECREMENT;
		else
			state = BOTH;
		break;
	case INCREMENT:
		if(A1 && A2)
			state = BOTH;
		else
			state = WAIT;
		break;
	case DECREMENT:
		if(A1 && A2)
			state = BOTH;
		else
			state = WAIT;
		break;
	case BOTH:
		if(A1 && A2)
			state = RESET;
		if(A1 && !A2)
			state = INCREMENT;
		if(!A1 && A2)
			state = DECREMENT;
		if(A1 && A2)
			state = BOTH;
		break;
	case WAIT:
		if(!A1 && !A2)
			state = BOTH;
		if(A1 && A2)
			state = RESET;
		else
			state = WAIT;
		break;
	case RESET:
		if(!A1 && !A2)
			state = INIT;
		if(A1 && !A2)
			state = INCREMENT;
		if(!A1 && A2)
			state = DECREMENT;
		if(A1 && A2)
			state = RESET;
	default:
		state = Start;
		break;
}//Transi3ons	
switch(state){//State ac3ons	
	case INIT:
		break;
	case INCREMENT:
		if(temp < 9)
			temp++;
		break;
	case DECREMENT:
		if(temp > 0)
			temp--;
		break;
	case RESET:
		temp = 0x00;
		break;
	default:
		break;
		
}//State ac3ons	
}	
int main(void){
	DDRA = 0x00;
	PORTA = 0xFF;
	DDRC = 0xFF;
	PORTC = 0x07;//Ini3alize outputs	
	state = Start;//Indicates ini3al call	
	temp = PORTC;
	while(1){
		Tick();
		PORTC = temp;
	}	
}	
