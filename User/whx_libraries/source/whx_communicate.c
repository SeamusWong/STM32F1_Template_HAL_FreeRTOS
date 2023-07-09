#include "whx_communicate.h"

/**
 * @description: USART区段
 */
void InitializeUSART1(void)
{
    InitializeUSART1ForPin();
    InitializeUSART1ForConfig();
}

void InitializeUSART1ForPin(void)
{
    FUNC_USART1_PIN_CLK_ENABLE();

    GPIO_InitTypeDef config_usart1_gpio;

    config_usart1_gpio.Pull = GPIO_PULLUP;
    config_usart1_gpio.Speed = GPIO_SPEED_FREQ_HIGH;
    config_usart1_gpio.Mode = GPIO_MODE_AF_PP; /* 配置Tx引脚为复用功能  */
    config_usart1_gpio.Pin = PORT_USART1_TX_PIN;
    HAL_GPIO_Init(PORT_USART1_TX_GROUP, &config_usart1_gpio);

    config_usart1_gpio.Pin = PORT_USART1_RX_PIN;
    config_usart1_gpio.Mode = GPIO_MODE_AF_INPUT; /* 配置Rx引脚为复用功能 */
    HAL_GPIO_Init(PORT_USART1_RX_GROUP, &config_usart1_gpio);
}

UART_HandleTypeDef V_handle_usart1;

void InitializeUSART1ForConfig(void)
{
    FUNC_USART1_CLK_ENABLE();

    V_handle_usart1.Instance = CONFIG_USART1_INSTANCE;
    V_handle_usart1.Init.Mode = CONFIG_USART1_MODE;
    V_handle_usart1.Init.BaudRate = CONFIG_USART1_BAUDRATE;
    V_handle_usart1.Init.WordLength = CONFIG_USART1_WORDLENGTH;
    V_handle_usart1.Init.StopBits = CONFIG_USART1_STOPBITS;
    V_handle_usart1.Init.Parity = CONFIG_USART1_PARITY;
    V_handle_usart1.Init.HwFlowCtl = CONFIG_USART1_HWCONTROL;
    // V_handle_usart1.Init.CLKLastBit = CONFIG_USART1_CLKLASTBIT;
    // V_handle_usart1.Init.CLKPhase = CONFIG_USART1_CLKPHASE;
    // V_handle_usart1.Init.CLKPolarity = CONFIG_USART1_CLKPOLARITY;
    FUNC_CHECK_FOR_HAL(HAL_UART_Init(&V_handle_usart1), "ERROR UART_Init");

    __HAL_UART_ENABLE(&V_handle_usart1);
}

/**
 * @description: 重定向stdio.h的fputc，发送一个字节数据到串口DEBUG_USART
 */
int32_t fputc(int32_t m_char, FILE *m_stream)
{
    HAL_UART_Transmit(&V_handle_usart1, (uint8_t *)&m_char, sizeof((uint8_t)m_char), CONFIG_USART1_TIMEOUT);

    FuncLED1SetColour(STATUS_LED_COLOUR_YELLOW);
    FUNC_DELAY_US_FOR_ALL(10);
    FuncLED1SetColour(STATUS_LED_COLOUR_BLACK);
    FUNC_DELAY_US_FOR_ALL(10);
    return 0;
}

/**
 * @description: 重定向stdio.h的fgetc，用于实现scanf、getchar等函数
 */
int32_t fgetc(FILE *m_stream)
{
    uint8_t m_char;
    HAL_UART_Receive(&V_handle_usart1, (uint8_t *)&m_char, sizeof((uint8_t)m_char), CONFIG_USART1_TIMEOUT);

    FuncLED1SetColour(STATUS_LED_COLOUR_BLUE);
    FUNC_DELAY_US_FOR_ALL(10);
    FuncLED1SetColour(STATUS_LED_COLOUR_BLACK);
    FUNC_DELAY_US_FOR_ALL(10);
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
    // FuncErrorAlert();
}

/**
 * @description: I2C区段
 */
I2C_HandleTypeDef V_handle_iic1;
I2C_HandleTypeDef V_handle_iic2;

void InitializeIIC1(void)
{
    InitializeIIC1ForPin();
    InitializeIIC1ForConfig();
}

void InitializeIIC1ForPin(void)
{
    FUNC_IIC1_PIN_CLK_ENABLE();

    GPIO_InitTypeDef config_iic1_gpio; /*定义一个GPIO_InitTypeDef类型的结构体*/

    config_iic1_gpio.Mode = GPIO_MODE_AF_OD;       /*设置引脚的输出类型为复用开漏输出*/
    config_iic1_gpio.Pull = GPIO_NOPULL;           /*设置引脚无上下拉*/
    config_iic1_gpio.Speed = GPIO_SPEED_FREQ_HIGH; /*设置引脚速率为高速 */

    config_iic1_gpio.Pin = PORT_IIC1_SCL_PIN; /*选择要控制的GPIO引脚*/
    HAL_GPIO_Init(PORT_IIC1_SCL_GROUP, &config_iic1_gpio);

    config_iic1_gpio.Pin = PORT_IIC1_SDA_PIN; /*选择要控制的GPIO引脚*/
    HAL_GPIO_Init(PORT_IIC1_SDA_GROUP, &config_iic1_gpio);
}

void InitializeIIC1ForConfig(void)
{
    FUNC_IIC1_CLK_ENABLE();

    FUNC_IIC1_FORCE_RESET();   /*强制I2C外设时钟复位*/
    FUNC_IIC1_RELEASE_RESET(); /*释放I2C外设时钟复位*/

    V_handle_iic1.Instance = I2C1;
    V_handle_iic1.Init.ClockSpeed = CONFIG_IIC1_CLOCKSPEED;
    V_handle_iic1.Init.AddressingMode = CONFIG_IIC1_ADDRESSINGMODE;
    V_handle_iic1.Init.DualAddressMode = CONFIG_IIC1_DUALADDRESSMODE;
    V_handle_iic1.Init.DutyCycle = CONFIG_IIC1_DUTYCYCLE;
    V_handle_iic1.Init.GeneralCallMode = CONFIG_IIC1_GENERALCALLMODE;
    V_handle_iic1.Init.NoStretchMode = CONFIG_IIC1_NOSTRETCHMODE;
    V_handle_iic1.Init.OwnAddress1 = CONFIG_IIC1_OWNADDRESSMODE_1;
    V_handle_iic1.Init.OwnAddress2 = CONFIG_IIC1_OWNADDRESSMODE_2;

    FUNC_CHECK_FOR_HAL(HAL_I2C_Init(&V_handle_iic1), "ERROR IIC1_Init");

    __HAL_I2C_ENABLE(&V_handle_iic1);
}

void FuncIIC1WaitForReady(uint16_t m_target_address)
{
    FUNC_WAITSTATUS_TIMEOUT(HAL_I2C_GetState(&V_handle_iic1), HAL_I2C_STATE_READY, CONFIG_IIC1_TIMEOUT, "ERROR IIC1_Timeout");

    FUNC_CHECK_FOR_HAL(HAL_I2C_IsDeviceReady(&V_handle_iic1, m_target_address, 1000, CONFIG_IIC1_TIMEOUT), "ERROR IIC1_Timeout_DeviceReady");

    FUNC_WAITSTATUS_TIMEOUT(HAL_I2C_GetState(&V_handle_iic1), HAL_I2C_STATE_READY, CONFIG_IIC1_TIMEOUT, "ERROR IIC1_Timeout");
}

void FuncIIC1Transmit(uint16_t m_target_address, uint8_t *m_buffer_ptr, uint16_t m_num_to_write)
{
    FuncIIC1WaitForReady(m_target_address);
    HAL_I2C_Master_Transmit(&V_handle_iic1, m_target_address, m_buffer_ptr, m_num_to_write, CONFIG_IIC1_TIMEOUT);
    FuncIIC1WaitForReady(m_target_address);
}

void FuncIIC1Receive(uint16_t m_target_address, uint8_t *m_buffer_ptr, uint16_t m_num_to_read)
{
    FuncIIC1WaitForReady(m_target_address);
    HAL_I2C_Master_Receive(&V_handle_iic1, m_target_address, m_buffer_ptr, m_num_to_read, CONFIG_IIC1_TIMEOUT);
    FuncIIC1WaitForReady(m_target_address);
}

void FuncIIC1WriteForMemory(uint16_t m_target_address, uint16_t m_target_pagesize, uint8_t *m_buffer_ptr, uint8_t m_target_mem_ptr, uint16_t m_num_to_write)
{
    HAL_StatusTypeDef flag = HAL_OK;
    while (m_target_mem_ptr % m_target_pagesize != 0 || m_num_to_write == 0)
    {
        flag = HAL_I2C_Mem_Write(&V_handle_iic1,             /*指向 I2C_HandleTypeDef 配置结构的指针*/
                                 m_target_address,           /*目标设备地址*/
                                 (uint16_t)m_target_mem_ptr, /*目标内部存储器地址*/
                                 I2C_MEMADD_SIZE_8BIT,       /*内存地址大小*/
                                 m_buffer_ptr,               /*准备发送的缓冲区指针*/
                                 sizeof(*m_buffer_ptr),      /*要发送的数据大小*/
                                 CONFIG_IIC1_TIMEOUT);      /*超时时间*/
        FuncIIC1WaitForReady(m_target_address);
        FUNC_CHECK_FOR_HAL(flag, "ERROR In FuncIIC1WriteForMemory!");

        m_buffer_ptr++;
        m_target_mem_ptr++;
        m_num_to_write--;
    }

    for (uint16_t count_page = (uint16_t)(m_num_to_write / m_target_pagesize); count_page > 0; count_page--)
    {
        flag = HAL_I2C_Mem_Write(&V_handle_iic1,             /*指向 I2C_HandleTypeDef 配置结构的指针*/
                                 m_target_address,           /*目标设备地址*/
                                 (uint16_t)m_target_mem_ptr, /*目标内部存储器地址*/
                                 I2C_MEMADD_SIZE_8BIT,       /*内存地址大小*/
                                 m_buffer_ptr,               /*准备发送的缓冲区指针*/
                                 m_target_pagesize,          /*要发送的数据大小*/
                                 CONFIG_IIC1_TIMEOUT);      /*超时时间*/
        FuncIIC1WaitForReady(m_target_address);
        FUNC_CHECK_FOR_HAL(flag, "ERROR In FuncIIC1WriteForMemory!");

        m_buffer_ptr += m_target_pagesize;
        m_target_mem_ptr += m_target_pagesize;
        m_num_to_write -= m_target_pagesize;
    }

    if (m_num_to_write > 0)
    {
        flag = HAL_I2C_Mem_Write(&V_handle_iic1,             /*指向 I2C_HandleTypeDef 配置结构的指针*/
                                 m_target_address,           /*目标设备地址*/
                                 (uint16_t)m_target_mem_ptr, /*目标内部存储器地址*/
                                 I2C_MEMADD_SIZE_8BIT,       /*内存地址大小*/
                                 m_buffer_ptr,               /*准备发送的缓冲区指针*/
                                 m_num_to_write,             /*要发送的数据大小*/
                                 CONFIG_IIC1_TIMEOUT);      /*超时时间*/
        FuncIIC1WaitForReady(m_target_address);
        FUNC_CHECK_FOR_HAL(flag, "ERROR In FuncIIC1WriteForMemory!");
    }
}

void FuncIIC1ReadForMemory(uint16_t m_target_address, uint8_t *m_buffer_ptr, uint8_t m_target_mem_ptr, uint16_t m_num_to_read)
{
    HAL_StatusTypeDef flag = HAL_OK;
    flag = HAL_I2C_Mem_Read(&V_handle_iic1,             /*指向 I2C_HandleTypeDef 配置结构的指针*/
                            m_target_address,           /*目标设备地址*/
                            (uint16_t)m_target_mem_ptr, /*目标内部存储器地址*/
                            I2C_MEMADD_SIZE_8BIT,       /*内存地址大小*/
                            m_buffer_ptr,               /*准备发送的缓冲区指针*/
                            m_num_to_read,              /*要发送的数据大小*/
                            CONFIG_IIC1_TIMEOUT);      /*超时时间*/
    FuncIIC1WaitForReady(m_target_address);
    FUNC_CHECK_FOR_HAL(flag, "ERROR In FuncIIC1WriteForMemory!");
}

/**
 * @description: SPI区段
 */
SPI_HandleTypeDef V_handle_spi1;

void InitializeSPI1(void)
{
    InitializeSPI1ForPin();
    InitializeSPI1ForConfig();
}

void InitializeSPI1ForPin(void)
{
    FUNC_SPI1_PIN_CLK_ENABLE();

    GPIO_InitTypeDef config_spi1_gpio; /*定义一个GPIO_InitTypeDef类型的结构体*/

    config_spi1_gpio.Mode = GPIO_MODE_AF_PP;       /*设置引脚的输出类型为复用推挽输出*/
    config_spi1_gpio.Pull = GPIO_PULLUP;           /*设置引脚无上下拉*/
    config_spi1_gpio.Speed = GPIO_SPEED_FREQ_HIGH; /*设置引脚速率为高速 */

    config_spi1_gpio.Pin = PORT_SPI1_SCL_PIN; /*选择要控制的GPIO引脚*/
    HAL_GPIO_Init(PORT_SPI1_SCL_GROUP, &config_spi1_gpio);

    config_spi1_gpio.Pin = PORT_SPI1_MISO_PIN; /*选择要控制的GPIO引脚*/
    HAL_GPIO_Init(PORT_SPI1_MISO_GROUP, &config_spi1_gpio);

    config_spi1_gpio.Pin = PORT_SPI1_MOSI_PIN; /*选择要控制的GPIO引脚*/
    HAL_GPIO_Init(PORT_SPI1_MOSI_GROUP, &config_spi1_gpio);
}

void InitializeSPI1ForConfig(void)
{
    FUNC_SPI1_CLK_ENABLE();

    V_handle_spi1.Instance = SPI1;
    V_handle_spi1.Init.BaudRatePrescaler = CONFIG_SPI1_BAUDRATEPRESCALER;
    V_handle_spi1.Init.CLKPhase = CONFIG_SPI1_CLKPHASE;
    V_handle_spi1.Init.CLKPolarity = CONFIG_SPI1_CLKPOLARITY;
    V_handle_spi1.Init.CRCCalculation = CONFIG_SPI1_CRCCALCULATION;
    V_handle_spi1.Init.CRCPolynomial = CONFIG_SPI1_CRCPOLYNOMIAL;
    V_handle_spi1.Init.DataSize = CONFIG_SPI1_DATASIZE;
    V_handle_spi1.Init.Direction = CONFIG_SPI1_DIRECTION;
    V_handle_spi1.Init.FirstBit = CONFIG_SPI1_FIRSTBIT;
    V_handle_spi1.Init.NSS = CONFIG_SPI1_NSS;
    V_handle_spi1.Init.TIMode = CONFIG_SPI1_TIMODE;

    V_handle_spi1.Init.Mode = CONFIG_SPI1_MODE;
    FUNC_CHECK_FOR_HAL(HAL_SPI_Init(&V_handle_spi1), "ERROR SPI1_Init");

    __HAL_SPI_ENABLE(&V_handle_spi1);
}

void FuncSPI1NSSReady(GPIO_TypeDef *m_gpio_group, uint16_t m_gpio_pin)
{

    if (V_handle_spi1.Init.CLKPolarity == SPI_POLARITY_LOW)
    {
        HAL_GPIO_WritePin(m_gpio_group, m_gpio_pin, GPIO_PIN_RESET);
    }
    else
    {
        HAL_GPIO_WritePin(m_gpio_group, m_gpio_pin, GPIO_PIN_SET);
    }

    FuncSPI1WaitForReady();
}

void FuncSPI1NSSQuit(GPIO_TypeDef *m_gpio_group, uint16_t m_gpio_pin)
{

    if (V_handle_spi1.Init.CLKPolarity == SPI_POLARITY_LOW)
    {
        HAL_GPIO_WritePin(m_gpio_group, m_gpio_pin, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(m_gpio_group, m_gpio_pin, GPIO_PIN_RESET);
    }
}

void FuncSPI1Transmit(uint8_t *m_buffer_ptr, uint16_t m_num_to_write)
{
    FuncSPI1WaitForReady();
    HAL_SPI_Transmit(&V_handle_spi1, m_buffer_ptr, m_num_to_write, CONFIG_SPI1_TIMEOUT);
    FuncSPI1WaitForReady();
}

void FuncSPI1Receive(uint8_t *m_buffer_ptr, uint16_t m_num_to_read)
{
    FuncSPI1WaitForReady();
    HAL_SPI_Receive(&V_handle_spi1, m_buffer_ptr, m_num_to_read, CONFIG_SPI1_TIMEOUT);
    FuncSPI1WaitForReady();
}

void FuncSPI1WaitForReady(void)
{
    /*等待传输结束*/
    FUNC_WAITSTATUS_TIMEOUT(HAL_SPI_GetState(&V_handle_spi1), HAL_SPI_STATE_READY, CONFIG_SPI1_TIMEOUT, "Timeout SPI1");
}
