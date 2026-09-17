# GPIO and I/O Register

| Signal | ESP32 GPIO | Expander channel | Direction | Active level | Pull | Boot state | Safe state | Source | Status |
|---|---:|---|---|---|---|---|---|---|---|
| DI_1 | GPIO4 | N/A | Input | N/A | N/A | N/A | N/A | Official PoE demo `WS_DIN.h` | VERIFIED |
| DI_2 | GPIO5 | N/A | Input | N/A | N/A | N/A | N/A | Official PoE demo `WS_DIN.h` | VERIFIED |
| DI_3 | GPIO6 | N/A | Input | N/A | N/A | N/A | N/A | Official PoE demo `WS_DIN.h` | VERIFIED |
| DI_4 | GPIO7 | N/A | Input | N/A | N/A | N/A | N/A | Official PoE demo `WS_DIN.h` | VERIFIED |
| DI_5 | GPIO8 | N/A | Input | N/A | N/A | N/A | N/A | https://www.waveshare.com/wiki/ESP32-S3-ETH-8DI-8RO | VERIFIED |
| DI_6 | GPIO9 | N/A | Input | N/A | N/A | N/A | N/A | https://www.waveshare.com/wiki/ESP32-S3-ETH-8DI-8RO | VERIFIED |
| DI_7 | GPIO10 | N/A | Input | N/A | N/A | N/A | N/A | https://www.waveshare.com/wiki/ESP32-S3-ETH-8DI-8RO | VERIFIED |
| DI_8 | GPIO11 | N/A | Input | N/A | N/A | N/A | N/A | https://www.waveshare.com/wiki/ESP32-S3-ETH-8DI-8RO | VERIFIED |
| ETH_INT | GPIO12 | N/A | Input | N/A | N/A | N/A | N/A | https://www.waveshare.com/wiki/ESP32-S3-ETH-8DI-8RO | VERIFIED |
| ETH_MOSI | GPIO13 | N/A | Output | N/A | N/A | N/A | N/A | https://www.waveshare.com/wiki/ESP32-S3-ETH-8DI-8RO | VERIFIED |
| ETH_MISO | GPIO14 | N/A | Input | N/A | N/A | N/A | N/A | https://www.waveshare.com/wiki/ESP32-S3-ETH-8DI-8RO | VERIFIED |
| ETH_SCLK | GPIO15 | N/A | Output | N/A | N/A | N/A | N/A | https://www.waveshare.com/wiki/ESP32-S3-ETH-8DI-8RO | VERIFIED |
| ETH_CS | GPIO16 | N/A | Output | N/A | N/A | N/A | N/A | https://www.waveshare.com/wiki/ESP32-S3-ETH-8DI-8RO | VERIFIED |
| RS485_TX | GPIO17 | N/A | Output | N/A | N/A | N/A | N/A | https://www.waveshare.com/wiki/ESP32-S3-ETH-8DI-8RO | VERIFIED |
| RS485_RX | GPIO18 | N/A | Input | N/A | N/A | N/A | N/A | https://www.waveshare.com/wiki/ESP32-S3-ETH-8DI-8RO | VERIFIED |
| RTC_INT | GPIO40 | N/A | Input | N/A | N/A | N/A | N/A | https://www.waveshare.com/wiki/ESP32-S3-ETH-8DI-8RO | VERIFIED |
| RTC_SCL | GPIO41 | N/A | Output | N/A | N/A | N/A | N/A | https://www.waveshare.com/wiki/ESP32-S3-ETH-8DI-8RO | VERIFIED |
| RTC_SDA | GPIO42 | N/A | I/O | N/A | N/A | N/A | N/A | https://www.waveshare.com/wiki/ESP32-S3-ETH-8DI-8RO | VERIFIED |
| RGB_LED | GPIO38 | N/A | Output | N/A | N/A | N/A | N/A | https://www.waveshare.com/wiki/ESP32-S3-ETH-8DI-8RO | VERIFIED |
| BUZZER | GPIO46 | N/A | Output | N/A | N/A | N/A | N/A | https://www.waveshare.com/wiki/ESP32-S3-ETH-8DI-8RO | VERIFIED |
| SDMMC_D0 | GPIO45 | N/A | I/O | N/A | N/A | N/A | N/A | Official PoE demo `WS_SD.h` | VERIFIED |
| SDMMC_CMD | GPIO47 | N/A | I/O | N/A | N/A | N/A | N/A | Official PoE demo `WS_SD.h` | VERIFIED |
| SDMMC_CLK | GPIO48 | N/A | Output | N/A | N/A | N/A | N/A | Official PoE demo `WS_SD.h` | VERIFIED |
| RELAY_1 | N/A | TCA9554 EXIO1 | Output | active level pending | N/A | N/A | de-energized level pending | Official PoE demo `WS_Relay.h`; `WS_TCA9554PWR.h` | VERIFIED; safe state pending |
| RELAY_2 | N/A | TCA9554 EXIO2 | Output | active level pending | N/A | N/A | de-energized level pending | Official PoE demo `WS_Relay.h`; `WS_TCA9554PWR.h` | VERIFIED; safe state pending |
| RELAY_3 | N/A | TCA9554 EXIO3 | Output | active level pending | N/A | N/A | de-energized level pending | Official PoE demo `WS_Relay.h`; `WS_TCA9554PWR.h` | VERIFIED; safe state pending |
| RELAY_4 | N/A | TCA9554 EXIO4 | Output | active level pending | N/A | N/A | de-energized level pending | Official PoE demo `WS_Relay.h`; `WS_TCA9554PWR.h` | VERIFIED; safe state pending |
| RELAY_5 | N/A | TCA9554 EXIO5 | Output | active level pending | N/A | N/A | de-energized level pending | Official PoE demo `WS_Relay.h`; `WS_TCA9554PWR.h` | VERIFIED; safe state pending |
| RELAY_6 | N/A | TCA9554 EXIO6 | Output | active level pending | N/A | N/A | de-energized level pending | Official PoE demo `WS_Relay.h`; `WS_TCA9554PWR.h` | VERIFIED; safe state pending |
| RELAY_7 | N/A | TCA9554 EXIO7 | Output | active level pending | N/A | N/A | de-energized level pending | Official PoE demo `WS_Relay.h`; `WS_TCA9554PWR.h` | VERIFIED; safe state pending |
| RELAY_8 | N/A | TCA9554 EXIO8 | Output | active level pending | N/A | N/A | de-energized level pending | Official PoE demo `WS_Relay.h`; `WS_TCA9554PWR.h` | VERIFIED; safe state pending |
| RELAY_EXPANDER | GPIO mapping pending | TCA9554 address 0x20 | I2C | N/A | N/A | N/A | N/A | Official PoE demo `WS_TCA9554PWR.h` | VERIFIED; ESP32 I2C pins pending |
