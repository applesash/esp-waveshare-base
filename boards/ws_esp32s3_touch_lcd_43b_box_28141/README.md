# Waveshare ESP32-S3-Touch-LCD-4.3B-BOX BSP

Do not implement until PHASE-02 evidence is complete for SKU 28141.

Official exact-SKU sources:
- https://www.waveshare.com/esp32-s3-touch-lcd-4.3b.htm?sku=28141
- https://docs.waveshare.com/ESP32-S3-Touch-LCD-4.3B

The 4.3B box variant is treated as the same electronics family as the non-box 4.3B design, with the enclosure difference being a mechanical packaging difference unless an exact source states otherwise.

## Component Model

This directory is the single ESP-IDF component for exact SKU 28141. `board_display`, `board_touch`, `board_rtc`, `board_storage`, and `board_rs485` own source-backed hardware initialization and neutral APIs. The diagnostic consumes those APIs and retains test patterns, raw touch logs, and other test-only behavior.

CAN physical validation is deferred by the owner. RTC transport is implemented, while retained-time and interrupt validation remain pending.

The board shares GPIO11, GPIO12, and GPIO13 between SPI SD storage and the RGB display data bus. Storage and display must therefore be serialized; the diagnostic mounts and unmounts storage before display initialization.
