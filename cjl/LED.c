#include <REGX52.H>
#include "Tools.h"
#define Y0C P2=P2&0X1F      // ��������ǰ��λ����
#define Y4C P2=P2&0X1F|0X80 // ��������ǰ��λ��Ϊ100  Y4ʹ��
#define Y5C P2=P2&0X1F|0XA0 // ��������ǰ��λ��Ϊ101  Y5ʹ��
#define Y6C P2=P2&0X1F|0XC0 // ��������ǰ��λ��Ϊ110  Y6ʹ��
#define Y7C P2=P2&0X1F|0XE0 // ��������ǰ��λ��Ϊ111  Y7ʹ��


// led ģ���� P07 06 P05 P04 P03 P02 P01 P00
// P2 ģ�� P27 P26 P25 P24 P23 P22 P21 P20
void Init_Led()
{
	//P2=P2&0X1F|0X80; // ʹY4C ʹ��
	Y4C;// ʹY4 ʹ��
	P0=0XFF; // ��ʼ��LEDȫ��
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


