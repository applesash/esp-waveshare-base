#include <string.h>

#include "board_storage.h"
#include "bsp/esp32_s3_touch_lcd_4.h"
#include "driver/gpio.h"
#include "driver/sdmmc_host.h"
#include "esp_check.h"
#include "esp_io_expander.h"
#include "esp_rom_sys.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdmmc_cmd.h"

#define BOARD_I2C_SDA_GPIO GPIO_NUM_15
#define BOARD_I2C_SCL_GPIO GPIO_NUM_7
#define BOARD_SDMMC_CLK_GPIO GPIO_NUM_2
#define BOARD_SDMMC_CMD_GPIO GPIO_NUM_1
#define BOARD_SDMMC_D0_GPIO GPIO_NUM_4

static const char *TAG = "board_storage_28154";

esp_err_t board_storage_prepare(void)
{
	const gpio_config_t bus_pins = {
		.pin_bit_mask = (1ULL << BOARD_I2C_SDA_GPIO) | (1ULL << BOARD_I2C_SCL_GPIO),
		.mode = GPIO_MODE_INPUT,
		.pull_up_en = GPIO_PULLUP_ENABLE,
		.pull_down_en = GPIO_PULLDOWN_DISABLE,
		.intr_type = GPIO_INTR_DISABLE,
	};
	ESP_RETURN_ON_ERROR(gpio_config(&bus_pins), TAG, "Configure I2C recovery pins failed");
	gpio_set_direction(BOARD_I2C_SCL_GPIO, GPIO_MODE_OUTPUT_OD);
	gpio_set_pull_mode(BOARD_I2C_SCL_GPIO, GPIO_PULLUP_ONLY);
	gpio_set_level(BOARD_I2C_SCL_GPIO, 1);
	esp_rom_delay_us(10);
	for (int pulse = 0; pulse < 9 && gpio_get_level(BOARD_I2C_SDA_GPIO) == 0; ++pulse) {
		gpio_set_level(BOARD_I2C_SCL_GPIO, 0);
		esp_rom_delay_us(10);
		gpio_set_level(BOARD_I2C_SCL_GPIO, 1);
		esp_rom_delay_us(10);
	}
	gpio_set_direction(BOARD_I2C_SDA_GPIO, GPIO_MODE_OUTPUT_OD);
	gpio_set_pull_mode(BOARD_I2C_SDA_GPIO, GPIO_PULLUP_ONLY);
	gpio_set_level(BOARD_I2C_SDA_GPIO, 0);
	esp_rom_delay_us(10);
	gpio_set_level(BOARD_I2C_SCL_GPIO, 1);
	esp_rom_delay_us(10);
	gpio_set_level(BOARD_I2C_SDA_GPIO, 1);
	esp_rom_delay_us(10);
	gpio_set_direction(BOARD_I2C_SDA_GPIO, GPIO_MODE_INPUT);
	gpio_set_direction(BOARD_I2C_SCL_GPIO, GPIO_MODE_INPUT);
	gpio_set_pull_mode(BOARD_I2C_SDA_GPIO, GPIO_PULLUP_ONLY);
	gpio_set_pull_mode(BOARD_I2C_SCL_GPIO, GPIO_PULLUP_ONLY);
	vTaskDelay(pdMS_TO_TICKS(20));

	esp_io_expander_handle_t helper = bsp_io_expander_init();
	const uint32_t output_mask = IO_EXPANDER_PIN_NUM_1 |
								 IO_EXPANDER_PIN_NUM_3 |
								 IO_EXPANDER_PIN_NUM_5 |
								 IO_EXPANDER_PIN_NUM_6;
	ESP_RETURN_ON_FALSE(helper != NULL, ESP_FAIL, TAG, "Initialize CH32 helper failed");
	ESP_RETURN_ON_ERROR(esp_io_expander_set_dir(helper, output_mask, IO_EXPANDER_OUTPUT), TAG, "Configure CH32 outputs failed");
	ESP_RETURN_ON_ERROR(esp_io_expander_set_dir(helper, IO_EXPANDER_PIN_NUM_7, IO_EXPANDER_INPUT), TAG, "Configure CH32 input failed");
	ESP_RETURN_ON_ERROR(esp_io_expander_set_level(helper, output_mask, 0), TAG, "Assert CH32 reset levels failed");
	vTaskDelay(pdMS_TO_TICKS(200));
	ESP_RETURN_ON_ERROR(esp_io_expander_set_level(helper,
												   IO_EXPANDER_PIN_NUM_5 |
												   IO_EXPANDER_PIN_NUM_1 |
												   IO_EXPANDER_PIN_NUM_3,
												   1),
						TAG,
						"Release CH32 reset levels failed");
	vTaskDelay(pdMS_TO_TICKS(200));
	return ESP_OK;
}

esp_err_t board_storage_probe(board_storage_card_info_t *card_info)
{
	sdmmc_card_t card = {0};
	sdmmc_host_t host = SDMMC_HOST_DEFAULT();
	sdmmc_slot_config_t slot = SDMMC_SLOT_CONFIG_DEFAULT();
	host.max_freq_khz = SDMMC_FREQ_PROBING;
	slot.clk = BOARD_SDMMC_CLK_GPIO;
	slot.cmd = BOARD_SDMMC_CMD_GPIO;
	slot.d0 = BOARD_SDMMC_D0_GPIO;
	slot.d1 = GPIO_NUM_NC;
	slot.d2 = GPIO_NUM_NC;
	slot.d3 = GPIO_NUM_NC;
	slot.width = 1;
	slot.flags |= SDMMC_SLOT_FLAG_INTERNAL_PULLUP;

	esp_err_t err = sdmmc_host_init();
	if (err == ESP_OK) {
		err = sdmmc_host_init_slot(host.slot, &slot);
	}
	if (err == ESP_OK) {
		err = sdmmc_card_init(&host, &card);
	}
	sdmmc_host_deinit();
	if (err == ESP_OK && card_info != NULL) {
		memset(card_info, 0, sizeof(*card_info));
		memcpy(card_info->name, card.cid.name, sizeof(card.cid.name));
		card_info->capacity_mb = (uint32_t)(((uint64_t)card.csd.capacity * card.csd.sector_size) / (1024 * 1024));
		card_info->max_freq_khz = card.max_freq_khz;
	}
	return err;
}

esp_err_t board_storage_mount(void)
{
	return bsp_sdcard_mount();
}

esp_err_t board_storage_unmount(void)
{
	return bsp_sdcard_unmount();
}
