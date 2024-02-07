#include "OneWire.hpp"

OneWire(USART_TypeDef *usart, uint32_t baud) {
    usart.Instance = iface;
    usart.Init.BaudRate = 9600;
    usart.Init.WordLength = UART_WORDLENGTH_8B;
    usart.Init.StopBits = UART_STOPBITS_1;
    usart.Init.Parity = UART_PARITY_NONE;
    usart.Init.Mode = UART_MODE_TX_RX;
    usart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    usart.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_HalfDuplex_Init(&usart) != HAL_OK)
    {
#ifdef DEBUG
#endif
        OneWire_Error_Handler();
    }
    return &usart;
}

}