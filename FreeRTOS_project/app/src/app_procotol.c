#include "config.h"
#include "FreeRTOS.h"
#include "task.h"
#include "protocol.h"

//LED1������
void prodis_task(void *pvParameters)
{
		uint32_t NotifyValue;
    while(1)
    {
//		NotifyValue=ulTaskNotifyTake(pdTRUE,portMAX_DELAY);	//��ȡ����֪ͨ
//		if(NotifyValue==1)																	//����֮ǰ������ֵ֪ͨΪ1��˵������֪ͨ��Ч
//		{
			pro_dis();
			  vTaskDelay(10);
//		}
				
    }
}
