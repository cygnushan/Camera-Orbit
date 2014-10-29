#include  "BH1750.h"   

#define   SCL_HIGH()     DDRB.2 = 0;
#define   SCL_LOW()      DDRB.2 = 1;
#define   SDA_HIGH()     DDRB.1 = 0;
#define   SDA_LOW()      DDRB.1 = 1;
#define   SDA_IN         PINB.1
#define   I2C_ACK        0
#define   I2C_NO_ACK     1
#define   nms            5

uint8  BUF[8];                   //�������ݻ�����          
uint8  lux_value[6];            //��ʾ����
int    dis_data;                //����
uint8  ACK;

//*********************************************************
void conversion(uint16 temp_data)  //  ����ת���� ����ʮ���٣�ǧ����
{  
    lux_value[0]=temp_data/10000+0x30 ;
    temp_data=temp_data%10000;   //ȡ������
    lux_value[1]=temp_data/1000+0x30 ;
    temp_data=temp_data%1000;    //ȡ������
    lux_value[2]=temp_data/100+0x30   ;
    temp_data=temp_data%100;     //ȡ������
    lux_value[3]=temp_data/10+0x30    ;
    temp_data=temp_data%10;      //ȡ������
    lux_value[4]=temp_data+0x30;     
}

/**************************************
��ʼ�ź�
**************************************/
void BH1750_Start()
{
    SDA_HIGH();                    //����������
    //delay_us(nms);                 //��ʱ
    SCL_HIGH();                    //����ʱ����
    delay_us(nms);                 //��ʱ
    SDA_LOW();                    //�����½���
    delay_us(nms);                 //��ʱ
    SCL_LOW();                    //����ʱ����
    delay_us(nms);
}

/**************************************
ֹͣ�ź�
**************************************/
void BH1750_Stop()
{
    SDA_LOW();                    //����������
    //delay_us(nms);                 //��ʱ
    SCL_HIGH();                    //����ʱ����
    delay_us(nms);                 //��ʱ
    SDA_HIGH();                    //����������
    delay_us(nms);                 //��ʱ
    SCL_LOW();                    //����ʱ����
    delay_us(nms);
}

/**************************************
����Ӧ���ź�
��ڲ���:ack (0:I2C_ACK 1:I2C_NAK)
**************************************/
void BH1750_SendACK(uint8 ack)
{
    SCL_LOW();            //����ʱ����
    delay_us(nms);       //��ʱ
    if (ack == I2C_ACK) //дӦ���ź�
    {
        SDA_LOW();
    }
    else
    {
        SDA_HIGH();
    }              
    SCL_HIGH();                   //����ʱ����
    delay_us(nms);                 //��ʱ
    SCL_LOW();                    //����ʱ����
    delay_us(nms);                 //��ʱ
}

/**************************************
����Ӧ���ź�
**************************************/
uint8 BH1750_RecvACK()
{
    SCL_HIGH();                    //����ʱ����
    delay_us(nms);                 //��ʱ 
    SDA_HIGH();                  //ʹSDAΪ����״̬
    ACK = SDA_IN;                   //��Ӧ���ź�
    SCL_LOW();                    //����ʱ����
    delay_us(nms);                 //��ʱ

    return ACK;
}

/**************************************
��IIC���߷���һ���ֽ�����
**************************************/
void BH1750_SendByte(uint8 dat)
{
    uint8 i;

    for (i=0; i<8; i++)         //8λ������
    {
        //SCL_LOW();                    //����ʱ����
        //delay_us(nms);                 //��ʱ
        if(dat & 0x80)        //�����ݿ�
        {
            SDA_HIGH();       
        }
        else
        {
            SDA_LOW();
        }
        delay_us(nms);             //��ʱ
        SCL_HIGH();              //����ʱ����
        //delay_us(nms);             //��ʱ
        dat <<= 1;              //�Ƴ����ݵ����λ
        delay_us(nms);             //��ʱ 
        SCL_LOW();                    //����ʱ����
        delay_us(nms);                 //��ʱ
    }
    BH1750_RecvACK();
}

/**************************************
��IIC���߽���һ���ֽ�����
**************************************/
uint8 BH1750_RecvByte()
{
    uint8 i;
    uint8 dat = 0;
    
    SCL_LOW();
    delay_us(nms);
    SDA_HIGH();                  //ʹSDAΪ����״̬,׼����ȡ����,
    for (i=0; i<8; i++)         //8λ������
    {
        SCL_LOW();
        delay_us(nms);
        SCL_HIGH(); 
        delay_us(nms);
        dat <<= 1;
        //delay_us(nms);             //��ʱ 
        if(SDA_IN)               //������ 
        {
            ++dat;
        }
        delay_us(nms);             //��ʱ
    } 
    SCL_LOW();
    delay_us(nms);    
    return dat;
}

//*********************************

void Single_Write_BH1750(uint8 REG_Address)
{
    BH1750_Start();                  //��ʼ�ź�
    BH1750_SendByte(SlaveAddress);   //�����豸��ַ+д�ź�
    BH1750_SendByte(REG_Address);    //�ڲ��Ĵ�����ַ��
  //  BH1750_SendByte(REG_data);       //�ڲ��Ĵ������ݣ�
    BH1750_Stop();                   //����ֹͣ�ź�
}

//********���ֽڶ�ȡ*****************************************
uint8 Single_Read_BH1750(uint8 REG_Address)
{  uint8 REG_data;
    BH1750_Start();                          //��ʼ�ź�
    BH1750_SendByte(SlaveAddress);           //�����豸��ַ+д�ź�
    BH1750_SendByte(REG_Address);                   //���ʹ洢��Ԫ��ַ����0��ʼ    
    BH1750_Start();                          //��ʼ�ź�
    BH1750_SendByte(SlaveAddress+1);         //�����豸��ַ+���ź�
    REG_data=BH1750_RecvByte();              //�����Ĵ�������
    BH1750_SendACK(1);   
    BH1750_Stop();                           //ֹͣ�ź�
    return REG_data; 
}

//*********************************************************
//
//��������BH1750�ڲ�����
//
//*********************************************************

void Multiple_Read_BH1750(void)
{   uint8 i;    
    BH1750_Start();                          //��ʼ�ź�
    BH1750_SendByte(SlaveAddress+1);         //�����豸��ַ+���ź�
    
     for (i=0; i<2; i++)                      //������ȡ2����ַ���ݣ��洢��BUF
    {
        BUF[i] = BH1750_RecvByte();          //BUF[0]�洢0x32��ַ�е�����
        if (i == 1)
        {

           BH1750_SendACK(1);                //���һ��������Ҫ��NOACK 
        }
        else
        {        
          BH1750_SendACK(0);                //��ӦACK 
        } 
        delay_us(nms);
   }

    BH1750_Stop();                          //ֹͣ�ź�
    delay_ms(nms);
}


//��ʼ��BH1750��������Ҫ��ο�pdf�����޸�****
void Init_BH1750()
{
   Single_Write_BH1750(0x01);
   //delay_ms(100);  
   //Single_Write_BH1750(0x10);   // H- resolution mode
   Single_Write_BH1750(0x42);    //����MT�Ĵ�����3λ111
   Single_Write_BH1750(0x65);    //����MT�Ĵ�����5λ11110,0.11 lux/count 

}
//*********************************************************
//������********
//*********************************************************
void get_lux(void)
{  
    float temp;
    //delay_ms(100);        //��ʱ100ms    
    //Init_BH1750();       //��ʼ��BH1750
 

    //Single_Write_BH1750(0x01);   // power on 
    //Single_Write_BH1750(0x47);    //����MT�Ĵ�����3λ111
    //Single_Write_BH1750(0x7e);    //����MT�Ĵ�����5λ11110,0.11 lux/count
    Single_Write_BH1750(0x11);   // H- resolution mode
    delay_ms(240);              //��ʱ180ms
    Multiple_Read_BH1750();       //�����������ݣ��洢��BUF��

    dis_data=BUF[0];
    dis_data=(dis_data<<8)+BUF[1];//�ϳ����ݣ�����������
    
    temp=(float)dis_data/1.2;

    conversion(temp);         //�������ݺ���ʾ
    delay_ms(120);           
} 


//�ֱ��Ӧ0-13EV��Ȧ��С1/3�����ع�ֵ�Ӵ�1.25������������ع�100ms,��������ع�10ms

//lux = 2.5*2^EV  EV = log2(f^2/T) ���Ƴ� T = 2.5f^2/lux * 1000ms
uint16 Get_TV()
{
    uint32 Tv_value;
    float temp;
    //delay_ms(100);        //��ʱ100ms    
    //Init_BH1750();       //��ʼ��BH1750
 

    //Single_Write_BH1750(0x01);   // power on 
    //Single_Write_BH1750(0x47);    //����MT�Ĵ�����3λ111
    //Single_Write_BH1750(0x7e);    //����MT�Ĵ�����5λ11110,0.11 lux/count
    Single_Write_BH1750(0x11);   // H- resolution mode
    delay_ms(240);              //��ʱ180ms
    Multiple_Read_BH1750();       //�����������ݣ��洢��BUF��

    dis_data=BUF[0];
    dis_data=(dis_data<<8)+BUF[1];//�ϳ����ݣ�����������
    
    temp=(float)dis_data/1.2;
    
    Tv_value = (float)e_coef*2.5*e_AV*e_AV/temp*1000;
    Tv_value = Tv_value << e_ND;
    Tv_value = Tv_value >> e_ISO; 
    
    return Tv_value;

}

