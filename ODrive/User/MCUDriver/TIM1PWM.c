#include "TIM1PWM.h"
#include "main.h"

#include "ADC1.h"


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

	HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_1);
	HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_2);
	HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_3);

    SetTIM1Channel1HighLeaveTime_us(0);
    SetTIM1Channel2HighLeaveTime_us(0);
    SetTIM1Channel3HighLeaveTime_us(0);
	SetTIM1Channel4HighLeaveTime_us(0);

    Timer1Channel4ITEnable(0);
}
/*************************************************************
** Function name:       Timer1ITEnable
** Descriptions:        定时一通道4比较中断使能
** Input parameters:    isEnable：1：使能 0：失能
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void Timer1Channel4ITEnable(uint8_t isEnable)
{
    if(isEnable == 1) {
        HAL_TIM_PWM_Start_IT(&htim1,TIM_CHANNEL_4);
	    HAL_TIM_Base_Start_IT(&htim1);
    } else {
        HAL_TIM_PWM_Stop_IT(&htim1,TIM_CHANNEL_4);
	    HAL_TIM_Base_Stop_IT(&htim1);
    }
}

/*************************************************************
** Function name:       SetTIM1Channel1HighLeaveTime_us
** Descriptions:        设置定时器1通道1高电平时间（中央对齐模式二）
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
    ccr = 42 * time;
    __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1, ccr);
}
/*************************************************************
** Function name:       SetTIM1Channel2HighLeaveTime_us
** Descriptions:        设置定时器1通道2高电平时间（中央对齐模式二）
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
** Descriptions:        设置定时器1通道3高电平时间（中央对齐模式二）
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

/*************************************************************
** Function name:       SetTIM1Channel4HighLeaveTime_us
** Descriptions:        设置定时器1通道4高电平时间（中央对齐模式二）
** Input parameters:    time：高电平时间 单位us 范围 0-100
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void SetTIM1Channel4HighLeaveTime_us(float time)
{
    uint32_t ccr;
    if (time < 0) {
        time = 0;
    }
    if (time > 100) {
        time = 100;
    }
    ccr = 42 * time;
    __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4, ccr);
}



