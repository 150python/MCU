#ifndef __GLOBAL_VARIABLE_H__
#define __GLOBAL_VARIABLE_H__

// ά��ȫ�ֵı���
#define Y0C P2=P2&0X1F      // ��P2������ǰ��λ����
#define Y4C P2=P2&0X1F|0X80 // ��P2������ǰ��λ��Ϊ100  Y4ʹ��
#define Y5C P2=P2&0X1F|0XA0 // ��P2������ǰ��λ��Ϊ101  Y5ʹ��
#define Y6C P2=P2&0X1F|0XC0 // ��P2������ǰ��λ��Ϊ110  Y6ʹ��
#define Y7C P2=P2&0X1F|0XE0 // ��P2������ǰ��λ��Ϊ111  Y7ʹ��
extern unsigned char interface; //��ʾ�����л����Ʊ�����0:��ʾʱ�䣬1����ʾ���ڣ�2��Сʱ������3�����ӵ�����4���������5���������6���µ�����7���յ��� //�ɰ���S7˳���л�
extern unsigned char key_value; //��ֵ
extern bit key_valid;
extern bit read_flag,flash_flag;

#endif