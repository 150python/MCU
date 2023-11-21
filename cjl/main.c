#include "Tools.h"
#include "LED.h"
#include "PressKey.h"
#include "Proteus.h"
#include "OneWire.h"

void main()
{
	Init_Led();
	Timer0_Init(1000);
	float temp;
	unsigned int temp_disp;
	while(1){
		
		//disp_buf_change(0,1,2,3,4,5,6,9);
		
		if(flag)
		{
//			light_led(3);
//			Delayms(100);
//			clear_led(3);
			temp = read_temprature();
			temp_disp = (int)(temp*100);
			disp_buf_change(10,10,10,10,temp_disp>=1000?temp_disp/1000:10,temp_disp>=100?temp_disp%1000/100:10,
			temp_disp%100/10,temp_disp%10);
			flag = 0;
		}
		Depend_Key_Read();
	}
}