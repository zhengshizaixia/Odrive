#include "PerDriverMain.h"
#include "main.h"

#include "SvpwmConfig.h"
#include "Timer.h"
#include "FOCConfig.h"

/*************************************************************
** Function name:      PerDriverMain_Init
** Descriptions:       外设初始化
** Input parameters:   none
** Output parameters:  none
** Returned value:     none
** Created by:         none
** Created date:       none
*************************************************************/
void PerDriverMain_Init(void)
{


}

/*************************************************************
** Function name:      PerDriverMain_Loop
** Descriptions:       外设循环
** Input parameters:   none
** Output parameters:  none
** Returned value:     none
** Created by:         none
** Created date:       none
*************************************************************/
int a = 0;
float speed = 0.2;
void PerDriverMain_Loop(void)
{
	
	//MotorSvpwmConfigTest();
	RUN_BY_LIMIT_BLOCK(5,
		FOCConfigPrintf();
	)
	
	for (uint16_t i =0; i<400; i++) {
		speed += 0.01;
		SetTarIDIQ(0,speed);
		HAL_Delay(50);
	}
	
	for (uint16_t i =0; i<400; i++) {
		speed -= 0.01;
		SetTarIDIQ(0,speed);
		HAL_Delay(50);
	}
	
	
	
//	RUN_BY_LIMIT_BLOCK(3000,
//	if (a == 1) {
//		SetTarIDIQ(0,2.0);
//		a = 0;
//	} else {
//		SetTarIDIQ(0,1.0);
//		a = 1;
//	})
	
	
	rt_hw_us_delay(1);
}


