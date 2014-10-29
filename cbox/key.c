#include "key.h"


static uint8 Get_RockValue(void)         //获取PortD口值  
{   
    if(0 == RockX)  
    {  
        return X_value;
    }  
  
    if(0 == RockY )  
    {  
        return Y_value;       
    }  
  
    if(0 == RockK )  
    {  
        return K_value;      
    }  
         
    return No_rock;    //0x07  没有任何按键  
}  

char Read_Rocker(uint8 *pRockValue)
{
    static uint8  rock_state=0;        //未按，普通短按，长按,连发等状态  
    static uint8  keyTimeCounts=0;  //在计时状态的计数器  
    static uint8  LastRock = No_rock; //保存按键释放时
    
    uint8 rock_type = 0;
    uint8 rock_value = 0; 
    rock_value = No_rock & Get_RockValue();      
  
    switch(rock_state) //这里检测到的是先前的状态  
    {  
    	case  state_keyUp:   //如果先前是初始态，即无动作 
        { 
        	if( No_rock != rock_value )
            {
        		rock_state = state_keyDown;
            } 		
        }
        break;  
        
    	case  state_keyDown: //如果先前是被按着的  
        {  
        	if( No_rock != rock_value ) 
         	{
            	rock_state = state_keyTime;
                keyTimeCounts = 0;
                LastRock = rock_value;
         	}    
         	else
            {
            	rock_state = state_keyUp;
            }
        } 
        break;
          
    	case  state_keyTime:  //如果先前已经转换到计时态(值为3),如果真的是手动按键,必然进入本代码块,并且会多次进入  
    	{
            if( No_rock == rock_value )
            {
             	//Disp_Char('3');
                rock_state = state_keyUp;
             	rock_type = keyPressed;     //返回1,一次完整的普通按键 
          	}    
          	else
          	{
             	if(++keyTimeCounts>key_longtimes)
             	{
                	rock_state = state_keyLong; //进入长按状态 
                	keyTimeCounts = 0;//计数器清空,便于进入连发重新计数
                	rock_type = keyLong; 
            	}
            }
    	}
    	break;  
          
    	case  state_keyLong:  //在长按状态检测连发  ,每0.2秒发一次
		{
            if( No_rock == rock_value )
          	{
            	rock_state = state_keyUp;   // 列线全部为高电平返回状态 0
          	} 
          	else  //按键时间超过2秒时 
          	{
          		if(++keyTimeCounts>key_autotimes)
            	{
            		keyTimeCounts = 0;
            		rock_type = keyAuto;   
            	}
            	rock_type |= keyLong;  //0x02是肯定的,0x04|0x02是可能的
          	}
        }
        break;
        
   		default:
        break;         
  }
   
  	*pRockValue = LastRock;
  	return rock_type; 
}


char Read_keyboard() 
{   
  static char key_state = 0, key_code, key_line; 
  char key_return = No_key,i; 
  switch (key_state) 
  { 
    case 0: 
         key_line = 0b00000010; 
         for (i=1; i<=3; i++)          // 扫描键盘 
         {   
            PORTA = ~key_line;         // 输出行线电平 
            PORTA = ~key_line;         // 必须送 2 次！！！（注 1） 
            key_code = Key_mask & PINA;    // 读行电平 
            if (key_code == Key_mask) 
                key_line <<= 1;        // 没有按键，继续扫描 
            else 
            { 
                key_state++;          // 有按键，停止扫描 
                break;            // 转消抖确认状态 
            } 
         } 
         break; 
    case 1: 
          if (key_code == (Key_mask & PINA))    // 再次读行电平 
          { 
            switch (key_line | key_code)    // 与状态 0 的相同，确认按键 
            {                // 键盘编码，返回编码值  
              case  0b01111000: 
                    key_return = K1_1; 
                    break; 
              case  0b10111000: 
                    key_return = K2_1; 
                    break; 
              case  0b11011000: 
                    key_return = K3_1; 
                    break; 
              case  0b11101000: 
                    key_return = K4_1; 
                    break;  
              case  0b01110100: 
                    key_return = K1_2; 
                    break; 
              case  0b10110100: 
                    key_return = K2_2; 
                    break; 
              case  0b11010100: 
                    key_return = K3_2; 
                    break; 
              case  0b11100100: 
                    key_return = K4_2; 
                    break;
              case  0b01110010: 
                    key_return = K1_3; 
                    break; 
              case  0b10110010: 
                    key_return = K2_3; 
                    break; 
              case  0b11010010: 
                    key_return = K3_3; 
                    break; 
              case  0b11100010: 
                    key_return = K4_3; 
                    break; 

            } 
            key_state++;        // 转入等待按键释放状态 
          } 
          else 
              key_state--;        // 两次列电平不同返回状态 0，（消抖处理） 
          break;             
    case 2:              // 等待按键释放状态 
          PORTA = 0b11110000;      // 行线全部输出低电平 
          PORTA = 0b11110000;      // 重复送一次 
          if ( (Key_mask & PINA) == Key_mask) 
            key_state=0;        // 列线全部为高电平返回状态 0 
          break; 
  } 
  return key_return; 
} 


/*
uint8 Read_keyboard(uint8 *pKeyValue)               
{  
    static uint8  key_state=0,key_code,key_line;        //未按，普通短按，长按,连发等状态  
    static uint8  keyTimeCounts=0;  //在计时状态的计数器  
    static uint8  LastKey = No_key; //保存按键释放时
    uint8 key_return = 0,i;
    uint8 key_value; 
  
    switch(key_state)           //这里检测到的是先前的状态  
    {  
    case  state_keyUp:   //如果先前是初始态，即无动作  
          key_line = 0b00000010; 
          for (i=1; i<=3; i++)          // 扫描键盘 
          {   
            PORTA = ~key_line;         // 输出行线电平 
            PORTA = ~key_line;         // 必须送 2 次！！！（注 1） 
            key_code = Key_mask & PINA;    // 读行电平 
            if (key_code == Key_mask) 
                key_line <<= 1;        // 没有按键，继续扫描 
            else 
            { 
                key_state = state_keyDown;
                break;             
            } 
         } 
         break;
          
    case  state_keyDown: //如果先前是被按着的  
          {  
             if (key_code == (Key_mask & PINA))    // 再次读行电平 
             { 
                switch (key_line | key_code)    // 与状态 0 的相同，确认按键 
                {                // 键盘编码，返回编码值  
                case  0b01111000: 
                        key_return = K1_1; 
                        break; 
                case  0b10111000: 
                        key_return = K2_1; 
                        break; 
                case  0b11011000: 
                        key_return = K3_1; 
                        break; 
                case  0b11101000: 
                        key_return = K4_1; 
                        break;  
                case  0b01110100: 
                        key_return = K1_2; 
                        break; 
                case  0b10110100: 
                        key_return = K2_2; 
                        break; 
                case  0b11010100: 
                        key_return = K3_2; 
                        break; 
                case  0b11100100: 
                        key_return = K4_2; 
                        break;
                case  0b01110010: 
                        key_return = K1_3; 
                        break; 
                case  0b10110010: 
                        key_return = K2_3; 
                        break; 
                case  0b11010010: 
                        key_return = K3_3; 
                        break; 
                case  0b11100010: 
                        key_return = K4_3; 
                        break; 
                default:
                        break;
                } 
                key_state = state_keyTime;        // 转入等待按键释放状态
                keyTimeCounts = 0;
                LastKey = key_value; 
             } 
             else 
                 key_state = state_keyUp;        // 两次列电平不同返回状态 0，（消抖处理） 
             break;
          } 
          
    case  state_keyTime:  //如果先前已经转换到计时态(值为3),如果真的是手动按键,必然进入本代码块,并且会多次进入  
          PORTA = 0b00001111;      // 行线全部输出低电平 
          PORTA = 0b00001111;      // 重复送一次 
          if ( (Key_mask & PINA) == Key_mask)
          {
             key_state = state_keyUp;
             key_return = keyPressed;     //返回1,一次完整的普通按键 
             //程序进入这个语句块，说明已经有2次以上10ms的中断，等于已经消抖  
             //那么此时检测到按键被释放，说明是一次普通短按 
          }    
          else
          {
             if(++keyTimeCounts>key_longtimes)
             {
                key_state = state_keyLong; //进入长按状态 
                keyTimeCounts = 0;//计数器清空,便于进入连发重新计数
                key_return = keyLong; 
            }
             //代码中,在2秒内如果我们一直按着key的话,返回值只会是0,不会识别为短按或长按的
          }
          break;  
          
    case  state_keyLong:  //在长按状态检测连发  ,每0.2秒发一次
          PORTA = 0b11110000;      // 行线全部输出低电平 
          PORTA = 0b11110000;      // 重复送一次 
          if ( (Key_mask & PINA) == Key_mask)
          {
            key_state = state_keyUp;   // 列线全部为高电平返回状态 0
          } 
          else  //按键时间超过2秒时 
          {
            if(++keyTimeCounts>key_autotimes)
                {
                    keyTimeCounts = 0;
                    key_return = keyAuto;   
                }
                key_return |= keyLong;  //0x02是肯定的,0x04|0x02是可能的
          }
          break;
    default:
          break;         
  }
   
  *pKeyValue = LastKey;
  return key_return;   
}  

*/