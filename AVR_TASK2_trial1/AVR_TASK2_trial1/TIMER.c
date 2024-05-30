/*
 * TIMER.c
 *
 * Created: 5/28/2024 4:50:28 AM
 *  Author: Administrator
 */ 
#include "LCD.h"
#include "BIT_MATH.h"
#include <avr/io.h>
#include <avr/delay.h>

void TIMER_off(){
	uint8_t timerOverflowCount;
	TCNT0=0;
	TCCR0A &=~ ((1<<WGM00) | (1<<WGM01));
	TCCR0B &=~ (1<<WGM02);
	TCCR0B |= ((1<<CS00) | (1<<CS02)) ;
	while (!(TIFR0 & 1<<TOV0));                //as long as TOV=0 >> do nth
	TIFR0 |= (1<< TOV0) ;                      // 0x01; //clear overflow flag
	timerOverflowCount++;                     //counting number of overflows
	if (timerOverflowCount>=25)
	{
		PORTB &= ~(1 << PORTB0);
		_delay_ms(200);
		timerOverflowCount=0;	}
}