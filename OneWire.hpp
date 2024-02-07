#include "stm32f4xx_hal_usart.h"

class OneWire {
    protected:
    UART_HandleTypeDef usart;
    OneWire(USART_TypeDef* usart, uint32_t baud);

}