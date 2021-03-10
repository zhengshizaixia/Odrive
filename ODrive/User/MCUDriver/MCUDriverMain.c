#include "MCUDriverMain.h"
#include "main.h"

#include "TIM1PWM.h"
#include "TIM3Encoder.h"
#include "timer.h"
#include "MotorGPIO.h"
/*************************************************************
** Function name:      MCUDriverMain_Init
** Descriptions:       芯片初始化
** Input parameters:   none
** Output parameters:  none
** Returned value:     none
** Created by:         none
** Created date:       none
*************************************************************/
void MCUDriverMain_Init(void)
{
	SetMotorEnable(1);
	TIM1_Init();
	TimerEncoderInit();
}

/*************************************************************
** Function name:      MCUDriverMain_Loop
** Descriptions:       芯片循环
** Input parameters:   none
** Output parameters:  none
** Returned value:     none
** Created by:         none
** Created date:       none
*************************************************************/
void MCUDriverMain_Loop(void)
{
//	RUN_BY_LIMIT_BLOCK(200,
//		printf("1:%d\r\n",GetTimer3EncoderCnt());
//		printf("2:%f\r\n",GetTimerEncoderAngle());
//	)
	

}


