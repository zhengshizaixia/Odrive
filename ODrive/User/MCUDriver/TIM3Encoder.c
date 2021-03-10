#include "TIM3Encoder.h"
#include "SEGGER_RTT_Conf.h"
#include "SEGGER_RTT.h"
#include "main.h"

#define CNTZERO 10000
#define ENCODERPLUSE 4000


extern TIM_HandleTypeDef htim3;

struct STimEnc_Struct {
    int32_t Tim3Cnt;        //编码器脉冲数 0-360°
    float angle;			//编码器角度 0-360°
};
typedef struct STimEnc_Struct TimEnc_Struct; /* TimEnc 类型 */
typedef TimEnc_Struct *PTimEnc_Struct;      /* PTimEnc 指针类型 */

TimEnc_Struct gSTTimerEncoder = {
    .Tim3Cnt = 0,
    .angle = 0,
};

/*************************************************************
** Function name:       TimerEncoderInit
** Descriptions:        初始化定时器3
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
*************************************************************/
void TimerEncoderInit(void)
{
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_1|TIM_CHANNEL_2);
    __HAL_TIM_SET_COUNTER(&htim3,CNTZERO);
    gSTTimerEncoder.angle = 0.0;
    gSTTimerEncoder.Tim3Cnt = 0;
}
/*************************************************************
** Function name:       TimerEncoderInit
** Descriptions:        复位定时器3
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
*************************************************************/
void TimerEncoderReset(void)
{
    __HAL_TIM_SET_COUNTER(&htim3,CNTZERO);
    gSTTimerEncoder.angle = 0.0;
    gSTTimerEncoder.Tim3Cnt = 0;
}
/*************************************************************
** Function name:       GetTimer3EncoderCnt
** Descriptions:        获取定时器3编码器模式CNT的值
** Input parameters:    None
** Output parameters:   None
** Returned value:      Timer3->CNT的值
*************************************************************/
int32_t GetTimer3EncoderCnt(void)
{
    gSTTimerEncoder.Tim3Cnt += __HAL_TIM_GET_COUNTER(&htim3) - CNTZERO;

    gSTTimerEncoder.Tim3Cnt = gSTTimerEncoder.Tim3Cnt % ENCODERPLUSE;
    __HAL_TIM_GET_COUNTER(&htim3) = CNTZERO;

    return gSTTimerEncoder.Tim3Cnt;
}
/*************************************************************
** Function name:       GetTimerEncoderAngle
** Descriptions:        获取编码器角度
** Input parameters:    None
** Output parameters:   None
** Returned value:      编码器角度
*************************************************************/
float GetTimerEncoderAngle(void)
{
    gSTTimerEncoder.angle = (float)GetTimer3EncoderCnt() / (float)ENCODERPLUSE * 360.0f;

    if (gSTTimerEncoder.angle < 0) {
        gSTTimerEncoder.angle = gSTTimerEncoder.angle + 360.0f;
    }
    return gSTTimerEncoder.angle;
}

