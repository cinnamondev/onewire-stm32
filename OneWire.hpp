#include "stm32f4xx_hal_uart.h"
#include "mbed.h"

struct onewire_iface {
    Mutex lock;
    UART_HandleTypeDef bus;
    Callback<void()> active_cb_rx = 0;
    Callback<void()> active_cb_tx = 0;
    uint8_t* inflight_rx_buffer = NULL;
    size_t inflight_rx_buffer_size = 0;
};

/**
 * @brief Write bytes to OneWire bus (blocking)
 * 
 */
void onewire_write_blk();
/**
 * @brief Write bytes to OneWire Bus (non-blocking)
 * 
 */
void onewire_write();
void onewire_read_blk(uint8_t buff, size_t n);
void onewire_read(uint8_t* buff, size_t n, Callback<void()> cb_fin);
// Internally, onewire_read_blind will not remove callbacks, but it will
// not intentionally set them. States that use callbacks will generally clear them once
// they are done, so this can be used in edge cases where you do not need to update the callback
// (edge cases defined in HAL_UART_{RX/TX}CpltCallback)

void onewire_write_read_blk();
/**
 * @brief Write & Read bytes from OneWire bus (Non-blocking)
 * 
 * @param tx_buff 
 * @param tx_n 
 * @param rx_buf 
 * @param rx_n 
 * @param cb_fin 
 */
void onewire_write_read(uint8_t* tx_buff, size_t tx_n, uint8_t* rx_buf, size_t rx_n, Callback<void()> cb_fin);