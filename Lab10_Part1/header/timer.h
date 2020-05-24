#include <avr/interrupt.h>

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerOn(){
	//AVR timer/counter controller register TCCR1
	TCCR1B = 0x0B;
	//AVR output compare register OCR1A
	OCR1A = 125;
	//AVR timer interrupt mask register
	TIMSK1 = 0x02;
	//Initialize AVR counter
	TCNT1 = 0;
	_avr_timer_cntcurr = _avr_timer_M;
	//TimerISR will be called ever _avr_timer_cntcurr miliseconds
	//Enable global interrupts
	SREG |= 0x80;
}

void TimerOff(){
	TCCR1B = 0x00;
}

void TimerISR(){
	TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect) {
	_avr_timer_cntcurr--;
	if(_avr_timer_cntcurr == 0){
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void TimerSet(unsigned long M){
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}
