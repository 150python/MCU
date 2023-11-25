#include <STC15F2K60S2.H>
#include "Global_Variable.h"

void cls_led()
{
	Y0C;
	P0=0xff;
	Y4C;
	Y0C;
}