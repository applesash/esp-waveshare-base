# 28141 Repository RTC Diagnostic: 2026-09-17

- Board identity: SKU 28141, MAC `14:c1:9f:4a:fd:a8`, port `/dev/ttyACM0`
- Firmware: repository `apps/display_diagnostic_28141`, ESP-IDF 5.5.5
- RTC: PCF85063A at I2C address `0x51` on the shared GPIO8/GPIO9 board bus
- Safety: read-only control and seconds-register probe; no time, alarm, or interrupt configuration write

## Result

```text
rtc=ESP_OK address=0x51 control=0x00 seconds_bcd=0xd3
```

The PCF85063A I2C transport and register reads passed. Bit 7 of the seconds register is set (`0xd3`), indicating oscillator-stop status; the readable seconds field is `0x53`. RTC retained-time validity and interrupt behavior remain unverified.