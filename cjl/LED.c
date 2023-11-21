#include <REGX52.H>
#include "Tools.h"

// led 模块是 P07 06 P05 P04 P03 P02 P01 P00
// P2 模块 P27 P26 P25 P24 P23 P22 P21 P20
void Init_Led()
{
	P2=P2&0X1F|0X80; // 使Y4C 使能
	P0=0XFF; // 初始化LED全灭
}

void clear_led(char dex)
{
	P0 = P0 | (0X01 << dex);
}

void light_led(int dex)
{
	P0 = P0 ^ (0X01 << dex);
}


