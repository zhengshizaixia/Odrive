#include "FOCConfig.h"
#include "FOC.h"

#include "MotorGPIO.h"
#include "ADC1.h"
#include "TIM3Encoder.h"
#include "TIM1PWM.h"
#include "SvpwmConfig.h"
#include "GPIONVIC.h"

#include "Timer.h"
#include "main.h"

#define M_OUTMAX  12.0f * 0.577f
#define M_KP  0.0001f
#define M_KI  0.00005f
#define M_KD  0.0f


/*************************************************************
** Function name:       Motor1AngleCalibration
** Descriptions:        电机一角度校准
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
static void MotorAngleCalibration(void)
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
    //while(1);
}
/*************************************************************
** Function name:       SetMotorAndTimITEnable
** Descriptions:        设置电机和定时器使能
** Input parameters:    isEnable：1：使能 2：失能
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
static void SetMotorAndTimITEnable(uint8_t isEnable)
{
	//设置驱动芯片使能
	SetMotorEnable(isEnable);
	//设置定时器使能
	Timer1Channel4ITEnable(isEnable);
}

/*************************************************************
** Function name:       GetMotorPreCurrent
** Descriptions:        获取电机 3相实际电流
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
static void GetMotorPreCurrent(float *ua,float *ub,float *uc)
{
	*ub = GetADC1ChannelXValue(0) - 0.0f;
	*uc = GetADC1ChannelXValue(1) - 0.0f;
	*ua = 0.0f - *ub - *uc;
	
	*ua = *ua * 0.1611f * 1.5f;
	*ub = *ub * 0.1611f * 1.5f;
	*uc = *uc * 0.1611f * 1.5f;
	
}

//声明FOC对象
FOC_EXPORT(gMotorFOC,7.0f,3,
			SetMotorAndTimITEnable,
			GetTimer3EncoderAngle,
			GetMotorSVPWMSector,
			GetMotorPreCurrent,
			MotorSvpwmGenerate)

/*************************************************************
** Function name:       FOCConfig_Init
** Descriptions:        FOC初始化
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void FOCConfig_Init(void)
{
	//角度校准
	MotorAngleCalibration();
	//设置PID参数
	SetCurrentPIDParams(&gMotorFOC,M_KP,M_KI,M_KD,M_OUTMAX);
	//FOC使能
    SetFocEnable(&gMotorFOC,1);
	
	//设置目标
	SetTarIDIQ(0,0);
}
/*************************************************************
** Function name:       MotorFocControl
** Descriptions:        电机FOC控制
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void MotorFocControl(void)
{
	FocContorl(&gMotorFOC);
}
/*************************************************************
** Function name:       SetTarIDIQ
** Descriptions:        设置电机目标电流
** Input parameters:    id：d轴电流单位A
**						iq: q轴电流单位A
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void SetTarIDIQ(float id,float iq)
{
	SetCurrentPIDTar(&gMotorFOC,id,iq);
}
/*************************************************************
** Function name:       FOCConfigPrintf
** Descriptions:        电机参数打印
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void FOCConfig_Printf(void)
{
	FOCPrintf(&gMotorFOC);
}



