#include <STC15F2K60S2.H>
#include "Global_Variable.h"
#include "Proteus.h"
#include "Timer.h"
#include "DS1302.h"
#include "Button.h"
#include "Led.h"


unsigned char interface=0; //��ʾ�����л����Ʊ�����0:��ʾʱ�䣬1����ʾ���ڣ�2��Сʱ������3�����ӵ�����4���������5���������6���µ�����7���յ��� //�ɰ���S7˳���л�
unsigned char key_value=0xff; //��ֵ
bit key_valid=0;
bit read_flag,flash_flag;

void main(){
	
	unsigned char second,minite,hour,date,month,year;
	cls_led(); cls_nbuzz();
	Timer0_Init(); // ��ʼ����ʱ��0
	Write_Ds1302(0x8e,0x00);// ȥд����
	Write_Ds1302(0x80,0x00);// ��
	Write_Ds1302(0x82,0x09);// ��
	Write_Ds1302(0x84,0x08);// ʱ
	Write_Ds1302(0x86,0x01);// ��
	Write_Ds1302(0x88,0x01);// ��
	Write_Ds1302(0x8c,0x22);// ��
	//DS1302��ʼ����22��1��1��8ʱ0��0�룻ע��:��DS1302���к󱸵�أ��Ͳ�Ҫ��ʱ�����ڳ�ʼ�������ˣ�����������ʱ����Ժ󿪹ػ����ܱ�֤ʱ������
	//��������û�нӱ��õ�أ�Ϊ����ʱ��������ӳ̶ȼ���ʱ���ʼ������Ȼ����Ҳ���ԣ���ÿ�ο���ʱ����������鷳��
	second=Read_Ds1302(0x81);
	minite=Read_Ds1302(0x83);
	hour=Read_Ds1302(0x85);//��ȡʱ�䣬��Ϊ������ʾֵ
	disp_buf_change(hour>>4,hour&0x0f,11,minite>>4,minite&0x0f,11,second>>4,second&0x0f);
	
	while(1){
		key_pro(); //���ð���������
		if(read_flag) //����־��Ч����ȡʱ������
		{
			read_flag=0;
			second=Read_Ds1302(0x81);
			minite=Read_Ds1302(0x83);
			hour=Read_Ds1302(0x85);
			date=Read_Ds1302(0x87);
			month=Read_Ds1302(0x89);
			year=Read_Ds1302(0x8d);
		}
		switch(interface) //����interface�Ĳ�ͬ��ʾ��ͬ���ܽ���
		{
			case 0://������ʾʱ�����
			{
				disp_buf_change(hour>>4,hour&0x0f,11,minite>>4,minite&0x0f,11,second>>4,second&0x0f);
			}break;
			case 1://������ʾ���ڽ���
			{
				disp_buf_change(year>>4,year&0x0f,11,month>>4,month&0x0f,11,date>>4,date&0x0f);
			}break;
			case 2://��ʾСʱ�������棨Сʱ��˸��
			{
					if(flash_flag)
					{
						disp_buf_change(hour>>4,hour&0x0f,11,minite>>4,minite&0x0f,11,second>>4,second&0x0f);
					}
					else
					{
						disp_buf_change(10,10,11,minite>>4,minite&0x0f,11,second>>4,second&0x0f);
					}
			}break;
			case 3://��ʾ���ӵ������棨������˸��
			{		
				if(flash_flag)
					{
						disp_buf_change(hour>>4,hour&0x0f,11,minite>>4,minite&0x0f,11,second>>4,second&0x0f);
					}
					else
					{
						disp_buf_change(hour>>4,hour&0x0f,11,10,10,11,second>>4,second&0x0f);
					}
			}break;
			case 4://��ʾ��������棨����˸��
			{
					if(flash_flag)
					{
						disp_buf_change(hour>>4,hour&0x0f,11,minite>>4,minite&0x0f,11,second>>4,second&0x0f);
					}
					else
					{
						disp_buf_change(hour>>4,hour&0x0f,11,minite>>4,minite&0x0f,11,10,10);
					}
			}break;
			case 5://��ʾ��ݵ������棨�����˸��
			{
					if(flash_flag)
					{
						disp_buf_change(year>>4,year&0x0f,11,month>>4,month&0x0f,11,date>>4,date&0x0f);
					}
					else
					{
						disp_buf_change(10,10,11,month>>4,month&0x0f,11,date>>4,date&0x0f);
					}
			}break;
			case 6://��ʾ�·ݵ������棨�·���˸��
			{
					if(flash_flag)
					{
						disp_buf_change(year>>4,year&0x0f,11,month>>4,month&0x0f,11,date>>4,date&0x0f);
					}
					else
					{
						disp_buf_change(year>>4,year&0x0f,11,10,10,11,date>>4,date&0x0f);
					}
			}break;
			case 7://��ʾ�յ������棨����˸��
			{
					if(flash_flag)
					{
						disp_buf_change(year>>4,year&0x0f,11,month>>4,month&0x0f,11,date>>4,date&0x0f);
					}
					else
					{
						disp_buf_change(year>>4,year&0x0f,11,month>>4,month&0x0f,11,10,10);
					}
			}break;				
		}
	}
		
}




