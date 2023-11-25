#include "Global_Variable.h"

#include "REG52.h" 
#include "INTRINS.h" //_nop_()�ڴ�ͷ�ļ��� #define DQ P14
#include "Timer.h"

sbit DQ = P1^4;
// ����д�л�ʱҪ�ǵø�λһ��

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
	ack = DQ;// 0Ϊ��һ���豸
	Delayus(500);
	return ack;
}

void Write_DS18B20_byte(unsigned char dat)
{
	unsigned char i;
	for(i = 0; i < 8; i ++)
	{
		DQ = 0;
		Delayus(5);
		DQ = dat&0X01;
		Delayus(60);
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
			received_byte |= 0X80; // DQ �ӵ�λ����λ���
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
	onewire_ack();
}

float read_temperature()
{
	unsigned char temh, teml;
	float temperature;
	init_DS18B20();
	Write_DS18B20_byte(0XCC);// ����ROMƥ��ָ��
	Write_DS18B20_byte(0X44);// �����¶�ת��ָ��
	Delayms(750);// �ȴ��¶�ת�����
	init_DS18B20();
	Write_DS18B20_byte(0XCC);
	Write_DS18B20_byte(0XBE);// д��ָ��
	teml = Read_DS18B20_byte();
	temh = Read_DS18B20_byte();
	temperature=(int)(temh<<8|teml) * 0.0625;
	return temperature;
	
}


/*  ��ʾ�¶�

void main()
{
	float temp;
	unsigned int temp_disp;
	Timer0_Init(1000);
	while(1){
		
		if(flag)
		{
			flag = 0;
			temp = read_temperature();
			temp_disp = (int)(temp*100);
			disp_buf_change(10,10,10,10,temp_disp>=1000?temp_disp/1000:10,temp_disp>=100?temp_disp%1000/100:10,
			temp_disp%100/10,temp_disp%10);
			
		}
		
	}
}

*/
