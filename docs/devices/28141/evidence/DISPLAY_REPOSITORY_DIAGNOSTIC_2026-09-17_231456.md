# 28141 Repository Display Diagnostic: 2026-09-17

- Board identity: SKU 28141, MAC `14:c1:9f:4a:fd:a8`, port `/dev/ttyACM0`
- Firmware: repository `apps/display_diagnostic_28141`, ESP-IDF 5.5.5
- Board component: `ws_esp32s3_touch_lcd_43b_box_28141`
- Panel: source-backed 800x480 RGB configuration, 16 MHz pixel clock

## Result

The repository-owned board display initializer and color-bar renderer ran successfully. Serial output reported:

```text
display=PASS sku=28141 resolution=800x480
touch=DEFERRED reset_interrupt_mapping_unverified
```

The user visually confirmed the red, green, and blue color bars. This validates the header-owned RGB pin map, timing, CH422G backlight setup, and panel transfer path. GT911 touch is not initialized by this firmware and remains unverified.