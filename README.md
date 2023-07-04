# STM32F1_Template_HAL_FreeRTOS

​	结合HAL库和FreeRTOS内核的STM32模板工程，基于书籍《STM32 HAL库开发实战指南——F103系列》以及野火F103霸道v2开发板开发，如果你有该系列开发板的话，此项目的代码可以直接编译并烧录，与此同时本项目也致力于实现良好的可移植性，故硬件接口与功能配置参数全部使用宏定义封装，以便于在其他公司开发板上展示其效果，同时也对几乎所有定义参数进行了注释，方便每一个学习者了解繁多的参数功能

​	**此项目仍在开发中，未完成，请等待**

## 用户库简要介绍（仅做暂时性解释，详细开发文档请等待）[.\User\whx_libraries](https://github.com/SeamusWong/STM32F1_Template_HAL_FreeRTOS/tree/main/User/whx_libraries)

- > `whx_communicate`
  >
  > 对STM32F1多种通信协议的封装，包括UART、SPI、IIC…

- > `whx_on_chip`
  >
  > 对STM32F1片上功能的封装，包括FSMC、DMA、TIM、ADC、DAC…

- > `whx_peripherals`
  >
  > 对开发板上所有设备提供的接口和功能函数，依赖于`whx_communicate`和`whx_on_chip`工作，包含三色LED、按键KEY、蜂鸣器BEEP、EEPROM、FLASH、LCD屏幕、电容按键…的引脚接口、配置函数和外部操作函数

- > `whx_interrupts`
  >
  > 包含所有中断的配置操作函数，包括GPIO、UART、ADC、TIM…的中断配置与实现，依赖于`whx_communicate`和`whx_on_chip`工作

## 主函数（仅做暂时性解释，详细开发文档请等待）[.\User\main.c以及.\User\whx_tasks.c](https://github.com/SeamusWong/STM32F1_Template_HAL_FreeRTOS/tree/main/User)

- > `whx_tasks`
  >
  > 内含依赖于FreeRTOS的所有任务函数，如果启用`ENABLE_FREERTOS`宏的话，这里是主要任务编写区

- > `main`
  >
  > 目前只含`SystemClockConfig`、`Initializer`、`Creator`三个子函数，他们执行并且只执行一次，作用分别是：
  >
  > - `SystemClockConfig`：系统初始时钟配置，包含系统时钟和总线时钟
  > - `Initializer`：执行全部外设与功能的初始化，控制中断使能
  > - `Creator`：依赖于FreeRTOS执行，控制全部任务的建立

------

