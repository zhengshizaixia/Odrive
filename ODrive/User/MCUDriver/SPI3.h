/***********************************************************************
* @file SPI3
* Description:
*
**********************************************************************
* File name:      SPI3.h
* Date:           2021-03-22
* Version:        V1.0
* Author          liuxiang
* @history:
* V1.0 创建文件
***********************************************************************/
#ifndef __SPI3_H__
#define __SPI3_H__
#include "stdint.h"

void SetSPI3CSIsEnable(uint8_t isEnable);
void SPI3TransmitData(uint16_t data);
uint16_t SPI3ReceiveData(void);
uint16_t SPI3TransmitReceiveData(uint16_t data);

#endif //__SPI3_H__


