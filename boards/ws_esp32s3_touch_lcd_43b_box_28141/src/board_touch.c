#include <string.h>

#include "board.h"
#include "board_bus_config.h"
#include "board_pins.h"
#include "driver/gpio.h"
#include "driver/i2c_master.h"
#include "esp_check.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define GT911_PRODUCT_ID_REGISTER 0x8140
#define GT911_STATUS_REGISTER 0x814e
#define GT911_POINT_REGISTER 0x8150

static const char *TAG = "board_touch_28141";
static i2c_master_dev_handle_t s_touch_handle;

static esp_err_t read_register(uint16_t address, uint8_t *data, size_t length)
{
    const uint8_t register_address[] = { address >> 8, address & 0xff };
    return i2c_master_transmit_receive(s_touch_handle, register_address, sizeof(register_address), data, length, 1000);
}

esp_err_t board_touch_probe(char product_id[5])
{
    ESP_RETURN_ON_ERROR(board_i2c_initialize(), TAG, "Create touch I2C bus failed");
    i2c_master_bus_handle_t bus = board_i2c_get_handle();
    ESP_RETURN_ON_FALSE(bus != NULL, ESP_ERR_INVALID_STATE, TAG, "Touch I2C bus unavailable");
    ESP_RETURN_ON_ERROR(board_ch422g_initialize(), TAG, "Initialize CH422G failed");
    const i2c_device_config_t touch_config = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = BOARD_GT911_I2C_ADDRESS,
        .scl_speed_hz = BOARD_CH422G_I2C_FREQ_HZ,
    };
    if (s_touch_handle == NULL) {
        ESP_RETURN_ON_ERROR(i2c_master_bus_add_device(bus, &touch_config, &s_touch_handle), TAG, "Add GT911 device failed");
    }

    uint8_t reset_assert = 0x2c;
    uint8_t reset_release = 0x2e;
    ESP_RETURN_ON_ERROR(i2c_master_transmit(board_ch422g_output_handle(), &reset_assert, 1, 1000), TAG, "Assert GT911 reset failed");
    vTaskDelay(pdMS_TO_TICKS(100));
    gpio_set_direction(BOARD_TOUCH_INTERRUPT_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_level(BOARD_TOUCH_INTERRUPT_GPIO, 0);
    vTaskDelay(pdMS_TO_TICKS(100));
    ESP_RETURN_ON_ERROR(i2c_master_transmit(board_ch422g_output_handle(), &reset_release, 1, 1000), TAG, "Release GT911 reset failed");
    vTaskDelay(pdMS_TO_TICKS(200));

    const uint8_t register_address[] = { GT911_PRODUCT_ID_REGISTER >> 8, GT911_PRODUCT_ID_REGISTER & 0xff };
    uint8_t response[4] = {0};
    ESP_RETURN_ON_ERROR(i2c_master_transmit_receive(s_touch_handle, register_address, sizeof(register_address), response, sizeof(response), 1000), TAG, "Read GT911 product ID failed");
    if (product_id != NULL) {
        memcpy(product_id, response, sizeof(response));
        product_id[4] = '\0';
    }
    return ESP_OK;
}

esp_err_t board_touch_read(uint8_t *count, uint16_t *x, uint16_t *y, uint16_t *size)
{
    ESP_RETURN_ON_FALSE(s_touch_handle != NULL, ESP_ERR_INVALID_STATE, TAG, "GT911 is not initialized");
    uint8_t status = 0;
    ESP_RETURN_ON_ERROR(read_register(GT911_STATUS_REGISTER, &status, 1), TAG, "Read GT911 status failed");
    if ((status & 0x80) == 0) {
        return ESP_ERR_NOT_FOUND;
    }
    uint8_t point[8] = {0};
    *count = status & 0x0f;
    if (*count > 0) {
        ESP_RETURN_ON_ERROR(read_register(GT911_POINT_REGISTER, point, sizeof(point)), TAG, "Read GT911 point failed");
        *x = (uint16_t)point[0] | ((uint16_t)point[1] << 8);
        *y = (uint16_t)point[2] | ((uint16_t)point[3] << 8);
        *size = (uint16_t)point[4] | ((uint16_t)point[5] << 8);
    }
    const uint8_t clear_status[] = { GT911_STATUS_REGISTER >> 8, GT911_STATUS_REGISTER & 0xff, 0 };
    return i2c_master_transmit(s_touch_handle, clear_status, sizeof(clear_status), 1000);
}
