#include "config.h"
#include "FreeRTOS.h"
#include "task.h"
#include "app_task.h"


//任务优先级
#define APP_START_TASK_PRIO		1
//任务堆栈大小	
#define APP_START_STK_SIZE 		128  
//任务句柄
TaskHandle_t App_StartTask_Handler;
//任务函数
void AppTaskCreate(void *pvParameters);


uint32_t ccc = 0;
int main(void)
{
  BaseType_t xReturn = pdPASS;//定义一个创建信息返回值，默认为pdPASS
	HAL_Init(); 								//初始化HAL库
	bsp_gpio_init();						//GPIO初始化
	bsp_uartinit(115200);				//初始化串口
	bsp_timer_init();
	printf("FreeRTOS Test!\n");
	 ccc  = HAL_RCC_GetSysClockFreq();
	/*创建开始任务*/
   xReturn =  xTaskCreate((TaskFunction_t )AppTaskCreate,   //任务函数
                (const char*    )"AppTaskCreate",          //任务名称
                (uint16_t       )APP_START_STK_SIZE,        //任务堆栈大小
                (void*          )NULL,                  		//传递给任务函数的参数
                (UBaseType_t    )APP_START_TASK_PRIO,       //任务优先级
                (TaskHandle_t*  )&App_StartTask_Handler);   //任务句柄              
  /* 启动任务调度 */           
  if(pdPASS == xReturn)
	{
    printf("开启任务调度\n");
		vTaskStartScheduler();   //启动任务，开启调度 
	}
	else
	{
		return -1;
	}
      
  /* 正常不会执行到这里 */  
  while(1);   
}
