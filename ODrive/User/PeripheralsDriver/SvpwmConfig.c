#include "SvpwmConfig.h"
#include "Svpwm.h"

#include "TIM1PWM.h"
#include "TIM3Encoder.h"
#include "MotorGPIO.h"
#include "arm_math.h"




#define U 0.5f

float motorAngle;

float GetMotorUα(void)
{
	float Uα;
    static float angle = 0.0f;
    angle = motorAngle;
	Uα = U* 0.577f * arm_sin_f32(angle * 0.01745f);
	return Uα;
}

float GetMotorUβ(void)
{
	float Uβ;
    static float angle = 0.0f;
	angle = motorAngle;
	Uβ = U* 0.577f * -arm_cos_f32(angle * 0.01745f);
	return Uβ;
}

//声明一个SVPWM对象
SVPWM_EXPORT(gMotor,100.0f,12.0f,
                SetTIM1Channel1HighLeaveTime_us,
                SetTIM1Channel2HighLeaveTime_us,
                SetTIM1Channel3HighLeaveTime_us)


/*************************************************************
** Function name:       MotorSvpwmGenerate
** Descriptions:        电机SVPWM生成
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void MotorSvpwmGenerate(float uα,float uβ)
{
    SvpwmContorol(&gMotor,uα,uβ);
}
/*************************************************************
** Function name:       GetMotorSVPWMSector
** Descriptions:        获取电机的扇区
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
uint8_t GetMotorSVPWMSector(void)
{
    return GetSVPWMSector(&gMotor);
}

/*************************************************************
** Function name:       MotorSvpwmConfigTest
** Descriptions:        电机SVPWM测试
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void MotorSvpwmConfigTest(void)
{
	SetMotorEnable(1);
	motorAngle = GetTimerEncoderAngle() * 4.0f;
	MotorSvpwmGenerate(GetMotorUα(),GetMotorUβ());
}


