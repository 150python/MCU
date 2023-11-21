#include "Tools.h"
#include "LED.h"
#include "PressKey.h"
#include "Proteus.h"
#include "OneWire.h"


void main()
{
	float temp;
	unsigned int temp_disp;
	close_led();// ¹Ø±Õled
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