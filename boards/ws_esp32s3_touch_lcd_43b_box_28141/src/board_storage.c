#include "board.h"
#include "board_bus_config.h"
#include "board_pins.h"
#include "driver/sdspi_host.h"
#include "esp_check.h"
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"

static const char *TAG = "board_storage_28141";
static sdmmc_card_t *s_card;

esp_err_t board_storage_mount(void)
{
	ESP_RETURN_ON_FALSE(s_card == NULL, ESP_ERR_INVALID_STATE, TAG, "Storage already mounted");
	ESP_RETURN_ON_ERROR(board_ch422g_initialize(), TAG, "Initialize CH422G failed");
	const uint8_t select_sd = 0x0a;
	ESP_RETURN_ON_ERROR(i2c_master_transmit(board_ch422g_output_handle(), &select_sd, 1, 1000), TAG, "Select SD card failed");

	sdmmc_host_t host = SDSPI_HOST_DEFAULT();
	const spi_bus_config_t bus_config = {
		.mosi_io_num = BOARD_SD_SPI_MOSI_GPIO,
		.miso_io_num = BOARD_SD_SPI_MISO_GPIO,
		.sclk_io_num = BOARD_SD_SPI_CLK_GPIO,
		.quadwp_io_num = -1,
		.quadhd_io_num = -1,
		.max_transfer_sz = 4000,
	};
	ESP_RETURN_ON_ERROR(spi_bus_initialize(host.slot, &bus_config, SDSPI_DEFAULT_DMA), TAG, "Initialize SD SPI bus failed");
	sdspi_device_config_t device_config = SDSPI_DEVICE_CONFIG_DEFAULT();
	device_config.gpio_cs = GPIO_NUM_NC;
	device_config.host_id = host.slot;
	const esp_vfs_fat_sdmmc_mount_config_t mount_config = {
		.format_if_mount_failed = false,
		.max_files = 5,
		.allocation_unit_size = 16 * 1024,
	};
	esp_err_t err = esp_vfs_fat_sdspi_mount("/sdcard", &host, &device_config, &mount_config, &s_card);
	if (err != ESP_OK) {
		spi_bus_free(host.slot);
	}
	return err;
}

esp_err_t board_storage_unmount(void)
{
	ESP_RETURN_ON_FALSE(s_card != NULL, ESP_ERR_INVALID_STATE, TAG, "Storage is not mounted");
	esp_vfs_fat_sdcard_unmount("/sdcard", s_card);
	s_card = NULL;
	return spi_bus_free(SPI2_HOST);
}
