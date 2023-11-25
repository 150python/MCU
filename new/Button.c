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


unsigned char key_scan() //独立按键键盘扫描函数，注意矩阵键盘设计也可采取此结构
{
	unsigned char temp;
	static unsigned char keypress_count,key_val; //keypress_count为连续检测到有按键按下的次数，用以去抖动
	P3=P3|0x0f;  //将P3低4位设置成输入方式，确保能正确读入P3口低4位引脚的电平
	temp=P3&0x0f;  //读入P3的低4位，tem的低4位为读入的P3的低4位，tem的高4位均为0
	if(temp!=0x0f) //如果读入的P3的低4位不全为0，说明有按键按下
	{
		if(keypress_count<5)//如果计数值小于5
		{
			keypress_count++;//计数值加1
		}
		else//如果连续5次均检测到有按键按下，判断是哪一个按键按下，读取键值 
		{
			if(P30==0) key_val=7;//如果P30等于0，说明4个独立按键中最上面那个标不S7的按键被按下，按键值为7，下面三行类似。注意：P30~P37等在stc15f2k60s2.h文件中有定义
			//但在reg51.h等文件中没有定义，使用时必须包含stc15f2k60s2.h这一类有P30定义的头文件
			else if(P31==0) key_val=6;
			else if(P32==0) key_val=5;
			else if(P33==0) key_val=4;
		}
		return 0xff;//按键处于被按下状态返回无效键值0xff
	}
	else  //如果未检测到按键按下（temp=0x0f,也就是读入的P3的低4位全1，说明无按键按下可按键已释放）
	{
		if(keypress_count<5)//keypress_count<5，说明检测到按键释放之前连续检测到按键处于被按下的状态的次数小于5，判断为按键抖动，按键值无效
		{
			keypress_count=0;
			return 0xff;//返回无效键值
		}
		else//keypress_count=5，说明检测到按键释放之前连续检测到按键处于被按下的状态的次数>=5，按键值有效，返回实际按键值
		{
			key_valid=1;//按键有效标志有效，按键处理进将用到此标志，并在处理时清0该标志。
			keypress_count=0;
			return key_val;//返回有效键值
		}
	}
}

void key_pro() //按键处理函数，处理界面切换及时间、日期调整
{
	unsigned char tem;
	if(key_valid)//如果按键有效标志有效才需处理
	{
		key_valid=0;
		if(key_value==7)//任意状态下按下按键为S7，此按键均有效，所以interface从0到7都要执行interface=(interface+1)%8;
			{
				interface=(interface+1)%8;
			}
		if(key_value==4)//任意状态下按下按键S4，均返回时间显示界面;
			{
				interface=0;
			}
		else //而S6、S5只在interface从2到7时有效，所以只在interface从2到7时进行处理
		{
			switch(interface)//interface从2到7的情况
			{			
				case 2: //小时调整，其他调整注释与小时调整注释类似，后面有再重复
				{
						switch(key_value)
						{
							case 6://被按下按键为S6，小时加1
							{
								tem=Read_Ds1302(0x85); //读取小时，结果为BCD码形式
								tem=((tem>>4)&0x03)*10+(tem&0x0f);//将小时变成10进制形式（参看ds1302的datasheet中各寄存器的形式，第10页Table 3. Register Address/Definition）
								tem=(tem+1)%24;//小时加1，结果不超过23
								tem=((tem/10)<<4)+(tem%10);//再变回BCD码形式
								Write_Ds1302(0x84,tem);
							}break;
							case 5://被按下按键为S5，小时减1
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
				case 3: //分钟调整
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
				case 4: //秒调整
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
				case 5: //年份调整
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
				case 6: //月份调整
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
				case 7: //日调整
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