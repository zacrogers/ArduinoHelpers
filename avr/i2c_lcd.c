/*
 * i2c_lcd.c
 *
 * Created: 14-Jan-20 7:49:38 PM
 *  Author: Zac
 */ 

#include "i2c_lcd.h"


void LCD_Init (I2C_LCD *lcd)
{
	i2c_init();
	i2c_start(lcd->address << 1);
	
	LCD_SendCmd(lcd, LCD_HOME);
	//_delay_ms(100);
	LCD_SendCmd(lcd, LCD_MODE_4BIT);
	//_delay_ms(100);
	LCD_SendCmd(lcd, LCD_CUR_HOME_1);
	//_delay_ms(100);
	LCD_SendCmd(lcd, LCD_CLEAR);
	//_delay_ms(100);
	LCD_SendCmd(lcd, LCD_CUR_BLINK_ON);
}

void LCD_SendCmd(I2C_LCD *lcd, char cmd)
{
	char data_u, data_l;   // data upper nibble, data lower nibble
	uint8_t data_t[4];

	data_u = (cmd & 0xf0);
	data_l = ((cmd << 4) & 0xf0);

	data_t[0] = data_u | 0x0C;  //en=1, rs=0
	data_t[1] = data_u | 0x08;  //en=0, rs=0
	data_t[2] = data_l | 0x0C;  //en=1, rs=0
	data_t[3] = data_l | 0x08;  //en=0, rs=0

	i2c_transmit((lcd->address << 1), (uint8_t *) data_t, 4);
}

void LCD_SendData(I2C_LCD *lcd, char data)
{
	char data_u, data_l;
	uint8_t data_t[4];

	data_u = (data & 0xf0);
	data_l = ((data << 4) & 0xf0);

	data_t[0] = data_u | 0x0D;  //en=1, rs=0
	data_t[1] = data_u | 0x09;  //en=0, rs=0
	data_t[2] = data_l | 0x0D;  //en=1, rs=0
	data_t[3] = data_l | 0x09;  //en=0, rs=0

	i2c_transmit((lcd->address << 1), (uint8_t *) data_t, 4);
}

void LCD_Clear(I2C_LCD *lcd)
{
	LCD_SendCmd(lcd, LCD_CLEAR);
}

void LCD_EnableCursor(I2C_LCD *lcd)
{
	LCD_SendCmd(lcd, LCD_CUR_BLINK_ON);
}

void LCD_DisableCursor(I2C_LCD *lcd)
{
	LCD_SendCmd(lcd, LCD_DISP_ON_CUR_OFF);
}


void LCD_SendString (I2C_LCD *lcd, const char *str)
{
	while (*str) LCD_SendData(lcd, *str++);
}


void LCD_SetCursor(I2C_LCD *lcd, uint8_t line, uint8_t col)
{
	if(line == 0)
	{
		LCD_SendCmd(lcd, LCD_CUR_HOME_1);
	}
	
	else
	{
		LCD_SendCmd(lcd, LCD_CUR_HOME_2);
	}

	for(int i = 0; i < col; i++)
	{
		LCD_SendCmd(lcd, LCD_CURSOR_INCR);
	}
}


