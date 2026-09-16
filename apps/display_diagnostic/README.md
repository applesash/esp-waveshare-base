# display_diagnostic

Initial 28154 diagnostic firmware scope:

- Reports ESP32-S3 identity, MAC, flash size, heap, and reset reason.
- Performs read-only I2C presence scans on the documented expander and touch buses.
- Does not initialize the LCD or decode touch input until exact display timing and touch interrupt evidence is complete.

Build and flash only through the guarded workflow from the repository root:

```bash
scripts/hardware/board-workflow.sh flash 28154 /dev/ttyACM0 apps/display_diagnostic
```

Implement only in the applicable authorized phase.
