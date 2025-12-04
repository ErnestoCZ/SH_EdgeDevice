#include "cuart.h"
#include <zephyr/drivers/uart.h>
#include <zephyr/logging/log.h>
#include <zephyr/devicetree.h>
#include <string.h>
LOG_MODULE_REGISTER(cuart, LOG_LEVEL_ERR);

//TODO buffer management
static char rx_buffer[256];
static const struct device *uart_dev = DEVICE_DT_GET(DT_NODELABEL(uart1));
static struct uart_config uart_cfg = {
    .baudrate = 115200,
    .parity = UART_CFG_PARITY_NONE,
    .stop_bits = UART_CFG_STOP_BITS_1,
    .data_bits = UART_CFG_DATA_BITS_8,
    .flow_ctrl = UART_CFG_FLOW_CTRL_NONE,
};
void uart_callback(const struct device *dev,
                   struct uart_event *evt,
                   void *user_data) {
    switch (evt->type) {
        case UART_RX_RDY:
            // Handle received data
            LOG_INF("Received %d bytes", evt->data.rx.len);
            //TODO push task to work queue to process rx_data
            strcpy(rx_buffer, (char *)evt->data.rx.buf);

            break;
        case UART_TX_DONE:
            // Handle transmission complete
            break;
        case UART_RX_DISABLED:
            // Handle RX disabled event
            LOG_INF("UART RX disabled");
            break;
        case UART_RX_BUF_REQUEST:
            // Handle buffer request
            break;
        case UART_RX_BUF_RELEASED:
            // Handle buffer released
            break;
        case UART_TX_ABORTED:
            // Handle transmission aborted
            break;
        default:
            break;
    }
}


void init_uart(void) {
  if (!device_is_ready(uart_dev)) {
    LOG_ERR("UART device not ready");
    return;
  }
    int ret = uart_configure(uart_dev, &uart_cfg);
    if (ret != 0) {
        LOG_ERR("Failed to configure UART");
    }

    uart_irq_rx_enable(uart_dev);
    uart_callback_set(uart_dev, uart_callback, NULL);
}


