# 28141 Official Isolated-I/O Loopback Validation: 2026-09-17

- Board identity: SKU 28141, MAC `14:c1:9f:4a:fd:a8`, port `/dev/ttyACM0`
- Source: unmodified official 4.3B-BOX ESP-IDF `05_IO_Test`
- Wiring: `DO0 -> DI0` and `DO1 -> DI1`, USB-powered; no external voltage injected
- Safety: the sample actively toggles only the two looped-back isolated outputs

## Result

The official I/O test reported:

```text
DI & DO OK!!!
```

This passes the two-channel isolated output-to-input loopback before display initialization.

## Separate Vendor Sample Failure

After the I/O pass, the official sample attempted RGB LCD framebuffer allocation and aborted with `ESP_ERR_NO_MEM`. The failing call was `esp_lcd_new_rgb_panel` in the vendor LCD implementation. This is unrelated to the completed I/O loopback and does not represent a repository display implementation result.