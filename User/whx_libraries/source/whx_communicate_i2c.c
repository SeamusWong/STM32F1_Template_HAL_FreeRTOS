#include "whx_communicate_i2c.h"

I2C_HandleTypeDef V_config_i2c_1;
I2C_HandleTypeDef V_config_i2c_2;

void InitializeI2C1(void)
{
    InitializeI2C1ForGPIO();
    InitializeI2C1ForProtocol();
}

void InitializeI2C1ForGPIO(void)
{
    FUNC_I2C_1_SCL_CLK_ENABLE();
    FUNC_I2C_1_SDA_CLK_ENABLE();

    GPIO_InitTypeDef config_i2c_gpio_struct; /*定义一个GPIO_InitTypeDef类型的结构体*/

    config_i2c_gpio_struct.Mode = GPIO_MODE_AF_OD;       /*设置引脚的输出类型为复用开漏输出*/
    config_i2c_gpio_struct.Pull = GPIO_NOPULL;           /*设置引脚无上下拉*/
    config_i2c_gpio_struct.Speed = GPIO_SPEED_FREQ_HIGH; /*设置引脚速率为高速 */

    config_i2c_gpio_struct.Pin = PORT_I2C_1_SCL_PIN; /*选择要控制的GPIO引脚*/
    HAL_GPIO_Init(PORT_I2C_1_SCL_GROUP, &config_i2c_gpio_struct);

    config_i2c_gpio_struct.Pin = PORT_I2C_1_SDA_PIN; /*选择要控制的GPIO引脚*/
    HAL_GPIO_Init(PORT_I2C_1_SDA_GROUP, &config_i2c_gpio_struct);
}

void InitializeI2C1ForProtocol(void)
{
    FUNC_I2C_1_CLK_ENABLE();

    FUNC_I2C_1_FORCE_RESET();   /*强制I2C外设时钟复位*/
    FUNC_I2C_1_RELEASE_RESET(); /*释放I2C外设时钟复位*/

    V_config_i2c_1.Instance = I2C1;
    V_config_i2c_1.Init.ClockSpeed = CONFIG_I2C_1_CLOCKSPEED;
    V_config_i2c_1.Init.AddressingMode = CONFIG_I2C_1_ADDRESSINGMODE;
    V_config_i2c_1.Init.DualAddressMode = CONFIG_I2C_1_DUALADDRESSMODE;
    V_config_i2c_1.Init.DutyCycle = CONFIG_I2C_1_DUTYCYCLE;
    V_config_i2c_1.Init.GeneralCallMode = CONFIG_I2C_1_GENERALCALLMODE;
    V_config_i2c_1.Init.NoStretchMode = CONFIG_I2C_1_NOSTRETCHMODE;
    V_config_i2c_1.Init.OwnAddress1 = CONFIG_I2C_1_OWNADDRESSMODE_1;
    V_config_i2c_1.Init.OwnAddress2 = CONFIG_I2C_1_OWNADDRESSMODE_2;

    if (HAL_I2C_Init(&V_config_i2c_1) != HAL_OK)
    {
        FuncErrorAlertLEDBEEP();
    }
    __HAL_I2C_ENABLE(&V_config_i2c_1);
}

void FuncI2C1WaitForReady(void)
{
    uint32_t timeout = CONFIG_I2C_1_TIMEOUT * (SystemCoreClock / 1000);
    while (HAL_I2C_GetState(&V_config_i2c_1) != HAL_I2C_STATE_READY)
    {
        if (!timeout--)
        {
            printf("Timeout I2C1\n");
            FuncErrorAlertLEDBEEP();
        }
    }

    timeout = CONFIG_I2C_1_TIMEOUT * (SystemCoreClock / 1000);
    while (HAL_I2C_IsDeviceReady(&V_config_i2c_1, CONFIG_I2C_1_ADDRESS_TARGETDEVICE, timeout, CONFIG_I2C_1_TIMEOUT) == HAL_TIMEOUT)
        ;

    timeout = CONFIG_I2C_1_TIMEOUT * (SystemCoreClock / 1000);
    while (HAL_I2C_GetState(&V_config_i2c_1) != HAL_I2C_STATE_READY)
    {
        if (!timeout--)
        {
            printf("Timeout I2C1\n");
            FuncErrorAlertLEDBEEP();
        }
    }
}

void FuncI2C1Transmit(uint8_t *m_buffer_ptr, uint16_t m_num_to_write)
{
    FuncI2C1WaitForReady();
    HAL_I2C_Master_Transmit(&V_config_i2c_1, CONFIG_I2C_1_ADDRESS_TARGETDEVICE, m_buffer_ptr, m_num_to_write, CONFIG_I2C_1_TIMEOUT);
    FuncI2C1WaitForReady();
}

void FuncI2C1Receive(uint8_t *m_buffer_ptr, uint16_t m_num_to_read)
{
    FuncI2C1WaitForReady();
    HAL_I2C_Master_Receive(&V_config_i2c_1, CONFIG_I2C_1_ADDRESS_TARGETDEVICE, m_buffer_ptr, m_num_to_read, CONFIG_I2C_1_TIMEOUT);
    FuncI2C1WaitForReady();
}

void FuncI2C1WriteForMemory(uint8_t *m_buffer_ptr, uint8_t m_target_mem_ptr, uint16_t m_num_to_write)
{
    HAL_StatusTypeDef flag = HAL_OK;
    while (m_target_mem_ptr % CONFIG_I2C_1_PAGESIZE != 0 || m_num_to_write == 0)
    {
        flag = HAL_I2C_Mem_Write(&V_config_i2c_1,            /*指向 I2C_HandleTypeDef 配置结构的指针*/
                                 CONFIG_I2C_1_ADDRESS_TARGETDEVICE, /*目标设备地址*/
                                 (uint16_t)m_target_mem_ptr,        /*目标内部存储器地址*/
                                 I2C_MEMADD_SIZE_8BIT,              /*内存地址大小*/
                                 m_buffer_ptr,                      /*准备发送的缓冲区指针*/
                                 sizeof(*m_buffer_ptr),             /*要发送的数据大小*/
                                 CONFIG_I2C_1_TIMEOUT);             /*超时时间*/
        FuncI2C1WaitForReady();
        if (flag != HAL_OK)
        {
            printf("ERROR In FuncI2C1WriteForMemory!\n");
            FuncErrorAlertLEDBEEP();
        }
        m_buffer_ptr++;
        m_target_mem_ptr++;
        m_num_to_write--;
    }

    for (uint16_t count_page = (uint16_t)(m_num_to_write / CONFIG_I2C_1_PAGESIZE); count_page > 0; count_page--)
    {
        flag = HAL_I2C_Mem_Write(&V_config_i2c_1,            /*指向 I2C_HandleTypeDef 配置结构的指针*/
                                 CONFIG_I2C_1_ADDRESS_TARGETDEVICE, /*目标设备地址*/
                                 (uint16_t)m_target_mem_ptr,        /*目标内部存储器地址*/
                                 I2C_MEMADD_SIZE_8BIT,              /*内存地址大小*/
                                 m_buffer_ptr,                      /*准备发送的缓冲区指针*/
                                 CONFIG_I2C_1_PAGESIZE,             /*要发送的数据大小*/
                                 CONFIG_I2C_1_TIMEOUT);             /*超时时间*/
        FuncI2C1WaitForReady();
        if (flag != HAL_OK)
        {
            printf("ERROR In FuncI2C1WriteForMemory!\n");
            FuncErrorAlertLEDBEEP();
        }
        m_buffer_ptr += CONFIG_I2C_1_PAGESIZE;
        m_target_mem_ptr += CONFIG_I2C_1_PAGESIZE;
        m_num_to_write -= CONFIG_I2C_1_PAGESIZE;
    }

    if (m_num_to_write > 0)
    {
        flag = HAL_I2C_Mem_Write(&V_config_i2c_1,            /*指向 I2C_HandleTypeDef 配置结构的指针*/
                                 CONFIG_I2C_1_ADDRESS_TARGETDEVICE, /*目标设备地址*/
                                 (uint16_t)m_target_mem_ptr,        /*目标内部存储器地址*/
                                 I2C_MEMADD_SIZE_8BIT,              /*内存地址大小*/
                                 m_buffer_ptr,                      /*准备发送的缓冲区指针*/
                                 m_num_to_write,                    /*要发送的数据大小*/
                                 CONFIG_I2C_1_TIMEOUT);             /*超时时间*/
        FuncI2C1WaitForReady();
        if (flag != HAL_OK)
        {
            printf("ERROR In FuncI2C1WriteForMemory!\n");
            FuncErrorAlertLEDBEEP();
        }
    }
}

void FuncI2C1ReadForMemory(uint8_t *m_buffer_ptr, uint8_t m_target_mem_ptr, uint16_t m_num_to_read)
{
    HAL_StatusTypeDef flag = HAL_OK;
    flag = HAL_I2C_Mem_Read(&V_config_i2c_1,            /*指向 I2C_HandleTypeDef 配置结构的指针*/
                            CONFIG_I2C_1_ADDRESS_TARGETDEVICE, /*目标设备地址*/
                            (uint16_t)m_target_mem_ptr,        /*目标内部存储器地址*/
                            I2C_MEMADD_SIZE_8BIT,              /*内存地址大小*/
                            m_buffer_ptr,                      /*准备发送的缓冲区指针*/
                            m_num_to_read,                     /*要发送的数据大小*/
                            CONFIG_I2C_1_TIMEOUT);             /*超时时间*/
    FuncI2C1WaitForReady();
    if (flag != HAL_OK)
    {
        printf("ERROR In FuncI2C1ReadForMemory!\n");
        FuncErrorAlertLEDBEEP();
    }
}

void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *m_handle)
{
    if (m_handle->Instance == I2C1)
    {
        printf("ERROR I2C1!\n");
        FuncErrorAlertLEDBEEP();
    }
    else
        ;
}
