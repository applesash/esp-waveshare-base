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

SD mapping is recorded: the active BSP uses native 1-bit SDMMC with CLK GPIO2, CMD GPIO1, and D0 GPIO4; no chip-select GPIO is used. GPIO1/GPIO2 overlap the LCD serial control nets and require sequencing validation before shared use. The schematic EXIO4/SDCS net is not used by the active native SDMMC implementation.

Additional peripheral inventory is recorded: CH32V003 helper at I2C 0x24, PCF85063A RTC at 0x51, buzzer EXIO6, RTC interrupt EXIO7, backlight PWM path, battery ADC path, and system power/reset control. The V4.0 schematic marks the QMI8658 IMU block NC/not populated.

Helper diagnostic: [HELPER_DIAGNOSTIC_2026-09-16_230500.md](evidence/HELPER_DIAGNOSTIC_2026-09-16_230500.md)

RTC/SD diagnostic: [RTC_SD_DIAGNOSTIC_2026-09-16_233000.md](evidence/RTC_SD_DIAGNOSTIC_2026-09-16_233000.md). RTC transport passed but oscillator-stop status is set; SD mount timed out with no format or write performed.

SD power-cycle validation: [SD_POWER_CYCLE_VALIDATION_2026-09-16_233400.md](evidence/SD_POWER_CYCLE_VALIDATION_2026-09-16_233400.md). SD-first sequencing still timed out; card/slot compatibility remains pending.

Raw SD probe: [SD_RAW_PROBE_2026-09-16_234600.md](evidence/SD_RAW_PROBE_2026-09-16_234600.md). Native SDMMC card initialization timed out at 400 kHz, before filesystem detection; exFAT has not been reached.

SD CH32 preparation: [SD_CH32_PREPARE_VALIDATION_2026-09-17_000600.md](evidence/SD_CH32_PREPARE_VALIDATION_2026-09-17_000600.md). Official helper/power/reset sequencing passes, but the 16 GB card still times out before filesystem detection.

Official sequence comparison: [SD_OFFICIAL_SEQUENCE_VALIDATION_2026-09-17_001000.md](evidence/SD_OFFICIAL_SEQUENCE_VALIDATION_2026-09-17_001000.md). I2C recovery and CH32 preparation now match the official hardware sequence; card protocol initialization still times out.

SD retry/pull-up validation: [SD_RETRY_PULLUP_VALIDATION_2026-09-17_002500.md](evidence/SD_RETRY_PULLUP_VALIDATION_2026-09-17_002500.md). Three 400 kHz attempts with ESP-IDF internal pull-ups all timed out; no format or write occurred.

SD timing-matrix validation: [SD_TIMING_MATRIX_VALIDATION_2026-09-17_205551.md](evidence/SD_TIMING_MATRIX_VALIDATION_2026-09-17_205551.md). With a new empty FAT32 16 GB card, post-helper delays of 0, 100, 500, and 2000 ms all timed out before filesystem detection; generic boot-settle timing is not the root cause within the tested range.

SD EXIO4-control validation: [SD_EXIO4_CONTROL_VALIDATION_2026-09-17_210434.md](evidence/SD_EXIO4_CONTROL_VALIDATION_2026-09-17_210434.md). The CH32 helper accepted EXIO4 levels 0 and 1, but both native SDMMC probes timed out before filesystem detection; EXIO4 level alone does not resolve the failure.

Official SD sample validation: [SD_OFFICIAL_SAMPLE_VALIDATION_2026-09-17_211349.md](evidence/SD_OFFICIAL_SAMPLE_VALIDATION_2026-09-17_211349.md). The unmodified official Waveshare `02_SD_Test` reproduced the same native SDMMC timeout with the empty FAT32 16 GB card before mount, write, or format; this rules out the repository diagnostic implementation as the cause.

Second-board official SD sample validation: [SD_OFFICIAL_SAMPLE_SECOND_BOARD_2026-09-17_211847.md](evidence/SD_OFFICIAL_SAMPLE_SECOND_BOARD_2026-09-17_211847.md). A second MAC-registered SKU 28154 board initialized the same card through SDMMC, then mounted, formatted, and passed post-format write/read checks with the official sample. This isolates the first board's timeout to its physical SDMMC path.

Second-board repository SD diagnostic: [SD_REPOSITORY_DIAGNOSTIC_SECOND_BOARD_2026-09-17_213109.md](evidence/SD_REPOSITORY_DIAGNOSTIC_SECOND_BOARD_2026-09-17_213109.md). The repository's read-only native SDMMC diagnostic passed raw initialization and BSP mount on board MAC `e8:3d:c1:f7:89:c0`, then completed display, helper, RTC, and touch checks successfully.

Storage BSP promotion: [STORAGE_BSP_PROMOTION_SECOND_BOARD_2026-09-17_220510.md](evidence/STORAGE_BSP_PROMOTION_SECOND_BOARD_2026-09-17_220510.md). The source-backed 28154 CH32 preparation and native SDMMC lifecycle now reside in the exact-SKU board component and passed through its read-only API on board MAC `e8:3d:c1:f7:89:c0`.

Second-board repository touch diagnostic: [TOUCH_REPOSITORY_DIAGNOSTIC_SECOND_BOARD_2026-09-17_213109.md](evidence/TOUCH_REPOSITORY_DIAGNOSTIC_SECOND_BOARD_2026-09-17_213109.md). Live GT911 touch frames and decoded coordinates across the 480x480 panel passed on board MAC `e8:3d:c1:f7:89:c0`.

Diagnostic run: [DIAGNOSTIC_RUN_2026-09-16_220000.md](evidence/DIAGNOSTIC_RUN_2026-09-16_220000.md)

Touch run: [TOUCH_DIAGNOSTIC_2026-09-16_220800.md](evidence/TOUCH_DIAGNOSTIC_2026-09-16_220800.md)

Raw touch run: [TOUCH_RAW_2026-09-16_221100.md](evidence/TOUCH_RAW_2026-09-16_221100.md)

Coordinate validation: [TOUCH_COORDINATE_VALIDATION_2026-09-16_221500.md](evidence/TOUCH_COORDINATE_VALIDATION_2026-09-16_221500.md)
