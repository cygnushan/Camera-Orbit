#include  "BH1750.h"   

#define   SCL_HIGH()     DDRB.2 = 0;
#define   SCL_LOW()      DDRB.2 = 1;
#define   SDA_HIGH()     DDRB.1 = 0;
#define   SDA_LOW()      DDRB.1 = 1;
#define   SDA_IN         PINB.1
#define   I2C_ACK        0
#define   I2C_NO_ACK     1
#define   nms            5

uint8  BUF[8];                   //接收数据缓存区          
uint8  lux_value[6];            //显示变量
int    dis_data;                //变量
uint8  ACK;

//*********************************************************
void conversion(uint16 temp_data)  //  数据转换出 个，十，百，千，万
{  
    lux_value[0]=temp_data/10000+0x30 ;
    temp_data=temp_data%10000;   //取余运算
    lux_value[1]=temp_data/1000+0x30 ;
    temp_data=temp_data%1000;    //取余运算
    lux_value[2]=temp_data/100+0x30   ;
    temp_data=temp_data%100;     //取余运算
    lux_value[3]=temp_data/10+0x30    ;
    temp_data=temp_data%10;      //取余运算
    lux_value[4]=temp_data+0x30;     
}

/**************************************
起始信号
**************************************/
void BH1750_Start()
{
    SDA_HIGH();                    //拉高数据线
    //delay_us(nms);                 //延时
    SCL_HIGH();                    //拉高时钟线
    delay_us(nms);                 //延时
    SDA_LOW();                    //产生下降沿
    delay_us(nms);                 //延时
    SCL_LOW();                    //拉低时钟线
    delay_us(nms);
}

/**************************************
停止信号
**************************************/
void BH1750_Stop()
{
    SDA_LOW();                    //拉低数据线
    //delay_us(nms);                 //延时
    SCL_HIGH();                    //拉高时钟线
    delay_us(nms);                 //延时
    SDA_HIGH();                    //产生上升沿
    delay_us(nms);                 //延时
    SCL_LOW();                    //拉低时钟线
    delay_us(nms);
}

/**************************************
发送应答信号
入口参数:ack (0:I2C_ACK 1:I2C_NAK)
**************************************/
void BH1750_SendACK(uint8 ack)
{
    SCL_LOW();            //拉低时钟线
    delay_us(nms);       //延时
    if (ack == I2C_ACK) //写应答信号
    {
        SDA_LOW();
    }
    else
    {
        SDA_HIGH();
    }              
    SCL_HIGH();                   //拉高时钟线
    delay_us(nms);                 //延时
    SCL_LOW();                    //拉低时钟线
    delay_us(nms);                 //延时
}

/**************************************
接收应答信号
**************************************/
uint8 BH1750_RecvACK()
{
    SCL_HIGH();                    //拉高时钟线
    delay_us(nms);                 //延时 
    SDA_HIGH();                  //使SDA为输入状态
    ACK = SDA_IN;                   //读应答信号
    SCL_LOW();                    //拉低时钟线
    delay_us(nms);                 //延时

    return ACK;
}

/**************************************
向IIC总线发送一个字节数据
**************************************/
void BH1750_SendByte(uint8 dat)
{
    uint8 i;

    for (i=0; i<8; i++)         //8位计数器
    {
        //SCL_LOW();                    //拉低时钟线
        //delay_us(nms);                 //延时
        if(dat & 0x80)        //送数据口
        {
            SDA_HIGH();       
        }
        else
        {
            SDA_LOW();
        }
        delay_us(nms);             //延时
        SCL_HIGH();              //拉高时钟线
        //delay_us(nms);             //延时
        dat <<= 1;              //移出数据的最高位
        delay_us(nms);             //延时 
        SCL_LOW();                    //拉低时钟线
        delay_us(nms);                 //延时
    }
    BH1750_RecvACK();
}

/**************************************
从IIC总线接收一个字节数据
**************************************/
uint8 BH1750_RecvByte()
{
    uint8 i;
    uint8 dat = 0;
    
    SCL_LOW();
    delay_us(nms);
    SDA_HIGH();                  //使SDA为输入状态,准备读取数据,
    for (i=0; i<8; i++)         //8位计数器
    {
        SCL_LOW();
        delay_us(nms);
        SCL_HIGH(); 
        delay_us(nms);
        dat <<= 1;
        //delay_us(nms);             //延时 
        if(SDA_IN)               //读数据 
        {
            ++dat;
        }
        delay_us(nms);             //延时
    } 
    SCL_LOW();
    delay_us(nms);    
    return dat;
}

//*********************************

void Single_Write_BH1750(uint8 REG_Address)
{
    BH1750_Start();                  //起始信号
    BH1750_SendByte(SlaveAddress);   //发送设备地址+写信号
    BH1750_SendByte(REG_Address);    //内部寄存器地址，
  //  BH1750_SendByte(REG_data);       //内部寄存器数据，
    BH1750_Stop();                   //发送停止信号
}

//********单字节读取*****************************************
uint8 Single_Read_BH1750(uint8 REG_Address)
{  uint8 REG_data;
    BH1750_Start();                          //起始信号
    BH1750_SendByte(SlaveAddress);           //发送设备地址+写信号
    BH1750_SendByte(REG_Address);                   //发送存储单元地址，从0开始    
    BH1750_Start();                          //起始信号
    BH1750_SendByte(SlaveAddress+1);         //发送设备地址+读信号
    REG_data=BH1750_RecvByte();              //读出寄存器数据
    BH1750_SendACK(1);   
    BH1750_Stop();                           //停止信号
    return REG_data; 
}

//*********************************************************
//
//连续读出BH1750内部数据
//
//*********************************************************

void Multiple_Read_BH1750(void)
{   uint8 i;    
    BH1750_Start();                          //起始信号
    BH1750_SendByte(SlaveAddress+1);         //发送设备地址+读信号
    
     for (i=0; i<2; i++)                      //连续读取2个地址数据，存储中BUF
    {
        BUF[i] = BH1750_RecvByte();          //BUF[0]存储0x32地址中的数据
        if (i == 1)
        {

           BH1750_SendACK(1);                //最后一个数据需要回NOACK 
        }
        else
        {        
          BH1750_SendACK(0);                //回应ACK 
        } 
        delay_us(nms);
   }

    BH1750_Stop();                          //停止信号
    delay_ms(nms);
}


//初始化BH1750，根据需要请参考pdf进行修改****
void Init_BH1750()
{
   Single_Write_BH1750(0x01);
   //delay_ms(100);  
   //Single_Write_BH1750(0x10);   // H- resolution mode
   Single_Write_BH1750(0x42);    //设置MT寄存器高3位111
   Single_Write_BH1750(0x65);    //设置MT寄存器低5位11110,0.11 lux/count 

}
//*********************************************************
//主程序********
//*********************************************************
void get_lux(void)
{  
    float temp;
    //delay_ms(100);        //延时100ms    
    //Init_BH1750();       //初始化BH1750
 

    //Single_Write_BH1750(0x01);   // power on 
    //Single_Write_BH1750(0x47);    //设置MT寄存器高3位111
    //Single_Write_BH1750(0x7e);    //设置MT寄存器低5位11110,0.11 lux/count
    Single_Write_BH1750(0x11);   // H- resolution mode
    delay_ms(240);              //延时180ms
    Multiple_Read_BH1750();       //连续读出数据，存储在BUF中

    dis_data=BUF[0];
    dis_data=(dis_data<<8)+BUF[1];//合成数据，即光照数据
    
    temp=(float)dis_data/1.2;

    conversion(temp);         //计算数据和显示
    delay_ms(120);           
} 


//分别对应0-13EV光圈缩小1/3档，曝光值加大1.25倍，无线最快曝光100ms,有线最快曝光10ms

//lux = 2.5*2^EV  EV = log2(f^2/T) 可推出 T = 2.5f^2/lux * 1000ms
uint16 Get_TV()
{
    uint32 Tv_value;
    float temp;
    //delay_ms(100);        //延时100ms    
    //Init_BH1750();       //初始化BH1750
 

    //Single_Write_BH1750(0x01);   // power on 
    //Single_Write_BH1750(0x47);    //设置MT寄存器高3位111
    //Single_Write_BH1750(0x7e);    //设置MT寄存器低5位11110,0.11 lux/count
    Single_Write_BH1750(0x11);   // H- resolution mode
    delay_ms(240);              //延时180ms
    Multiple_Read_BH1750();       //连续读出数据，存储在BUF中

    dis_data=BUF[0];
    dis_data=(dis_data<<8)+BUF[1];//合成数据，即光照数据
    
    temp=(float)dis_data/1.2;
    
    Tv_value = (float)e_coef*2.5*e_AV*e_AV/temp*1000;
    Tv_value = Tv_value << e_ND;
    Tv_value = Tv_value >> e_ISO; 
    
    return Tv_value;

}

