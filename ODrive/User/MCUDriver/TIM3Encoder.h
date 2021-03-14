
/***********************************************************************
* @file TIM3Encoder
* Description:
*
**********************************************************************
* File name:      TIM3Encoder.h
* Date:           2021-03-10
* Version:        V1.0
* Author          liuxiang
* @history:
* V1.0 创建文件
***********************************************************************/
#ifndef __TIM3Encoder_H__
#define __TIM3Encoder_H__
#include "stdint.h"

#include "stdio.h"
#include "stdint.h"





void TimerEncoderInit(void);
void TimerEncoderReset(void);
int32_t GetTimer3EncoderCnt(void);
void SetTimer3EncoderCnt(int32_t cnt);
float GetTimer3EncoderAngle(void);

#endif //__TIM3Encoder_H__





