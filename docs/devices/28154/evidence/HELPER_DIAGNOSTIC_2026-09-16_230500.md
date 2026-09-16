# 28154 CH32 Helper Diagnostic: 2026-09-16

- Board MAC: `94:a9:90:dd:16:6c`
- Helper address: `0x24`
- Helper initialization: PASS
- Battery ADC read transport: PASS
- Battery ADC raw value: `437`
- Interrupt read transport: PASS
- Interrupt value returned: `255`; semantic decoding remains pending
- LCD test pattern: PASS
- GT911 product ID: `911`

The raw battery ADC value is recorded without converting it to voltage because the board-specific divider and calibration have not yet been physically validated. The interrupt value is recorded without interpreting `255` as a logical state.
