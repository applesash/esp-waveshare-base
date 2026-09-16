# Industrial HMI and Automation Platform

Reusable ESP-IDF platform for:

- Waveshare ESP32-S3-Touch-LCD-4, SKU 28154
- Waveshare ESP32-S3-Touch-LCD-4.3B-BOX, SKU 28141
- Waveshare ESP32-S3 WiFi 8CH Relay Module RS485, SKU 30838

Start by reading `AGENT_CONTRACT.md`, `AGENT_STARTUP.md`, and `PROJECT_STATUS.md`.
Only PHASE-00 and PHASE-01 are initially authorized.

## Phase recovery
Every successful phase must be committed, tagged, pushed, snapshotted, and verified before the next phase begins. See `docs/recovery/RECOVERY_POLICY.md`.
