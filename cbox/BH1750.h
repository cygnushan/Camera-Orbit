#ifndef _H_BH1750
#define _H_BH1750

#include "main.h"


#define SlaveAddress   0x46 //定义器件在IIC总线中的从地址,根据ALT  ADDRESS地址引脚不同修改
                              //ALT  ADDRESS引脚接地时地址为0x46，接电源时地址为0xB8

                             //连续的读取内部寄存器数据

void BH1750_Start();                    //起始信号
void BH1750_Stop();                     //停止信号
void BH1750_SendACK(uint8 ack);           //应答ACK
uint8 BH1750_RecvACK();                  //读ack
void BH1750_SendByte(uint8 dat);         //IIC单个字节写
uint8 BH1750_RecvByte();                 //IIC单个字节读
void Init_BH1750(void);

void Single_Write_BH1750(uint8 REG_Address);               //单个写入数据
uint8 Single_Read_BH1750(uint8 REG_Address);               //单个读取内部寄存器数据
void Multiple_Read_BH1750(void);
void conversion(uint16 temp_data); 

void get_lux(void);
uint16 Get_TV();
#endif