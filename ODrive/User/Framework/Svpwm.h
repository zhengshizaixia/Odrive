#ifndef Svpwm_h
#define Svpwm_h

#include "stdint.h"





struct SSvpwm_Struct
{
    float uα;		//阿尔法轴目标电压 	(最大值为母线电压 * sqrt(3) / 3)
    float uβ;		//贝塔轴目标电压   	(最大值为母线电压 * sqrt(3) / 3)
    float u1;		//用于扇区判断
    float u2;		//用于扇区判断
    float u3;		//用于扇区判断
    float t0;		//0矢量作用时长
    float t1;		//1矢量作用时长
    float t2;		//2矢量作用时长
    float t3;		//3矢量作用时长
    float t4;		//4矢量作用时长
    float t5;		//5矢量作用时长
    float t6;		//6矢量作用时长
    float t7;		//7矢量作用时长
    float ts;		//SVPWM周期
    float udc;		//母线电压
    uint8_t sector;//扇区索引
    void (*SetChannelAHighLeaveTime_us)(float time); //一个SVPWM周期内A相绕组高电平时间(中央对齐方式)
    void (*SetChannelBHighLeaveTime_us)(float time); //一个SVPWM周期内B相绕组高电平时间(中央对齐方式)
    void (*SetChannelCHighLeaveTime_us)(float time); //一个SVPWM周期内C相绕组高电平时间(中央对齐方式)
};
typedef struct SSvpwm_Struct Svpwm_Struct;
typedef Svpwm_Struct *PSvpwm_Struct;


/*************************************************************
** Function name:       SVPWM_EXPORT
** Descriptions:        初始化一个SVPMW对象
** Input parameters:    x:对象名字
**                      xTs：SVPWM波形周期 单位us 建议 50
**                      xSetChannelAHighLeaveTime_us：设置A相高电平时间
**                      xSetChannelBHighLeaveTime_us：设置B相高电平时间
**                      xSetChannelCHighLeaveTime_us：设置C相高电平时间
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
#define SVPWM_EXPORT(x,xTs,xudc,xSetChannelAHighLeaveTime_us,xSetChannelBHighLeaveTime_us,xSetChannelCHighLeaveTime_us)     \
Svpwm_Struct x = {                      \
    .uα = 0,                            \
    .uβ = 0,                            \
    .u1 = 0,                            \
    .u2 = 0,                            \
    .u3 = 0,                            \
    .t0 = 0,                            \
    .t1 = 0,                            \
    .t2 = 0,                            \
    .t3 = 0,                            \
    .t4 = 0,                            \
    .t5 = 0,                            \
    .t6 = 0,                            \
    .t7 = 0,                            \
    .ts = xTs,                          \
    .udc = xudc,                        \
    .sector = 0,                        \
    .SetChannelAHighLeaveTime_us = xSetChannelAHighLeaveTime_us,            \
    .SetChannelBHighLeaveTime_us = xSetChannelBHighLeaveTime_us,            \
    .SetChannelCHighLeaveTime_us = xSetChannelCHighLeaveTime_us,            \
};



void SvpwmContorol(PSvpwm_Struct pSvpwm,float uα,float uβ);
uint8_t GetSVPWMSector(PSvpwm_Struct pSvpwm);
#endif /* Svpwm_h */
