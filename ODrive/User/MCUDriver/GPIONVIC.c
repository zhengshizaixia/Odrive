#include "GPIONVIC.h"

#include "main.h"
#include "TIM3Encoder.h"




struct SEncoderCalibration_Struct
{
    /* data */
    int calibrationValue;  //校准值
    uint8_t calibrationFlag;     //第一次值
};

struct SEncoderCalibration_Struct gEncoderCal = {0};



/*************************************************************
** Function name:       GPIONVIC_Init
** Descriptions:        IO中断初始化
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void GPIONVIC_Init(void)
{
    gEncoderCal.calibrationValue = 0;
    gEncoderCal.calibrationFlag = 0;
}
/*************************************************************
** Function name:       GPIONVIC_DeInit
** Descriptions:        IO中断反初始化
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void GPIONVIC_DeInit(void)
{
    gEncoderCal.calibrationValue = 0;
    gEncoderCal.calibrationFlag = 0;
}

/*************************************************************
** Function name:       HAL_GPIO_EXTI_Callback
** Descriptions:        中断回调函数
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
		if(GPIO_Pin == Encoder_Z_Pin) {
            if (gEncoderCal.calibrationFlag == 0) {
                gEncoderCal.calibrationValue = GetTimer3EncoderCnt();
                gEncoderCal.calibrationFlag = 1;
            } else {
                SetTimer3EncoderCnt(gEncoderCal.calibrationFlag);
            }
            printf("1:%d\r\n",gEncoderCal.calibrationValue);
        }
}


