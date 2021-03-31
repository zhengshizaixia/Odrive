#include "PositionPID.h"





#include "stdio.h"
#include "SEGGER_RTT.h"
#include "SEGGER_RTT_Conf.h"

volatile uint32_t gPositionPID_TimeCNT;



/*************************************************************
** Function name:       PositionPIDControl
** Descriptions:        位置PID控制
** Input parameters:    pPositionPID:结构体指针
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
static void PositionPIDControl(PPositionPIDControl_Struct pPositionPID)
{

    pPositionPID->pPID.pre = pPositionPID->GetPrePosition();
    pPositionPID->pPID.bais = pPositionPID->pPID.tar - pPositionPID->pPID.pre;
    pPositionPID->pPID.out = pPositionPID->pPID.kp* pPositionPID->pPID.bais + pPositionPID->pPID.kd * (pPositionPID->pPID.bais - pPositionPID->pPID.last_bias) +  pPositionPID->pPID.ki * pPositionPID->pPID.err;
    pPositionPID->pPID.last_bias = pPositionPID->pPID.bais;
    pPositionPID->pPID.err += pPositionPID->pPID.bais;

	if (pPositionPID->pPID.out > pPositionPID->pPID.outMax) {
		pPositionPID->pPID.out = pPositionPID->pPID.outMax;
	} else if (pPositionPID->pPID.out < -pPositionPID->pPID.outMax) {
		pPositionPID->pPID.out = -pPositionPID->pPID.outMax;
	}
    if(pPositionPID->isEnable == 0) {
        pPositionPID->pPID.out = 0;
    }
    pPositionPID->SetMotorSpeed(pPositionPID->pPID.out);
}

/*************************************************************
** Function name:       PositionPIDCycle
** Descriptions:        位置PID循环函数
** Input parameters:    pPositionPID:结构体指针
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void PositionPIDCycle(PPositionPIDControl_Struct pPositionPID)
{
    if(POSITIONPID_TIMEOUT(pPositionPID->pPID.cycle * 1000.0f,pPositionPID->sysTimer)) {
        pPositionPID->sysTimer = POSITIONPID_GETTIME();
        PositionPIDControl(pPositionPID);
    }
}
/*************************************************************
** Function name:       SetPositionPIDParams
** Descriptions:        设置位置PID参数
** Input parameters:    pPositionPID:结构体指针
**                      kp:比例
**                      ki:积分
**                      kd:微分
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void SetPositionPIDParams(PPositionPIDControl_Struct pPositionPID,float kp,float ki,float kd)
{
    pPositionPID->pPID.kp = kp;
    pPositionPID->pPID.ki = ki;
    pPositionPID->pPID.kd = kd;
}
/*************************************************************
** Function name:       SetPositionPIDTar
** Descriptions:        设置目标值
** Input parameters:    pPositionPID:结构体指针
**                      tar:目标位置
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void SetPositionPIDTar(PPositionPIDControl_Struct pPositionPID,float tar)
{
    pPositionPID->pPID.tar = tar;
}



/*************************************************************
** Function name:       SetPositionPIDEnable
** Descriptions:        设置位置PID使能
** Input parameters:    pPositionPID:结构体指针
**                      isEnable:1: 使能0：失能
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void SetPositionPIDEnable(PPositionPIDControl_Struct pPositionPID,float isEnable)
{
    pPositionPID->isEnable = isEnable;
}




/*************************************************************
** Function name:       PositionPIDPrintf
** Descriptions:        位置PID信息打印
** Input parameters:    pPositionPID:结构体指针
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void PositionPIDPrintf(PPositionPIDControl_Struct pPositionPID)
{
	printf("2:%f\r\n",pPositionPID->pPID.pre);
	printf("3:%f\r\n",pPositionPID->pPID.tar);
}










