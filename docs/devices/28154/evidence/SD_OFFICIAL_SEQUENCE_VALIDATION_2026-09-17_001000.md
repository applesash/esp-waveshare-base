# 28154 SD Official Sequence Validation: 2026-09-17

## Code-path comparison

The official Waveshare SD example was inspected for hardware facts only. Our implementation now includes both required pre-mount stages:

1. Shared I2C bus recovery on SDA GPIO15/SCL GPIO7.
2. CH32V003 helper initialization at `0x24`, direction setup, system-enable assertion, LCD/touch reset release, and required delays.

The active SD path remains native 1-bit SDMMC:

- CLK GPIO2
- CMD GPIO1
- D0 GPIO4
- No SPI chip-select

## Runtime result

```text
sd_board_prepare=PASS ch32=0x24 sys_en=1 lcd_reset=1 touch_reset=1
sdcard_raw_probe=ESP_ERR_TIMEOUT
sdcard_mount=ESP_ERR_TIMEOUT
```

The 16 GB card still fails before card protocol initialization. No filesystem detection, exFAT detection, formatting, or writing was reached.

Conclusion: the official board initialization sequence is now present and passing; remaining failure is card/slot/electrical compatibility or physical contact.
