#include "motor.h"


void RunMotor()
{
    unsigned int nowrun;
    unsigned int Int_dist;
    
    //nowrun = clk_cnt*64/3;
    Int_step = Str2Int(step);
    Int_dist = Str2Int(distance); 
    Int_interval = Str2Int(interval);
     
    step_cnt = Int_step*256/3;
    if((clk_cnt%step_cnt) == 0) //如果运行到步进距离
    {
        OCIE0 = 0; //关T0中断
        delay_ms(50);
        Shutter = 0;//开始曝光
        OCIE2 = 1;//开T2中断
    } 
    
    
    
    

}

unsigned int Str2Int(eeprom unsigned char array)
{
    unsigned int IntValue;
    IntValue = array[0]*1000 + array[1]*100 + array[2]*10 +array[3];
    return IntValue;    
}