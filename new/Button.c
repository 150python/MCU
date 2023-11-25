#include "Global_Variable.h"
#include <STC15F2K60S2.H>
#include "DS1302.h"

void cls_nbuzz()
{
	Y0C;
	P0=0x00;
	Y5C;
	Y0C;
}


unsigned char key_scan() //������������ɨ�躯����ע�����������Ҳ�ɲ�ȡ�˽ṹ
{
	unsigned char temp;
	static unsigned char keypress_count,key_val; //keypress_countΪ������⵽�а������µĴ���������ȥ����
	P3=P3|0x0f;  //��P3��4λ���ó����뷽ʽ��ȷ������ȷ����P3�ڵ�4λ���ŵĵ�ƽ
	temp=P3&0x0f;  //����P3�ĵ�4λ��tem�ĵ�4λΪ�����P3�ĵ�4λ��tem�ĸ�4λ��Ϊ0
	if(temp!=0x0f) //��������P3�ĵ�4λ��ȫΪ0��˵���а�������
	{
		if(keypress_count<5)//�������ֵС��5
		{
			keypress_count++;//����ֵ��1
		}
		else//�������5�ξ���⵽�а������£��ж�����һ���������£���ȡ��ֵ 
		{
			if(P30==0) key_val=7;//���P30����0��˵��4�������������������Ǹ��겻S7�İ��������£�����ֵΪ7�������������ơ�ע�⣺P30~P37����stc15f2k60s2.h�ļ����ж���
			//����reg51.h���ļ���û�ж��壬ʹ��ʱ�������stc15f2k60s2.h��һ����P30�����ͷ�ļ�
			else if(P31==0) key_val=6;
			else if(P32==0) key_val=5;
			else if(P33==0) key_val=4;
		}
		return 0xff;//�������ڱ�����״̬������Ч��ֵ0xff
	}
	else  //���δ��⵽�������£�temp=0x0f,Ҳ���Ƕ����P3�ĵ�4λȫ1��˵���ް������¿ɰ������ͷţ�
	{
		if(keypress_count<5)//keypress_count<5��˵����⵽�����ͷ�֮ǰ������⵽�������ڱ����µ�״̬�Ĵ���С��5���ж�Ϊ��������������ֵ��Ч
		{
			keypress_count=0;
			return 0xff;//������Ч��ֵ
		}
		else//keypress_count=5��˵����⵽�����ͷ�֮ǰ������⵽�������ڱ����µ�״̬�Ĵ���>=5������ֵ��Ч������ʵ�ʰ���ֵ
		{
			key_valid=1;//������Ч��־��Ч��������������õ��˱�־�����ڴ���ʱ��0�ñ�־��
			keypress_count=0;
			return key_val;//������Ч��ֵ
		}
	}
}

void key_pro() //��������������������л���ʱ�䡢���ڵ���
{
	unsigned char tem;
	if(key_valid)//���������Ч��־��Ч���账��
	{
		key_valid=0;
		if(key_value==7)//����״̬�°��°���ΪS7���˰�������Ч������interface��0��7��Ҫִ��interface=(interface+1)%8;
			{
				interface=(interface+1)%8;
			}
		if(key_value==4)//����״̬�°��°���S4��������ʱ����ʾ����;
			{
				interface=0;
			}
		else //��S6��S5ֻ��interface��2��7ʱ��Ч������ֻ��interface��2��7ʱ���д���
		{
			switch(interface)//interface��2��7�����
			{			
				case 2: //Сʱ��������������ע����Сʱ����ע�����ƣ����������ظ�
				{
						switch(key_value)
						{
							case 6://�����°���ΪS6��Сʱ��1
							{
								tem=Read_Ds1302(0x85); //��ȡСʱ�����ΪBCD����ʽ
								tem=((tem>>4)&0x03)*10+(tem&0x0f);//��Сʱ���10������ʽ���ο�ds1302��datasheet�и��Ĵ�������ʽ����10ҳTable 3. Register Address/Definition��
								tem=(tem+1)%24;//Сʱ��1�����������23
								tem=((tem/10)<<4)+(tem%10);//�ٱ��BCD����ʽ
								Write_Ds1302(0x84,tem);
							}break;
							case 5://�����°���ΪS5��Сʱ��1
							{
								tem=Read_Ds1302(0x85);
								tem=((tem>>4)&0x03)*10+(tem&0x0f);
								if(tem>=1)
								tem--;
								else tem=23;
								tem=((tem/10)<<4)+(tem%10);
								Write_Ds1302(0x84,tem);
							}break;
						}
				}break;
				case 3: //���ӵ���
				{		
						switch(key_value)
						{
							case 6:
							{
								tem=Read_Ds1302(0x83);
								tem=(tem>>4)*10+(tem&0x0f);
								tem=(tem+1)%60;
								tem=((tem/10)<<4)+(tem%10);
								Write_Ds1302(0x82,tem);
							}break;
							case 5:
							{
								tem=Read_Ds1302(0x83);
								tem=(tem>>4)*10+(tem&0x0f);
								if(tem>=1)
								tem--;
								else tem=59;
								tem=((tem/10)<<4)+(tem%10);
								Write_Ds1302(0x82,tem);
							}break;
						}
				}break;
				case 4: //�����
				{
						switch(key_value)
						{
							case 6:
							{
								tem=Read_Ds1302(0x81);
								tem=(tem>>4)*10+(tem&0x0f);
								tem=(tem+1)%60;
								tem=((tem/10)<<4)+(tem%10);
								Write_Ds1302(0x80,tem);
							}break;
							case 5:
							{
								tem=Read_Ds1302(0x81);
								tem=(tem>>4)*10+(tem&0x0f);
								if(tem>=1)
								tem--;
								else tem=59;
								tem=((tem/10)<<4)+(tem%10);
								Write_Ds1302(0x80,tem);
							}break;
						}
				}break;
				case 5: //��ݵ���
				{
						switch(key_value)
						{
							case 6:
							{
								tem=Read_Ds1302(0x8d);
								tem=(tem>>4)*10+(tem&0x0f);
								tem=(tem+1)%100;
								tem=((tem/10)<<4)+(tem%10);
								Write_Ds1302(0x8c,tem);
							}break;
							case 5:
							{
								tem=Read_Ds1302(0x8d);
								tem=(tem>>4)*10+(tem&0x0f);
								if(tem>=1)
								tem=(tem-1);
								else tem=99;
								tem=((tem/10)<<4)+(tem%10);
								Write_Ds1302(0x8c,tem);
							}break;
						}
				}break;
				case 6: //�·ݵ���
				{
						switch(key_value)
						{
							case 6:
							{
								tem=Read_Ds1302(0x89);
								tem=(tem>>4)*10+(tem&0x0f);
								tem=(tem+1)%13;
								if(tem==0) tem=1;
								tem=((tem/10)<<4)+(tem%10);
								Write_Ds1302(0x88,tem);
							}break;
							case 5:
							{
								tem=Read_Ds1302(0x89);
								tem=(tem>>4)*10+(tem&0x0f);
								if(tem>=2)
								tem--;
								else tem=12;
								tem=((tem/10)<<4)+(tem%10);
								Write_Ds1302(0x88,tem);
							}break;
						}
				}break;
				case 7: //�յ���
				{
						switch(key_value)
						{
							case 6:
							{
								tem=Read_Ds1302(0x87);
								tem=(tem>>4)*10+(tem&0x0f);
								tem=(tem+1)%32;
								if(tem==0) tem=1;
								tem=((tem/10)<<4)+(tem%10);
								Write_Ds1302(0x86,tem);
							}break;
							case 5:
							{
								tem=Read_Ds1302(0x87);
								tem=(tem>>4)*10+(tem&0x0f);
								if(tem>=2)
								tem--;
								else tem=31;
								tem=((tem/10)<<4)+(tem%10);
								Write_Ds1302(0x86,tem);
							}break;
						}
				}break;					
			}	
		}				
	}
}