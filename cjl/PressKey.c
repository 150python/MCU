#include <REGX52.H>
#include "Tools.h"
// �������У�5-10��ms ����
// �ͷŽ�Ҳ��(5-10)ms ����
// ֻ���м�ģ�20-200��ms �ȶ�

void Depend_Key_Read() // ����������P30 P31 P32 P33 
{
	if(P3_0 == 0)
	{
		Delayms(20);
		while(P3_0==0);
		Delayms(20);
		P0_0 = !P0_0;	
	}
}




