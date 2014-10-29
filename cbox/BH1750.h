#ifndef _H_BH1750
#define _H_BH1750

#include "main.h"


#define SlaveAddress   0x46 //����������IIC�����еĴӵ�ַ,����ALT  ADDRESS��ַ���Ų�ͬ�޸�
                              //ALT  ADDRESS���Žӵ�ʱ��ַΪ0x46���ӵ�Դʱ��ַΪ0xB8

                             //�����Ķ�ȡ�ڲ��Ĵ�������

void BH1750_Start();                    //��ʼ�ź�
void BH1750_Stop();                     //ֹͣ�ź�
void BH1750_SendACK(uint8 ack);           //Ӧ��ACK
uint8 BH1750_RecvACK();                  //��ack
void BH1750_SendByte(uint8 dat);         //IIC�����ֽ�д
uint8 BH1750_RecvByte();                 //IIC�����ֽڶ�
void Init_BH1750(void);

void Single_Write_BH1750(uint8 REG_Address);               //����д������
uint8 Single_Read_BH1750(uint8 REG_Address);               //������ȡ�ڲ��Ĵ�������
void Multiple_Read_BH1750(void);
void conversion(uint16 temp_data); 

void get_lux(void);
uint16 Get_TV();
#endif