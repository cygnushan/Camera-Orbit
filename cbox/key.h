#ifndef _H_KEY
#define _H_KEY

#include "main.h"

#define state_keyUp         0       //��ʼ״̬,δ����  
#define state_keyDown       1       //��������  
#define state_keyTime       2       //������ʱ̬  
#define state_keyLong       3       //���� 

#define keyUp        0x00    //��ʼ״̬  
#define keyPressed   0x01    //��������,��ͨ����  
#define keyLong      0x02    //����  
#define keyAuto      0x04    //�Զ�����

#define RockX PIND.0
#define RockK PIND.1	
#define RockY PIND.2
#define Rock_mask 0x07
#define X_value		0x06
#define K_value		0x05
#define Y_value		0x03

#define No_rock 0x07
#define Down  0x03
#define Enter 0x05
#define Left  0x06

#define Esc   10
#define OK    11

#define No_key  255 
#define K1_1  	1 
#define K1_2  	2 
#define K1_3  	3 
#define K2_1  	4 
#define K2_2  	5 
#define K2_3  	6 
#define K3_1  	7 
#define K3_2  	8 
#define K3_3  	9 
#define K4_1  	10 
#define K4_2  	0 
#define K4_3    11 
#define Key_mask   0b11110000  //PA7-PA4��������

#define key_autotimes 20
#define key_longtimes 100

//static uint8 Get_RockValue(void);
uint8 Read_Rocker(uint8 *pRockValue);
uint8 Read_keyboard();

#endif