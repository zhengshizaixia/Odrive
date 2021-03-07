#include "FOC.h"
#include "math.h"
#include "arm_math.h"

#include "stdio.h"
#include "SEGGER_RTT.h"
#include "SEGGER_RTT_Conf.h"


#define FOC_SQRT_3 1.732f
#define FOC_ANGLE_TO_RADIN 0.01745f


volatile uint32_t gFoc_TimeCNT;
/*************************************************************
** Function name:       GetElectricalAngle
** Descriptions:        获取电气角度
** Input parameters:    pFOC:结构体指针
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
static void GetElectricalAngle(PFOC_Struct pFOC)
{
    pFOC->angle = pFOC->GetEncoderAngle() * pFOC->polePairs;
    pFOC->radian = pFOC->angle * FOC_ANGLE_TO_RADIN;
}
/*************************************************************
** Function name:       CurrentReconstruction
** Descriptions:        电流重构
** Input parameters:    pFOC:结构体指针
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
static void CurrentReconstruction(PFOC_Struct pFOC)
{
    pFOC->GetPreCurrent(&pFOC->ia,&pFOC->ib,&pFOC->ic);
    switch (pFOC->GetSVPWMSector()) {
        case 1:
            pFOC->ia =0.0f - pFOC->ib - pFOC->ic;
            break;
        case 2:
            pFOC->ib =0.0f - pFOC->ia - pFOC->ic;
            break;
        case 3:
            pFOC->ib =0.0f - pFOC->ia - pFOC->ic;
            break;
        case 4:
            pFOC->ic =0.0f - pFOC->ia - pFOC->ib;
            break;
        case 5:
            pFOC->ic =0.0f - pFOC->ia - pFOC->ib;
            break;
        case 6:
            pFOC->ia =0.0f - pFOC->ib - pFOC->ic;
            break;
        default:
            break;
    }
//	printf("5:%f\r\n",pFOC->ia);
//	printf("6:%f\r\n",pFOC->ib);
//	printf("7:%f\r\n",pFOC->ic);
}
/*************************************************************
** Function name:       ClarkeTransform
** Descriptions:        Clarke正变换
** Input parameters:    pFOC:结构体指针
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
static void ClarkeTransform(PFOC_Struct pFOC)
{
    pFOC->iα = pFOC->ia;
    pFOC->iβ = (pFOC->ia + 2.0f * pFOC->ib) / FOC_SQRT_3;
}
/*************************************************************
** Function name:       ParkTransform
** Descriptions:        Park正变换
** Input parameters:    pFOC:结构体指针
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
static void ParkTransform(PFOC_Struct pFOC)
{
    pFOC->id = pFOC->iα * arm_cos_f32(pFOC->radian) + pFOC->iβ * arm_sin_f32(pFOC->radian);
    pFOC->iq = -pFOC->iα * arm_sin_f32(pFOC->radian) + pFOC->iβ * arm_cos_f32(pFOC->radian);
}

/*************************************************************
** Function name:       ParkAntiTransform
** Descriptions:        Park反变换
** Input parameters:    pFOC:结构体指针
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
static void ParkAntiTransform(PFOC_Struct pFOC)
{
    pFOC->iαSVPWM = pFOC->idPID.out * arm_cos_f32(pFOC->radian) - pFOC->iqPID.out * arm_sin_f32(pFOC->radian);
    pFOC->iβSVPWM = pFOC->idPID.out * arm_sin_f32(pFOC->radian) + pFOC->iqPID.out * arm_cos_f32(pFOC->radian);
}

/*************************************************************
** Function name:       CurrentPIControlID
** Descriptions:        D轴电流闭环
** Input parameters:    pFOC:结构体指针
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
static void CurrentPIControlID(PFOC_Struct pFOC)
{
    //获取实际值
    pFOC->idPID.pre = pFOC->id;
    //获取目标值
    pFOC->idPID.tar = pFOC->tarid;
    //计算偏差
    pFOC->idPID.bias = pFOC->idPID.tar - pFOC->idPID.pre;
    //计算PID输出值
    pFOC->idPID.out += pFOC->idPID.kp * (pFOC->idPID.bias - pFOC->idPID.lastBias) + pFOC->idPID.ki * pFOC->idPID.bias;
    //保存偏差
    pFOC->idPID.lastBias = pFOC->idPID.bias;

    if (pFOC->idPID.out > fabs(pFOC->idPID.outMax)) {
        pFOC->idPID.out = fabs(pFOC->idPID.outMax);
    }

    if (pFOC->idPID.out < -fabs(pFOC->idPID.outMax)) {
        pFOC->idPID.out = -fabs(pFOC->idPID.outMax);
    }
//	printf("3:%f\r\n",pFOC->tarid);
//	printf("4:%f\r\n",pFOC->id);
}
/*************************************************************
** Function name:       CurrentPIControlIQ
** Descriptions:        Q轴电流闭环
** Input parameters:    pFOC:结构体指针
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
static void CurrentPIControlIQ(PFOC_Struct pFOC)
{
    //获取实际值
    pFOC->iqPID.pre = pFOC->iq;
    //获取目标值
    pFOC->iqPID.tar = pFOC->tariq;
    //计算偏差
    pFOC->iqPID.bias = pFOC->iqPID.tar - pFOC->iqPID.pre;
    //计算PID输出值
    pFOC->iqPID.out += pFOC->iqPID.kp * (pFOC->iqPID.bias - pFOC->iqPID.lastBias) + pFOC->iqPID.ki * pFOC->iqPID.bias;
    //保存偏差
    pFOC->iqPID.lastBias = pFOC->iqPID.bias;

    if (pFOC->iqPID.out > fabs(pFOC->iqPID.outMax)) {
        pFOC->iqPID.out = fabs(pFOC->iqPID.outMax);
    }

    if (pFOC->iqPID.out < -fabs(pFOC->iqPID.outMax)) {
        pFOC->iqPID.out = -fabs(pFOC->iqPID.outMax);
    }

//	printf("1:%f\r\n",pFOC->tariq);
//	printf("2:%f\r\n",pFOC->iq);
}

/*************************************************************
** Function name:       FocContorl
** Descriptions:        FOC控制流程
** Input parameters:    pFOC:结构体指针
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
static void FocContorl(PFOC_Struct pFOC)
{
    pFOC->SetEnable( pFOC->isEnable);
    //0.获取电气角度
    GetElectricalAngle(pFOC);
    //1计算实际电流值
        //1.0电流重构
        CurrentReconstruction(pFOC);
        //1.1Clarke变换
        ClarkeTransform(pFOC);
        //1.2Park变换
        ParkTransform(pFOC);
    //2.做PID闭环
    CurrentPIControlID(pFOC);
    CurrentPIControlIQ(pFOC);
	// pFOC->iqPID.out = 1;
	pFOC->idPID.out = 0.0f;
    //3.计算输出值iα i贝塔
    ParkAntiTransform(pFOC);
    //4.输出SVPWM
    pFOC->SvpwmGenerate(pFOC->iαSVPWM,pFOC->iβSVPWM);
	return;
}
/*************************************************************
** Function name:       FOCCycle
** Descriptions:        FOC主循环
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void FOCCycle(PFOC_Struct pFOC)
{
        if(FOC_TIMEOUT(pFOC->cycle*1000,pFOC->startTime)) {
            pFOC->startTime = FOC_GETTIME();
            FocContorl(pFOC);
        }
}
/*************************************************************
** Function name:       SetCurrentPIDTar
** Descriptions:        设置D轴和Q轴的目标值
** Input parameters:    pFOC：FOC对象指针
**                      tarid：D轴目标电流
**                      tariq：Q轴目标电流
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void SetCurrentPIDTar(PFOC_Struct pFOC,float tarid,float tariq)
{
    pFOC->tarid = tarid;
    pFOC->tariq = tariq;
}
/*************************************************************
** Function name:       SetCurrentPIDParams
** Descriptions:        设置电流环参数
** Input parameters:    pFOC：FOC对象指针
**                      kp:比例
**                      ki:积分
**                      kd:微分
**                      outMax:输出限幅
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void SetCurrentPIDParams(PFOC_Struct pFOC,float kp,float ki,float kd,float outMax)
{
    pFOC->idPID.kp = kp;
    pFOC->idPID.ki = ki;
    pFOC->idPID.kd = kd;
    pFOC->idPID.outMax = outMax;

    pFOC->iqPID.kp = kp;
    pFOC->iqPID.ki = ki;
    pFOC->iqPID.kd = kd;
    pFOC->iqPID.outMax = outMax;
}
/*************************************************************
** Function name:       SetFocEnable
** Descriptions:        设置FOC使能
** Input parameters:    pFOC：FOC对象指针
**                      isEnable:是否使能
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void SetFocEnable(PFOC_Struct pFOC,uint8_t isEnable)
{
    pFOC->isEnable = isEnable;
}



