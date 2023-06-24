#ifndef H_WHX_ON_CHIP_
#define H_WHX_ON_CHIP_

#include "whx_libraries_all.h"

/**
 * @description: FSMC端口配置
 */
#define PORT_FSMC_NE_1_GROUP /*FSMC片选引脚，低电平有效，每个片选对应不同内存块*/
#define PORT_FSMC_NE_1_PIN   /*FSMC片选引脚，低电平有效，每个片选对应不同内存块*/

#define PORT_FSMC_NE_2_GROUP
#define PORT_FSMC_NE_2_PIN

#define PORT_FSMC_NE_3_GROUP
#define PORT_FSMC_NE_3_PIN

#define PORT_FSMC_NE_4_GROUP GPIOG     /*FSMC片选引脚，低电平有效，每个片选对应不同内存块*/
#define PORT_FSMC_NE_4_PIN GPIO_PIN_12 /*FSMC片选引脚，低电平有效，每个片选对应不同内存块*/

#define PORT_FSMC_NWE_GROUP GPIOD    /*写信号，上升沿有效*/
#define PORT_FSMC_NWE_PIN GPIO_PIN_5 /*写信号，上升沿有效*/

#define PORT_FSMC_NOE_GROUP GPIOD    /*读信号，上升沿有效*/
#define PORT_FSMC_NOE_PIN GPIO_PIN_4 /*读信号，上升沿有效*/

#define PORT_FSMC_A23_GROUP GPIOE
#define PORT_FSMC_A23_PIN GPIO_PIN_2

#define PORT_FSMC_D0_GROUP GPIOD     /*数据信号线*/
#define PORT_FSMC_D0_PIN GPIO_PIN_14 /*数据信号线*/

#define PORT_FSMC_D1_GROUP GPIOD     /*数据信号线*/
#define PORT_FSMC_D1_PIN GPIO_PIN_15 /*数据信号线*/

#define PORT_FSMC_D2_GROUP GPIOD
#define PORT_FSMC_D2_PIN GPIO_PIN_0

#define PORT_FSMC_D3_GROUP GPIOD
#define PORT_FSMC_D3_PIN GPIO_PIN_1

#define PORT_FSMC_D4_GROUP GPIOE
#define PORT_FSMC_D4_PIN GPIO_PIN_7

#define PORT_FSMC_D5_GROUP GPIOE
#define PORT_FSMC_D5_PIN GPIO_PIN_8

#define PORT_FSMC_D6_GROUP GPIOE
#define PORT_FSMC_D6_PIN GPIO_PIN_9

#define PORT_FSMC_D7_GROUP GPIOE
#define PORT_FSMC_D7_PIN GPIO_PIN_10

#define PORT_FSMC_D8_GROUP GPIOE
#define PORT_FSMC_D8_PIN GPIO_PIN_11

#define PORT_FSMC_D9_GROUP GPIOE
#define PORT_FSMC_D9_PIN GPIO_PIN_12

#define PORT_FSMC_D10_GROUP GPIOE
#define PORT_FSMC_D10_PIN GPIO_PIN_13

#define PORT_FSMC_D11_GROUP GPIOE
#define PORT_FSMC_D11_PIN GPIO_PIN_14

#define PORT_FSMC_D12_GROUP GPIOE
#define PORT_FSMC_D12_PIN GPIO_PIN_15

#define PORT_FSMC_D13_GROUP GPIOD
#define PORT_FSMC_D13_PIN GPIO_PIN_8

#define PORT_FSMC_D14_GROUP GPIOD
#define PORT_FSMC_D14_PIN GPIO_PIN_9

#define PORT_FSMC_D15_GROUP GPIOD
#define PORT_FSMC_D15_PIN GPIO_PIN_10

#define FUNC_FSMC_PIN_ALL_CLK_ENABLE(args) \
    do                                     \
    {                                      \
        __HAL_RCC_FSMC_CLK_ENABLE();       \
        __HAL_RCC_GPIOD_CLK_ENABLE();      \
        __HAL_RCC_GPIOE_CLK_ENABLE();      \
        __HAL_RCC_GPIOF_CLK_ENABLE();      \
        __HAL_RCC_GPIOG_CLK_ENABLE();      \
    } while (0U)
#define FUNC_FSMC_CLK_ENABLE(args) __HAL_RCC_FSMC_CLK_ENABLE()
#define FUNC_FSMC_CLK_DISABLE(args) __HAL_RCC_FSMC_CLK_DISABLE()
/*********************************FSMC端口配置************************************/

/**
 * @description: FSMC功能
 */
extern SRAM_HandleTypeDef V_config_sram; /*SRAM控制句柄*/
extern FSMC_NORSRAM_TimingTypeDef V_config_fsmc_nosram_timing_read;
extern FSMC_NORSRAM_TimingTypeDef V_config_fsmc_nosram_timing_write;

#define CONFIG_FSMC_NORSRAM_NSBANK FSMC_NORSRAM_BANK4                        /*存储区块号*/
#define CONFIG_FSMC_NORSRAM_DATAADDRESSMUX FSMC_DATA_ADDRESS_MUX_DISABLE     /*是否启用地址/数据复用*/
#define CONFIG_FSMC_NORSRAM_MEMORYTYPE FSMC_MEMORY_TYPE_NOR                  /*存储器类型*/
#define CONFIG_FSMC_NORSRAM_MEMORYDATAWIDTH FSMC_NORSRAM_MEM_BUS_WIDTH_16    /*存储器数据宽度*/
#define CONFIG_FSMC_NORSRAM_BURSTACCESSMODE FSMC_BURST_ACCESS_MODE_DISABLE   /*是否使能突发访问,仅对同步突发存储器有效,此处未用到*/
#define CONFIG_FSMC_NORSRAM_WAITSIGNALPOLARITY FSMC_WAIT_SIGNAL_POLARITY_LOW /*设置等待信号的极性,仅在突发模式访问下有用*/
#define CONFIG_FSMC_NORSRAM_WAITSIGNALACTIVE FSMC_WAIT_TIMING_BEFORE_WS      /*存储器是在等待周期之前的一个时钟周期还是等待周期期间使能NWAIT*/
#define CONFIG_FSMC_NORSRAM_WRITEOPERATION FSMC_WRITE_OPERATION_ENABLE       /*存储器写使能*/
#define CONFIG_FSMC_NORSRAM_WAITSIGNAL FSMC_WAIT_SIGNAL_DISABLE              /*是否是能等待状态插入,此处未用到*/
#define CONFIG_FSMC_NORSRAM_EXTENDMODE FSMC_EXTENDED_MODE_DISABLE            /*是否使用使能扩展模式*/
#define CONFIG_FSMC_NORSRAM_ASYNCHRONOUSWAIT FSMC_ASYNCHRONOUS_WAIT_DISABLE  /*是否使能异步传输期间的等待信号,此处未用到*/
#define CONFIG_FSMC_NORSRAM_WRITEBURST FSMC_WRITE_BURST_DISABLE              /*是否使能异步的写突发操作*/
#define CONFIG_FSMC_NORSRAM_PAGESIZE 256                                     /*页大小*/

#define CONFIG_FSMC_NORSRAM_TIMING_READ_ADDRESSSETUPTIME 1            /*地址建立时间*/
#define CONFIG_FSMC_NORSRAM_TIMING_READ_ADDRESSHOLDTIME 0             /*地址保持时间*/
#define CONFIG_FSMC_NORSRAM_TIMING_READ_DATASETUPTIME 15              /*地址建立时间*/
#define CONFIG_FSMC_NORSRAM_TIMING_READ_BUSTURNDURATION 0             /*总线周转阶段持续时间*/
#define CONFIG_FSMC_NORSRAM_TIMING_READ_CLKDIVISION 0                 /*CLK时钟输出信号周期*/
#define CONFIG_FSMC_NORSRAM_TIMING_READ_DATALATENCY 0                 /*同步突发NOR FLASH的数据延迟*/
#define CONFIG_FSMC_NORSRAM_TIMING_READ_ACCESSMODE FSMC_ACCESS_MODE_B /*异步模式配置*/

#define CONFIG_FSMC_NORSRAM_TIMING_WRITE_ADDRESSSETUPTIME 1            /*地址建立时间*/
#define CONFIG_FSMC_NORSRAM_TIMING_WRITE_ADDRESSHOLDTIME 0             /*地址保持时间*/
#define CONFIG_FSMC_NORSRAM_TIMING_WRITE_DATASETUPTIME 3               /*地址建立时间*/
#define CONFIG_FSMC_NORSRAM_TIMING_WRITE_BUSTURNDURATION 0             /*总线周转阶段持续时间*/
#define CONFIG_FSMC_NORSRAM_TIMING_WRITE_CLKDIVISION 0                 /*CLK时钟输出信号周期*/
#define CONFIG_FSMC_NORSRAM_TIMING_WRITE_DATALATENCY 0                 /*同步突发NOR FLASH的数据延迟*/
#define CONFIG_FSMC_NORSRAM_TIMING_WRITE_ACCESSMODE FSMC_ACCESS_MODE_B /*异步模式配置*/
/***************************************************************************************
2^26 =0X0400 0000 = 64MB,每个 BANK 有4*64MB = 256MB
64MB:FSMC_Bank1_NORSRAM1:0X6000 0000 ~ 0X63FF FFFF
64MB:FSMC_Bank1_NORSRAM2:0X6400 0000 ~ 0X67FF FFFF
64MB:FSMC_Bank1_NORSRAM3:0X6800 0000 ~ 0X6BFF FFFF
64MB:FSMC_Bank1_NORSRAM4:0X6C00 0000 ~ 0X6FFF FFFF

选择BANK1-BORSRAM4 连接 TFT，地址范围为0X6C00 0000 ~ 0X6FFF FFFF
FSMC_A23 接LCD的DC(寄存器/数据选择)脚
寄存器基地址 = 0X6C00 0000
RAM基地址 = 0X6D00 0000 = 0X6C00 0000+2^23*2 = 0X6C00 0000 + 0X100 0000 = 0X6D00 0000
当选择不同的地址线时，地址要重新计算
****************************************************************************************/
#define STATUS_FSMC_ADDRESS_COMMD ((uint32_t)FSMC_BANK1_4)                                     /*命令操作地址*/
#define STATUS_FSMC_ADDRESS_DATA ((uint32_t)(STATUS_FSMC_ADDRESS_COMMD + (0x1UL << (23 + 1)))) /*数据操作地址*/

// #define STATUS_FSMC_ADDRESS_COMMD ((uint32_t)0x6C000000)   /*命令操作地址*/
// #define STATUS_FSMC_ADDRESS_DATA ((uint32_t)0x6D000000)  /*数据操作地址*/

void InitializeFSMCNORSRAM(void);
void InitializeFSMCNORSRAMForGPIO(void);
void InitializeFSMCNORSRAMForProtocol(void);
void FuncFSMCCommand(__IO uint16_t m_commd_fsmc);
void FuncFSMCWriteDataForSingle(__IO uint16_t m_data_fsmc);
uint16_t FuncFSMCReadDataForSingle(void);
/*********************************FSMC功能************************************/

/**
 * @description: DMA端口配置
 */
#define PORT_DMA1_CHANNEL PORT_ADC1_DMACHANNEL
#define FUNC_DMA1_CLK_ENABLE(args) __HAL_RCC_DMA1_CLK_ENABLE()
/*********************************DMA端口配置************************************/

/**
 * @description: DMA功能
 */
extern DMA_HandleTypeDef V_config_dma1;

#define CONFIG_DMA1_DIRECTION DMA_PERIPH_TO_MEMORY              /*传输方向*/
#define CONFIG_DMA1_PERIPHINC DMA_PINC_DISABLE                  /*使能外设地址递增*/
#define CONFIG_DMA1_MEMINC DMA_MINC_ENABLE                      /*使能存储器地址递增*/
#define CONFIG_DMA1_PERIPHDATAALIGNMENT DMA_PDATAALIGN_HALFWORD /*外设数据宽度*/
#define CONFIG_DMA1_MEMDATAALIGNMENT DMA_MDATAALIGN_HALFWORD    /*存储器数据宽度*/
#define CONFIG_DMA1_MODE DMA_CIRCULAR                           /*模式选择*/
#define CONFIG_DMA1_PRIORITY DMA_PRIORITY_MEDIUM                /*优先级*/

void InitializeDMA1(void);
void InitializeDMA1ForGPIO(void);
void InitializeDMA1ForProtocol(void);
/*********************************DMA功能************************************/

/**
 * @description: TIM端口配置
 */

/*基本定时器*/
#define FUNC_TIM6BASE_CLK_ENABLE(args) __HAL_RCC_TIM6_CLK_ENABLE()
#define FUNC_TIM6BASE_CLK_DISABLE(args) __HAL_RCC_TIM6_CLK_DISABLE()

/*高级定时器*/
#define PORT_TIM1ADVANCE_OC_PWM1_PORT GPIOC     /*PWM输出引脚*/
#define PORT_TIM1ADVANCE_OC_PWM1_PIN GPIO_PIN_6 /*PWM输出引脚*/

#define PORT_TIM1ADVANCE_OCN_PWM1_PORT GPIOA     /*PWM互补输出引脚*/
#define PORT_TIM1ADVANCE_OCN_PWM1_PIN GPIO_PIN_5 /*PWM互补输出引脚*/

#define PORT_TIM1ADVANCE_CHANNEL TIM_CHANNEL_1 /*TIM输出通道选择，共有4个，前3个有对应的互补通道，与IO相对应*/

#define FUNC_TIM1ADVANCE_PIN_ALL_CLK_ENABLE(args) \
    do                                            \
    {                                             \
        __HAL_RCC_GPIOA_CLK_ENABLE();             \
        __HAL_RCC_GPIOC_CLK_ENABLE();             \
    } while (0U)
#define FUNC_TIM1ADVANCE_CLK_ENABLE(args) __HAL_RCC_TIM1_CLK_ENABLE()
#define FUNC_TIM1ADVANCE_CLK_DISABLE(args) __HAL_RCC_TIM1_CLK_DISABLE()

#define PORT_TIM5GENERAL_IC_PWM1_PORT GPIOA     /*PWM输出引脚*/
#define PORT_TIM5GENERAL_IC_PWM1_PIN GPIO_PIN_0 /*PWM输出引脚*/

#define PORT_TIM5GENERAL_CHANNEL TIM_CHANNEL_1 /*TIM捕获通道选择，共有4个，与IO相对应*/

#define FUNC_TIM5GENERAL_PIN_ALL_CLK_ENABLE(args) \
    do                                            \
    {                                             \
        __HAL_RCC_GPIOA_CLK_ENABLE();             \
    } while (0U)
#define FUNC_TIM5GENERAL_CLK_ENABLE(args) __HAL_RCC_TIM5_CLK_ENABLE()
#define FUNC_TIM5GENERAL_CLK_DISABLE(args) __HAL_RCC_TIM5_CLK_DISABLE()
/*********************************TIM端口配置************************************/

/**
 * @description: TIM功能
 */
extern TIM_HandleTypeDef V_config_tim6base;

/*基本定时器*/
/*实际定时时间为1/(72M/(定时器预分频*定时器周期)),71&1000对应的是1ms*/
#define CONFIG_TIM6_BASE_PRESCALER (72 - 1)             /*定时器预分频，实际时钟频率是72M/(CONFIG_TIM6BASE_PRESCALER + 1)*/
#define CONFIG_TIM6_BASE_COUNTERMODE TIM_COUNTERMODE_UP /*向上/向下计数，Base只有向上*/
#define CONFIG_TIM6_BASE_PERIOD (1000 - 1)              /*定时器周期，即计数到多少产生对应事件和中断*/
#define CONFIG_TIM6_BASE_CLOCKDIVISION NULL             /*时钟分频，设置定时器时钟CK_INT频率与数字滤波器采样时钟频率分频比，Base无效*/
#define CONFIG_TIM6_BASE_REPETIONCOUNTER NULL           /*重复计数器，属于高级控制寄存器专用寄存器位，利用它可以非常容易控制输出PWM的个数*/

#define CONFIG_TIM6_MASTER_OUTPUTTRIGGER TIM_TRGO_RESET          /*TIM 主模式选择(触发输出)*/
#define CONFIG_TIM6_MASTER_SLAVEMODE TIM_MASTERSLAVEMODE_DISABLE /*TIM主/从模式*/

extern TIM_HandleTypeDef V_config_tim5general;

/*高级定时器--基本部分*/
#define CONFIG_TIM1_BASE_PRESCALER (72 - 1)                   /*定时器预分频，实际时钟频率是72M/(CONFIG_TIM1BASE_PRESCALER + 1)*/
#define CONFIG_TIM1_BASE_COUNTERMODE TIM_COUNTERMODE_UP       /*向上/向下计数，Base只有向上*/
#define CONFIG_TIM1_BASE_PERIOD (1000 - 1)                    /*定时器周期，即计数到多少产生对应事件和中断*/
#define CONFIG_TIM1_BASE_CLOCKDIVISION TIM_CLOCKDIVISION_DIV1 /*时钟分频，设置定时器时钟CK_INT频率与数字滤波器采样时钟频率分频比，Base无效*/
#define CONFIG_TIM1_BASE_REPETIONCOUNTER 0                    /*重复计数器，属于高级控制寄存器专用寄存器位，利用它可以非常容易控制输出PWM的个数*/

#define CONFIG_TIM1_CLOCK_CLOCKSOURCE TIM_CLOCKSOURCE_INTERNAL /*时钟源*/
#define CONFIG_TIM1_CLOCK_CLOCKPOLARITY NULL                   /*时钟极性*/
#define CONFIG_TIM1_CLOCK_CLOCKPRESCALER NULL                  /*时钟预分频器*/
#define CONFIG_TIM1_CLOCK_CLOCKFILTER NULL                     /*时钟滤波器*/

#define CONFIG_TIM1_MASTER_OUTPUTTRIGGER TIM_TRGO_RESET          /*TIM 主模式选择(触发输出)*/
#define CONFIG_TIM1_MASTER_SLAVEMODE TIM_MASTERSLAVEMODE_DISABLE /*TIM主/从模式*/

/*高级定时器--比较输出部分*/
/*PWM的最终输出脉冲宽度由：{CONFIG_BASE_PRESCALER，CONFIG_BASE_PERIOD，CONFIG_OC_PULSE}共同控制*/
#define CONFIG_TIM1_OC_OCMODE TIM_OCMODE_PWM1              /*比较输出模式选择，总共有八种，常用的为PWM1/PWM2*/
#define CONFIG_TIM1_OC_OCFASTMODE NULL                     /*比较输出模式快速使能，可以快速使能或者禁能输出*/
#define CONFIG_TIM1_OC_PULSE 500                           /*比较输出脉冲宽度，决定脉冲宽度。可设置范围为0至65535。*/
#define CONFIG_TIM1_OC_OCPOLARITY TIM_OCPOLARITY_HIGH      /*比较输出极性，可选OCx为高电平有效或低电平有效。它决定着定时器通道有效电平*/
#define CONFIG_TIM1_OC_OCNPOLARITY TIM_OCNPOLARITY_HIGH    /*比较互补输出极性，可选OCxN为高电平有效或低电平有效*/
#define CONFIG_TIM1_OC_OCIDLESTATE TIM_OCIDLESTATE_SET     /*空闲状态时通道输出电平设置，即在空闲状态(BDTR_MOE位为0)时，经过死区时间后定时器通道输出高电平或低电平。*/
#define CONFIG_TIM1_OC_OCNIDLESTATE TIM_OCNIDLESTATE_RESET /*空闲状态时互补通道输出电平设置，设定值必须与OCIdleState相反*/

/*高级定时器--捕获输入部分*/
#define CONFIG_TIM1_IC_ICPOLARITY NULL  /*输入捕获边沿触发选择，可选上升沿触发、下降沿触发或边沿跳变触发*/
#define CONFIG_TIM1_IC_ICSELECTION NULL /*输入通道选择，捕获通道ICx的信号可来自三个输入通道，分别 为TIM_ICSELECTION_DIRECTTI、TIM_ICSELECTION_INDIRECTTI或TIM_ICSELECTION_TRC*/
#define CONFIG_TIM1_IC_ICPRESCALER NULL /*输入捕获通道预分频器，可设置1、2、4、8分频*/
#define CONFIG_TIM1_IC_ICFILTER NULL    /*输入捕获滤波器设置，可选设置0x0至0x0F,一般我们不使用滤波器，即设置为0*/

/*高级定时器--断路死区部分*/
#define CONFIG_TIM1_BDT_OFFSTATERUNMODE TIM_OSSR_ENABLE            /*运行模式下的关闭状态选择*/
#define CONFIG_TIM1_BDT_OFFSTATEIDLEMODE TIM_OSSI_ENABLE           /*空闲模式下的关闭状态选择*/
#define CONFIG_TIM1_BDT_LOCKLEVEL TIM_LOCKLEVEL_1                  /*锁定级别配置*/
#define CONFIG_TIM1_BDT_DEADTIME 11                                /*配置死区发生器，定义死区持续时间，可选设置范围为0x0至0xFF*/
#define CONFIG_TIM1_BDT_BREAKSTATE TIM_BREAK_ENABLE                /*断路输入功能选择，可选使能或禁止*/
#define CONFIG_TIM1_BDT_BREAKPOLARITY TIM_BREAKPOLARITY_LOW        /*断路输入通道BRK极性选择，可选高电平有效或低电平有效*/
#define CONFIG_TIM1_BDT_BREAKFILTER 0                              /*断路输入滤波器，定义BRK输入的采样频率和适用于BRK的数字滤波器带宽*/
#define CONFIG_TIM1_BDT_BREAK2STATE NULL                           /*断路2输入功能选择，可选使能或禁止*/
#define CONFIG_TIM1_BDT_BREAK2POLARITY NULL                        /*断路2输入通道BRK2极性选择，可选高电平有效或低电平有效*/
#define CONFIG_TIM1_BDT_BREAK2FILTER NULL                          /*断路2输入滤波器，定义BRK2输入的采样频率和适用于BRK2的数字滤波器带宽*/
#define CONFIG_TIM1_BDT_AUTOMATICOUTPUT TIM_AUTOMATICOUTPUT_ENABLE /*自动输出使能，可选使能或禁止*/

extern TIM_HandleTypeDef V_config_tim5general;

/*高级定时器--基本部分*/
#define CONFIG_TIM5_BASE_PRESCALER (72 - 1)                   /*定时器预分频，实际时钟频率是72M/(CONFIG_TIM5BASE_PRESCALER + 1)*/
#define CONFIG_TIM5_BASE_COUNTERMODE TIM_COUNTERMODE_UP       /*向上/向下计数，Base只有向上*/
#define CONFIG_TIM5_BASE_PERIOD (1000 - 1)                    /*定时器周期，即计数到多少产生对应事件和中断*/
#define CONFIG_TIM5_BASE_CLOCKDIVISION TIM_CLOCKDIVISION_DIV1 /*时钟分频，设置定时器时钟CK_INT频率与数字滤波器采样时钟频率分频比，Base无效*/
#define CONFIG_TIM5_BASE_REPETIONCOUNTER 0                    /*重复计数器，属于高级控制寄存器专用寄存器位，利用它可以非常容易控制输出PWM的个数*/

#define CONFIG_TIM5_CLOCK_CLOCKSOURCE TIM_CLOCKSOURCE_INTERNAL /*时钟源*/
#define CONFIG_TIM5_CLOCK_CLOCKPOLARITY NULL                   /*时钟极性*/
#define CONFIG_TIM5_CLOCK_CLOCKPRESCALER NULL                  /*时钟预分频器*/
#define CONFIG_TIM5_CLOCK_CLOCKFILTER NULL                     /*时钟滤波器*/

#define CONFIG_TIM5_MASTER_OUTPUTTRIGGER TIM_TRGO_RESET          /*TIM 主模式选择(触发输出)*/
#define CONFIG_TIM5_MASTER_SLAVEMODE TIM_MASTERSLAVEMODE_DISABLE /*TIM主/从模式*/

/*高级定时器--比较输出部分*/
/*PWM的最终输出脉冲宽度由：{CONFIG_BASE_PRESCALER，CONFIG_BASE_PERIOD，CONFIG_OC_PULSE}共同控制*/
#define CONFIG_TIM5_OC_OCMODE NULL       /*比较输出模式选择，总共有八种，常用的为PWM1/PWM2*/
#define CONFIG_TIM5_OC_OCFASTMODE NULL   /*比较输出模式快速使能，可以快速使能或者禁能输出*/
#define CONFIG_TIM5_OC_PULSE NULL        /*比较输出脉冲宽度，决定脉冲宽度。可设置范围为0至65535。*/
#define CONFIG_TIM5_OC_OCPOLARITY NULL   /*比较输出极性，可选OCx为高电平有效或低电平有效。它决定着定时器通道有效电平*/
#define CONFIG_TIM5_OC_OCNPOLARITY NULL  /*比较互补输出极性，可选OCxN为高电平有效或低电平有效*/
#define CONFIG_TIM5_OC_OCIDLESTATE NULL  /*空闲状态时通道输出电平设置，即在空闲状态(BDTR_MOE位为0)时，经过死区时间后定时器通道输出高电平或低电平。*/
#define CONFIG_TIM5_OC_OCNIDLESTATE NULL /*空闲状态时互补通道输出电平设置，设定值必须与OCIdleState相反*/

/*高级定时器--捕获输入部分*/
#define CONFIG_TIM5_IC_ICPOLARITY TIM_INPUTCHANNELPOLARITY_RISING /*输入捕获边沿触发选择，可选上升沿触发、下降沿触发或边沿跳变触发*/
#define CONFIG_TIM5_IC_ICSELECTION TIM_ICSELECTION_DIRECTTI       /*输入通道选择，捕获通道ICx的信号可来自三个输入通道，分别 为TIM_ICSELECTION_DIRECTTI、TIM_ICSELECTION_INDIRECTTI或TIM_ICSELECTION_TRC*/
#define CONFIG_TIM5_IC_ICPRESCALER TIM_ICPSC_DIV1                 /*输入捕获通道预分频器，可设置1、2、4、8分频*/
#define CONFIG_TIM5_IC_ICFILTER 0                                 /*输入捕获滤波器设置，可选设置0x0至0x0F,一般我们不使用滤波器，即设置为0*/

/*高级定时器--断路死区部分*/
#define CONFIG_TIM5_BDT_OFFSTATERUNMODE NULL  /*运行模式下的关闭状态选择*/
#define CONFIG_TIM5_BDT_OFFSTATEIDLEMODE NULL /*空闲模式下的关闭状态选择*/
#define CONFIG_TIM5_BDT_LOCKLEVEL NULL        /*锁定级别配置*/
#define CONFIG_TIM5_BDT_DEADTIME NULL         /*配置死区发生器，定义死区持续时间，可选设置范围为0x0至0xFF*/
#define CONFIG_TIM5_BDT_BREAKSTATE NULL       /*断路输入功能选择，可选使能或禁止*/
#define CONFIG_TIM5_BDT_BREAKPOLARITY NULL    /*断路输入通道BRK极性选择，可选高电平有效或低电平有效*/
#define CONFIG_TIM5_BDT_BREAKFILTER NULL      /*断路输入滤波器，定义BRK输入的采样频率和适用于BRK的数字滤波器带宽*/
#define CONFIG_TIM5_BDT_BREAK2STATE NULL      /*断路2输入功能选择，可选使能或禁止*/
#define CONFIG_TIM5_BDT_BREAK2POLARITY NULL   /*断路2输入通道BRK2极性选择，可选高电平有效或低电平有效*/
#define CONFIG_TIM5_BDT_BREAK2FILTER NULL     /*断路2输入滤波器，定义BRK2输入的采样频率和适用于BRK2的数字滤波器带宽*/
#define CONFIG_TIM5_BDT_AUTOMATICOUTPUT NULL  /*自动输出使能，可选使能或禁止*/

typedef struct
{
    uint8_t flag_finish;    /*捕获结束标志位*/
    uint8_t flag_start;     /*捕获开始标志位*/
    uint16_t data_register; /*捕获寄存器当前值*/
    uint16_t data_period;   /*寄存器更新次数*/
} Type_Status_TIM_IC;

extern Type_Status_TIM_IC V_data_tim_ic;

void InitializeTIM6Base(void);
void InitializeTIM6BaseForGPIO(void);
void InitializeTIM6BaseForProtocol(void);

void InitializeTIM1Advance(void);
void InitializeTIM1AdvanceForGPIO(void);
void InitializeTIM1AdvanceForProtocol(void);
void FuncTIM1AdvancePWMStart(void);
void FuncTIM1AdvancePWMStop(void);
void FuncTIM1AdvancePWMChangePulse(uint16_t m_pulse_ms);

void InitializeTIM5General(void);
void InitializeTIM5GeneralForGPIO(void);
void InitializeTIM5GeneralForProtocol(void);
/*********************************TIM功能************************************/

/**
 * @description: Others
 */

/*********************************Others************************************/

#endif /*H_WHX_ON_CHIP_*/
