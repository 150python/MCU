#include <REGX52.H>
#include "Tools.h"
#define Y0C P2=P2&0X1F      // 将锁存器前三位清零
#define Y4C P2=P2&0X1F|0X80 // 将锁存器前三位置为100  Y4使能
#define Y5C P2=P2&0X1F|0XA0 // 将锁存器前三位置为101  Y5使能
#define Y6C P2=P2&0X1F|0XC0 // 将锁存器前三位置为110  Y6使能
#define Y7C P2=P2&0X1F|0XE0 // 将锁存器前三位置为111  Y7使能


// led 模块是 P07 06 P05 P04 P03 P02 P01 P00
// P2 模块 P27 P26 P25 P24 P23 P22 P21 P20
void Init_Led()
{
	//P2=P2&0X1F|0X80; // 使Y4C 使能
	Y4C;// 使Y4 使能
	P0=0XFF; // 初始化LED全灭
}

void clear_led(char dex)
{
	P0 = P0 | (0X01 << dex);
}

void close_led()
{
	Y0C;
	P0=0XFF;
	Y4C;
	Y0C;
}

void light_led(int dex)
{
	P0 = P0 ^ (0X01 << dex);
}


