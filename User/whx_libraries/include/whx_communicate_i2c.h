#ifndef H_WHX_COMMUNICATE_I2C_
#define H_WHX_COMMUNICATE_I2C_

#include <stdio.h>
#include <stm32f1xx.h>
#include <stm32f1xx_hal.h>
#include "whx_peripherals.h"

extern I2C_HandleTypeDef V_config_i2c_1;
extern I2C_HandleTypeDef V_config_i2c_2;

/**
 * @description: I2C1配置
 */
#define PORT_I2C_1_SCL_GROUP PORT_EEPROM_SCL_GROUP
#define PORT_I2C_1_SCL_PIN PORT_EEPROM_SCL_PIN

#define PORT_I2C_1_SDA_GROUP PORT_EEPROM_SDA_GROUP
#define PORT_I2C_1_SDA_PIN PORT_EEPROM_SDA_PIN

#define FUNC_I2C_1_CLK_ENABLE(args) __HAL_RCC_I2C1_CLK_ENABLE(args)
#define FUNC_I2C_1_SCL_CLK_ENABLE(args) FUNC_EEPROM_SCL_CLK_ENABLE(args)
#define FUNC_I2C_1_SDA_CLK_ENABLE(args) FUNC_EEPROM_SDA_CLK_ENABLE(args)
#define FUNC_I2C_1_CLK_DISABLE(args) __HAL_RCC_I2C1_CLK_DISABLE(args)
#define FUNC_I2C_1_SCL_CLK_DISABLE(args) FUNC_EEPROM_SCL_CLK_DISABLE(args)
#define FUNC_I2C_1_SDA_CLK_DISABLE(args) FUNC_EEPROM_SDA_CLK_DISABLE(args)

#define FUNC_I2C_1_FORCE_RESET(args) __HAL_RCC_I2C1_FORCE_RESET(args)
#define FUNC_I2C_1_RELEASE_RESET(args) __HAL_RCC_I2C1_RELEASE_RESET(args)

#define CONFIG_I2C_1_ADDRESS_TARGETDEVICE PORT_EEPROM_ADDRESS_0     /*目标设备地址*/
#define CONFIG_I2C_1_TOTALSIZE_TARGETDEVICE STATUS_EEPROM_TOTALSIZE /*目标设备总容量(用于清空)*/
#define CONFIG_I2C_1_TIMEOUT 1000                                   /*超时时间*/
#define CONFIG_I2C_1_PAGESIZE STATUS_EEPROM_PAGESIZE                /*页大小*/

#define CONFIG_I2C_1_ADDRESSINGMODE I2C_ADDRESSINGMODE_7BIT  /*寻址模式7/10位*/
#define CONFIG_I2C_1_CLOCKSPEED 400000                       /*时钟频率<400kHZ*/
#define CONFIG_I2C_1_DUALADDRESSMODE I2C_DUALADDRESS_DISABLE /*是否选择双寻址模式*/
#define CONFIG_I2C_1_DUTYCYCLE I2C_DUTYCYCLE_2               /*指定I2C快速模式占空比*/
#define CONFIG_I2C_1_GENERALCALLMODE I2C_GENERALCALL_DISABLE /*是否选择一般呼叫模式*/
#define CONFIG_I2C_1_NOSTRETCHMODE I2C_NOSTRETCH_DISABLE     /*是否选择NO STRETCH模式*/
#define CONFIG_I2C_1_OWNADDRESSMODE_1 0x11                   /*自身地址分配1（和外设地址不同就行）*/
#define CONFIG_I2C_1_OWNADDRESSMODE_2 0                      /*自身地址分配2（和外设地址不同就行）*/

/*********************************I2C1配置************************************/

/**
 * @description: I2C功能
 */

void InitializeI2C1(void);
void InitializeI2C1ForGPIO(void);
void InitializeI2C1ForProtocol(void);
void FuncI2C1WaitForReady(void);
void FuncI2C1Transmit(uint8_t *m_buffer_ptr, uint16_t m_num_to_write);
void FuncI2C1Receive(uint8_t *m_buffer_ptr, uint16_t m_num_to_read);
/**
 * @description:指定位置写入
 * @param {uint8_t} *m_buffer_ptr 准备发送的缓冲区指针
 * @param {uint8_t} m_target_mem_ptr 目标内部存储器地址
 * @param {uint8_t} m_num_to_write  要写入的字节数
 * @return {*}
 */
void FuncI2C1WriteForMemory(uint8_t *m_buffer_ptr, uint8_t m_target_mem_ptr, uint16_t m_num_to_write);
/**
 * @description:指定位置读取
 * @param {uint8_t} *m_buffer_ptr 准备接受的缓冲区指针
 * @param {uint8_t} m_target_mem_ptr 目标内部存储器地址
 * @param {uint8_t} m_num_to_read  要读取的字节数
 * @return {*}
 */
void FuncI2C1ReadForMemory(uint8_t *m_buffer_ptr, uint8_t m_target_mem_ptr, uint16_t m_num_to_read);
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *m_handle);
/*********************************I2C功能************************************/

#endif
