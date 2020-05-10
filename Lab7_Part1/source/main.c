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
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include <avr/interrupt.h>
#include <stdio.h>
#include "../header/io.h"
#include "../header/timer.h"

#define SET_BIT(p,i) ((p) |= (1 << (i)))
#define CLR_BIT(p,i) ((p) &= ~(1 << (i)))
#define GET_BIT(p,i) ((p) & (1 << (i)))
          
/*-------------------------------------------------------------------------*/

#define DATA_BUS PORTC		// port connected to pins 7-14 of LCD display
#define CONTROL_BUS PORTD	// port connected to pins 4 and 6 of LCD disp.
#define RS 6			// pin number of uC connected to pin 4 of LCD disp.
#define E 7			// pin number of uC connected to pin 6 of LCD disp.

/*-------------------------------------------------------------------------*/

void LCD_ClearScreen(void) {
   LCD_WriteCommand(0x01);
}

void LCD_init(void) {

    //wait for 100 ms.
	delay_ms(100);
	LCD_WriteCommand(0x38);
	LCD_WriteCommand(0x06);
	LCD_WriteCommand(0x0f);
	LCD_WriteCommand(0x01);
	delay_ms(10);						 
}

void LCD_WriteCommand (unsigned char Command) {
   CLR_BIT(CONTROL_BUS,RS);
   DATA_BUS = Command;
   SET_BIT(CONTROL_BUS,E);
   asm("nop");
   CLR_BIT(CONTROL_BUS,E);
   delay_ms(2); // ClearScreen requires 1.52ms to execute
}

void LCD_WriteData(unsigned char Data) {
   SET_BIT(CONTROL_BUS,RS);
   DATA_BUS = Data;
   SET_BIT(CONTROL_BUS,E);
   asm("nop");
   CLR_BIT(CONTROL_BUS,E);
   delay_ms(1);
}

void LCD_DisplayString( unsigned char column, const unsigned char* string) {
   LCD_ClearScreen();
   unsigned char c = column;
   while(*string) {
      LCD_Cursor(c++);
      LCD_WriteData(*string++);
   }
}

void LCD_Cursor(unsigned char column) {
   if ( column < 17 ) { // 16x1 LCD: column < 9
						// 16x2 LCD: column < 17
      LCD_WriteCommand(0x80 + column - 1);
   } else {
      LCD_WriteCommand(0xB8 + column - 9);	// 16x1 LCD: column - 1
											// 16x2 LCD: column - 9
   }
}

void delay_ms(int miliSec) //for 8 Mhz crystal

{
    int i,j;
    for(i=0;i<miliSec;i++)
    for(j=0;j<775;j++)
  {
   asm("nop");
  }
}

enum State {Start, In, I, D, R} state;
unsigned char tmpA, tmpC, i = 0;
void Tick(){
	switch(state){
		case Start:	
			state = In;
			break;
		case In:
			if(tmpA == 1)
				state = I;
			else if(tmpA == 2)
				state = D;
			else if(tmpA == 3)
				state = R;
			else
				state = In;
			break;
		case I:
			if(tmpA == 0)
				state = In;
			else if(tmpA == 3)
				state = R;
			else{
				state = I;
				if(i < 9)
					i++;
			}
			break;
		case D:
			if(tmpA == 0)
				state = In;
			else if(tmpA == 3)
				state = R;
			else{
				state = D;
				if(i > 0)
					i--;
			}
			break;
		case R:
			if(tmpA == 0){
				state = In;
				i = 0;
				tmpC = 0;
			}
			else
				state = R;
			break;
		default:
			break;
	} //Transition

	switch(state){
		case Start:
			tmpC = 0;
			break;
		case In:
			break;
		case I:
			if(tmpC < 9 && i < 10)
				tmpC++;
			break;
		case D:
			if(tmpC > 0 && i > -1)
				tmpC--;
			break;
		case R:
			tmpC = 0;
			break;
		default:
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;
	PORTA = 0xFF;
	DDRC = 0xFF;
	PORTC = 0x00;
	DDRD = 0xFF;
	PORTD = 0x00;
	state = Start;
	TimerSet(1000);
	TimerOn();
	LCD_init();
	//LCD_DisplayString(1, "Hello World");
    /* Insert your solution below */
    while (1) {
	//continue;
	while(!TimerFlag);
	TimerFlag = 0;
	tmpA = ~PINA & 0x0F;
	Tick();
	LCD_Cursor(1);
	LCD_WriteData(tmpC + '0');

    }
    return 1;
}
