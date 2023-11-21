#include <REGX52.H>
// 数码管共阳极                 P27 P26 P25
#define Y0C P2=P2&0X1F      // 将锁存器前三位清零
#define Y4C P2=P2&0X1F|0X80 // 将锁存器前三位置为100  Y4使能
#define Y5C P2=P2&0X1F|0XA0 // 将锁存器前三位置为101  Y5使能
#define Y6C P2=P2&0X1F|0XC0 // 将锁存器前三位置为110  Y6使能
#define Y7C P2=P2&0X1F|0XE0 // 将锁存器前三位置为111  Y7使能

unsigned char code duan_code[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff,0xc8}; //共阳
unsigned char disp_buf[8];

void disp_buf_change(unsigned char one,two,three,four,five,six,seven,eight)
{
	disp_buf[0]=duan_code[one];
	disp_buf[1]=duan_code[two];
	disp_buf[2]=duan_code[three];
	disp_buf[3]=duan_code[four];
	disp_buf[4]=duan_code[five];
	disp_buf[5]=duan_code[six];
	disp_buf[6]=duan_code[seven];
	disp_buf[7]=duan_code[eight];
}

void disp(unsigned char i)
{
	static unsigned char disp_com;
	Y0C;// 初始化锁存器
	P0 = 0X00;// 位选置为0
	Y6C;// 打开位选锁存器  消除重影
	Y0C;// 关闭位选锁存器
	if(i==disp_com)
	{
		P0=disp_buf[disp_com]&0x7f;
	}
	else
	{
		P0=disp_buf[disp_com];
	}
	Y7C; // 打开段选锁存器 将上面的P0输入进去
	Y0C; // 关闭段选
	P0=1<<disp_com;
	disp_com=(disp_com+1)%8;
	Y6C; //打开位选，将上面的P0输入进去
	Y0C; // 关闭段选
}

