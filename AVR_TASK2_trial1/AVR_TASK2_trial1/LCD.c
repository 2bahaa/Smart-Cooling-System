

#include "LCD.h"
#include "BIT_MATH.h"
#include <avr/io.h>
#include <avr/delay.h>

void LCD_Init()
{
	DDRD=0XFF;
	LCD_cmd(0x02);
	LCD_cmd(0x28);
	LCD_cmd(0x0C);
	LCD_cmd(0x06);
	LCD_cmd(0x01);
	_delay_ms(2);

	
}

void LCD_cmd(unsigned char cmd)
{
	PORTD=(PORTD & 0X0F)|(cmd & 0xF0);
	Clear_Bit(LCD_Ctrl_Out,RS);
	Set_Bit(LCD_Ctrl_Out,E);
	_delay_us(1);
	Clear_Bit(LCD_Ctrl_Out,E);
	_delay_us(20);
	PORTD=(PORTD & 0X0F)|(cmd<<4);
	Set_Bit(LCD_Ctrl_Out,E);
	_delay_us(1);
	Clear_Bit(LCD_Ctrl_Out,E);
	_delay_ms(2);

}

void LCD_write(unsigned char data )
{
	
	PORTD=(PORTD & 0X0F)|(data & 0xF0);
	Set_Bit(LCD_Ctrl_Out,RS);
	Set_Bit(LCD_Ctrl_Out,E);
	_delay_us(1);
	Clear_Bit(LCD_Ctrl_Out,E);
	_delay_us(200);
	PORTD=(PORTD & 0X0F)|(data<<4);
	Set_Bit(LCD_Ctrl_Out,E);
	_delay_us(1);
	Clear_Bit(LCD_Ctrl_Out,E);
	_delay_ms(2);
}

void write_string(char *str)
{
	int i;
	for(i=0;str[i]!=0;i++)
	{
		LCD_write(str[i]);
	}
}

void LCD_gotoxy(unsigned char x,unsigned char y)
{
	if(y==0)
	{
		LCD_cmd(0x80+x);
	}
	if(y==1)
	{
		LCD_cmd(0XC0+x);
	}
	_delay_us(10);
}
