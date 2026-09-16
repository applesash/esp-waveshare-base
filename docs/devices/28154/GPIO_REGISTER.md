# GPIO and I/O Register

| Signal | ESP32 GPIO | Expander channel | Direction | Active level | Pull | Boot state | Safe state | Source | Status |
|---|---:|---|---|---|---|---|---|---|---|
| IO_EXPANDER_I2C_SDA | GPIO8 | N/A | I/O | N/A | N/A | N/A | N/A | https://www.waveshare.com/wiki/ESP32-S3-Touch-LCD-4 | VERIFIED |
| IO_EXPANDER_I2C_SCL | GPIO9 | N/A | I/O | N/A | N/A | N/A | N/A | https://www.waveshare.com/wiki/ESP32-S3-Touch-LCD-4 | VERIFIED |
| TOUCH_I2C_SCL | GPIO7 | N/A | I/O | N/A | N/A | N/A | N/A | https://www.waveshare.com/wiki/ESP32-S3-Touch-LCD-4 | VERIFIED |
| TOUCH_I2C_SDA | GPIO15 | N/A | I/O | N/A | N/A | N/A | N/A | https://www.waveshare.com/wiki/ESP32-S3-Touch-LCD-4 | VERIFIED |
| TOUCH_INT | not specified on the source page | N/A | Input | N/A | N/A | N/A | N/A | https://www.waveshare.com/wiki/ESP32-S3-Touch-LCD-4 | UNVERIFIED |
| LCD_SERIAL_SDA | GPIO1 | N/A | Output | N/A | N/A | N/A | N/A | https://github.com/waveshareteam/ESP32-S3-Touch-LCD-4/blob/main/hardware/schematics/ESP32-S3-Touch-LCD-4%20V4.0.pdf | VERIFIED |
| LCD_SERIAL_SCL | GPIO2 | N/A | Output | N/A | N/A | N/A | N/A | https://github.com/waveshareteam/ESP32-S3-Touch-LCD-4/blob/main/hardware/schematics/ESP32-S3-Touch-LCD-4%20V4.0.pdf | VERIFIED |
| LCD_SERIAL_CS | GPIO42 | N/A | Output | N/A | N/A | N/A | N/A | https://github.com/waveshareteam/ESP32-S3-Touch-LCD-4/blob/main/hardware/schematics/ESP32-S3-Touch-LCD-4%20V4.0.pdf | VERIFIED |
| LCD_RGB_PCLK | GPIO41 | N/A | Output | N/A | N/A | N/A | N/A | https://github.com/waveshareteam/ESP32-S3-Touch-LCD-4/blob/main/hardware/schematics/ESP32-S3-Touch-LCD-4%20V4.0.pdf | VERIFIED |
| LCD_RGB_HSYNC | GPIO38 | N/A | Output | N/A | N/A | N/A | N/A | https://github.com/waveshareteam/ESP32-S3-Touch-LCD-4/blob/main/hardware/schematics/ESP32-S3-Touch-LCD-4%20V4.0.pdf | VERIFIED |
| LCD_RGB_VSYNC | GPIO39 | N/A | Output | N/A | N/A | N/A | N/A | https://github.com/waveshareteam/ESP32-S3-Touch-LCD-4/blob/main/hardware/schematics/ESP32-S3-Touch-LCD-4%20V4.0.pdf | VERIFIED |
| LCD_RGB_DE | GPIO40 | N/A | Output | N/A | N/A | N/A | N/A | https://github.com/waveshareteam/ESP32-S3-Touch-LCD-4/blob/main/hardware/schematics/ESP32-S3-Touch-LCD-4%20V4.0.pdf | VERIFIED |
| LCD_RGB_R0 | not resolved from schematic text extraction | N/A | Output | N/A | N/A | N/A | N/A | https://github.com/waveshareteam/ESP32-S3-Touch-LCD-4/blob/main/hardware/schematics/ESP32-S3-Touch-LCD-4%20V4.0.pdf | UNVERIFIED |
| LCD_RGB_R1 | GPIO46 | N/A | Output | N/A | N/A | N/A | N/A | https://github.com/waveshareteam/ESP32-S3-Touch-LCD-4/blob/main/hardware/schematics/ESP32-S3-Touch-LCD-4%20V4.0.pdf | VERIFIED |
| LCD_RGB_R2 | GPIO3 | N/A | Output | N/A | N/A | N/A | N/A | https://github.com/waveshareteam/ESP32-S3-Touch-LCD-4/blob/main/hardware/schematics/ESP32-S3-Touch-LCD-4%20V4.0.pdf | VERIFIED |
| LCD_RGB_R3 | GPIO8 | N/A | Output | N/A | N/A | N/A | N/A | https://github.com/waveshareteam/ESP32-S3-Touch-LCD-4/blob/main/hardware/schematics/ESP32-S3-Touch-LCD-4%20V4.0.pdf | VERIFIED |
| LCD_RGB_R4 | GPIO18 | N/A | Output | N/A | N/A | N/A | N/A | https://github.com/waveshareteam/ESP32-S3-Touch-LCD-4/blob/main/hardware/schematics/ESP32-S3-Touch-LCD-4%20V4.0.pdf | VERIFIED |
| LCD_RGB_R5 | GPIO17 | N/A | Output | N/A | N/A | N/A | N/A | https://github.com/waveshareteam/ESP32-S3-Touch-LCD-4/blob/main/hardware/schematics/ESP32-S3-Touch-LCD-4%20V4.0.pdf | VERIFIED |
| LCD_RGB_G0 | GPIO14 | N/A | Output | N/A | N/A | N/A | N/A | https://github.com/waveshareteam/ESP32-S3-Touch-LCD-4/blob/main/hardware/schematics/ESP32-S3-Touch-LCD-4%20V4.0.pdf | VERIFIED |
| LCD_RGB_G1 | GPIO13 | N/A | Output | N/A | N/A | N/A | N/A | https://github.com/waveshareteam/ESP32-S3-Touch-LCD-4/blob/main/hardware/schematics/ESP32-S3-Touch-LCD-4%20V4.0.pdf | VERIFIED |
| LCD_RGB_G2 | GPIO12 | N/A | Output | N/A | N/A | N/A | N/A | https://github.com/waveshareteam/ESP32-S3-Touch-LCD-4/blob/main/hardware/schematics/ESP32-S3-Touch-LCD-4%20V4.0.pdf | VERIFIED |
| LCD_RGB_G3 | GPIO11 | N/A | Output | N/A | N/A | N/A | N/A | https://github.com/waveshareteam/ESP32-S3-Touch-LCD-4/blob/main/hardware/schematics/ESP32-S3-Touch-LCD-4%20V4.0.pdf | VERIFIED |
| LCD_RGB_G4 | GPIO10 | N/A | Output | N/A | N/A | N/A | N/A | https://github.com/waveshareteam/ESP32-S3-Touch-LCD-4/blob/main/hardware/schematics/ESP32-S3-Touch-LCD-4%20V4.0.pdf | VERIFIED |
| LCD_RGB_G5 | GPIO9 | N/A | Output | N/A | N/A | N/A | N/A | https://github.com/waveshareteam/ESP32-S3-Touch-LCD-4/blob/main/hardware/schematics/ESP32-S3-Touch-LCD-4%20V4.0.pdf | VERIFIED |
| LCD_RGB_B0 | not resolved from schematic text extraction | N/A | Output | N/A | N/A | N/A | N/A | https://github.com/waveshareteam/ESP32-S3-Touch-LCD-4/blob/main/hardware/schematics/ESP32-S3-Touch-LCD-4%20V4.0.pdf | UNVERIFIED |
| LCD_RGB_B1 | GPIO5 | N/A | Output | N/A | N/A | N/A | N/A | https://github.com/waveshareteam/ESP32-S3-Touch-LCD-4/blob/main/hardware/schematics/ESP32-S3-Touch-LCD-4%20V4.0.pdf | VERIFIED |
| LCD_RGB_B2 | GPIO45 | N/A | Output | N/A | N/A | N/A | N/A | https://github.com/waveshareteam/ESP32-S3-Touch-LCD-4/blob/main/hardware/schematics/ESP32-S3-Touch-LCD-4%20V4.0.pdf | VERIFIED |
| LCD_RGB_B3 | GPIO48 | N/A | Output | N/A | N/A | N/A | N/A | https://github.com/waveshareteam/ESP32-S3-Touch-LCD-4/blob/main/hardware/schematics/ESP32-S3-Touch-LCD-4%20V4.0.pdf | VERIFIED |
| LCD_RGB_B4 | GPIO47 | N/A | Output | N/A | N/A | N/A | N/A | https://github.com/waveshareteam/ESP32-S3-Touch-LCD-4/blob/main/hardware/schematics/ESP32-S3-Touch-LCD-4%20V4.0.pdf | VERIFIED |
| LCD_RGB_B5 | GPIO21 | N/A | Output | N/A | N/A | N/A | N/A | https://github.com/waveshareteam/ESP32-S3-Touch-LCD-4/blob/main/hardware/schematics/ESP32-S3-Touch-LCD-4%20V4.0.pdf | VERIFIED |
