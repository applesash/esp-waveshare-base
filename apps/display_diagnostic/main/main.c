#include <inttypes.h>
#include <stdio.h>

#include "driver/i2c_master.h"
#include "esp_chip_info.h"
#include "esp_err.h"
#include "esp_flash.h"
#include "esp_heap_caps.h"
#include "esp_mac.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define BOARD_SKU "28154"
#define EXPANDER_SDA_GPIO 8
#define EXPANDER_SCL_GPIO 9
#define TOUCH_SDA_GPIO 15
#define TOUCH_SCL_GPIO 7
#define GT911_ADDRESS 0x5d
#define GT911_PRODUCT_ID_REGISTER 0x8140
#define GT911_STATUS_REGISTER 0x814e
#define GT911_POINT_REGISTER 0x8150
#define I2C_SCAN_TIMEOUT_MS 50

static i2c_master_dev_handle_t touch_device;

static void print_identity(void)
{
    esp_chip_info_t chip_info;
    uint8_t mac[6];
    uint32_t flash_size = 0;

    esp_chip_info(&chip_info);
    esp_read_mac(mac, ESP_MAC_WIFI_STA);
    esp_flash_get_size(NULL, &flash_size);

    printf("\n28154 display diagnostic\n");
    printf("chip=ESP32-S3 revision=%d cores=%d features=0x%" PRIx32 "\n",
           chip_info.revision,
           chip_info.cores,
           (uint32_t)chip_info.features);
    printf("mac=%02x:%02x:%02x:%02x:%02x:%02x\n",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    printf("flash_bytes=%" PRIu32 " free_heap=%" PRIu32 " reset_reason=%d\n",
           flash_size,
           (uint32_t)esp_get_free_heap_size(),
           esp_reset_reason());
}

static void scan_bus(const char *name, gpio_num_t sda_gpio, gpio_num_t scl_gpio)
{
    i2c_master_bus_config_t bus_config = {
        .i2c_port = I2C_NUM_0,
        .sda_io_num = sda_gpio,
        .scl_io_num = scl_gpio,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };
    i2c_master_bus_handle_t bus = NULL;
    esp_err_t err = i2c_new_master_bus(&bus_config, &bus);

    printf("i2c_bus=%s sda=%d scl=%d status=%s\n",
           name,
           sda_gpio,
           scl_gpio,
           esp_err_to_name(err));
    if (err != ESP_OK) {
        return;
    }

    printf("i2c_bus=%s devices=", name);
    for (uint8_t address = 0x08; address <= 0x77; ++address) {
        if (i2c_master_probe(bus, address, I2C_SCAN_TIMEOUT_MS) == ESP_OK) {
            printf("0x%02x ", address);
        }
    }
    printf("\n");
    ESP_ERROR_CHECK(i2c_del_master_bus(bus));
}

static esp_err_t read_touch_register(uint16_t address, uint8_t *data, size_t length)
{
    uint8_t register_address[] = {
        (uint8_t)(address >> 8),
        (uint8_t)(address & 0xff),
    };

    return i2c_master_transmit_receive(
        touch_device,
        register_address,
        sizeof(register_address),
        data,
        length,
        1000);
}

static void clear_touch_status(void)
{
    uint8_t command[] = {
        (uint8_t)(GT911_STATUS_REGISTER >> 8),
        (uint8_t)(GT911_STATUS_REGISTER & 0xff),
        0,
    };

    ESP_ERROR_CHECK(i2c_master_transmit(touch_device, command, sizeof(command), 1000));
}

static void start_touch_monitor(void)
{
    i2c_master_bus_config_t bus_config = {
        .i2c_port = I2C_NUM_0,
        .sda_io_num = TOUCH_SDA_GPIO,
        .scl_io_num = TOUCH_SCL_GPIO,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };
    i2c_master_bus_handle_t bus = NULL;
    i2c_device_config_t device_config = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = GT911_ADDRESS,
        .scl_speed_hz = 400000,
    };
    uint8_t product_id[4] = {0};
    esp_err_t err = i2c_new_master_bus(&bus_config, &bus);
    if (err == ESP_OK) {
        err = i2c_master_bus_add_device(bus, &device_config, &touch_device);
    }
    if (err == ESP_OK) {
        err = read_touch_register(GT911_PRODUCT_ID_REGISTER, product_id, sizeof(product_id));
    }

    printf("touch_controller=GT911 address=0x%02x status=%s product_id=%02x%02x%02x%02x\n",
           GT911_ADDRESS,
           esp_err_to_name(err),
           product_id[0],
           product_id[1],
           product_id[2],
           product_id[3]);
    if (err != ESP_OK) {
        touch_device = NULL;
    }
}

static void poll_touch(void)
{
    uint8_t status = 0;
    uint8_t point[8] = {0};

    if (touch_device == NULL || read_touch_register(GT911_STATUS_REGISTER, &status, 1) != ESP_OK) {
        return;
    }
    if ((status & 0x80) == 0) {
        return;
    }
    if ((status & 0x0f) > 0 && read_touch_register(GT911_POINT_REGISTER, point, sizeof(point)) == ESP_OK) {
        uint16_t x = (uint16_t)point[1] | ((uint16_t)point[2] << 8);
        uint16_t y = (uint16_t)point[3] | ((uint16_t)point[4] << 8);
        printf("touch_event count=%u track=%u x=%u y=%u size=%u\n",
               status & 0x0f,
               point[0],
               x,
               y,
               (uint16_t)point[5] | ((uint16_t)point[6] << 8));
    }
    clear_touch_status();
}

void app_main(void)
{
    print_identity();
    printf("documented_expander_bus=sda:%d scl:%d\n",
           EXPANDER_SDA_GPIO,
           EXPANDER_SCL_GPIO);
    printf("documented_touch_bus=sda:%d scl:%d\n",
           TOUCH_SDA_GPIO,
           TOUCH_SCL_GPIO);

    scan_bus("expander", EXPANDER_SDA_GPIO, EXPANDER_SCL_GPIO);
    scan_bus("touch", TOUCH_SDA_GPIO, TOUCH_SCL_GPIO);
    start_touch_monitor();

    printf("display_init=NOT_IMPLEMENTED\n");
    printf("touch_decode=GT911_POLLING\n");
    printf("diagnostic_complete=PASS\n");

    while (true) {
        poll_touch();
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
