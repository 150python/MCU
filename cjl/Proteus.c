#include <REGX52.H>
// ����ܹ�����                 P27 P26 P25
#define Y0C P2=P2&0X1F      // ��������ǰ��λ����
#define Y4C P2=P2&0X1F|0X80 // ��������ǰ��λ��Ϊ100  Y4ʹ��
#define Y5C P2=P2&0X1F|0XA0 // ��������ǰ��λ��Ϊ101  Y5ʹ��
#define Y6C P2=P2&0X1F|0XC0 // ��������ǰ��λ��Ϊ110  Y6ʹ��
#define Y7C P2=P2&0X1F|0XE0 // ��������ǰ��λ��Ϊ111  Y7ʹ��

unsigned char code duan_code[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff,0xc8}; //����
unsigned char disp_buf[8];

void disp_buf_change(unsigned char one,two,three,four,five,six,seven,eight)
{
	disp_buf[0]=duan_code[one];
	disp_buf[1]=duan_code[two];
	disp_buf[2]=duan_code[three];
	disp_buf[3]=duan_code[four];
	disp_buf[4]=duan_code[five];
	disp_buf[5]=duan_code[six];
	disp_buf[6]=duan_code[seven];
	disp_buf[7]=duan_code[eight];
}

void disp(unsigned char i)
{
	static unsigned char disp_com;
	Y0C;// ��ʼ��������
	P0 = 0X00;// λѡ��Ϊ0
	Y6C;// ��λѡ������  ������Ӱ
	Y0C;// �ر�λѡ������
	if(i==disp_com)
	{
		P0=disp_buf[disp_com]&0x7f;
	}
	else
	{
		P0=disp_buf[disp_com];
	}
	Y7C; // �򿪶�ѡ������ �������P0�����ȥ
	Y0C; // �رն�ѡ
	P0=1<<disp_com;
	disp_com=(disp_com+1)%8;
	Y6C; //��λѡ���������P0�����ȥ
	Y0C; // �رն�ѡ
}

