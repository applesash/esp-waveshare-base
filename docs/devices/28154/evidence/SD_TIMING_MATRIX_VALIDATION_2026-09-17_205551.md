# 28154 SDMMC Timing Matrix Validation: 2026-09-17

- Board identity: SKU 28154, MAC `94:a9:90:dd:16:6c`, port `/dev/ttyACM0`
- Card: newly installed user-reported 16 GB microSD, empty FAT32
- Firmware: `apps/display_diagnostic`, flashed through `scripts/hardware/board-workflow.sh`
- SD path: native 1-bit SDMMC, CLK GPIO2, CMD GPIO1, D0 GPIO4, internal pull-ups enabled
- Board preparation: CH32 helper at `0x24`; SYS_EN, LCD reset, and touch reset released before probe
- Safety: read-only raw initialization and mount probe; no format or write performed

## Result

The post-helper-release settle-time matrix was tested before LCD initialization:

| Settle delay | Raw SDMMC initialization |
|---:|---|
| 0 ms | `ESP_ERR_TIMEOUT` |
| 100 ms | `ESP_ERR_TIMEOUT` |
| 500 ms | `ESP_ERR_TIMEOUT` |
| 2000 ms | `ESP_ERR_TIMEOUT` |

The subsequent BSP mount also returned `ESP_ERR_TIMEOUT`. Each failure occurred in `sdmmc_init_ocr: send_op_cond` before filesystem detection, so FAT32 was not reached. The display, CH32 helper, RTC, and GT911 touch controller initialized successfully after the SD attempts.

## Conclusion

The empty FAT32 card and tested 0-2000 ms post-helper settling window do not resolve the native SDMMC timeout. Generic board boot-settle timing is not the root cause within this range. Further work must retain the exact-SKU native SDMMC mapping and investigate the card/slot electrical path or a source-backed SD control requirement not represented in the current native path.