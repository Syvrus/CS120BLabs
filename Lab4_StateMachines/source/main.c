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
enum States{ Start, INIT, INCREMENT, DECREMENT, BOTH, RELEASE_B } state;	
void Tick(){
switch(state){//Transi3ons	
	case Start:
		state = INIT;
		break;
 	case INIT:
		if(PINA & 0x03 == 0x01)
			state = INCREMENT;;
		if(PINA & 0x03 == 0x02)
			state = DECREMENT;
		if(PINA & 0x03 == 0x03)
			state = BOTH		
		break;
	case INCREMENT:
		if(temp < 9)
			temp++;
		if(PINA & 0x03 == 0x02)
			state = DECREMENT;
		if(PINA & 0x03 == 0x03)
			state = BOTH;
		if(PINA & 0x00 == 0x00)
			state = RELEASE_B;
		break;
	case ON_RELEASE:
		if(PINA & 0x01)
			state = OFF_PRESS;
		else
			state = ON_RELEASE;
		break;
	case OFF_PRESS:
		if(PINA & 0x01)
			state = OFF_PRESS;
		else
			state = OFF_RELEASE;
		break;
	default:
		state = Start;
		break;
}//Transi3ons	
switch(state){//State ac3ons	
	case ON_PRESS:
		PORTB = 0x02;
		break;
	case OFF_PRESS:
		PORTB = 0x01;
		break;
	case OFF_RELEASE:
	case ON_RELEASE:
		break;
	default:
		PORTB = 0x01;
		break;
		
}//State ac3ons	
}	
void main(){
	DDRA = 0x00;
	PORTA = 0xFF;
	DDRB = 0xFF;	
 	PORTB = 0x01;//Ini3alize outputs	
	state = Start;//Indicates ini3al call	
	while(1){
		Tick();
	}	
}	
