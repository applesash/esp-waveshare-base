# 28154 Official Waveshare SD Sample Validation: 2026-09-17

- Board identity: SKU 28154, MAC `94:a9:90:dd:16:6c`, port `/dev/ttyACM0`
- Card: user-reported empty FAT32 16 GB microSD
- Source: unmodified `examples/esp-idf/02_SD_Test` from the official Waveshare `ESP32-S3-Touch-LCD-4` repository, commit `aa604c1`
- SDK: ESP-IDF 5.5.5, target `esp32s3`
- SD path: native 1-bit SDMMC, CLK GPIO2, CMD GPIO1, D0 GPIO4
- Helper sequence: official I2C recovery and CH32V003 initialization at address `0x24`; EXIO1, EXIO3, EXIO5, and EXIO6 configured before mount
- Sample permission: the empty card was explicitly approved for the sample's normal write-and-format flow

## Result

The sample built and flashed successfully, but the native SDMMC mount failed before any filesystem operation:

```text
Initializing SD card
Using SDMMC peripheral
Mounting filesystem
sdmmc_init_ocr: send_op_cond (1) returned 0x107
Failed to initialize the card (ESP_ERR_TIMEOUT). Make sure SD card lines have pull-up resistors in place.
```

The failure occurred before mounting, writing, reading, or formatting. The approved destructive sample flow therefore did not modify the card.

## Power-Cycle Repeat

The board was physically power-cycled with the same official sample and card installed. The clean boot reproduced the same `ESP_ERR_TIMEOUT` in `sdmmc_init_ocr: send_op_cond` at the SD mount stage. The sample again returned from `app_main` before any write or format operation.

## Conclusion

The unmodified official Waveshare SD sample reproduces the same `ESP_ERR_TIMEOUT` as the repository diagnostic, including after a physical power cycle. The fault is not caused by repository application code, the CH32 preparation sequence, the tested post-helper timing range, EXIO4 state, or reset order. Investigate the physical SDMMC electrical path, including card seating, slot condition, and external pull-ups on CMD/D0, before making further firmware changes.