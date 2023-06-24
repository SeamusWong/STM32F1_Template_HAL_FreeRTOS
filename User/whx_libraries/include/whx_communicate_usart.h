#ifndef H_WHX_COMMUNICATE_USART_
#define H_WHX_COMMUNICATE_USART_

#include <stdio.h>
#include <stm32f1xx.h>
#include <stm32f1xx_hal.h>
#include "whx_peripherals.h"

/**
 * @description: USART端口配置
 */
#define PORT_USART_1_RX_GROUP GPIOA
#define PORT_USART_1_RX_PIN GPIO_PIN_10

#define PORT_USART_1_TX_GROUP GPIOA
#define PORT_USART_1_TX_PIN GPIO_PIN_9

#define CONFIG_USART_1_INSTANCE USART1                  /*寄存器地址*/
#define CONFIG_USART_1_MODE USART_MODE_TX_RX            /*工作模式*/
#define CONFIG_USART_1_BAUDRATE 115200                  /*波特率*/
#define CONFIG_USART_1_WORDLENGTH USART_WORDLENGTH_8B   /*字长*/
#define CONFIG_USART_1_STOPBITS USART_STOPBITS_1        /*停止位*/
#define CONFIG_USART_1_PARITY USART_PARITY_ODD          /*校验状态*/
#define CONFIG_USART_1_HWCONTROL UART_HWCONTROL_NONE    /*硬件流控模式状态*/
#define CONFIG_USART_1_CLKLASTBIT USART_LASTBIT_DISABLE /*是否使能接收器采样最后一位数据*/
#define CONFIG_USART_1_CLKPHASE USART_PHASE_1EDGE       /*数据采样在上升/下降沿进行*/
#define CONFIG_USART_1_CLKPOLARITY USART_POLARITY_LOW   /*使用正/负极性的时钟信号*/
#define CONFIG_USART_1_TIMEOUT 1000U                    /*超时时间*/

#define FUNC_USART_1_CLK_ENABLE() __HAL_RCC_USART1_CLK_ENABLE()
#define FUNC_USART_1_RX_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()
#define FUNC_USART_1_TX_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()
#define FUNC_USART_1_CLK_DISABLE() __HAL_RCC_USART1_CLK_DISABLE()
#define FUNC_USART_1_RX_CLK_DISABLE() __HAL_RCC_GPIOA_CLK_DISABLE()
#define FUNC_USART_1_TX_CLK_DISABLE() __HAL_RCC_GPIOA_CLK_DISABLE()
/*********************************USART端口配置************************************/

/**
 * @description: USART功能
 */
extern UART_HandleTypeDef V_config_usart_1;

void InitializeUSART1(void);
void InitializeUSART1ForGPIO(void);
void InitializeUSART1ForProtocol(void);
void FuncUSART1SendStr(char *m_str);
int32_t fputc(int32_t m_char, FILE *m_stream);
int32_t fgetc(FILE *m_stream);
void HAL_UART_ErrorCallback(UART_HandleTypeDef *m_handle);
/*********************************USART功能************************************/

#endif
