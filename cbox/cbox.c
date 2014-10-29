/*****************************************************
Project : 
Version : 
Date    : 2013-10-15
Author  : cygnus
Company : hust
Comments: 


Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*****************************************************/

#include "main.h"

uint8 DisplayStart; //显示时的第一个菜单项
uint8 DisplayPoint; //显示指针
uint8 MaxItems;    //同层显示节点数

//extern struct MenuItem
//{
//    unsigned char MenuCount;
//    flash unsigned char *DisplayString;
//    void (*Subs)();
//    struct MenuItem *ChildrenMenus;
//    struct MenuItem *ParentMenus;
//};
//
//struct MenuItem *TempMenu;
//extern struct MenuItem *MenuPoint;

#pragma warn-
eeprom unsigned char images[5]= "0100";
eeprom unsigned char interval[5]="0005";
eeprom unsigned char step[5]= "0010";
eeprom unsigned char dist[5]="1235";

eeprom unsigned char str_speed[5]= "0060";

eeprom unsigned char divid[5]= "0016";

eeprom unsigned char TV[5]= "0002";

eeprom float e_coef = 1.0; //曝光校准系数
eeprom float e_AV = 2.8;  //光圈值
eeprom unsigned int e_ISO = 0; //感光度(0 -> 100,1 -> 200,2 -> 400)
eeprom unsigned char expos_mode = camera; //曝光控制模式
eeprom unsigned char e_HDR = 0;  //HDR曝光范围 0-6EV
eeprom unsigned char e_ND = 0;  //ND滤镜减光值 0-10EV
#pragma warn+

uint8 work_mode;

uint8 key_value;
uint8 rocker_type;
uint8 *pRockValue;

uint8 subdiv;
uint8 int_speed;
uint16 Int_step;

uint8 run_type; //运动类型，水平 0 垂直 1

uint8  step_mode = 1;
uint16 exp_dist = 0;
int16 now_dist = 0;
int16 last_dist = 0;
uint16 temp_dist = 0;
uint32 dist_cnt = 0; //距离脉冲计数

unsigned char UserChooseR = 0;   //用户所选菜单项，行号
unsigned char UserChooseC = 0;   //列号
//unsigned char finished = 0;
//unsigned char clk_cnt = 0;
//unsigned int step_flag = 0;

uint16 photo_taken = 0;
uint16 photo_left;
uint16 exp_photos;
uint32 expos_value;
uint16 delay_value;

uint16 cnt_10ms = 0;
uint32 flag_1ms = 0;
uint8  time_10ms = 0;
uint8  calc_flag = 0;
uint8  run_finish = 1;
uint8  expos_finish = 0; //曝光结束标志
uint8  delay_finish = 0; //延时结束
uint8 work_state = idle_state;

interrupt [TIM0_COMP] void timer0_comp_isr(void)
{
    time_10ms = 1;
    calc_flag = 1;
    cnt_10ms++; 
    
    if(cnt_10ms == delay_value*100)
    {
    	delay_finish = 1;
    	cnt_10ms = 0;
    }

}

interrupt [TIM1_COMPA] void timer1_compa_isr(void)
{
    mCLK = ~mCLK;
    dist_cnt++; 
    if(calc_flag) //每10ms计算一次距离
    {
    	calc_flag = 0;
        temp_dist = 3*dist_cnt/(16*subdiv);
    	if(0==mCWW)
    	{
        	now_dist = last_dist + temp_dist;
    		if(now_dist >= max_dist)
            {
            	moto_stop();
                now_dist = max_dist;
            }            
    	}
    	else
    	{
    		now_dist = last_dist - temp_dist;
            if(now_dist < 0)
            {
            	moto_stop();
                now_dist = 0;
            }
    	}

    	if(step_mode)
    	{
            if(temp_dist >= exp_dist)
    		{
    			moto_stop();
    		}
    	}
    }
}

// Timer2 output compare interrupt service routine  短时曝光
interrupt [TIM2_COMP] void timer2_comp_isr(void)
{
// Place your code here
    flag_1ms++;

    if(flag_1ms == expos_value)
    {
    	Shutter = 0; 
    	Focus = 0;
    	flag_1ms = 0;
        expos_finish = 1;
    }
}
// Declare your global variables here


uint16 Str2Int(eeprom unsigned char array[])
{
    uint16 IntValue;
    IntValue = (array[0]-0x30)*1000 + (array[1]-0x30)*100 + (array[2]-0x30)*10 + (array[3]-0x30);
    return IntValue;    
}

unsigned char *Int2Str(unsigned int IntValue)
{
    uint8 i;
    static unsigned char Str[5];
    Str[0] = IntValue/1000;
    Str[1] = IntValue/100 - Str[0]*10;
    Str[2] = IntValue/10 - Str[0]*100 -Str[1]*10;
    Str[3] = IntValue%10;
	for (i=0;i<4;i++)
	{
		Str[i] = Str[i] + 0x30;
	}    
    return Str;    
}

void main(void)
{
	sys_init();
    //初始化电机控制信号
    //subdiv = 16;
    moto_set(int_speed,subdiv);
    //Shutter = 0;
    //Focus = 0; 
    //moto_run(100);  

	// Global enable interrupts
	#asm("sei")
    
    Lcd_Init();
    delay_ms(5);
    Init_BH1750();       //初始化BH1750
    
    Clear_Scr();                 
	MenuInitialation(); 
    ShowMenu();
    UserChooseR = 1; 
    
	while(1)   
	{ 
        if(time_10ms)  //10ms定时扫描键盘    
        { 
        	time_10ms = 0;   
        	*pRockValue=No_rock;
        	rocker_type = Read_Rocker(pRockValue);
			if(rocker_type == keyPressed)
			{
            	switch(*pRockValue)   
				{      
					case  Down:   
					  		UserChooseR ++;   
					  		if(UserChooseR == 3)   
					  		{   
								UserChooseR = 1;   
					  		}   
					  		break;				  
					case  Enter:
					  		TempMenu = MenuPoint;
					  		Clear_Scr(); 
					  		if(MenuPoint[UserChooseR].ChildrenMenus != NULL)   
					  		{   
						  		MenuPoint = MenuPoint[UserChooseR].ChildrenMenus;   
						  		//UserChooseR = 0;   
						  		//DisplayStart = 0;   
					  		} 
					  		ShowMenu(); 					  
                      		if(TempMenu[UserChooseR].Subs != NULLSubs)   
					  		{   
						 		(*TempMenu[UserChooseR].Subs)();
					  		} 
					  		//Clear_Scr();					
					  		break;		 
				}

            	Set_Cursor(UserChooseR,1);

        		//ShowMenu();
        	}

        	key_value= Read_keyboard();
			if(key_value != No_key)
			{
	        	switch(key_value)
	        	{
	        		case Esc:
                		work_mode = 0;
                        work_state = idle_state;
                        //TIMSK &= ~(1<<OCIE2);
						break;	
	        		case OK: 
                        work_mode = 1;
                        //TIMSK |= (1<<OCIE2); 
	  				 	break;
                	case 0:
                        moto_zero('A');
                        break; 
                	case 1:
                		moto_zero('B');
                        break;
                	default:
                		break;	
				}

        	} 

        }     
	    
        
    	switch(work_state)
        {
            	case idle_state:
                				if(work_mode)
                                {
                                	work_state = step_run;
                                }
                                break;
        		case step_run:
            					moto_run(Int_step);
                    			work_state = start_expos;    
                    			break;
        		case start_expos:
            					if(run_finish)
                    			{
                    				if( expos_mode == camera )
                                    	{ expos_value = def_tv; } 
                                    else if( expos_mode == sensor )
                                    	{ expos_value = Get_TV();}
                                    else
                                    	{ expos_value = (long)1000*Str2Int(TV);}
                                    
                                    flag_1ms = 0;
                                    Shutter = 1;
                                    Focus = 1;	
                                	work_state = stop_expos;
                    			}
                            	break;
            	case stop_expos:
            					if(expos_finish)
                            	{
                                	expos_finish = 0;
                                    photo_taken++;
                                	photo_left = exp_photos - photo_taken;
                                	work_state = delay_state;
                                    cnt_10ms = 0;
                            	}
                            	break;
            	case delay_state:
            					if(photo_taken == exp_photos)
                            	{
                            		work_mode = 0;
                            	}
            					if(delay_finish)
                            	{
                            		delay_finish = 0;
                                    work_state = idle_state;
                            	}
                            	break;
            	default:
            			break;

        } 

    }    
} 

void sys_init()
{
	PORTA=0x00;
	DDRA=0x0F;
	PORTB=0x00;
	DDRB=0xFF;
	PORTC=0xFF;
	DDRC=0xFF;

	PORTD=0x0F;
	DDRD=0xF0; //PD0-PD3输入 PD4-PD7输出

	// Timer/Counter 0 initialization
	// Clock source: System Clock
	// Clock value: 8000.000 kHz
	// Mode: CTC top=OCR0
	// OC0 output: Disconnected
	TCCR0=0x0d; //1024分频
	//TCNT0=0x00;
	OCR0=0x4D; //10ms
 
    // Timer/Counter 1 initialization
    TCCR1A=0x00;
    TCCR1B=0x0b;  //64分频
    OCR1AH=0x00;
    OCR1AL=0x00;

    
	// Timer/Counter 2 initialization  //1ms  
	TCCR2=0x0B;  //32分频
	OCR2=0xF9;

	TIMSK |= (1<<OCIE0)|(1<<OCIE2); //使能T0中断 
    
    mEN = 1;
    mCWW = 0; 

	work_mode = 0;
    
    Int_step = Str2Int(step);
    subdiv = Str2Int(divid);
    int_speed = Str2Int(str_speed); 
    delay_value = Str2Int(interval);
    
    exp_photos = Str2Int(images);
    photo_taken = 0;
    photo_left = exp_photos;
    
    run_type = Horizon;//水平运行
}

