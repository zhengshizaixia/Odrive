#include "AngleCalibrationFunc.h"


#include "MotorGPIO.h"
#include "TIM3Encoder.h"
#include "TIM1PWM.h"
#include "main.h"
#include "GPIONVIC.h"


/*************************************************************
** Function name:       Motor1AngleCalibration
** Descriptions:        电机一角度校准
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void Motor1AngleCalibration(void)
{
	//1.使能电机
	SetMotorEnable(1);
	//2.电机旋转至a轴
	SetTIM1Channel1HighLeaveTime_us(52);
	SetTIM1Channel2HighLeaveTime_us(48);
	SetTIM1Channel3HighLeaveTime_us(48);
	HAL_Delay(500);
	//3.读取角度
	for (uint8_t i = 0; i < 10; i++) {
		TimerEncoderReset();
		HAL_Delay(50);
	}
	//4.电机失能
	SetTIM1Channel1HighLeaveTime_us(0);
	SetTIM1Channel2HighLeaveTime_us(0);
	SetTIM1Channel3HighLeaveTime_us(0);
	SetMotorEnable(0);
	GPIONVIC_Init();
	HAL_Delay(2000);
	Timer1ITEnable();
    //while(1);
}

/*************************************************************
** Function name:      AngleCalibrationFunc_Init
** Descriptions:       编码器角度校准
** Input parameters:   none
** Output parameters:  none
** Returned value:     none
** Created by:         none
** Created date:       none
*************************************************************/
void AngleCalibrationFunc_Init(void)
{
    Motor1AngleCalibration();
}




