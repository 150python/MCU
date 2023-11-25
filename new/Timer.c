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
	TMOD |= 0X00; // ���ö�ʱ��0����ģʽ0��16λ�Զ�����
	TL0 = 0X18; TH0 = 0XFC; // ���ö�ʱ�����ʱ��Ϊ1ms
	ET0 = 1; // ������ʱ��0�ж�����
	EA = 1; // �������ж�����
	TR0 = 1; // ������ʱ��0
	PT0 = 0; // �������ȼ�Ϊ�����ȼ�
}

void Timer0() interrupt 1    // 1ms�ж�
{	
	
	static unsigned int count100ms = 0, count500ms = 0;
	if(count100ms ++ == 100)
	{
		read_flag=1;//��ʱ��0.1sʱ������־��Ϊ��Ч��������0.1s��ȡһ��ʱ������
		count100ms=0;
	}
	if(count500ms ++ == 500)
	{
		flash_flag=~flash_flag;//��˸��־ÿ0.5s�ı�һ�Σ���ʱ�䡢���ڵ���ʱ����ǰ���������˸
		count500ms=0;
	}
	if(key_valid==0)  //������Ч��־��Чʱ�Ż������ⰴ�����˱�־�ڼ�⵽������Чʱ��1�������������0��
		key_value=key_scan();//ִ�а���ɨ��
	disp(8);//��ʾ����ÿ�ζ�ʱ�ж϶�Ҫִ��
}





