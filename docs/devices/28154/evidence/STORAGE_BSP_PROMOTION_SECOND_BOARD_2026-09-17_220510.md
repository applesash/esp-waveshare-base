# 28154 Storage BSP Promotion: Second Board: 2026-09-17

- Board identity: SKU 28154, MAC `e8:3d:c1:f7:89:c0`, port `/dev/ttyACM0`
- Firmware: repository `apps/display_diagnostic`, ESP-IDF 5.5.5
- Board component: `ws_esp32s3_touch_lcd_4_28154`
- Storage API: `board_storage_prepare`, `board_storage_probe`, `board_storage_mount`, and `board_storage_unmount`
- Safety: `CONFIG_BSP_SD_FORMAT_ON_MOUNT_FAIL` disabled; no card write or format

## Result

The diagnostic delegates reusable storage preparation and native SDMMC lifecycle to the exact-SKU board component. On the second board instance, it reported:

```text
sd_board_prepare=ESP_OK
sdcard_raw_probe=ESP_OK
sdcard_raw_card=name:SA16G capacity_mb:14772 max_freq_khz:400
sdcard_mount=ESP_OK
sdcard=PASS card_detected=1
```

## Conclusion

The verified I2C recovery, CH32V003 preparation, and native 1-bit SDMMC lifecycle are now preserved in the SKU 28154 BSP rather than remaining in diagnostic application code. Board MAC `94:a9:90:dd:16:6c` remains an instance-specific SDMMC hardware-path failure; core startup continues independently of SD availability.