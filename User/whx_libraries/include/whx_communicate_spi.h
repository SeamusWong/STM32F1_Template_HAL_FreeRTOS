#ifndef H_WHX_COMMUNICATE_SPI_
#define H_WHX_COMMUNICATE_SPI_

#include <stdio.h>
#include <stm32f1xx.h>
#include <stm32f1xx_hal.h>
#include "whx_peripherals.h"

extern SPI_HandleTypeDef V_config_spi_1;

/**
 * @description: SPI端口配置
 */
#define PORT_SPI_1_SCL_GROUP PORT_FLASH_SCL_GROUP
#define PORT_SPI_1_SCL_PIN PORT_FLASH_SCL_PIN

#define PORT_SPI_1_MISO_GROUP PORT_FLASH_MISO_GROUP
#define PORT_SPI_1_MISO_PIN PORT_FLASH_MISO_PIN

#define PORT_SPI_1_MOSI_GROUP PORT_FLASH_MOSI_GROUP
#define PORT_SPI_1_MOSI_PIN PORT_FLASH_MOSI_PIN

#define PORT_SPI_1_NSS_1_GROUP PORT_FLASH_NSS_GROUP /*片选引脚，有几个外设从机就应该有几个NSS，也叫CS*/
#define PORT_SPI_1_NSS_1_PIN PORT_FLASH_NSS_PIN

#define FUNC_SPI_1_CLK_ENABLE(args) __HAL_RCC_SPI1_CLK_ENABLE(args)
#define FUNC_SPI_1_SCL_CLK_ENABLE(args) FUNC_FLASH_SCL_CLK_ENABLE(args)
#define FUNC_SPI_1_MISO_CLK_ENABLE(args) FUNC_FLASH_MISO_CLK_ENABLE(args)
#define FUNC_SPI_1_MOSI_CLK_ENABLE(args) FUNC_FLASH_MOSI_CLK_ENABLE(args)
#define FUNC_SPI_1_NSS_1_CLK_ENABLE(args) FUNC_FLASH_NSS_CLK_ENABLE(args)
#define FUNC_SPI_1_CLK_DISABLE(args) __HAL_RCC_SPI1_CLK_DISABLE(args)
#define FUNC_SPI_1_SCL_CLK_DISABLE(args) FUNC_FLASH_SCL_CLK_DISABLE(args)
#define FUNC_SPI_1_MISO_CLK_DISABLE(args) FUNC_FLASH_MISO_CLK_DISABLE(args)
#define FUNC_SPI_1_MOSI_CLK_DISABLE(args) FUNC_FLASH_MOSI_CLK_DISABLE(args)
#define FUNC_SPI_1_NSS_1_CLK_DISABLE(args) FUNC_FLASH_NSS_CLK_DISABLE(args)

#define FUNC_SPI_1_FORCE_RESET(args) __HAL_RCC_SPI1_FORCE_RESET(args)
#define FUNC_SPI_1_RELEASE_RESET(args) __HAL_RCC_SPI1_RELEASE_RESET(args)

#define CONFIG_SPI_1_TIMEOUT CONFIG_FLASH_TIMEOUT /*超时时间*/

#define CONFIG_SPI_1_BAUDRATEPRESCALER SPI_BAUDRATEPRESCALER_4 /*波特率预分频*/
#define CONFIG_SPI_1_CLKPHASE SPI_PHASE_1EDGE                  /*时钟相位奇/偶边沿采样*/
#define CONFIG_SPI_1_CLKPOLARITY SPI_POLARITY_LOW              /*时钟极性高/低电平*/
#define CONFIG_SPI_1_CRCCALCULATION SPI_CRCCALCULATION_DISABLE /*是否启用CRC计算*/
#define CONFIG_SPI_1_CRCPOLYNOMIAL 0                           /*CRC校验的表达式参数*/
#define CONFIG_SPI_1_DATASIZE SPI_DATASIZE_8BIT                /*数据帧长度8/16位*/
#define CONFIG_SPI_1_DIRECTION SPI_DIRECTION_2LINES            /*双向模式状态*/
#define CONFIG_SPI_1_FIRSTBIT SPI_FIRSTBIT_MSB                 /*起始位是MSB/LSB*/
#define CONFIG_SPI_1_NSS SPI_NSS_SOFT                          /*NSS引脚由硬件/软件指定*/
#define CONFIG_SPI_1_TIMODE SPI_TIMODE_DISABLE                 /*是否启动TI模式*/
#define CONFIG_SPI_1_MODE SPI_MODE_MASTER                      /*操作模式主机/从机*/

/*********************************SPI端口配置************************************/

/**
 * @description: SPI功能
 */
void InitializeSPI1(void);
void InitializeSPI1ForGPIO(void);
void InitializeSPI1ForProtocol(void);
/**
 * @description: SPI1指定位置发送
 * @param {uint8_t} *m_buffer_ptr 准备发送的缓冲区指针
 * @param {uint16_t} m_num_to_write 要写入的字节数
 * @return {*}
 */
void FuncSPI1NSSReady(void);
void FuncSPI1NSSQuit(void);
void FuncSPI1Transmit(uint8_t *m_buffer_ptr, uint16_t m_num_to_write);
void FuncSPI1Receive(uint8_t *m_buffer_ptr, uint16_t m_num_to_read);
void FuncSPI1WaitForReady(void);
void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *m_handle);
/*********************************SPI功能************************************/
#endif
