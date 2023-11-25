#include <STC15F2K60S2.H>
#include "Global_Variable.h"
#include "Proteus.h"
#include "Timer.h"
#include "DS1302.h"
#include "Button.h"
#include "Led.h"


unsigned char interface=0; //显示界面切换控制变量。0:显示时间，1：显示日期，2：小时调整，3：分钟调整，4：秒调整，5：年调整，6：月调整，7：日调整 //由按键S7顺次切换
unsigned char key_value=0xff; //键值
bit key_valid=0;
bit read_flag,flash_flag;

void main(){
	
	unsigned char second,minite,hour,date,month,year;
	cls_led(); cls_nbuzz();
	Timer0_Init(); // 初始化定时器0
	Write_Ds1302(0x8e,0x00);// 去写保护
	Write_Ds1302(0x80,0x00);// 秒
	Write_Ds1302(0x82,0x09);// 分
	Write_Ds1302(0x84,0x08);// 时
	Write_Ds1302(0x86,0x01);// 日
	Write_Ds1302(0x88,0x01);// 月
	Write_Ds1302(0x8c,0x22);// 年
	//DS1302初始化成22年1月1日8时0分0秒；注意:如DS1302接有后备电池，就不要加时间日期初始化代码了，这样调整好时间后，以后开关机都能保证时间正常
	//本开发板没有接备用电池，为降低时间调整复杂程度加了时间初始化，当然不加也可以，但每次开机时间调整都较麻烦。
	second=Read_Ds1302(0x81);
	minite=Read_Ds1302(0x83);
	hour=Read_Ds1302(0x85);//读取时间，作为开机显示值
	disp_buf_change(hour>>4,hour&0x0f,11,minite>>4,minite&0x0f,11,second>>4,second&0x0f);
	
	while(1){
		key_pro(); //调用按键处理函数
		if(read_flag) //读标志有效，读取时间日期
		{
			read_flag=0;
			second=Read_Ds1302(0x81);
			minite=Read_Ds1302(0x83);
			hour=Read_Ds1302(0x85);
			date=Read_Ds1302(0x87);
			month=Read_Ds1302(0x89);
			year=Read_Ds1302(0x8d);
		}
		switch(interface) //根据interface的不同显示不同功能界面
		{
			case 0://正常显示时间界面
			{
				disp_buf_change(hour>>4,hour&0x0f,11,minite>>4,minite&0x0f,11,second>>4,second&0x0f);
			}break;
			case 1://正常显示日期界面
			{
				disp_buf_change(year>>4,year&0x0f,11,month>>4,month&0x0f,11,date>>4,date&0x0f);
			}break;
			case 2://显示小时调整界面（小时闪烁）
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
			case 3://显示分钟调整界面（分钟闪烁）
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
			case 4://显示秒调整界面（秒闪烁）
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
			case 5://显示年份调整界面（年份闪烁）
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
			case 6://显示月份调整界面（月份闪烁）
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
			case 7://显示日调整界面（日闪烁）
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




