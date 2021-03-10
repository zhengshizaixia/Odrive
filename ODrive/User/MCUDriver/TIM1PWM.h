#ifndef TIM1_h
#define TIM1_h

#include "stdint.h"


void TIM1_Init(void);
void SetTIM1Channel1HighLeaveTime_us(float time);
void SetTIM1Channel2HighLeaveTime_us(float time);
void SetTIM1Channel3HighLeaveTime_us(float time);
#endif /* TIM1_h */
