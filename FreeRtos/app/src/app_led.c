#include "config.h"
#include "FreeRTOS.h"
#include "task.h"
//LED0任务函数 
void led0_task(void *pvParameters)
{
    while(1)
    {
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);
        vTaskDelay(500);
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);
        vTaskDelay(500);
    }
}   

//LED1任务函数
void led1_task(void *pvParameters)
{
    while(1)
    {
        HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_SET);
        vTaskDelay(500);
        HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_RESET);
        vTaskDelay(500);
    }
}
