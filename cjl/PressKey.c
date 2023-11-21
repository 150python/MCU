#include <REGX52.H>
#include "Tools.h"
// 按键会有（5-10）ms 抖动
// 释放建也有(5-10)ms 抖动
// 只有中间的（20-200）ms 稳定

void Depend_Key_Read() // 独立按键：P30 P31 P32 P33 
{
	if(P3_0 == 0)
	{
		Delayms(20);
		while(P3_0==0);
		Delayms(20);
		P0_0 = !P0_0;	
	}
}




