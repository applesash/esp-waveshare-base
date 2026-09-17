# 28141 Official SPI SD Validation: 2026-09-17

- Board identity: SKU 28141, MAC `14:c1:9f:4a:fd:a8`, port `/dev/ttyACM0`
- Card: 16 GB FAT32 microSD, `SA16G`
- Source: unmodified official 4.3B-BOX ESP-IDF `03_SD_Test`
- SDK: ESP-IDF 5.5.5, target `esp32s3`
- SD interface: SPI, MOSI GPIO11, MISO GPIO13, CLK GPIO12, CH422G EXIO4 chip select
- CH422G I2C: SCL GPIO9, SDA GPIO8

## Result

The official sample mounted the card and passed both write/read checks:

```text
Filesystem mounted
Name: SA16G
Type: SDHC
Speed: 20.00 MHz (limit: 20.00 MHz)
Size: 14772MB
Read from file: 'Hello SA16G!'
Read from file: 'Nihao SA16G!'
Card unmounted
```

No format option was enabled. The vendor sample emitted an ESP-IDF legacy-I2C-driver warning; no vendor implementation code was copied into this repository.