#include "whx_tasks.h"

#if ENABLE_FREERTOS

/**
 * @description: 任务句柄
 */
TaskHandle_t V_handle_task_DeviceStart = NULL;
TaskHandle_t V_handle_task_IdleLED = NULL;
TaskHandle_t V_handle_task_ScreenShowInfo = NULL;
TaskHandle_t V_handle_task_CapacitiveButtonLED = NULL;
TaskHandle_t V_handle_task_Tim5General = NULL;
TaskHandle_t V_handle_task_ADC = NULL;
/*********************************任务句柄*********************************/

/**
 * @description: 消息队列句柄
 */

QueueHandle_t V_handle_queue_screen_adc = NULL;
QueueHandle_t V_handle_queue_screen_capacitivebutton = NULL;
QueueHandle_t V_handle_queue_screen_tim5general = NULL;
QueueHandle_t V_handle_queue_screen_systemtime = NULL;
/*********************************消息队列句柄*********************************/

/**
 * @description: 事件组句柄
 */
EventGroupHandle_t V_handle_event_screen_refresh; /*高8位不能用于设置事件，所以32位的事件组变量只能使用24个事件*/
/*********************************事件组句柄*********************************/

/**
 * @description: 定时器句柄
 */
TimerHandle_t V_handle_timer_systemtime = NULL;
/*********************************定时器句柄*********************************/

void TaskDeviceStart(void)
{
    FuncCapacitiveButton1SetThreshold(FuncCapacitiveButton1GetPulseWidth() * 1.1);

    printf("Hi, I'm STM32 for SeamusWong!\n");

    for (int count = 0; count < 3; count++)
    {
        FuncLED1SetColour(STATUS_LED_COLOUR_WHITE);
        HAL_Delay(150);
        FuncLED1SetColour(STATUS_LED_COLOUR_BLACK);
        HAL_Delay(150);
    }

    for (int count_pixel = 0; count_pixel < 3; count_pixel++)
    {
        uint16_t times_rec = 8;
        for (int count_rec = 0; count_rec < times_rec; count_rec++)
        {
            uint16_t pixel_width = STATUS_LCD_PIXELWIDTH - count_rec * (STATUS_LCD_PIXELWIDTH / times_rec);
            uint16_t pixel_height = STATUS_LCD_PIXELHEIGHT - count_rec * (STATUS_LCD_PIXELHEIGHT / times_rec);
            FuncLCD1DrawRectangleForCenter(STATUS_LCD_PIXELWIDTH / 2, STATUS_LCD_PIXELHEIGHT / 2, pixel_width, pixel_height, STATUS_LCD_COLOUR_CYAN, STATUS_LCD_FILL_EMPTY);
            HAL_Delay(40);
            FuncLCD1DrawFullScreen(STATUS_LCD_COLOUR_BACKGROUND);
            HAL_Delay(40);
        }
    }

    taskENTER_CRITICAL();                   // 进入临界区
    vTaskDelete(V_handle_task_DeviceStart); // 删除任务
    taskEXIT_CRITICAL();                    // 退出临界区
}

void TaskIdleLED(void)
{
    while (1)
    {
        if (FuncLED1ReadColour() == STATUS_LED_COLOUR_BLACK)
        {
            FuncLED1SetColour(STATUS_LED_COLOUR_GREEN);
            vTaskDelay(V_TASK_DELAY_TIME(5));
            FuncLED1SetColour(STATUS_LED_COLOUR_BLACK);
        }
        vTaskDelay(V_TASK_DELAY_TIME(2000));
    }
}

void TaskScreenShowInfo(void)
{
    while (1)
    {

        EventBits_t events_list = 0;
        events_list = xEventGroupWaitBits(V_handle_event_screen_refresh,  /*事件组句柄*/
                                          0xffffffU,                      /*要监控的事件(全部监控)*/
                                          pdFALSE,                        /*是否在满足条件时清除上方的时间标志位*/
                                          pdFALSE,                        /*pdTRUE为与逻辑，pdFALSE为或逻辑*/
                                          V_TASK_DELAY_TIME(0xffffffff)); /*超时等待时间*/

        /*背景区域*/
        // FuncLCD1DrawFullScreen(STATUS_LCD_COLOUR_GREY);
        // FuncLCD1DrawRectangleForCorner(0, 0, STATUS_LCD_PIXELWIDTH / 2, STATUS_LCD_PIXELHEIGHT / 2, STATUS_LCD_COLOUR_YELLOW, STATUS_LCD_FILL_FULL);
        // FuncLCD1DrawStrForASCII(5, 16, "Hi,I'm\nSTM32F103ZET6 for\nSeamus Wong!", STATUS_LCD_COLOUR_BLACK, &V_font_ascii_handle_conslons_24x16);

        /*数据刷新区域*/
        if (events_list & EVENT_SCREEN_REFRESH_ADC)
        {
            Type_Queue_Screen_ADC queue_adc;
            if (xQueueReceive(V_handle_queue_screen_adc, &queue_adc, 0) == pdPASS)
            {
                char info_adc[20];
                sprintf(info_adc, "ADC1_CH1:%.2f V", queue_adc.ch1_voltage);
                FuncLCD1DrawRectangleForCorner(0, 190, STATUS_LCD_PIXELWIDTH, V_font_ascii_handle_conslons_16x8.height, STATUS_LCD_COLOUR_BACKGROUND, STATUS_LCD_FILL_FULL);
                FuncLCD1DrawStrForASCII(0, 190, info_adc, STATUS_LCD_COLOUR_RED, &V_font_ascii_handle_conslons_16x8);
            }
            xEventGroupClearBits(V_handle_event_screen_refresh, EVENT_SCREEN_REFRESH_ADC);
        }

        if (events_list & EVENT_SCREEN_REFRESH_CAPACITIVEBUTTON)
        {
            Type_Queue_Screen_CapacitiveButton queue_capacitivebutton;
            if (xQueueReceive(V_handle_queue_screen_capacitivebutton, &queue_capacitivebutton, 0) == pdPASS)
            {
                char info_capacitivebutton[20];
                sprintf(info_capacitivebutton, "TIM5_IC_CH2:%d / %d", queue_capacitivebutton.width, V_data_capacitivebutton_threshold);
                FuncLCD1DrawRectangleForCorner(0, 170, STATUS_LCD_PIXELWIDTH, V_font_ascii_handle_conslons_16x8.height, STATUS_LCD_COLOUR_BACKGROUND, STATUS_LCD_FILL_FULL);
                FuncLCD1DrawStrForASCII(0, 170, info_capacitivebutton, STATUS_LCD_COLOUR_GREEN, &V_font_ascii_handle_conslons_16x8);
            }
            xEventGroupClearBits(V_handle_event_screen_refresh, EVENT_SCREEN_REFRESH_CAPACITIVEBUTTON);
        }

        if (events_list & EVENT_SCREEN_REFRESH_TIM5GENERAL)
        {
            Type_Queue_Screen_Tim5General queue_tim5general;
            if (xQueueReceive(V_handle_queue_screen_tim5general, &queue_tim5general, 0) == pdPASS)
            {
                char info_tim5general[20];
                sprintf(info_tim5general, "TIM5_IC_CH1:%d ms", queue_tim5general.ch1_ic_value / ((HAL_RCC_GetHCLKFreq() / 1000) / CONFIG_TIM5_BASE_PRESCALER));
                FuncLCD1DrawRectangleForCorner(0, 150, STATUS_LCD_PIXELWIDTH, V_font_ascii_handle_conslons_16x8.height, STATUS_LCD_COLOUR_BACKGROUND, STATUS_LCD_FILL_FULL);
                FuncLCD1DrawStrForASCII(0, 150, info_tim5general, STATUS_LCD_COLOUR_BLUE, &V_font_ascii_handle_conslons_16x8);
            }
            xEventGroupClearBits(V_handle_event_screen_refresh, EVENT_SCREEN_REFRESH_TIM5GENERAL);
        }
    }
}

void TaskCapacitiveButtonLED(void)
{
    while (1)
    {
        Type_Status_CapacitiveButton flag = FuncCapacitiveButton1GetStatus();
        if (flag == STATUS_CAPACITIVEBUTTON_ON)
        {
            FuncLED1SetColour(STATUS_LED_COLOUR_PURPLE);
        }
        else
        {
            FuncLED1SetColour(STATUS_LED_COLOUR_BLACK);
        }

        Type_Queue_Screen_CapacitiveButton info;
        static Type_Queue_Screen_CapacitiveButton info_record;

        info.width = FuncCapacitiveButton1GetPulseWidth();

        if (info.width != info_record.width)
        {
            info_record.width = info.width;

            FUNC_CHECK_FOR_FREERTOS(xQueueOverwrite(
                                        V_handle_queue_screen_capacitivebutton, /*消息队列句柄*/
                                        &info),                                 /*消息指针*/
                                    "ERROR_QueueSend_Type_Queue_Screen_CapacitiveButton");
            xEventGroupSetBits(
                V_handle_event_screen_refresh,          /*事件组句柄*/
                EVENT_SCREEN_REFRESH_CAPACITIVEBUTTON); /*要置位的事件*/
        }

        vTaskDelay(V_TASK_DELAY_TIME(50));
    }
}

void TaskTim5General(void)
{
    while (1)
    {
        Type_Queue_Screen_Tim5General info;
        static Type_Queue_Screen_Tim5General info_record;

        info.ch1_ic_value = FuncTIM5GeneralGetICValue(PORT_TIM5GENERAL_CHANNEL_1);

        if (info.ch1_ic_value != info_record.ch1_ic_value)
        {
            info_record.ch1_ic_value = info.ch1_ic_value;

            FUNC_CHECK_FOR_FREERTOS(xQueueOverwrite(
                                        V_handle_queue_screen_tim5general, /*消息队列句柄*/
                                        &info),                            /*消息指针*/
                                    "ERROR_QueueSend_Type_Queue_Screen_Tim5General");
            xEventGroupSetBits(
                V_handle_event_screen_refresh,     /*事件组句柄*/
                EVENT_SCREEN_REFRESH_TIM5GENERAL); /*要置位的事件*/
        }

        vTaskDelay(V_TASK_DELAY_TIME(50));
    }
}

void TaskADC(void)
{
    while (1)
    {
        Type_Queue_Screen_ADC info;
        static Type_Queue_Screen_ADC info_record;

        info.ch1_voltage = FuncADC1GetVoltage(PORT_ADC1_CH11_CHANNEL);

        if (info.ch1_voltage - info_record.ch1_voltage > 0.01 || info.ch1_voltage - info_record.ch1_voltage < -0.01)
        {
            info_record.ch1_voltage = info.ch1_voltage;

            FUNC_CHECK_FOR_FREERTOS(xQueueOverwrite(
                                        V_handle_queue_screen_adc, /*消息队列句柄*/
                                        &info),                    /*消息指针*/
                                    "ERROR_QueueSend_Type_Queue_Screen_ADC");
            xEventGroupSetBits(
                V_handle_event_screen_refresh, /*事件组句柄*/
                EVENT_SCREEN_REFRESH_ADC);     /*要置位的事件*/
        }

        vTaskDelay(V_TASK_DELAY_TIME(50));
    }
}

void TimerTaskScreenSystemTime(void *id_timer)
{
    char info_systemtime[20];
    float time_second = (float)xTaskGetTickCount() / 1000.0;
    sprintf(info_systemtime, "Boot Time:%.1f s", time_second);
    FuncLCD1DrawRectangleForCorner(0, 0, STATUS_LCD_PIXELWIDTH, V_font_ascii_handle_conslons_16x8.height, STATUS_LCD_COLOUR_BACKGROUND, STATUS_LCD_FILL_FULL);
    FuncLCD1DrawStrForASCII(0, 0, info_systemtime, STATUS_LCD_COLOUR_MAGENTA, &V_font_ascii_handle_conslons_16x8);
}

#else
#endif /*ENABLE_FREERTOS*/
