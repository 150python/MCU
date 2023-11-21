#include <INTRINS.H>
#include <STC15F2K60S2.H>
#include "LED.h"
#include "Proteus.h"

bit flag = 0;
unsigned int timer;// ����Ϊ��λ

void Delayus(unsigned int xus)	//@12.000MHz
{
	while(xus --)
	{
		_nop_();
		_nop_();
		_nop_();
		_nop_();
	}
}

void Delayms(unsigned int xms)	//@12.000MHz
{
	unsigned char data i, j;
	while(xms --)
	{
		i = 12;
		j = 169;
		do
		{
			while (--j);
		} while (--i);
	}
}

void Timer0_Init(unsigned int timer_x)
{
	timer = timer_x;
	TMOD |= 0X00; // ���ö�ʱ��0����ģʽ0��16λ�Զ�����
	TL0 = 0X18; TH0 = 0XFC; // ���ö�ʱ�����ʱ��Ϊ1ms
	ET0 = 1; // ������ʱ��0�ж�����
	EA = 1; // �������ж�����
	TR0 = 1; // ������ʱ��0
	PT0 = 0; // �������ȼ�Ϊ�����ȼ�
}

void Timer0() interrupt 1
{	
	
	static unsigned int Timer0_Count=0;
	Timer0_Count ++;
	if(Timer0_Count == timer)
	{
		Timer0_Count = 0;
		flag = 1;
	}
	disp(5);// С����λ��0��1��2��3��4��5��6��7  8Ϊ��С����
}



