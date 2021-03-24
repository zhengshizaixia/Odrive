#ifndef FocConfig_h
#define FocConfig_h

#include "stdint.h"

void FOCConfig_Init(void);
void FOCConfig_Loop(void);

void MotorFocControl(void);
void FOCConfig_Printf(void);
void SetTarIDIQ(float id,float iq);
#endif /* FocConfig_h */
