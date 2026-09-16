# 28154 SD CH32 Preparation Validation: 2026-09-17

- Official SD example fact reviewed: CH32 helper must be initialized before SD mount.
- Diagnostic now performs helper setup before SD:
  - CH32 I2C address `0x24`
  - Output direction: touch reset, LCD reset, SYS_EN, buzzer enable
  - Initial low level, delay, then SYS_EN/LCD reset/touch reset high
- Runtime result: `sd_board_prepare=PASS ch32=0x24 sys_en=1 lcd_reset=1 touch_reset=1`
- Raw SDMMC probe: `ESP_ERR_TIMEOUT`
- SD mount: `ESP_ERR_TIMEOUT`
- Card: user-reported 16 GB card
- No format or write performed

The official helper/power/reset preparation is now present and passing. The card still fails before filesystem detection, so the remaining issue is card/slot/electrical compatibility or card seating rather than missing CH32 preparation.
