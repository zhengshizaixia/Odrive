#include "TIM1PWM.h"
#include "main.h"



#include "SEGGER_RTT_Conf.h"
#include "SEGGER_RTT.h"
#include "stdio.h"


extern TIM_HandleTypeDef htim1;

/*************************************************************
** Function name:       TIM1_Init
** Descriptions:        定时器1初始化
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void TIM1_Init(void)
{
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
    __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,0);
    __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,0);
    __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,0);

    SetTIM1Channel1HighLeaveTime_us(10);
    SetTIM1Channel2HighLeaveTime_us(50);
    SetTIM1Channel3HighLeaveTime_us(90);
}
/*************************************************************
** Function name:       SetTIM1Channel1HighLeaveTime_us
** Descriptions:        设置定时器1通道1高电平时间（中央对齐模式一）
** Input parameters:    time：高电平时间 单位us 范围 0-100
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void SetTIM1Channel1HighLeaveTime_us(float time)
{
    uint32_t ccr;
    if (time < 0) {
        time = 0;
    }
    if (time > 100) {
        time = 100;
    }
    ccr = 4200 - 42 * time;
    __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1, ccr);
}
/*************************************************************
** Function name:       SetTIM1Channel2HighLeaveTime_us
** Descriptions:        设置定时器1通道2高电平时间（中央对齐模式一）
** Input parameters:    time：高电平时间 单位us 范围 0-100
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void SetTIM1Channel2HighLeaveTime_us(float time)
{
    uint32_t ccr;
    if (time < 0) {
        time = 0;
    }
    if (time > 100) {
        time = 100;
    }
    ccr = 42 * time;
    __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2, ccr);
}
/*************************************************************
** Function name:       SetTIM1Channel3HighLeaveTime_us
** Descriptions:        设置定时器1通道3高电平时间（中央对齐模式一）
** Input parameters:    time：高电平时间 单位us 范围 0-100
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void SetTIM1Channel3HighLeaveTime_us(float time)
{
    uint32_t ccr;
    if (time < 0) {
        time = 0;
    }
    if (time > 100) {
        time = 100;
    }
    ccr = 42 * time;
    __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3, ccr);
}





