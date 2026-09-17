#include "board.h"
#include "board_bus_config.h"
#include "esp_check.h"

#define PCF85063A_CONTROL_REGISTER 0x00
#define PCF85063A_SECONDS_REGISTER 0x04

static const char *TAG = "board_rtc_28141";

static esp_err_t read_register(i2c_master_dev_handle_t device, uint8_t address, uint8_t *value)
{
	return i2c_master_transmit_receive(device, &address, 1, value, 1, 1000);
}

esp_err_t board_rtc_probe(uint8_t *control, uint8_t *seconds_bcd)
{
	ESP_RETURN_ON_FALSE(control != NULL && seconds_bcd != NULL, ESP_ERR_INVALID_ARG, TAG, "Output pointers are required");
	ESP_RETURN_ON_ERROR(board_i2c_initialize(), TAG, "Initialize shared I2C bus failed");
	const i2c_device_config_t rtc_config = {
		.dev_addr_length = I2C_ADDR_BIT_LEN_7,
		.device_address = BOARD_RTC_I2C_ADDRESS,
		.scl_speed_hz = BOARD_CH422G_I2C_FREQ_HZ,
	};
	i2c_master_dev_handle_t rtc;
	ESP_RETURN_ON_ERROR(i2c_master_bus_add_device(board_i2c_get_handle(), &rtc_config, &rtc), TAG, "Add PCF85063A failed");
	ESP_RETURN_ON_ERROR(read_register(rtc, PCF85063A_CONTROL_REGISTER, control), TAG, "Read PCF85063A control failed");
	return read_register(rtc, PCF85063A_SECONDS_REGISTER, seconds_bcd);
}
