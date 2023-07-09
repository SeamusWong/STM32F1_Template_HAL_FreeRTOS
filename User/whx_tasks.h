#ifndef H_WHX_TASKS_
#define H_WHX_TASKS_

/* FreeRTOS头文件 */
#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"
#include "queue.h"
#include "list.h"
#include "timers.h"
#include "event_groups.h"
#include "croutine.h"
/* 开发板硬件头文件 */
#include "whx_libraries_all.h"
#include "whx_peripherals.h"
#include "whx_interrupts.h"
#include "whx_communicate.h"
#include "whx_on_chip.h"

#define V_TASK_DELAY_TIME(x) (x / portTICK_PERIOD_MS)

/**
 * @description: 任务句柄
 */
static TaskHandle_t V_handle_task_DeviceStart = NULL;
static TaskHandle_t V_handle_task_IdleLED = NULL;
static TaskHandle_t V_handle_task_ScreenSystemTime = NULL;
static TaskHandle_t V_handle_task_ScreenShowInfo = NULL;
static TaskHandle_t V_handle_task_CapacitiveButtonLED = NULL;
static TaskHandle_t V_handle_task_ScreenChangeByKey = NULL;
/*********************************任务句柄************************************/

/**
 * @description: 任务声明
 */
void TaskDeviceStart(void);
void TaskIdleLED(void);
void TaskScreenSystemTime(void);
void TaskScreenShowInfo(void);
void TaskCapacitiveButtonLED(void);
void TaskScreenChangeByKey(void);
/*********************************任务句柄************************************/

#endif /*H_WHX_TASKS_*/
