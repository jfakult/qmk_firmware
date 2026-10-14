#include QMK_KEYBOARD_H
#include <stdint.h>

enum layers {
  _BASE,
};

// Data-driven: uses the layout name from info.json ("LAYOUT_all")
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    // 56 positions (8 rows x 7 cols) because your data-driven layout is full-matrix.
    // Put KC_NO anywhere you don't have a physical switch.

    // Left half: rows 0-3 (7 cols each)  = 28
    KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,
    KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,
    KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,
    KC_LSFT,KC_LCTL,KC_LALT,KC_SPC, KC_NO,  KC_NO,  KC_NO,  // example: unused spots

    // Right half: rows 4-7 (7 cols each) = 28
    KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSLS,KC_BSPC,
    KC_K,   KC_L,   KC_SCLN,KC_QUOT,KC_ENT, KC_NO,  KC_NO,
    KC_COMM,KC_DOT, KC_SLSH,KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,KC_NO,  KC_NO,  KC_NO
  )
};

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT); // keep QMK effects from fighting you
}

void housekeeping_task_user(void) {
    static uint8_t hue = 0;
    hue++;

    for (uint8_t i = 0; i < RGBLIGHT_LED_COUNT; i++) {
        rgblight_sethsv_at(hue + i * 10, 255, 150, i);
    }
}

