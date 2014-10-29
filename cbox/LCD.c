#include "lcd.h"

/********************************************************************
* ���� : Send_Byte()
* ���� : ����Һ���Ĵ���ͨ��Э�飬��������
* ���� : zdata
* ��� : ��
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
* ���� : Write_Com()
* ���� : дָ��
* ���� : cmdcode
* ��� : ��
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
* ���� : Write_Data()
* ���� : д����
* ���� : data
* ��� : ��
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
* ���� : Clear_Scr()
* ���� : ����
* ���� : ��
* ��� : ��
***********************************************************************/
void Clear_Scr(void)
{
  Write_Com(0x30);
  delay_us (100);
  Write_Com(0x01);
  delay_ms (20);
}

/********************************************************************
* ���� : Lcd_Init()
* ���� : ��ʼ������
* ���� : cmdcode
* ��� : ��
***********************************************************************/
void Lcd_Init()
{  
    RST = 0;
    delay_ms(40);
    RST = 1;
    delay_us(100);
    Write_Com(0x30);//�����趨��8λ���ƽӿڣ�����ָ���
    delay_us(50);
	Clear_Scr();
    Write_Com(0x06);//���治�ƶ���������ƣ�AC�Զ���1
    delay_us(50);
    Write_Com(0x0d);//������ʾON�������ʾON�����λ�÷�����˸
    delay_us(50);
}


void Set_Mode(uint8 x)
{  
    if(x)
    {
        Write_Com(0x30);//�����趨��8λ���ƽӿڣ�����ָ���
        delay_us(50);
        Write_Com(0x0d);//������ʾON�������ʾON�����λ�÷�����˸
        delay_us(50);
    } 
    else
    {
        Write_Com(0x30);//�����趨��8λ���ƽӿڣ�����ָ���
        delay_us(50);
        Write_Com(0x0c);//������ʾON�������ʾOFF�����λ�÷�����˸
        delay_us(50);    
    }
}


/********************************************************************
* ���� : Set_Cursor()
* ���� : ���ù��λ��
* ���� : �к�rows,�к�columns
* ��� : ��
***********************************************************************/
void Set_Cursor(uint8 rows,uint8 columns)
{
  uint8 i;
  switch(rows)
  {
    case 0x00: i=0x80; break;//��һ��
	case 0x01: i=0x90; break;//�ڶ���
	case 0x02: i=0x88; break;//������
	case 0x03: i=0x98; break;//������
	default : break;
  }
  i = columns + i;//�к�
  Write_Com(i);//д��ַ
}

//��ʾ�ַ�����
void Disp_Char(uint8 x,uint8 y,uint8 word)
{
	Set_Cursor(x,y);
    delay_us(10);
	Write_Data(word);
}

/********************************************************************
* ���� : Disp_Str()
* ���� : ��ָ��λ����ʾ�ַ���
* ���� : �к�x���к�y���ַ���*s
* ��� : ��
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

