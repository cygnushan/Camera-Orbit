#ifndef _H_KEY
#define _H_KEY

#include "main.h"

#define state_keyUp         0       //初始状态,未按键  
#define state_keyDown       1       //键被按下  
#define state_keyTime       2       //按键计时态  
#define state_keyLong       3       //长按 

#define keyUp        0x00    //初始状态  
#define keyPressed   0x01    //键被按过,普通按键  
#define keyLong      0x02    //长按  
#define keyAuto      0x04    //自动连发

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
#define Key_mask   0b11110000  //PA7-PA4行线输入

#define key_autotimes 20
#define key_longtimes 100

//static uint8 Get_RockValue(void);
uint8 Read_Rocker(uint8 *pRockValue);
uint8 Read_keyboard();

#endif