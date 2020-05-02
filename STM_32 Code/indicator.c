#include "indicator.h"

void indicator_1(int number){
	
	static uint32_t mask = P0 | P1 | P2 | P3 | P4 | P5 | P6 | P7;

	static const uint32_t decoder[] = {
        P0 | P1 | P2 | P6 | P4 | P5, // 0
        P2 | P4 , // 1
        P0 | P1 | P7 | P5 | P4, // 2
        P5 | P1 | P7 | P2 | P4, // 3
        P6 | P7 | P4 | P2, // 4
		    P6 | P7 | P5 | P2 | P1, // 5
        P6 | P7 | P5 | P2 | P1 | P0, //6
        P5 | P4 | P2, // 7
        P6 | P7 | P4 | P2 | P1 | P0 | P5, // 8
        P6 | P7 | P4 | P2 | P1 | P5, // 9
    };
  const uint8_t max_num = sizeof(decoder) / sizeof(uint32_t);
		
  uint32_t port_state = 0;
  port_state = LL_GPIO_ReadOutputPort(GP);
  port_state = (port_state & ~mask) | decoder[number % max_num];
  LL_GPIO_WriteOutputPort(GP, port_state);
}


void indicator_4(int indicator, int number, int decimal){

	static uint32_t mask = P0 | P1 | P2 | P3 | P4 | P5 | P6 | P7;

	// P0 - left down
	// P1 - down
	// P2 - right down
	// P3 - middle
	// P4 - decimal point
	// P5 - right up
	// P6 - left up
	// P7 - up
	
	static const uint32_t decoder[] = {
        P4 | P3, // 0
        P6 | P3 | P4 | P7 | P1 | P0, // 1
        P2 | P6 | P4, // 2
        P0 | P6 | P4, // 3
        P0 | P1 | P4 | P7, // 4
		    P0 | P5 | P4, // 5
        P5 | P4, //6
        P0 | P1 | P3 | P4 | P6, // 7
        P4, // 8
				P4 | P0, // 9
    };
  const uint8_t max_num = sizeof(decoder) / sizeof(uint32_t);
		
  uint32_t port_state = 0;
  port_state = LL_GPIO_ReadOutputPort(GP);
  port_state = (port_state & ~mask) | decoder[number % max_num];
  LL_GPIO_WriteOutputPort(GP, port_state);

	switch (indicator) {
		case 1: {
			LL_GPIO_SetOutputPin(GP2, PI1); 
			LL_GPIO_ResetOutputPin(GP2, PI2); 
			LL_GPIO_ResetOutputPin(GP2, PI3); 
			LL_GPIO_ResetOutputPin(GP2, PI4); 
			break;
		}
		case 2: {
			LL_GPIO_ResetOutputPin(GP2, PI1); 
			LL_GPIO_SetOutputPin(GP2, PI2); 
			LL_GPIO_ResetOutputPin(GP2, PI3); 
			LL_GPIO_ResetOutputPin(GP2, PI4); 
			break;
		}
		case 3: {
			LL_GPIO_ResetOutputPin(GP2, PI1); 
			LL_GPIO_ResetOutputPin(GP2, PI2); 
			LL_GPIO_SetOutputPin(GP2, PI3); 
			LL_GPIO_ResetOutputPin(GP2, PI4); 
			break;
		}
		case 4: {
			LL_GPIO_ResetOutputPin(GP2, PI1); 
			LL_GPIO_ResetOutputPin(GP2, PI2); 
			LL_GPIO_ResetOutputPin(GP2, PI3); 
			LL_GPIO_SetOutputPin(GP2, PI4); 
			break;
		}
	}
	
	if(decimal == indicator) {
		LL_GPIO_ResetOutputPin(GP, P4); 
	}
	else {
		LL_GPIO_SetOutputPin(GP, P4); 
	}
}
