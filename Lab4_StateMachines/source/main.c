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
enum States{ Start, INIT, INCREMENT, DECREMENT, BOTH, RELEASE_I, RELEASE_D,  RELEASE_B } state;	
void Tick(){
unsigned char temp = PORTC;
switch(state){//Transi3ons	
	case Start:
		state = INIT;
		break;
 	case INIT:
		if(PINA & 0x03 == 0x01){
			if(temp < 9)
				temp++;
			state = INCREMENT;
		}
		if(PINA & 0x03 == 0x02){
			if(temp > 0)
				temp--;
			state = DECREMENT;
		}
		if(PINA & 0x03 == 0x03)
			state = BOTH;
		break;
	case INCREMENT:
		if(PINA & 0x03 == 0x02){
			if(temp > 0)
				temp--;
			state = DECREMENT;
		}
		if(PINA & 0x03 == 0x03)
			state = BOTH;
		if(PINA & 0x00 == 0x00)
			state = RELEASE_B;
		break;
	case DECREMENT:
		if(PINA & 0x03 == 0x01){
			if(temp < 9)
				temp++;
			state = INCREMENT;
		}
		if(PINA & 0x03 == 0x03)
			state = BOTH;
		if(PINA & 0x03 == 0x00)
			state = RELEASE_B;
		break;
	case BOTH:
		if(PINA & 0x03 == 0x02)
			state = RELEASE_I;
		if(PINA & 0x03 == 0x01)
			state = RELEASE_D;
		if(PINA & 0x03 == 0x00)
			state = RELEASE_B;
		break;
	case RELEASE_I:
		if(PINA & 0x03 == 0x00)
			state = RELEASE_B;
		if(PINA & 0x03 == 0x01){
			if(temp < 9)
				temp++;
			state = INCREMENT;
		}
		if(PINA & 0x03 == 0x03){
			if(temp < 9)
				temp++;
			state = BOTH;
		}
		break;
	case RELEASE_D:
		if(PINA & 0x03 == 0x00)
			state = RELEASE_B;
		if(PINA & 0x03 == 0x02){
			if(temp > 0)
				temp--;
			state = DECREMENT;
		}
		if(PINA & 0x03 == 0x03){
			if(temp > 0)
				temp--;
			state = BOTH;
		}
		break;
	case RELEASE_B:
		temp = 0;
		if(PINA & 0x03 == 0x01){
			if(temp < 9)
				temp++;
			state = INCREMENT;
		}
		if(PINA & 0x03 == 0x02){
			if(temp > 0)
				temp--;
			state = DECREMENT;
		}
		if(PINA & 0x03 == 0x03)
			state = BOTH;
		break;
	default:
		state = Start;
		break;
}//Transi3ons	
switch(state){//State ac3ons	
	default:
		break;
		
}//State ac3ons	
}	
void main(){
	DDRA = 0x00;
	PORTA = 0xFF;
	DDRC = 0xFF;
	PORTC = 0x07;//Ini3alize outputs	
	state = Start;//Indicates ini3al call	
	while(1){
		Tick();
	}	
}	
