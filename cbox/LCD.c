#include "lcd.h"

/********************************************************************
* 名称 : Send_Byte()
* 功能 : 按照液晶的串口通信协议，发送数据
* 输入 : zdata
* 输出 : 无
***********************************************************************/
void Send_Byte(uint8 zdata)
{
    uint16 i;
    for(i=0; i<8; i++)
    {
        if((zdata << i) & 0x80)
        {
            SID = 1;
        }
        else 
        {
            SID = 0;
        }
        SCLK = 0;
        SCLK = 1;
    }
}

/********************************************************************
* 名称 : Write_Com()
* 功能 : 写指令
* 输入 : cmdcode
* 输出 : 无
***********************************************************************/
void Write_Com(uint8 cmdcode)
{
    CS = 1;
    Send_Byte(0xf8);
    Send_Byte(cmdcode & 0xf0);
    Send_Byte((cmdcode << 4) & 0xf0);
    delay_us(2);
}

/********************************************************************
* 名称 : Write_Data()
* 功能 : 写数据
* 输入 : data
* 输出 : 无
***********************************************************************/
void Write_Data(uint8 Dispdata)
{
    CS = 1;
    Send_Byte(0xfa);
    Send_Byte(Dispdata & 0xf0);
    Send_Byte((Dispdata << 4) & 0xf0);
    delay_us(2);
}

/********************************************************************
* 名称 : Clear_Scr()
* 功能 : 清屏
* 输入 : 无
* 输出 : 无
***********************************************************************/
void Clear_Scr(void)
{
  Write_Com(0x30);
  delay_us (100);
  Write_Com(0x01);
  delay_ms (20);
}

/********************************************************************
* 名称 : Lcd_Init()
* 功能 : 初始化函数
* 输入 : cmdcode
* 输出 : 无
***********************************************************************/
void Lcd_Init()
{  
    RST = 0;
    delay_ms(40);
    RST = 1;
    delay_us(100);
    Write_Com(0x30);//功能设定：8位控制接口，基本指令动作
    delay_us(50);
	Clear_Scr();
    Write_Com(0x06);//画面不移动，光标右移，AC自动加1
    delay_us(50);
    Write_Com(0x0d);//整体显示ON，光标显示ON，光标位置反白闪烁
    delay_us(50);
}


void Set_Mode(uint8 x)
{  
    if(x)
    {
        Write_Com(0x30);//功能设定：8位控制接口，基本指令动作
        delay_us(50);
        Write_Com(0x0d);//整体显示ON，光标显示ON，光标位置反白闪烁
        delay_us(50);
    } 
    else
    {
        Write_Com(0x30);//功能设定：8位控制接口，基本指令动作
        delay_us(50);
        Write_Com(0x0c);//整体显示ON，光标显示OFF，光标位置反白闪烁
        delay_us(50);    
    }
}


/********************************************************************
* 名称 : Set_Cursor()
* 功能 : 设置光标位置
* 输入 : 行号rows,列号columns
* 输出 : 无
***********************************************************************/
void Set_Cursor(uint8 rows,uint8 columns)
{
  uint8 i;
  switch(rows)
  {
    case 0x00: i=0x80; break;//第一行
	case 0x01: i=0x90; break;//第二行
	case 0x02: i=0x88; break;//第三行
	case 0x03: i=0x98; break;//第四行
	default : break;
  }
  i = columns + i;//列号
  Write_Com(i);//写地址
}

//显示字符函数
void Disp_Char(uint8 x,uint8 y,uint8 word)
{
	Set_Cursor(x,y);
    delay_us(10);
	Write_Data(word);
}

/********************************************************************
* 名称 : Disp_Str()
* 功能 : 在指定位置显示字符串
* 输入 : 行号x，列号y，字符串*s
* 输出 : 无
***********************************************************************/

void Disp_Str1(uint8 x,uint8 y,char *s)
{  
	Set_Cursor(x,y);
    while(*s > 0)
    { 
        Write_Data(*s);
        s++;
        delay_us(50);
    }
}

void Disp_Str(uint8 x,uint8 y,flash char *s)
{  
	Set_Cursor(x,y);
    while(*s > 0)
    { 
        Write_Data(*s);
        s++;
        delay_us(50);
    }
}

void Disp_Str_eeprom(uint8 x,uint8 y,eeprom char *s)
{  
	Set_Cursor(x,y);
    while(*s > 0)
    { 
        Write_Data(*s);
        s++;
        delay_us(50);
    }
}

