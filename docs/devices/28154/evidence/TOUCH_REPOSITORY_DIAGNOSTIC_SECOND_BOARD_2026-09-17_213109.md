# 28154 Repository Touch Diagnostic: Second Board: 2026-09-17

- Board identity: SKU 28154, MAC `e8:3d:c1:f7:89:c0`, port `/dev/ttyACM0`
- Firmware: repository `apps/display_diagnostic`, ESP-IDF 5.5.5
- Touch controller: GT911 at I2C address `0x5d`, product ID `911`
- Panel geometry: 480x480

## Result

The diagnostic identified the controller and received live touch frames after the user touched the display. Sample decoded events included:

```text
touch_event count=1 track=0 x=62 y=211 size=11
touch_event count=1 track=0 x=456 y=479 size=7
touch_event count=1 track=0 x=227 y=277 size=12
touch_event count=1 track=0 x=262 y=258 size=20
touch_event count=1 track=0 x=248 y=243 size=19
touch_event count=1 track=0 x=91 y=55 size=17
```

All observed coordinates were within the 480x480 panel bounds. Live GT911 detection and raw coordinate decoding passed on this second board instance.