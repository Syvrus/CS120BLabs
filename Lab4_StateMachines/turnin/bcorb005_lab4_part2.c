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
enum States{ Start, INIT, INCREMENT, DECREMENT, BOTH, RELEASE_I, RELEASE_D, RELEASE_B } state;	
unsigned char temp, A1, A2;
void Tick(){
switch(state){//Transi3ons
	case Start:
		state = INIT;
		break;
 	case INIT:
		if((PINA & 0x03) == 0x01){
			if(temp < 9){
				temp++;
				PORTC = temp;
			}
			state = INCREMENT;
		}
		if((PINA & 0x03) == 0x02){
			if(temp > 0){
				temp--;
				PORTC = temp;
			}
			state = DECREMENT;
		}
		if((PINA & 0x03) == 0x03)
			state = BOTH;
		break;
	case INCREMENT:
		if((PINA & 0x03) == 0x02){
			if(temp > 0){
				temp--;
				PORTC = temp;
			}
			state = DECREMENT;
		}
		if((PINA & 0x03) == 0x03){
			if(temp > 0){
				temp--;
				PORTC = temp;
			}
			state = BOTH;
		}
		if((PINA & 0x00) == 0x00)
			state = RELEASE_B;
		break;
	case DECREMENT:
		if((PINA & 0x03) == 0x01){
			if(temp < 9){
				temp++;
				PORTC = temp;
			}
			state = INCREMENT;
		}
		if((PINA & 0x03) == 0x03){
			if(temp < 9){
				temp++;
				PORTC = temp;
			}
			state = BOTH;
		}
		if((PINA & 0x03) == 0x00)
			state = RELEASE_B;
		break;
	case BOTH:
		if((PINA & 0x03) == 0x02)
			state = RELEASE_I;
		if((PINA & 0x03) == 0x01)
			state = RELEASE_D;
		if((PINA & 0x03) == 0x00)
			state = RELEASE_B;
		break;
	case RELEASE_I:
		if((PINA & 0x03) == 0x00)
			state = RELEASE_B;
		if((PINA & 0x03) == 0x01){
			if(temp < 9){
				temp++;
				PORTC = temp;
			}
			state = INCREMENT;
		}
		if((PINA & 0x03) == 0x03){
			if(temp < 9){
				temp++;
				PORTC = temp;
			}
			state = BOTH;
		}
		break;
	case RELEASE_D:
		if((PINA & 0x03) == 0x00)
			state = RELEASE_B;
		if((PINA & 0x03) == 0x02){
			if(temp > 0){
				temp--;
				PORTC = temp;
			}
			state = DECREMENT;
		}
		if((PINA & 0x03) == 0x03){
			if(temp > 0){
				temp--;
				PORTC = temp;
			}
			state = BOTH;
		}
		break;
	case RELEASE_B:
		temp = 0;
		PORTC = temp;
		if((PINA & 0x03) == 0x01){
			if(temp < 9){
				temp++;
				PORTC = temp;
			}
			state = INCREMENT;
		}
		if((PINA & 0x03) == 0x02){
			if(temp > 0){
				temp--;
				PORTC = temp;
			}
			state = DECREMENT;
		}
		if((PINA & 0x03) == 0x03)
			state = BOTH;
		break;
	default:
		state = Start;
		break;
}//Transi3ons	
switch(state){//State ac3ons	
	case INIT:
	case INCREMENT:
	case DECREMENT:
	case BOTH:
	case RELEASE_I:
	case RELEASE_D:
	case RELEASE_B:
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
	}	
}	
