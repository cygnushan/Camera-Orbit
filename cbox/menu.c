#include "menu.h"

struct MenuItem MainMenu[4];
struct MenuItem StateMenu[4];
struct MenuItem PlanMenu[4];
struct MenuItem ParaMenu[4];
struct MenuItem ExposureMenu[4];
struct MenuItem SensorMenu[4];
struct MenuItem MotorMenu[4];
struct MenuItem ManulMenu[4];
struct MenuItem ShutterMenu[4];

struct MenuItem *TempMenu;
struct MenuItem *MenuPoint = MainMenu;


void NULLSubs(void) //空操作函数
{ 

}

/**************************************************************   
*  函数说明：状态显示函数                         *   
**************************************************************/  
void ShowState(void)
{
	char *s_taken = (char *) malloc(5); 
    char *s_left = (char *) malloc(5);
    char *s_dist = (char *) malloc(5);
    
    uint8 time_cnt = 0; 
    uint8 esc_flag = 0;
    //UserChooseR = 0;
    //Set_Cursor(0,0);

    itoa(photo_taken,s_taken);
    Disp_Str1(0,2,s_taken);

    itoa(photo_left,s_left);
    Disp_Str1(0,6,s_left); 

    itoa(now_dist,s_dist);
    Disp_Str1(1,5,s_dist);

    Set_Mode(OFF);
    while(!esc_flag)
    {
        if(time_10ms)  //10ms定时扫描键盘    
        { 
        	time_10ms = 0; 

			key_value= Read_keyboard();
			if(key_value == Esc)
			{
            	Set_Mode(ON);
            	if(MenuPoint[UserChooseR].ParentMenus != NULL) 
            	{ 
             		MenuPoint = MenuPoint[UserChooseR].ParentMenus; 
             		UserChooseR = 1; 
             		UserChooseC = 1; 
            	} 
            	esc_flag = 1;	
			} 
            
            if(++time_cnt == 100)
            {
                time_cnt = 0;
                
        		//s_taken = Int2Str(photo_taken);
        		itoa(photo_taken,s_taken);
        		Disp_Str(0,2,"    ");
        		Disp_Str1(0,2,s_taken);

        		//s_left = Int2Str(photo_left);
        		itoa(photo_left,s_left);
        		Disp_Str(0,6,"    ");
        		Disp_Str1(0,6,s_left); 

        		//dist_str = Int2Str(now_dist);
        		itoa(now_dist,s_dist);
        		Disp_Str(1,5,"    ");
        		Disp_Str1(1,5,s_dist);
        		//delay_ms(50);
            }
        }           
    }
    
    
    free(s_taken);
	free(s_left);
    free(s_dist);
    Clear_Scr();
	ShowMenu();
}

/**************************************************************   
*  函数说明：State目录初始化函数                         *   
**************************************************************/  
void StateMenuInit(void)
{
    StateMenu[0].MenuCount = 4;   
    StateMenu[0].DisplayString = "已拍    剩余";   
    StateMenu[0].Subs = NULLSubs;   
    StateMenu[0].ChildrenMenus = NULL;   
    StateMenu[0].ParentMenus = MainMenu;   
       
    StateMenu[1].MenuCount = 4;   
    StateMenu[1].DisplayString = "当前行程      MM";   
    StateMenu[1].Subs = NULLSubs;   
    StateMenu[1].ChildrenMenus = NULL;   
    StateMenu[1].ParentMenus = MainMenu;   
       
    StateMenu[2].MenuCount = 4;   
    StateMenu[2].DisplayString = "运行时间00:00:00";   
    StateMenu[2].Subs = NULLSubs;   
    StateMenu[2].ChildrenMenus = NULL;   
    StateMenu[2].ParentMenus = MainMenu;   
       
    StateMenu[3].MenuCount = 4;   
    StateMenu[3].DisplayString = "剩余时间00:00:00";   
    StateMenu[3].Subs = NULLSubs;   
    StateMenu[3].ChildrenMenus = NULL;   
    StateMenu[3].ParentMenus = MainMenu;   
}

/**************************************************************   
*  函数说明：Plan目录初始化函数                          *     
**************************************************************/  
void PlanMenuInit(void)
{
    PlanMenu[0].MenuCount = 4;   
    PlanMenu[0].DisplayString = "拍摄张数:";   
    PlanMenu[0].Subs = NULLSubs;   
    PlanMenu[0].ChildrenMenus = NULL;   
    PlanMenu[0].ParentMenus = ParaMenu;   
       
    PlanMenu[1].MenuCount = 4;   
    PlanMenu[1].DisplayString = "拍摄间隔:      S";   
    PlanMenu[1].Subs = NULLSubs;   
    PlanMenu[1].ChildrenMenus = NULL;   
    PlanMenu[1].ParentMenus = ParaMenu;   
       
    PlanMenu[2].MenuCount = 4;   
    PlanMenu[2].DisplayString = "步进距离:     MM";   
    PlanMenu[2].Subs = NULLSubs;   
    PlanMenu[2].ChildrenMenus = NULL;   
    PlanMenu[2].ParentMenus = ParaMenu;   
       
    PlanMenu[3].MenuCount = 4;   
    PlanMenu[3].DisplayString = "计划行程:     MM";   
    PlanMenu[3].Subs = NULLSubs;   
    PlanMenu[3].ChildrenMenus = NULL;   
    PlanMenu[3].ParentMenus = ParaMenu;   
}


/**************************************************************   
*  函数说明：手动模式初始化函数                          *    
**************************************************************/  
void ManulMenuInit(void)
{
    ManulMenu[0].MenuCount = 4;   
    ManulMenu[0].DisplayString = "****手动模式****";   
    ManulMenu[0].Subs = NULLSubs;   
    ManulMenu[0].ChildrenMenus = NULL;   
    ManulMenu[0].ParentMenus = ParaMenu;   
       
    ManulMenu[1].MenuCount = 4;   
    ManulMenu[1].DisplayString = "当前位置      mm";   
    ManulMenu[1].Subs = NULLSubs;   
    ManulMenu[1].ChildrenMenus = NULL;   
    ManulMenu[1].ParentMenus = ParaMenu; 

    ManulMenu[2].MenuCount = 4;   
    ManulMenu[2].DisplayString = "按←前进按↓后退";   
    ManulMenu[2].Subs = NULLSubs;   
    ManulMenu[2].ChildrenMenus = NULL;   
    ManulMenu[2].ParentMenus = ParaMenu; 

    ManulMenu[3].MenuCount = 4;   
    ManulMenu[3].DisplayString = "    松开即停    ";   
    ManulMenu[3].Subs = NULLSubs;   
    ManulMenu[3].ChildrenMenus = NULL;   
    ManulMenu[3].ParentMenus = ParaMenu;    
}

/**************************************************************   
*  函数说明：Exposure目录初始化函数                          *  
**************************************************************/  
void ExposureMenuInit(void)
{
    ExposureMenu[0].MenuCount = 4;   
    ExposureMenu[0].DisplayString = "当前模式:";   
    ExposureMenu[0].Subs = NULLSubs;   
    ExposureMenu[0].ChildrenMenus = NULL;   
    ExposureMenu[0].ParentMenus = ParaMenu;   
       
    ExposureMenu[1].MenuCount = 4;   
    ExposureMenu[1].DisplayString = "1.相机控制";   
    ExposureMenu[1].Subs = NULLSubs;   
    ExposureMenu[1].ChildrenMenus = NULL;   
    ExposureMenu[1].ParentMenus = ParaMenu;   
       
    ExposureMenu[2].MenuCount = 4;   
    ExposureMenu[2].DisplayString = "2.光传感器";   
    ExposureMenu[2].Subs = SetSensor;   
    ExposureMenu[2].ChildrenMenus = SensorMenu;   
    ExposureMenu[2].ParentMenus = ParaMenu;   
       
    ExposureMenu[3].MenuCount = 4;   
    ExposureMenu[3].DisplayString = "3.自定义";   
    ExposureMenu[3].Subs = SetShutter;   
    ExposureMenu[3].ChildrenMenus = ShutterMenu;   
    ExposureMenu[3].ParentMenus = ParaMenu;   
}

/**************************************************************   
*  函数说明：自定义曝光目录初始化                                     *     
**************************************************************/   
void ShutterMenuInit(void)   
{   
     ShutterMenu[0].MenuCount = 4;   
     ShutterMenu[0].DisplayString = "曝光时间:      S";   
     ShutterMenu[0].Subs = NULLSubs;   
     ShutterMenu[0].ChildrenMenus = NULL;   
     ShutterMenu[0].ParentMenus = ExposureMenu;   
 
     ShutterMenu[1].MenuCount = 4;   
     ShutterMenu[1].DisplayString = "";   
     ShutterMenu[1].Subs = NULLSubs;   
     ShutterMenu[1].ChildrenMenus = NULL;   
     ShutterMenu[1].ParentMenus = ExposureMenu;   
   
     ShutterMenu[2].MenuCount = 4;   
     ShutterMenu[2].DisplayString = "";   
     ShutterMenu[2].Subs = NULLSubs;   
     ShutterMenu[2].ChildrenMenus = NULL;     
     ShutterMenu[2].ParentMenus = ExposureMenu;   
        
     ShutterMenu[3].MenuCount = 4;   
     ShutterMenu[3].DisplayString = "";   
     ShutterMenu[3].Subs = NULLSubs;   
     ShutterMenu[3].ChildrenMenus = NULL;       
     ShutterMenu[3].ParentMenus = ExposureMenu;   
} 

/**************************************************************   
*  函数说明：根目录初始化                                     *     
**************************************************************/   
void MainMenuInit(void)   
{   
     MainMenu[0].MenuCount = 4;   
     MainMenu[0].DisplayString = "******菜单******";   
     MainMenu[0].Subs = NULLSubs;   
     MainMenu[0].ChildrenMenus = NULL;   
     MainMenu[0].ParentMenus = NULL;   
 
     MainMenu[1].MenuCount = 4;   
     MainMenu[1].DisplayString = "  1.当前状态";   
     MainMenu[1].Subs = ShowState;   
     MainMenu[1].ChildrenMenus = StateMenu;   
     MainMenu[1].ParentMenus = NULL;   
   
     MainMenu[2].MenuCount = 4;   
     MainMenu[2].DisplayString = "  2.参数设置";   
     MainMenu[2].Subs = SetPara;   
     MainMenu[2].ChildrenMenus = ParaMenu;     
     MainMenu[2].ParentMenus = NULL;   
        
     MainMenu[3].MenuCount = 4;   
     MainMenu[3].DisplayString = "开始(#) 停止(*)";   
     MainMenu[3].Subs = NULLSubs;   
     MainMenu[3].ChildrenMenus = NULL;       
     MainMenu[3].ParentMenus = NULL;   
} 

/**************************************************************   
*  函数说明：Parameter目录初始化函数                          *  
**************************************************************/  
void ParaMenuInit(void)
{
    ParaMenu[0].MenuCount = 4;   
    ParaMenu[0].DisplayString = "1.拍摄计划";   
    ParaMenu[0].Subs = SetShootPlan;   
    ParaMenu[0].ChildrenMenus = PlanMenu;   
    ParaMenu[0].ParentMenus = MainMenu;   
       
    ParaMenu[1].MenuCount = 4;   
    ParaMenu[1].DisplayString = "2.曝光模式";   
    ParaMenu[1].Subs = SetExposure;   
    ParaMenu[1].ChildrenMenus = ExposureMenu;   
    ParaMenu[1].ParentMenus = MainMenu;   
       
    ParaMenu[2].MenuCount = 4;   
    ParaMenu[2].DisplayString = "3.电机设置";   
    ParaMenu[2].Subs = SetMotor;   
    ParaMenu[2].ChildrenMenus = MotorMenu;   
    ParaMenu[2].ParentMenus = MainMenu;   
       
    ParaMenu[3].MenuCount = 4;   
    ParaMenu[3].DisplayString = "4.手控模式";   
    ParaMenu[3].Subs = ManulMode;   
    ParaMenu[3].ChildrenMenus = ManulMenu;   
    ParaMenu[3].ParentMenus = MainMenu;   
}

/**************************************************************   
*  函数说明：光传感器设置目录初始化函数                          *  
**************************************************************/  
void SensorMenuInit(void)
{
    SensorMenu[0].MenuCount = 4;   
    SensorMenu[0].DisplayString = "F:    ISO:";   
    SensorMenu[0].Subs = NULLSubs;   
    SensorMenu[0].ChildrenMenus = NULL;   
    SensorMenu[0].ParentMenus = ExposureMenu;   
       
    SensorMenu[1].MenuCount = 4;   
    SensorMenu[1].DisplayString = "快门:         ms";   
    SensorMenu[1].Subs = NULLSubs;   
    SensorMenu[1].ChildrenMenus = NULL;   
    SensorMenu[1].ParentMenus = ExposureMenu;   
       
    SensorMenu[2].MenuCount = 4;   
    SensorMenu[2].DisplayString = "补偿系数:";   
    SensorMenu[2].Subs = NULLSubs;   
    SensorMenu[2].ChildrenMenus = NULL;   
    SensorMenu[2].ParentMenus = ExposureMenu;   
       
    SensorMenu[3].MenuCount = 4;   
    SensorMenu[3].DisplayString = "HDR:±   ND:  EV";   
    SensorMenu[3].Subs = NULLSubs;   
    SensorMenu[3].ChildrenMenus = NULL;   
    SensorMenu[3].ParentMenus = ExposureMenu;  
}

/**************************************************************   
*  函数说明：电机参数设置目录初始化函数                          *  
**************************************************************/  
void MotorMenuInit(void)
{
    MotorMenu[0].MenuCount = 4;   
    MotorMenu[0].DisplayString = "****电机参数****";
    MotorMenu[0].Subs = NULLSubs;   
    MotorMenu[0].ChildrenMenus = NULL;   
    MotorMenu[0].ParentMenus = ParaMenu;   
       
    MotorMenu[1].MenuCount = 4;   
    MotorMenu[1].DisplayString = "速度:      %";   
    MotorMenu[1].Subs = NULLSubs;   
    MotorMenu[1].ChildrenMenus = NULL;   
    MotorMenu[1].ParentMenus = ParaMenu;   
       
    MotorMenu[2].MenuCount = 4;   
    MotorMenu[2].DisplayString = "细分:";   
    MotorMenu[2].Subs = NULLSubs;   
    MotorMenu[2].ChildrenMenus = NULL;   
    MotorMenu[2].ParentMenus = ParaMenu;   
       
    MotorMenu[3].MenuCount = 4;   
    MotorMenu[3].DisplayString = "模式:";   
    MotorMenu[3].Subs = NULLSubs;   
    MotorMenu[3].ChildrenMenus = NULL;   
    MotorMenu[3].ParentMenus = ParaMenu;  
}

/**************************************************************   
*  函数说明：目录初始化函数                                   *  
**************************************************************/   
void MenuInitialation(void)   
{  
    MainMenuInit();   
    StateMenuInit();   
    PlanMenuInit();   
    ParaMenuInit();   
    ExposureMenuInit(); 
    SensorMenuInit();
    MotorMenuInit();
    ManulMenuInit();
    ShutterMenuInit();	
} 

/**************************************************************   
*  函数说明：目录显示函数                                     *   
**************************************************************/   
void ShowMenu(void)   
{   
    unsigned char n = 0; 
    MaxItems = MenuPoint[0].MenuCount;   
    DisplayPoint = DisplayStart;    
	for(n = 0;n<MaxItems;n++)   
	{   				  
		Disp_Str(n,0,MenuPoint[DisplayPoint++].DisplayString);
	}
	Set_Cursor(1,1);
}   

/**************************************************************   
*  函数说明：参数设置函数                                     *   
**************************************************************/ 
void SetPara(void)
{
    uint8 esc_flag = 0;
    UserChooseR = 0;
    Set_Cursor(0,0);
    while(!esc_flag)
    {
        if(time_10ms)  //10ms定时扫描键盘    
        { 
        time_10ms = 0; 
		*pRockValue=No_rock;
        rocker_type = Read_Rocker(pRockValue);
		if(rocker_type & keyPressed)
		{
			switch(*pRockValue)   
			{      
				case  Down:   
					  UserChooseR ++;   
					  if(UserChooseR == 4)   
					  {   
						UserChooseR = 0;   
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
			
            Set_Cursor(UserChooseR,0);
		}
        
		key_value= Read_keyboard();
		if(key_value != No_key)
		{
	        switch(key_value)
	        {
	        	case Esc:
						if(MenuPoint[UserChooseR].ParentMenus != NULL) 
						{ 
						 MenuPoint = MenuPoint[UserChooseR].ParentMenus; 
						 UserChooseR = 1; 
						 UserChooseC = 1; 
						} 
						esc_flag = 1;
						break;	
	        	case OK:
					    //Set_Mode();
	  				 	break;	
			}

		}

    	}        
    }
	Clear_Scr();
	ShowMenu();
}



/**************************************************************   
*  函数说明：拍摄设置函数                                     *   
**************************************************************/ 
void SetShootPlan(void)
{
	uint8 esc_flag = 0;
	uint8 count = 0;

    Disp_Str_eeprom(0,5,images);
	Disp_Str_eeprom(1,5,interval);
	Disp_Str_eeprom(2,5,step);
	Disp_Str_eeprom(3,5,dist);

	UserChooseR = 0;
	UserChooseC = 6;
    Set_Cursor(UserChooseR,UserChooseC);
	while(!esc_flag)
	{
        if(time_10ms)  //10ms定时扫描键盘    
        { 
        time_10ms = 0; 
		*pRockValue=No_rock;
        rocker_type = Read_Rocker(pRockValue);
		if(rocker_type & keyPressed)
		{
			switch(*pRockValue)   
			{      
				case  Down:   
					  UserChooseR ++;   
					  if(UserChooseR == 4)   
					  {   
						UserChooseR = 0;   
					  }   
					  break;
				case  Left:	
					  UserChooseC --;   
					  if(UserChooseC == 4)   
					  {	
					    UserChooseC = 6;	 
					  }	
					  break;
			}			

            Set_Cursor(UserChooseR,UserChooseC);
		}


		key_value= Read_keyboard();
		if(key_value != No_key)
		{
	        switch(key_value)
	        {
	        	case Esc:
						if(MenuPoint[UserChooseR].ParentMenus != NULL) 
						{ 
						 MenuPoint = MenuPoint[UserChooseR].ParentMenus; 
						 UserChooseR = 0; 
						 UserChooseC = 0;
						 //DisplayStart = 0; 
						} 
						esc_flag = 1;
						break;	
	        	case OK:
					    //Set_Mode();
	  				 	break;
				default:
						switch(UserChooseR)
						{
							case 0:
									if(UserChooseC==5)
									{
										if(count==0)
											images[0] = key_value + 0x30;
										else
											images[1] = key_value + 0x30;
									}
									if(UserChooseC==6)
									{
										if(count==0)
											images[2] = key_value + 0x30;
										else
											images[3] = key_value + 0x30;
									}
									Disp_Str_eeprom(0,5,images);
                                    exp_photos = Str2Int(images);
									break;
							case 1:
									if(UserChooseC==5)
									{
										if(count==0)
											interval[0] = key_value + 0x30;
										else
											interval[1] = key_value + 0x30;
									}
									if(UserChooseC==6)
									{
										if(count==0)
											interval[2] = key_value + 0x30;
										else
											interval[3] = key_value + 0x30;
									}
									Disp_Str_eeprom(1,5,interval);
                                    delay_value = Str2Int(interval);
									break;
							case 2:
									if(UserChooseC==5)
									{
										if(count==0)
											step[0] = key_value + 0x30;
										else
											step[1] = key_value + 0x30;
									}
									if(UserChooseC==6)
									{
										if(count==0)
											step[2] = key_value + 0x30;
										else
											step[3] = key_value + 0x30;
									}
									Disp_Str_eeprom(2,5,step);
                                    Int_step = Str2Int(step);
									break;
							case 3:
									if(UserChooseC==5)
									{
										if(count==0)
											dist[0] = key_value + 0x30;
										else
											dist[1] = key_value + 0x30;
									}
									if(UserChooseC==6)
									{
										if(count==0)
											dist[2] = key_value + 0x30;
										else
											dist[3] = key_value + 0x30;
									}
									Disp_Str_eeprom(3,5,dist);
									break;
						}			

			}

			count = count + 1;
			if(count==2)
				count = 0;	

		}

    	}		
	}
    
	photo_taken = 0;
    photo_left = exp_photos;
	Clear_Scr();
	ShowMenu();
}


/**************************************************************   
*  函数说明：曝光设置函数                         *   
**************************************************************/  
void SetExposure(void)
{
    uint8 esc_flag = 0; 
    
    Disp_Char(0,5,expos_mode);
    UserChooseR = 1;
    Set_Cursor(1,0);
    while(!esc_flag)
    {
        if(time_10ms)  //10ms定时扫描键盘    
        { 
        time_10ms = 0; 
		*pRockValue=No_rock;
        rocker_type = Read_Rocker(pRockValue);
		if(rocker_type & keyPressed)
		{
			switch(*pRockValue)   
			{      
				case  Down:   
					  UserChooseR ++;   
					  if(UserChooseR == 4)   
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
                         Disp_Char(0,5,expos_mode);
					  } 
					  //Clear_Scr();					
					  break;		 
			}
			
            Set_Cursor(UserChooseR,0);
		}
        
		key_value= Read_keyboard();
		if(key_value != No_key)
		{
	        switch(key_value)
	        {
	        	case Esc:
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
                        switch(UserChooseR)
                        {
                            case 1:
                                    expos_mode = camera;
                                    break;
                            case 2:
                                    expos_mode = sensor;
                                    break;
                            case 3:
                                    expos_mode = fixed;
                                    break;                        
                        }
                        
	  				 	break;	
            }  
            
            Disp_Char(0,5,expos_mode);
            Set_Cursor(UserChooseR,0);
            
		}
        } 
               
    }
	Clear_Scr();
	ShowMenu();
    
}


/**************************************************************   
*  函数说明：光传感器设置函数                         *   
**************************************************************/  
void SetSensor(void)
{

    char *str_AV = (char *) malloc(5); 
    char *str_TV = (char *) malloc(8); 
    char *str_ISO = (char *) malloc(5);
    char *str_coef = (char *) malloc(5);
    char *str_HDR = (char *) malloc(2);
    char *str_ND = (char *) malloc(3);
    
	uint8 AV_NO = 1;
    uint8 esc_flag = 0;
    uint8 time_cnt = 0;
     
    float coef,AV;
    uint32 int_TV;
    uint16 ISO;
    uint8 HDR,ND;
    
    Set_Mode(OFF);
    
    ISO = 100 << e_ISO; 
    itoa(ISO,str_ISO);
    Disp_Str1(0,5,str_ISO);
    
    AV = e_AV;
    ftoa(AV,1,str_AV);
    Disp_Str1(0,1,str_AV);
    
    coef = e_coef;
    ftoa(coef,2,str_coef);
    Disp_Str1(2,5,str_coef); 
    
    HDR = e_HDR;
    itoa(HDR,str_HDR);
    Disp_Str1(3,3,str_HDR);
            
    ND = e_ND;
    itoa(ND,str_ND);
    Disp_Str1(3,6,str_ND);

	while(!esc_flag)
	{
        if(time_10ms)  //10ms定时扫描键盘    
        { 
        time_10ms = 0; 

		key_value= Read_keyboard();
		if(key_value != No_key)
		{
	        switch(key_value)
	        {
	        	case Esc:
						if(MenuPoint[UserChooseR].ParentMenus != NULL) 
						{ 
						 MenuPoint = MenuPoint[UserChooseR].ParentMenus; 
						 UserChooseR = 1; 
						 UserChooseC = 0;
						 //DisplayStart = 0; 
						} 
						esc_flag = 1;
						break;	
	        	case OK:
					    //Set_Mode();
	  				 	break; 
				case  1:
                		AV_NO++;
                      	if(AV_NO==8)
                        {
                        	AV_NO = 1;
                        }   
					  	break;
                case  3:
                		e_ISO++;
                        if(e_ISO == 6)
                        {e_ISO = 0;} 
                        ISO = 100 << e_ISO;
                        break;
                case  4:
                		coef -= 0.05;
                        break;
                case  6:
                		coef += 0.05;
                        break;
                case  7:
                		HDR++;
                        if(HDR == 7)
                        {
                        	HDR = 0;
                        }
                		break;	
                case  9:
                		ND++;
                        if(ND == 11)
                        {
                        	ND = 0;
                        }	
				default:
                		break;			
			} 
            
            switch(AV_NO)
            {
            	case 1:
                		AV = 2.8;
                        break;
            	case 2:
                		AV = 4.0;
                        break;
            	case 3:
                		AV = 5.6;
                        break;
            	case 4:
                		AV = 8.0;
                        break;
            	case 5:
                		AV = 11;
                        break;
            	case 6:
                		AV = 16;
                        break;
            	case 7:
                		AV = 22;
                        break;
                default:
                		break;                
            }			
		
        	e_AV = AV;
            ftoa(AV,1,str_AV);
            Disp_Str(0,1,"    ");  
    		Disp_Str1(0,1,str_AV);
            
            e_coef = coef;	 
    		ftoa(coef,2,str_coef); 
    		Disp_Str1(2,5,str_coef); 
            
            itoa(ISO,str_ISO);
            Disp_Str(0,5,"      ");
            Disp_Str1(0,5,str_ISO);
            
            e_HDR = HDR;
            itoa(HDR,str_HDR);
            Disp_Str1(3,3,str_HDR);
            
            e_ND = ND;
            itoa(ND,str_ND);
            Disp_Str(3,6,"  ");
            Disp_Str1(3,6,str_ND);
		}
        
        if(++time_cnt == 100)
        {
        	time_cnt = 0;
            //get_lux(); 
        	//Disp_Str1(0,4,lux_value);
            int_TV = Get_TV(); 
            ltoa(int_TV,str_TV); 
            Disp_Str(1,3,"      ");
            Disp_Str1(1,3,str_TV);    
        }		
		}
    }
	  
    free(str_AV);
    free(str_TV);
    free(str_ISO);
    free(str_coef);
    free(str_HDR);
    free(str_ND);
    
    Set_Mode(ON);
	Clear_Scr();
	ShowMenu();
}

/**************************************************************   
*  函数说明：电机参数设置函数                         *   
**************************************************************/  
void SetMotor(void)
{
	uint8 esc_flag = 0;
	uint8 count = 0;

    Disp_Str_eeprom(1,3,str_speed);
	Disp_Str_eeprom(2,3,divid);
    if(run_type == Horizon)
    {
    	Disp_Str(3,3,"水平");
    }
    else
    {
    	Disp_Str(3,3,"垂直");
    }

	UserChooseR = 1;
	UserChooseC = 4;
    Set_Cursor(UserChooseR,UserChooseC);
	while(!esc_flag)
	{
        if(time_10ms)  //10ms定时扫描键盘    
        { 
        time_10ms = 0; 
        *pRockValue=No_rock;
        rocker_type = Read_Rocker(pRockValue);
		if(rocker_type & keyPressed)
		{
			switch(*pRockValue)   
			{      
				case  Down:   
					  UserChooseR ++;   
					  if(UserChooseR == 4)   
					  {   
						UserChooseR = 1;   
					  }   
					  break;
				case  Left:	
					  UserChooseC --;   
					  if(UserChooseC == 2)   
					  {	
					    UserChooseC = 4;	 
					  }	
					  break;
			}			

            Set_Cursor(UserChooseR,UserChooseC);
		}


		key_value= Read_keyboard();
		if(key_value != No_key)
		{
	        switch(key_value)
	        {
	        	case Esc:
						if(MenuPoint[UserChooseR].ParentMenus != NULL) 
						{ 
						 MenuPoint = MenuPoint[UserChooseR].ParentMenus; 
						 UserChooseR = 0; 
						 UserChooseC = 0;
						 //DisplayStart = 0; 
						} 
						esc_flag = 1;
						break;	
	        	case OK:
					    //Set_Mode();
	  				 	break;
				default:
						switch(UserChooseR)
						{
							case 1:
									if(UserChooseC==3)
									{
										if(count==0)
											str_speed[0] = key_value + 0x30;
										else
											str_speed[1] = key_value + 0x30;
									}
									if(UserChooseC==4)
									{
										if(count==0)
											str_speed[2] = key_value + 0x30;
										else
											str_speed[3] = key_value + 0x30;
									}
									Disp_Str_eeprom(0,3,str_speed);
                                    int_speed = Str2Int(str_speed);
									break;
							case 2:
									if(UserChooseC==3)
									{
										if(count==0)
											divid[0] = key_value + 0x30;
										else
											divid[1] = key_value + 0x30;
									}
									if(UserChooseC==4)
									{
										if(count==0)
											divid[2] = key_value + 0x30;
										else
											divid[3] = key_value + 0x30;
									}
									Disp_Str_eeprom(2,3,divid);
                                    subdiv = Str2Int(divid);
									break;
							case 3:
                                    //待添加功能
									break;
						}			

			}

			count = count + 1;
			if(count==2)
				count = 0;	

		}
	
    	}		
	} 
      
	moto_set(int_speed,subdiv);
	Clear_Scr();
	ShowMenu();
}


/**************************************************************   
*  函数说明：自定义快门设置函数                         *   
**************************************************************/  
void SetShutter(void)
{
	uint8 esc_flag = 0;
	uint8 count = 0;

    Disp_Str_eeprom(0,5,TV);

	UserChooseR = 0;
	UserChooseC = 5;
    Set_Cursor(UserChooseR,UserChooseC);
	
	while(!esc_flag)
	{
        if(time_10ms)  //10ms定时扫描键盘    
        { 
        time_10ms = 0; 
		*pRockValue=No_rock;
        rocker_type = Read_Rocker(pRockValue);
		if(rocker_type & keyPressed)
		{
			switch(*pRockValue)   
			{      
				case  Down:   
					  UserChooseR ++;   
					  if(UserChooseR == 3)   
					  {   
						UserChooseR = 0;   
					  }   
					  break;
				case  Left:	
					  UserChooseC --;   
					  if(UserChooseC == 4)   
					  {	
					    UserChooseC = 6;	 
					  } 	
					  break;
			}			

            Set_Cursor(UserChooseR,UserChooseC);
		}


		key_value= Read_keyboard();
		if(key_value != No_key)
		{
	        switch(key_value)
	        {
	        	case Esc:
						if(MenuPoint[UserChooseR].ParentMenus != NULL) 
						{ 
						 MenuPoint = MenuPoint[UserChooseR].ParentMenus; 
						 UserChooseR = 1; 
						 UserChooseC = 0;
						 //DisplayStart = 0; 
						} 
						esc_flag = 1;
						break;	
	        	case OK:
					    Disp_Str(0,7," S");
	  				 	break;
				default:
						switch(UserChooseR)
						{
							case 0:
									if(UserChooseC==5)
									{
										if(count==0)
											TV[0] = key_value + 0x30;
										else
											TV[1] = key_value + 0x30;
									}
									if(UserChooseC==6)
									{
										if(count==0)
											TV[2] = key_value + 0x30;
										else
											TV[3] = key_value + 0x30;
									}
									Disp_Str_eeprom(0,5,TV);
									break;
							case 1:
                                    //
									break;
							case 2:
                                    //
									break;
						}			

			}

			count = count + 1;
			if(count==2)
				count = 0;	

		}
    
    	}    		
	}
	
    //expos_value = Str2Int(TV);
	Clear_Scr();
	ShowMenu();
}