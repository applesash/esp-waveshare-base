#pragma once

#include <stdint.h>

#include "esp_err.h"

typedef struct {
    char name[8];
    uint32_t capacity_mb;
    uint32_t max_freq_khz;
} board_storage_card_info_t;

esp_err_t board_storage_prepare(void);
esp_err_t board_storage_probe(board_storage_card_info_t *card_info);
esp_err_t board_storage_mount(void);
esp_err_t board_storage_unmount(void);