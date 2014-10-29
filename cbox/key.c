#include "key.h"


static uint8 Get_RockValue(void)         //��ȡPortD��ֵ  
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
         
    return No_rock;    //0x07  û���κΰ���  
}  

char Read_Rocker(uint8 *pRockValue)
{
    static uint8  rock_state=0;        //δ������ͨ�̰�������,������״̬  
    static uint8  keyTimeCounts=0;  //�ڼ�ʱ״̬�ļ�����  
    static uint8  LastRock = No_rock; //���水���ͷ�ʱ
    
    uint8 rock_type = 0;
    uint8 rock_value = 0; 
    rock_value = No_rock & Get_RockValue();      
  
    switch(rock_state) //�����⵽������ǰ��״̬  
    {  
    	case  state_keyUp:   //�����ǰ�ǳ�ʼ̬�����޶��� 
        { 
        	if( No_rock != rock_value )
            {
        		rock_state = state_keyDown;
            } 		
        }
        break;  
        
    	case  state_keyDown: //�����ǰ�Ǳ����ŵ�  
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
          
    	case  state_keyTime:  //�����ǰ�Ѿ�ת������ʱ̬(ֵΪ3),���������ֶ�����,��Ȼ���뱾�����,���һ��ν���  
    	{
            if( No_rock == rock_value )
            {
             	//Disp_Char('3');
                rock_state = state_keyUp;
             	rock_type = keyPressed;     //����1,һ����������ͨ���� 
          	}    
          	else
          	{
             	if(++keyTimeCounts>key_longtimes)
             	{
                	rock_state = state_keyLong; //���볤��״̬ 
                	keyTimeCounts = 0;//���������,���ڽ����������¼���
                	rock_type = keyLong; 
            	}
            }
    	}
    	break;  
          
    	case  state_keyLong:  //�ڳ���״̬�������  ,ÿ0.2�뷢һ��
		{
            if( No_rock == rock_value )
          	{
            	rock_state = state_keyUp;   // ����ȫ��Ϊ�ߵ�ƽ����״̬ 0
          	} 
          	else  //����ʱ�䳬��2��ʱ 
          	{
          		if(++keyTimeCounts>key_autotimes)
            	{
            		keyTimeCounts = 0;
            		rock_type = keyAuto;   
            	}
            	rock_type |= keyLong;  //0x02�ǿ϶���,0x04|0x02�ǿ��ܵ�
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
         for (i=1; i<=3; i++)          // ɨ����� 
         {   
            PORTA = ~key_line;         // ������ߵ�ƽ 
            PORTA = ~key_line;         // ������ 2 �Σ�������ע 1�� 
            key_code = Key_mask & PINA;    // ���е�ƽ 
            if (key_code == Key_mask) 
                key_line <<= 1;        // û�а���������ɨ�� 
            else 
            { 
                key_state++;          // �а�����ֹͣɨ�� 
                break;            // ת����ȷ��״̬ 
            } 
         } 
         break; 
    case 1: 
          if (key_code == (Key_mask & PINA))    // �ٴζ��е�ƽ 
          { 
            switch (key_line | key_code)    // ��״̬ 0 ����ͬ��ȷ�ϰ��� 
            {                // ���̱��룬���ر���ֵ  
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
            key_state++;        // ת��ȴ������ͷ�״̬ 
          } 
          else 
              key_state--;        // �����е�ƽ��ͬ����״̬ 0������������ 
          break;             
    case 2:              // �ȴ������ͷ�״̬ 
          PORTA = 0b11110000;      // ����ȫ������͵�ƽ 
          PORTA = 0b11110000;      // �ظ���һ�� 
          if ( (Key_mask & PINA) == Key_mask) 
            key_state=0;        // ����ȫ��Ϊ�ߵ�ƽ����״̬ 0 
          break; 
  } 
  return key_return; 
} 


/*
uint8 Read_keyboard(uint8 *pKeyValue)               
{  
    static uint8  key_state=0,key_code,key_line;        //δ������ͨ�̰�������,������״̬  
    static uint8  keyTimeCounts=0;  //�ڼ�ʱ״̬�ļ�����  
    static uint8  LastKey = No_key; //���水���ͷ�ʱ
    uint8 key_return = 0,i;
    uint8 key_value; 
  
    switch(key_state)           //�����⵽������ǰ��״̬  
    {  
    case  state_keyUp:   //�����ǰ�ǳ�ʼ̬�����޶���  
          key_line = 0b00000010; 
          for (i=1; i<=3; i++)          // ɨ����� 
          {   
            PORTA = ~key_line;         // ������ߵ�ƽ 
            PORTA = ~key_line;         // ������ 2 �Σ�������ע 1�� 
            key_code = Key_mask & PINA;    // ���е�ƽ 
            if (key_code == Key_mask) 
                key_line <<= 1;        // û�а���������ɨ�� 
            else 
            { 
                key_state = state_keyDown;
                break;             
            } 
         } 
         break;
          
    case  state_keyDown: //�����ǰ�Ǳ����ŵ�  
          {  
             if (key_code == (Key_mask & PINA))    // �ٴζ��е�ƽ 
             { 
                switch (key_line | key_code)    // ��״̬ 0 ����ͬ��ȷ�ϰ��� 
                {                // ���̱��룬���ر���ֵ  
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
                key_state = state_keyTime;        // ת��ȴ������ͷ�״̬
                keyTimeCounts = 0;
                LastKey = key_value; 
             } 
             else 
                 key_state = state_keyUp;        // �����е�ƽ��ͬ����״̬ 0������������ 
             break;
          } 
          
    case  state_keyTime:  //�����ǰ�Ѿ�ת������ʱ̬(ֵΪ3),���������ֶ�����,��Ȼ���뱾�����,���һ��ν���  
          PORTA = 0b00001111;      // ����ȫ������͵�ƽ 
          PORTA = 0b00001111;      // �ظ���һ�� 
          if ( (Key_mask & PINA) == Key_mask)
          {
             key_state = state_keyUp;
             key_return = keyPressed;     //����1,һ����������ͨ���� 
             //�������������飬˵���Ѿ���2������10ms���жϣ������Ѿ�����  
             //��ô��ʱ��⵽�������ͷţ�˵����һ����ͨ�̰� 
          }    
          else
          {
             if(++keyTimeCounts>key_longtimes)
             {
                key_state = state_keyLong; //���볤��״̬ 
                keyTimeCounts = 0;//���������,���ڽ����������¼���
                key_return = keyLong; 
            }
             //������,��2�����������һֱ����key�Ļ�,����ֵֻ����0,����ʶ��Ϊ�̰��򳤰���
          }
          break;  
          
    case  state_keyLong:  //�ڳ���״̬�������  ,ÿ0.2�뷢һ��
          PORTA = 0b11110000;      // ����ȫ������͵�ƽ 
          PORTA = 0b11110000;      // �ظ���һ�� 
          if ( (Key_mask & PINA) == Key_mask)
          {
            key_state = state_keyUp;   // ����ȫ��Ϊ�ߵ�ƽ����״̬ 0
          } 
          else  //����ʱ�䳬��2��ʱ 
          {
            if(++keyTimeCounts>key_autotimes)
                {
                    keyTimeCounts = 0;
                    key_return = keyAuto;   
                }
                key_return |= keyLong;  //0x02�ǿ϶���,0x04|0x02�ǿ��ܵ�
          }
          break;
    default:
          break;         
  }
   
  *pKeyValue = LastKey;
  return key_return;   
}  

*/