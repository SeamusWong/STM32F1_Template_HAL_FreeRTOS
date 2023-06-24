#ifndef H_WHX_INTERRUPTS_
#define H_WHX_INTERRUPTS_

#include <stm32f1xx.h>
#include <stm32f1xx_hal.h>
#include "whx_peripherals.h"
#include "whx_communicate_usart.h"

/**
 * @description: 引脚中断端口配置
 */
#define PORT_INTERRUPT_GPIO_1_GROUP GPIOA
#define PORT_INTERRUPT_GPIO_1_PIN GPIO_PIN_0
#define PORT_INTERRUPT_GPIO_1_EXTI_IRQ EXTI0_IRQn

#define FUNC_INTERRUPT_GPIO_1_CLK_ENABLE(args) __HAL_RCC_GPIOA_CLK_ENABLE(args)
#define FUNC_INTERRUPT_GPIO_1_CLK_DISABLE() __HAL_RCC_GPIOA_CLK_DISABLE()
/*********************************引脚中断端口配置************************************/

/**
 * @description: 引脚中断功能
 */

void InitializeInterruptForGpio(void);
void FuncInterruptForGpioEnable(void);
void FuncInterruptForGpioDisable(void);
void FuncInterruptGpioCallback(uint16_t m_interrupt_pin);
/*********************************引脚中断功能************************************/

/**
 * @description: 引脚中断服务替换
 */
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI4_IRQHandler(void);
void HAL_GPIO_EXTI_Callback(uint16_t m_interrupt_pin);
/*********************************引脚中断服务替换************************************/

/**
 * @description: UART中断服务替换
 */
#define PORT_USART_1_EXTI_IRQ USART1_IRQn
#define CONFIG_USART_1_BUFFERSIZE 1

void USART1_IRQHandler(void);
/*********************************UART中断服务替换************************************/

/**
 * @description: UART中断功能
 */
extern UART_HandleTypeDef V_config_usart_1;

void InitializeInterruptForUSART(void);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *m_config_usart_1_struct);
/*********************************UART中断功能************************************/

/**
 * @description: ADC中断端口配置
 */
#define PORT_INTERRUPT_ADC1_EXTI_IRQ ADC1_IRQn
/*********************************ADC中断端口配置************************************/

/**
 * @description: ADC中断功能
 */
extern ADC_HandleTypeDef V_config_adc1;

void InitializeInterruptForADC1(void);
void FuncInterruptForADC1Enable(void);
void FuncInterruptForADC1Disable(void);
/*转换完成中断回调函数（非阻塞模式）*/
void FuncInterruptADCCallbackForConvCplt(ADC_HandleTypeDef *m_adc_struct);
/*********************************ADC中断功能************************************/

/**
 * @description: ADC中断服务替换
 */
void ADC1_IRQHandler(void);
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *m_adc_struct);
/*********************************ADC中断服务替换************************************/

/**
 * @description: TIM中断端口配置
 */
#define PORT_INTERRUPT_TIM6BASE_EXTI_IRQ TIM6_IRQn
/*********************************TIM中断端口配置************************************/

/**
 * @description: TIM中断功能
 */

/*基本定时器*/
extern TIM_HandleTypeDef V_config_tim6base;

void InitializeInterruptForTIM6Base(void);
void FuncInterruptForTIM6BaseEnable(void);
void FuncInterruptForTIM6BaseDisable(void);

/*高级定时器*/
/*定时器中断回调*/
void FuncInterruptTIMCallbackForPeriodElapsed(TIM_HandleTypeDef *m_tim_struct);
/*********************************TIM中断功能************************************/

/**
 * @description: TIM中断服务替换
 */
void TIM6_IRQHandler(void);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *m_tim_struct);
/*********************************TIM中断服务替换************************************/

/**
 * @description: Others
 */
void HAL_SYSTICK_Callback(void);
/*********************************Others************************************/

#endif
