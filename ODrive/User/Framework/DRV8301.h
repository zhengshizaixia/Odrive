/***********************************************************************
* @file DRV8301
* Description:
*
**********************************************************************
* File name:      DRV8301.h
* Date:           2021-03-22
* Version:        V1.0
* Author          liuxiang
* @history:
* V1.0 创建文件
***********************************************************************/
#ifndef __DRV8301_H__
#define __DRV8301_H__
#include "stdint.h"


struct SDRV8301_Struct
{
    uint8_t rw;
    uint8_t addr;
    uint16_t data;
    void (*SetCSIsEnable)(uint8_t isEnable);
    uint16_t (*ReadData)(void);
    void (*WriteData)(uint16_t data);
	uint16_t (*WriteReadData)(uint16_t data);
    /* data */
};

typedef struct SDRV8301_Struct DRV8301_Struct;
typedef DRV8301_Struct *PDRV8301_Struct;


#define DRV8301_EXPORT(x,xSetCSIsEnable,xReadData,xWriteData,xWriteReadData)   \
DRV8301_Struct x = {                                            \
    .rw = 0,                                                    \
    .addr = 0,                                                  \
    .data = 0,                                                  \
    .SetCSIsEnable = xSetCSIsEnable,                            \
    .ReadData = xReadData,                                      \
    .WriteData = xWriteData,                                    \
	.WriteReadData = xWriteReadData,      						\
};


void DRV8301SetGain(PDRV8301_Struct gDRV8301);
#endif //__DRV8301_H__



