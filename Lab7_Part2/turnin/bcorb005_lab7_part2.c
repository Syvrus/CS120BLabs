/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
//Link: https://www.youtube.com/watch?v=6XuirMBYXWY
#include <avr/io.h>
#include "../header/timer.h"
#include "../header/io.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include <stdio.h>

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
unsigned char s[3] = {0x01, 0x02, 0x04};
unsigned i = 0, p = 0;

enum State{Start, Ascend, Descend, PauseP, PauseR} state;

unsigned tmpA, tmpD;

void Tick(){
	switch(state){
		case Start:
			p = 5;
			state = Ascend;
			break;
		case Ascend:
			if(tmpA == 1){
				if(i == 1){
					if(p < 9)
						p++;
				}
				else if(p > 0) 
					p--;
				state = PauseP;
			}
			else
			if(i == 2){
				state = Descend;
				//i = 0;
			}else
				state = Ascend;
			break;
		case Descend:
			if(tmpA == 1){
				if(i == 1){
					if(p < 9)
						p++;
				}
				else if(p > 0) 
					p--;
				state = PauseP;
			}
			else
			if(i == 0){
				state = Ascend;
				//i = 0;
			}
			else{
				state = Descend;
			}
			break;
		case PauseP:
			if(p == 9)
				LCD_DisplayString(1, "You Win");
			if(tmpA == 1){
				state = PauseP;	
			}else
				state = PauseR;
			break;
		case PauseR:
			if(tmpA == 1){
				if(p == 9){
					LCD_ClearScreen();
					p = 5;
				}
				i = 0;
				state = Ascend;
			}else{
				state = PauseR;
			}
			break;
		default:
			break;
	}

	switch(state){
		case Start:
			break;
		case Ascend:
			if(i < 3){
				tmpD = s[i];
				if(tmpA == 0)
					i++;
			}
			break;
		case Descend:
			if(i > 0){
				tmpD = s[i];
				if(tmpA == 0)
					i--;
			}
			break;
		case PauseP:
		case PauseR:
			tmpD = s[i];
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
	TimerSet(300);
	TimerOn();
	LCD_init();
	tmpD = 0x00;
    /* Insert your solution below */
    while (1) {
        while(!TimerFlag);
	TimerFlag = 0;
	tmpA = ~PINA & 0x01;
	Tick();
	PORTD = tmpD;
	if(p < 9){
		LCD_ClearScreen();
		LCD_Cursor(1);
		LCD_WriteData(p + '0');
	}


    }
    return 1;
}
