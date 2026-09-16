# 28154 Touch Coordinate Validation: 2026-09-16

## Session

- Firmware: `display_diagnostic_28154`
- Port: `/dev/ttyACM0`
- MAC: `94:a9:90:dd:16:6c`
- Panel geometry: 480x480
- GT911 address: `0x5d`

## Observed samples

```text
touch_raw count=1 bytes=dc 01 01 00 06 00 00 00
touch_event count=1 track=0 x=476 y=1 size=6

touch_raw count=1 bytes=d9 01 07 00 09 00 00 00
touch_event count=1 track=0 x=473 y=7 size=9

touch_raw count=1 bytes=07 00 20 00 0c 00 00 00
touch_event count=1 track=0 x=7 y=32 size=12

touch_raw count=1 bytes=00 00 df 01 06 00 00 00
touch_event count=1 track=0 x=0 y=479 size=6

touch_raw count=1 bytes=ca 00 e6 00 11 00 00 00
touch_event count=1 track=0 x=202 y=230 size=17

touch_raw count=1 bytes=ca 00 fd 00 12 00 00 00
touch_event count=1 track=0 x=202 y=253 size=18
```

## Result

- GT911 identification: PASS
- Touch event reception: PASS
- Coordinate byte decoding: PASS for observed corner and center samples
- Coordinates within 480x480 bounds: PASS
- Axis transform/calibration: initial validation PASS for observed points; broader grid testing remains useful
- LCD pixel output: NOT TESTED
