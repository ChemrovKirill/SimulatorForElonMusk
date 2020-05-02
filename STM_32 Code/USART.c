#include "USART.h"

typedef struct {
    uint8_t cmd;
    uint8_t params[10];
    uint8_t active;
} uart_req_t;

static uart_req_t uart_req;

void gpio_config_USART() {
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
	//USART1_TX
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_9, LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetAFPin_8_15(GPIOA, LL_GPIO_PIN_9, LL_GPIO_AF_1);
	LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_9, LL_GPIO_SPEED_FREQ_HIGH);
	//USART1_RX
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_10, LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetAFPin_8_15(GPIOA, LL_GPIO_PIN_10, LL_GPIO_AF_1);
	LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_10, LL_GPIO_SPEED_FREQ_HIGH);
}


void usart_config() {
	LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_USART1);
	LL_RCC_SetUSARTClockSource(LL_RCC_USART1_CLKSOURCE_PCLK1);
	
	LL_USART_SetTransferDirection(USART1, LL_USART_DIRECTION_TX_RX); // Duplex mode
	LL_USART_SetParity(USART1, LL_USART_PARITY_NONE);                // No parity bits
	LL_USART_SetDataWidth(USART1, LL_USART_DATAWIDTH_8B);            // Packet 8 bits
	LL_USART_SetStopBitsLength(USART1, LL_USART_STOPBITS_1);         // One stop bit
	LL_USART_SetTransferBitOrder(USART1, LL_USART_BITORDER_LSBFIRST);// Bit order: less significant ahead
	LL_USART_SetBaudRate(USART1, SystemCoreClock, LL_USART_OVERSAMPLING_16, 115200);          // 115200 baud rate
	LL_USART_EnableIT_IDLE(USART1);                                  // Byte arrival and end of interruption
	LL_USART_EnableIT_RXNE(USART1);
	
	LL_USART_Enable(USART1);
	while (!(LL_USART_IsActiveFlag_TEACK(USART1) && LL_USART_IsActiveFlag_REACK(USART1)));

	NVIC_SetPriority(USART1_IRQn, 0);
	NVIC_EnableIRQ(USART1_IRQn);
}


void USART1_IRQHandler(void)
{
    static uint8_t pos = 0;

    if (LL_USART_IsActiveFlag_RXNE(USART1)) {
        if (pos == 0) {
            uart_req.cmd = LL_USART_ReceiveData8(USART1);
        } else {
            uart_req.params[pos - 1] = LL_USART_ReceiveData8(USART1);
        }
        pos++;
    }
    if (LL_USART_IsActiveFlag_IDLE(USART1)) {
        pos = 0;
        uart_req.active = 1;
        LL_USART_ClearFlag_IDLE(USART1);
    }
    return;
}





void manage_requests(void) {
    uint8_t is_ok = 0;
			
	
    if (!uart_req.active)
        return;
		
		static int count = 1;
		//indicator_4(count, count, 3);

		switch (uart_req.params[count - 1]) { 
			case '0': {	indicator_4(count, 0, 3);	break;	}
			case '1': {	indicator_4(count, 1, 3);	break;	}
			case '2': {	indicator_4(count, 2, 3);	break;	}
			case '3': {	indicator_4(count, 3, 3);	break;	}
			case '4': {	indicator_4(count, 4, 3);	break;	}
			case '5': {	indicator_4(count, 5, 3); break;	}
			case '6': {	indicator_4(count, 6, 3);	break;	}
			case '7': {	indicator_4(count, 7, 3);	break;	}
			case '8': {	indicator_4(count, 8, 3);	break;	}
			case '9': {	indicator_4(count, 9, 3);	break;	}			
		}
		
		++count;
		if(count >= 5) {count = 1;}

		
    while (!LL_USART_IsActiveFlag_TXE(USART1)); // Wait until the channel is released
    //LL_USART_TransmitData8(USART1, is_ok + '0');

		
    uart_req.active = 0;
    return;
}
