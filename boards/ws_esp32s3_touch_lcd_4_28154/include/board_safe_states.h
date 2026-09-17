#pragma once

/* Official CH32 sequence: assert reset/buzzer low, then release SYS_EN/LCD/TP reset high. */
#define BOARD_INIT_TOUCH_RESET_EXPANDER_CHANNEL 1
#define BOARD_INIT_LCD_RESET_EXPANDER_CHANNEL 3
#define BOARD_INIT_SYSTEM_ENABLE_EXPANDER_CHANNEL 5
#define BOARD_INIT_BUZZER_ENABLE_EXPANDER_CHANNEL 6
#define BOARD_INIT_ASSERT_LEVEL 0
#define BOARD_INIT_RELEASE_LEVEL 1

/* Owner-approved: no external connector output is driven until its authorized service owns it. */
#define BOARD_SAFE_STATE_EXTERNAL_OUTPUTS_RESOLVED 1
#define BOARD_SAFE_STATE_EXTERNAL_OUTPUTS_CONFIGURE_AT_STARTUP 0
