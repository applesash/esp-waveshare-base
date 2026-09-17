# Source Register

| Source ID | Document/URL | Revision | Purpose | Page/Line/Macro | Date verified | Status |
|---|---|---|---|---|---|---|
| 28154-BASE-001 | https://www.waveshare.com/wiki/ESP32-S3-Touch-LCD-4 | Official Waveshare exact-SKU wiki page | Canonical source for SKU 28154 | Wiki page title and board identity; hardware mapping still under review | 2026-09-16 | UNVERIFIED |
| 28154-HW-001 | https://github.com/waveshareteam/ESP32-S3-Touch-LCD-4/blob/main/hardware/HARDWARE_REFERENCE.md | Official Waveshare V4.0 hardware reference | 480x480 RGB LCD, ST7701, GT911, CH32 helper, shared I2C | Hardware blocks and shared control bus | 2026-09-16 | VERIFIED |
| 28154-HW-002 | https://github.com/waveshareteam/ESP32-S3-Touch-LCD-4/blob/main/hardware/schematics/ESP32-S3-Touch-LCD-4%20V4.0.pdf | Official Waveshare V4.0 schematic | RGB/control net-to-GPIO mapping | Exact schematic net labels | 2026-09-16 | VERIFIED |
| 28154-SW-001 | https://github.com/waveshareteam/ESP32-S3-Touch-LCD-4/tree/main/examples/esp-idf/02_SD_Test | Official Waveshare V4.0 ESP-IDF storage example | CH32 I2C recovery, output direction, reset/system-enable sequence, and native SDMMC facts | `main/sd_card_example_main.c` CH32 masks and prepare sequence | 2026-09-18 | VERIFIED |
| 28154-SW-002 | waveshare/esp32_s3_touch_lcd_4 managed component v3.0.0 | Official Waveshare managed BSP | Touch interrupt, reset, system-enable, buzzer, RTC, SDMMC, and LCD control constants | `include/bsp/esp32_s3_touch_lcd_4.h` | 2026-09-18 | VERIFIED |
