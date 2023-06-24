#include "whx_interrupts.h"

/**
 * @description: GPIO中断区域
 */
void InitializeInterruptForGpio(void)
{
    FUNC_INTERRUPT_GPIO_1_CLK_ENABLE();

    GPIO_InitTypeDef config_interrupt_struct;

    config_interrupt_struct.Mode = GPIO_MODE_IT_RISING;
    config_interrupt_struct.Pull = GPIO_NOPULL;

    config_interrupt_struct.Pin = PORT_INTERRUPT_GPIO_1_PIN;
    HAL_GPIO_Init(PORT_INTERRUPT_GPIO_1_GROUP, &config_interrupt_struct);

    HAL_NVIC_SetPriority(PORT_INTERRUPT_GPIO_1_EXTI_IRQ, 2, 0);
    FuncInterruptForGpioEnable();
}

void FuncInterruptForGpioEnable(void)
{
    HAL_NVIC_EnableIRQ(PORT_INTERRUPT_GPIO_1_EXTI_IRQ);
}

void FuncInterruptForGpioDisable(void)
{
    HAL_NVIC_DisableIRQ(PORT_INTERRUPT_GPIO_1_EXTI_IRQ);
}

/**
 * @description: GPIO中断回调函数
 */
void FuncInterruptGpioCallback(uint16_t m_interrupt_pin)
{
    switch (m_interrupt_pin)
    {
    case PORT_INTERRUPT_GPIO_1_PIN:
        /**/;
        break;

    default:
        break;
    }
}

void EXTI0_IRQHandler(void) { HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0); }
void EXTI1_IRQHandler(void) { HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1); }
void EXTI2_IRQHandler(void) { HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2); }
void EXTI3_IRQHandler(void) { HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3); }
void EXTI4_IRQHandler(void) { HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4); }
void HAL_GPIO_EXTI_Callback(uint16_t m_interrupt_pin) { FuncInterruptGpioCallback(m_interrupt_pin); }

/**
 * @description: UART中断区域
 */
void InitializeInterruptForUSART(void)
{
    HAL_NVIC_EnableIRQ(PORT_USART_1_EXTI_IRQ);
    HAL_NVIC_SetPriority(PORT_USART_1_EXTI_IRQ, 3, 3);
}

void USART1_IRQHandler(void)
{
    uint8_t ch = 0;

    if (__HAL_UART_GET_FLAG(&V_config_usart_1, UART_FLAG_RXNE) != RESET)
    {
        ch = (uint16_t)READ_REG(V_config_usart_1.Instance->DR);
        WRITE_REG(V_config_usart_1.Instance->DR, ch);
    }
}

/**
 * @description: ADC中断区域
 */
void InitializeInterruptForADC1(void)
{
    HAL_NVIC_EnableIRQ(PORT_INTERRUPT_ADC1_EXTI_IRQ);
    HAL_NVIC_SetPriority(PORT_INTERRUPT_ADC1_EXTI_IRQ, 1, 1);
    FuncInterruptForADC1Enable();
}

void FuncInterruptForADC1Enable(void)
{
    HAL_ADC_Start_IT(&V_config_adc1);
    HAL_NVIC_EnableIRQ(PORT_INTERRUPT_ADC1_EXTI_IRQ);
}

void FuncInterruptForADC1Disable(void)
{
    HAL_ADC_Stop_IT(&V_config_adc1);
    HAL_NVIC_DisableIRQ(PORT_INTERRUPT_ADC1_EXTI_IRQ);
}

/**
 * @description: ADC转换完成中断回调函数（非阻塞模式）
 */
void FuncInterruptADCCallbackForConvCplt(ADC_HandleTypeDef *m_adc_struct)
{
    if (m_adc_struct->Instance == ADC1)
    {
        ;
    }
}

void ADC1_IRQHandler(void) { HAL_ADC_IRQHandler(&V_config_adc1); }
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *m_adc_struct) { FuncInterruptADCCallbackForConvCplt(m_adc_struct); }

/**
 * @description: TIM中断区域
 */
void InitializeInterruptForTIM6Base(void)
{
    HAL_NVIC_EnableIRQ(PORT_INTERRUPT_TIM6BASE_EXTI_IRQ);
    HAL_NVIC_SetPriority(PORT_INTERRUPT_TIM6BASE_EXTI_IRQ, 1, 0);
}

void FuncInterruptForTIM6BaseEnable(void)
{
    HAL_TIM_Base_Start_IT(&V_config_tim6base);
    HAL_NVIC_EnableIRQ(PORT_INTERRUPT_TIM6BASE_EXTI_IRQ);
}

void FuncInterruptForTIM6BaseDisable(void)
{
    HAL_TIM_Base_Stop_IT(&V_config_tim6base);
    HAL_NVIC_DisableIRQ(PORT_INTERRUPT_TIM6BASE_EXTI_IRQ);
}

/**
 * @description: TIM定时器中断回调
 */
void FuncInterruptTIMCallbackForPeriodElapsed(TIM_HandleTypeDef *m_tim_struct)
{
    if (m_tim_struct->Instance == TIM6)
    {
        ;
    }
}

void TIM6_IRQHandler(void) { HAL_TIM_IRQHandler(&V_config_tim6base); }
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *m_tim_struct) { FuncInterruptTIMCallbackForPeriodElapsed(m_tim_struct); }

/**
 * @description: Others
 */
void HAL_SYSTICK_Callback(void)
{
    ;
}
