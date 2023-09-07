/* 开发板硬件头文件 */
#include "whx_libraries_all.h"
#include "whx_peripherals.h"
#include "whx_interrupts.h"
#include "whx_communicate.h"
#include "whx_on_chip.h"

#if ENABLE_FREERTOS
/* 用户任务 */
#include "whx_tasks.h"
#else
#endif

static void Initializer(void); /* 用于初始化板载相关资源 */

#if ENABLE_FREERTOS
static TaskHandle_t V_handle_task_Creator = NULL;
static void Creator(void); /* 用于创建和初始化FreeRTOS中的所有任务、事件和信号量 */
#else
#endif

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
  FUNC_CHECK_FOR_HAL(HAL_RCC_OscConfig(&oscinitstruct), "ERROR OscConfig");

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  clkinitstruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  clkinitstruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  clkinitstruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  clkinitstruct.APB2CLKDivider = RCC_HCLK_DIV1;
  clkinitstruct.APB1CLKDivider = RCC_HCLK_DIV2;
  FUNC_CHECK_FOR_HAL(HAL_RCC_ClockConfig(&clkinitstruct, FLASH_LATENCY_2), "ERROR ClockConfig");
}

/**
 * @description: *****************************主程序开始*****************************
 */
static void Initializer(void)
{
  /*外设初始化*/
  InitializeLED1();    /* LED初始化 */
  InitializeKEY2();    /* 按键初始化 */
  InitializeBEEP1();   /* 蜂鸣器初始化 */
  InitializeUSART1();  /* USART通信初始化 */
  InitializeEEPROM1(); /* EEPROM读写初始化 */
  // InitializeFLASH1();      /* FLASH读写初始化【FLASH接口和DAC有冲突，不要同时使用】 */
  InitializeLCD1();        /* LCD液晶屏幕初始化 */
  InitializeADC1();        /* ADC电压读取初始化 */
  InitializeDAC1();        /* DAC电压输出初始化【FLASH接口和DAC有冲突，不要同时使用】 */
  InitializeTIM6Base();    /* TIM6 基本定时器初始化 */
  InitializeTIM1Advance(); /* TIM1 PWM输出初始化 */
  InitializeTIM5General();
  InitializeCapacitiveButton1();

  /*中断初始化*/
  // InitializeInterruptForGpio(1, 0);     /* 按键中断初始化	*/
  InitializeInterruptForADC1(1, 1);     /* ADC中断初始化 */
  InitializeInterruptForTIM6Base(1, 3); /* TIM6定时器中断初始化 */
  InitializeInterruptForTIM5General(1, 2);
  // InitializeInterruptForUSART(1,4); /* 通信中断初始化 */

  /*中断开启*/
  // FuncInterruptForGpioEnable();
  // FuncInterruptForUSARTEnable();
  FuncInterruptForADC1Enable();
  FuncInterruptForTIM6BaseEnable();
  FuncInterruptForTIM5GeneralEnable();
}

int main(void)
{
  HAL_Init();
  SystemClockConfig(); /* 系统时钟初始化 */

  Initializer(); /* 开发板硬件初始化 */

#if ENABLE_FREERTOS
  /***********************************************************************/
  FUNC_CHECK_FOR_FREERTOS(xTaskCreate((TaskFunction_t)Creator,                 /* 任务入口函数 */
                                      (const char *)"Creator",                 /* 任务名字 */
                                      (uint16_t)512,                           /* 任务栈大小 */
                                      (void *)NULL,                            /* 任务入口函数参数 */
                                      (UBaseType_t)10,                         /* 任务的优先级 */
                                      (TaskHandle_t *)&V_handle_task_Creator), /* 任务控制块指针 */
                          "ERROR_TaskCreate_Creator");
  /***********************************************************************/

  vTaskStartScheduler(); /* 启动任务，开启调度 */

#else
#endif

  while (1)
    ;
  return -1;
}

#if ENABLE_FREERTOS
static void Creator(void)
{

  taskENTER_CRITICAL(); // 进入临界区

  /**
   * @description: 任务创建区
   */
  FUNC_CHECK_FOR_FREERTOS(xTaskCreate((TaskFunction_t)TaskDeviceStart,             /* 任务入口函数 */
                                      (const char *)"TaskDeviceStart",             /* 任务名字 */
                                      (uint16_t)512,                               /* 任务栈大小 */
                                      (void *)NULL,                                /* 任务入口函数参数 */
                                      (UBaseType_t)10,                             /* 任务的优先级 */
                                      (TaskHandle_t *)&V_handle_task_DeviceStart), /* 任务控制块指针 */
                          "ERROR_TaskCreate_TaskDeviceStart");
  FUNC_CHECK_FOR_FREERTOS(xTaskCreate((TaskFunction_t)TaskIdleLED,             /* 任务入口函数 */
                                      (const char *)"TaskIdleLED",             /* 任务名字 */
                                      (uint16_t)512,                           /* 任务栈大小 */
                                      (void *)NULL,                            /* 任务入口函数参数 */
                                      (UBaseType_t)1,                          /* 任务的优先级 */
                                      (TaskHandle_t *)&V_handle_task_IdleLED), /* 任务控制块指针 */
                          "ERROR_TaskCreate_TaskIdleLED");
  FUNC_CHECK_FOR_FREERTOS(xTaskCreate((TaskFunction_t)TaskScreenShowInfo,             /* 任务入口函数 */
                                      (const char *)"TaskScreenShowInfo",             /* 任务名字 */
                                      (uint16_t)512,                                  /* 任务栈大小 */
                                      (void *)NULL,                                   /* 任务入口函数参数 */
                                      (UBaseType_t)2,                                 /* 任务的优先级 */
                                      (TaskHandle_t *)&V_handle_task_ScreenShowInfo), /* 任务控制块指针 */
                          "ERROR_TaskCreate_TaskScreenShowInfo");
  FUNC_CHECK_FOR_FREERTOS(xTaskCreate((TaskFunction_t)TaskCapacitiveButtonLED,             /* 任务入口函数 */
                                      (const char *)"TaskCapacitiveButtonLED",             /* 任务名字 */
                                      (uint16_t)512,                                       /* 任务栈大小 */
                                      (void *)NULL,                                        /* 任务入口函数参数 */
                                      (UBaseType_t)3,                                      /* 任务的优先级 */
                                      (TaskHandle_t *)&V_handle_task_CapacitiveButtonLED), /* 任务控制块指针 */
                          "ERROR_TaskCreate_TaskCapacitiveButtonLED");
  FUNC_CHECK_FOR_FREERTOS(xTaskCreate((TaskFunction_t)TaskTim5General,             /* 任务入口函数 */
                                      (const char *)"TaskTim5General",             /* 任务名字 */
                                      (uint16_t)512,                               /* 任务栈大小 */
                                      (void *)NULL,                                /* 任务入口函数参数 */
                                      (UBaseType_t)3,                              /* 任务的优先级 */
                                      (TaskHandle_t *)&V_handle_task_Tim5General), /* 任务控制块指针 */
                          "ERROR_TaskCreate_TaskTim5General");
  FUNC_CHECK_FOR_FREERTOS(xTaskCreate((TaskFunction_t)TaskADC,             /* 任务入口函数 */
                                      (const char *)"TaskADC",             /* 任务名字 */
                                      (uint16_t)512,                       /* 任务栈大小 */
                                      (void *)NULL,                        /* 任务入口函数参数 */
                                      (UBaseType_t)3,                      /* 任务的优先级 */
                                      (TaskHandle_t *)&V_handle_task_ADC), /* 任务控制块指针 */
                          "ERROR_TaskCreate_TaskADC");
  /***********************************任务创建区***********************************/

  /**
   * @description: 消息队列创建区
   */
  V_handle_queue_screen_adc = xQueueCreate((UBaseType_t)CONFIG_QUEUE_SCREEN_ADC_SIZE,   /*消息队列长度*/
                                           (UBaseType_t)sizeof(Type_Queue_Screen_ADC)); /*消息占用空间*/
  if (V_handle_queue_screen_adc == NULL)
  {
    printf("ERROR_QueueCreate_V_handle_queue_screen_adc\n");
    FuncErrorAlert();
  }

  V_handle_queue_screen_capacitivebutton = xQueueCreate((UBaseType_t)CONFIG_QUEUE_SCREEN_CAPACITIVEBUTTON_SIZE,   /*消息队列长度*/
                                                        (UBaseType_t)sizeof(Type_Queue_Screen_CapacitiveButton)); /*消息占用空间*/
  if (V_handle_queue_screen_adc == NULL)
  {
    printf("ERROR_QueueCreate_V_handle_queue_screen_capacitivebutton\n");
    FuncErrorAlert();
  }

  V_handle_queue_screen_tim5general = xQueueCreate((UBaseType_t)CONFIG_QUEUE_SCREEN_TIM5GENERAL_SIZE,   /*消息队列长度*/
                                                   (UBaseType_t)sizeof(Type_Queue_Screen_Tim5General)); /*消息占用空间*/
  if (V_handle_queue_screen_adc == NULL)
  {
    printf("ERROR_QueueCreate_V_handle_queue_screen_tim5general\n");
    FuncErrorAlert();
  }
  /*********************************消息队列创建区*********************************/

  /**
   * @description: 事件组创建区
   */
  V_handle_event_screen_refresh = xEventGroupCreate();
  if (V_handle_event_screen_refresh == NULL)
  {
    printf("ERROR_EventCreate_V_handle_event_screen_refresh\n");
    FuncErrorAlert();
  }
  /*********************************事件组创建区*********************************/

  /**
   * @description: 定时器创建区
   */
  V_handle_timer_systemtime = xTimerCreate((const char *)"TimerSystemTime",                     /*软件定时器名字*/
                                           (TickType_t)pdMS_TO_TICKS(1000),                     /*定时器的周期，单位为系统节拍周期*/
                                           (UBaseType_t)pdTRUE,                                 /*pdTRUE 周期模式，pdFALSE 单次模式（运行一次后进入休眠态）*/
                                           (void *)1,                                           /*软件定时器ID，一个回调函数根据ID号来处理不同的软件定时器*/
                                           (TimerCallbackFunction_t)TimerTaskScreenSystemTime); /*回调函数*/
  if (V_handle_timer_systemtime == NULL)
  {
    printf("ERROR_TimerCreate_V_handle_timer_systemtime\n");
    FuncErrorAlert();
  }
  else
  {
    xTimerStart(V_handle_timer_systemtime, pdMS_TO_TICKS(1000));
  }
  /*********************************定时器创建区*********************************/

  /**
   * @description: Others
   */

  /*********************************Others*********************************/

  vTaskDelete(V_handle_task_Creator); // 删除Creator任务
  taskEXIT_CRITICAL();                // 退出临界区
}
#else
#endif
/****************************END OF FILE****************************/
