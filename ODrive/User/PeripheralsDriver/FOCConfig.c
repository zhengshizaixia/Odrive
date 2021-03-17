#include "FOCConfig.h"

#include "MotorGPIO.h"
#include "FOC.h"
#include "SvpwmConfig.h"
#include "ADC1.h"
#include "TIM3Encoder.h"

#include "Timer.h"


//#define M_KP  0.00008f
//#define M_KI  0.00005f
#define M_TAR_IQ  3.0f
#define M_TAR_ID  0.0f
#define M_OUTMAX  12.0f * 0.577f
#define M_KP  0.0001f
#define M_KI  0.00005f
#define M_KD  0.0f


/*************************************************************
** Function name:       GetMotor1PreCurrent
** Descriptions:        获取电机1 3相电流值
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void GetMotorPreCurrent(float *ua,float *ub,float *uc)
{
	*ub = GetADC1ChannelXValue(0) - 0.0f;
	*uc = GetADC1ChannelXValue(1) - 0.0f;
	*ua = 0 - *ub - *uc;
}

//声明两个FOC对象
FOC_EXPORT(gMotorFOC,0.0005f,7.0f,3,SetMotorEnable,GetTimer3EncoderAngle,GetMotorSVPWMSector,GetMotorPreCurrent,MotorSvpwmGenerate)



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

    SetFocEnable(&gMotorFOC,1);
    SetCurrentPIDTar(&gMotorFOC,M_TAR_ID,M_TAR_IQ);
    SetCurrentPIDParams(&gMotorFOC,M_KP,M_KI,M_KD,M_OUTMAX);
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
** Function name:       FOCConfigPrintf
** Descriptions:        电机参数打印
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void FOCConfigPrintf(void)
{
	FOCPrintf(&gMotorFOC);
}


void SetTarIDIQ(float id,float iq)
{
	SetCurrentPIDTar(&gMotorFOC,id,iq);
}

