#include "ADC1.h"
#include "main.h"


extern ADC_HandleTypeDef hadc1;

//一介低通滤波系数
#define FILTER_KP 0.5f


struct SADC1_Struct{
	uint32_t adDmaValue[2];
	int adValue[2];
	int lastAdValue[2];
};
struct SADC1_Struct gADC1 = {0};



/*************************************************************
** Function name:       ADC1_Init
** Descriptions:        ADC1初始化
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void ADC1_Init(void)
{
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)gADC1.adDmaValue, 2);
}
/*************************************************************
** Function name:       GetADC1ChannelXValue
** Descriptions:        获取ADC通道 10 - 11的值
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
int32_t GetADC1ChannelXValue(uint8_t channel)
{
	int32_t value;
	value = (int32_t)(FILTER_KP * (float)gADC1.adValue[channel] + (1-FILTER_KP) * (float)gADC1.lastAdValue[channel]);
	gADC1.lastAdValue[channel] = value;
	return value;
}

/*************************************************************
** Function name:       GetMotor1ADCValue
** Descriptions:        Motor1读取一次ADC的值
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void ADCDMAStart(void)
{
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)gADC1.adDmaValue, 2);
}

/*************************************************************
** Function name:       ADCDMAIRQHandler
** Descriptions:        ADC1DMA读取中断服务函数
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void ADCDMAIRQHandler(void)
{
	gADC1.adValue[0] = ((int)gADC1.adDmaValue[0] - 2014)/10.0f;
	gADC1.adValue[1] = ((int)gADC1.adDmaValue[1] - 1996)/10.0f;
}


