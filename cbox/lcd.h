#ifndef _H_LCD
#define _H_LCD

#include "main.h"

//LCD接口定义
#define RST  PORTD.4
#define CS   PORTD.5
#define SID  PORTD.6
#define SCLK PORTD.7

void Send_Byte(uint8 zdata);
void Write_Com(uint8 cmdcode);
void Write_Data(uint8 Dispdata);
void Clear_Scr(void);
void Lcd_Init();
void Set_Mode(uint8 x);
void Set_Cursor(uint8 rows,uint8 columns);
void Disp_Char(uint8 x,uint8 y,uint8 word);
void Disp_Str1(uint8 x,uint8 y,char *s);
void Disp_Str(uint8 x,uint8 y,flash char *s);
void Disp_Str_eeprom(uint8 x,uint8 y,eeprom char *s);

#endif