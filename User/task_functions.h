#ifndef H_TASK_FUNCTIONS_
#define H_TASK_FUNCTIONS_

#include "stdarg.h"
#include <stm32f1xx_hal.h>
/* FreeRTOS头文件 */
#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"
/* 开发板硬件头文件 */
#include "whx_peripherals.h"
#include "whx_interrupts.h"
#include "whx_communicate_usart.h"

#define V_TASK_DELAY_TIME(x) (x / portTICK_PERIOD_MS)

/**
 * @description: 任务句柄
 */
static TaskHandle_t Handle_Task_DeviceStart = NULL;
static TaskHandle_t Handle_Task_IdleLED = NULL;
static TaskHandle_t Handle_Task_KEYBeep = NULL;
static TaskHandle_t Handle_Task_ScreenSystemTime = NULL;
/*********************************任务句柄************************************/

/**
 * @description: 任务声明
 */
void TaskDeviceStart(void);
void TaskIdleLED(void);
void TaskKEYBeep(void);
void TaskScreenSystemTime(void);
/*********************************任务句柄************************************/

#endif
