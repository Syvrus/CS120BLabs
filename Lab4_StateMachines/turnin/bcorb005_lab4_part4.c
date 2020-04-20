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
enum States{ Start, FIRST_PRESS, FIRST_RELEASE, SECOND_PRESS, UNLOCK } state;	
//unsigned char temp, A1, A2;

void Tick(){
switch(state){//Transi3ons	
	case Start:
		state = FIRST_PRESS;
		break;
 	case FIRST_PRESS:
		if(PINA == 0x04)
			state = FIRST_PRESS;
		else
			state = Start;
		break;
	case FIRST_RELEASE:
		if(PINA == 0x00)
			state = SECOND_PRESS;
		if(PINA == 0x04)
			state = FIRST_PRESS;
		else
			state = Start;
		break;
	case SECOND_PRESS:
		if(PINA == 0x02)
			state = UNLOCK;
		if(PINA = 0x00)
			state = SECOND_PRESS;
		else
			state = Start;
		break;
	case UNLOCK:
		if(PINA == 0x80)
			state = Start;
		else
			state = UNLOCK;
		break;
	default:
		break;
}//Transi3ons	
switch(state){//State ac3ons	
	case FIRST_PRESS:
	case FIRST_RELEASE:
	case SECOND_PRESS:
		PORTB = 0x00;
		break;
	case UNLOCK:
		PORTB = 0x01;
	default:
		break;
}//State ac3ons	
}	
void main(){
	DDRA = 0x00;
	PORTA = 0xFF;
	DDRB = 0xFE;
	PORTB = 0x01;//Ini3alize outputs	
	state = Start;//Indicates ini3al call	
	while(1){
		Tick();
	}	
}			
