/* Header file for our microcontroller family */
#include <stdio.h>

#include "stm32f0xx.h"

#include "Lib/stm32f0xx_ll_rcc.h"
#include "Lib/stm32f0xx_ll_system.h"
#include "Lib/stm32f0xx_ll_bus.h"
#include "Lib/stm32f0xx_ll_gpio.h"
#include "Lib/stm32f0xx_ll_usart.h"

#include "indicator.h"
#include "USART.h"

static void gpio_config(void) {
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
  LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_8, LL_GPIO_MODE_OUTPUT);
  LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_9, LL_GPIO_MODE_OUTPUT);

	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_0, LL_GPIO_MODE_INPUT);
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_1, LL_GPIO_MODE_INPUT);
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_2, LL_GPIO_MODE_INPUT);
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_3, LL_GPIO_MODE_INPUT);
	
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_4, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_5, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_6, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_7, LL_GPIO_MODE_OUTPUT);

	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_0, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_1, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_2, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_10, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_3, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_4, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_5, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_6, LL_GPIO_MODE_OUTPUT);

  return;
}

void wait(float x) {
	for(int i = 0; i < 1000 * x; ++i) {}
}


int main(void) {
	
	gpio_config();
	gpio_config_USART();

	usart_config();
	
	
	
	int status;
	int number = 0;
	
	int button_pressed;
	int debouncer_clk = 0;
	
	
	
	LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_9); 

	while(1) {
		unsigned char message = 128;
		if (LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_1)) {
			message += 64;
		}
		if (LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_2)) {
			message += 32;
		}
		if (LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_3)) {
			message += 16;
		}

		
		if (LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_1) || LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_2) || LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_3)) {
			LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_8);
		}
		else{
			LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_8);
		}		
		
		LL_USART_TransmitData8(USART1, message);			

    manage_requests();		
		
		wait(0.1);		
	}
}
