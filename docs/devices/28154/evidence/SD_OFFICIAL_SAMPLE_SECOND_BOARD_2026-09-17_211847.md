# 28154 Official SD Sample: Second Board: 2026-09-17

- Board identity: SKU 28154, MAC `e8:3d:c1:f7:89:c0`, port `/dev/ttyACM0`
- Card: same user-reported empty FAT32 16 GB microSD used on the first board
- Source: unmodified `examples/esp-idf/02_SD_Test` from the official Waveshare `ESP32-S3-Touch-LCD-4` repository, commit `aa604c1`
- SDK: ESP-IDF 5.5.5, target `esp32s3`
- SD path: native 1-bit SDMMC, CLK GPIO2, CMD GPIO1, D0 GPIO4
- Helper sequence: official I2C recovery and CH32V003 initialization at address `0x24`; EXIO1, EXIO3, EXIO5, and EXIO6 configured before mount

## Result

The official sample built and flashed successfully. Unlike the first board, it passed SDMMC card initialization and failed only at FAT filesystem mount:

```text
Initializing SD card
Using SDMMC peripheral
Mounting filesystem
vfs_fat_sdmmc: failed to mount card (13)
Failed to mount filesystem. If you want the card to be formatted, set the CONFIG_EXAMPLE_FORMAT_IF_MOUNT_FAILED menuconfig option.
```

The sample reached the filesystem stage but was built with its default format-on-mount-failure option disabled, so it performed no write or format.

## Conclusion

With the same card and unchanged official sample, the second 28154 board progresses past SDMMC protocol initialization while the first board times out in `sdmmc_init_ocr`. This isolates the first board's failure to its SDMMC electrical/card-slot path rather than firmware initialization or card format.

## Format And Read/Write Validation

The temporary official sample configuration was changed to set `CONFIG_EXAMPLE_FORMAT_IF_MOUNT_FAILED=y`, rebuilt, and flashed to this same verified board with explicit approval to format the empty card. The sample passed all intended filesystem operations:

```text
Filesystem mounted
Name: SA16G
Type: SDHC
Speed: 20.00 MHz (limit: 20.00 MHz)
Size: 14772MB
File written
Read from file: 'Hello SA16G!'
Formatting card, allocation unit size=16384
file doesnt exist, format done
File written
Read from file: 'Nihao SA16G!'
Card unmounted
```

The card was formatted successfully and remained usable through the post-format write/read verification. This establishes a physically tested native SDMMC and FAT filesystem path for board MAC `e8:3d:c1:f7:89:c0`.