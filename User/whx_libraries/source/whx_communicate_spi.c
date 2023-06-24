#include "whx_communicate_spi.h"

SPI_HandleTypeDef V_config_spi_1;

void InitializeSPI1(void)
{
    InitializeSPI1ForGPIO();
    InitializeSPI1ForProtocol();
}

void InitializeSPI1ForGPIO(void)
{
    FUNC_SPI_1_SCL_CLK_ENABLE();
    FUNC_SPI_1_MISO_CLK_ENABLE();
    FUNC_SPI_1_MOSI_CLK_ENABLE();
    FUNC_SPI_1_NSS_1_CLK_ENABLE();

    GPIO_InitTypeDef config_spi_gpio_struct; /*定义一个GPIO_InitTypeDef类型的结构体*/

    config_spi_gpio_struct.Mode = GPIO_MODE_AF_PP;       /*设置引脚的输出类型为复用推挽输出*/
    config_spi_gpio_struct.Pull = GPIO_PULLUP;           /*设置引脚无上下拉*/
    config_spi_gpio_struct.Speed = GPIO_SPEED_FREQ_HIGH; /*设置引脚速率为高速 */

    config_spi_gpio_struct.Pin = PORT_SPI_1_SCL_PIN; /*选择要控制的GPIO引脚*/
    HAL_GPIO_Init(PORT_SPI_1_SCL_GROUP, &config_spi_gpio_struct);

    config_spi_gpio_struct.Pin = PORT_SPI_1_MISO_PIN; /*选择要控制的GPIO引脚*/
    HAL_GPIO_Init(PORT_SPI_1_MISO_GROUP, &config_spi_gpio_struct);

    config_spi_gpio_struct.Pin = PORT_SPI_1_MOSI_PIN; /*选择要控制的GPIO引脚*/
    HAL_GPIO_Init(PORT_SPI_1_MOSI_GROUP, &config_spi_gpio_struct);

    config_spi_gpio_struct.Mode = GPIO_MODE_OUTPUT_PP; /*设置引脚的输出类型为推挽输出*/
    config_spi_gpio_struct.Pin = PORT_SPI_1_NSS_1_PIN; /*选择要控制的GPIO引脚*/
    HAL_GPIO_Init(PORT_SPI_1_NSS_1_GROUP, &config_spi_gpio_struct);
}

void InitializeSPI1ForProtocol(void)
{
    FUNC_SPI_1_CLK_ENABLE();

    V_config_spi_1.Instance = SPI1;
    V_config_spi_1.Init.BaudRatePrescaler = CONFIG_SPI_1_BAUDRATEPRESCALER;
    V_config_spi_1.Init.CLKPhase = CONFIG_SPI_1_CLKPHASE;
    V_config_spi_1.Init.CLKPolarity = CONFIG_SPI_1_CLKPOLARITY;
    V_config_spi_1.Init.CRCCalculation = CONFIG_SPI_1_CRCCALCULATION;
    V_config_spi_1.Init.CRCPolynomial = CONFIG_SPI_1_CRCPOLYNOMIAL;
    V_config_spi_1.Init.DataSize = CONFIG_SPI_1_DATASIZE;
    V_config_spi_1.Init.Direction = CONFIG_SPI_1_DIRECTION;
    V_config_spi_1.Init.FirstBit = CONFIG_SPI_1_FIRSTBIT;
    V_config_spi_1.Init.NSS = CONFIG_SPI_1_NSS;
    V_config_spi_1.Init.TIMode = CONFIG_SPI_1_TIMODE;

    V_config_spi_1.Init.Mode = CONFIG_SPI_1_MODE;
    if (HAL_SPI_Init(&V_config_spi_1) != HAL_OK)
    {
        FuncErrorAlertLEDBEEP();
    }
    __HAL_SPI_ENABLE(&V_config_spi_1);
}

void FuncSPI1NSSReady(void)
{
    if (V_config_spi_1.Init.CLKPolarity == SPI_POLARITY_LOW)
    {
        HAL_GPIO_WritePin(PORT_SPI_1_NSS_1_GROUP, PORT_SPI_1_NSS_1_PIN, GPIO_PIN_RESET);
    }
    else
    {
        HAL_GPIO_WritePin(PORT_SPI_1_NSS_1_GROUP, PORT_SPI_1_NSS_1_PIN, GPIO_PIN_SET);
    }
    FuncSPI1WaitForReady();
}

void FuncSPI1NSSQuit(void)
{
    if (V_config_spi_1.Init.CLKPolarity == SPI_POLARITY_LOW)
    {
        HAL_GPIO_WritePin(PORT_SPI_1_NSS_1_GROUP, PORT_SPI_1_NSS_1_PIN, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(PORT_SPI_1_NSS_1_GROUP, PORT_SPI_1_NSS_1_PIN, GPIO_PIN_RESET);
    }
}

void FuncSPI1Transmit(uint8_t *m_buffer_ptr, uint16_t m_num_to_write)
{
    FuncSPI1WaitForReady();
    HAL_SPI_Transmit(&V_config_spi_1,m_buffer_ptr,m_num_to_write,CONFIG_SPI_1_TIMEOUT);
    FuncSPI1WaitForReady();
}

void FuncSPI1Receive(uint8_t *m_buffer_ptr, uint16_t m_num_to_read)
{
    FuncSPI1WaitForReady();
    HAL_SPI_Receive(&V_config_spi_1,m_buffer_ptr,m_num_to_read,CONFIG_SPI_1_TIMEOUT);
    FuncSPI1WaitForReady();
}

void FuncSPI1WaitForReady(void)
{
    /*等待传输结束*/
    uint32_t timeout = CONFIG_SPI_1_TIMEOUT * (SystemCoreClock / 1000);
    while (HAL_SPI_GetState(&V_config_spi_1) != HAL_SPI_STATE_READY)
    {
        if(!timeout--)
        {
            printf("Timeout SPI1\n");
            FuncErrorAlertLEDBEEP();
        }
    }
}

void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *m_handle)
{
    if (m_handle->Instance == SPI1)
    {
        printf("ERROR SPI1!\n");
        FuncErrorAlertLEDBEEP();
    }
    else
        ;
}
