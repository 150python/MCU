#include <INTRINS.H>
#include <STC15F2K60S2.H>
#include "LED.h"
#include "Proteus.h"

bit flag = 0;
unsigned int timer;// 毫秒为单位

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
	TMOD |= 0X00; // 设置定时器0工作模式0，16位自动重载
	TL0 = 0X18; TH0 = 0XFC; // 设置定时器溢出时间为1ms
	ET0 = 1; // 开启定时器0中断允许
	EA = 1; // 开启总中断允许
	TR0 = 1; // 开启定时器0
	PT0 = 0; // 设置优先级为低优先级
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
	disp(5);// 小数点位置0，1，2，3，4，5，6，7  8为无小数点
}



