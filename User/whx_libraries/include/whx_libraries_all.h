#include <stdio.h>
#include <stdlib.h>
#include <stm32f1xx.h>
#include <stm32f1xx_hal.h>
#include <stdarg.h>

#define ENABLE_FREERTOS 1 /*启用FreeRTOS内核*/

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
#else
#endif

#include "GB2312_Font.h"

#define NO_USE NULL /*仅用在配置宏定义中，表示这项配置没有使用，仅在代码当中起提示和便于学习作用*/

extern void FuncErrorAlert(void);

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

#define FUNC_DELAY_US_FOR_ALL(m_time_us)                                              \
    {                                                                                 \
        uint32_t delay = (uint32_t)m_time_us * (HAL_RCC_GetSysClockFreq() / 1000000); \
        while (delay--)                                                               \
            __asm("nop");                                                             \
    }
