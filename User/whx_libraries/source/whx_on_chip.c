#include "whx_on_chip.h"

/**
 * @description: FSMC区段
 */
SRAM_HandleTypeDef V_config_sram; /*SRAM控制句柄*/
FSMC_NORSRAM_TimingTypeDef V_config_fsmc_nosram_timing_read;
FSMC_NORSRAM_TimingTypeDef V_config_fsmc_nosram_timing_write;

void InitializeFSMCNORSRAM(void)
{
    InitializeFSMCNORSRAMForGPIO();
    InitializeFSMCNORSRAMForProtocol();
}

void InitializeFSMCNORSRAMForGPIO(void)
{
    FUNC_FSMC_PIN_ALL_CLK_ENABLE();
    GPIO_InitTypeDef config_fsmc_norsram_gpio;

    config_fsmc_norsram_gpio.Mode = GPIO_MODE_AF_PP;
    config_fsmc_norsram_gpio.Pull = GPIO_PULLUP;
    config_fsmc_norsram_gpio.Speed = GPIO_SPEED_FREQ_HIGH;

    config_fsmc_norsram_gpio.Pin = PORT_FSMC_NWE_PIN;
    HAL_GPIO_Init(PORT_FSMC_NWE_GROUP, &config_fsmc_norsram_gpio);
    config_fsmc_norsram_gpio.Pin = PORT_FSMC_NOE_PIN;
    HAL_GPIO_Init(PORT_FSMC_NOE_GROUP, &config_fsmc_norsram_gpio);
    config_fsmc_norsram_gpio.Pin = PORT_FSMC_NE_4_PIN;
    HAL_GPIO_Init(PORT_FSMC_NE_4_GROUP, &config_fsmc_norsram_gpio);
    config_fsmc_norsram_gpio.Pin = PORT_FSMC_A23_PIN;
    HAL_GPIO_Init(PORT_FSMC_A23_GROUP, &config_fsmc_norsram_gpio);
    config_fsmc_norsram_gpio.Pin = PORT_FSMC_D0_PIN;
    HAL_GPIO_Init(PORT_FSMC_D0_GROUP, &config_fsmc_norsram_gpio);
    config_fsmc_norsram_gpio.Pin = PORT_FSMC_D1_PIN;
    HAL_GPIO_Init(PORT_FSMC_D1_GROUP, &config_fsmc_norsram_gpio);
    config_fsmc_norsram_gpio.Pin = PORT_FSMC_D2_PIN;
    HAL_GPIO_Init(PORT_FSMC_D2_GROUP, &config_fsmc_norsram_gpio);
    config_fsmc_norsram_gpio.Pin = PORT_FSMC_D3_PIN;
    HAL_GPIO_Init(PORT_FSMC_D3_GROUP, &config_fsmc_norsram_gpio);
    config_fsmc_norsram_gpio.Pin = PORT_FSMC_D4_PIN;
    HAL_GPIO_Init(PORT_FSMC_D4_GROUP, &config_fsmc_norsram_gpio);
    config_fsmc_norsram_gpio.Pin = PORT_FSMC_D5_PIN;
    HAL_GPIO_Init(PORT_FSMC_D5_GROUP, &config_fsmc_norsram_gpio);
    config_fsmc_norsram_gpio.Pin = PORT_FSMC_D6_PIN;
    HAL_GPIO_Init(PORT_FSMC_D6_GROUP, &config_fsmc_norsram_gpio);
    config_fsmc_norsram_gpio.Pin = PORT_FSMC_D7_PIN;
    HAL_GPIO_Init(PORT_FSMC_D7_GROUP, &config_fsmc_norsram_gpio);
    config_fsmc_norsram_gpio.Pin = PORT_FSMC_D8_PIN;
    HAL_GPIO_Init(PORT_FSMC_D8_GROUP, &config_fsmc_norsram_gpio);
    config_fsmc_norsram_gpio.Pin = PORT_FSMC_D9_PIN;
    HAL_GPIO_Init(PORT_FSMC_D9_GROUP, &config_fsmc_norsram_gpio);
    config_fsmc_norsram_gpio.Pin = PORT_FSMC_D10_PIN;
    HAL_GPIO_Init(PORT_FSMC_D10_GROUP, &config_fsmc_norsram_gpio);
    config_fsmc_norsram_gpio.Pin = PORT_FSMC_D11_PIN;
    HAL_GPIO_Init(PORT_FSMC_D11_GROUP, &config_fsmc_norsram_gpio);
    config_fsmc_norsram_gpio.Pin = PORT_FSMC_D12_PIN;
    HAL_GPIO_Init(PORT_FSMC_D12_GROUP, &config_fsmc_norsram_gpio);
    config_fsmc_norsram_gpio.Pin = PORT_FSMC_D13_PIN;
    HAL_GPIO_Init(PORT_FSMC_D13_GROUP, &config_fsmc_norsram_gpio);
    config_fsmc_norsram_gpio.Pin = PORT_FSMC_D14_PIN;
    HAL_GPIO_Init(PORT_FSMC_D14_GROUP, &config_fsmc_norsram_gpio);
    config_fsmc_norsram_gpio.Pin = PORT_FSMC_D15_PIN;
    HAL_GPIO_Init(PORT_FSMC_D15_GROUP, &config_fsmc_norsram_gpio);
}

void InitializeFSMCNORSRAMForProtocol(void)
{
    FUNC_FSMC_CLK_ENABLE();
    V_config_sram.Instance = FSMC_NORSRAM_DEVICE;          /*寄存器基地址*/
    V_config_sram.Extended = FSMC_NORSRAM_EXTENDED_DEVICE; /*扩展模式寄存器基地址*/
    V_config_sram.Init.NSBank = CONFIG_FSMC_NORSRAM_NSBANK;
    V_config_sram.Init.DataAddressMux = CONFIG_FSMC_NORSRAM_DATAADDRESSMUX;
    V_config_sram.Init.MemoryType = CONFIG_FSMC_NORSRAM_MEMORYTYPE;
    V_config_sram.Init.MemoryDataWidth = CONFIG_FSMC_NORSRAM_MEMORYDATAWIDTH;
    V_config_sram.Init.BurstAccessMode = CONFIG_FSMC_NORSRAM_BURSTACCESSMODE;
    V_config_sram.Init.WaitSignalPolarity = CONFIG_FSMC_NORSRAM_WAITSIGNALPOLARITY;
    V_config_sram.Init.WaitSignalActive = CONFIG_FSMC_NORSRAM_WAITSIGNALACTIVE;
    V_config_sram.Init.WriteOperation = CONFIG_FSMC_NORSRAM_WRITEOPERATION;
    V_config_sram.Init.WaitSignal = CONFIG_FSMC_NORSRAM_WAITSIGNAL;
    V_config_sram.Init.ExtendedMode = CONFIG_FSMC_NORSRAM_EXTENDMODE;
    V_config_sram.Init.AsynchronousWait = CONFIG_FSMC_NORSRAM_ASYNCHRONOUSWAIT;
    V_config_sram.Init.WriteBurst = CONFIG_FSMC_NORSRAM_WRITEBURST;
    // V_config_sram.Init.PageSize = CONFIG_FSMC_NORSRAM_PAGESIZE;

    V_config_fsmc_nosram_timing_read.AddressSetupTime = CONFIG_FSMC_NORSRAM_TIMING_READ_ADDRESSSETUPTIME;
    V_config_fsmc_nosram_timing_read.AddressHoldTime = CONFIG_FSMC_NORSRAM_TIMING_READ_ADDRESSHOLDTIME;
    V_config_fsmc_nosram_timing_read.DataSetupTime = CONFIG_FSMC_NORSRAM_TIMING_READ_DATASETUPTIME;
    V_config_fsmc_nosram_timing_read.BusTurnAroundDuration = CONFIG_FSMC_NORSRAM_TIMING_READ_BUSTURNDURATION;
    V_config_fsmc_nosram_timing_read.CLKDivision = CONFIG_FSMC_NORSRAM_TIMING_READ_CLKDIVISION;
    V_config_fsmc_nosram_timing_read.DataLatency = CONFIG_FSMC_NORSRAM_TIMING_READ_DATALATENCY;
    V_config_fsmc_nosram_timing_read.AccessMode = CONFIG_FSMC_NORSRAM_TIMING_READ_ACCESSMODE;

    V_config_fsmc_nosram_timing_write.AddressSetupTime = CONFIG_FSMC_NORSRAM_TIMING_WRITE_ADDRESSSETUPTIME;
    V_config_fsmc_nosram_timing_write.AddressHoldTime = CONFIG_FSMC_NORSRAM_TIMING_WRITE_ADDRESSHOLDTIME;
    V_config_fsmc_nosram_timing_write.DataSetupTime = CONFIG_FSMC_NORSRAM_TIMING_WRITE_DATASETUPTIME;
    V_config_fsmc_nosram_timing_write.BusTurnAroundDuration = CONFIG_FSMC_NORSRAM_TIMING_WRITE_BUSTURNDURATION;
    V_config_fsmc_nosram_timing_write.CLKDivision = CONFIG_FSMC_NORSRAM_TIMING_WRITE_CLKDIVISION;
    V_config_fsmc_nosram_timing_write.DataLatency = CONFIG_FSMC_NORSRAM_TIMING_WRITE_DATALATENCY;
    V_config_fsmc_nosram_timing_write.AccessMode = CONFIG_FSMC_NORSRAM_TIMING_WRITE_ACCESSMODE;
    FUNC_CHECK_FOR_HAL(HAL_SRAM_Init(&V_config_sram, &V_config_fsmc_nosram_timing_read, &V_config_fsmc_nosram_timing_write), "ERROR SRAM_Init");
}

void FuncFSMCCommand(__IO uint16_t m_command_fsmc)
{
    *((__IO uint16_t *)STATUS_FSMC_ADDRESS_COMMD) = m_command_fsmc;
}

void FuncFSMCWriteDataForSingle(__IO uint16_t m_data_fsmc)
{
    *((__IO uint16_t *)STATUS_FSMC_ADDRESS_DATA) = m_data_fsmc;
}

uint16_t FuncFSMCReadDataForSingle(void)
{
    return *((__IO uint16_t *)STATUS_FSMC_ADDRESS_DATA);
}

/**
 * @description: DMA区段
 */
DMA_HandleTypeDef V_config_dma1;

void InitializeDMA1(void)
{
    InitializeDMA1ForGPIO();
    InitializeDMA1ForProtocol();
}

void InitializeDMA1ForGPIO(void)
{
    ;
}

void InitializeDMA1ForProtocol(void)
{
    FUNC_DMA1_CLK_ENABLE();

    V_config_dma1.Instance = PORT_DMA1_CHANNEL;

    V_config_dma1.Init.Direction = CONFIG_DMA1_DIRECTION;
    V_config_dma1.Init.PeriphInc = CONFIG_DMA1_PERIPHINC;
    V_config_dma1.Init.MemInc = CONFIG_DMA1_MEMINC;
    V_config_dma1.Init.PeriphDataAlignment = CONFIG_DMA1_PERIPHDATAALIGNMENT;
    V_config_dma1.Init.MemDataAlignment = CONFIG_DMA1_MEMDATAALIGNMENT;
    V_config_dma1.Init.Mode = CONFIG_DMA1_MODE;
    V_config_dma1.Init.Priority = CONFIG_DMA1_PRIORITY;
    FUNC_CHECK_FOR_HAL(HAL_DMA_Init(&V_config_dma1), "ERROR DMA_Init");
}

/**
 * @description: TIM区段
 */

/*基本定时器*/
TIM_HandleTypeDef V_config_tim6base;

void InitializeTIM6Base(void)
{
    InitializeTIM6BaseForGPIO();
    InitializeTIM6BaseForProtocol();
}

void InitializeTIM6BaseForGPIO(void)
{
    FUNC_TIM6BASE_CLK_ENABLE();
}

void InitializeTIM6BaseForProtocol(void)
{
    V_config_tim6base.Instance = TIM6;
    V_config_tim6base.Init.Prescaler = CONFIG_TIM6_BASE_PRESCALER;
    V_config_tim6base.Init.CounterMode = CONFIG_TIM6_BASE_COUNTERMODE;
    V_config_tim6base.Init.Period = CONFIG_TIM6_BASE_PERIOD;
    FUNC_CHECK_FOR_HAL(HAL_TIM_Base_Init(&V_config_tim6base), "ERROR TIM6_Init_Base");

    TIM_MasterConfigTypeDef config_tim6base_master;
    config_tim6base_master.MasterOutputTrigger = CONFIG_TIM6_MASTER_OUTPUTTRIGGER;
    config_tim6base_master.MasterSlaveMode = CONFIG_TIM6_MASTER_SLAVEMODE;
    FUNC_CHECK_FOR_HAL(HAL_TIMEx_MasterConfigSynchronization(&V_config_tim6base, &config_tim6base_master), "ERROR TIM6_Init");
}

/*高级定时器*/
TIM_HandleTypeDef V_config_tim1advance;

void InitializeTIM1Advance(void)
{
    InitializeTIM1AdvanceForGPIO();
    InitializeTIM1AdvanceForProtocol();
    FuncTIM1AdvancePWMStart();
}

void InitializeTIM1AdvanceForGPIO(void)
{
    FUNC_TIM1ADVANCE_PIN_CLK_ENABLE();
    GPIO_InitTypeDef config_tim1advance_gpio;

    config_tim1advance_gpio.Mode = GPIO_MODE_AF_PP;
    config_tim1advance_gpio.Pull = GPIO_NOPULL;
    config_tim1advance_gpio.Speed = GPIO_SPEED_FREQ_HIGH;

    config_tim1advance_gpio.Pin = PORT_TIM1ADVANCE_OC_PIN;
    HAL_GPIO_Init(PORT_TIM1ADVANCE_OC_GROUP, &config_tim1advance_gpio);
    config_tim1advance_gpio.Pin = PORT_TIM1ADVANCE_OCN_PIN;
    HAL_GPIO_Init(PORT_TIM1ADVANCE_OCN_GROUP, &config_tim1advance_gpio);
}

void InitializeTIM1AdvanceForProtocol(void)
{
    FUNC_TIM1ADVANCE_CLK_ENABLE();

    V_config_tim1advance.Instance = TIM1;
    V_config_tim1advance.Init.Prescaler = CONFIG_TIM1_BASE_PRESCALER;
    V_config_tim1advance.Init.CounterMode = CONFIG_TIM1_BASE_COUNTERMODE;
    V_config_tim1advance.Init.Period = CONFIG_TIM1_BASE_PERIOD;
    V_config_tim1advance.Init.RepetitionCounter = CONFIG_TIM1_BASE_REPETIONCOUNTER;
    V_config_tim1advance.Init.ClockDivision = CONFIG_TIM1_BASE_CLOCKDIVISION;
    FUNC_CHECK_FOR_HAL(HAL_TIM_Base_Init(&V_config_tim1advance), "ERROR TIM1_Init_Base");

    TIM_ClockConfigTypeDef config_tim1advance_clock;
    config_tim1advance_clock.ClockSource = CONFIG_TIM1_CLOCK_CLOCKSOURCE;
    FUNC_CHECK_FOR_HAL(HAL_TIM_ConfigClockSource(&V_config_tim1advance, &config_tim1advance_clock), "ERROR TIM1_Init_Clock");

    TIM_MasterConfigTypeDef config_tim1advance_master;
    config_tim1advance_master.MasterOutputTrigger = CONFIG_TIM1_MASTER_OUTPUTTRIGGER;
    config_tim1advance_master.MasterSlaveMode = CONFIG_TIM1_MASTER_SLAVEMODE;
    FUNC_CHECK_FOR_HAL(HAL_TIMEx_MasterConfigSynchronization(&V_config_tim1advance, &config_tim1advance_master), "ERROR TIM1_Init_Master");

    TIM_BreakDeadTimeConfigTypeDef config_tim1advance_bdt;
    config_tim1advance_bdt.AutomaticOutput = CONFIG_TIM1_BDT_AUTOMATICOUTPUT;
    config_tim1advance_bdt.BreakFilter = CONFIG_TIM1_BDT_BREAKFILTER;
    config_tim1advance_bdt.BreakPolarity = CONFIG_TIM1_BDT_BREAKPOLARITY;
    config_tim1advance_bdt.BreakState = CONFIG_TIM1_BDT_BREAKSTATE;
    config_tim1advance_bdt.DeadTime = CONFIG_TIM1_BDT_DEADTIME;
    config_tim1advance_bdt.LockLevel = CONFIG_TIM1_BDT_LOCKLEVEL;
    config_tim1advance_bdt.OffStateIDLEMode = CONFIG_TIM1_BDT_OFFSTATEIDLEMODE;
    config_tim1advance_bdt.OffStateRunMode = CONFIG_TIM1_BDT_OFFSTATERUNMODE;
    FUNC_CHECK_FOR_HAL(HAL_TIMEx_ConfigBreakDeadTime(&V_config_tim1advance, &config_tim1advance_bdt), "ERROR TIM1_Init_BreakDeadTime");

    TIM_OC_InitTypeDef config_tim1advance_oc;
    config_tim1advance_oc.OCMode = CONFIG_TIM1_OC_OCMODE;
    config_tim1advance_oc.OCIdleState = CONFIG_TIM1_OC_OCIDLESTATE;
    config_tim1advance_oc.OCNIdleState = CONFIG_TIM1_OC_OCNIDLESTATE;
    config_tim1advance_oc.OCNPolarity = CONFIG_TIM1_OC_OCNPOLARITY;
    config_tim1advance_oc.OCPolarity = CONFIG_TIM1_OC_OCPOLARITY;
    config_tim1advance_oc.Pulse = CONFIG_TIM1_OC_PULSE;
    FUNC_CHECK_FOR_HAL(HAL_TIM_PWM_ConfigChannel(&V_config_tim1advance, &config_tim1advance_oc, PORT_TIM1ADVANCE_CHANNEL_1), "ERROR TIM1_Init_OC");
}

void FuncTIM1AdvancePWMStart(void)
{
    HAL_TIM_PWM_Start(&V_config_tim1advance, PORT_TIM1ADVANCE_CHANNEL_1);
    HAL_TIMEx_PWMN_Start(&V_config_tim1advance, PORT_TIM1ADVANCE_CHANNEL_1);
}

void FuncTIM1AdvancePWMStop(void)
{
    HAL_TIM_PWM_Stop(&V_config_tim1advance, PORT_TIM1ADVANCE_CHANNEL_1);
    HAL_TIMEx_PWMN_Stop(&V_config_tim1advance, PORT_TIM1ADVANCE_CHANNEL_1);
}

void FuncTIM1AdvancePWMChangePulse(uint16_t m_pulse_ms)
{
    FuncTIM1AdvancePWMStop();
    uint16_t pulse = m_pulse_ms / (7200000 / CONFIG_TIM1_BASE_PRESCALER);

    TIM_OC_InitTypeDef config_tim1advance_oc;
    config_tim1advance_oc.Pulse = pulse;
    FUNC_CHECK_FOR_HAL(HAL_TIM_PWM_ConfigChannel(&V_config_tim1advance, &config_tim1advance_oc, PORT_TIM1ADVANCE_CHANNEL_1), "ERROR TIM1_PWMChangePulse");
    FuncTIM1AdvancePWMStart();
}

TIM_HandleTypeDef V_config_tim5general;
Type_Status_TIM_IC V_data_tim5general_ic_ch1 = {0, 0, 0, 0};
Type_Status_TIM_IC V_data_tim5general_ic_ch2 = {0, 0, 0, 0};

void InitializeTIM5General(void)
{
    InitializeTIM5GeneralForGPIO();
    InitializeTIM5GeneralForProtocol();
}

void InitializeTIM5GeneralForGPIO(void)
{
    FUNC_TIM5GENERAL_PIN_CLK_ENABLE();

    GPIO_InitTypeDef config_tim5general_gpio;

    config_tim5general_gpio.Mode = GPIO_MODE_INPUT;
    config_tim5general_gpio.Pull = GPIO_PULLDOWN;
    config_tim5general_gpio.Speed = GPIO_SPEED_FREQ_HIGH;

    config_tim5general_gpio.Pin = PORT_TIM5GENERAL_IC_CH1_PIN;
    HAL_GPIO_Init(PORT_TIM5GENERAL_IC_CH1_GROUP, &config_tim5general_gpio);
    config_tim5general_gpio.Pin = PORT_TIM5GENERAL_IC_CH2_PIN;
    HAL_GPIO_Init(PORT_TIM5GENERAL_IC_CH2_GROUP, &config_tim5general_gpio);
}

void InitializeTIM5GeneralForProtocol(void)
{
    FUNC_TIM5GENERAL_CLK_ENABLE();

    V_config_tim5general.Instance = TIM5;
    V_config_tim5general.Init.Prescaler = CONFIG_TIM5_BASE_PRESCALER;
    V_config_tim5general.Init.CounterMode = CONFIG_TIM5_BASE_COUNTERMODE;
    V_config_tim5general.Init.Period = CONFIG_TIM5_BASE_PERIOD;
    V_config_tim5general.Init.ClockDivision = CONFIG_TIM5_BASE_CLOCKDIVISION;
    FUNC_CHECK_FOR_HAL(HAL_TIM_Base_Init(&V_config_tim5general), "ERROR TIM5_Init_Base");

    TIM_ClockConfigTypeDef config_tim5general_clock;
    config_tim5general_clock.ClockSource = CONFIG_TIM5_CLOCK_CLOCKSOURCE;
    FUNC_CHECK_FOR_HAL(HAL_TIM_ConfigClockSource(&V_config_tim5general, &config_tim5general_clock), "ERROR TIM5_Init_Clock");

    TIM_MasterConfigTypeDef config_tim5general_master;
    config_tim5general_master.MasterOutputTrigger = CONFIG_TIM5_MASTER_OUTPUTTRIGGER;
    config_tim5general_master.MasterSlaveMode = CONFIG_TIM5_MASTER_SLAVEMODE;
    FUNC_CHECK_FOR_HAL(HAL_TIMEx_MasterConfigSynchronization(&V_config_tim5general, &config_tim5general_master), "ERROR TIM5_Init_Master");

    TIM_IC_InitTypeDef config_tim5general_ic;
    config_tim5general_ic.ICFilter = CONFIG_TIM5_IC_ICFILTER;
    config_tim5general_ic.ICPolarity = CONFIG_TIM5_IC_ICPOLARITY;
    config_tim5general_ic.ICPrescaler = CONFIG_TIM5_IC_ICPRESCALER;
    config_tim5general_ic.ICSelection = CONFIG_TIM5_IC_ICSELECTION;
    FUNC_CHECK_FOR_HAL(HAL_TIM_IC_ConfigChannel(&V_config_tim5general, &config_tim5general_ic, PORT_TIM5GENERAL_CHANNEL_1), "ERROR TIM5_Init_IC_Ch1");
    FUNC_CHECK_FOR_HAL(HAL_TIM_IC_ConfigChannel(&V_config_tim5general, &config_tim5general_ic, PORT_TIM5GENERAL_CHANNEL_2), "ERROR TIM5_Init_IC_Ch2");
}

uint32_t FuncTIM5GeneralGetICValue(uint32_t m_channel)
{
    uint32_t result = 0;
    switch (m_channel)
    {
    case PORT_TIM5GENERAL_CHANNEL_1:
        result = V_data_tim5general_ic_ch1.data_result;
        break;

    case PORT_TIM5GENERAL_CHANNEL_2:
        result = V_data_tim5general_ic_ch2.data_result;
        break;

    default:
        break;
    }
    return result;
}
