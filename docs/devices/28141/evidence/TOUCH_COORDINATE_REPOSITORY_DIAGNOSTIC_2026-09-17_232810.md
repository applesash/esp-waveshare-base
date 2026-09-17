# 28141 Repository GT911 Coordinate Validation: 2026-09-17

- Board identity: SKU 28141, MAC `14:c1:9f:4a:fd:a8`, port `/dev/ttyACM0`
- Firmware: repository `apps/display_diagnostic_28141`, ESP-IDF 5.5.5
- Touch controller: GT911 at `0x5d`, product ID `911`
- Source-backed routing: shared I2C GPIO8/GPIO9, reset through CH422G EXIO1, interrupt GPIO4
- Panel geometry: 800x480

## Result

Following the source-backed reset and identification sequence, the repository-owned raw poller received live GT911 data while the user touched the panel. Observed samples included:

```text
touch_event count=1 x=387 y=276 size=80
touch_event count=1 x=383 y=273 size=80
touch_event count=1 x=395 y=274 size=63
touch_event count=1 x=396 y=278 size=79
```

The reported points are within the 800x480 panel bounds. GT911 identification, event reception, and raw coordinate decoding passed. The diagnostic preserves every raw press sample; production input semantics will be implemented separately in the Phase-05 adapter.

## Remaining Validation

Full corner/grid transform validation and LVGL input-adapter validation remain Phase-05 work.