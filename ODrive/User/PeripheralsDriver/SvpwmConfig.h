/***********************************************************************
* @file SvpwmConfig
* Description:
*
**********************************************************************
* File name:      SvpwmConfig.h
* Date:           2021-03-10
* Version:        V1.0
* Author          liuxiang
* @history:
* V1.0 创建文件
***********************************************************************/
#ifndef __SvpwmConfig_H__
#define __SvpwmConfig_H__
#include "stdint.h"


uint8_t GetMotorSVPWMSector(void);
void MotorSvpwmGenerate(float uα,float uβ);
void MotorSvpwmConfigTest(void);
#endif //__SvpwmConfig_H__


