#include "Global_Variable.h"
#include <INTRINS.H>
#include <STC15F2K60S2.H>
#include "Button.h"
#include "Proteus.h"

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

void Timer0_Init()
{
	TMOD |= 0X00; // 设置定时器0工作模式0，16位自动重载
	TL0 = 0X18; TH0 = 0XFC; // 设置定时器溢出时间为1ms
	ET0 = 1; // 开启定时器0中断允许
	EA = 1; // 开启总中断允许
	TR0 = 1; // 开启定时器0
	PT0 = 0; // 设置优先级为低优先级
}

void Timer0() interrupt 1    // 1ms中断
{	
	
	static unsigned int count100ms = 0, count500ms = 0;
	if(count100ms ++ == 100)
	{
		read_flag=1;//计时到0.1s时，读标志置为有效。本例第0.1s读取一次时间日期
		count100ms=0;
	}
	if(count500ms ++ == 500)
	{
		flash_flag=~flash_flag;//闪烁标志每0.5s改变一次，在时间、日期调整时，当前最调整量闪烁
		count500ms=0;
	}
	if(key_valid==0)  //按键有效标志无效时才会继续检测按键（此标志在检测到按键有效时置1，按键处理后清0）
		key_value=key_scan();//执行按键扫描
	disp(8);//显示函数每次定时中断都要执行
}





