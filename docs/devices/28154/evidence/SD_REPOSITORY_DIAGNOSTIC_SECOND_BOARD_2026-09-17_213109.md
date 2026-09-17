# 28154 Repository SD Diagnostic: Second Board: 2026-09-17

- Board identity: SKU 28154, MAC `e8:3d:c1:f7:89:c0`, port `/dev/ttyACM0`
- Card: 16 GB FAT32 microSD formatted and verified by the official Waveshare SD sample
- Firmware: repository `apps/display_diagnostic`, ESP-IDF 5.5.5
- SD path: native 1-bit SDMMC, CLK GPIO2, CMD GPIO1, D0 GPIO4
- Board preparation: I2C recovery followed by CH32V003 setup at `0x24`; touch reset, LCD reset, and system enable released before SD initialization
- Safety: `CONFIG_BSP_SD_FORMAT_ON_MOUNT_FAIL` disabled; the diagnostic performs no card format or write

## Result

```text
sd_board_prepare=PASS ch32=0x24 sys_en=1 lcd_reset=1 touch_reset=1
sdcard_raw_probe=ESP_OK
sdcard_raw_card=name:SA16G capacity_mb:14772 max_freq_khz:400
sdcard_mount=ESP_OK
sdcard=PASS card_detected=1
lcd_init=PASS resolution=480x480 pattern=red-green-blue
ch32_helper=PASS
rtc=ESP_OK
touch_controller=GT911 address=0x5d status=ESP_OK
diagnostic_complete=PASS
```

## Conclusion

The repository diagnostic now follows the source-backed native SDMMC and CH32 preparation sequence without importing the official sample implementation. It successfully initialized and mounted the card on the second physical SKU 28154 board while preserving a read-only SD test policy. The first board, MAC `94:a9:90:dd:16:6c`, remains a board-specific SDMMC electrical-path failure.