/*
 * LCD.h
 *
 * Created: 5/27/2024 10:10:34 PM
 *  Author: Mohamed Bahaa
 */ 


#ifndef LCD_H_
#define LCD_H_

#include <avr/io.h>

#define LCD_Data_Dir DDRB
#define LCD_Data_Out PORTB
#define LCD_Ctrl_Dir DDRD
#define LCD_Ctrl_Out PORTD

#define E PD0
#define RS PD1


void INT_LCD();
void LCD_cmd(unsigned char cmd);
void LCD_write(unsigned char data );
void write_string(char *str);
void LCD_gotoxy(unsigned char x,unsigned char y);



#endif /* LCD_H_ */