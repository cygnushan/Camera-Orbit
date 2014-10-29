#include "moto.h"

uint16 pulse;

void moto_set(uint8 speed,uint8 subdiv)
{
    uint16 OCR_value;
    
    mEN = 1;
    mCLK = 0;
    micro_step(subdiv);
    //pulse = 8*speed*subdiv;//����ÿ����������Ĭ�����ת��Ϊ3.6r/S,�ٶ�100,2*200*3.6
    pulse = 14.4*speed*subdiv;
    OCR_value = T1_FREQ/pulse - 1; 
    OCR1AH = OCR_value>>8;
    OCR1AL = OCR_value & 0x00ff; 
}

void moto_run(uint16 dist)
{
//    uint32 exp_cnt;   
//    TIMSK = TIMSK & (~0x10); //��T1�жϣ�
//    dist_cnt = 0;
//    exp_cnt = (uint32)16*subdiv*dist/3; //�ﵽ�þ�����Ҫ��������� 2*200*step/75��ÿ��0.375mm
//    TIMSK = TIMSK | 0x10;  //���жϣ��������
//    while(dist_cnt<exp_cnt)
//    {;}                    //�ȴ����е�Ŀ�����
//    TIMSK = TIMSK & (~0x10);//���жϷ��� 
//    dist_cnt = 0;
	run_finish = 0; 
	step_mode = 1;
	exp_dist = dist;  
	TIMSK = TIMSK | 0x10;  //���жϣ��������     
}


void moto_go()
{
    mCWW = 0;
    //dist_cnt = 0;
    TIMSK = TIMSK | 0x10;  //���жϣ��������
}

void moto_back()
{
    mCWW = 1;
    //dist_cnt = 0;
    TIMSK = TIMSK | 0x10;  //���жϣ��������
}

void moto_stop()
{
    TIMSK = TIMSK & (~0x10);//���ж�,���ֹͣ����CLK���룬����
    last_dist = now_dist;
    dist_cnt = 0;
    step_mode = 0;
    run_finish = 1;
}

void micro_step(uint8 subdiv)
{
    switch(subdiv)
    {
        case 1:
                mM1 = 0;mM2 = 0;mM3 = 0;
                break;
        case 2:
                mM1 = 1;mM2 = 0;mM3 = 0;
                break;
        case 4:
                mM1 = 0;mM2 = 1;mM3 = 0;
                break;
        case 8:
                mM1 = 1;mM2 = 1;mM3 = 0;
                break;
        case 16:
                mM1 = 0;mM2 = 0;mM3 = 1;
                break;
        case 32:
                mM1 = 1;mM2 = 0;mM3 = 1;
                break;
        case 64:
                mM1 = 0;mM2 = 1;mM3 = 1;
                break;
        case 128:
                mM1 = 1;mM2 = 1;mM3 = 1;
                break;
        default:
                break;
    }

}


/**************************************************************   
*  ����˵��������ģʽ���ú���                         *   
**************************************************************/  
void ManulMode(void)
{
    char *s_dist = (char *) malloc(5);
    
    uint8 esc_flag = 0;

    uint8 key_value;
    uint8 rock_type;
    //char *dist_str = "";
    
    uint8 run_flag = 0; 
    
    //dist_str = Int2Str(now_dist);
    itoa(now_dist,s_dist);
    Disp_Str1(1,5,s_dist);

    Set_Mode(OFF);
    while(!esc_flag)
    {
        if(time_10ms)  //10ms��ʱɨ�����    
        { 
            time_10ms = 0;
            *pRockValue=No_rock;
            rock_type = Read_Rocker(pRockValue); 
            
            if( rock_type & keyPressed )
            {
               ;
            }
            
            else if(rock_type & keyLong)
            {
                switch(*pRockValue)
                {
                	case Left:
                                if(now_dist>=max_dist)
                                {
                                	moto_stop();
                                    now_dist = max_dist;
                                }
                                if( (!run_flag) && (now_dist < max_dist))
                                {
                                	run_flag = 1;
                                    moto_go();
                                }
                                break;
                    case Down:
                                if(now_dist<=0)
                                {
                                	moto_stop();
                                    now_dist = 0;
                                }
                                if( (!run_flag) && (now_dist > 1))
                                {
                                	run_flag = 1;
                                    moto_back();
                                }
                                break;
                    default:
                    			break; 
                } 
                
                    
            	itoa(now_dist,s_dist);
                Disp_Str(1,5,"    ");
            	Disp_Str1(1,5,s_dist);

            } 
            
            else
            {   
                if(run_flag)
                {
                    run_flag = 0;
                    moto_stop();
                } 
            } 
            
            key_value= Read_keyboard();
			if(key_value != No_key)
			{
	        	switch(key_value)
	        	{
	        		case Esc: 
                        	Set_Mode(ON);
							if(MenuPoint[UserChooseR].ParentMenus != NULL) 
							{ 
						 		MenuPoint = MenuPoint[UserChooseR].ParentMenus; 
						 		UserChooseR = 0; 
						 		UserChooseC = 0; 
							} 
							esc_flag = 1;
							break;	
	        		case OK:
					    	//Set_Mode();
	  				 		break;
                    default:
                    		break;
				}

			}   

    	}
    } 
    
    free(s_dist);	 
	Clear_Scr();
	ShowMenu();
}

void moto_zero(char point)
{
	if(point == 'A')
    {
        mCWW = 1;
        moto_run(now_dist);
    }
    if(point == 'B')
    {
        mCWW = 0;
        moto_run(max_dist-now_dist);
    }    
}


/*
// Timer 0 output compare interrupt service routine  
interrupt [TIM0_COMP] void timer0_comp_isr(void)
{
// Place your code here
    unsigned int Int_len;
    unsigned int Int_step;
    
    CLK = ~CLK;
    clk_cnt++;
    Int_len = Str2Int(length);
    if(flag_1mm==0)
        {CWW = 0;}
    if(flag_1mm>=Int_len)
        {CWW = 1;}
    
    if(clk_cnt==85)//���ʱ���ź�3.2KHz 3200/75=42.6Pulse/mm
        {
            clk_cnt = 0;
            step_flag++;
            if(CWW)
                {
                    flag_1mm--;  
                }
            else
                {
                    flag_1mm++;
                }             
        }

    if(run_mode)
    {
        Int_step = Str2Int(step);

        //Int_interval = Str2Int(interval);

        if( step_flag == Int_step ) //������е���������
        {
            step_flag = 0;
            CLK = 0;
            TIMSK = TIMSK & 0xfd;//OCIE0 = 0 ��T0�ж�
            Focus   = 1;
            //delay_ms(10);
            Shutter = 1;//��ʼ�ع�
            TIMSK = TIMSK | 0x80;//OCIE2 = 1 ��T2�ж�
        }  
    }
    
}

//    if(flag_1ms == Expo_value)
//    {
//        taken++;
//        left = Str2Int(images) - taken;
//        if(left == 0)
//            {finished = 1;}
//        Shutter = 0;//�ع�ʱ�䵽��ֹͣ�ع�
//        Focus   = 0; 
//        TIMSK = TIMSK & 0x7f;//OCIE2 = 0; 
//        delay_ms(2000); 
//        TIMSK = TIMSK | 0x02;//OCIE0 = 1;
//        flag_1ms = 0;
//    }

*/
