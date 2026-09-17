# Validation Status

Source-based hardware facts have been extracted from the official Waveshare wiki and recorded. On 2026-09-16, the user-identified exact board responded on `/dev/ttyACM0` as an ESP32-S3 USB JTAG/serial device; the latest connection-level evidence is recorded in [PHYSICAL_VALIDATION_2026-09-16_213908.md](evidence/PHYSICAL_VALIDATION_2026-09-16_213908.md).

Current status: CONNECTION VERIFIED; FUNCTIONAL RELAY/GPIO/RS485 VALIDATION PENDING

Phase-02 source correction: SKU 30838 is the ESP32-S3-POE-ETH-8DI-8RO variant. Extract exact mapping and safe-state facts from the official PoE demo and the SKU-confirmed board sources before implementation. Do not use the CAN-suffixed variants or infer relay, DI, SD, and TCA9554 behavior from a family listing.
