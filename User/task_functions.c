#include "task_functions.h"

void TaskDeviceStart(void)
{
    for (int count = 0; count < 3; count++)
    {
        FuncLEDColourSet(STATUS_LED_COLOUR_WHITE);
        vTaskDelay(V_TASK_DELAY_TIME(150));
        FuncLEDColourSet(STATUS_LED_COLOUR_BLACK);
        vTaskDelay(V_TASK_DELAY_TIME(150));
    }

    for (int count_pixel = 0; count_pixel < 3; count_pixel++)
    {
        uint16_t times_rec = 8;
        for (int count_rec = 0; count_rec < times_rec; count_rec++)
        {
            uint16_t pixel_width = STATUS_LCD_PIXELWIDTH - count_rec * (STATUS_LCD_PIXELWIDTH / times_rec);
            uint16_t pixel_height = STATUS_LCD_PIXELHEIGHT - count_rec * (STATUS_LCD_PIXELHEIGHT / times_rec);
            FuncLCDDrawRectangleForCenter(STATUS_LCD_PIXELWIDTH / 2, STATUS_LCD_PIXELHEIGHT / 2, pixel_width, pixel_height, STATUS_LCD_COLOUR_CYAN, STATUS_LCD_LINEFILL_EMPTY);
            vTaskDelay(V_TASK_DELAY_TIME(40));
            FuncLCDDrawFullScreen(STATUS_LCD_COLOUR_BACKGROUND);
            vTaskDelay(V_TASK_DELAY_TIME(40));
        }
    }
    FuncUSART1SendStr("Hi, I'm STM32 for SeamusWong!\n");

    FuncLCDDrawFullScreen(STATUS_LCD_COLOUR_GBLUE);
    FuncLCDDrawRectangleForCorner(0, 0, STATUS_LCD_PIXELWIDTH / 2, STATUS_LCD_PIXELHEIGHT / 2, STATUS_LCD_COLOUR_YELLOW, STATUS_LCD_LINEFILL_FULL);
    FuncLCDDrawStrForASCII(5, 16, "Hi,I'm\nSTM32F103ZET6 for\nSeamus Wong!", STATUS_LCD_COLOUR_BLACK, &V_font_ascii_handle_conslons_24x16);

    taskENTER_CRITICAL();                 // 进入临界区
    vTaskDelete(Handle_Task_DeviceStart); // 删除任务
    taskEXIT_CRITICAL();                  // 退出临界区
}

void TaskIdleLED(void)
{
    while (1)
    {
        FuncLEDColourSet(STATUS_LED_COLOUR_GREEN);
        vTaskDelay(V_TASK_DELAY_TIME(20));
        FuncLEDColourSet(STATUS_LED_COLOUR_BLACK);
        vTaskDelay(V_TASK_DELAY_TIME(2000));
    }
}

void TaskKEYBeep(void)
{
    while (1)
    {
        if (FuncKEY1StatusRead() == STATUS_KEY_ON)
        {
            FuncBEEPSet(STATUS_BEEP_ON);
        }

        if (FuncKEY2StatusRead() == STATUS_KEY_ON)
        {
            FuncBEEPSet(STATUS_BEEP_OFF);
        }
        vTaskDelay(V_TASK_DELAY_TIME(50));
    }
}

void TaskScreenSystemTime(void)
{
    double time_sys = 0.0;
    while (1)
    {
        time_sys = (double)xTaskGetTickCount() / 1000.0;
        char m_str[20];
        sprintf(m_str, "Boot Time:%.1f", time_sys);
        FuncLCDDrawRectangleForCorner(0, 0, STATUS_LCD_PIXELWIDTH, V_font_ascii_handle_conslons_16x8.height, STATUS_LCD_COLOUR_BACKGROUND, STATUS_LCD_LINEFILL_FULL);
        FuncLCDDrawStrForASCII(0, 0, m_str, STATUS_LCD_COLOUR_MAGENTA, &V_font_ascii_handle_conslons_16x8);
        vTaskDelay(V_TASK_DELAY_TIME(1000));
    }
}
