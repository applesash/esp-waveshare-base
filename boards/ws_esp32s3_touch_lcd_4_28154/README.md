# Waveshare ESP32-S3-Touch-LCD-4 BSP

Do not implement until PHASE-02 evidence is complete for SKU 28154.

Official exact-SKU source page: https://www.waveshare.com/wiki/ESP32-S3-Touch-LCD-4
The SKU can appear in generic search results or family listings; the exact wiki page is the authoritative source for this board.

## Component Model

This directory is one ESP-IDF component for the complete exact-SKU board architecture. Each `src/board_*.c` module owns one verified peripheral area, while the component exposes neutral APIs to hardware providers and diagnostics. Applications must not duplicate board GPIO, bus, expander, or driver initialization.

The implemented `board_storage` module owns the source-backed I2C recovery, CH32V003 preparation, and native 1-bit SDMMC lifecycle. Future display, touch, RS485, RTC, and other modules shall extend this component only after the applicable phase gate, source evidence, and physical validation pass. Diagnostic probes and physical evidence remain retained under `docs/devices/28154/`.

## Current Coverage

This is not yet a complete BSP. Only `board_storage` is compiled and exposed; the validated display, touch, RS485, RTC, and helper findings remain in evidence and diagnostic code pending their applicable phase-gated promotion.
