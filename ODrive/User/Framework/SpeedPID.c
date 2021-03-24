#include "SpeedPID.h"

#include "stdio.h"
#include "SEGGER_RTT.h"
#include "SEGGER_RTT_Conf.h"

volatile uint32_t gSpeedPID_TimeCNT;



/*************************************************************
** Function name:       SpeedPIDControl
** Descriptions:        速度PID控制
** Input parameters:    pSpeedPID:结构体指针
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
static void SpeedPIDControl(PSpeedPIDControl_Struct pSpeedPID)
{

    pSpeedPID->sPID.pre = pSpeedPID->GetPreSpeed();
    pSpeedPID->sPID.bais = pSpeedPID->sPID.tar - pSpeedPID->sPID.pre;
    pSpeedPID->sPID.out += pSpeedPID->sPID.kp*(pSpeedPID->sPID.bais - pSpeedPID->sPID.last_bias) +  pSpeedPID->sPID.ki * pSpeedPID->sPID.bais;
    pSpeedPID->sPID.last_bias = pSpeedPID->sPID.bais;

	if (pSpeedPID->sPID.out > pSpeedPID->sPID.outMax) {
		pSpeedPID->sPID.out = pSpeedPID->sPID.outMax;
	} else if (pSpeedPID->sPID.out < -pSpeedPID->sPID.outMax) {
		pSpeedPID->sPID.out = -pSpeedPID->sPID.outMax;
	}
    if(pSpeedPID->isEnable == 0) {
        pSpeedPID->sPID.out = 0;
    }
    pSpeedPID->SetOutCurrent(pSpeedPID->sPID.out);
}

/*************************************************************
** Function name:       SpeedPIDCycle
** Descriptions:        速度PID循环函数
** Input parameters:    pSpeedPID:结构体指针
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void SpeedPIDCycle(PSpeedPIDControl_Struct pSpeedPID)
{
    if(SPEEDPID_TIMEOUT(pSpeedPID->sPID.cycle * 1000.0f,pSpeedPID->sysTimer)) {
        pSpeedPID->sysTimer = SPEEDPID_GETTIME();
        SpeedPIDControl(pSpeedPID);
    }
}
/*************************************************************
** Function name:       SetSpeedPIDParams
** Descriptions:        设置速度PID参数
** Input parameters:    pSpeedPID:结构体指针
**                      kp:比例
**                      ki:积分
**                      kd:微分
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void SetSpeedPIDParams(PSpeedPIDControl_Struct pSpeedPID,float kp,float ki,float kd)
{
    pSpeedPID->sPID.kp = kp;
    pSpeedPID->sPID.ki = ki;
    pSpeedPID->sPID.kd = kd;
}
/*************************************************************
** Function name:       SetSpeedPIDTar
** Descriptions:        设置目标值
** Input parameters:    pSpeedPID:结构体指针
**                      tar:目标速度
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void SetSpeedPIDTar(PSpeedPIDControl_Struct pSpeedPID,float tar)
{
    pSpeedPID->sPID.tar = tar;
}



/*************************************************************
** Function name:       SetSpeedPIDEnable
** Descriptions:        设置速度PID使能
** Input parameters:    pSpeedPID:结构体指针
**                      isEnable:1: 使能0：失能
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void SetSpeedPIDEnable(PSpeedPIDControl_Struct pSpeedPID,float isEnable)
{
    pSpeedPID->isEnable = isEnable;
}




/*************************************************************
** Function name:       SpeedPIDPrintf
** Descriptions:        速度PID信息打印
** Input parameters:    pSpeedPID:结构体指针
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void SpeedPIDPrintf(PSpeedPIDControl_Struct pSpeedPID)
{
	printf("2:%f\r\n",pSpeedPID->sPID.pre);
	printf("3:%f\r\n",pSpeedPID->sPID.tar);
}



























