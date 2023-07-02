#include "whx_interrupts.h"

/**
 * @description: GPIO中断区域
 */
void InitializeInterruptForGpio(uint32_t m_priority_preempt, uint32_t m_priority_sub)
{
    FUNC_INTERRUPT_GPIO_1_CLK_ENABLE();

    GPIO_InitTypeDef config_interrupt_struct;

    config_interrupt_struct.Mode = GPIO_MODE_IT_RISING;
    config_interrupt_struct.Pull = GPIO_NOPULL;

    config_interrupt_struct.Pin = PORT_INTERRUPT_GPIO_1_PIN;
    HAL_GPIO_Init(PORT_INTERRUPT_GPIO_1_GROUP, &config_interrupt_struct);

    HAL_NVIC_SetPriority(PORT_INTERRUPT_GPIO_1_EXTI_IRQ, m_priority_preempt, m_priority_sub);
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
void FuncInterruptGpioCallback(uint16_t m_pin)
{
    switch (m_pin)
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
void HAL_GPIO_EXTI_Callback(uint16_t m_pin) { FuncInterruptGpioCallback(m_pin); }

/**
 * @description: UART中断区域
 */
void InitializeInterruptForUSART(uint32_t m_priority_preempt, uint32_t m_priority_sub)
{
    HAL_NVIC_SetPriority(PORT_USART_1_IRQN, m_priority_preempt, m_priority_sub);
}

void FuncInterruptForUSARTEnable(void)
{
    HAL_NVIC_EnableIRQ(PORT_USART_1_IRQN);
}

void FuncInterruptForUSARTDisable(void)
{
    HAL_NVIC_DisableIRQ(PORT_USART_1_IRQN);
}

void USART1_IRQHandler(void)
{
    uint8_t ch = 0;

    if (__HAL_UART_GET_FLAG(&V_config_usart1, UART_FLAG_RXNE) != RESET)
    {
        ch = (uint16_t)READ_REG(V_config_usart1.Instance->DR);
        WRITE_REG(V_config_usart1.Instance->DR, ch);
    }
}

/**
 * @description: ADC中断区域
 */
void InitializeInterruptForADC1(uint32_t m_priority_preempt, uint32_t m_priority_sub)
{
    HAL_NVIC_SetPriority(PORT_INTERRUPT_ADC1_IRQN, m_priority_preempt, m_priority_sub);
}

void FuncInterruptForADC1Enable(void)
{
    HAL_NVIC_EnableIRQ(PORT_INTERRUPT_ADC1_IRQN);
    HAL_ADC_Start_IT(&V_config_adc1);
}

void FuncInterruptForADC1Disable(void)
{
    HAL_NVIC_DisableIRQ(PORT_INTERRUPT_ADC1_IRQN);
    HAL_ADC_Stop_IT(&V_config_adc1);
}

/**
 * @description: ADC转换完成中断回调函数（非阻塞模式）
 */
void FuncInterruptADCCallbackForConvCplt(ADC_HandleTypeDef *m_config_adc)
{
    if (m_config_adc->Instance == ADC1)
    {
        ;
    }
}

void ADC1_IRQHandler(void) { HAL_ADC_IRQHandler(&V_config_adc1); }
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *m_config_adc) { FuncInterruptADCCallbackForConvCplt(m_config_adc); }

/**
 * @description: TIM中断区域
 */

/*基本定时器*/
void InitializeInterruptForTIM6Base(uint32_t m_priority_preempt, uint32_t m_priority_sub)
{
    HAL_NVIC_SetPriority(PORT_INTERRUPT_TIM6BASE_IRQN, m_priority_preempt, m_priority_sub);
}

void FuncInterruptForTIM6BaseEnable(void)
{
    HAL_NVIC_EnableIRQ(PORT_INTERRUPT_TIM6BASE_IRQN);
    HAL_TIM_Base_Start_IT(&V_config_tim6base);
}

void FuncInterruptForTIM6BaseDisable(void)
{
    HAL_NVIC_DisableIRQ(PORT_INTERRUPT_TIM6BASE_IRQN);
    HAL_TIM_Base_Stop_IT(&V_config_tim6base);
}

/*高级定时器*/
void InitializeInterruptForTIM5General(uint32_t m_priority_preempt, uint32_t m_priority_sub)
{
    HAL_NVIC_SetPriority(PORT_INTERRUPT_TIM5GENERAL_IRQN, m_priority_preempt, m_priority_sub);
}

void FuncInterruptForTIM5GeneralEnable(void)
{
    HAL_NVIC_EnableIRQ(PORT_INTERRUPT_TIM5GENERAL_IRQN);
    FUNC_CHECK_FOR_HAL(HAL_TIM_Base_Start_IT(&V_config_tim5general), "ERROR TIM5_Interrupt_Base_Start");
    FUNC_CHECK_FOR_HAL(HAL_TIM_IC_Start_IT(&V_config_tim5general, PORT_TIM5GENERAL_CHANNEL_1), "ERROR TIM5_Interrupt_IC_Start");
    FUNC_CHECK_FOR_HAL(HAL_TIM_IC_Start_IT(&V_config_tim5general, PORT_TIM5GENERAL_CHANNEL_2), "ERROR TIM5_Interrupt_IC_Start");
}

void FuncInterruptForTIM5GeneralDisable(void)
{
    HAL_NVIC_DisableIRQ(PORT_INTERRUPT_TIM5GENERAL_IRQN);
    HAL_TIM_Base_Stop_IT(&V_config_tim5general);
    HAL_TIM_IC_Stop_IT(&V_config_tim5general, PORT_TIM5GENERAL_CHANNEL_1);
    HAL_TIM_IC_Stop_IT(&V_config_tim5general, PORT_TIM5GENERAL_CHANNEL_2);
}

/**
 * @description: TIM定时器中断回调
 */
/*定时器周期溢出回调*/
void FuncInterruptTIMCallbackForPeriodElapsed(TIM_HandleTypeDef *m_config_tim)
{
    if (m_config_tim->Instance == TIM6)
    {
        ;
    }
    if (m_config_tim->Instance == TIM5)
    {
        V_data_tim5general_ic_ch1.data_period++;
        V_data_tim5general_ic_ch2.data_period++;
    }
}

/*定时器输入捕获回调*/
void FuncInterruptTIMCallbackFoICCapture(TIM_HandleTypeDef *m_config_tim)
{
    if (m_config_tim->Instance == TIM5)
    {
        switch (m_config_tim->Channel)
        {
        case HAL_TIM_ACTIVE_CHANNEL_1:
        {
            TIM_IC_InitTypeDef config_tim5general_ic;
            if (V_data_tim5general_ic_ch1.flag_start == 0)
            {
                HAL_TIM_IC_Stop_IT(&V_config_tim5general, PORT_TIM5GENERAL_CHANNEL_1);
                __HAL_TIM_SET_COUNTER(&V_config_tim5general, 0);

                config_tim5general_ic.ICPolarity = (CONFIG_TIM5_IC_ICPOLARITY == TIM_ICPOLARITY_RISING ? TIM_ICPOLARITY_FALLING : TIM_ICPOLARITY_RISING);
                config_tim5general_ic.ICFilter = CONFIG_TIM5_IC_ICFILTER;
                config_tim5general_ic.ICPrescaler = CONFIG_TIM5_IC_ICPRESCALER;
                config_tim5general_ic.ICSelection = CONFIG_TIM5_IC_ICSELECTION;
                HAL_TIM_IC_ConfigChannel(&V_config_tim5general, &config_tim5general_ic, PORT_TIM5GENERAL_CHANNEL_1);

                /*启动输入捕获*/
                HAL_TIM_IC_Start_IT(&V_config_tim5general, PORT_TIM5GENERAL_CHANNEL_1);

                V_data_tim5general_ic_ch1.data_period = 0;
                V_data_tim5general_ic_ch1.data_register = 0;
                V_data_tim5general_ic_ch1.flag_start = 1;
            }
            else
            {
                HAL_TIM_IC_Stop_IT(&V_config_tim5general, PORT_TIM5GENERAL_CHANNEL_1);

                V_data_tim5general_ic_ch1.data_register = HAL_TIM_ReadCapturedValue(&V_config_tim5general, PORT_TIM5GENERAL_CHANNEL_1);
                V_data_tim5general_ic_ch1.data_result = V_data_tim5general_ic_ch1.data_period * CONFIG_TIM5_BASE_PERIOD + V_data_tim5general_ic_ch1.data_register;

                config_tim5general_ic.ICPolarity = (CONFIG_TIM5_IC_ICPOLARITY == TIM_ICPOLARITY_RISING ? TIM_ICPOLARITY_RISING : TIM_ICPOLARITY_FALLING);
                config_tim5general_ic.ICFilter = CONFIG_TIM5_IC_ICFILTER;
                config_tim5general_ic.ICPrescaler = CONFIG_TIM5_IC_ICPRESCALER;
                config_tim5general_ic.ICSelection = CONFIG_TIM5_IC_ICSELECTION;
                HAL_TIM_IC_ConfigChannel(&V_config_tim5general, &config_tim5general_ic, PORT_TIM5GENERAL_CHANNEL_1);

                /*启动输入捕获*/
                HAL_TIM_IC_Start_IT(&V_config_tim5general, PORT_TIM5GENERAL_CHANNEL_1);

                V_data_tim5general_ic_ch1.data_period = 0;
                V_data_tim5general_ic_ch1.data_register = 0;
                V_data_tim5general_ic_ch1.flag_start = 0;
            }
        }
        break;

        case HAL_TIM_ACTIVE_CHANNEL_2:
        {
            TIM_IC_InitTypeDef config_tim5general_ic;
            if (V_data_tim5general_ic_ch2.flag_start == 0)
            {
                HAL_TIM_IC_Stop_IT(&V_config_tim5general, PORT_TIM5GENERAL_CHANNEL_2);

                V_data_tim5general_ic_ch2.data_register = HAL_TIM_ReadCapturedValue(&V_config_tim5general, PORT_TIM5GENERAL_CHANNEL_2);
                V_data_tim5general_ic_ch2.data_result = V_data_tim5general_ic_ch2.data_period * CONFIG_TIM5_BASE_PERIOD + V_data_tim5general_ic_ch2.data_register;

                HAL_TIM_IC_Start_IT(&V_config_tim5general, PORT_TIM5GENERAL_CHANNEL_2);

                V_data_tim5general_ic_ch2.data_period = 0;
                V_data_tim5general_ic_ch2.data_register = 0;
                V_data_tim5general_ic_ch2.flag_start = 1;
            }
        }

        default:
            break;
        }
    }
}

void TIM6_IRQHandler(void) { HAL_TIM_IRQHandler(&V_config_tim6base); }
void TIM5_IRQHandler(void) { HAL_TIM_IRQHandler(&V_config_tim5general); }
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *m_config_tim) { FuncInterruptTIMCallbackForPeriodElapsed(m_config_tim); }
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *m_config_tim) { FuncInterruptTIMCallbackFoICCapture(m_config_tim); }

/**
 * @description: Others
 */
void HAL_SYSTICK_Callback(void)
{
    ;
}
