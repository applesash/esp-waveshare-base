# 28154 SD Retry/Pull-up Validation: 2026-09-17

- Card: user-reported 16 GB microSD
- Native SDMMC: 1-bit, CLK GPIO2, CMD GPIO1, D0 GPIO4
- Probe clock: 400 kHz
- ESP-IDF internal pull-ups: enabled on slot pins for this experiment
- Raw initialization attempts: 3

## Results

```text
sdcard_raw_attempt=1 result=ESP_ERR_TIMEOUT
sdcard_raw_attempt=2 result=ESP_ERR_TIMEOUT
sdcard_raw_attempt=3 result=ESP_ERR_TIMEOUT
sdcard_raw_probe=ESP_ERR_TIMEOUT
sdcard_mount=ESP_ERR_TIMEOUT
```

No formatting or writing occurred. Retries and internal pull-ups did not change the result. The card still fails before filesystem detection, pointing to card/slot electrical contact, signal wiring, or card-controller compatibility.
