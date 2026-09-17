#include "board.h"
#include "driver/uart.h"
#include "esp_check.h"

#define BOARD_RS485_UART UART_NUM_2
#define BOARD_RS485_TX_GPIO GPIO_NUM_44
#define BOARD_RS485_RX_GPIO GPIO_NUM_43
#define BOARD_RS485_BAUD 115200

static const char *TAG = "board_rs485_28141";

esp_err_t board_rs485_initialize(void)
{
	const uart_config_t config = {
		.baud_rate = BOARD_RS485_BAUD,
		.data_bits = UART_DATA_8_BITS,
		.parity = UART_PARITY_DISABLE,
		.stop_bits = UART_STOP_BITS_1,
		.flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
		.source_clk = UART_SCLK_DEFAULT,
	};
	ESP_RETURN_ON_ERROR(uart_driver_install(BOARD_RS485_UART, 1024, 0, 0, NULL, 0), TAG, "Install UART2 driver failed");
	ESP_RETURN_ON_ERROR(uart_param_config(BOARD_RS485_UART, &config), TAG, "Configure UART2 failed");
	return uart_set_pin(BOARD_RS485_UART, BOARD_RS485_TX_GPIO, BOARD_RS485_RX_GPIO, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
}
