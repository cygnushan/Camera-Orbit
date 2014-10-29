#ifndef _H_MENU
#define _H_MENU

#define ON 1
#define OFF 0

#include "main.h"

struct MenuItem
{
    unsigned char MenuCount;
    flash unsigned char *DisplayString;
    void (*Subs)();
    struct MenuItem *ChildrenMenus;
    struct MenuItem *ParentMenus;
};



extern struct MenuItem *MenuPoint;

extern struct MenuItem *TempMenu;

//extern unsigned int flag_1mm,taken,left;
//extern uint8 UserChooseC;
//extern uint8 UserChooseR;
//extern uint8 key_value;
//extern uint8 rocker_value;
//extern uint8 lux_value[6];
//extern unsigned int Expo_value;
//extern eeprom unsigned char images[5],interval[5],dist[5],length[5];
//extern eeprom unsigned char speed[5],step[5],divid[5];
//extern eeprom unsigned char mode[3];
//extern eeprom unsigned char light1[5],shutter1[5],light2[5],shutter2[5];
//extern eeprom unsigned char TV[5];

void MainMenuInit(void);
void StateMenuInit(void);
void PlanMenuInit(void);
void ExposureMenuInit(void);
void MenuInitialation(void);   
void ShowMenu(void);
void NULLSubs(void);
void SetShootPlan(void);
void SetPara(void);
void SetExposure(void);

void SetSensor(void);
void SetMotor(void);
void SetShutter(void);
void get_lux();

unsigned char *Int2Str(unsigned int IntValue);
unsigned int Str2Int(eeprom unsigned char array[]);

#endif