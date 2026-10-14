#pragma once

// If your SK6812 strip is RGBW (most are)
#define WS2812_RGBW

// Optional but recommended
#define RGBLIGHT_LIMIT_VAL 180
#define RGBLIGHT_SLEEP

// Split behavior (simple + reliable)
#define MASTER_LEFT

#define SOFT_SERIAL_PIN GP0

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 250U
