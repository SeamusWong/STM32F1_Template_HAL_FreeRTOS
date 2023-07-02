#ifndef H_WHX_PERIPHERALS_
#define H_WHX_PERIPHERALS_

#include "whx_libraries_all.h"
#include "whx_communicate.h"
#include "whx_on_chip.h"

void SystemClockConfig(void);

/**
 * @description: LED端口配置
 */
#define PORT_LED_1_P1_GROUP GPIOB
#define PORT_LED_1_P1_PIN GPIO_PIN_5

#define PORT_LED_1_P2_GROUP GPIOB
#define PORT_LED_1_P2_PIN GPIO_PIN_0

#define PORT_LED_1_P3_GROUP GPIOB
#define PORT_LED_1_P3_PIN GPIO_PIN_1

#define FUNC_LED_1_PIN_CLK_ENABLE(args) \
    do                                  \
    {                                   \
        __HAL_RCC_GPIOB_CLK_ENABLE();   \
    } while (0U);
#define FUNC_LED_1_PIN_CLK_DISABLE(args) \
    do                                   \
    {                                    \
        __HAL_RCC_GPIOB_CLK_DISABLE();   \
    } while (0U);

/*********************************LED端口配置************************************/

/**
 * @description: LED功能
 */
#define STATUS_LED_ON GPIO_PIN_RESET
#define STATUS_LED_OFF GPIO_PIN_SET

typedef enum
{
    STATUS_LED_COLOUR_RED,
    STATUS_LED_COLOUR_GREEN,
    STATUS_LED_COLOUR_BLUE,
    STATUS_LED_COLOUR_YELLOW,
    STATUS_LED_COLOUR_PURPLE,
    STATUS_LED_COLOUR_CYAN,
    STATUS_LED_COLOUR_WHITE,
    STATUS_LED_COLOUR_BLACK
} Type_Status_LED_Colour;

void InitializeLED1(void);
void InitializeLED1ForPin(void);
void InitializeLED1ForProcotol(void);
void FuncLED1SetColour(Type_Status_LED_Colour m_colour);
Type_Status_LED_Colour FuncLED1ReadColour(void);
void FuncLED1Toggle(void);
/*********************************LED功能************************************/

/**
 * @description: KEY端口配置
 */
#define PORT_KEY_1_GROUP GPIOA
#define PORT_KEY_1_PIN GPIO_PIN_0

#define PORT_KEY_2_GROUP GPIOC
#define PORT_KEY_2_PIN GPIO_PIN_13

#define FUNC_KEY_1_PIN_CLK_ENABLE(args) \
    do                                  \
    {                                   \
        __HAL_RCC_GPIOA_CLK_ENABLE();   \
    } while (0U);
#define FUNC_KEY_1_PIN_CLK_DISABLE(args) \
    do                                   \
    {                                    \
        __HAL_RCC_GPIOA_CLK_DISABLE();   \
    } while (0U);

#define FUNC_KEY_2_PIN_CLK_ENABLE(args) \
    do                                  \
    {                                   \
        __HAL_RCC_GPIOC_CLK_ENABLE();   \
    } while (0U);
#define FUNC_KEY_2_PIN_CLK_DISABLE(args) \
    do                                   \
    {                                    \
        __HAL_RCC_GPIOC_CLK_DISABLE();   \
    } while (0U);
/*********************************KEY端口配置************************************/

/**
 * @description: KEY功能
 */
typedef enum
{
    STATUS_KEY_ON = GPIO_PIN_SET,
    STATUS_KEY_OFF = GPIO_PIN_RESET
} Type_Status_KEY;

void InitializeKEY1(void);
void InitializeKEY1ForPin(void);
void InitializeKEY1ForProcotol(void);
Type_Status_KEY FuncKEY1ReadStatus(void);

void InitializeKEY2(void);
void InitializeKEY2ForPin(void);
void InitializeKEY2ForProcotol(void);
Type_Status_KEY FuncKEY2ReadStatus(void);
/*********************************KEY功能************************************/

/**
 * @description: BEEP端口配置
 */
#define PORT_BEEP_1_GROUP GPIOC
#define PORT_BEEP_1_PIN GPIO_PIN_0

#define FUNC_BEEP_1_PIN_CLK_ENABLE(args) \
    do                                   \
    {                                    \
        __HAL_RCC_GPIOC_CLK_ENABLE();    \
    } while (0U);
#define FUNC_BEEP_1_PIN_CLK_DISABLE(args) \
    do                                    \
    {                                     \
        __HAL_RCC_GPIOC_CLK_DISABLE();    \
    } while (0U);
/*********************************BEEP端口配置************************************/

/**
 * @description: BEEP功能
 */
typedef enum
{
    STATUS_BEEP_ON = GPIO_PIN_SET,
    STATUS_BEEP_OFF = GPIO_PIN_RESET
} Type_Status_BEEP;

void InitializeBEEP1(void);
void InitializeBEEP1ForPin(void);
void InitializeBEEP1ForProcotol(void);
void FuncBEEP1SetStatus(Type_Status_BEEP m_status_beep);
/*********************************BEEP功能************************************/

/**
 * @description: EEPROM端口配置
 */
#define PORT_EEPROM_1_SCL_GROUP PORT_I2C_1_SCL_GROUP
#define PORT_EEPROM_1_SCL_PIN PORT_I2C_1_SCL_PIN

#define PORT_EEPROM_1_SDA_GROUP PORT_I2C_1_SDA_GROUP
#define PORT_EEPROM_1_SDA_PIN PORT_I2C_1_SDA_PIN

#define FUNC_EEPROM_1_PIN_CLK_ENABLE(args) \
    do                                     \
    {                                      \
        FUNC_IIC1_PIN_CLK_ENABLE();        \
    } while (0U);
#define FUNC_EEPROM_1_PIN_CLK_DISABLE(args) \
    do                                      \
    {                                       \
        FUNC_IIC1_PIN_CLK_DISABLE();        \
    } while (0U);

#define FUNC_EEPROM_1_CLK_ENABLE(args) FUNC_IIC1_CLK_ENABLE(args)
#define FUNC_EEPROM_1_CLK_DISABLE(args) FUNC_IIC1_CLK_DISABLE(args)

#define PORT_EEPROM_1_ADDRESS_0 0xA0 /*设备总线地址*/

#define STATUS_EEPROM_1_TOTALSIZE 256 /*总容量*/
#define STATUS_EEPROM_1_PAGESIZE 8    /*页大小*/
/*********************************EEPROM端口配置************************************/

/**
 * @description: EEPROM功能
 */
void InitializeEEPROM1(void);
void InitializeEEPROM1ForPin(void);
void InitializeEEPROM1ForProtocol(void);
/**
 * @description:EEPROM指定位置写入
 * @param {uint8_t} *m_buffer_ptr 准备发送的缓冲区指针
 * @param {uint8_t} m_target_mem_ptr 目标内部存储器地址
 * @param {uint8_t} m_num_to_write  要写入的字节数
 * @return {*}
 */
void FuncEEPROM1Write(uint8_t *m_buffer_ptr, uint8_t m_target_mem_ptr, uint16_t m_num_to_write);
/**
 * @description:EEPROM指定位置读取
 * @param {uint8_t} *m_buffer_ptr 准备接受的缓冲区指针
 * @param {uint8_t} m_target_mem_ptr 目标内部存储器地址
 * @param {uint8_t} m_num_to_read  要读取的字节数
 * @return {*}
 */
void FuncEEPROM1Read(uint8_t *m_buffer_ptr, uint8_t m_target_mem_ptr, uint16_t m_num_to_read);
void FuncEEPROM1ClearAll(void);
/*********************************EEPROM功能************************************/

/**
 * @description: FLASH端口配置
 */
#define PORT_FLASH_1_SCL_GROUP PORT_SPI1_SCL_GROUP
#define PORT_FLASH_1_SCL_PIN PORT_SPI1_SCL_PIN

#define PORT_FLASH_1_MISO_GROUP PORT_SPI1_MISO_GROUP
#define PORT_FLASH_1_MISO_PIN PORT_SPI1_MISO_PIN

#define PORT_FLASH_1_MOSI_GROUP PORT_SPI1_MOSI_GROUP
#define PORT_FLASH_1_MOSI_PIN PORT_SPI1_MOSI_PIN

#define PORT_FLASH_1_NSS_GROUP GPIOA /*片选引脚，有几个外设从机就应该有几个NSS，也叫CS*/
#define PORT_FLASH_1_NSS_PIN GPIO_PIN_4

#define FUNC_FLASH_1_PIN_CLK_ENABLE(args) \
    do                                    \
    {                                     \
        __HAL_RCC_GPIOA_CLK_ENABLE();     \
        FUNC_SPI1_PIN_CLK_ENABLE();       \
    } while (0U);
#define FUNC_FLASH_1_PIN_CLK_DISABLE(args) \
    do                                     \
    {                                      \
        __HAL_RCC_GPIOA_CLK_DISABLE();     \
        FUNC_SPI1_PIN_CLK_DISABLE();       \
    } while (0U);

#define STATUS_FLASH_1_ID 0xEF4017 /*硬件ID，代表了出厂型号*/
#define STATUS_FLASH_1_PAGESIZE 256

#define CONFIG_FLASH_1_TIMEOUT 1000 /*存储超时*/
/*********************************FLASH端口配置************************************/

/**
 * @description: FLASH指令编码表
 */
typedef enum
{
    COMMD_FLASH_WRITEENABLE = 0x06,
    COMMD_FLASH_WRITEDISABLE = 0x04,
    COMMD_FLASH_READSTATUSREG = 0x05,
    COMMD_FLASH_WRITESTATUSREG = 0x01,
    COMMD_FLASH_READDATA = 0x03,
    COMMD_FLASH_FASTREADDATA = 0x0B,
    COMMD_FLASH_FASTREADDUAL = 0x3B,
    COMMD_FLASH_PAGEPROGRAM = 0x02,
    COMMD_FLASH_BLOCKERASE = 0xD8,
    COMMD_FLASH_SECTORERASE = 0x20,
    COMMD_FLASH_CHIPERASE = 0xC7,
    COMMD_FLASH_POWERDOWN = 0xB9,
    COMMD_FLASH_RELEASEPOWERDOWN = 0xAB,
    COMMD_FLASH_DEVICEID = 0xAB,
    COMMD_FLASH_MANUFACTDEVICEID = 0x90,
    COMMD_FLASH_JEDECDEVICEID = 0x9F
} Type_Commd_FLASH;

/*********************************FLASH指令编码表************************************/

/**
 * @description: FLASH功能
 */
#define FUNC_FLASH_1_TRANSMIT(m_buffer_ptr, m_num_to_write) FuncSPI1Transmit(m_buffer_ptr, m_num_to_write);
#define FUNC_FLASH_1_RECEIVE(m_buffer_ptr, m_num_to_read) FuncSPI1Receive(m_buffer_ptr, m_num_to_read)
#define FUNC_FLASH_1_NSS_READY(args) FuncSPI1NSSReady(PORT_FLASH_1_NSS_GROUP,PORT_FLASH_1_NSS_PIN)
#define FUNC_FLASH_1_NSS_QUIT(args) FuncSPI1NSSQuit(PORT_FLASH_1_NSS_GROUP, PORT_FLASH_1_NSS_PIN)

void InitializeFLASH1(void);
void InitializeFLASH1ForPin(void);
void InitializeFLASH1ForProtocol(void);
void FuncFLASH1Command(Type_Commd_FLASH m_commd_flash);
uint32_t FuncFLASH1CallbackID(void);
void FuncFLASH1WriteEnable(void);
void FuncFLASH1EraseForSectorSingle(uint32_t m_target_mem_ptr);
void FuncFLASH1EraseForSector(uint32_t m_target_mem_ptr, uint16_t m_num_to_write);
void FuncFLASH1WriteForPage(uint8_t *m_buffer_ptr, uint32_t m_target_mem_ptr, uint16_t m_num_to_write);
void FuncFLASH1Write(uint8_t *m_buffer_ptr, uint32_t m_target_mem_ptr, uint16_t m_num_to_write);
void FuncFLASH1Read(uint8_t *m_buffer_ptr, uint32_t m_target_mem_ptr, uint16_t m_num_to_read);
void FuncFLASH1WaitForWrite(void);
void FuncFLASH1WaitForRead(void);
/*********************************FLASH功能************************************/

/**
 * @description: LCD端口配置
 */
#define PORT_LCD_CS_GROUP PORT_FSMC_NE_4_GROUP /*片选，选择NOR/SRAM块*/
#define PORT_LCD_CS_PIN PORT_FSMC_NE_4_PIN     /*片选，选择NOR/SRAM块*/

#define PORT_LCD_NSS_GROUP PORT_LCD_CS_GROUP /*CS改名字*/
#define PORT_LCD_NSS_PIN PORT_LCD_CS_PIN     /*CS改名字*/

#define PORT_LCD_RST_GROUP GPIOG     /*复位引脚*/
#define PORT_LCD_RST_PIN GPIO_PIN_11 /*复位引脚*/

#define PORT_LCD_BK_GROUP GPIOG    /*背光引脚*/
#define PORT_LCD_BK_PIN GPIO_PIN_6 /*背光引脚*/

#define PORT_LCD_RS_GROUP PORT_FSMC_A23_GROUP /*DATA/COMMAND引脚*/
#define PORT_LCD_RS_PIN PORT_FSMC_A23_PIN     /*DATA/COMMAND引脚*/

#define PORT_LCD_WR_GROUP PORT_FSMC_NWE_GROUP /*写使能*/
#define PORT_LCD_WR_PIN PORT_FSMC_NWE_PIN     /*写使能*/

#define PORT_LCD_RD_GROUP PORT_FSMC_NOE_GROUP /*读使能*/
#define PORT_LCD_RD_PIN PORT_FSMC_NOE_PIN     /*读使能*/

#define PORT_LCD_DB0_GROUP PORT_FSMC_D0_GROUP /*数据信号线*/
#define PORT_LCD_DB0_PIN PORT_FSMC_D0_PIN     /*数据信号线*/

#define PORT_LCD_DB1_GROUP PORT_FSMC_D1_GROUP /*数据信号线*/
#define PORT_LCD_DB1_PIN PORT_FSMC_D1_PIN     /*数据信号线*/

#define PORT_LCD_DB2_GROUP PORT_FSMC_D2_GROUP
#define PORT_LCD_DB2_PIN PORT_FSMC_D2_PIN

#define PORT_LCD_DB3_GROUP PORT_FSMC_D3_GROUP
#define PORT_LCD_DB3_PIN PORT_FSMC_D3_PIN

#define PORT_LCD_DB4_GROUP PORT_FSMC_D4_GROUP
#define PORT_LCD_DB4_PIN PORT_FSMC_D4_PIN

#define PORT_LCD_DB5_GROUP PORT_FSMC_D5_GROUP
#define PORT_LCD_DB5_PIN PORT_FSMC_D5_PIN

#define PORT_LCD_DB6_GROUP PORT_FSMC_D6_GROUP
#define PORT_LCD_DB6_PIN PORT_FSMC_D6_PIN

#define PORT_LCD_DB7_GROUP PORT_FSMC_D7_GROUP
#define PORT_LCD_DB7_PIN PORT_FSMC_D7_PIN

#define PORT_LCD_DB8_GROUP PORT_FSMC_D8_GROUP
#define PORT_LCD_DB8_PIN PORT_FSMC_D8_PIN

#define PORT_LCD_DB9_GROUP PORT_FSMC_D9_GROUP
#define PORT_LCD_DB9_PIN PORT_FSMC_D9_PIN

#define PORT_LCD_DB10_GROUP PORT_FSMC_D10_GROUP
#define PORT_LCD_DB10_PIN PORT_FSMC_D10_PIN

#define PORT_LCD_DB11_GROUP PORT_FSMC_D11_GROUP
#define PORT_LCD_DB11_PIN PORT_FSMC_D11_PIN

#define PORT_LCD_DB12_GROUP PORT_FSMC_D12_GROUP
#define PORT_LCD_DB12_PIN PORT_FSMC_D12_PIN

#define PORT_LCD_DB13_GROUP PORT_FSMC_D13_GROUP
#define PORT_LCD_DB13_PIN PORT_FSMC_D13_PIN

#define PORT_LCD_DB14_GROUP PORT_FSMC_D14_GROUP
#define PORT_LCD_DB14_PIN PORT_FSMC_D14_PIN

#define PORT_LCD_DB15_GROUP PORT_FSMC_D15_GROUP
#define PORT_LCD_DB15_PIN PORT_FSMC_D15_PIN

#define STATUS_LCD_PIXELWIDTH 240  /*屏幕宽度*/
#define STATUS_LCD_PIXELHEIGHT 320 /*屏幕高度*/

#define FUNC_LCD_PIN_ALL_CLK_ENABLE(args) FUNC_FSMC_PIN_ALL_CLK_ENABLE(args)

/*********************************LCD端口配置************************************/

/**
 * @description: LCD功能(本LCD控制芯片为ST7789V)
 */
typedef enum
{
    COMMD_LCD_NOP = 0x00,
    COMMD_LCD_SWRESET = 0x01,   /* Software Reset */
    COMMD_LCD_RDDID = 0x04,     /* Read Display ID */
    COMMD_LCD_RDDST = 0x09,     /* Read Display Status */
    COMMD_LCD_RDDPM = 0x0A,     /* Read Display Power Mode */
    COMMD_LCD_RDDMADCTL = 0x0B, /* Read Display MADCTL */
    COMMD_LCD_RDDCOLMOD = 0x0C, /* Read Display Pixel Format */
    COMMD_LCD_RDDIM = 0x0D,     /* Read Display Image Mode */
    COMMD_LCD_RDDSM = 0x0E,     /* Read Display Signal Mode */
    COMMD_LCD_RDDSDR = 0x0F,    /* Read Display Self-Diagnostic Result */
    COMMD_LCD_SLPIN = 0x10,     /* Sleep in */
    COMMD_LCD_SLPOUT = 0x11,    /* Sleep Out */
    COMMD_LCD_PTLON = 0x12,     /* Partial Display Mode On */
    COMMD_LCD_NORON = 0x13,     /* Normal Display Mode On */
    COMMD_LCD_INVOFF = 0x20,    /* Display Inversion Off */
    COMMD_LCD_INVON = 0x21,     /* Display Inversion On */
    COMMD_LCD_GAMSET = 0x26,    /* Gamma Set */
    COMMD_LCD_DISPOFF = 0x28,   /* Display Off */
    COMMD_LCD_DISPON = 0x29,    /* Display On */
    COMMD_LCD_CASET = 0x2A,     /* Column Address Set */
    COMMD_LCD_RASET = 0x2B,     /* Row Address Set */
    COMMD_LCD_RAMWR = 0x2C,     /* Memory Write */
    COMMD_LCD_RAMRD = 0x2E,     /* Memory Read */
    COMMD_LCD_PTLAR = 0x30,     /* Partial Area */
    COMMD_LCD_VSCRDEF = 0x33,   /* Vertical Scrolling Definition */
    COMMD_LCD_TEOFF = 0x34,     /* Tearing Effect Line OFF */
    COMMD_LCD_TEON = 0x35,      /* Tearing Effect Line On */
    COMMD_LCD_MADCTL = 0x36,    /* Memory Data Access Control */
    COMMD_LCD_VSCSAD = 0x37,    /* Vertical Scroll Start Address of RAM */
    COMMD_LCD_IDMOFF = 0x38,    /* Idle Mode Off */
    COMMD_LCD_IDMON = 0x39,     /* Idle mode on */
    COMMD_LCD_COLMOD = 0x3A,    /* Interface Pixel Format */
    COMMD_LCD_WRMEMC = 0x3C,    /* Write Memory Continue */
    COMMD_LCD_RDMEMC = 0x3E,    /* Read Memory Continue */
    COMMD_LCD_STE = 0x44,       /* Set Tear Scanline */
    COMMD_LCD_GSCAN = 0x45,     /* Get Scanline */
    COMMD_LCD_WRDISBV = 0x51,   /* Write Display Brightness */
    COMMD_LCD_RDDISBV = 0x52,   /* Read Display Brightness Value */
    COMMD_LCD_WRCTRLD = 0x53,   /* Write CTRL Display */
    COMMD_LCD_RDCTRLD = 0x54,   /* Read CTRL Value Display */
    COMMD_LCD_WRCACE = 0x55,    /* Write Content Adaptive Brightness Control and Color Enhancement */
    COMMD_LCD_RDCABC = 0x56,    /* Read Content Adaptive Brightness Control */
    COMMD_LCD_WRCABCMB = 0x5E,  /* Write CABC Minimum Brightness */
    COMMD_LCD_RDCABCMB = 0x5F,  /* Read CABC Minimum Brightness */
    COMMD_LCD_RDABCSDR = 0x68,  /* Read Automatic Brightness Control Self-Diagnostic Result */
    COMMD_LCD_RDID1 = 0xDA,     /* Read ID1 */
    COMMD_LCD_RDID2 = 0xDB,     /* Read ID2 */
    COMMD_LCD_RDID3 = 0xDC,     /* Read ID3 */

    COMMD_LCD_RAMCTRL = 0xB0,   /* RAM Control */
    COMMD_LCD_RGBCTRL = 0xB1,   /* RGB Interface Control */
    COMMD_LCD_PORCTRL = 0xB2,   /* Porch Setting */
    COMMD_LCD_FRCTRL1 = 0xB3,   /* Frame Rate Control 1 (In partial mode/ idle colors) */
    COMMD_LCD_GCTRL = 0xB7,     /* Gate Control */
    COMMD_LCD_DGMEN = 0xBA,     /* Digital Gamma Enable */
    COMMD_LCD_VCOMS = 0xBB,     /* VCOM Setting */
    COMMD_LCD_LCMCTRL = 0xC0,   /* LCM Control */
    COMMD_LCD_IDSET = 0xC1,     /* Code Setting */
    COMMD_LCD_VDVVREN = 0xC2,   /* VDV and VRH Command Enable */
    COMMD_LCD_VRS = 0xC3,       /* VRH Set */
    COMMD_LCD_VDVS = 0xC4,      /* VDV Set */
    COMMD_LCD_VCMOFSET = 0xC5,  /* VCOM Offset Set */
    COMMD_LCD_FRCTRL2 = 0xC6,   /* Frame Rate Control in Normal Mode */
    COMMD_LCD_CABCCTRL = 0xC7,  /* CABC Control */
    COMMD_LCD_REGSEL1 = 0xC8,   /* Register Value Selection 1 */
    COMMD_LCD_REGSEL2 = 0xCA,   /* Register Value Selection 2 */
    COMMD_LCD_PWMFRSEL = 0xCC,  /* PWM Frequency Selection */
    COMMD_LCD_PWCTRL1 = 0xD0,   /* Power Control 1 */
    COMMD_LCD_VAPVANEN = 0xD2,  /* Enable VAP/VAN signal output */
    COMMD_LCD_CMD2EN = 0xDF,    /* Command 2 Enable */
    COMMD_LCD_PVGAMCTRL = 0xE0, /* Positive Voltage Gamma Control */
    COMMD_LCD_NVGAMCTRL = 0xE1, /* Negative Voltage Gamma Control */
    COMMD_LCD_DGMLUTR = 0xE2,   /* Digital Gamma Look-up Table for Red */
    COMMD_LCD_DGMLUTB = 0xE3,   /* Digital Gamma Look-up Table for Blue */
    COMMD_LCD_GATECTRL = 0xE4,  /* Gate Control */
    COMMD_LCD_SPI2EN = 0xE7,    /* SPI2 Enable */
    COMMD_LCD_PWCTRL2 = 0xE8,   /* Power Control 2 */
    COMMD_LCD_EQCTRL = 0xE9,    /* Equalize time control */
    COMMD_LCD_PROMCTRL = 0xEC,  /* Program Mode Control */
    COMMD_LCD_PROMEN = 0xFA,    /* Program Mode Enable */
    COMMD_LCD_NVMSET = 0xFC,    /* NVM Setting */
    COMMD_LCD_PROMACT = 0xFE    /* Program action */

    // COMMD_LCD_DEVICEID = 0x04,
    // COMMD_LCD_SETGRAMDIRECTION = 0x36,
    // COMMD_LCD_SETX = 0x2A,
    // COMMD_LCD_SETY = 0x2B,
    // COMMD_LCD_GRAMWRITE = 0x2C,
    // COMMD_LCD_GRAMREAD = 0x2E,
} Type_Commd_LCD;

typedef enum
{
    STATUS_LCD_COLOUR_WHITE = 0xFFFF,
    STATUS_LCD_COLOUR_BLACK = 0x0000,
    STATUS_LCD_COLOUR_GREY = 0xF7DE,
    STATUS_LCD_COLOUR_BLUE = 0x001F,
    STATUS_LCD_COLOUR_BABYBLUE = 0x051F,
    STATUS_LCD_COLOUR_RED = 0xF800,
    STATUS_LCD_COLOUR_MAGENTA = 0xF81F, /*洋红色*/
    STATUS_LCD_COLOUR_GREEN = 0x07E0,
    STATUS_LCD_COLOUR_CYAN = 0x7FFF,
    STATUS_LCD_COLOUR_YELLOW = 0xFFE0,
    STATUS_LCD_COLOUR_BRED = 0xF81F,
    STATUS_LCD_COLOUR_GRED = 0xFFE0,
    STATUS_LCD_COLOUR_GBLUE = 0x07FF
} Type_Status_LCD_Colour;
#define STATUS_LCD_COLOUR_BACKGROUND ((Type_Status_LCD_Colour)STATUS_LCD_COLOUR_BLACK)

typedef enum
{
    STATUS_LCD_LIGHT_DISABLE = 0,
    STATUS_LCD_LIGHT_ENABLE = !STATUS_LCD_LIGHT_DISABLE
} Type_Status_LCD_Light;

typedef enum
{
    STATUS_LCD_DISPLAYDIRECTION_VERTICAL_LEFTTOP_RIGHTBOTTOM,
    STATUS_LCD_DISPLAYDIRECTION_VERTICAL_RIGHTBOTTOM_LEFTTOP,
    STATUS_LCD_DISPLAYDIRECTION_VERTICAL_LEFTBOTTOM_RIGHTTOP,
    STATUS_LCD_DISPLAYDIRECTION_VERTICAL_RIGHTTOP_LEFTBOTTOM,

    STATUS_LCD_DISPLAYDIRECTION_HORIZONTAL_LEFTTOP_RIGHTBOTTOM,
    STATUS_LCD_DISPLAYDIRECTION_HORIZONTAL_RIGHTBOTTOM_LEFTTOP,
    STATUS_LCD_DISPLAYDIRECTION_HORIZONTAL_LEFTBOTTOM_RIGHTTOP,
    STATUS_LCD_DISPLAYDIRECTION_HORIZONTAL_RIGHTTOP_LEFTBOTTOM
} Type_Status_LCD_DisplayDirection;

typedef enum
{
    STATUS_LCD_LINEDIRECTION_VERTICAL,
    STATUS_LCD_LINEDIRECTION_HORIZONTAL
} Type_Status_LCD_LineDirection;

typedef enum
{
    STATUS_LCD_LINEFILL_EMPTY,
    STATUS_LCD_LINEFILL_FULL
} Type_Status_LCD_LineFill;

void InitializeLCD(void);
void InitializeLCDForGpio(void);
void InitializeLCDForProtocol(void);
void FuncLCDCommand(Type_Commd_LCD m_commd_lcd);
void FuncLCDWriteDataForSingle(uint16_t m_data_lcd);
uint16_t FuncLCDReadDataForSingle(void);
uint32_t FuncLCDCallbackID(void);
void FuncLCDReset(void);
void FuncLCDSetBacklight(Type_Status_LCD_Light m_light);
void FuncLCDSetDisplayDirection(Type_Status_LCD_DisplayDirection m_direction);
void FuncLCDSetWindow(uint16_t m_point_x, uint16_t m_point_y, uint16_t m_window_width, uint16_t m_window_height);
void FuncLCDFill(uint32_t m_num_point, Type_Status_LCD_Colour m_colour);
void FuncLCDDrawFullScreen(Type_Status_LCD_Colour m_colour);
void FuncLCDDrawPoint(uint16_t m_point_x, uint16_t m_point_y, Type_Status_LCD_Colour m_colour);
void FuncLCDDrawLine(uint16_t m_point_x, uint16_t m_point_y, uint16_t m_length, Type_Status_LCD_Colour m_colour, Type_Status_LCD_LineDirection m_direction);
void FuncLCDDrawRectangleForCorner(uint16_t m_point_x, uint16_t m_point_y, uint16_t m_width, uint16_t m_height, Type_Status_LCD_Colour m_colour, Type_Status_LCD_LineFill m_fill);
void FuncLCDDrawRectangleForCenter(uint16_t m_point_x, uint16_t m_point_y, uint16_t m_width, uint16_t m_height, Type_Status_LCD_Colour m_colour, Type_Status_LCD_LineFill m_fill);
/**
 * @description: 返回某个像素点的颜色
 * @return {*}16位颜色值(5位R|6位G|5位B)，与Type_Status_LCD_Colour遵循相同规则
 */
uint16_t FuncLCDReadColour(uint16_t m_point_x, uint16_t m_point_y);
void FuncLCDDrawCharForASCII(uint16_t m_point_x, uint16_t m_point_y, char m_char, Type_Status_LCD_Colour m_colour, Type_Font_ASCII *m_font);
void FuncLCDDrawStrForASCII(uint16_t m_point_x, uint16_t m_point_y, char *m_str, Type_Status_LCD_Colour m_colour, Type_Font_ASCII *m_font);
/*********************************LCD功能************************************/

/**
 * @description: ADC端口配置
 */
#define PORT_ADC1_1_GROUP GPIOC
#define PORT_ADC1_1_PIN GPIO_PIN_1
#define PORT_ADC1_1_CHANNEL ADC_CHANNEL_11 /*通道和引脚具有对应关系,根据ADCx的不同有些变化*/

#define PORT_ADC1_DMACHANNEL DMA1_Channel1 /*ADC1占据DMA1的通道1，是固定的*/

#define FUNC_ADC1_PIN_CLK_ENABLE(args) \
    do                                 \
    {                                  \
        __HAL_RCC_GPIOA_CLK_ENABLE();  \
        __HAL_RCC_GPIOC_CLK_ENABLE();  \
        __HAL_RCC_ADC1_CLK_ENABLE();   \
    } while (0U);

#define STATUS_ADC1_INPUTVOLTAGE ((float)3.3)       /*ADC输入电压范围，由由VREF-、VREF+、VDDA、VSSA、这四个外部引脚决定*/
#define STATUS_ADC1_ACCURACY ((float)(0x1UL << 12)) /*ADC精度，12位就是4096个等级*/
/*********************************ADC端口配置************************************/

/**
 * @description: ADC功能
 */
extern ADC_HandleTypeDef V_config_adc1;

extern uint16_t V_data_adc1_array[7]; /*ADC有最多16个通道，但DMA1只有7个*/

#define CONFIG_ADC1_CLK_PERIPHCLOCKSELECTION RCC_PERIPHCLK_ADC /*ADC外设时钟*/
#define CONFIG_ADC1_CLK_ADCCLOCKSELECTION RCC_ADCPCLK2_DIV6    /*分频因子，最终时钟是72M/因子*/

#define CONFIG_ADC1_CHANNEL_SAMPLINGTIME ADC_SAMPLETIME_55CYCLES_5 /*采样时间（ADC周期）*/

#define CONFIG_ADC1_DATAALIGN ADC_DATAALIGN_RIGHT       /*左/右对齐*/
#define CONFIG_ADC1_SCANCONVMODE ENABLE                 /*多通道/单通道模式*/
#define CONFIG_ADC1_CONTINUOUSCONVMODE ENABLE           /*使能连续转换*/
#define CONFIG_ADC1_NBROFCONVERSION 1                   /*连续转换通道数*/
#define CONFIG_ADC1_NBROFDISCCONVERSION 0               /*不连续转换通道数*/
#define CONFIG_ADC1_DISCONTINUOUSCONVMODE DISABLE       /*使能不连续转换*/
#define CONFIG_ADC1_EXTERNALTRIGCONV ADC_SOFTWARE_START /*转换触发信号选择*/

void InitializeADC1(void);
void InitializeADC1ForGpio(void);
void InitializeADC1ForProtocol(void);
float FuncADC1GetVoltage(uint32_t m_adc_channel);
/*********************************ADC功能************************************/

/**
 * @description: 电容按键端口配置
 */
#define PORT_CAPACITIVEBUTTON_1_GROUP GPIOA
#define PORT_CAPACITIVEBUTTON_1_PIN GPIO_PIN_1

#define FUNC_CAPACITIVEBUTTON_PIN_CLK_ENABLE(args) \
    do                                             \
    {                                              \
        __HAL_RCC_GPIOA_CLK_ENABLE();              \
    } while (0U);

typedef enum
{
    STATUS_CAPACITIVEBUTTON_ON = GPIO_PIN_RESET,
    STATUS_CAPACITIVEBUTTON_OFF = GPIO_PIN_SET
} Type_Status_CapacitiveButton;

extern uint16_t V_data_capacitivebutton_threshold; /*电容按键脉冲阈值*/

void InitializeCapacitiveButton(void);
void InitializeCapacitiveButtonForGpio(void);
void InitializeCapacitiveButtonForProtocol(void);
void FuncCapacitiveButtonReset(void);
uint16_t FuncCapacitiveButtonReadPulseWidth(void);
void FuncCapacitiveButtonSetThreshold(uint16_t m_threshold);
Type_Status_CapacitiveButton FuncCapacitiveButtonStatusRead(void);
/*********************************电容按键端口配置************************************/

/**
 * @description: Others
 */
#define FUNC_CHECK_FOR_HAL(m_func, m_info) \
    do                                     \
    {                                      \
        if (m_func != HAL_OK)              \
        {                                  \
            printf(m_info);                \
            printf("\n");                  \
            FuncErrorAlert();              \
        }                                  \
    } while (0U);

#define FUNC_WAITSTATUS_TIMEOUT(m_func, m_status_wait, m_timeout_ms, m_info) \
    do                                                                       \
    {                                                                        \
        uint32_t timeout = m_timeout_ms * (SystemCoreClock / 1000);          \
        while (m_func != m_status_wait)                                      \
        {                                                                    \
            if (!timeout--)                                                  \
            {                                                                \
                printf(m_info);                                              \
                printf("\n");                                                \
                FuncErrorAlert();                                            \
            }                                                                \
        }                                                                    \
    } while (0U);
void FuncErrorAlert(void);
void FuncDelayMicrosecondsForAll(uint32_t us);
/*********************************Others************************************/

/**
 * @description: END
 */
/*********************************END************************************/

#endif /*H_WHX_PERIPHERALS_*/
