# Capability Matrix

| Capability | Status | Source | Implementation | Physical evidence |
|---|---|---|---|---|
| 4-inch 480x480 RGB capacitive touch LCD | VERIFIED | https://www.waveshare.com/wiki/ESP32-S3-Touch-LCD-4 | Display panel and RGB bus expected | Not physically tested |
| GT911 touch controller | VERIFIED | https://www.waveshare.com/wiki/ESP32-S3-Touch-LCD-4 | Touch stack via I2C and interrupt path | Not physically tested |
| 5-point capacitive touch | VERIFIED | https://www.waveshare.com/wiki/ESP32-S3-Touch-LCD-4 | Touch input to ESP32-S3 | Not physically tested |
| CH32 helper I2C bus | VERIFIED | https://github.com/waveshareteam/ESP32-S3-Touch-LCD-4/blob/main/hardware/HARDWARE_REFERENCE.md | CH32V003F4U6 at 0x24 on SDA GPIO15/SCL GPIO7 | Not physically tested |
| CAN interface | VERIFIED | https://github.com/waveshareteam/ESP32-S3-Touch-LCD-4/blob/main/hardware/schematics/ESP32-S3-Touch-LCD-4%20V4.0.pdf | CAN TX GPIO6, RX GPIO0; transceiver and connector path source-verified | Not physically tested |
| RS485 interface | VERIFIED | https://github.com/waveshareteam/ESP32-S3-Touch-LCD-4/blob/main/hardware/schematics/ESP32-S3-Touch-LCD-4%20V4.0.pdf | RS485 TX GPIO43, RX GPIO44; transceiver and green connector path source-verified | Not physically tested |
| WiFi / Bluetooth | VERIFIED | https://www.waveshare.com/wiki/ESP32-S3-Touch-LCD-4 | ESP32-S3 radio path | Not physically tested |
| RTC / battery hold | VERIFIED | https://github.com/waveshareteam/ESP32-S3-Touch-LCD-4/blob/main/hardware/HARDWARE_REFERENCE.md | PCF85063A at 0x51; battery/power glue through CH32 helper | Not physically tested |
| Buzzer | VERIFIED | https://github.com/waveshareteam/ESP32-S3-Touch-LCD-4/blob/main/hardware/HARDWARE_REFERENCE.md | Buzzer enable through CH32 EXIO6 | Not physically tested |
| LCD backlight | VERIFIED | https://github.com/waveshareteam/ESP32-S3-Touch-LCD-4/blob/main/hardware/HARDWARE_REFERENCE.md | Backlight control through CH32 helper/PWM path | Not physically tested |
| Battery voltage ADC | VERIFIED | https://github.com/waveshareteam/ESP32-S3-Touch-LCD-4/blob/main/hardware/HARDWARE_REFERENCE.md | Battery measurement through CH32 helper ADC path | Not physically tested |
| System power control | VERIFIED | https://github.com/waveshareteam/ESP32-S3-Touch-LCD-4/blob/main/hardware/HARDWARE_REFERENCE.md | Power/reset control through CH32 helper | Not physically tested |
| IMU | NOT_PRESENT | https://github.com/waveshareteam/ESP32-S3-Touch-LCD-4/blob/main/hardware/schematics/ESP32-S3-Touch-LCD-4%20V4.0.pdf | QMI8658 block is marked NC in the V4.0 schematic | Not applicable |
| SD card slot | VERIFIED | https://github.com/waveshareteam/ESP32-S3-Touch-LCD-4/blob/main/hardware/HARDWARE_REFERENCE.md | 1-bit SDMMC: CLK GPIO2, CMD GPIO1, D0 GPIO4; card select via CH32 EXIO4 | Not physically tested |
| USB | VERIFIED | https://www.waveshare.com/wiki/ESP32-S3-Touch-LCD-4 | Full-speed USB path expected | Not physically tested |
