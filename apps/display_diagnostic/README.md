# display_diagnostic_28154

Initial 28154 diagnostic firmware scope:

- Reports ESP32-S3 identity, MAC, flash size, heap, and reset reason.
- Performs read-only I2C presence scans on the documented expander and touch buses.
- Reads the GT911 product/status registers at the observed `0x5d` address and prints touch coordinates when a touch is reported.
- Does not initialize the LCD until exact display timing evidence is complete.

Build and flash only through the guarded workflow from the repository root:

```bash
scripts/build/build-board.sh 28154 build
scripts/hardware/board-workflow.sh flash 28154 /dev/ttyACM0 apps/display_diagnostic
```

Implement only in the applicable authorized phase.
