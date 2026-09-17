#include <stdio.h>

#include "board.h"
#include "esp_err.h"
#include "esp_lcd_panel_ops.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
    esp_lcd_panel_handle_t panel = NULL;
    char touch_product_id[5] = {0};
    esp_err_t storage_error = board_storage_mount();
    printf("storage_mount=%s\n", esp_err_to_name(storage_error));
    if (storage_error == ESP_OK) {
        printf("storage=PASS read_only_mount=1\n");
        board_storage_unmount();
    }
    ESP_ERROR_CHECK(board_display_initialize(&panel));
    ESP_ERROR_CHECK(board_display_draw_test_pattern(panel));
    printf("display=PASS sku=28141 resolution=800x480\n");
    esp_err_t rs485_error = board_rs485_initialize();
    printf("rs485_initialize=%s uart=2 tx_gpio=44 rx_gpio=43\n", esp_err_to_name(rs485_error));
    uint8_t rtc_control = 0;
    uint8_t rtc_seconds_bcd = 0;
    esp_err_t rtc_error = board_rtc_probe(&rtc_control, &rtc_seconds_bcd);
    printf("rtc=%s address=0x51 control=0x%02x seconds_bcd=0x%02x\n",
           esp_err_to_name(rtc_error), rtc_control, rtc_seconds_bcd);
    esp_err_t touch_error = board_touch_probe(touch_product_id);
    printf("touch=%s controller=GT911 address=0x5d product_id=%s\n",
           esp_err_to_name(touch_error),
           touch_error == ESP_OK ? touch_product_id : "unavailable");
    while (touch_error == ESP_OK) {
        uint8_t count = 0;
        uint16_t x = 0;
        uint16_t y = 0;
        uint16_t size = 0;
        esp_err_t read_error = board_touch_read(&count, &x, &y, &size);
        if (read_error == ESP_OK && count > 0) {
            printf("touch_event count=%u x=%u y=%u size=%u\n", count, x, y, size);
        } else if (read_error != ESP_OK && read_error != ESP_ERR_NOT_FOUND) {
            printf("touch_read=%s\n", esp_err_to_name(read_error));
        }
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}