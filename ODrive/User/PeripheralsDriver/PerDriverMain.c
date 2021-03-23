#include "PerDriverMain.h"
#include "main.h"

#include "SvpwmConfig.h"
#include "Timer.h"
#include "FOCConfig.h"
#include "DRV8301Config.h"

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
	HAL_Delay(2000);
	//DRV8301Config_Init();
	FOCConfig_Init();
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
float speed = 0.4;
void PerDriverMain_Loop(void)
{
	
	//MotorSvpwmConfigTest();
	RUN_BY_LIMIT_BLOCK(2,
		FOCConfigPrintf();
	)
	
	RUN_BY_LIMIT_BLOCK(2000,
		if (a == 0) {
			a = 1;
			SetTarIDIQ(0,10);
		} else if (a == 1){
			a = 2;
			SetTarIDIQ(0,5);
		} else if (a == 2){
			a = 3;
			SetTarIDIQ(0,0);
		} else if (a == 3){
			a = 4;
			SetTarIDIQ(0,-5);
		} else if (a == 4){
			a = 5;
			SetTarIDIQ(0,-10);
		} else if (a == 5){
			a = 6;
			SetTarIDIQ(0,-5);
		} else if (a == 6){
			a = 7;
			SetTarIDIQ(0,0);
		} else if (a == 7){
			a = 0;
			SetTarIDIQ(0,5);
		}
		
	)
//	
//	RUN_BY_LIMIT_BLOCK(4000,
//		SetTarIDIQ(-0.5,0);
//	)
	
//	for (uint16_t i =0; i<200; i++) {
//		speed += 0.01;
//		SetTarIDIQ(0,speed);
//		HAL_Delay(50);
//	}
//	
//	for (uint16_t i =0; i<200; i++) {
//		speed -= 0.01;
//		SetTarIDIQ(0,speed);
//		HAL_Delay(50);
//	}
	
	rt_hw_us_delay(1);
}


