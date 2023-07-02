#ifndef H_WHX_COMMUNICATE_
#define H_WHX_COMMUNICATE_

#include "whx_libraries_all.h"
#include "whx_peripherals.h"
#include "whx_on_chip.h"

/**
 * @description: USART端口配置
 */
#define PORT_USART1_RX_GROUP GPIOA
#define PORT_USART1_RX_PIN GPIO_PIN_10

#define PORT_USART1_TX_GROUP GPIOA
#define PORT_USART1_TX_PIN GPIO_PIN_9

#define CONFIG_USART1_INSTANCE USART1                  /*寄存器地址*/
#define CONFIG_USART1_MODE USART_MODE_TX_RX            /*工作模式*/
#define CONFIG_USART1_BAUDRATE 115200                  /*波特率*/
#define CONFIG_USART1_WORDLENGTH USART_WORDLENGTH_8B   /*字长*/
#define CONFIG_USART1_STOPBITS USART_STOPBITS_1        /*停止位*/
#define CONFIG_USART1_PARITY USART_PARITY_ODD          /*校验状态*/
#define CONFIG_USART1_HWCONTROL UART_HWCONTROL_NONE    /*硬件流控模式状态*/
#define CONFIG_USART1_CLKLASTBIT USART_LASTBIT_DISABLE /*是否使能接收器采样最后一位数据*/
#define CONFIG_USART1_CLKPHASE NULL       /*数据采样在上升/下降沿进行*/
#define CONFIG_USART1_CLKPOLARITY NULL   /*使用正/负极性的时钟信号*/
#define CONFIG_USART1_TIMEOUT 1000U                    /*超时时间*/

#define FUNC_USART1_PIN_CLK_ENABLE(args) \
    do                                   \
    {                                    \
        __HAL_RCC_GPIOA_CLK_ENABLE();    \
    } while (0U);
#define FUNC_USART1_PIN_CLK_DISABLE(args) \
    do                                    \
    {                                     \
        __HAL_RCC_GPIOA_CLK_DISABLE();    \
    } while (0U);

#define FUNC_USART_1_CLK_ENABLE() __HAL_RCC_USART1_CLK_ENABLE()
#define FUNC_USART_1_CLK_DISABLE() __HAL_RCC_USART1_CLK_DISABLE()
/*********************************USART端口配置************************************/

/**
 * @description: USART功能
 */
extern UART_HandleTypeDef V_config_usart1;

void InitializeUSART1(void);
void InitializeUSART1ForPin(void);
void InitializeUSART1ForProtocol(void);
int32_t fputc(int32_t m_char, FILE *m_stream);
int32_t fgetc(FILE *m_stream);
void HAL_UART_ErrorCallback(UART_HandleTypeDef *m_handle);
/*********************************USART功能************************************/

/**
 * @description: I2C1配置
 */
#define PORT_IIC1_SCL_GROUP GPIOB
#define PORT_IIC1_SCL_PIN GPIO_PIN_6

#define PORT_IIC1_SDA_GROUP GPIOB
#define PORT_IIC1_SDA_PIN GPIO_PIN_7

#define FUNC_IIC1_PIN_CLK_ENABLE(args) \
    do                                  \
    {                                   \
        __HAL_RCC_GPIOB_CLK_ENABLE();   \
    } while (0U);
#define FUNC_IIC1_PIN_CLK_DISABLE(args) \
    do                                   \
    {                                    \
        __HAL_RCC_GPIOB_CLK_DISABLE();   \
    } while (0U);

#define FUNC_IIC1_CLK_ENABLE(args) __HAL_RCC_I2C1_CLK_ENABLE(args)
#define FUNC_IIC1_CLK_DISABLE(args) __HAL_RCC_I2C1_CLK_DISABLE(args)

#define FUNC_IIC1_FORCE_RESET(args) __HAL_RCC_I2C1_FORCE_RESET(args)
#define FUNC_IIC1_RELEASE_RESET(args) __HAL_RCC_I2C1_RELEASE_RESET(args)

#define CONFIG_IIC1_TIMEOUT 1000                                   /*超时时间*/

#define CONFIG_IIC1_ADDRESSINGMODE I2C_ADDRESSINGMODE_7BIT  /*寻址模式7/10位*/
#define CONFIG_IIC1_CLOCKSPEED 400000                       /*时钟频率<400kHZ*/
#define CONFIG_IIC1_DUALADDRESSMODE I2C_DUALADDRESS_DISABLE /*是否选择双寻址模式*/
#define CONFIG_IIC1_DUTYCYCLE I2C_DUTYCYCLE_2               /*指定I2C快速模式占空比*/
#define CONFIG_IIC1_GENERALCALLMODE I2C_GENERALCALL_DISABLE /*是否选择一般呼叫模式*/
#define CONFIG_IIC1_NOSTRETCHMODE I2C_NOSTRETCH_DISABLE     /*是否选择NO STRETCH模式*/
#define CONFIG_IIC1_OWNADDRESSMODE_1 0x11                   /*自身地址分配1（和外设地址不同就行）*/
#define CONFIG_IIC1_OWNADDRESSMODE_2 0                      /*自身地址分配2（和外设地址不同就行）*/
/*********************************I2C1配置************************************/

/**
 * @description: I2C功能
 */
extern I2C_HandleTypeDef V_config_iic1;

void InitializeIIC1(void);
void InitializeIIC1ForPin(void);
void InitializeIIC1ForProtocol(void);
void FuncIIC1WaitForReady(uint16_t m_target_address);
void FuncIIC1Transmit(uint16_t m_target_address,uint8_t *m_buffer_ptr, uint16_t m_num_to_write);
void FuncIIC1Receive(uint16_t m_target_address,uint8_t *m_buffer_ptr, uint16_t m_num_to_read);
/**
 * @description:指定位置写入
 * @param {uint8_t} *m_buffer_ptr 准备发送的缓冲区指针
 * @param {uint8_t} m_target_mem_ptr 目标内部存储器地址
 * @param {uint8_t} m_num_to_write  要写入的字节数
 * @return {*}
 */
void FuncIIC1WriteForMemory(uint16_t m_target_address,uint16_t m_target_pagesize,uint8_t *m_buffer_ptr, uint8_t m_target_mem_ptr, uint16_t m_num_to_write);
/**
 * @description:指定位置读取
 * @param {uint8_t} *m_buffer_ptr 准备接受的缓冲区指针
 * @param {uint8_t} m_target_mem_ptr 目标内部存储器地址
 * @param {uint8_t} m_num_to_read  要读取的字节数
 * @return {*}
 */
void FuncIIC1ReadForMemory(uint16_t m_target_address,uint8_t *m_buffer_ptr, uint8_t m_target_mem_ptr, uint16_t m_num_to_read);
/*********************************I2C功能************************************/

/**
 * @description: SPI端口配置
 */
#define PORT_SPI1_SCL_GROUP GPIOA
#define PORT_SPI1_SCL_PIN GPIO_PIN_5

#define PORT_SPI1_MISO_GROUP GPIOA
#define PORT_SPI1_MISO_PIN GPIO_PIN_6

#define PORT_SPI1_MOSI_GROUP GPIOA
#define PORT_SPI1_MOSI_PIN GPIO_PIN_7

#define FUNC_SPI1_PIN_CLK_ENABLE(args) \
    do                                 \
    {                                  \
        __HAL_RCC_GPIOA_CLK_ENABLE();  \
    } while (0U);
#define FUNC_SPI1_PIN_CLK_DISABLE(args) \
    do                                  \
    {                                   \
        __HAL_RCC_GPIOA_CLK_DISABLE();  \
    } while (0U);

#define FUNC_SPI1_CLK_ENABLE(args) __HAL_RCC_SPI1_CLK_ENABLE(args)
#define FUNC_SPI1_CLK_DISABLE(args) __HAL_RCC_SPI1_CLK_DISABLE(args)

#define FUNC_SPI1_FORCE_RESET(args) __HAL_RCC_SPI1_FORCE_RESET(args)
#define FUNC_SPI1_RELEASE_RESET(args) __HAL_RCC_SPI1_RELEASE_RESET(args)

#define CONFIG_SPI1_TIMEOUT 1000 /*超时时间*/

#define CONFIG_SPI1_BAUDRATEPRESCALER SPI_BAUDRATEPRESCALER_4 /*波特率预分频*/
#define CONFIG_SPI1_CLKPHASE SPI_PHASE_1EDGE                  /*时钟相位奇/偶边沿采样*/
#define CONFIG_SPI1_CLKPOLARITY SPI_POLARITY_LOW              /*时钟极性高/低电平*/
#define CONFIG_SPI1_CRCCALCULATION SPI_CRCCALCULATION_DISABLE /*是否启用CRC计算*/
#define CONFIG_SPI1_CRCPOLYNOMIAL 0                           /*CRC校验的表达式参数*/
#define CONFIG_SPI1_DATASIZE SPI_DATASIZE_8BIT                /*数据帧长度8/16位*/
#define CONFIG_SPI1_DIRECTION SPI_DIRECTION_2LINES            /*双向模式状态*/
#define CONFIG_SPI1_FIRSTBIT SPI_FIRSTBIT_MSB                 /*起始位是MSB/LSB*/
#define CONFIG_SPI1_NSS SPI_NSS_SOFT                          /*NSS引脚由硬件/软件指定*/
#define CONFIG_SPI1_TIMODE SPI_TIMODE_DISABLE                 /*是否启动TI模式*/
#define CONFIG_SPI1_MODE SPI_MODE_MASTER                      /*操作模式主机/从机*/
/*********************************SPI端口配置************************************/

/**
 * @description: SPI功能
 */
extern SPI_HandleTypeDef V_config_spi1;

void InitializeSPI1(void);
void InitializeSPI1ForPin(void);
void InitializeSPI1ForProtocol(void);
void FuncSPI1NSSReady(GPIO_TypeDef *m_gpio_group, uint16_t m_gpio_pin);
void FuncSPI1NSSQuit(GPIO_TypeDef *m_gpio_group, uint16_t m_gpio_pin);
/**
 * @description: SPI1指定位置发送
 * @param {uint8_t} *m_buffer_ptr 准备发送的缓冲区指针
 * @param {uint16_t} m_num_to_write 要写入的字节数
 * @return {*}
 */
void FuncSPI1Transmit(uint8_t *m_buffer_ptr, uint16_t m_num_to_write);
void FuncSPI1Receive(uint8_t *m_buffer_ptr, uint16_t m_num_to_read);
void FuncSPI1WaitForReady(void);
/*********************************SPI功能************************************/

/**
 * @description: Others
 */
/*********************************Others************************************/

#endif
