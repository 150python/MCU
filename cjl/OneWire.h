#ifndef __OneWire_H__
#define __OneWire_H__
void reset_onewire_bus();
bit onewire_ack();
unsigned char Read_DS18B20_byte();
void Write_DS18B20_byte(unsigned char dat);
void init_DS18B20();
float read_temprature();

#endif