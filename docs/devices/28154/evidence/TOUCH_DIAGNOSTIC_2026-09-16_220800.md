# 28154 Touch Diagnostic: 2026-09-16

## Firmware and identity

- Firmware project: `display_diagnostic_28154`
- Serial port: `/dev/ttyACM0`
- MAC: `94:a9:90:dd:16:6c`
- Flash: 16 MB detected and reported at runtime
- GT911 address: `0x5d`
- GT911 product ID bytes: `39 31 31 00` (`911`)

## Runtime results

- Touch I2C bus initialization: PASS
- GT911 register read: PASS
- Touch status polling: PASS
- Touch events received: PASS; three events were observed during the monitor session

Observed raw events:

```text
touch_event count=1 track=25 x=35585 y=6144 size=0
touch_event count=1 track=206 x=63232 y=8192 size=0
touch_event count=1 track=221 x=43777 y=4352 size=0
```

## Interpretation

The GT911 controller and event path are responding, but the raw coordinates are outside the documented 480x480 display range. Coordinate byte layout, calibration, axis transform, and touch-release handling require further validation before touch can be marked functionally verified.
