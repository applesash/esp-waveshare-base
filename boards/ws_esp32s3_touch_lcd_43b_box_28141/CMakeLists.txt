idf_component_register(
	SRCS "src/board_display.c" "src/board_touch.c" "src/board_rtc.c" "src/board_storage.c" "src/board_rs485.c"
	INCLUDE_DIRS "include"
	REQUIRES esp_driver_i2c esp_driver_gpio esp_driver_spi esp_driver_sdspi esp_driver_uart esp_lcd fatfs
)
