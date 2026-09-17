# Changelog

## Unreleased
- Added mandatory BSP-promotion and evidence-retention gates to the serial/storage, display, touch, and I/O hardware phases.
- Added mandatory per-SKU physical-validation gates: all three boards for serial/storage, both touch-display boards for display and touch, and every applicable capability on every supported SKU for I/O.
- Promoted the verified SKU 28154 storage initialization and native SDMMC lifecycle into the unified board component, with read-only physical validation on a second board instance.
- Preserved the 28154 storage validation in its board manifest and capability header; identified the official 28141 schematic/demo sources and corrected SKU 30838 to the PoE Ethernet 8DI/8RO variant for Phase-02 evidence completion.

## 0.1.4
- Completed PHASE-02 source evidence discovery for the three supported SKUs using the official Waveshare pages and documentation.
- Recorded exact source, GPIO, capability, and validation status evidence for the display and relay boards while keeping physical hardware validation explicitly pending.
- Updated project status and traceability to reflect PHASE-02 in progress and the remaining closeout requirements.

## 0.1.3
- Confirmed local PHASE-01 workspace validation gate and recorded its evidence in the project status and restore-point docs.
- Remote publish remains pending GitHub authentication and remote repository configuration, so the checkpoint is fully validated locally but not yet published remotely.

## 0.1.2
- Completed local PHASE-00 repository baseline and PHASE-01 workspace validation.
- Added VS Code workspace file for the ESP-IDF project and verified the required toolchain checks using the repository script.
- Documented local phase checkpoint status and restore-point tracking while remote publishing remains pending GitHub authentication and remote setup.

## 0.1.1
- Integrated mandatory phase restore points, immutable tags, HTTPS push verification, snapshots, and recovery checks.

## 0.1.0
- Established Version 3.0 repository and agent contract baseline.
