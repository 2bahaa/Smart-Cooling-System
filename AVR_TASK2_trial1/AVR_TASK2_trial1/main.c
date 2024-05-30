/*
 * main file 
 *
 * Created: 5/28/2024 4:50:41 AM
 *  Author: BAHAA AND BAHRAM
 *
 *   SMART COOLING SYSTEM 
 */ 




#include <avr/io.h>
#include "LCD.h"
#include "ADC.h"
#include "BIT_MATH.h"
#define F_CPU 16000000UL           // Fclk AT 16MHZ
#include <avr/delay.h>
#include <string.h>
#include <stdio.h>
#define channel 2                //setting channel of ADC 
#include "TIMER.h"
#include <avr/interrupt.h>
int TEMP_THRESHOLD = 30;     //Default Threshold
int main(void)
{   
	DDRB &=~ (1<<DDD2);
	PORTB |= (1<<PORTD2);
	EICRA|=(1<<ISC00);
	EIMSK|=(1<<INT0);
	DDRB &=~ (1<<DDD3);
	PORTB |= (1<<PORTD3);
	EICRA|=(1<<ISC10);
	EIMSK|=(1<<INT1);
	sei(); 
	DDRB |= (1<<DDB0);             //PB0 as Output 
    char temp[36];               //carry out array For LCD 
	LCD_Init();                 //LCD Initialization
    ADC_conf();                //ADC Configuration
	
	
	// MAIN PROGRAM
    while (1) 
    {
		// SENSING TEMPERATURE USING ADC
		
		uint16_t adc_value = ADC_Read(channel);                               // Read the ADC value from the LM35 sensor
		unsigned char temperature = (adc_value * 5.0 / 1024.0) * 100.0;      //Voltage-Temperature Relation
		
		//Condition if Temperature greater than or equal threshold(30) 
		if (temperature >= TEMP_THRESHOLD)
		{
			//configure AC
			PORTB |= (1<<PORTB0);     //Fan ON
			                            
			//LCD PRINT CONFIGURATION
			
			sprintf(temp,"Temperature:%d",temperature);           //copying value into LCD
			LCD_gotoxy(0,0);                                      //1st character place
	       write_string(temp); 
		   sprintf(temp,"ON,THRESHOLD:%d   ",TEMP_THRESHOLD);           //copying value into LCD
		    LCD_gotoxy(0,1);                                      //1st character place
		    write_string(temp);                                  //writing on display
			_delay_ms(400);                                       //delay before sensing timing condition
			
			
		 //condition to start timer to stop AC                
			if(temperature<TEMP_THRESHOLD)
		{	
			uint8_t timerOverflowCount;                              //overflow counter
			TCNT0=0;                                                // initialize counter to 0
			TCCR0A &=~ ((1<<WGM00) | (1<<WGM01));                  //configure Normal mode of TIMER0
			TCCR0B &=~ (1<<WGM02);                                //configure Normal mode of TIMER0
			TCCR0B |= ((1<<CS00) | (1<<CS02)) ;                  //start timer at pre-scale 1024
			while (!(TIFR0 & 1<<TOV0));                         //as long as TOV=0 >> do nth
			TIFR0 |= (1<< TOV0) ;                              // 0x01; //clear overflow flag
			timerOverflowCount++;                             //INCREEMENT COUNTER each time an Overflow Occur
			_delay_ms(200);                                   
			
			sprintf(temp,"OFF,THRESHOLD:%d   ",TEMP_THRESHOLD);                                //copying value into LCD
			LCD_gotoxy(0,1);                                      //1st character place
			write_string(temp);                                   //writing on display
			  
			  
	//If timer reaches 25 counts which is equivalent to 10 sec
			if (timerOverflowCount>=25)
			{
				PORTB &= ~(1 << PORTB0);                           //turn AC OFF
				_delay_ms(200);                                   //delay 
				timerOverflowCount=0;                            // clear the overflow counter			}
			
		}
			
		}
		
		else
		{
			PORTB &=~ (1<<PORTB0);
			sprintf(temp,"Temperature:%d",temperature);           //copying value into temp
			LCD_gotoxy(0,0);                                     //1st character place
			write_string(temp);                                 //writing on display
			
			sprintf(temp,"OFF,Threshold:%d   ",TEMP_THRESHOLD);                            //copying value into LCD
			LCD_gotoxy(0,1);                                  //1st character place
			write_string(temp);                              //writing on display
		}
		
	}
}
 ISR(INT0_vect){
	 PORTB ^=(1<<PORTB7);
	 TEMP_THRESHOLD++;
 }
 ISR(INT1_vect){
 PORTB ^=(1<<PORTB6);
 TEMP_THRESHOLD--;
 }


