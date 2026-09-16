# Validation Status

Source-based hardware facts have been extracted from the official Waveshare page and recorded. On 2026-09-16, the user-identified exact board responded on `/dev/ttyACM0` as an ESP32-S3 USB JTAG/serial device with MAC `94:a9:90:dd:16:6c`; the latest MAC-validated evidence is recorded in [PHYSICAL_VALIDATION_2026-09-16_214937.md](evidence/PHYSICAL_VALIDATION_2026-09-16_214937.md).

Current status: CONNECTION, GT911 TOUCH COORDINATES, AND LCD TEST PATTERN VERIFIED

LCD implementation status: ST7701 initialization is delegated to the official managed BSP; RGB565 channel mapping and timing values are source-recorded. Runtime initialization and RGB test-pattern transfer passed.

LCD firmware implementation is present through the official managed BSP and has been flashed. Runtime initialization and visual RGB pattern validation passed.

LCD run: [LCD_DIAGNOSTIC_2026-09-16_230300.md](evidence/LCD_DIAGNOSTIC_2026-09-16_230300.md)

LCD visual run: [LCD_VISUAL_VALIDATION_2026-09-16_230400.md](evidence/LCD_VISUAL_VALIDATION_2026-09-16_230400.md)

Green connector/source mapping is now recorded: SDA GPIO15, SCL GPIO7, RS485 TX GPIO44, RS485 RX GPIO43, CAN TX GPIO6, and CAN RX GPIO0. Electrical function remains physically untested.

RS485 diagnostic: [RS485_DIAGNOSTIC_2026-09-16_232400.md](evidence/RS485_DIAGNOSTIC_2026-09-16_232400.md). Corrected official mapping is TX GPIO44/RX GPIO43; physical transport is active but exact echo validation remains pending.

RS485 validation: [RS485_VALIDATION_2026-09-16_232800.md](evidence/RS485_VALIDATION_2026-09-16_232800.md). UART0/USB Serial-JTAG console separation and 9600-baud byte-for-byte echo passed.

SD mapping is recorded: 1-bit SDMMC uses CLK GPIO2, CMD GPIO1, D0 GPIO4, with card select through CH32 EXIO4. These pins overlap the documented LCD serial control nets and require board-level sequencing validation before shared use.

Additional peripheral inventory is recorded: CH32V003 helper at I2C 0x24, PCF85063A RTC at 0x51, buzzer EXIO6, RTC interrupt EXIO7, backlight PWM path, battery ADC path, and system power/reset control. The V4.0 schematic marks the QMI8658 IMU block NC/not populated.

Helper diagnostic: [HELPER_DIAGNOSTIC_2026-09-16_230500.md](evidence/HELPER_DIAGNOSTIC_2026-09-16_230500.md)

RTC/SD diagnostic: [RTC_SD_DIAGNOSTIC_2026-09-16_233000.md](evidence/RTC_SD_DIAGNOSTIC_2026-09-16_233000.md). RTC transport passed but oscillator-stop status is set; SD mount timed out with no format or write performed.

SD power-cycle validation: [SD_POWER_CYCLE_VALIDATION_2026-09-16_233400.md](evidence/SD_POWER_CYCLE_VALIDATION_2026-09-16_233400.md). SD-first sequencing still timed out; card/slot compatibility remains pending.

Diagnostic run: [DIAGNOSTIC_RUN_2026-09-16_220000.md](evidence/DIAGNOSTIC_RUN_2026-09-16_220000.md)

Touch run: [TOUCH_DIAGNOSTIC_2026-09-16_220800.md](evidence/TOUCH_DIAGNOSTIC_2026-09-16_220800.md)

Raw touch run: [TOUCH_RAW_2026-09-16_221100.md](evidence/TOUCH_RAW_2026-09-16_221100.md)

Coordinate validation: [TOUCH_COORDINATE_VALIDATION_2026-09-16_221500.md](evidence/TOUCH_COORDINATE_VALIDATION_2026-09-16_221500.md)
