idf_component_register(
	SRCS "src/board_storage.c"
	INCLUDE_DIRS "include"
	REQUIRES esp32_s3_touch_lcd_4 esp_driver_gpio esp_driver_sdmmc fatfs
)
