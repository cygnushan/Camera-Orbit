#ifndef _H_MAIN
#define _H_MAIN

#define NULL 0
#define Horizon   0
#define Vertical  1

typedef  signed char  		int8;    // 8位有符号整型数
typedef  signed int     	int16;   //16位有符号整型数
typedef  signed long int    int32;   //32位有符号整型数
typedef  unsigned char      uint8;   // 8位无符号整型数
typedef  unsigned int       uint16;  //16位无符号整型数
typedef  unsigned long int  uint32;  //32位无符号整型数

//#include <STDLIB.H>
#include <math.h>      
#include <stdio.h> 
#include <stdlib.h>    
#include <mega16.h>
#include <delay.h>

#include "lcd.h"
#include "key.h"
#include "menu.h"
#include "moto.h"
#include "BH1750.h"

#define Shutter PORTB.3
#define Focus   PORTB.4

#define idle_state   0
#define step_run 	 1
#define start_expos  2
#define stop_expos	 3
#define delay_state	 4

#define camera  0x31
#define sensor  0x32
#define fixed   0x33

#define def_tv  200

extern uint16 photo_taken;
extern uint16 photo_left;
extern uint16 exp_photos;
extern uint16 delay_value;
extern uint32 expos_value;

extern uint8 DisplayStart; //显示时的第一个菜单项
extern uint8 DisplayPoint; //显示指针
extern uint8 MaxItems;    //同层显示节点数
//
//extern uint8 UserChooseC;
//extern uint8 UserChooseR;
extern float coef;
extern float AV;
extern uint16 Int_step;
extern uint8 int_speed;
extern uint8 subdiv;
extern uint8 time_10ms;
extern uint8 run_finish;
extern uint8 run_type;

extern uint8  step_mode;
extern uint16 exp_dist;
extern int16 now_dist;
extern int16 last_dist;
extern uint32 dist_cnt;

extern uint8 rocker_type;
extern uint8 *pRockValue;

extern unsigned int flag_1mm,taken,left;
extern uint8 UserChooseC;
extern uint8 UserChooseR;
extern uint8 key_value;
extern uint8 rocker_value;
extern uint8 lux_value[6];

extern eeprom unsigned char images[5],interval[5],dist[5],length[5];
extern eeprom unsigned char str_speed[5],step[5],divid[5];
extern eeprom unsigned char mode[3];
extern eeprom unsigned char TV[5];

extern eeprom float e_coef,e_AV;
extern eeprom unsigned int e_ISO;
extern eeprom unsigned char expos_mode;
extern eeprom unsigned char e_HDR,e_ND;

void sys_init();
#endif