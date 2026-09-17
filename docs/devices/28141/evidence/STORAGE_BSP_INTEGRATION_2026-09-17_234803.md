# 28141 Storage BSP Integration: 2026-09-17

- Board identity: SKU 28141, MAC `14:c1:9f:4a:fd:a8`, port `/dev/ttyACM0`
- Firmware: repository `apps/display_diagnostic_28141`, ESP-IDF 5.5.5
- Storage path: SPI MOSI GPIO11, MISO GPIO13, CLK GPIO12, CH422G EXIO4 selection
- Safety: read-only mount attempt; no file write or format

## Result

The repository `board_storage` implementation compiled and was run before display initialization. It still failed during card initialization:

```text
storage_mount=ESP_ERR_TIMEOUT
```

The independent official 28141 SPI SD sample had previously mounted and passed write/read checks on the same board and card. The repository display, UART2 RS485 initialization, PCF85063A transport, and GT911 identification continued to pass in the same boot.

## Conclusion

The repository storage adapter is not yet physically validated and must not be marked physically tested. Its remaining implementation difference from the exact official sample requires focused repair. The documented shared SPI/RGB pin serialization remains required but did not resolve this timeout.