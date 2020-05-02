#ifndef __INDICATOR__
#define __INDICATOR__

#include <stdio.h>

#include "stm32f0xx.h"

#include "Lib/stm32f0xx_ll_rcc.h"
#include "Lib/stm32f0xx_ll_system.h"
#include "Lib/stm32f0xx_ll_bus.h"
#include "Lib/stm32f0xx_ll_gpio.h"

#define P0 LL_GPIO_PIN_0
#define P1 LL_GPIO_PIN_1
#define P2 LL_GPIO_PIN_2
#define P3 LL_GPIO_PIN_10
#define P4 LL_GPIO_PIN_3
#define P5 LL_GPIO_PIN_4
#define P6 LL_GPIO_PIN_5
#define P7 LL_GPIO_PIN_6

#define PI1 LL_GPIO_PIN_4
#define PI2 LL_GPIO_PIN_5
#define PI3 LL_GPIO_PIN_6
#define PI4 LL_GPIO_PIN_7

#define GP GPIOB
#define GP2 GPIOA

void indicator_1(int number);
void indicator_4(int indicator, int number, int decimal);





#endif //__INDICATOR__
