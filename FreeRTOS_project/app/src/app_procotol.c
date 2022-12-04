#include "config.h"
#include "FreeRTOS.h"
#include "task.h"
#include "protocol.h"

//LED1任务函数
void prodis_task(void *pvParameters)
{
		uint32_t NotifyValue;
    while(1)
    {
//		NotifyValue=ulTaskNotifyTake(pdTRUE,portMAX_DELAY);	//获取任务通知
//		if(NotifyValue==1)																	//清零之前的任务通知值为1，说明任务通知有效
//		{
			pro_dis();
			  vTaskDelay(10);
//		}
				
    }
}
