# Capability Matrix

| Capability | Status | Source | Implementation | Physical evidence |
|---|---|---|---|---|
| 8 digital inputs | VERIFIED | https://www.waveshare.com/wiki/ESP32-S3-ETH-8DI-8RO | Digital input detection path present | Not physically tested |
| 8 relay outputs | VERIFIED | https://www.waveshare.com/wiki/ESP32-S3-ETH-8DI-8RO | Relay output stage present | Not physically tested |
| Ethernet | VERIFIED | https://www.waveshare.com/wiki/ESP32-S3-ETH-8DI-8RO | W5500/Ethernet port path present | Not physically tested |
| RS485 | VERIFIED | https://www.waveshare.com/wiki/ESP32-S3-ETH-8DI-8RO | UART RX/TX present on GPIO17/GPIO18 | Not physically tested |
| WiFi / Bluetooth | VERIFIED | https://www.waveshare.com/wiki/ESP32-S3-ETH-8DI-8RO | ESP32-S3 radio path | Not physically tested |
| RTC | VERIFIED | https://www.waveshare.com/wiki/ESP32-S3-ETH-8DI-8RO | RTC_IN / RTC_I2C path present | Not physically tested |
| RGB status LED | VERIFIED | https://www.waveshare.com/wiki/ESP32-S3-ETH-8DI-8RO | GPIO38 LED output | Not physically tested |
| Buzzer | VERIFIED | https://www.waveshare.com/wiki/ESP32-S3-ETH-8DI-8RO | GPIO46 output | Not physically tested |
| SD card | VERIFIED | Official PoE demo `WS_SD.h` | Native 1-bit SDMMC: CLK GPIO48, CMD GPIO47, D0 GPIO45 | Not physically tested |
| Power input / wide-voltage supply | VERIFIED | https://www.waveshare.com/wiki/ESP32-S3-ETH-8DI-8RO | 7~36V input path present | Not physically tested |
| Display / LCD | NOT_PRESENT | https://www.waveshare.com/wiki/ESP32-S3-ETH-8DI-8RO | Relay controller board; no onboard LCD listed | Not applicable |
| Touch | NOT_PRESENT | https://www.waveshare.com/wiki/ESP32-S3-ETH-8DI-8RO | No onboard touch controller listed | Not applicable |
| USB | VERIFIED | https://www.waveshare.com/wiki/ESP32-S3-ETH-8DI-8RO | USB Type-C for power, flashing, and communication | Not physically tested |
