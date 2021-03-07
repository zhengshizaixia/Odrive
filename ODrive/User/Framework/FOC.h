#ifndef FOC_h
#define FOC_h

#include "stdint.h"


extern volatile uint32_t gFoc_TimeCNT;

/*
增量式PI调节
*/
struct PI_Struct
{
    /* data */
    float kp;
    float ki;
    float kd;

    float pre;
    float tar;
    float bias;
    float lastBias;
    float out;
    float outMax;
};


/*
FOC结构体
*/
struct SFOC_Struct
{
    /* data */
    uint32_t startTime;
    float cycle;

    uint8_t isEnable; //电机使能
    uint8_t polePairs; //极对数

    float tariq;        //目标电流
    float tarid;        //目标电流
    float angle;        //角度
    float radian;       //弧度

    float ia;           //a 相实际电流
    float ib;           //b 相实际电流
	float ic;           //b 相实际电流
    float iα;           //clarke变换后 * 2/3后 Iα
    float iβ;           //clarke变换后 * 2/3后 Iβ
    float iq;           //park变换后 Iq
    float id;           //park变换后 Id

    float iαSVPWM;      //park反变换后 后 Iα
    float iβSVPWM;      //park反变换后 后 Iβ

    struct PI_Struct idPID;
    struct PI_Struct iqPID;
    void (*SetEnable)(uint8_t isEnable);
    float (*GetEncoderAngle)(void);
    uint8_t (*GetSVPWMSector)(void);
    void (*GetPreCurrent)(float *ua,float *ub,float *uc);
    void (*SvpwmGenerate)(float uα,float uβ);
};
typedef struct SFOC_Struct FOC_Struct;
typedef FOC_Struct *PFOC_Struct;

/*************************************************************
** Function name:       FOC_EXPORT
** Descriptions:        声明一个FOC对象
**                      xCycle：FOC控制周期 单位S 建议 0.01
**                      xGetPreCurrent：获取相电流值，注意检测时间窗口
**                      xSvpwmGenerate：SVPWM生成函数。配合SVPWM.h
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
#define FOC_EXPORT(x,xCycle,xpolePairs,xSetEnable,xGetEncoderAngle,xGetSVPWMSector,xGetPreCurrent,xSvpwmGenerate)    \
FOC_Struct x = {                            \
    .startTime = 0,                         \
    .cycle = xCycle,                        \
    .isEnable = 0,                          \
    .polePairs = xpolePairs,                \
    .tarid = 0.0,                           \
    .tariq = 0.0,                           \
    .angle = 0.0,                           \
    .radian = 0.0,                          \
    .ia = 0.0,                              \
    .ib = 0.0,                              \
    .ic = 0.0,                              \
    .iα = 0.0,                              \
    .iβ = 0.0,                               \
    .iq = 0.0,                              \
    .id = 0.0,                              \
    .iαSVPWM = 0.0,                         \
    .iβSVPWM = 0.0,                         \
    .idPID = {0},                           \
    .iqPID = {0},                           \
    .SetEnable = xSetEnable,          \
    .GetEncoderAngle = xGetEncoderAngle,    \
    .GetSVPWMSector = xGetSVPWMSector,      \
    .GetPreCurrent = xGetPreCurrent,        \
    .SvpwmGenerate = xSvpwmGenerate,        \
};




/*************************************************************
** Function name:       WS2812_TIMEBASE
** Descriptions:        时基,放在周期为1ms的函数里面执行
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
*************************************************************/
#define FOC_TIMEBASE(ms)                \
        gFoc_TimeCNT+= ms

/*************************************************************
** Function name:       WS2812_GETTIME
** Descriptions:        获取起始时间
** Input parameters:    None
** Output parameters:   None
** Returned value:      (uint32_t)起始时间
*************************************************************/
#define FOC_GETTIME(void)                        \
    gFoc_TimeCNT

/*************************************************************
** Function name:       WS2812_TIMEOUT
** Descriptions:        检查超时
** Input parameters:    timeOut：(uint32_t)超时时间
**                      startTime:(uint32_t)开始的时间
** Output parameters:   None
** Returned value:      false,未超时，true，超时
*************************************************************/
#define FOC_TIMEOUT(timeOut,startTime)                \
    ((gFoc_TimeCNT - startTime) >= timeOut ? 1 : 0)





void FOCCycle(PFOC_Struct pFOC);
void SetCurrentPIDTar(PFOC_Struct pFOC,float tarid,float tariq);
void SetCurrentPIDParams(PFOC_Struct pFOC,float kp,float ki,float kd,float outMax);
void SetFocEnable(PFOC_Struct pFOC,uint8_t isEnable);




#endif /* FOC_h */
