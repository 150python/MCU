#include "Tools.h"
// 读和写切换时要记得复位一次

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
	ack = DQ;// 0为有一线设备
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
			received_byte |= 0X80; // DQ 从低位到高位输出
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
	Write_DS18B20_byte(0XCC)// 跳过ROM匹配指令
	Write_DS18B20_byte(0X44);// 启动温度转化指令
	Delayus(750);// 等待温度转化完成
	init_DS18B20()
	Write_DS18B20_byte(0XCC);
	Write_DS18B20_byte(0XBE);// 写读指令
	teml = Read_DS18B20_byte();
	temh = Read_DS18B20_byte();
	temprature = (temh<<8+teml)*0.0625;
	return temprature;
	
}
