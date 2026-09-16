# Industrial HMI and Automation Platform

Reusable ESP-IDF platform for:

- Waveshare ESP32-S3-Touch-LCD-4, SKU 28154
- Waveshare ESP32-S3-Touch-LCD-4.3B-BOX, SKU 28141
- Waveshare ESP32-S3 WiFi 8CH Relay Module RS485, SKU 30838

Start by reading `AGENT_CONTRACT.md`, `AGENT_STARTUP.md`, and `PROJECT_STATUS.md`.
Only PHASE-00 and PHASE-01 are initially authorized.

## Phase recovery
Every successful phase must be committed, tagged, pushed, snapshotted, and verified before the next phase begins. See `docs/recovery/RECOVERY_POLICY.md`.

On Linux, the repeatable workflow is `scripts/github/create-phase-checkpoint.sh`, followed by `scripts/github/finalize-phase-closeout.sh` and `scripts/github/verify-phase-closeout.sh`.

For board testing, use `scripts/hardware/board-workflow.sh check SKU [PORT]` before any flash. Use its `flash` mode only with an approved firmware project and explicit confirmation.

For board-specific builds, use `scripts/build/build-board.sh SKU build`. The registry rejects unimplemented SKUs instead of building another board's project.
