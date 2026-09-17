# 28141 Repository GT911 Identification: 2026-09-17

- Board identity: SKU 28141, MAC `14:c1:9f:4a:fd:a8`, port `/dev/ttyACM0`
- Firmware: repository `apps/display_diagnostic_28141`, ESP-IDF 5.5.5
- Board component: `ws_esp32s3_touch_lcd_43b_box_28141`
- Source-backed touch routing: GT911 at `0x5d` on I2C GPIO8/GPIO9; `CTP_RST` through CH422G EXIO1; `CTP_IRQ` on GPIO4

## Initial Result And Repair

The first repository probe attempted to create a second I2C0 bus after display initialization and reset-looped with `ESP_ERR_INVALID_STATE`. The board component was corrected to own one shared I2C0 bus and one set of CH422G device handles. The diagnostic now reports probe errors instead of aborting.

## Final Result

After recovery flashing, the display remained stable with user-confirmed red, green, and blue bars and the board reported:

```text
touch=ESP_OK controller=GT911 address=0x5d product_id=911
```

The shared-I2C, CH422G reset, and GT911 identification path passed. Live coordinate/event validation remains required before the touch capability is marked physically tested.