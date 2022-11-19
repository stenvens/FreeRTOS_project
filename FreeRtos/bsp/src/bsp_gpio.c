#include "bsp_gpio.h"

/**
  * @brief   GPIO≥ı ºªØ   
  * @note    none  
  * @param   none
  * @retval 
  */
void bsp_gpio_init(void)
{
#ifdef STM32F103x
		GPIO_InitTypeDef GPIO_Initure;
	
		__HAL_RCC_GPIOA_CLK_ENABLE();		
		__HAL_RCC_GPIOD_CLK_ENABLE();		
	  UART_CLK();
		__HAL_RCC_AFIO_CLK_ENABLE();
	
		GPIO_Initure.Pin		=UART_TX_PIN;			
		GPIO_Initure.Mode		=GPIO_MODE_AF_PP;		
		GPIO_Initure.Pull		=GPIO_PULLUP;		
		GPIO_Initure.Speed	=GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(UART_TX_PORT,&GPIO_Initure);	

		GPIO_Initure.Pin	=UART_RX_PIN;
		GPIO_Initure.Mode	=GPIO_MODE_AF_INPUT;	
		HAL_GPIO_Init(UART_TX_PORT,&GPIO_Initure);
	
		
		GPIO_Initure.Pin		=GPIO_PIN_8;			
		GPIO_Initure.Mode		=GPIO_MODE_OUTPUT_PP;		
		GPIO_Initure.Pull		=GPIO_PULLUP;		
		GPIO_Initure.Speed	=GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	

		GPIO_Initure.Pin	=GPIO_PIN_2;
		HAL_GPIO_Init(GPIOD,&GPIO_Initure);
	
		
#endif

}

