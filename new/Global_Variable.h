#ifndef __GLOBAL_VARIABLE_H__
#define __GLOBAL_VARIABLE_H__

// 维护全局的变量
#define Y0C P2=P2&0X1F      // 将P2锁存器前三位清零
#define Y4C P2=P2&0X1F|0X80 // 将P2锁存器前三位置为100  Y4使能
#define Y5C P2=P2&0X1F|0XA0 // 将P2锁存器前三位置为101  Y5使能
#define Y6C P2=P2&0X1F|0XC0 // 将P2锁存器前三位置为110  Y6使能
#define Y7C P2=P2&0X1F|0XE0 // 将P2锁存器前三位置为111  Y7使能
extern unsigned char interface; //显示界面切换控制变量。0:显示时间，1：显示日期，2：小时调整，3：分钟调整，4：秒调整，5：年调整，6：月调整，7：日调整 //由按键S7顺次切换
extern unsigned char key_value; //键值
extern bit key_valid;
extern bit read_flag,flash_flag;

#endif