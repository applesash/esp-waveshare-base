# GPIO and I/O Register

| Signal | ESP32 GPIO | Expander channel | Direction | Active level | Pull | Boot state | Safe state | Source | Status |
|---|---:|---|---|---|---|---|---|---|---|
| Exact GPIO map | N/A | N/A | N/A | N/A | N/A | N/A | N/A | https://www.waveshare.com/esp32-s3-touch-lcd-4.3b.htm?sku=28141; https://docs.waveshare.com/ESP32-S3-Touch-LCD-4.3B | UNVERIFIED |
| CH422G_I2C_SCL | GPIO9 | N/A | I2C | N/A | N/A | N/A | N/A | Official 4.3B-BOX ESP-IDF `03_SD_Test/sdkconfig.defaults` | VERIFIED |
| CH422G_I2C_SDA | GPIO8 | N/A | I2C | N/A | N/A | N/A | N/A | Official 4.3B-BOX ESP-IDF `03_SD_Test/sdkconfig.defaults` | VERIFIED |
| CH422G_CONTROL | GPIO8/GPIO9 | I2C writes `0x24`, `0x38` | I/O expander control | N/A | N/A | N/A | N/A | Official 4.3B-BOX ESP-IDF `03_SD_Test/main/sd_card.c` | VERIFIED; exact channel map pending |
| SD_CARD_CS | N/A | CH422G EXIO4 | Output | active level pending | N/A | N/A | N/A | https://www.waveshare.com/wiki/ESP32-S3-Touch-LCD-4.3B | VERIFIED |
| SD_SPI_MOSI | GPIO11 | N/A | Output | N/A | N/A | N/A | N/A | Official 4.3B-BOX ESP-IDF `03_SD_Test/sdkconfig.defaults` | VERIFIED |
| SD_SPI_MISO | GPIO13 | N/A | Input | N/A | N/A | N/A | N/A | Official 4.3B-BOX ESP-IDF `03_SD_Test/sdkconfig.defaults` | VERIFIED |
| SD_SPI_CLK | GPIO12 | N/A | Output | N/A | N/A | N/A | N/A | Official 4.3B-BOX ESP-IDF `03_SD_Test/sdkconfig.defaults` | VERIFIED |
| TOUCH_IRQ | GPIO4 | N/A | Input after reset | N/A | N/A | N/A | N/A | Official 4.3B schematic, `CTP_IRQ` net | VERIFIED |
| TOUCH_RST | N/A | CH422G EXIO1 | Output | low assert, high release | N/A | N/A | N/A | Official 4.3B schematic, `CTP_RST` net; official `08_lvgl_Porting` reset sequence | VERIFIED |
| GT911 | GPIO8/GPIO9 | N/A | I2C | address 0x5d | N/A | N/A | N/A | Official 4.3B wiki I2C address table; official `08_lvgl_Porting` GT911 configuration | VERIFIED |
| LCD_RESET | N/A | CH422G EXIO3 | Output | low assert, high release | N/A | initial state source sequence asserts low | safe state requires policy | Official 4.3B-BOX Arduino `esp_panel_board_custom_conf.h` | VERIFIED |
| BACKLIGHT | N/A | CH422G EXIO2 | Output | high on, low off | N/A | configuration idle-on | low is source-backed off state | Official 4.3B-BOX Arduino `esp_panel_board_custom_conf.h` | VERIFIED |
| ISOLATED_DI0 | N/A | CH422G IO0 | Input | source test reads high when paired DO0 is high | N/A | input | N/A | Official 4.3B-BOX Arduino `05_IO_Test/waveshare_io_port.h` | VERIFIED |
| ISOLATED_DI1 | N/A | CH422G IO5 | Input | source test reads high when paired DO1 is high | N/A | input | N/A | Official 4.3B-BOX Arduino `05_IO_Test/waveshare_io_port.h` | VERIFIED |
| ISOLATED_DO0 | N/A | CH422G OC8 | Output | high observed as loopback active | N/A | source test initializes high | safe external state requires policy | Official 4.3B-BOX Arduino `05_IO_Test/waveshare_io_port.h`; `waveshare_io_port.cpp` | VERIFIED |
| ISOLATED_DO1 | N/A | CH422G OC9 | Output | high observed as loopback active | N/A | source test initializes high | safe external state requires policy | Official 4.3B-BOX Arduino `05_IO_Test/waveshare_io_port.h`; `waveshare_io_port.cpp` | VERIFIED |
| RTC | GPIO8/GPIO9 | N/A | I2C | address 0x51 | N/A | N/A | N/A | Official 4.3B-BOX ESP-IDF `04_RTC_Test/main/rtc_pcf85063a.h` | VERIFIED |
| RTC_INTERRUPT | GPIO mapping pending | CH422G IO6 path | Input | N/A | N/A | N/A | N/A | Official 4.3B schematic `RTC_INT` net | VERIFIED; direct ESP32 route pending |
| RS485_TX | GPIO44 | N/A | Output | N/A | N/A | N/A | N/A | Official 4.3B-BOX ESP-IDF `02_RS485_Test/sdkconfig.defaults` | PHYSICALLY_TESTED; UART2 |
| RS485_RX | GPIO43 | N/A | Input | N/A | N/A | N/A | N/A | Official 4.3B-BOX ESP-IDF `02_RS485_Test/sdkconfig.defaults` | PHYSICALLY_TESTED; UART2 |
| ISOLATED_IO_LOOPBACK | N/A | CH422G-controlled DO0/DO1 and DI0/DI1 | Output to input | Source-backed test connection | N/A | N/A | N/A | https://www.waveshare.com/wiki/ESP32-S3-Touch-LCD-4.3B | VERIFIED; wire DO0 to DI0 and DO1 to DI1 for the initial test |
| Notes | The official 4.3B pages confirm the board is the same electronics family as the non-box 4.3B variant, but no exact GPIO pin list is published in the source page used for this record. | N/A | N/A | N/A | N/A | N/A | N/A | https://www.waveshare.com/esp32-s3-touch-lcd-4.3b.htm?sku=28141 | VERIFIED |
