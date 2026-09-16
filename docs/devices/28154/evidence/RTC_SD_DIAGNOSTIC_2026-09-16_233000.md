# 28154 RTC and SD Diagnostic: 2026-09-16

## RTC

- Device address: `0x51`
- Register read transport: PASS
- Seconds register: `0xd9`
- Interpretation: oscillator-stop/status bit is set; time is not valid or has not been initialized
- RTC functional time validation: PENDING

## SD

- Card was inserted before flashing
- Mount attempt: `ESP_ERR_TIMEOUT`
- No format performed
- No file written
- SD functional validation: PENDING

The SD result requires a power-cycle/reinsert check and confirmation of card format/card health. The shared LCD serial/SD GPIO1/GPIO2 usage may also require board-specific sequencing.
