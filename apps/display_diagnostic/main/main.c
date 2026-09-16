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
#define I2C_SCAN_TIMEOUT_MS 50

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

    printf("display_init=NOT_IMPLEMENTED\n");
    printf("touch_decode=NOT_IMPLEMENTED\n");
    printf("diagnostic_complete=PASS\n");

    while (true) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
