# display_diagnostic_28154

Initial 28154 diagnostic firmware scope:

- Reports ESP32-S3 identity, MAC, flash size, heap, and reset reason.
- Performs read-only I2C presence scans on the documented expander and touch buses.
- Reads the GT911 product/status registers at the observed `0x5d` address and prints touch coordinates when a touch is reported.
- Initializes the LCD through the official Waveshare ESP-IDF BSP and renders an RGB565 red/green/blue test pattern.
- Runs a read-only native 1-bit SDMMC initialization and mount check using the official GPIO2 clock, GPIO1 command, and GPIO4 data mapping. It does not format or write the inserted card.

Build and flash only through the guarded workflow from the repository root:

```bash
scripts/build/build-board.sh 28154 build
scripts/hardware/board-workflow.sh flash 28154 /dev/ttyACM0 apps/display_diagnostic
```

Implement only in the applicable authorized phase.
