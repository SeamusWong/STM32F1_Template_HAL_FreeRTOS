#ifndef H_WHX_TASKS_
#define H_WHX_TASKS_

/* 开发板硬件头文件 */
#include "whx_libraries_all.h"
#include "whx_peripherals.h"
#include "whx_interrupts.h"
#include "whx_communicate.h"
#include "whx_on_chip.h"

#if ENABLE_FREERTOS

#define V_TASK_DELAY_TIME(x) (x / portTICK_PERIOD_MS)

/**
 * @description: 任务句柄声明
 */
extern TaskHandle_t V_handle_task_DeviceStart;
extern TaskHandle_t V_handle_task_IdleLED;
extern TaskHandle_t V_handle_task_ScreenSystemTime;
extern TaskHandle_t V_handle_task_ScreenShowInfo;
extern TaskHandle_t V_handle_task_CapacitiveButtonLED;
extern TaskHandle_t V_handle_task_Tim5General;
extern TaskHandle_t V_handle_task_ADC;
/*********************************任务句柄声明*********************************/

/**
 * @description: 任务声明
 */
void TaskDeviceStart(void);
void TaskIdleLED(void);
void TaskScreenSystemTime(void);
void TaskScreenShowInfo(void);
void TaskCapacitiveButtonLED(void);
void TaskTim5General(void);
void TaskADC(void);
/*********************************任务句柄*********************************/

/**
 * @description: 消息队列声明
 */
typedef struct
{
    float ch1_voltage;
} Type_Queue_Screen_ADC;
extern QueueHandle_t V_handle_queue_screen_adc;

typedef struct
{
    uint16_t width;
} Type_Queue_Screen_CapacitiveButton;
extern QueueHandle_t V_handle_queue_screen_capacitivebutton;

typedef struct
{
    uint32_t ch1_ic_value;
} Type_Queue_Screen_Tim5General;
extern QueueHandle_t V_handle_queue_screen_tim5general;

typedef struct
{
    float second;
} Type_Queue_Screen_SystemTime;
extern QueueHandle_t V_handle_queue_screen_systemtime;
/*********************************消息队列声明*********************************/

/**
 * @description: 事件组
 */
typedef enum
{
    EVENT_SCREEN_REFRESH_ADC = (0x1 << 0),
    EVENT_SCREEN_REFRESH_CAPACITIVEBUTTON = (0x1 << 1),
    EVENT_SCREEN_REFRESH_TIM5GENERAL = (0x1 << 2),
    EVENT_SCREEN_REFRESH_SYSTEMTIME = (0x1 << 3),
} Type_Event_Screen;
extern EventGroupHandle_t V_handle_event_screen_refresh; /*高8位不能用于设置事件，所以32位的事件组变量只能使用24个事件*/
/*********************************事件组*********************************/

/**
 * @description: Others
 */

/*********************************Others*********************************/

#else
#endif /*ENABLE_FREERTOS*/

#endif /*H_WHX_TASKS_*/
