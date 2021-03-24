/***********************************************************************
* @file SpeedPIDConfig
* Description:
*
**********************************************************************
* File name:      SpeedPIDConfig.h
* Date:           2021-03-24
* Version:        V1.0
* Author          liuxiang
* @history:
* V1.0 创建文件
***********************************************************************/
#ifndef __SpeedPIDConfig_H__
#define __SpeedPIDConfig_H__
#include "stdint.h"


void SpeedPIDConfig_Init(void);
void SetSpeedPIDConfigTarSpeed(float tarSpeed);
void SpeedPIDConfig_Loop(void);
void SpeedPIDConfig_Printf(void);


#endif //__SpeedPIDConfig_H__



