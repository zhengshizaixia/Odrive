#include "DRV8301Config.h"

#include "DRV8301.h"
#include "SPI3.h"
#include "MotorGPIO.h"
#include "main.h"

DRV8301_EXPORT(gDRV8301,SetSPI3CSIsEnable,SPI3ReceiveData,SPI3TransmitData,SPI3TransmitReceiveData)




void DRV8301Config_Init(void)
{
    //设置增益80V/V
	SetMotorEnable(0);
	HAL_Delay(30);
	SetMotorEnable(1);
	HAL_Delay(30);
    DRV8301SetGain(&gDRV8301);
	//SetMotorEnable(0);
}



