#include "board.h"
#include "board_bus_config.h"
#include "board_display_timing.h"
#include "board_pins.h"
#include "driver/i2c_master.h"
#include "esp_check.h"
#include "esp_lcd_panel_rgb.h"

static const char *TAG = "board_display_28141";
static i2c_master_bus_handle_t s_i2c_bus;
static i2c_master_dev_handle_t s_ch422g_config;
static i2c_master_dev_handle_t s_ch422g_output;

esp_err_t board_i2c_initialize(void)
{
	if (s_i2c_bus != NULL) {
		return ESP_OK;
	}
	const i2c_master_bus_config_t bus_config = {
		.i2c_port = BOARD_CH422G_I2C_PORT,
		.sda_io_num = BOARD_CH422G_I2C_SDA_GPIO,
		.scl_io_num = BOARD_CH422G_I2C_SCL_GPIO,
		.clk_source = I2C_CLK_SRC_DEFAULT,
	};
	return i2c_new_master_bus(&bus_config, &s_i2c_bus);
}

i2c_master_bus_handle_t board_i2c_get_handle(void)
{
	return s_i2c_bus;
}

esp_err_t board_ch422g_initialize(void)
{
	if (s_ch422g_output != NULL) {
		return ESP_OK;
	}
	ESP_RETURN_ON_ERROR(board_i2c_initialize(), TAG, "Create CH422G bus failed");
	const i2c_device_config_t config_device = {
		.dev_addr_length = I2C_ADDR_BIT_LEN_7,
		.device_address = BOARD_CH422G_CONFIGURATION_ADDRESS,
		.scl_speed_hz = BOARD_CH422G_I2C_FREQ_HZ,
	};
	const i2c_device_config_t output_device = {
		.dev_addr_length = I2C_ADDR_BIT_LEN_7,
		.device_address = BOARD_CH422G_OUTPUT_ADDRESS,
		.scl_speed_hz = BOARD_CH422G_I2C_FREQ_HZ,
	};
	ESP_RETURN_ON_ERROR(i2c_master_bus_add_device(s_i2c_bus, &config_device, &s_ch422g_config), TAG, "Add CH422G config device failed");
	ESP_RETURN_ON_ERROR(i2c_master_bus_add_device(s_i2c_bus, &output_device, &s_ch422g_output), TAG, "Add CH422G output device failed");
	const uint8_t output_mode = 0x01;
	ESP_RETURN_ON_ERROR(i2c_master_transmit(s_ch422g_config, &output_mode, 1, 1000), TAG, "Set CH422G output mode failed");
	return ESP_OK;
}

i2c_master_dev_handle_t board_ch422g_output_handle(void)
{
	return s_ch422g_output;
}

esp_err_t board_display_initialize(esp_lcd_panel_handle_t *panel)
{
	ESP_RETURN_ON_FALSE(panel != NULL, ESP_ERR_INVALID_ARG, TAG, "Panel handle is required");
	ESP_RETURN_ON_ERROR(board_ch422g_initialize(), TAG, "Initialize CH422G failed");
	const uint8_t backlight_on = 0x1e;
	ESP_RETURN_ON_ERROR(i2c_master_transmit(s_ch422g_output, &backlight_on, 1, 1000), TAG, "Enable backlight failed");
	const esp_lcd_rgb_panel_config_t panel_config = {
		.clk_src = LCD_CLK_SRC_DEFAULT,
		.data_width = 16,
		.bits_per_pixel = 16,
		.num_fbs = 1,
		.timings = {
			.pclk_hz = BOARD_LCD_PIXEL_CLOCK_HZ,
			.h_res = BOARD_LCD_HORIZONTAL_RESOLUTION,
			.v_res = BOARD_LCD_VERTICAL_RESOLUTION,
			.hsync_pulse_width = BOARD_LCD_HSYNC_PULSE_WIDTH,
			.hsync_back_porch = BOARD_LCD_HSYNC_BACK_PORCH,
			.hsync_front_porch = BOARD_LCD_HSYNC_FRONT_PORCH,
			.vsync_pulse_width = BOARD_LCD_VSYNC_PULSE_WIDTH,
			.vsync_back_porch = BOARD_LCD_VSYNC_BACK_PORCH,
			.vsync_front_porch = BOARD_LCD_VSYNC_FRONT_PORCH,
			.flags.pclk_active_neg = BOARD_LCD_PCLK_ACTIVE_NEGATIVE,
		},
		.hsync_gpio_num = BOARD_LCD_RGB_HSYNC_GPIO,
		.vsync_gpio_num = BOARD_LCD_RGB_VSYNC_GPIO,
		.de_gpio_num = BOARD_LCD_RGB_DE_GPIO,
		.pclk_gpio_num = BOARD_LCD_RGB_PCLK_GPIO,
		.data_gpio_nums = { BOARD_LCD_RGB_DATA0_GPIO, BOARD_LCD_RGB_DATA1_GPIO, BOARD_LCD_RGB_DATA2_GPIO, BOARD_LCD_RGB_DATA3_GPIO, BOARD_LCD_RGB_DATA4_GPIO, BOARD_LCD_RGB_DATA5_GPIO, BOARD_LCD_RGB_DATA6_GPIO, BOARD_LCD_RGB_DATA7_GPIO, BOARD_LCD_RGB_DATA8_GPIO, BOARD_LCD_RGB_DATA9_GPIO, BOARD_LCD_RGB_DATA10_GPIO, BOARD_LCD_RGB_DATA11_GPIO, BOARD_LCD_RGB_DATA12_GPIO, BOARD_LCD_RGB_DATA13_GPIO, BOARD_LCD_RGB_DATA14_GPIO, BOARD_LCD_RGB_DATA15_GPIO },
		.flags.fb_in_psram = true,
	};
	ESP_RETURN_ON_ERROR(esp_lcd_new_rgb_panel(&panel_config, panel), TAG, "Create RGB panel failed");
	return esp_lcd_panel_init(*panel);
}

esp_err_t board_display_draw_test_pattern(esp_lcd_panel_handle_t panel)
{
	ESP_RETURN_ON_FALSE(panel != NULL, ESP_ERR_INVALID_ARG, TAG, "Panel handle is required");
	uint16_t line[BOARD_LCD_HORIZONTAL_RESOLUTION];
	for (int y = 0; y < BOARD_LCD_VERTICAL_RESOLUTION; ++y) {
		const uint16_t color = y < BOARD_LCD_VERTICAL_RESOLUTION / 3 ? 0xf800 :
							   y < (BOARD_LCD_VERTICAL_RESOLUTION * 2) / 3 ? 0x07e0 : 0x001f;
		for (int x = 0; x < BOARD_LCD_HORIZONTAL_RESOLUTION; ++x) {
			line[x] = color;
		}
		ESP_RETURN_ON_ERROR(esp_lcd_panel_draw_bitmap(panel, 0, y, BOARD_LCD_HORIZONTAL_RESOLUTION, y + 1, line), TAG, "Draw test pattern failed");
	}
	return ESP_OK;
}
