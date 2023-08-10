#include <stdio.h>
#include <stdlib.h>
#include <stm32f1xx.h>
#include <stm32f1xx_hal.h>
#include <stdarg.h>

#define ENABLE_FREERTOS 1 /*是否启用FreeRTOS内核，禁用后所有和FreeRTOS有关的代码全部失效*/

#if ENABLE_FREERTOS
/* FreeRTOS头文件 */
#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"
#include "queue.h"
#include "list.h"
#include "timers.h"
#include "event_groups.h"
#include "croutine.h"
#include "semphr.h"
#else
#endif

#include "GB2312_Font.h"

/*下方是在本库中随处用到的最基本量和函数*/

#define NO_USE NULL /*仅用在配置宏定义中，表示这项配置没有使用，仅在代码当中起提示和便于学习作用*/

/**
 * @description: 错误报警函数，需要外部实现，不能退出，进入了就表示你又要改BUG了
 */
extern void FuncErrorAlert(void);

/**
 * @description: 用于HAL库中各处返回值必须是HAL_OK的校验，不是就报错
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

#if ENABLE_FREERTOS

/**
 * @description: 用于FreeRTOS中各处返回值必须是pdPASS的校验，不是就报错
 */
#define FUNC_CHECK_FOR_FREERTOS(m_func, m_info) \
    do                                          \
    {                                           \
        if (m_func != pdPASS)                   \
        {                                       \
            printf(m_info);                     \
            printf("\n");                       \
            FuncErrorAlert();                   \
        }                                       \
    } while (0U);
#else
#endif

/**
 * @description: 在一段毫秒时间内等待一个值，超时了就报错
 */
#define FUNC_WAITSTATUS_TIMEOUT(m_func, m_status_wait, m_timeout_ms, m_info)            \
    do                                                                                  \
    {                                                                                   \
        uint32_t timeout = (uint32_t)m_timeout_ms * (HAL_RCC_GetSysClockFreq() / 1000); \
        while (m_func != m_status_wait)                                                 \
        {                                                                               \
            if (!timeout--)                                                             \
            {                                                                           \
                printf(m_info);                                                         \
                printf("\n");                                                           \
                FuncErrorAlert();                                                       \
            }                                                                           \
        }                                                                               \
    } while (0U);

/**
 * @description: 一个微秒级的延时，可以用在任何地方
 */
#define FUNC_DELAY_US_FOR_ALL(m_time_us)                                              \
    {                                                                                 \
        uint32_t delay = (uint32_t)m_time_us * (HAL_RCC_GetSysClockFreq() / 1000000); \
        while (delay--)                                                               \
            __asm("nop");                                                             \
    }
