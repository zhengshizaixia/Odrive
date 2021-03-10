#include "Timer.h"
#include "main.h"
uint32_t gMS_TimeCNT;

//us must < 1000!!!
void rt_hw_us_delay(uint32_t us)
{
	uint32_t start, now, delta, reload, us_tick;
	start = SysTick->VAL;
	reload = SysTick->LOAD;
	us_tick = SystemCoreClock / 1000000UL;
	do {
		now = SysTick->VAL;
		delta = start > now ? start - now : reload + start - now;
	} while(delta < us_tick * us);
}
