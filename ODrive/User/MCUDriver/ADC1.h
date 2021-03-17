#ifndef ADC1_h
#define ADC1_h

#include "stdint.h"

void ADC1_Init(void);
int32_t GetADC1ChannelXValue(uint8_t channel);
void ADCDMAStart(void);
void ADCDMAIRQHandler(void);

#endif /* ADC1_h */
