#ifndef __USART__
#define __USART__

#include "stm32f0xx.h"

#include "Lib/stm32f0xx_ll_rcc.h"
#include "Lib/stm32f0xx_ll_system.h"
#include "Lib/stm32f0xx_ll_bus.h"
#include "Lib/stm32f0xx_ll_gpio.h"
#include "Lib/stm32f0xx_ll_usart.h"

#include "indicator.h"

void gpio_config_USART();
void usart_config();

void manage_requests(void);


#endif //__USART__
