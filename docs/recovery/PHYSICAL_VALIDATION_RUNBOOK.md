# Exact Hardware Validation Runbook

This runbook records physical validation evidence. Source evidence alone must not be marked as physical validation.

## Preconditions

- Use the exact SKU identified in the applicable board manifest.
- Record board serial or asset identifier, date, operator, power supply, cable, and firmware commit.
- Photograph or otherwise record the wiring before energizing the board.
- Start with outputs in the documented safe state.
- Stop on unexpected heat, smell, current, motion, relay activity, or bus traffic.

## Per-board record

| SKU | Board identity | Asset ID | Date | Operator | Result |
|---|---|---|---|---|---|
| 28154 | ESP32-S3-Touch-LCD-4 | PENDING | PENDING | PENDING | NOT RUN |
| 28141 | ESP32-S3-Touch-LCD-4.3B-BOX | PENDING | PENDING | PENDING | NOT RUN |
| 30838 | ESP32-S3-ETH-8DI-8RO | PENDING | PENDING | PENDING | NOT RUN |

## Required observations

Begin each board session with the read-only identity probe:

```bash
scripts/hardware/probe-esp32.sh 28154
```

Replace `28154` with the connected SKU. Pass `/dev/ttyACM0` as a second argument when more than one serial device is present. The probe records chip and flash identity but does not validate display, touch, GPIO, bus, relay, or power-cycle behavior.

For every board, attach evidence for:

- Boot, reset, brownout, and serial logging behavior.
- Every source-backed GPIO or bus mapping used by the application.
- Display initialization, orientation, color order, and touch coordinates where applicable.
- Digital input transitions and debounce behavior where applicable.
- Relay output safe state, activation, release, and power-cycle behavior for SKU 30838.
- RS485 and CAN electrical wiring, termination, direction control, and communication behavior where applicable.
- SD, USB, Ethernet, Wi-Fi, Bluetooth, RTC, buzzer, and RGB capabilities where applicable.
- Recovery after power removal, reconnect, invalid settings, and interrupted communication.

## Evidence locations

Store board-specific measurements and photographs under the matching `docs/devices/<SKU>/` directory. Update that directory's `VALIDATION_STATUS.md` only after the observations are complete and reproducible.
