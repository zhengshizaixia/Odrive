#include "SPI3.h"

#include "main.h"
extern SPI_HandleTypeDef hspi3;




/*************************************************************
** Function name:       SetSPI3CSIsEnable
** Descriptions:        设置SPI3片选引脚使能
** Input parameters:    isEnbale： 0：使能 1：失能
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void SetSPI3CSIsEnable(uint8_t isEnable)
{
    HAL_GPIO_WritePin(DRV8301_CS_GPIO_Port,DRV8301_CS_Pin, (GPIO_PinState)isEnable);
}
/*************************************************************
** Function name:       SPI3TransmitData
** Descriptions:        SPI3发送数据
** Input parameters:    data: 要传输的数据
** Output parameters:   None
** Returned value:      None
*************************************************************/
void SPI3TransmitData(uint16_t data)
{
    uint16_t txData;
    txData = data;
    HAL_SPI_Transmit(&hspi3,(uint8_t *)(&txData),1,1000);
}
/*************************************************************
** Function name:       SPI3ReceiveData
** Descriptions:        SPI3读取数据
** Input parameters:    None
** Output parameters:   要读取的数据
** Returned value:      None
*************************************************************/
uint16_t SPI3ReceiveData(void)
{
    uint16_t rxData;
    HAL_SPI_Receive(&hspi3,(uint8_t *)(&rxData),1,1000);
    return rxData;
}


/*************************************************************
** Function name:       SPI3TransmitReceiveData
** Descriptions:        SPI3读取数据
** Input parameters:    data: 要传输的数据
** Output parameters:   要读取的数据
** Returned value:      None
*************************************************************/
uint16_t SPI3TransmitReceiveData(uint16_t data)
{
    uint16_t txData;
	uint16_t rxData;
    HAL_SPI_TransmitReceive(&hspi3,(uint8_t *)(&txData),(uint8_t *)(&rxData),1,1000);
    return rxData;
}