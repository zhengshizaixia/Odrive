#include "DRV8301.h"
#include "main.h"

#include "stdio.h"
#include "SEGGER_RTT.h"
#include "SEGGER_RTT_Conf.h"

#define STATUS_REG_1 0x00
#define STATUS_REG_2 0x01
#define CONTROL_REG_1 0x02
#define CONTROL_REG_2 0x03





void DRV8301SetGain(PDRV8301_Struct gDRV8301)
{
    gDRV8301->SetCSIsEnable(0);
	HAL_Delay(2);
	printf("GAIN:%d\r\n",gDRV8301->WriteReadData(0x180C));
	printf("GAIN:%d\r\n",gDRV8301->WriteReadData(0x1800));
	gDRV8301->SetCSIsEnable(1);
}






