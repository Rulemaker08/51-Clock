#ifndef __I2C_H_
#define __I2C_H_

void I2C_Start();
void I2C_Stop();
void I2C_SendByte(unsigned char Data);
unsigned char I2C_ReceiveByte();
void I2C_SendAck(unsigned char SA);
unsigned char I2C_ReceiveAck();


#endif