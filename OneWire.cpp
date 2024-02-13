#include "OneWire.hpp"
#include "mbed.h"
#ifdef DEBUG
static bool isOneInstance = false; // debug marker multiple instances started
#endif
static struct onewire_iface iface;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* uart) {
    if(iface.bus.Instance != uart) return;
    if(iface.active_cb_rx) iface.active_cb_rx();
    if(iface.inflight_rx_buffer != NULL) {
        iface.inflight_rx_buffer = NULL;
        iface.inflight_rx_buffer_size = 0;
    }
    iface.active_cb_rx = 0;
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef* uart) {
    if (iface.active_cb_tx) iface.active_cb_tx();
    if (iface.inflight_rx_buffer != NULL) {
        onewire_read(iface.inflight_rx_buffer, iface.inflight_rx_buffer_size, iface.active_cb_rx);
    }
    iface.active_cb_tx = 0;
}

void onewire_init(USART_TypeDef* usart, unsigned long baud) {
#ifdef DEBUG
    if(isOneInstance) {
        printf("Mult OW Inst N/A. Will break RELEASE.");
    }
#endif
    iface.bus.Instance = usart;
    iface.bus.Init.BaudRate = 9600;
    iface.bus.Init.WordLength = UART_WORDLENGTH_8B;
    iface.bus.Init.StopBits = UART_STOPBITS_1;
    iface.bus.Init.Parity = UART_PARITY_NONE;
    iface.bus.Init.Mode = UART_MODE_TX_RX;
    iface.bus.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    iface.bus.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_HalfDuplex_Init(&iface.bus) != HAL_OK)
    {
#ifdef DEBUG
#endif
    }
}

// Base methods
void onewire_write_read_blk() {

}
void onewire_write_blk() {}
void onewire_write() {}
void onewire_read_blk(uint8_t buff, size_t n) {}
void onewire_read(uint8_t* buff, size_t n, Callback<void()> cb_fin) {}
void onewire_write_read(uint8_t* tx_buff, size_t tx_n, uint8_t* rx_buf, size_t rx_n, Callback<void()> cb_fin) {
    iface.active_cb_rx = cb_fin;
    HAL_UART_Transmit_IT(&iface.bus, tx_buff, tx_n);
    HAL_UART_Receive_IT();
}
