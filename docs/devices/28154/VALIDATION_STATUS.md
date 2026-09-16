# Validation Status

Source-based hardware facts have been extracted from the official Waveshare page and recorded. On 2026-09-16, the user-identified exact board responded on `/dev/ttyACM0` as an ESP32-S3 USB JTAG/serial device with MAC `94:a9:90:dd:16:6c`; the latest MAC-validated evidence is recorded in [PHYSICAL_VALIDATION_2026-09-16_214937.md](evidence/PHYSICAL_VALIDATION_2026-09-16_214937.md).

Current status: CONNECTION AND GT911 TOUCH COORDINATES VERIFIED; LCD FUNCTIONAL VALIDATION PENDING

LCD implementation blocker: RGB channel R0 and B0 still require exact schematic confirmation; ST7701 initialization commands and RGB timing values are not yet recorded.

Green connector/source mapping is now recorded: SDA GPIO15, SCL GPIO7, RS485 TX GPIO43, RS485 RX GPIO44, CAN TX GPIO6, and CAN RX GPIO0. Electrical function remains physically untested.

SD mapping is recorded: 1-bit SDMMC uses CLK GPIO2, CMD GPIO1, D0 GPIO4, with card select through CH32 EXIO4. These pins overlap the documented LCD serial control nets and require board-level sequencing validation before shared use.

Additional peripheral inventory is recorded: CH32V003 helper at I2C 0x24, PCF85063A RTC at 0x51, buzzer EXIO6, RTC interrupt EXIO7, backlight PWM path, battery ADC path, and system power/reset control. The V4.0 schematic marks the QMI8658 IMU block NC/not populated.

Diagnostic run: [DIAGNOSTIC_RUN_2026-09-16_220000.md](evidence/DIAGNOSTIC_RUN_2026-09-16_220000.md)

Touch run: [TOUCH_DIAGNOSTIC_2026-09-16_220800.md](evidence/TOUCH_DIAGNOSTIC_2026-09-16_220800.md)

Raw touch run: [TOUCH_RAW_2026-09-16_221100.md](evidence/TOUCH_RAW_2026-09-16_221100.md)

Coordinate validation: [TOUCH_COORDINATE_VALIDATION_2026-09-16_221500.md](evidence/TOUCH_COORDINATE_VALIDATION_2026-09-16_221500.md)
