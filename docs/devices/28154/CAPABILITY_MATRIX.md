# Capability Matrix

| Capability | Status | Source | Implementation | Physical evidence |
|---|---|---|---|---|
| 4-inch 480x480 RGB capacitive touch LCD | VERIFIED | https://www.waveshare.com/wiki/ESP32-S3-Touch-LCD-4 | Display panel and RGB bus expected | Not physically tested |
| GT911 touch controller | VERIFIED | https://www.waveshare.com/wiki/ESP32-S3-Touch-LCD-4 | Touch stack via I2C and interrupt path | Not physically tested |
| 5-point capacitive touch | VERIFIED | https://www.waveshare.com/wiki/ESP32-S3-Touch-LCD-4 | Touch input to ESP32-S3 | Not physically tested |
| I2C expansion / IO bus | VERIFIED | https://www.waveshare.com/wiki/ESP32-S3-Touch-LCD-4 | TCA9554 IO expander expected | Not physically tested |
| CAN interface | VERIFIED | https://github.com/waveshareteam/ESP32-S3-Touch-LCD-4/blob/main/hardware/schematics/ESP32-S3-Touch-LCD-4%20V4.0.pdf | CAN TX GPIO6, RX GPIO0; transceiver and connector path source-verified | Not physically tested |
| RS485 interface | VERIFIED | https://github.com/waveshareteam/ESP32-S3-Touch-LCD-4/blob/main/hardware/schematics/ESP32-S3-Touch-LCD-4%20V4.0.pdf | RS485 TX GPIO43, RX GPIO44; transceiver and green connector path source-verified | Not physically tested |
| WiFi / Bluetooth | VERIFIED | https://www.waveshare.com/wiki/ESP32-S3-Touch-LCD-4 | ESP32-S3 radio path | Not physically tested |
| RTC / battery hold | VERIFIED | https://www.waveshare.com/wiki/ESP32-S3-Touch-LCD-4 | RTC and charge circuit expected | Not physically tested |
| SD card slot | VERIFIED | https://github.com/waveshareteam/ESP32-S3-Touch-LCD-4/blob/main/hardware/HARDWARE_REFERENCE.md | 1-bit SDMMC: CLK GPIO2, CMD GPIO1, D0 GPIO4; card select via CH32 EXIO4 | Not physically tested |
| USB | VERIFIED | https://www.waveshare.com/wiki/ESP32-S3-Touch-LCD-4 | Full-speed USB path expected | Not physically tested |
