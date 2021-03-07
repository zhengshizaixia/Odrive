#include "Svpwm.h"
#include "math.h"


#include "SEGGER_RTT_Conf.h"
#include "SEGGER_RTT.h"
#include "stdio.h"


#define SVPWM_SQRT3_2 0.866f
#define SVPWM_SQRT3 1.732f
/*************************************************************
** Function name:       SectorJudgment
** Descriptions:        扇区判断,利用uα和uβ来判断扇区
** Input parameters:    pSvpwm：结构体名字
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void SvpwmSectorJudgment(PSvpwm_Struct pSvpwm)
{
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t sector;

    pSvpwm->u1 = pSvpwm->uβ;
    // pSvpwm->u2 = pSvpwm->uα * sqrt(3) / 2 - pSvpwm->uβ / 2;
    // pSvpwm->u3 = -pSvpwm->uα * sqrt(3) / 2 - pSvpwm->uβ / 2;
	pSvpwm->u2 = pSvpwm->uα * SVPWM_SQRT3_2 - pSvpwm->uβ / 2;
	pSvpwm->u3 = -pSvpwm->uα * SVPWM_SQRT3_2 - pSvpwm->uβ / 2;


    if (pSvpwm->u1 > 0) {
        a = 1;
    } else {
        a = 0;
    }
    if (pSvpwm->u2 > 0) {
        b = 1;
    } else {
        b = 0;
    }
    if (pSvpwm->u3 > 0) {
        c = 1;
    } else {
        c = 0;
    }

   sector = 4*c + 2*b + a;
    switch (sector) {
        case 3:
            pSvpwm->sector = 1;
            break;
        case 1:
            pSvpwm->sector = 2;
            break;
        case 5:
            pSvpwm->sector = 3;
            break;
        case 4:
            pSvpwm->sector = 4;
            break;
        case 6:
            pSvpwm->sector = 5;
            break;
        case 2:
            pSvpwm->sector = 6;
            break;
    }
}
/*************************************************************
** Function name:       GetVectorDuration
** Descriptions:        获取矢量作用时长
** Input parameters:    pSvpwm:结构体指针
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void GetVectorDuration(PSvpwm_Struct pSvpwm)
{
    switch (pSvpwm->sector) {
        case 1:
            pSvpwm->t4 = SVPWM_SQRT3 * pSvpwm->ts / pSvpwm->udc * pSvpwm->u2;
            pSvpwm->t6 = SVPWM_SQRT3 * pSvpwm->ts / pSvpwm->udc * pSvpwm->u1;
            pSvpwm->t0 = pSvpwm->t7 = (pSvpwm->ts - pSvpwm->t4 - pSvpwm->t6) / 2;
            break;
        case 2:
            pSvpwm->t2 = -SVPWM_SQRT3 * pSvpwm->ts / pSvpwm->udc * pSvpwm->u2;
            pSvpwm->t6 = -SVPWM_SQRT3 * pSvpwm->ts / pSvpwm->udc * pSvpwm->u3;
            pSvpwm->t0 = pSvpwm->t7 = (pSvpwm->ts - pSvpwm->t2 - pSvpwm->t6) / 2;
            break;
        case 3:
            pSvpwm->t2 = SVPWM_SQRT3 * pSvpwm->ts / pSvpwm->udc * pSvpwm->u1;
            pSvpwm->t3 = SVPWM_SQRT3 * pSvpwm->ts / pSvpwm->udc * pSvpwm->u3;
            pSvpwm->t0 = pSvpwm->t7 = (pSvpwm->ts - pSvpwm->t2 - pSvpwm->t3) / 2;
            break;
        case 4:
            pSvpwm->t1 = -SVPWM_SQRT3 * pSvpwm->ts / pSvpwm->udc * pSvpwm->u1;
            pSvpwm->t3 = -SVPWM_SQRT3 * pSvpwm->ts / pSvpwm->udc * pSvpwm->u2;
            pSvpwm->t0 = pSvpwm->t7 = (pSvpwm->ts - pSvpwm->t1 - pSvpwm->t3) / 2;
            break;
        case 5:
            pSvpwm->t1 = SVPWM_SQRT3 * pSvpwm->ts / pSvpwm->udc * pSvpwm->u3;
            pSvpwm->t5 = SVPWM_SQRT3 * pSvpwm->ts / pSvpwm->udc * pSvpwm->u2;
            pSvpwm->t0 = pSvpwm->t7 = (pSvpwm->ts - pSvpwm->t1 - pSvpwm->t5) / 2;
            break;
        case 6:
            pSvpwm->t4 = -SVPWM_SQRT3 * pSvpwm->ts / pSvpwm->udc * pSvpwm->u3;
            pSvpwm->t5 = -SVPWM_SQRT3 * pSvpwm->ts / pSvpwm->udc * pSvpwm->u1;
            pSvpwm->t0 = pSvpwm->t7 = (pSvpwm->ts - pSvpwm->t4 - pSvpwm->t5) / 2;
            break;
        default:
            break;
    }
}
/*************************************************************
** Function name:       SvpwmGenerate
** Descriptions:        SVPWM生成周期函数
** Input parameters:    pSvpwm:结构体指针
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void SvpwmGenerate(PSvpwm_Struct pSvpwm)
{
    float ta;
    float tb;
    float tc;
    switch (pSvpwm->sector) {
        case 1:
            ta = pSvpwm->t4 + pSvpwm->t6 + pSvpwm->t7;
            tb = pSvpwm->t6 + pSvpwm->t7;
            tc = pSvpwm->t7;
            break;
        case 2:
            ta = pSvpwm->t6 + pSvpwm->t7;
            tb = pSvpwm->t2 + pSvpwm->t6 + pSvpwm->t7;
            tc = pSvpwm->t7;
            break;
        case 3:
            ta = pSvpwm->t7;
            tb = pSvpwm->t2 + pSvpwm->t3 + pSvpwm->t7;
            tc = pSvpwm->t3 + pSvpwm->t7;
            break;
        case 4:
            ta = pSvpwm->t7;
            tb = pSvpwm->t3 + pSvpwm->t7;
            tc = pSvpwm->t1 + pSvpwm->t3 + pSvpwm->t7;
            break;
        case 5:
            ta = pSvpwm->t5 + pSvpwm->t7;
            tb = pSvpwm->t7;
            tc = pSvpwm->t1 + pSvpwm->t5 + pSvpwm->t7;
            break;
        case 6:
            ta = pSvpwm->t4 + pSvpwm->t5 + pSvpwm->t7;
            tb = pSvpwm->t7;
            tc = pSvpwm->t5 + pSvpwm->t7;
            break;
    }
//    printf("1:%f\r\n",ta);
//    printf("2:%f\r\n",tb);
//    printf("3:%f\r\n",tc);
    pSvpwm->SetChannelAHighLeaveTime_us(ta);
    pSvpwm->SetChannelBHighLeaveTime_us(tb);
    pSvpwm->SetChannelCHighLeaveTime_us(tc);
}
/*************************************************************
** Function name:       SvpwmContorol
** Descriptions:        Svpwm控制
** Input parameters:    pSvpwm:结构体指针
**                      uα：阿尔法轴目标电压
**                      uβ：贝塔轴目标电压
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void SvpwmContorol(PSvpwm_Struct pSvpwm,float uα,float uβ)
{
    pSvpwm->uα = uα;
    pSvpwm->uβ = uβ;
    //1.扇区判断
    SvpwmSectorJudgment(pSvpwm);
    //1.计算矢量作用时长
    GetVectorDuration(pSvpwm);
    //1.SVPWM生成
    SvpwmGenerate(pSvpwm);
}
/*************************************************************
** Function name:       GetSVPWMSector
** Descriptions:        获取SVPWM扇区
** Input parameters:    None
** Output parameters:   None
** Returned value:      SVPWM扇区(1-6)
** Remarks:             None
*************************************************************/
uint8_t GetSVPWMSector(PSvpwm_Struct pSvpwm)
{
    return pSvpwm->sector;
}




