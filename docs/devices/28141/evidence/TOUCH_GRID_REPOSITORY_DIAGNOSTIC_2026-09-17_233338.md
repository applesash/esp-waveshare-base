# 28141 Repository GT911 Corner/Grid Validation: 2026-09-17

- Board identity: SKU 28141, MAC `14:c1:9f:4a:fd:a8`, port `/dev/ttyACM0`
- Firmware: repository `apps/display_diagnostic_28141`, ESP-IDF 5.5.5
- Touch controller: GT911 at `0x5d`, product ID `911`
- Panel geometry: 800x480

## Test

The user touched top-left, top-right, bottom-left, bottom-right, and center regions. The source-backed raw GT911 poller recorded representative samples:

| Intended region | Representative coordinate |
|---|---:|
| Top-left | `(28,25)` |
| Top-right | `(780,63)` |
| Bottom-left | `(19,463)` |
| Bottom-right | `(772,434)` |
| Center | `(356,217)` |

## Result

All reported coordinates were inside the $800 \times 480$ panel bounds. The corner ordering matched the physical touch locations, with no axis swap, mirror, or out-of-bounds event observed. Raw GT911 identification, press reception, coordinate decoding, range, and initial transform validation passed.

LVGL input-adapter and application button activation validation remain Phase-05 work.