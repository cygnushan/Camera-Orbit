#ifndef _H_MOTO
#define _H_MOTO

#include "main.h"

#define T1_FREQ  125000  // 8M/64分频
#define max_dist 1235    //滑轨有效长度1235mm

#define mCLK 	PORTC.2
#define mCWW 	PORTC.3
#define mM1  	PORTC.4
#define mM3  	PORTC.5
#define mM2  	PORTC.6
#define mEN  	PORTC.7

void micro_step(uint8 subdiv);
void moto_run(uint16 dist);
void moto_set(uint8 speed,uint8 subdiv);

void moto_go();
void moto_back();
void moto_stop();
void moto_zero(char point);

void ManulMode(void);

#endif