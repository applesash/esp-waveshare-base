# 28154 SDMMC EXIO4 Control Validation: 2026-09-17

- Board identity: SKU 28154, MAC `94:a9:90:dd:16:6c`, port `/dev/ttyACM0`
- Card: newly installed user-reported 16 GB microSD, empty FAT32
- Firmware: `apps/display_diagnostic`, flashed through `scripts/hardware/board-workflow.sh`
- SD path: native 1-bit SDMMC, CLK GPIO2, CMD GPIO1, D0 GPIO4, internal pull-ups enabled
- Board preparation: CH32 helper at `0x24`; SYS_EN, LCD reset, and touch reset released before probe
- Safety: read-only raw initialization and mount probe; no format or write performed

## Experiment

After the existing 0, 100, 500, and 2000 ms post-helper timing probes, the diagnostic configured the source-recorded EXIO4/SDCS channel as an output through the official CH32 helper driver. It then ran a fresh native SDMMC probe after a 500 ms settle period at each logic level. The test deliberately reports raw levels and does not assume an active polarity.

| EXIO4 level | Helper configuration | Raw SDMMC initialization |
|---:|---|---|
| 0 | `ESP_OK` | `ESP_ERR_TIMEOUT` |
| 1 | `ESP_OK` | `ESP_ERR_TIMEOUT` |

The subsequent BSP mount also returned `ESP_ERR_TIMEOUT`. Each failure occurred in `sdmmc_init_ocr: send_op_cond` before filesystem detection. LCD, CH32 helper, RTC, and GT911 touch initialization succeeded after the SD probes.

## Conclusion

Changing EXIO4 alone does not resolve the SDMMC protocol timeout. Together with the timing matrix, this rules out the tested post-helper delay range and both EXIO4 logic levels as the immediate cause. Further investigation requires source-backed inspection of the SD card electrical path or a physical slot/card compatibility check; an unsupported SDSPI remap must not be introduced.