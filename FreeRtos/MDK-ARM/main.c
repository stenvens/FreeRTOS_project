#include "config.h"
#include "FreeRTOS.h"
#include "task.h"
#include "app_task.h"


//�������ȼ�
#define APP_START_TASK_PRIO		1
//�����ջ��С	
#define APP_START_STK_SIZE 		128  
//������
TaskHandle_t App_StartTask_Handler;
//������
void AppTaskCreate(void *pvParameters);


uint32_t ccc = 0;
int main(void)
{
  BaseType_t xReturn = pdPASS;//����һ��������Ϣ����ֵ��Ĭ��ΪpdPASS
	HAL_Init(); 								//��ʼ��HAL��
	bsp_gpio_init();						//GPIO��ʼ��
	bsp_uartinit(115200);				//��ʼ������
	bsp_timer_init();
	printf("FreeRTOS Test!\n");
	 ccc  = HAL_RCC_GetSysClockFreq();
	/*������ʼ����*/
   xReturn =  xTaskCreate((TaskFunction_t )AppTaskCreate,   //������
                (const char*    )"AppTaskCreate",          //��������
                (uint16_t       )APP_START_STK_SIZE,        //�����ջ��С
                (void*          )NULL,                  		//���ݸ��������Ĳ���
                (UBaseType_t    )APP_START_TASK_PRIO,       //�������ȼ�
                (TaskHandle_t*  )&App_StartTask_Handler);   //������              
  /* ����������� */           
  if(pdPASS == xReturn)
	{
    printf("�����������\n");
		vTaskStartScheduler();   //�������񣬿������� 
	}
	else
	{
		return -1;
	}
      
  /* ��������ִ�е����� */  
  while(1);   
}
