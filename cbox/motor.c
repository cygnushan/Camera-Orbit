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
    if((clk_cnt%step_cnt) == 0) //������е���������
    {
        OCIE0 = 0; //��T0�ж�
        delay_ms(50);
        Shutter = 0;//��ʼ�ع�
        OCIE2 = 1;//��T2�ж�
    } 
    
    
    
    

}

unsigned int Str2Int(eeprom unsigned char array)
{
    unsigned int IntValue;
    IntValue = array[0]*1000 + array[1]*100 + array[2]*10 +array[3];
    return IntValue;    
}