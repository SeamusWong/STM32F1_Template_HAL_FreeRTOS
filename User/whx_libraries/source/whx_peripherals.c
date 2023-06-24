#include "whx_peripherals.h"

/**
 * @brief  System Clock Configuration
 *         The system Clock is configured as follow :
 *            System Clock source            = PLL (HSE)
 *            SYSCLK(Hz)                     = 72000000
 *            HCLK(Hz)                       = 72000000
 *            AHB Prescaler                  = 1
 *            APB1 Prescaler                 = 2
 *            APB2 Prescaler                 = 1
 *            HSE Frequency(Hz)              = 8000000
 *            HSE PREDIV1                    = 1
 *            PLLMUL                         = 9
 *            Flash Latency(WS)              = 2
 * @param  None
 * @retval None
 */
void SystemClockConfig(void)
{
    RCC_ClkInitTypeDef clkinitstruct = {0};
    RCC_OscInitTypeDef oscinitstruct = {0};

    /* Enable HSE Oscillator and activate PLL with HSE as source */
    oscinitstruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    oscinitstruct.HSEState = RCC_HSE_ON;
    oscinitstruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    oscinitstruct.PLL.PLLState = RCC_PLL_ON;
    oscinitstruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    oscinitstruct.PLL.PLLMUL = RCC_PLL_MUL9;
    FUNC_CHECK_INIT(HAL_RCC_OscConfig(&oscinitstruct), "ERROR OscConfig");

    /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
       clocks dividers */
    clkinitstruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    clkinitstruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    clkinitstruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    clkinitstruct.APB2CLKDivider = RCC_HCLK_DIV1;
    clkinitstruct.APB1CLKDivider = RCC_HCLK_DIV2;
    FUNC_CHECK_INIT(HAL_RCC_ClockConfig(&clkinitstruct, FLASH_LATENCY_2), "ERROR ClockConfig");
}

/**
 * @description: LED区段
 */
void InitializeLED(void)
{
    FUNC_LED_1_CLK_ENABLE();
    FUNC_LED_2_CLK_ENABLE();
    FUNC_LED_3_CLK_ENABLE();

    GPIO_InitTypeDef config_led_struct; /*定义一个GPIO_InitTypeDef类型的结构体*/

    config_led_struct.Mode = GPIO_MODE_OUTPUT_PP;   /*设置引脚的输出类型为推挽输出*/
    config_led_struct.Pull = GPIO_PULLUP;           /*设置引脚为上拉模式*/
    config_led_struct.Speed = GPIO_SPEED_FREQ_HIGH; /*设置引脚速率为高速 */

    config_led_struct.Pin = PORT_LED_1_PIN | PORT_LED_2_PIN | PORT_LED_3_PIN; /*选择要控制的GPIO引脚*/
    HAL_GPIO_Init(PORT_LED_1_GROUP, &config_led_struct);

    FuncLEDColourSet(STATUS_LED_COLOUR_BLACK);
}

void FuncLEDColourSet(Type_Status_LED_Colour m_colour)
{
    switch (m_colour)
    {
    case STATUS_LED_COLOUR_RED:
        HAL_GPIO_WritePin(PORT_LED_1_GROUP, PORT_LED_1_PIN, STATUS_LED_ON);
        HAL_GPIO_WritePin(PORT_LED_2_GROUP, PORT_LED_2_PIN, STATUS_LED_OFF);
        HAL_GPIO_WritePin(PORT_LED_3_GROUP, PORT_LED_3_PIN, STATUS_LED_OFF);
        break;

    case STATUS_LED_COLOUR_GREEN:
        HAL_GPIO_WritePin(PORT_LED_1_GROUP, PORT_LED_1_PIN, STATUS_LED_OFF);
        HAL_GPIO_WritePin(PORT_LED_2_GROUP, PORT_LED_2_PIN, STATUS_LED_ON);
        HAL_GPIO_WritePin(PORT_LED_3_GROUP, PORT_LED_3_PIN, STATUS_LED_OFF);
        break;

    case STATUS_LED_COLOUR_BLUE:
        HAL_GPIO_WritePin(PORT_LED_1_GROUP, PORT_LED_1_PIN, STATUS_LED_OFF);
        HAL_GPIO_WritePin(PORT_LED_2_GROUP, PORT_LED_2_PIN, STATUS_LED_OFF);
        HAL_GPIO_WritePin(PORT_LED_3_GROUP, PORT_LED_3_PIN, STATUS_LED_ON);
        break;

    case STATUS_LED_COLOUR_YELLOW:
        HAL_GPIO_WritePin(PORT_LED_1_GROUP, PORT_LED_1_PIN, STATUS_LED_ON);
        HAL_GPIO_WritePin(PORT_LED_2_GROUP, PORT_LED_2_PIN, STATUS_LED_ON);
        HAL_GPIO_WritePin(PORT_LED_3_GROUP, PORT_LED_3_PIN, STATUS_LED_OFF);
        break;

    case STATUS_LED_COLOUR_PURPLE:
        HAL_GPIO_WritePin(PORT_LED_1_GROUP, PORT_LED_1_PIN, STATUS_LED_ON);
        HAL_GPIO_WritePin(PORT_LED_2_GROUP, PORT_LED_2_PIN, STATUS_LED_OFF);
        HAL_GPIO_WritePin(PORT_LED_3_GROUP, PORT_LED_3_PIN, STATUS_LED_ON);
        break;

    case STATUS_LED_COLOUR_CYAN:
        HAL_GPIO_WritePin(PORT_LED_1_GROUP, PORT_LED_1_PIN, STATUS_LED_OFF);
        HAL_GPIO_WritePin(PORT_LED_2_GROUP, PORT_LED_2_PIN, STATUS_LED_ON);
        HAL_GPIO_WritePin(PORT_LED_3_GROUP, PORT_LED_3_PIN, STATUS_LED_ON);
        break;

    case STATUS_LED_COLOUR_WHITE:
        HAL_GPIO_WritePin(PORT_LED_1_GROUP, PORT_LED_1_PIN, STATUS_LED_ON);
        HAL_GPIO_WritePin(PORT_LED_2_GROUP, PORT_LED_2_PIN, STATUS_LED_ON);
        HAL_GPIO_WritePin(PORT_LED_3_GROUP, PORT_LED_3_PIN, STATUS_LED_ON);
        break;

    case STATUS_LED_COLOUR_BLACK:
        HAL_GPIO_WritePin(PORT_LED_1_GROUP, PORT_LED_1_PIN, STATUS_LED_OFF);
        HAL_GPIO_WritePin(PORT_LED_2_GROUP, PORT_LED_2_PIN, STATUS_LED_OFF);
        HAL_GPIO_WritePin(PORT_LED_3_GROUP, PORT_LED_3_PIN, STATUS_LED_OFF);
        break;

    default:
        break;
    }
}

Type_Status_LED_Colour FuncLEDColourRead(void)
{
    Type_Status_LED_Colour result;
    GPIO_PinState state_red = HAL_GPIO_ReadPin(PORT_LED_1_GROUP, PORT_LED_1_PIN);
    GPIO_PinState state_green = HAL_GPIO_ReadPin(PORT_LED_2_GROUP, PORT_LED_2_PIN);
    GPIO_PinState state_blue = HAL_GPIO_ReadPin(PORT_LED_3_GROUP, PORT_LED_3_PIN);

    if (state_red == STATUS_KEY_ON && state_green == STATUS_KEY_OFF && state_blue == STATUS_KEY_OFF)
    {
        result = STATUS_LED_COLOUR_RED;
    }
    else if (state_red == STATUS_KEY_OFF && state_green == STATUS_KEY_ON && state_blue == STATUS_KEY_OFF)
    {
        result = STATUS_LED_COLOUR_GREEN;
    }
    else if (state_red == STATUS_KEY_OFF && state_green == STATUS_KEY_OFF && state_blue == STATUS_KEY_ON)
    {
        result = STATUS_LED_COLOUR_BLUE;
    }
    else if (state_red == STATUS_KEY_ON && state_green == STATUS_KEY_ON && state_blue == STATUS_KEY_OFF)
    {
        result = STATUS_LED_COLOUR_YELLOW;
    }
    else if (state_red == STATUS_KEY_ON && state_green == STATUS_KEY_OFF && state_blue == STATUS_KEY_ON)
    {
        result = STATUS_LED_COLOUR_PURPLE;
    }
    else if (state_red == STATUS_KEY_OFF && state_green == STATUS_KEY_ON && state_blue == STATUS_KEY_ON)
    {
        result = STATUS_LED_COLOUR_CYAN;
    }
    else if (state_red == STATUS_KEY_ON && state_green == STATUS_KEY_ON && state_blue == STATUS_KEY_ON)
    {
        result = STATUS_LED_COLOUR_WHITE;
    }
    else if (state_red == STATUS_KEY_OFF && state_green == STATUS_KEY_OFF && state_blue == STATUS_KEY_OFF)
    {
        result = STATUS_LED_COLOUR_BLACK;
    }
    else
    {
        result = STATUS_LED_COLOUR_BLACK;
    }
    return result;
}

void FuncLEDToggle(void)
{
    static Type_Status_LED_Colour colour_record = STATUS_LED_COLOUR_WHITE;
    if (FuncLEDColourRead() != STATUS_LED_COLOUR_BLACK)
    {
        colour_record = FuncLEDColourRead();
        FuncLEDColourSet(STATUS_LED_COLOUR_BLACK);
    }
    else
    {
        FuncLEDColourSet(colour_record);
    }
}

/**
 * @description: KEY区段
 */
void InitializeKEY(void)
{

    FUNC_KEY_1_CLK_ENABLE(); /*开启按键GPIO口的时钟*/
    FUNC_KEY_2_CLK_ENABLE();

    GPIO_InitTypeDef config_key_gpio_struct;

    config_key_gpio_struct.Mode = GPIO_MODE_INPUT; /*设置引脚为输入模式*/
    config_key_gpio_struct.Pull = GPIO_NOPULL;     /*设置引脚不上拉也不下拉*/

    config_key_gpio_struct.Pin = PORT_KEY_1_PIN | PORT_KEY_2_PIN; /*选择按键的引脚*/
    HAL_GPIO_Init(PORT_KEY_1_GROUP, &config_key_gpio_struct);     /*使用上面的结构体初始化按键*/
}

Type_Status_Key FuncKEY1StatusRead(void)
{
    static uint8_t status_key_1_record = STATUS_KEY_OFF;
    if (HAL_GPIO_ReadPin(PORT_KEY_1_GROUP, PORT_KEY_1_PIN) == STATUS_KEY_ON)
    {
        status_key_1_record = STATUS_KEY_ON;
    }

    if (HAL_GPIO_ReadPin(PORT_KEY_1_GROUP, PORT_KEY_1_PIN) == STATUS_KEY_OFF && status_key_1_record == STATUS_KEY_ON)
    {
        status_key_1_record = STATUS_KEY_OFF;
        return STATUS_KEY_ON;
    }
    else
    {
        return STATUS_KEY_OFF;
    }
}

Type_Status_Key FuncKEY2StatusRead(void)
{
    static uint8_t status_key_2_record = STATUS_KEY_OFF;
    if (HAL_GPIO_ReadPin(PORT_KEY_2_GROUP, PORT_KEY_2_PIN) == STATUS_KEY_ON)
    {
        status_key_2_record = STATUS_KEY_ON;
    }

    if (HAL_GPIO_ReadPin(PORT_KEY_2_GROUP, PORT_KEY_2_PIN) == STATUS_KEY_OFF && status_key_2_record == STATUS_KEY_ON)
    {
        status_key_2_record = STATUS_KEY_OFF;
        return STATUS_KEY_ON;
    }
    else
    {
        return STATUS_KEY_OFF;
    }
}

/**
 * @description: BEEP区段
 */
void InitializeBEEP(void)
{

    FUNC_BEEP_CLK_ENABLE(); /*开启GPIO口的时钟*/

    GPIO_InitTypeDef config_beep_gpio_struct;

    config_beep_gpio_struct.Mode = GPIO_MODE_OUTPUT_PP;   /*设置引脚为推挽输出模式*/
    config_beep_gpio_struct.Pull = GPIO_PULLDOWN;         /*设置引脚下拉*/
    config_beep_gpio_struct.Speed = GPIO_SPEED_FREQ_HIGH; /*设置GPIO速率为50MHz */

    config_beep_gpio_struct.Pin = PORT_BEEP_PIN;              /*选择引脚*/
    HAL_GPIO_Init(PORT_BEEP_GROUP, &config_beep_gpio_struct); /*使用上面的结构体初始化*/
    FuncBEEPSet(STATUS_BEEP_OFF);
}

void FuncBEEPSet(Type_Status_BEEP m_status_beep)
{
    switch (m_status_beep)
    {
    case STATUS_BEEP_ON:
        HAL_GPIO_WritePin(PORT_BEEP_GROUP, PORT_BEEP_PIN, GPIO_PIN_SET);
        break;

    case STATUS_BEEP_OFF:
        HAL_GPIO_WritePin(PORT_BEEP_GROUP, PORT_BEEP_PIN, GPIO_PIN_RESET);
        break;

    default:
        break;
    }
}

/**
 * @description: EEPROM区段
 */
void InitializeEEPROM(void)
{
    InitializeI2C1();
}

void FuncEEPROMWrite(uint8_t *m_buffer_ptr, uint8_t m_target_mem_ptr, uint16_t m_num_to_write)
{
    FuncI2C1WriteForMemory(m_buffer_ptr, m_target_mem_ptr, m_num_to_write);
}

void FuncEEPROMRead(uint8_t *m_buffer_ptr, uint8_t m_target_mem_ptr, uint16_t m_num_to_read)
{
    FuncI2C1ReadForMemory(m_buffer_ptr, m_target_mem_ptr, m_num_to_read);
}

void FuncEEPROMClearAll(void)
{
    uint8_t buffer_clear[CONFIG_I2C_1_TOTALSIZE_TARGETDEVICE] = {0};
    FuncEEPROMWrite(buffer_clear, 0x0, CONFIG_I2C_1_TOTALSIZE_TARGETDEVICE);
}

/**
 * @description: FLASH区段
 */
void InitializeFLASH(void)
{
    InitializeSPI1();
}

void FuncFLASHCommand(Type_Commd_FLASH m_commd_flash)
{
    uint8_t signal = m_commd_flash;
    FUNC_FLASH_TRANSMIT((uint8_t *)&signal, sizeof(signal));
}

uint32_t FuncFLASHCallbackID(void)
{
    uint32_t result;
    uint8_t callback_id[3] = {0};

    FUNC_FLASH_NSS_READY();
    FuncFLASHCommand(COMMD_FLASH_JEDECDEVICEID);
    FUNC_FLASH_RECEIVE((uint8_t *)&callback_id, sizeof(callback_id));
    FUNC_FLASH_NSS_QUIT();

    result = (callback_id[0] << 8 * 2) | (callback_id[1] << 8 * 1) | (callback_id[2] << 8 * 0);
    return result;
}

void FuncFLASHWriteEnable(void)
{
    FUNC_FLASH_NSS_READY();
    FuncFLASHCommand(COMMD_FLASH_WRITEENABLE);
    FUNC_FLASH_NSS_QUIT();
    FuncFLASHWaitForWrite();
}

void FuncFLASHEraseForSectorSingle(uint32_t m_target_mem_ptr)
{
    FuncFLASHWriteEnable();
    if (m_target_mem_ptr % 0x001000 != 0)
    {
        m_target_mem_ptr -= m_target_mem_ptr % 0x001000;
        m_target_mem_ptr += 0x001000;
    }
    FUNC_FLASH_NSS_READY();
    FuncFLASHCommand(COMMD_FLASH_SECTORERASE);

    uint8_t target_men_ptr_array[3] = {0};
    target_men_ptr_array[0] = (uint8_t)m_target_mem_ptr >> 8 * 2;
    target_men_ptr_array[1] = (uint8_t)m_target_mem_ptr >> 8 * 1;
    target_men_ptr_array[2] = (uint8_t)m_target_mem_ptr >> 8 * 0;
    FUNC_FLASH_TRANSMIT((uint8_t *)target_men_ptr_array, sizeof(target_men_ptr_array));

    FUNC_FLASH_NSS_QUIT();
    FuncFLASHWaitForWrite();
}

void FuncFLASHEraseForSector(uint32_t m_target_mem_ptr, uint16_t m_num_to_write)
{
    if (m_target_mem_ptr % 0x001000 != 0)
    {
        m_target_mem_ptr -= m_target_mem_ptr % 0x001000;
        m_target_mem_ptr += 0x001000;
    }

    for (uint16_t count_page = (uint16_t)(m_num_to_write / 0x001000); count_page > 0; count_page--)
    {
        FuncFLASHEraseForSectorSingle(m_target_mem_ptr);
        m_target_mem_ptr += 0x001000;
        m_num_to_write -= 0x001000;
    }

    if (m_num_to_write > 0)
    {
        FuncFLASHEraseForSectorSingle(m_target_mem_ptr);
    }
}

void FuncFLASHWriteForPage(uint8_t *m_buffer_ptr, uint32_t m_target_mem_ptr, uint16_t m_num_to_write)
{
    if (m_num_to_write == 0)
    {
        return;
    }
    if (m_num_to_write > STATUS_FLASH_PAGESIZE)
    {
        m_num_to_write = STATUS_FLASH_PAGESIZE;
    }
    FuncFLASHWriteEnable();
    FUNC_FLASH_NSS_READY();
    FuncFLASHCommand(COMMD_FLASH_PAGEPROGRAM);

    uint8_t target_men_ptr_array[3] = {0};
    target_men_ptr_array[0] = (uint8_t)m_target_mem_ptr >> 8 * 2;
    target_men_ptr_array[1] = (uint8_t)m_target_mem_ptr >> 8 * 1;
    target_men_ptr_array[2] = (uint8_t)m_target_mem_ptr >> 8 * 0;
    FUNC_FLASH_TRANSMIT((uint8_t *)target_men_ptr_array, sizeof(target_men_ptr_array));

    FUNC_FLASH_TRANSMIT((uint8_t *)m_buffer_ptr, m_num_to_write);

    FUNC_FLASH_NSS_QUIT();
    FuncFLASHWaitForWrite();
}

void FuncFLASHWrite(uint8_t *m_buffer_ptr, uint32_t m_target_mem_ptr, uint16_t m_num_to_write)
{
    FuncFLASHEraseForSector(m_target_mem_ptr, m_num_to_write);
    HAL_Delay(100);

    if (m_num_to_write < STATUS_FLASH_PAGESIZE - (m_target_mem_ptr % STATUS_FLASH_PAGESIZE))
    {
        FuncFLASHWriteForPage(m_buffer_ptr, m_target_mem_ptr, m_num_to_write);
        m_num_to_write -= m_num_to_write;
    }
    else
    {
        uint16_t temp_num_to_write = STATUS_FLASH_PAGESIZE - (m_target_mem_ptr % STATUS_FLASH_PAGESIZE);
        FuncFLASHWriteForPage(m_buffer_ptr, m_target_mem_ptr, temp_num_to_write);
        m_buffer_ptr += temp_num_to_write;
        m_target_mem_ptr += temp_num_to_write;
        m_num_to_write -= temp_num_to_write;
    }

    for (uint16_t count_page = (uint16_t)(m_num_to_write / STATUS_FLASH_PAGESIZE); count_page > 0; count_page--)
    {
        FuncFLASHWriteForPage(m_buffer_ptr, m_target_mem_ptr, STATUS_FLASH_PAGESIZE);
        m_buffer_ptr += STATUS_FLASH_PAGESIZE;
        m_target_mem_ptr += STATUS_FLASH_PAGESIZE;
        m_num_to_write -= STATUS_FLASH_PAGESIZE;
    }

    if (m_num_to_write > 0)
    {
        FuncFLASHWriteForPage(m_buffer_ptr, m_target_mem_ptr, m_num_to_write);
    }
}

void FuncFLASHRead(uint8_t *m_buffer_ptr, uint32_t m_target_mem_ptr, uint16_t m_num_to_read)
{
    FUNC_FLASH_NSS_READY();
    FuncFLASHCommand(COMMD_FLASH_READDATA);

    uint8_t target_men_ptr_array[3] = {0};
    target_men_ptr_array[0] = (uint8_t)m_target_mem_ptr >> 8 * 2;
    target_men_ptr_array[1] = (uint8_t)m_target_mem_ptr >> 8 * 1;
    target_men_ptr_array[2] = (uint8_t)m_target_mem_ptr >> 8 * 0;
    FUNC_FLASH_TRANSMIT((uint8_t *)target_men_ptr_array, sizeof(target_men_ptr_array));

    FUNC_FLASH_RECEIVE(m_buffer_ptr, m_num_to_read);
    FUNC_FLASH_NSS_QUIT();
}

void FuncFLASHWaitForWrite(void)
{
    FUNC_FLASH_NSS_READY();
    FuncFLASHCommand(COMMD_FLASH_READSTATUSREG);
    uint8_t flag = 0x0;

    uint32_t timeout = CONFIG_FLASH_TIMEOUT * (SystemCoreClock / 1000);
    while ((flag & 0x01) == SET)
    {
        FUNC_FLASH_RECEIVE((uint8_t *)&flag, sizeof flag);
        if (!timeout--)
        {
            printf("FLASH Timeout\n");
            FuncErrorAlertLEDBEEP();
        }
    }
    FUNC_FLASH_NSS_QUIT();
}

void FuncFLASHWaitForRead(void)
{
    ;
}

/**
 * @description: LCD区段
 */
void InitializeLCD(void)
{
    InitializeLCDForGpio();
    InitializeLCDForProtocol();
    /**
     * @description: 初始化命令
     */
    FuncLCDSetBacklight(STATUS_LCD_LIGHT_ENABLE);
    FuncLCDReset();

    FuncFSMCCommand(COMMD_LCD_SWRESET);
    HAL_Delay(20);
    FuncFSMCCommand(COMMD_LCD_DISPOFF);
    HAL_Delay(20);
    FuncFSMCCommand(COMMD_LCD_SLPIN);
    HAL_Delay(20);

    FuncFSMCCommand(COMMD_LCD_MADCTL);
    FuncLCDWriteDataForSingle(0xC0);
    HAL_Delay(5);
    FuncFSMCCommand(COMMD_LCD_COLMOD);
    FuncLCDWriteDataForSingle(0x55);
    HAL_Delay(5);
    /*ST7789S Frame rate setting*/
    FuncFSMCCommand(COMMD_LCD_PORCTRL);
    FuncLCDWriteDataForSingle(0x0c);
    FuncLCDWriteDataForSingle(0x0c);
    FuncLCDWriteDataForSingle(0x00);
    FuncLCDWriteDataForSingle(0x33);
    FuncLCDWriteDataForSingle(0x33);
    HAL_Delay(5);
    FuncFSMCCommand(COMMD_LCD_GCTRL);
    FuncLCDWriteDataForSingle(0x35);
    HAL_Delay(5);
    /*ST7789S Power setting*/
    FuncFSMCCommand(COMMD_LCD_VCOMS);
    FuncLCDWriteDataForSingle(0x35);
    FuncFSMCCommand(COMMD_LCD_LCMCTRL);
    FuncLCDWriteDataForSingle(0x2c);
    FuncFSMCCommand(COMMD_LCD_VDVVREN);
    FuncLCDWriteDataForSingle(0x01);
    FuncFSMCCommand(COMMD_LCD_VRS);
    FuncLCDWriteDataForSingle(0x13);
    FuncFSMCCommand(COMMD_LCD_VDVS);
    FuncLCDWriteDataForSingle(0x20);
    FuncFSMCCommand(COMMD_LCD_FRCTRL2);
    FuncLCDWriteDataForSingle(0x0f);
    FuncFSMCCommand(COMMD_LCD_REGSEL2);
    FuncLCDWriteDataForSingle(0x0f);
    FuncFSMCCommand(COMMD_LCD_REGSEL1);
    FuncLCDWriteDataForSingle(0x08);
    FuncFSMCCommand(COMMD_LCD_WRCACE);
    FuncLCDWriteDataForSingle(0x90);
    FuncFSMCCommand(COMMD_LCD_PWCTRL1);
    FuncLCDWriteDataForSingle(0xa4);
    FuncLCDWriteDataForSingle(0xa1);
    HAL_Delay(5);
    /*ST7789S gamma setting*/
    FuncFSMCCommand(COMMD_LCD_PVGAMCTRL);
    FuncLCDWriteDataForSingle(0xd0);
    FuncLCDWriteDataForSingle(0x00);
    FuncLCDWriteDataForSingle(0x06);
    FuncLCDWriteDataForSingle(0x09);
    FuncLCDWriteDataForSingle(0x0b);
    FuncLCDWriteDataForSingle(0x2a);
    FuncLCDWriteDataForSingle(0x3c);
    FuncLCDWriteDataForSingle(0x55);
    FuncLCDWriteDataForSingle(0x4b);
    FuncLCDWriteDataForSingle(0x08);
    FuncLCDWriteDataForSingle(0x16);
    FuncLCDWriteDataForSingle(0x14);
    FuncLCDWriteDataForSingle(0x19);
    FuncLCDWriteDataForSingle(0x20);
    FuncFSMCCommand(COMMD_LCD_NVGAMCTRL);
    FuncLCDWriteDataForSingle(0xd0);
    FuncLCDWriteDataForSingle(0x00);
    FuncLCDWriteDataForSingle(0x06);
    FuncLCDWriteDataForSingle(0x09);
    FuncLCDWriteDataForSingle(0x0b);
    FuncLCDWriteDataForSingle(0x29);
    FuncLCDWriteDataForSingle(0x36);
    FuncLCDWriteDataForSingle(0x54);
    FuncLCDWriteDataForSingle(0x4b);
    FuncLCDWriteDataForSingle(0x0d);
    FuncLCDWriteDataForSingle(0x16);
    FuncLCDWriteDataForSingle(0x14);
    FuncLCDWriteDataForSingle(0x21);
    FuncLCDWriteDataForSingle(0x20);
    HAL_Delay(5);
    /* column address control set */
    FuncFSMCCommand(COMMD_LCD_CASET);
    FuncLCDWriteDataForSingle(0x00FF & ((STATUS_LCD_PIXELWIDTH - 1) >> (8 * 3)));
    FuncLCDWriteDataForSingle(0x00FF & ((STATUS_LCD_PIXELWIDTH - 1) >> (8 * 2)));
    FuncLCDWriteDataForSingle(0x00FF & ((STATUS_LCD_PIXELWIDTH - 1) >> (8 * 1))); /*发送高8位*/
    FuncLCDWriteDataForSingle(0x00FF & ((STATUS_LCD_PIXELWIDTH - 1) >> (8 * 0))); /*发送低8位*/
    HAL_Delay(5);
    /* page address control set */
    FuncFSMCCommand(COMMD_LCD_RASET);
    FuncLCDWriteDataForSingle(0x00FF & ((STATUS_LCD_PIXELHEIGHT - 1) >> (8 * 3)));
    FuncLCDWriteDataForSingle(0x00FF & ((STATUS_LCD_PIXELHEIGHT - 1) >> (8 * 2)));
    FuncLCDWriteDataForSingle(0x00FF & ((STATUS_LCD_PIXELHEIGHT - 1) >> (8 * 1))); /*发送高8位*/
    FuncLCDWriteDataForSingle(0x00FF & ((STATUS_LCD_PIXELHEIGHT - 1) >> (8 * 0))); /*发送低8位*/
    HAL_Delay(5);
    /* Sleep Out (11h)  */
    FuncFSMCCommand(COMMD_LCD_SLPOUT); // Exit Sleep
    HAL_Delay(20);
    /* Display ON (29h) */
    FuncFSMCCommand(COMMD_LCD_DISPON); // Display on

    FuncLCDSetDisplayDirection(STATUS_LCD_DISPLAYDIRECTION_VERTICAL_LEFTTOP_RIGHTBOTTOM);
    FuncLCDDrawFullScreen(STATUS_LCD_COLOUR_BACKGROUND);
}

void InitializeLCDForGpio(void)
{
    FUNC_LCD_PIN_ALL_CLK_ENABLE();

    GPIO_InitTypeDef config_lcd_gpio_struct;

    config_lcd_gpio_struct.Mode = GPIO_MODE_OUTPUT_PP;
    config_lcd_gpio_struct.Pull = GPIO_PULLUP;
    config_lcd_gpio_struct.Speed = GPIO_SPEED_FREQ_HIGH;

    config_lcd_gpio_struct.Pin = PORT_LCD_BK_PIN;
    HAL_GPIO_Init(PORT_LCD_BK_GROUP, &config_lcd_gpio_struct);
    config_lcd_gpio_struct.Pin = PORT_LCD_RST_PIN;
    HAL_GPIO_Init(PORT_LCD_RST_GROUP, &config_lcd_gpio_struct);
}

void InitializeLCDForProtocol(void)
{
    InitializeFSMCNORSRAM();
}

void FuncLCDCommand(Type_Commd_LCD m_commd_lcd)
{
    FuncFSMCCommand(m_commd_lcd);
}

void FuncLCDWriteDataForSingle(uint16_t m_data_lcd)
{
    FuncFSMCWriteDataForSingle(m_data_lcd);
}

uint16_t FuncLCDReadDataForSingle(void)
{
    return FuncFSMCReadDataForSingle();
}

uint32_t FuncLCDCallbackID(void)
{
    uint32_t result = 0x0;
    FuncLCDCommand(COMMD_LCD_RDDID);

    for (uint8_t count = 0; count < 2; count++)
    {
        FuncLCDReadDataForSingle(); /*假读*/
    }
    for (uint8_t count = 0; count < 2; count++)
    {
        result <<= 8;
        result |= FuncLCDReadDataForSingle();
    }
    return result;
}

void FuncLCDReset(void)
{
    HAL_GPIO_WritePin(PORT_LCD_RST_GROUP, PORT_LCD_RST_PIN, GPIO_PIN_RESET);
    HAL_Delay(5);
    HAL_GPIO_WritePin(PORT_LCD_RST_GROUP, PORT_LCD_RST_PIN, GPIO_PIN_SET);
    HAL_Delay(5);
}

void FuncLCDSetBacklight(Type_Status_LCD_Light m_light)
{
    switch (m_light)
    {
    case STATUS_LCD_LIGHT_ENABLE:
        HAL_GPIO_WritePin(PORT_LCD_BK_GROUP, PORT_LCD_BK_PIN, GPIO_PIN_RESET);
        break;

    case STATUS_LCD_LIGHT_DISABLE:
        HAL_GPIO_WritePin(PORT_LCD_BK_GROUP, PORT_LCD_BK_PIN, GPIO_PIN_SET);
        break;

    default:
        break;
    }
}

void FuncLCDSetDisplayDirection(Type_Status_LCD_DisplayDirection m_direction)
{
    FuncFSMCCommand(COMMD_LCD_SLPIN);
    HAL_Delay(20);

    FuncFSMCCommand(COMMD_LCD_MADCTL);
    switch (m_direction)
    {
    case STATUS_LCD_DISPLAYDIRECTION_VERTICAL_LEFTTOP_RIGHTBOTTOM:
        FuncLCDWriteDataForSingle(0xC0);
        break;

    case STATUS_LCD_DISPLAYDIRECTION_VERTICAL_RIGHTBOTTOM_LEFTTOP:
        FuncLCDWriteDataForSingle(0x00);
        break;

    case STATUS_LCD_DISPLAYDIRECTION_VERTICAL_LEFTBOTTOM_RIGHTTOP:
        FuncLCDWriteDataForSingle(0x40);
        break;

    case STATUS_LCD_DISPLAYDIRECTION_VERTICAL_RIGHTTOP_LEFTBOTTOM:
        FuncLCDWriteDataForSingle(0x80);
        break;

    case STATUS_LCD_DISPLAYDIRECTION_HORIZONTAL_LEFTTOP_RIGHTBOTTOM:
        FuncLCDWriteDataForSingle(0xA0);
        break;

    case STATUS_LCD_DISPLAYDIRECTION_HORIZONTAL_RIGHTBOTTOM_LEFTTOP:
        FuncLCDWriteDataForSingle(0x60);
        break;

    case STATUS_LCD_DISPLAYDIRECTION_HORIZONTAL_LEFTBOTTOM_RIGHTTOP:
        FuncLCDWriteDataForSingle(0xE0);
        break;

    case STATUS_LCD_DISPLAYDIRECTION_HORIZONTAL_RIGHTTOP_LEFTBOTTOM:
        FuncLCDWriteDataForSingle(0x20);
        break;

    default:
        break;
    }
    HAL_Delay(5);

    FuncFSMCCommand(COMMD_LCD_SLPOUT);
    HAL_Delay(20);
}

void FuncLCDSetWindow(uint16_t m_point_x, uint16_t m_point_y, uint16_t m_window_width, uint16_t m_window_height)
{
    if (m_point_x >= STATUS_LCD_PIXELWIDTH || m_point_y >= STATUS_LCD_PIXELHEIGHT)
    {
        return;
    }

    FuncLCDCommand(COMMD_LCD_CASET);
    FuncLCDWriteDataForSingle(0x00FF & (m_point_x >> (8 * 1)));                        /*发送高8位*/
    FuncLCDWriteDataForSingle(0x00FF & (m_point_x >> (8 * 0)));                        /*发送低8位*/
    FuncLCDWriteDataForSingle(0x00FF & ((m_point_x + m_window_width - 1) >> (8 * 1))); /*发送高8位*/
    FuncLCDWriteDataForSingle(0x00FF & ((m_point_x + m_window_width - 1) >> (8 * 0))); /*发送低8位*/

    FuncLCDCommand(COMMD_LCD_RASET);
    FuncLCDWriteDataForSingle(0x00FF & (m_point_y >> (8 * 1)));                         /*发送高8位*/
    FuncLCDWriteDataForSingle(0x00FF & (m_point_y >> (8 * 0)));                         /*发送低8位*/
    FuncLCDWriteDataForSingle(0x00FF & ((m_point_y + m_window_height - 1) >> (8 * 1))); /*发送高8位*/
    FuncLCDWriteDataForSingle(0x00FF & ((m_point_y + m_window_height - 1) >> (8 * 0))); /*发送低8位*/
}

void FuncLCDFill(uint32_t m_num_point, Type_Status_LCD_Colour m_colour)
{
    FuncLCDCommand(COMMD_LCD_RAMWR);
    for (int count = 0; count < m_num_point; count++)
    {
        FuncLCDWriteDataForSingle((uint16_t)m_colour);
    }
}

void FuncLCDDrawFullScreen(Type_Status_LCD_Colour m_colour)
{
    FuncLCDSetWindow(0, 0, STATUS_LCD_PIXELWIDTH, STATUS_LCD_PIXELHEIGHT);
    FuncLCDFill(STATUS_LCD_PIXELWIDTH * STATUS_LCD_PIXELHEIGHT, m_colour);
}

void FuncLCDDrawPoint(uint16_t m_point_x, uint16_t m_point_y, Type_Status_LCD_Colour m_colour)
{
    if (m_point_x >= STATUS_LCD_PIXELWIDTH || m_point_y >= STATUS_LCD_PIXELHEIGHT)
    {
        return;
    }
    FuncLCDSetWindow(m_point_x, m_point_y, 1, 1);
    FuncLCDCommand(COMMD_LCD_RAMWR);
    FuncLCDWriteDataForSingle((uint16_t)m_colour);
}

void FuncLCDDrawLine(uint16_t m_point_x, uint16_t m_point_y, uint16_t m_length, Type_Status_LCD_Colour m_colour, Type_Status_LCD_LineDirection m_direction)
{
    if (m_point_x >= STATUS_LCD_PIXELWIDTH || m_point_y >= STATUS_LCD_PIXELHEIGHT)
    {
        return;
    }

    switch (m_direction)
    {
    case STATUS_LCD_LINEDIRECTION_VERTICAL:
        FuncLCDSetWindow(m_point_x, m_point_y, 1, m_length);
        break;

    case STATUS_LCD_LINEDIRECTION_HORIZONTAL:
        FuncLCDSetWindow(m_point_x, m_point_y, m_length, 1);
        break;

    default:
        break;
    }
    FuncLCDFill(m_length, m_colour);
}

void FuncLCDDrawRectangleForCorner(uint16_t m_point_x, uint16_t m_point_y, uint16_t m_width, uint16_t m_height, Type_Status_LCD_Colour m_colour, Type_Status_LCD_LineFill m_fill)
{
    if (m_point_x + m_width > STATUS_LCD_PIXELWIDTH || m_point_y + m_height > STATUS_LCD_PIXELHEIGHT)
    {
        return;
    }

    switch (m_fill)
    {
    case STATUS_LCD_LINEFILL_FULL:
        FuncLCDSetWindow(m_point_x, m_point_y, m_width, m_height);
        FuncLCDFill(m_width * m_height, m_colour);
        break;

    case STATUS_LCD_LINEFILL_EMPTY:
        FuncLCDDrawLine(m_point_x, m_point_y, m_width, m_colour, STATUS_LCD_LINEDIRECTION_HORIZONTAL);
        FuncLCDDrawLine(m_point_x, m_point_y + m_height, m_width, m_colour, STATUS_LCD_LINEDIRECTION_HORIZONTAL);
        FuncLCDDrawLine(m_point_x, m_point_y, m_height, m_colour, STATUS_LCD_LINEDIRECTION_VERTICAL);
        FuncLCDDrawLine(m_point_x + m_width, m_point_y, m_height, m_colour, STATUS_LCD_LINEDIRECTION_VERTICAL);
        break;

    default:
        break;
    }
}

void FuncLCDDrawRectangleForCenter(uint16_t m_point_x, uint16_t m_point_y, uint16_t m_width, uint16_t m_height, Type_Status_LCD_Colour m_colour, Type_Status_LCD_LineFill m_fill)
{
    FuncLCDDrawRectangleForCorner(m_point_x - (m_width / 2), m_point_y - (m_height / 2), m_width, m_height, m_colour, m_fill);
}

/**
 * @description: 返回某个像素点的颜色
 * @return {*}16位颜色值(5位R|6位G|5位B)，与Type_Status_LCD_Colour遵循相同规则
 */
uint16_t FuncLCDReadColour(uint16_t m_point_x, uint16_t m_point_y)
{
    if (m_point_x >= STATUS_LCD_PIXELWIDTH || m_point_y >= STATUS_LCD_PIXELHEIGHT)
    {
        return STATUS_LCD_COLOUR_BLACK;
    }

    uint8_t colour_r = 0, colour_g = 0, colour_b = 0;
    uint16_t colour_rg = 0, colour_bb, result = 0;
    FuncLCDSetWindow(m_point_x, m_point_y, 1, 1);
    FuncLCDCommand(COMMD_LCD_RAMRD);

    FuncLCDReadDataForSingle(); /*假读*/
    colour_rg = FuncLCDReadDataForSingle();
    colour_r = (uint8_t)((colour_rg >> (8 * 1)) & 0xF8); /*只保留高5位*/
    colour_g = (uint8_t)((colour_rg >> (8 * 0)) & 0xFC); /*只保留高6位*/
    colour_bb = FuncLCDReadDataForSingle();
    colour_b = (uint8_t)((colour_bb >> (8 * 1)) & 0xF8); /*只保留高5位*/

    result = ((colour_r << 8) | (colour_g << 3) | (colour_b >> 3));

    return result;
}

void FuncLCDDrawCharForASCII(uint16_t m_point_x, uint16_t m_point_y, char m_char, Type_Status_LCD_Colour m_colour, Type_Font_ASCII *m_font)
{
    char char_position = m_char - ' ';                                         /*字符在ASCII中的位置*/
    uint8_t char_size = (m_font->width * m_font->height) / 8;                  /*字模所占字节数*/
    char *char_ptr = (char *)(&m_font->font_table[char_position * char_size]); /*字模首个点地址*/

    FuncLCDSetWindow(m_point_x, m_point_y, m_font->width, m_font->height);
    FuncLCDCommand(COMMD_LCD_RAMWR);
    for (uint8_t count_byte = 0; count_byte < char_size; count_byte++)
    {
        for (uint8_t count_bit = 0; count_bit < 8; count_bit++)
        {
            uint8_t char_point_position_y = m_point_y + ((count_byte * 8 + count_bit) / m_font->width);
            uint8_t char_point_position_x = m_point_x + ((count_byte * 8 + count_bit) % m_font->width);
            uint16_t char_point_colour = FuncLCDReadColour(char_point_position_x, char_point_position_y);
            FuncLCDCommand(COMMD_LCD_RAMWR);
            if (char_ptr[count_byte] & (0x80 >> count_bit))
            {
                FuncLCDWriteDataForSingle(m_colour);
            }
            else
            {
                FuncLCDWriteDataForSingle(char_point_colour);
            }
        }
    }
}

void FuncLCDDrawStrForASCII(uint16_t m_point_x, uint16_t m_point_y, char *m_str, Type_Status_LCD_Colour m_colour, Type_Font_ASCII *m_font)
{
    char char_point_x = m_point_x, char_point_y = m_point_y;
    for (uint8_t count_char = 0; m_str[count_char] > 0; count_char++)
    {
        if (char_point_x + m_font->height > STATUS_LCD_PIXELWIDTH)
        {
            char_point_x = m_point_x;
            char_point_y += m_font->height;
        }

        if (m_str[count_char] == '\n')
        {
            char_point_x = m_point_x;
            char_point_y += m_font->height;
            continue;
        }
        FuncLCDDrawCharForASCII(char_point_x, char_point_y, m_str[count_char], m_colour, m_font);
        char_point_x += m_font->width;
    }
}

/**
 * @description: ADC区段
 */
ADC_HandleTypeDef V_config_adc1;

uint16_t V_data_adc1_array[7] = {0}; /*ADC有最多16个通道，但DMA1只有7个*/

void InitializeADC1(void)
{
    InitializeDMA1();
    InitializeADC1ForGpio();
    InitializeADC1ForProtocol();
}

void InitializeADC1ForGpio(void)
{
    FUNC_ADC1_PIN_ALL_CLK_ENABLE();

    GPIO_InitTypeDef config_adc1_gpio_struct;

    config_adc1_gpio_struct.Mode = GPIO_MODE_ANALOG;
    config_adc1_gpio_struct.Pull = GPIO_NOPULL;
    config_adc1_gpio_struct.Speed = GPIO_SPEED_FREQ_HIGH;

    config_adc1_gpio_struct.Pin = PORT_ADC1_1_PIN;
    HAL_GPIO_Init(PORT_ADC1_1_GROUP, &config_adc1_gpio_struct);
    config_adc1_gpio_struct.Pin = PORT_ADC1_2_PIN;
    HAL_GPIO_Init(PORT_ADC1_2_GROUP, &config_adc1_gpio_struct);
}

void InitializeADC1ForProtocol(void)
{
    RCC_PeriphCLKInitTypeDef config_adc1_clk_struct;

    config_adc1_clk_struct.PeriphClockSelection = CONFIG_ADC1_CLK_PERIPHCLOCKSELECTION;
    config_adc1_clk_struct.AdcClockSelection = CONFIG_ADC1_CLK_ADCCLOCKSELECTION;
    HAL_RCCEx_PeriphCLKConfig(&config_adc1_clk_struct); /*ADC时钟初始化*/

    V_config_adc1.Instance = ADC1;
    V_config_adc1.Init.ContinuousConvMode = CONFIG_ADC1_CONTINUOUSCONVMODE;
    V_config_adc1.Init.DataAlign = CONFIG_ADC1_DATAALIGN;
    V_config_adc1.Init.DiscontinuousConvMode = CONFIG_ADC1_DISCONTINUOUSCONVMODE;
    V_config_adc1.Init.ExternalTrigConv = CONFIG_ADC1_EXTERNALTRIGCONV;
    V_config_adc1.Init.NbrOfConversion = CONFIG_ADC1_NBROFCONVERSION;
    V_config_adc1.Init.NbrOfDiscConversion = CONFIG_ADC1_NBROFDISCCONVERSION;
    V_config_adc1.Init.ScanConvMode = CONFIG_ADC1_SCANCONVMODE;
    FUNC_CHECK_INIT(HAL_ADC_Init(&V_config_adc1), "ERROR ADC_Init");

    ADC_ChannelConfTypeDef config_adc1_channel_struct;

    config_adc1_channel_struct.SamplingTime = CONFIG_ADC1_CHANNEL_SAMPLINGTIME;

    config_adc1_channel_struct.Channel = PORT_ADC1_1_CHANNEL;
    config_adc1_channel_struct.Rank = 1;
    HAL_ADC_ConfigChannel(&V_config_adc1, &config_adc1_channel_struct);
    config_adc1_channel_struct.Channel = PORT_ADC1_2_CHANNEL;
    config_adc1_channel_struct.Rank = 2;
    HAL_ADC_ConfigChannel(&V_config_adc1, &config_adc1_channel_struct);

    __HAL_LINKDMA(&V_config_adc1, DMA_Handle, V_config_dma1);

    // HAL_ADC_Start(&V_config_adc1);
    HAL_ADC_Start_DMA(&V_config_adc1, (uint32_t *)&V_data_adc1_array, CONFIG_ADC1_NBROFCONVERSION);
}

float FuncADC1GetVoltage(uint32_t m_adc_channel)
{
    float result = 0.0;
    if (m_adc_channel == PORT_ADC1_1_CHANNEL)
    {
        result = ((float)V_data_adc1_array[0] / STATUS_ADC1_ACCURACY) * STATUS_ADC1_INPUTVOLTAGE;
    }
    else if (m_adc_channel == PORT_ADC1_2_CHANNEL)
    {
        result = ((float)V_data_adc1_array[1] / STATUS_ADC1_ACCURACY) * STATUS_ADC1_INPUTVOLTAGE;
    }
    else
        ;
    return result;
}

void FuncErrorAlertLEDBEEP(void)
{
    // FuncBEEPSet(STATUS_BEEP_ON);
    FuncLEDColourSet(STATUS_LED_COLOUR_RED);
    while (1)
        ;
}

/**
 * @description: Others
 */
void FuncDelayMicrosecondsForAll(uint32_t us)
{
    uint32_t delay = (HAL_RCC_GetHCLKFreq() / 8000000 * us);
    while (delay--)
        ;
}
