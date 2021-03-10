#include "MotorGPIO.h"
#include "main.h"

/*************************************************************
** Function name:       SetMotorEnable
** Descriptions:        设置电机使能标志
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void SetMotorEnable(uint8_t isEnable)
{
    HAL_GPIO_WritePin(Motor_Enable_GPIO_Port,Motor_Enable_Pin, (GPIO_PinState)isEnable);
}



