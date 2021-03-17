#include "SvpwmConfig.h"
#include "Svpwm.h"

#include "TIM1PWM.h"




//声明一个SVPWM对象
SVPWM_EXPORT(gMotor,100.0f,80.0f,1.0f,12.0f,
                SetTIM1Channel1HighLeaveTime_us,
                SetTIM1Channel2HighLeaveTime_us,
                SetTIM1Channel3HighLeaveTime_us,
				SetTIM1Channel4HighLeaveTime_us)


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

