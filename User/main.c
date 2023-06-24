#include <stm32f1xx_hal.h>
/* 开发板硬件头文件 */
#include "GB2312_Font.h"
#include "whx_peripherals.h"
#include "whx_interrupts.h"
#include "whx_communicate_usart.h"
#include "whx_communicate_i2c.h"
#include "whx_communicate_spi.h"
/* FreeRTOS头文件 */
#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"
#include "queue.h"
#include "list.h"
#include "timers.h"
#include "event_groups.h"
#include "croutine.h"
/* 任务 */
#include "task_functions.h"

#define MAIN_ENABLE_FREERTOS 1 /*启用FreeRTOS内核*/

static void Initializer(void); /* 用于初始化板载相关资源 */

#if MAIN_ENABLE_FREERTOS
/**
 * @description: 任务句柄
 */
static TaskHandle_t Handle_Task_Creator = NULL;
/*********************/
#else
#endif

#if MAIN_ENABLE_FREERTOS
static void Creator(void); /* FreeRTOS任务创建 */
#else
#endif

static void Initializer(void)
{
  // HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
  HAL_Init();
  SystemClockConfig();     /* 系统时钟初始化 */
  InitializeLED();         /* LED初始化 */
  InitializeKEY();         /* 按键初始化 */
  InitializeBEEP();        /* 蜂鸣器初始化 */
  InitializeUSART1();      /* USART通信初始化 */
  InitializeEEPROM();      /* EEPROM读写初始化 */
  InitializeFLASH();       /* FLASH读写初始化 */
  InitializeLCD();         /* LCD液晶屏幕初始化 */
  InitializeADC1();        /* ADC电压读取初始化 */
  InitializeTIM6Base();    /* TIM6 基本定时器初始化 */
  InitializeTIM1Advance(); /* TIM1 PWM输出初始化 */

  // InitializeInterruptForGpio();  /* 按键中断初始化	*/
  // InitializeInterruptForUSART(); /* 通信中断初始化 */
  InitializeInterruptForADC1(); /* ADC中断初始化 */
  // InitializeInterruptForTIM6Base();
  // FuncInterruptForTIM6BaseEnable();
}

int main(void)
{
  Initializer(); /* 开发板硬件初始化 */

#if MAIN_ENABLE_FREERTOS
  BaseType_t status_task_create = pdPASS;                                 /* 定义一个创建信息返回值，默认为pdPASS */
  status_task_create = xTaskCreate((TaskFunction_t)Creator,               /* 任务入口函数 */
                                   (const char *)"Creator",               /* 任务名字 */
                                   (uint16_t)512,                         /* 任务栈大小 */
                                   (void *)NULL,                          /* 任务入口函数参数 */
                                   (UBaseType_t)1,                        /* 任务的优先级 */
                                   (TaskHandle_t *)&Handle_Task_Creator); /* 任务控制块指针 */

  if (pdPASS == status_task_create)
  {
    vTaskStartScheduler(); /* 启动任务，开启调度 */
  }
  else
  {
    FuncErrorAlertLEDBEEP();
  }
#else
#endif

  return -1;
}

#if MAIN_ENABLE_FREERTOS
static void Creator(void)
{

  taskENTER_CRITICAL();                   // 进入临界区
  BaseType_t status_task_create = pdPASS; /* 定义一个创建信息返回值，默认为pdPASS */

  /***********************************************************************/
  status_task_create = xTaskCreate((TaskFunction_t)TaskDeviceStart,           /* 任务入口函数 */
                                   (const char *)"TaskDeviceStart",           /* 任务名字 */
                                   (uint16_t)512,                             /* 任务栈大小 */
                                   (void *)NULL,                              /* 任务入口函数参数 */
                                   (UBaseType_t)10,                           /* 任务的优先级 */
                                   (TaskHandle_t *)&Handle_Task_DeviceStart); /* 任务控制块指针 */
  if (status_task_create != pdPASS)
  {
    FuncErrorAlertLEDBEEP();
  }
  /***********************************************************************/
  /***********************************************************************/
  status_task_create = xTaskCreate((TaskFunction_t)TaskIdleLED,           /* 任务入口函数 */
                                   (const char *)"TaskIdleLED",           /* 任务名字 */
                                   (uint16_t)512,                         /* 任务栈大小 */
                                   (void *)NULL,                          /* 任务入口函数参数 */
                                   (UBaseType_t)1,                        /* 任务的优先级 */
                                   (TaskHandle_t *)&Handle_Task_IdleLED); /* 任务控制块指针 */
  if (status_task_create != pdPASS)
  {
    FuncErrorAlertLEDBEEP();
  }
  /***********************************************************************/
  /***********************************************************************/
  status_task_create = xTaskCreate((TaskFunction_t)TaskKEYBeep,           /* 任务入口函数 */
                                   (const char *)"TaskKEYBeep",           /* 任务名字 */
                                   (uint16_t)512,                         /* 任务栈大小 */
                                   (void *)NULL,                          /* 任务入口函数参数 */
                                   (UBaseType_t)2,                        /* 任务的优先级 */
                                   (TaskHandle_t *)&Handle_Task_KEYBeep); /* 任务控制块指针 */
  if (status_task_create != pdPASS)
  {
    FuncErrorAlertLEDBEEP();
  }
  /***********************************************************************/
  /***********************************************************************/
  status_task_create = xTaskCreate((TaskFunction_t)TaskScreenSystemTime,           /* 任务入口函数 */
                                   (const char *)"TaskScreenSystemTime",           /* 任务名字 */
                                   (uint16_t)512,                                  /* 任务栈大小 */
                                   (void *)NULL,                                   /* 任务入口函数参数 */
                                   (UBaseType_t)3,                                 /* 任务的优先级 */
                                   (TaskHandle_t *)&Handle_Task_ScreenSystemTime); /* 任务控制块指针 */
  if (status_task_create != pdPASS)
  {
    FuncErrorAlertLEDBEEP();
  }
  /***********************************************************************/

  vTaskDelete(Handle_Task_Creator); // 删除AppTaskCreate任务
  taskEXIT_CRITICAL();              // 退出临界区
}
#else
#endif
/********************************END OF FILE****************************/
