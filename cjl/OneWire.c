#include "Tools.h"
// ����д�л�ʱҪ�ǵø�λһ��

void reset_onewire_bus()
{
	DQ = 1;
	Delayus(5);
	DQ = 0;
	Delayus(500);
	DQ = 1;
}

bit onewire_ack()
{
	bit ack = 0;
	Delayus(69);
	ack = DQ;// 0Ϊ��һ���豸
	Delayus(500);
	return ack;
}

void Write_DS18B20_byte(unsigned char dat)
{
	unsigned char i;
	for(i = 0; i < 8; i ++)
	{
		DQ = 0;
		Delayus(10);
		DQ = dat&0X01;
		Delayus(120);
		dat >>= 1;
		DQ = 1;
	}
}



unsigned char Read_DS18B20_byte()
{
	unsigned char i, received_byte;
	for(i = 0; i < 8; i ++)
	{
		DQ = 0;
		Delayus(5);
		DQ = 1;
		Delayus(5);
		received_byte >>= 1;
		if(DQ == 1)
		{
			received_byte |= 0X80; // DQ �ӵ�λ����λ���
		}
		Delayus(120);
		DQ = 1;
		Delayus(5);
	}
	return received_byte;
}

void init_DS18B20()
{
	reset_onewire_bus();
	bit ok = onewire_ack();
}

float read_temprature()
{
	unsigned char temh, teml;
	int temp;
	float temprature;
	init_DS18B20()
	Write_DS18B20_byte(0XCC)// ����ROMƥ��ָ��
	Write_DS18B20_byte(0X44);// �����¶�ת��ָ��
	Delayus(750);// �ȴ��¶�ת�����
	init_DS18B20()
	Write_DS18B20_byte(0XCC);
	Write_DS18B20_byte(0XBE);// д��ָ��
	teml = Read_DS18B20_byte();
	temh = Read_DS18B20_byte();
	temprature = (temh<<8+teml)*0.0625;
	return temprature;
	
}
