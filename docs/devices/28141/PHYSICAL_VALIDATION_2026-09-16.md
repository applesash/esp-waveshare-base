# Physical Validation Session: 2026-09-16

## Board identification

- User-provided identity: Waveshare ESP32-S3-Touch-LCD-4.3B-BOX, SKU 28141
- Host serial port: `/dev/ttyACM0`
- USB identity: Espressif USB JTAG/serial debug unit, `303a:1001`
- Chip: ESP32-S3, QFN56, revision v0.2
- Features reported by ROM: Wi-Fi, BLE, embedded PSRAM
- PSRAM: 8 MB
- Flash: 16 MB, manufacturer `0x46`, device `0x4018`
- Crystal: 40 MHz
- Flash voltage: 3.3 V
- MAC: `14:c1:9f:4a:fd:a8`

## Commands executed

```text
python -m esptool --port /dev/ttyACM0 chip_id
python -m esptool --port /dev/ttyACM0 flash_id
```

Both commands completed successfully and performed a hard reset after the read-only probe.

## Result

- USB connection and ESP32-S3 identity: PASS
- Exact Waveshare SKU confirmation: USER-IDENTIFIED, not independently readable from USB descriptors
- Display initialization: NOT TESTED
- Touch controller and coordinate transform: NOT TESTED
- GPIO and bus behavior: NOT TESTED
- Power-cycle and recovery behavior: NOT TESTED

Functional validation requires a board-specific diagnostic firmware and documented wiring/test observations.
