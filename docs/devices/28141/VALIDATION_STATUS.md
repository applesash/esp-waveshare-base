# Validation Status

Source-based hardware facts have been extracted from the official Waveshare product and docs pages and recorded. On 2026-09-16, the user-identified exact board responded on `/dev/ttyACM0` as an ESP32-S3 USB JTAG/serial device; connection-level evidence is recorded in [PHYSICAL_VALIDATION_2026-09-16.md](evidence/PHYSICAL_VALIDATION_2026-09-16.md).

Current status: CONNECTION VERIFIED; FUNCTIONAL PHYSICAL VALIDATION PENDING

Phase-02 source acquisition: the official 4.3B schematic and 4.3B-BOX demo package have been identified in [SOURCE_REGISTER.md](SOURCE_REGISTER.md). The official SD demo verifies CH422G I2C SCL GPIO9/SDA GPIO8 and SD SPI MOSI GPIO11/MISO GPIO13/CLK GPIO12, with chip select through EXIO4. Extract the remaining exact CH422G channel, reset, display, touch, RS485, CAN, RTC, isolated-I/O, backlight, and safe-state facts before implementation. No mapping from the 28154 or another 4.3-family SKU may be reused.

SD validation: [SD_OFFICIAL_SAMPLE_2026-09-17_223030.md](evidence/SD_OFFICIAL_SAMPLE_2026-09-17_223030.md). The official exact-board SPI sample mounted the 16 GB FAT32 card and passed write/read verification on MAC `14:c1:9f:4a:fd:a8`. No format was performed.

Isolated-I/O test plan: the official `05_IO_Test` uses direct loopbacks `DO0 -> DI0` and `DO1 -> DI1`; no external voltage injection is required for this initial controlled test. CAN source evidence is retained, but CAN physical validation is explicitly deferred by the owner.

Isolated-I/O validation: [IO_LOOPBACK_OFFICIAL_SAMPLE_2026-09-17_223948.md](evidence/IO_LOOPBACK_OFFICIAL_SAMPLE_2026-09-17_223948.md). The official sample passed the DO0/DI0 and DO1/DI1 loopbacks on MAC `14:c1:9f:4a:fd:a8`; its later vendor LCD framebuffer-allocation failure is recorded separately and does not invalidate the I/O result.

RS485 validation: [RS485_OFFICIAL_SAMPLE_2026-09-17_224500.md](evidence/RS485_OFFICIAL_SAMPLE_2026-09-17_224500.md). The official UART2 echo sample passed byte-for-byte RS485 validation on TX GPIO44/RX GPIO43 at 115200 8N1, with USB Serial/JTAG retained for the console.

Display source and visual validation: the official 800x480 RGB LVGL sample initialized and displayed on MAC `14:c1:9f:4a:fd:a8`; its source-backed pin and timing values are now captured in the exact-SKU board headers. That sample has GT911 disabled by its own configuration, so it is not touch-validation evidence. GT911 reset/interrupt routing and raw touch validation remain pending.

Repository display validation: [DISPLAY_REPOSITORY_DIAGNOSTIC_2026-09-17_231456.md](evidence/DISPLAY_REPOSITORY_DIAGNOSTIC_2026-09-17_231456.md). The exact-SKU board component initialized the 800x480 panel and rendered user-confirmed red, green, and blue bars on MAC `14:c1:9f:4a:fd:a8`. Touch remains deferred pending exact routing evidence.

Repository GT911 identification: [TOUCH_REPOSITORY_PROBE_2026-09-17_232008.md](evidence/TOUCH_REPOSITORY_PROBE_2026-09-17_232008.md). The source-backed shared-I2C, CH422G reset, and GT911 product-ID probe passed on MAC `14:c1:9f:4a:fd:a8`. Live touch-coordinate validation remains pending.

Repository GT911 coordinates: [TOUCH_COORDINATE_REPOSITORY_DIAGNOSTIC_2026-09-17_232810.md](evidence/TOUCH_COORDINATE_REPOSITORY_DIAGNOSTIC_2026-09-17_232810.md). Live GT911 events and raw decoded coordinates passed within the 800x480 panel bounds on MAC `14:c1:9f:4a:fd:a8`. Full transform-grid and LVGL input-adapter validation remain Phase-05 work.

Repository GT911 corner/grid validation: [TOUCH_GRID_REPOSITORY_DIAGNOSTIC_2026-09-17_233338.md](evidence/TOUCH_GRID_REPOSITORY_DIAGNOSTIC_2026-09-17_233338.md). Top-left, top-right, bottom-left, bottom-right, and center input matched the expected 800x480 raw coordinate orientation, with no out-of-bounds events. LVGL input-adapter validation remains Phase-05 work.

Repository RTC transport validation: [RTC_REPOSITORY_DIAGNOSTIC_2026-09-17_233750.md](evidence/RTC_REPOSITORY_DIAGNOSTIC_2026-09-17_233750.md). The read-only PCF85063A probe passed at address `0x51` on MAC `14:c1:9f:4a:fd:a8`; oscillator-stop status is set, so retained-time validity and RTC interrupt behavior remain pending.

Repository storage BSP integration: [STORAGE_BSP_INTEGRATION_2026-09-17_234803.md](evidence/STORAGE_BSP_INTEGRATION_2026-09-17_234803.md). The local SPI storage adapter currently times out even when serialized before display initialization. The official sample remains physical evidence that the board/card path works; this local implementation is not yet physically validated.

Phase-02 safe-state baseline: source-backed initialization levels for LCD reset, touch reset, backlight, and isolated DO0/DO1 are recorded in `board_safe_states.h` and `GPIO_REGISTER.md`. A safe external-output policy remains unresolved, and official sources disagree on CH422G address representation (`0x20` high-level device configuration versus `0x24`/`0x38` raw endpoints). Do not add production CH422G control code until this discrepancy is resolved and an approved safe-state policy is recorded.
