# ESP32 Probe: 2026-09-16_214239

## Probe metadata

- Requested SKU: `28154`
- Serial port: `/dev/ttyACM0`
- Probe type: read-only chip and flash identity; no erase or firmware write
- USB descriptor: `Bus 003 Device 015: ID 303a:1001 Espressif USB JTAG/serial debug unit`

## Chip probe

```text
esptool.py v4.12.0
Serial port /dev/ttyACM0
Connecting...
Detecting chip type... ESP32-S3
Chip is ESP32-S3 (QFN56) (revision v0.2)
Features: WiFi, BLE, Embedded PSRAM 8MB (AP_3v3)
Crystal is 40MHz
USB mode: USB-Serial/JTAG
MAC: 94:a9:90:dd:16:6c
Uploading stub...
Running stub...
Stub running...
Warning: ESP32-S3 has no Chip ID. Reading MAC instead.
MAC: 94:a9:90:dd:16:6c
Hard resetting via RTS pin...
```

## Flash probe

```text
esptool.py v4.12.0
Serial port /dev/ttyACM0
Connecting...
Detecting chip type... ESP32-S3
Chip is ESP32-S3 (QFN56) (revision v0.2)
Features: WiFi, BLE, Embedded PSRAM 8MB (AP_3v3)
Crystal is 40MHz
USB mode: USB-Serial/JTAG
MAC: 94:a9:90:dd:16:6c
Uploading stub...
Running stub...
Stub running...
Manufacturer: 46
Device: 4018
Detected flash size: 16MB
Flash type set in eFuse: quad (4 data lines)
Flash voltage set by eFuse to 3.3V
Hard resetting via RTS pin...
```

## Interpretation

- USB/chip/flash connection: PASS
- Exact Waveshare SKU: requires user identification or board-specific evidence
- Display, touch, GPIO, bus, relay, and power-cycle behavior: NOT TESTED by this probe
