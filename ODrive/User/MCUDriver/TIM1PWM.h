#ifndef TIM1_h
#define TIM1_h

#include "stdint.h"


void TIM1_Init(void);
void SetTIM1Channel1HighLeaveTime_us(float time);
void SetTIM1Channel2HighLeaveTime_us(float time);
void SetTIM1Channel3HighLeaveTime_us(float time);
void SetTIM1Channel4HighLeaveTime_us(float time);
void Timer1Channel4ITEnable(uint8_t isEnable);
#endif /* TIM1_h */
