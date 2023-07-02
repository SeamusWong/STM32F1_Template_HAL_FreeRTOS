#include "whx_tasks.h"

void TaskDeviceStart(void)
{
    FuncCapacitiveButtonSetThreshold(FuncCapacitiveButtonReadPulseWidth() * 1.1);

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
            FuncLCDDrawRectangleForCenter(STATUS_LCD_PIXELWIDTH / 2, STATUS_LCD_PIXELHEIGHT / 2, pixel_width, pixel_height, STATUS_LCD_COLOUR_CYAN, STATUS_LCD_LINEFILL_EMPTY);
            HAL_Delay(40);
            FuncLCDDrawFullScreen(STATUS_LCD_COLOUR_BACKGROUND);
            HAL_Delay(40);
        }
    }
    printf("Hi, I'm STM32 for SeamusWong!\n");

    FuncLCDDrawFullScreen(STATUS_LCD_COLOUR_GREY);
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
        if (FuncLED1ReadColour() == STATUS_LED_COLOUR_BLACK)
        {
            FuncLED1SetColour(STATUS_LED_COLOUR_GREEN);
            vTaskDelay(V_TASK_DELAY_TIME(10));
            FuncLED1SetColour(STATUS_LED_COLOUR_BLACK);
        }
        vTaskDelay(V_TASK_DELAY_TIME(2000));
    }
}

void TaskScreenSystemTime(void)
{
    double time_sys = 0.0;
    while (1)
    {
        time_sys = (double)xTaskGetTickCount() / 1000.0;
        char m_str[20];
        sprintf(m_str, "Boot Time:%.1f s", time_sys);
        FuncLCDDrawRectangleForCorner(0, 0, STATUS_LCD_PIXELWIDTH, V_font_ascii_handle_conslons_16x8.height, STATUS_LCD_COLOUR_BACKGROUND, STATUS_LCD_LINEFILL_FULL);
        FuncLCDDrawStrForASCII(0, 0, m_str, STATUS_LCD_COLOUR_MAGENTA, &V_font_ascii_handle_conslons_16x8);
        vTaskDelay(V_TASK_DELAY_TIME(1000));
    }
}

void TaskScreenShowInfo(void)
{
    while (1)
    {
        char m_str[20];
        sprintf(m_str, "TIM5_IC_CH1:%d ms", FuncTIM5GeneralGetICValue(PORT_TIM5GENERAL_CHANNEL_1) / ((HAL_RCC_GetHCLKFreq() / 1000) / CONFIG_TIM5_BASE_PRESCALER));
        FuncLCDDrawRectangleForCorner(0, 150, STATUS_LCD_PIXELWIDTH, V_font_ascii_handle_conslons_16x8.height, STATUS_LCD_COLOUR_BACKGROUND, STATUS_LCD_LINEFILL_FULL);
        FuncLCDDrawStrForASCII(0, 150, m_str, STATUS_LCD_COLOUR_BLUE, &V_font_ascii_handle_conslons_16x8);

        sprintf(m_str, "TIM5_IC_CH2:%d / %d", FuncCapacitiveButtonReadPulseWidth(), V_data_capacitivebutton_threshold);
        FuncLCDDrawRectangleForCorner(0, 170, STATUS_LCD_PIXELWIDTH, V_font_ascii_handle_conslons_16x8.height, STATUS_LCD_COLOUR_BACKGROUND, STATUS_LCD_LINEFILL_FULL);
        FuncLCDDrawStrForASCII(0, 170, m_str, STATUS_LCD_COLOUR_GREEN, &V_font_ascii_handle_conslons_16x8);
        vTaskDelay(V_TASK_DELAY_TIME(100));

        sprintf(m_str, "ADC1_CH1:%.2f V", FuncADC1GetVoltage(PORT_ADC1_1_CHANNEL));
        FuncLCDDrawRectangleForCorner(0, 190, STATUS_LCD_PIXELWIDTH, V_font_ascii_handle_conslons_16x8.height, STATUS_LCD_COLOUR_BACKGROUND, STATUS_LCD_LINEFILL_FULL);
        FuncLCDDrawStrForASCII(0, 190, m_str, STATUS_LCD_COLOUR_CYAN, &V_font_ascii_handle_conslons_16x8);
        vTaskDelay(V_TASK_DELAY_TIME(100));
    }
}

void TaskCapacitiveButtonLED(void)
{
    while (1)
    {
        if (FuncCapacitiveButtonStatusRead() == STATUS_CAPACITIVEBUTTON_ON)
        {
            FuncLED1SetColour(STATUS_LED_COLOUR_PURPLE);
        }
        else
        {
            FuncLED1SetColour(STATUS_LED_COLOUR_BLACK);
        }
        vTaskDelay(V_TASK_DELAY_TIME(50));
    }
}

void TaskScreenChangeByKey(void)
{
    uint8_t flag = 0;
    while (1)
    {
        if (FuncKEY2ReadStatus() == STATUS_KEY_ON)
        {
            FuncLCDDrawFullScreen(STATUS_LCD_COLOUR_BACKGROUND);
            if (flag == 0)
            {
                FuncLCDSetDisplayDirection(STATUS_LCD_DISPLAYDIRECTION_HORIZONTAL_RIGHTBOTTOM_LEFTTOP);
                flag = 1;
            }
            else
            {
                FuncLCDSetDisplayDirection(STATUS_LCD_DISPLAYDIRECTION_VERTICAL_LEFTTOP_RIGHTBOTTOM);
                flag = 0;
            }
        }
        else
        {
            FuncLED1SetColour(STATUS_LED_COLOUR_BLACK);
        }
        vTaskDelay(V_TASK_DELAY_TIME(50));
    }
}