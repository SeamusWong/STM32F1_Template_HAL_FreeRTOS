#include "whx_peripherals.h"

/**
 * @description: LED区段
 */
void InitializeLED1(void)
{
    InitializeLED1ForPin();
    InitializeLED1ForConfig();

    FuncLED1SetColour(STATUS_LED_COLOUR_BLACK);
}

static void InitializeLED1ForPin(void)
{
    FUNC_LED_1_PIN_CLK_ENABLE();

    GPIO_InitTypeDef config_led_1_gpio; /*定义一个GPIO_InitTypeDef类型的结构体*/

    config_led_1_gpio.Mode = GPIO_MODE_OUTPUT_PP;   /*设置引脚的输出类型为推挽输出*/
    config_led_1_gpio.Pull = GPIO_PULLUP;           /*设置引脚为上拉模式*/
    config_led_1_gpio.Speed = GPIO_SPEED_FREQ_HIGH; /*设置引脚速率为高速 */

    config_led_1_gpio.Pin = PORT_LED_1_P1_PIN | PORT_LED_1_P2_PIN | PORT_LED_1_P3_PIN; /*选择要控制的GPIO引脚*/
    HAL_GPIO_Init(PORT_LED_1_P1_GROUP, &config_led_1_gpio);
}

static void InitializeLED1ForConfig(void)
{
    ;
}

void FuncLED1SetColour(Type_Status_LED_Colour m_colour)
{
    switch (m_colour)
    {
    case STATUS_LED_COLOUR_RED:
        HAL_GPIO_WritePin(PORT_LED_1_P1_GROUP, PORT_LED_1_P1_PIN, (GPIO_PinState)STATUS_LED_ON);
        HAL_GPIO_WritePin(PORT_LED_1_P2_GROUP, PORT_LED_1_P2_PIN, (GPIO_PinState)STATUS_LED_OFF);
        HAL_GPIO_WritePin(PORT_LED_1_P3_GROUP, PORT_LED_1_P3_PIN, (GPIO_PinState)STATUS_LED_OFF);
        break;

    case STATUS_LED_COLOUR_GREEN:
        HAL_GPIO_WritePin(PORT_LED_1_P1_GROUP, PORT_LED_1_P1_PIN, (GPIO_PinState)STATUS_LED_OFF);
        HAL_GPIO_WritePin(PORT_LED_1_P2_GROUP, PORT_LED_1_P2_PIN, (GPIO_PinState)STATUS_LED_ON);
        HAL_GPIO_WritePin(PORT_LED_1_P3_GROUP, PORT_LED_1_P3_PIN, (GPIO_PinState)STATUS_LED_OFF);
        break;

    case STATUS_LED_COLOUR_BLUE:
        HAL_GPIO_WritePin(PORT_LED_1_P1_GROUP, PORT_LED_1_P1_PIN, (GPIO_PinState)STATUS_LED_OFF);
        HAL_GPIO_WritePin(PORT_LED_1_P2_GROUP, PORT_LED_1_P2_PIN, (GPIO_PinState)STATUS_LED_OFF);
        HAL_GPIO_WritePin(PORT_LED_1_P3_GROUP, PORT_LED_1_P3_PIN, (GPIO_PinState)STATUS_LED_ON);
        break;

    case STATUS_LED_COLOUR_YELLOW:
        HAL_GPIO_WritePin(PORT_LED_1_P1_GROUP, PORT_LED_1_P1_PIN, (GPIO_PinState)STATUS_LED_ON);
        HAL_GPIO_WritePin(PORT_LED_1_P2_GROUP, PORT_LED_1_P2_PIN, (GPIO_PinState)STATUS_LED_ON);
        HAL_GPIO_WritePin(PORT_LED_1_P3_GROUP, PORT_LED_1_P3_PIN, (GPIO_PinState)STATUS_LED_OFF);
        break;

    case STATUS_LED_COLOUR_PURPLE:
        HAL_GPIO_WritePin(PORT_LED_1_P1_GROUP, PORT_LED_1_P1_PIN, (GPIO_PinState)STATUS_LED_ON);
        HAL_GPIO_WritePin(PORT_LED_1_P2_GROUP, PORT_LED_1_P2_PIN, (GPIO_PinState)STATUS_LED_OFF);
        HAL_GPIO_WritePin(PORT_LED_1_P3_GROUP, PORT_LED_1_P3_PIN, (GPIO_PinState)STATUS_LED_ON);
        break;

    case STATUS_LED_COLOUR_CYAN:
        HAL_GPIO_WritePin(PORT_LED_1_P1_GROUP, PORT_LED_1_P1_PIN, (GPIO_PinState)STATUS_LED_OFF);
        HAL_GPIO_WritePin(PORT_LED_1_P2_GROUP, PORT_LED_1_P2_PIN, (GPIO_PinState)STATUS_LED_ON);
        HAL_GPIO_WritePin(PORT_LED_1_P3_GROUP, PORT_LED_1_P3_PIN, (GPIO_PinState)STATUS_LED_ON);
        break;

    case STATUS_LED_COLOUR_WHITE:
        HAL_GPIO_WritePin(PORT_LED_1_P1_GROUP, PORT_LED_1_P1_PIN, (GPIO_PinState)STATUS_LED_ON);
        HAL_GPIO_WritePin(PORT_LED_1_P2_GROUP, PORT_LED_1_P2_PIN, (GPIO_PinState)STATUS_LED_ON);
        HAL_GPIO_WritePin(PORT_LED_1_P3_GROUP, PORT_LED_1_P3_PIN, (GPIO_PinState)STATUS_LED_ON);
        break;

    case STATUS_LED_COLOUR_BLACK:
        HAL_GPIO_WritePin(PORT_LED_1_P1_GROUP, PORT_LED_1_P1_PIN, (GPIO_PinState)STATUS_LED_OFF);
        HAL_GPIO_WritePin(PORT_LED_1_P2_GROUP, PORT_LED_1_P2_PIN, (GPIO_PinState)STATUS_LED_OFF);
        HAL_GPIO_WritePin(PORT_LED_1_P3_GROUP, PORT_LED_1_P3_PIN, (GPIO_PinState)STATUS_LED_OFF);
        break;

    default:
        break;
    }
}

Type_Status_LED_Colour FuncLED1ReadColour(void)
{
    Type_Status_LED_Colour result;
    Type_Status_LED state_red = (Type_Status_LED)HAL_GPIO_ReadPin(PORT_LED_1_P1_GROUP, PORT_LED_1_P1_PIN);
    Type_Status_LED state_green = (Type_Status_LED)HAL_GPIO_ReadPin(PORT_LED_1_P2_GROUP, PORT_LED_1_P2_PIN);
    Type_Status_LED state_blue = (Type_Status_LED)HAL_GPIO_ReadPin(PORT_LED_1_P3_GROUP, PORT_LED_1_P3_PIN);

    if (state_red == STATUS_LED_ON && state_green == STATUS_LED_OFF && state_blue == STATUS_LED_OFF)
    {
        result = STATUS_LED_COLOUR_RED;
    }
    else if (state_red == STATUS_LED_OFF && state_green == STATUS_LED_ON && state_blue == STATUS_LED_OFF)
    {
        result = STATUS_LED_COLOUR_GREEN;
    }
    else if (state_red == STATUS_LED_OFF && state_green == STATUS_LED_OFF && state_blue == STATUS_LED_ON)
    {
        result = STATUS_LED_COLOUR_BLUE;
    }
    else if (state_red == STATUS_LED_ON && state_green == STATUS_LED_ON && state_blue == STATUS_LED_OFF)
    {
        result = STATUS_LED_COLOUR_YELLOW;
    }
    else if (state_red == STATUS_LED_ON && state_green == STATUS_LED_OFF && state_blue == STATUS_LED_ON)
    {
        result = STATUS_LED_COLOUR_PURPLE;
    }
    else if (state_red == STATUS_LED_OFF && state_green == STATUS_LED_ON && state_blue == STATUS_LED_ON)
    {
        result = STATUS_LED_COLOUR_CYAN;
    }
    else if (state_red == STATUS_LED_ON && state_green == STATUS_LED_ON && state_blue == STATUS_LED_ON)
    {
        result = STATUS_LED_COLOUR_WHITE;
    }
    else if (state_red == STATUS_LED_OFF && state_green == STATUS_LED_OFF && state_blue == STATUS_LED_OFF)
    {
        result = STATUS_LED_COLOUR_BLACK;
    }
    else
    {
        result = STATUS_LED_COLOUR_BLACK;
    }
    return result;
}

void FuncLED1Toggle(void)
{
    static Type_Status_LED_Colour colour_record = STATUS_LED_COLOUR_WHITE;
    if (FuncLED1ReadColour() != STATUS_LED_COLOUR_BLACK)
    {
        colour_record = FuncLED1ReadColour();
        FuncLED1SetColour(STATUS_LED_COLOUR_BLACK);
    }
    else
    {
        FuncLED1SetColour(colour_record);
    }
}

/**
 * @description: KEY区段
 */
void InitializeKEY1(void)
{
    InitializeKEY1ForPin();
    InitializeKEY1ForConfig();
}

static void InitializeKEY1ForPin(void)
{
    FUNC_KEY_1_PIN_CLK_ENABLE(); /*开启按键GPIO口的时钟*/

    GPIO_InitTypeDef config_key_1_gpio;

    config_key_1_gpio.Mode = GPIO_MODE_INPUT; /*设置引脚为输入模式*/
    config_key_1_gpio.Pull = GPIO_NOPULL;     /*设置引脚不上拉也不下拉*/

    config_key_1_gpio.Pin = PORT_KEY_1_PIN;              /*选择按键的引脚*/
    HAL_GPIO_Init(PORT_KEY_1_GROUP, &config_key_1_gpio); /*使用上面的结构体初始化按键*/
}

static void InitializeKEY1ForConfig(void)
{
    ;
}

Type_Status_KEY FuncKEY1GetStatus(void)
{
    Type_Status_KEY result = STATUS_KEY_OFF;
    static Type_Status_KEY status_key_1_record = STATUS_KEY_OFF;

    if (HAL_GPIO_ReadPin(PORT_KEY_1_GROUP, PORT_KEY_1_PIN) == STATUS_KEY_ON)
    {
        status_key_1_record = STATUS_KEY_ON;
    }

    if (HAL_GPIO_ReadPin(PORT_KEY_1_GROUP, PORT_KEY_1_PIN) == STATUS_KEY_OFF && status_key_1_record == STATUS_KEY_ON)
    {
        status_key_1_record = STATUS_KEY_OFF;
        result = STATUS_KEY_ON;
    }
    else
    {
        result = STATUS_KEY_OFF;
    }

    return result;
}

void InitializeKEY2(void)
{
    InitializeKEY2ForPin();
    InitializeKEY2ForConfig();
}

static void InitializeKEY2ForPin(void)
{
    FUNC_KEY_2_PIN_CLK_ENABLE();

    GPIO_InitTypeDef config_key_2_gpio;

    config_key_2_gpio.Mode = GPIO_MODE_INPUT; /*设置引脚为输入模式*/
    config_key_2_gpio.Pull = GPIO_NOPULL;     /*设置引脚不上拉也不下拉*/

    config_key_2_gpio.Pin = PORT_KEY_2_PIN;              /*选择按键的引脚*/
    HAL_GPIO_Init(PORT_KEY_2_GROUP, &config_key_2_gpio); /*使用上面的结构体初始化按键*/
}

static void InitializeKEY2ForConfig(void)
{
    ;
}

Type_Status_KEY FuncKEY2GetStatus(void)
{
    Type_Status_KEY result = STATUS_KEY_OFF;
    static Type_Status_KEY status_key_2_record = STATUS_KEY_OFF;

    if (HAL_GPIO_ReadPin(PORT_KEY_2_GROUP, PORT_KEY_2_PIN) == STATUS_KEY_ON)
    {
        status_key_2_record = STATUS_KEY_ON;
    }

    if (HAL_GPIO_ReadPin(PORT_KEY_2_GROUP, PORT_KEY_2_PIN) == STATUS_KEY_OFF && status_key_2_record == STATUS_KEY_ON)
    {
        status_key_2_record = STATUS_KEY_OFF;
        result = STATUS_KEY_ON;
    }
    else
    {
        result = STATUS_KEY_OFF;
    }

    return result;
}

/**
 * @description: BEEP区段
 */
void InitializeBEEP1(void)
{
    InitializeBEEP1ForPin();
    InitializeBEEP1ForConfig();

    FuncBEEP1SetStatus(STATUS_BEEP_OFF);
}

static void InitializeBEEP1ForPin(void)
{
    FUNC_BEEP_1_PIN_CLK_ENABLE(); /*开启GPIO口的时钟*/

    GPIO_InitTypeDef config_beep_gpio_struct;

    config_beep_gpio_struct.Mode = GPIO_MODE_OUTPUT_PP;   /*设置引脚为推挽输出模式*/
    config_beep_gpio_struct.Pull = GPIO_PULLDOWN;         /*设置引脚下拉*/
    config_beep_gpio_struct.Speed = GPIO_SPEED_FREQ_HIGH; /*设置GPIO速率为50MHz */

    config_beep_gpio_struct.Pin = PORT_BEEP_1_PIN;              /*选择引脚*/
    HAL_GPIO_Init(PORT_BEEP_1_GROUP, &config_beep_gpio_struct); /*使用上面的结构体初始化*/
}

static void InitializeBEEP1ForConfig(void)
{
    ;
}

void FuncBEEP1SetStatus(Type_Status_BEEP m_status_beep)
{
    switch (m_status_beep)
    {
    case STATUS_BEEP_ON:
        HAL_GPIO_WritePin(PORT_BEEP_1_GROUP, PORT_BEEP_1_PIN, (GPIO_PinState)STATUS_BEEP_ON);
        break;

    case STATUS_BEEP_OFF:
        HAL_GPIO_WritePin(PORT_BEEP_1_GROUP, PORT_BEEP_1_PIN, (GPIO_PinState)STATUS_BEEP_OFF);
        break;

    default:
        break;
    }
}

/**
 * @description: EEPROM区段
 */
void InitializeEEPROM1(void)
{
    InitializeIIC1();

    InitializeEEPROM1ForPin();
    InitializeEEPROM1ForConfig();
}

static void InitializeEEPROM1ForPin(void)
{
    ;
}

static void InitializeEEPROM1ForConfig(void)
{
    ;
}

void FuncEEPROM1Write(uint8_t *m_buffer_ptr, uint8_t m_target_mem_ptr, uint16_t m_num_to_write)
{
    FuncIIC1WriteForMemory(PORT_EEPROM_1_ADDRESS_0, STATUS_EEPROM_1_PAGESIZE, m_buffer_ptr, m_target_mem_ptr, m_num_to_write);
}

void FuncEEPROM1Read(uint8_t *m_buffer_ptr, uint8_t m_target_mem_ptr, uint16_t m_num_to_read)
{
    FuncIIC1ReadForMemory(PORT_EEPROM_1_ADDRESS_0, m_buffer_ptr, m_target_mem_ptr, m_num_to_read);
}

void FuncEEPROM1ClearAll(void)
{
    uint8_t *buffer_clear = (uint8_t *)calloc(1, STATUS_EEPROM_1_TOTALSIZE);
    FuncEEPROM1Write(buffer_clear, 0x0, STATUS_EEPROM_1_TOTALSIZE);
    free(buffer_clear);
}

/**
 * @description: FLASH区段
 */
void InitializeFLASH1(void)
{
    InitializeSPI1();

    InitializeFLASH1ForPin();
    InitializeFLASH1ForConfig();
}

static void InitializeFLASH1ForPin(void)
{
    FUNC_FLASH_1_PIN_CLK_ENABLE();
    GPIO_InitTypeDef config_flash_1_gpio; /*定义一个GPIO_InitTypeDef类型的结构体*/

    config_flash_1_gpio.Mode = GPIO_MODE_OUTPUT_PP;   /*设置引脚的输出类型为推挽输出*/
    config_flash_1_gpio.Pull = GPIO_PULLUP;           /*设置引脚无上下拉*/
    config_flash_1_gpio.Speed = GPIO_SPEED_FREQ_HIGH; /*设置引脚速率为高速 */

    config_flash_1_gpio.Pin = PORT_FLASH_1_NSS_PIN; /*选择要控制的GPIO引脚*/
    HAL_GPIO_Init(PORT_FLASH_1_NSS_GROUP, &config_flash_1_gpio);
}

static void InitializeFLASH1ForConfig(void)
{
    ;
}

void FuncFLASH1Command(Type_Commd_FLASH m_commd_flash)
{
    uint8_t signal = m_commd_flash;
    FUNC_FLASH_1_TRANSMIT((uint8_t *)&signal, sizeof(signal));
}

uint32_t FuncFLASH1CallbackDeviceID(void)
{
    uint32_t result;
    uint8_t callback_id[3] = {0};

    FUNC_FLASH_1_NSS_READY();
    FuncFLASH1Command(COMMD_FLASH_JEDECDEVICEID);
    FUNC_FLASH_1_RECEIVE((uint8_t *)&callback_id, sizeof(callback_id));
    FUNC_FLASH_1_NSS_QUIT();

    result = (callback_id[0] << 8 * 2) | (callback_id[1] << 8 * 1) | (callback_id[2] << 8 * 0);
    return result;
}

void FuncFLASH1WriteEnable(void)
{
    FUNC_FLASH_1_NSS_READY();
    FuncFLASH1Command(COMMD_FLASH_WRITEENABLE);
    FUNC_FLASH_1_NSS_QUIT();
    FuncFLASH1WaitForWrite();
}

void FuncFLASH1EraseForSectorSingle(uint32_t m_target_mem_ptr)
{
    FuncFLASH1WriteEnable();
    if (m_target_mem_ptr % 0x001000 != 0)
    {
        m_target_mem_ptr -= m_target_mem_ptr % 0x001000;
        m_target_mem_ptr += 0x001000;
    }
    FUNC_FLASH_1_NSS_READY();
    FuncFLASH1Command(COMMD_FLASH_SECTORERASE);

    uint8_t target_men_ptr_array[3] = {0};
    target_men_ptr_array[0] = (uint8_t)m_target_mem_ptr >> 8 * 2;
    target_men_ptr_array[1] = (uint8_t)m_target_mem_ptr >> 8 * 1;
    target_men_ptr_array[2] = (uint8_t)m_target_mem_ptr >> 8 * 0;
    FUNC_FLASH_1_TRANSMIT((uint8_t *)target_men_ptr_array, sizeof(target_men_ptr_array));

    FUNC_FLASH_1_NSS_QUIT();
    FuncFLASH1WaitForWrite();
}

void FuncFLASH1EraseForSector(uint32_t m_target_mem_ptr, uint16_t m_num_to_write)
{
    if (m_target_mem_ptr % 0x001000 != 0)
    {
        m_target_mem_ptr -= m_target_mem_ptr % 0x001000;
        m_target_mem_ptr += 0x001000;
    }

    for (uint16_t count_page = (uint16_t)(m_num_to_write / 0x001000); count_page > 0; count_page--)
    {
        FuncFLASH1EraseForSectorSingle(m_target_mem_ptr);
        m_target_mem_ptr += 0x001000;
        m_num_to_write -= 0x001000;
    }

    if (m_num_to_write > 0)
    {
        FuncFLASH1EraseForSectorSingle(m_target_mem_ptr);
    }
}

void FuncFLASH1WriteForPage(uint8_t *m_buffer_ptr, uint32_t m_target_mem_ptr, uint16_t m_num_to_write)
{
    if (m_num_to_write == 0)
    {
        return;
    }
    if (m_num_to_write > STATUS_FLASH_1_PAGESIZE)
    {
        m_num_to_write = STATUS_FLASH_1_PAGESIZE;
    }
    FuncFLASH1WriteEnable();
    FUNC_FLASH_1_NSS_READY();
    FuncFLASH1Command(COMMD_FLASH_PAGEPROGRAM);

    uint8_t target_men_ptr_array[3] = {0};
    target_men_ptr_array[0] = (uint8_t)m_target_mem_ptr >> 8 * 2;
    target_men_ptr_array[1] = (uint8_t)m_target_mem_ptr >> 8 * 1;
    target_men_ptr_array[2] = (uint8_t)m_target_mem_ptr >> 8 * 0;
    FUNC_FLASH_1_TRANSMIT((uint8_t *)target_men_ptr_array, sizeof(target_men_ptr_array));

    FUNC_FLASH_1_TRANSMIT((uint8_t *)m_buffer_ptr, m_num_to_write);

    FUNC_FLASH_1_NSS_QUIT();
    FuncFLASH1WaitForWrite();
}

void FuncFLASH1Write(uint8_t *m_buffer_ptr, uint32_t m_target_mem_ptr, uint16_t m_num_to_write)
{
    FuncFLASH1EraseForSector(m_target_mem_ptr, m_num_to_write);

    if (m_num_to_write < STATUS_FLASH_1_PAGESIZE - (m_target_mem_ptr % STATUS_FLASH_1_PAGESIZE))
    {
        FuncFLASH1WriteForPage(m_buffer_ptr, m_target_mem_ptr, m_num_to_write);
        m_num_to_write -= m_num_to_write;
    }
    else
    {
        uint16_t temp_num_to_write = STATUS_FLASH_1_PAGESIZE - (m_target_mem_ptr % STATUS_FLASH_1_PAGESIZE);
        FuncFLASH1WriteForPage(m_buffer_ptr, m_target_mem_ptr, temp_num_to_write);
        m_buffer_ptr += temp_num_to_write;
        m_target_mem_ptr += temp_num_to_write;
        m_num_to_write -= temp_num_to_write;
    }

    for (uint16_t count_page = (uint16_t)(m_num_to_write / STATUS_FLASH_1_PAGESIZE); count_page > 0; count_page--)
    {
        FuncFLASH1WriteForPage(m_buffer_ptr, m_target_mem_ptr, STATUS_FLASH_1_PAGESIZE);
        m_buffer_ptr += STATUS_FLASH_1_PAGESIZE;
        m_target_mem_ptr += STATUS_FLASH_1_PAGESIZE;
        m_num_to_write -= STATUS_FLASH_1_PAGESIZE;
    }

    if (m_num_to_write > 0)
    {
        FuncFLASH1WriteForPage(m_buffer_ptr, m_target_mem_ptr, m_num_to_write);
    }
}

void FuncFLASH1Read(uint8_t *m_buffer_ptr, uint32_t m_target_mem_ptr, uint16_t m_num_to_read)
{
    FUNC_FLASH_1_NSS_READY();
    FuncFLASH1Command(COMMD_FLASH_READDATA);

    uint8_t target_men_ptr_array[3] = {0};
    target_men_ptr_array[0] = (uint8_t)m_target_mem_ptr >> 8 * 2;
    target_men_ptr_array[1] = (uint8_t)m_target_mem_ptr >> 8 * 1;
    target_men_ptr_array[2] = (uint8_t)m_target_mem_ptr >> 8 * 0;
    FUNC_FLASH_1_TRANSMIT((uint8_t *)target_men_ptr_array, sizeof(target_men_ptr_array));

    FUNC_FLASH_1_RECEIVE(m_buffer_ptr, m_num_to_read);
    FUNC_FLASH_1_NSS_QUIT();
}

void FuncFLASH1WaitForWrite(void)
{
    FUNC_FLASH_1_NSS_READY();
    uint8_t flag = 0x0;
    uint32_t timeout = CONFIG_FLASH_1_TIMEOUT * (SystemCoreClock / 1000);

    do
    {
        FuncFLASH1Command(COMMD_FLASH_READSTATUSREG);
        FUNC_FLASH_1_RECEIVE((uint8_t *)&flag, sizeof flag);
        if (!timeout--)
        {
            printf("Timeout Flash_1\n");
            FuncErrorAlert();
        }
    } while ((flag & 0x01) == SET);
    FUNC_FLASH_1_NSS_QUIT();
}

void FuncFLASH1WaitForRead(void)
{
    ;
}

/**
 * @description: LCD区段
 */
void InitializeLCD1(void)
{
    InitializeFSMCNORSRAM();

    InitializeLCD1ForPin();
    InitializeLCD1ForConfig();
    /**
     * @description: 初始化命令
     */
    FuncLCD1SetBacklight(STATUS_LCD_BKLIGHT_ENABLE);
    FuncLCD1Reset();

    FuncFSMCCommand(COMMD_LCD_SWRESET);
    HAL_Delay(20);
    FuncFSMCCommand(COMMD_LCD_DISPOFF);
    HAL_Delay(20);
    FuncFSMCCommand(COMMD_LCD_SLPIN);
    HAL_Delay(20);

    FuncFSMCCommand(COMMD_LCD_MADCTL);
    FuncLCD1WriteDataForSingle(0xC0);
    HAL_Delay(5);
    FuncFSMCCommand(COMMD_LCD_COLMOD);
    FuncLCD1WriteDataForSingle(0x55);
    HAL_Delay(5);
    /*ST7789S Frame rate setting*/
    FuncFSMCCommand(COMMD_LCD_PORCTRL);
    FuncLCD1WriteDataForSingle(0x0c);
    FuncLCD1WriteDataForSingle(0x0c);
    FuncLCD1WriteDataForSingle(0x00);
    FuncLCD1WriteDataForSingle(0x33);
    FuncLCD1WriteDataForSingle(0x33);
    HAL_Delay(5);
    FuncFSMCCommand(COMMD_LCD_GCTRL);
    FuncLCD1WriteDataForSingle(0x35);
    HAL_Delay(5);
    /*ST7789S Power setting*/
    FuncFSMCCommand(COMMD_LCD_VCOMS);
    FuncLCD1WriteDataForSingle(0x35);
    FuncFSMCCommand(COMMD_LCD_LCMCTRL);
    FuncLCD1WriteDataForSingle(0x2c);
    FuncFSMCCommand(COMMD_LCD_VDVVREN);
    FuncLCD1WriteDataForSingle(0x01);
    FuncFSMCCommand(COMMD_LCD_VRS);
    FuncLCD1WriteDataForSingle(0x13);
    FuncFSMCCommand(COMMD_LCD_VDVS);
    FuncLCD1WriteDataForSingle(0x20);
    FuncFSMCCommand(COMMD_LCD_FRCTRL2);
    FuncLCD1WriteDataForSingle(0x0f);
    FuncFSMCCommand(COMMD_LCD_REGSEL2);
    FuncLCD1WriteDataForSingle(0x0f);
    FuncFSMCCommand(COMMD_LCD_REGSEL1);
    FuncLCD1WriteDataForSingle(0x08);
    FuncFSMCCommand(COMMD_LCD_WRCACE);
    FuncLCD1WriteDataForSingle(0x90);
    FuncFSMCCommand(COMMD_LCD_PWCTRL1);
    FuncLCD1WriteDataForSingle(0xa4);
    FuncLCD1WriteDataForSingle(0xa1);
    HAL_Delay(5);
    /*ST7789S gamma setting*/
    FuncFSMCCommand(COMMD_LCD_PVGAMCTRL);
    FuncLCD1WriteDataForSingle(0xd0);
    FuncLCD1WriteDataForSingle(0x00);
    FuncLCD1WriteDataForSingle(0x06);
    FuncLCD1WriteDataForSingle(0x09);
    FuncLCD1WriteDataForSingle(0x0b);
    FuncLCD1WriteDataForSingle(0x2a);
    FuncLCD1WriteDataForSingle(0x3c);
    FuncLCD1WriteDataForSingle(0x55);
    FuncLCD1WriteDataForSingle(0x4b);
    FuncLCD1WriteDataForSingle(0x08);
    FuncLCD1WriteDataForSingle(0x16);
    FuncLCD1WriteDataForSingle(0x14);
    FuncLCD1WriteDataForSingle(0x19);
    FuncLCD1WriteDataForSingle(0x20);
    FuncFSMCCommand(COMMD_LCD_NVGAMCTRL);
    FuncLCD1WriteDataForSingle(0xd0);
    FuncLCD1WriteDataForSingle(0x00);
    FuncLCD1WriteDataForSingle(0x06);
    FuncLCD1WriteDataForSingle(0x09);
    FuncLCD1WriteDataForSingle(0x0b);
    FuncLCD1WriteDataForSingle(0x29);
    FuncLCD1WriteDataForSingle(0x36);
    FuncLCD1WriteDataForSingle(0x54);
    FuncLCD1WriteDataForSingle(0x4b);
    FuncLCD1WriteDataForSingle(0x0d);
    FuncLCD1WriteDataForSingle(0x16);
    FuncLCD1WriteDataForSingle(0x14);
    FuncLCD1WriteDataForSingle(0x21);
    FuncLCD1WriteDataForSingle(0x20);
    HAL_Delay(5);
    /* column address control set */
    FuncFSMCCommand(COMMD_LCD_CASET);
    FuncLCD1WriteDataForSingle(0x00FF & ((STATUS_LCD_PIXELWIDTH - 1) >> (8 * 3)));
    FuncLCD1WriteDataForSingle(0x00FF & ((STATUS_LCD_PIXELWIDTH - 1) >> (8 * 2)));
    FuncLCD1WriteDataForSingle(0x00FF & ((STATUS_LCD_PIXELWIDTH - 1) >> (8 * 1))); /*发送高8位*/
    FuncLCD1WriteDataForSingle(0x00FF & ((STATUS_LCD_PIXELWIDTH - 1) >> (8 * 0))); /*发送低8位*/
    HAL_Delay(5);
    /* page address control set */
    FuncFSMCCommand(COMMD_LCD_RASET);
    FuncLCD1WriteDataForSingle(0x00FF & ((STATUS_LCD_PIXELHEIGHT - 1) >> (8 * 3)));
    FuncLCD1WriteDataForSingle(0x00FF & ((STATUS_LCD_PIXELHEIGHT - 1) >> (8 * 2)));
    FuncLCD1WriteDataForSingle(0x00FF & ((STATUS_LCD_PIXELHEIGHT - 1) >> (8 * 1))); /*发送高8位*/
    FuncLCD1WriteDataForSingle(0x00FF & ((STATUS_LCD_PIXELHEIGHT - 1) >> (8 * 0))); /*发送低8位*/
    HAL_Delay(5);
    /* Sleep Out (11h)  */
    FuncFSMCCommand(COMMD_LCD_SLPOUT); // Exit Sleep
    HAL_Delay(20);
    /* Display ON (29h) */
    FuncFSMCCommand(COMMD_LCD_DISPON); // Display on

    FuncLCD1SetDisplayDirection(STATUS_LCD_DISPLAYDIRECTION_VERTICAL_LEFTTOP_RIGHTBOTTOM);
    FuncLCD1DrawFullScreen(STATUS_LCD_COLOUR_BACKGROUND);
}

static void InitializeLCD1ForPin(void)
{
    FUNC_LCD_PIN_CLK_ENABLE();

    GPIO_InitTypeDef config_lcd_1_gpio;

    config_lcd_1_gpio.Mode = GPIO_MODE_OUTPUT_PP;
    config_lcd_1_gpio.Pull = GPIO_PULLUP;
    config_lcd_1_gpio.Speed = GPIO_SPEED_FREQ_HIGH;

    config_lcd_1_gpio.Pin = PORT_LCD_1_BK_PIN;
    HAL_GPIO_Init(PORT_LCD_1_BK_GROUP, &config_lcd_1_gpio);
    config_lcd_1_gpio.Pin = PORT_LCD_1_RST_PIN;
    HAL_GPIO_Init(PORT_LCD_1_RST_GROUP, &config_lcd_1_gpio);
}

static void InitializeLCD1ForConfig(void)
{
    ;
}

void FuncLCD1Command(Type_Commd_LCD m_commd_lcd)
{
    FuncFSMCCommand(m_commd_lcd);
}

void FuncLCD1WriteDataForSingle(uint16_t m_data_lcd)
{
    FuncFSMCWriteDataForSingle(m_data_lcd);
}

uint16_t FuncLCD1ReadDataForSingle(void)
{
    return FuncFSMCReadDataForSingle();
}

uint32_t FuncLCD1CallbackID(void)
{
    uint32_t result = 0x0;
    FuncLCD1Command(COMMD_LCD_RDDID);

    for (uint8_t count = 0; count < 2; count++)
    {
        FuncLCD1ReadDataForSingle(); /*假读*/
    }
    for (uint8_t count = 0; count < 2; count++)
    {
        result <<= 8;
        result |= FuncLCD1ReadDataForSingle();
    }
    return result;
}

void FuncLCD1Reset(void)
{
    HAL_GPIO_WritePin(PORT_LCD_1_RST_GROUP, PORT_LCD_1_RST_PIN, GPIO_PIN_RESET);
    HAL_Delay(5);
    HAL_GPIO_WritePin(PORT_LCD_1_RST_GROUP, PORT_LCD_1_RST_PIN, GPIO_PIN_SET);
    HAL_Delay(5);
}

void FuncLCD1SetBacklight(Type_Status_LCD_BkLight m_light)
{
    switch (m_light)
    {
    case STATUS_LCD_BKLIGHT_ENABLE:
        HAL_GPIO_WritePin(PORT_LCD_1_BK_GROUP, PORT_LCD_1_BK_PIN, (GPIO_PinState)STATUS_LCD_BKLIGHT_ENABLE);
        break;

    case STATUS_LCD_BKLIGHT_DISABLE:
        HAL_GPIO_WritePin(PORT_LCD_1_BK_GROUP, PORT_LCD_1_BK_PIN, (GPIO_PinState)STATUS_LCD_BKLIGHT_DISABLE);
        break;

    default:
        break;
    }
}

void FuncLCD1SetDisplayDirection(Type_Status_LCD_DisplayDirection m_direction)
{
    FuncFSMCCommand(COMMD_LCD_SLPIN);
    HAL_Delay(20);

    FuncFSMCCommand(COMMD_LCD_MADCTL);
    switch (m_direction)
    {
    case STATUS_LCD_DISPLAYDIRECTION_VERTICAL_LEFTTOP_RIGHTBOTTOM:
        FuncLCD1WriteDataForSingle(0xC0);
        break;

    case STATUS_LCD_DISPLAYDIRECTION_VERTICAL_RIGHTBOTTOM_LEFTTOP:
        FuncLCD1WriteDataForSingle(0x00);
        break;

    case STATUS_LCD_DISPLAYDIRECTION_VERTICAL_LEFTBOTTOM_RIGHTTOP:
        FuncLCD1WriteDataForSingle(0x40);
        break;

    case STATUS_LCD_DISPLAYDIRECTION_VERTICAL_RIGHTTOP_LEFTBOTTOM:
        FuncLCD1WriteDataForSingle(0x80);
        break;

    case STATUS_LCD_DISPLAYDIRECTION_HORIZONTAL_LEFTTOP_RIGHTBOTTOM:
        FuncLCD1WriteDataForSingle(0xA0);
        break;

    case STATUS_LCD_DISPLAYDIRECTION_HORIZONTAL_RIGHTBOTTOM_LEFTTOP:
        FuncLCD1WriteDataForSingle(0x60);
        break;

    case STATUS_LCD_DISPLAYDIRECTION_HORIZONTAL_LEFTBOTTOM_RIGHTTOP:
        FuncLCD1WriteDataForSingle(0xE0);
        break;

    case STATUS_LCD_DISPLAYDIRECTION_HORIZONTAL_RIGHTTOP_LEFTBOTTOM:
        FuncLCD1WriteDataForSingle(0x20);
        break;

    default:
        break;
    }
    HAL_Delay(5);

    FuncFSMCCommand(COMMD_LCD_SLPOUT);
    HAL_Delay(20);
}

void FuncLCD1SetWindow(uint16_t m_point_x, uint16_t m_point_y, uint16_t m_window_width, uint16_t m_window_height)
{
    if (m_point_x >= STATUS_LCD_PIXELWIDTH || m_point_y >= STATUS_LCD_PIXELHEIGHT)
    {
        return;
    }

    FuncLCD1Command(COMMD_LCD_CASET);
    FuncLCD1WriteDataForSingle(0x00FF & (m_point_x >> (8 * 1)));                        /*发送高8位*/
    FuncLCD1WriteDataForSingle(0x00FF & (m_point_x >> (8 * 0)));                        /*发送低8位*/
    FuncLCD1WriteDataForSingle(0x00FF & ((m_point_x + m_window_width - 1) >> (8 * 1))); /*发送高8位*/
    FuncLCD1WriteDataForSingle(0x00FF & ((m_point_x + m_window_width - 1) >> (8 * 0))); /*发送低8位*/

    FuncLCD1Command(COMMD_LCD_RASET);
    FuncLCD1WriteDataForSingle(0x00FF & (m_point_y >> (8 * 1)));                         /*发送高8位*/
    FuncLCD1WriteDataForSingle(0x00FF & (m_point_y >> (8 * 0)));                         /*发送低8位*/
    FuncLCD1WriteDataForSingle(0x00FF & ((m_point_y + m_window_height - 1) >> (8 * 1))); /*发送高8位*/
    FuncLCD1WriteDataForSingle(0x00FF & ((m_point_y + m_window_height - 1) >> (8 * 0))); /*发送低8位*/
}

void FuncLCD1Fill(uint32_t m_num_point, Type_Status_LCD_Colour m_colour)
{
    FuncLCD1Command(COMMD_LCD_RAMWR);
    for (int count = 0; count < m_num_point; count++)
    {
        FuncLCD1WriteDataForSingle((uint16_t)m_colour);
    }
}

void FuncLCD1DrawFullScreen(Type_Status_LCD_Colour m_colour)
{
    FuncLCD1SetWindow(0, 0, STATUS_LCD_PIXELWIDTH, STATUS_LCD_PIXELHEIGHT);
    FuncLCD1Fill(STATUS_LCD_PIXELWIDTH * STATUS_LCD_PIXELHEIGHT, m_colour);
}

void FuncLCD1DrawPoint(uint16_t m_point_x, uint16_t m_point_y, Type_Status_LCD_Colour m_colour)
{
    if (m_point_x >= STATUS_LCD_PIXELWIDTH || m_point_y >= STATUS_LCD_PIXELHEIGHT)
    {
        return;
    }
    FuncLCD1SetWindow(m_point_x, m_point_y, 1, 1);
    FuncLCD1Command(COMMD_LCD_RAMWR);
    FuncLCD1WriteDataForSingle((uint16_t)m_colour);
}

void FuncLCD1DrawLine(uint16_t m_point_x, uint16_t m_point_y, uint16_t m_length, Type_Status_LCD_Colour m_colour, Type_Status_LCD_LineDirection m_direction)
{
    if (m_point_x >= STATUS_LCD_PIXELWIDTH || m_point_y >= STATUS_LCD_PIXELHEIGHT)
    {
        return;
    }

    switch (m_direction)
    {
    case STATUS_LCD_LINEDIRECTION_VERTICAL:
        FuncLCD1SetWindow(m_point_x, m_point_y, 1, m_length);
        break;

    case STATUS_LCD_LINEDIRECTION_HORIZONTAL:
        FuncLCD1SetWindow(m_point_x, m_point_y, m_length, 1);
        break;

    default:
        break;
    }
    FuncLCD1Fill(m_length, m_colour);
}

void FuncLCD1DrawRectangleForCorner(uint16_t m_point_x, uint16_t m_point_y, uint16_t m_width, uint16_t m_height, Type_Status_LCD_Colour m_colour, Type_Status_LCD_Fill m_fill)
{
    if (m_point_x + m_width > STATUS_LCD_PIXELWIDTH || m_point_y + m_height > STATUS_LCD_PIXELHEIGHT)
    {
        return;
    }

    switch (m_fill)
    {
    case STATUS_LCD_FILL_FULL:
        FuncLCD1SetWindow(m_point_x, m_point_y, m_width, m_height);
        FuncLCD1Fill(m_width * m_height, m_colour);
        break;

    case STATUS_LCD_FILL_EMPTY:
        FuncLCD1DrawLine(m_point_x, m_point_y, m_width, m_colour, STATUS_LCD_LINEDIRECTION_HORIZONTAL);
        FuncLCD1DrawLine(m_point_x, m_point_y + m_height, m_width, m_colour, STATUS_LCD_LINEDIRECTION_HORIZONTAL);
        FuncLCD1DrawLine(m_point_x, m_point_y, m_height, m_colour, STATUS_LCD_LINEDIRECTION_VERTICAL);
        FuncLCD1DrawLine(m_point_x + m_width, m_point_y, m_height, m_colour, STATUS_LCD_LINEDIRECTION_VERTICAL);
        break;

    default:
        break;
    }
}

void FuncLCD1DrawRectangleForCenter(uint16_t m_point_x, uint16_t m_point_y, uint16_t m_width, uint16_t m_height, Type_Status_LCD_Colour m_colour, Type_Status_LCD_Fill m_fill)
{
    FuncLCD1DrawRectangleForCorner(m_point_x - (m_width / 2), m_point_y - (m_height / 2), m_width, m_height, m_colour, m_fill);
}

/**
 * @description: 返回某个像素点的颜色
 * @return {*}16位颜色值(5位R|6位G|5位B)，与Type_Status_LCD_Colour遵循相同规则
 */
uint16_t FuncLCD1GetColour(uint16_t m_point_x, uint16_t m_point_y)
{
    if (m_point_x >= STATUS_LCD_PIXELWIDTH || m_point_y >= STATUS_LCD_PIXELHEIGHT)
    {
        return STATUS_LCD_COLOUR_BLACK;
    }

    uint8_t colour_r = 0, colour_g = 0, colour_b = 0;
    uint16_t colour_rg = 0, colour_bb, result = 0;
    FuncLCD1SetWindow(m_point_x, m_point_y, 1, 1);
    FuncLCD1Command(COMMD_LCD_RAMRD);

    FuncLCD1ReadDataForSingle(); /*假读*/
    colour_rg = FuncLCD1ReadDataForSingle();
    colour_r = (uint8_t)((colour_rg >> (8 * 1)) & 0xF8); /*只保留高5位*/
    colour_g = (uint8_t)((colour_rg >> (8 * 0)) & 0xFC); /*只保留高6位*/
    colour_bb = FuncLCD1ReadDataForSingle();
    colour_b = (uint8_t)((colour_bb >> (8 * 1)) & 0xF8); /*只保留高5位*/

    result = ((colour_r << 8) | (colour_g << 3) | (colour_b >> 3));

    return result;
}

void FuncLCD1DrawCharForASCII(uint16_t m_point_x, uint16_t m_point_y, char m_char, Type_Status_LCD_Colour m_colour, Type_Font_ASCII *m_font)
{
    char char_position = m_char - ' ';                                         /*字符在ASCII中的位置*/
    uint8_t char_size = (m_font->width * m_font->height) / 8;                  /*字模所占字节数*/
    char *char_ptr = (char *)(&m_font->font_table[char_position * char_size]); /*字模首个点地址*/

    FuncLCD1SetWindow(m_point_x, m_point_y, m_font->width, m_font->height);
    FuncLCD1Command(COMMD_LCD_RAMWR);
    for (uint8_t count_byte = 0; count_byte < char_size; count_byte++)
    {
        for (uint8_t count_bit = 0; count_bit < 8; count_bit++)
        {
            uint8_t char_point_position_y = m_point_y + ((count_byte * 8 + count_bit) / m_font->width);
            uint8_t char_point_position_x = m_point_x + ((count_byte * 8 + count_bit) % m_font->width);
            uint16_t char_point_colour = FuncLCD1GetColour(char_point_position_x, char_point_position_y);
            FuncLCD1Command(COMMD_LCD_RAMWR);
            if (char_ptr[count_byte] & (0x80 >> count_bit))
            {
                FuncLCD1WriteDataForSingle(m_colour);
            }
            else
            {
                FuncLCD1WriteDataForSingle(char_point_colour);
            }
        }
    }
}

void FuncLCD1DrawStrForASCII(uint16_t m_point_x, uint16_t m_point_y, char *m_str, Type_Status_LCD_Colour m_colour, Type_Font_ASCII *m_font)
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
        FuncLCD1DrawCharForASCII(char_point_x, char_point_y, m_str[count_char], m_colour, m_font);
        char_point_x += m_font->width;
    }
}

/**
 * @description: 电容按键区段
 */
uint16_t V_data_capacitivebutton_threshold = 0;

void InitializeCapacitiveButton1(void)
{
    InitializeTIM5General();

    InitializeCapacitiveButton1ForPin();
    InitializeCapacitiveButton1ForConfig();
}

static void InitializeCapacitiveButton1ForPin(void)
{
    ;
}

static void InitializeCapacitiveButton1ForConfig(void)
{
    ;
}

void FuncCapacitiveButton1Reset(void)
{
    GPIO_InitTypeDef config_capacitive_button_gpio_struct;

    config_capacitive_button_gpio_struct.Mode = GPIO_MODE_OUTPUT_PP;
    config_capacitive_button_gpio_struct.Pull = GPIO_PULLDOWN;
    config_capacitive_button_gpio_struct.Speed = GPIO_SPEED_FREQ_HIGH;

    config_capacitive_button_gpio_struct.Pin = PORT_CAPACITIVEBUTTON_1_PIN;
    HAL_GPIO_Init(PORT_CAPACITIVEBUTTON_1_GROUP, &config_capacitive_button_gpio_struct);

    HAL_GPIO_WritePin(PORT_CAPACITIVEBUTTON_1_GROUP, PORT_CAPACITIVEBUTTON_1_PIN, GPIO_PIN_RESET);
    FUNC_DELAY_US_FOR_ALL(500);

    config_capacitive_button_gpio_struct.Mode = GPIO_MODE_INPUT;
    config_capacitive_button_gpio_struct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PORT_CAPACITIVEBUTTON_1_GROUP, &config_capacitive_button_gpio_struct);

    __HAL_TIM_SET_COUNTER(&V_handle_tim5general, 0);
    V_data_tim5general_ic_ch2.data_period = 0;
    V_data_tim5general_ic_ch2.data_register = 0;
    V_data_tim5general_ic_ch2.flag_start = 0;
}

uint16_t FuncCapacitiveButton1GetPulseWidth(void)
{
    uint16_t result = 0;
    for (int count = 0; count < 10; count++)
    {
        FuncCapacitiveButton1Reset();

        FUNC_WAITSTATUS_TIMEOUT(V_data_tim5general_ic_ch2.flag_start, 1, 10, "ERROR Timeout_CapacitiveButton");

        result += FuncTIM5GeneralGetICValue(PORT_TIM5GENERAL_CHANNEL_2);
    }
    result /= 10;
    return result;
}

void FuncCapacitiveButton1SetThreshold(uint16_t m_threshold)
{
    V_data_capacitivebutton_threshold = m_threshold;
}

Type_Status_CapacitiveButton FuncCapacitiveButton1GetStatus(void)
{
    if (FuncCapacitiveButton1GetPulseWidth() > V_data_capacitivebutton_threshold)
    {
        return STATUS_CAPACITIVEBUTTON_ON;
    }
    else
    {
        return STATUS_CAPACITIVEBUTTON_OFF;
    }
}

/**
 * @description: Others
 */
void FuncErrorAlert(void)
{
    // FuncBEEP1SetStatus(STATUS_BEEP_ON);
    FuncLED1SetColour(STATUS_LED_COLOUR_RED);
    while (1)
        ;
}
