#include "whx_communicate_usart.h"

void InitializeUSART1(void)
{
    InitializeUSART1ForGPIO();
    InitializeUSART1ForProtocol();
}

void InitializeUSART1ForGPIO(void)
{
    FUNC_USART_1_RX_CLK_ENABLE();
    FUNC_USART_1_TX_CLK_ENABLE();

    GPIO_InitTypeDef config_usart_gpio_struct;

    config_usart_gpio_struct.Pull = GPIO_PULLUP;
    config_usart_gpio_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    config_usart_gpio_struct.Mode = GPIO_MODE_AF_PP; /* 配置Tx引脚为复用功能  */
    config_usart_gpio_struct.Pin = PORT_USART_1_TX_PIN;
    HAL_GPIO_Init(PORT_USART_1_TX_GROUP, &config_usart_gpio_struct);

    config_usart_gpio_struct.Pin = PORT_USART_1_RX_PIN;
    config_usart_gpio_struct.Mode = GPIO_MODE_AF_INPUT; /* 配置Rx引脚为复用功能 */
    HAL_GPIO_Init(PORT_USART_1_RX_GROUP, &config_usart_gpio_struct);
}

UART_HandleTypeDef V_config_usart_1;

void InitializeUSART1ForProtocol(void)
{
    FUNC_USART_1_CLK_ENABLE();

    V_config_usart_1.Instance = CONFIG_USART_1_INSTANCE;
    V_config_usart_1.Init.Mode = CONFIG_USART_1_MODE;
    V_config_usart_1.Init.BaudRate = CONFIG_USART_1_BAUDRATE;
    V_config_usart_1.Init.WordLength = CONFIG_USART_1_WORDLENGTH;
    V_config_usart_1.Init.StopBits = CONFIG_USART_1_STOPBITS;
    V_config_usart_1.Init.Parity = CONFIG_USART_1_PARITY;
    V_config_usart_1.Init.HwFlowCtl = CONFIG_USART_1_HWCONTROL;
    // V_config_usart_1.Init.CLKLastBit = CONFIG_USART_1_CLKLASTBIT;
    // V_config_usart_1.Init.CLKPhase = CONFIG_USART_1_CLKPHASE;
    // V_config_usart_1.Init.CLKPolarity = CONFIG_USART_1_CLKPOLARITY;
    FUNC_CHECK_INIT(HAL_UART_Init(&V_config_usart_1), "ERROR UART_Init");

    __HAL_UART_ENABLE(&V_config_usart_1);
}

void FuncUSART1SendStr(char *m_str)
{
    for (int count_char = 0; m_str[count_char] != '\0'; count_char++)
    {
        HAL_UART_Transmit(&V_config_usart_1, (uint8_t *)&m_str[count_char], sizeof m_str[count_char], CONFIG_USART_1_TIMEOUT);
    }

    FuncLEDColourSet(STATUS_LED_COLOUR_YELLOW);
    HAL_Delay(50);
    FuncLEDColourSet(STATUS_LED_COLOUR_BLACK);
    HAL_Delay(50);
    while (__HAL_UART_GET_FLAG(&V_config_usart_1, USART_FLAG_TC) == RESET)
        ;
}

/**
 * @description: 重定向stdio.h的fputc，发送一个字节数据到串口DEBUG_USART
 */
int32_t fputc(int32_t m_char, FILE *m_stream)
{
    HAL_UART_Transmit(&V_config_usart_1, (uint8_t *)&m_char, sizeof((uint8_t)m_char), CONFIG_USART_1_TIMEOUT);
    return 0;
}

/**
 * @description: 重定向stdio.h的fgetc，用于实现scanf、getchar等函数
 */
int32_t fgetc(FILE *m_stream)
{
    uint8_t m_char;
    HAL_UART_Receive(&V_config_usart_1, (uint8_t *)&m_char, sizeof((uint8_t)m_char), CONFIG_USART_1_TIMEOUT);
    return (int32_t)m_char;
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *m_handle)
{
    uint8_t temp;
    printf("ERROR UART:");
    if (m_handle->Instance == USART1)
    {
        switch (m_handle->ErrorCode)
        {
        case HAL_UART_ERROR_DMA:
            printf("HAL_UART_ERROR_DMA\n");
            break;

        case HAL_UART_ERROR_FE:
            printf("HAL_UART_ERROR_FE\n");
            break;

        case HAL_UART_ERROR_NE:
            printf("HAL_UART_ERROR_NE\n");
            break;

        case HAL_UART_ERROR_ORE:
            printf("HAL_UART_ERROR_ORE\n");
            __HAL_UNLOCK(m_handle);
            __HAL_UART_CLEAR_FLAG(m_handle, HAL_UART_ERROR_ORE);
            HAL_UART_Receive_IT(m_handle, &temp, 1);
            break;

        case HAL_UART_ERROR_PE:
            printf("HAL_UART_ERROR_PE\n");
            break;

        case HAL_UART_ERROR_NONE:
            printf("HAL_UART_ERROR_NONE\n");
            __HAL_UNLOCK(m_handle);
            __HAL_UART_CLEAR_FLAG(m_handle, HAL_UART_ERROR_NONE);
            HAL_UART_Receive_IT(m_handle, &temp, 1);
            return;

        default:
            break;
        }
    }
    else
        ;
    // FuncErrorAlertLEDBEEP();
}
