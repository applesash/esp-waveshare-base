#pragma once

#include "esp_err.h"
#include "esp_lcd_panel_ops.h"
#include "driver/i2c_master.h"

esp_err_t board_i2c_initialize(void);
i2c_master_bus_handle_t board_i2c_get_handle(void);
esp_err_t board_ch422g_initialize(void);
i2c_master_dev_handle_t board_ch422g_output_handle(void);
esp_err_t board_display_initialize(esp_lcd_panel_handle_t *panel);
esp_err_t board_display_draw_test_pattern(esp_lcd_panel_handle_t panel);
esp_err_t board_touch_probe(char product_id[5]);
esp_err_t board_touch_read(uint8_t *count, uint16_t *x, uint16_t *y, uint16_t *size);
esp_err_t board_rtc_probe(uint8_t *control, uint8_t *seconds_bcd);
esp_err_t board_storage_mount(void);
esp_err_t board_storage_unmount(void);
esp_err_t board_rs485_initialize(void);
