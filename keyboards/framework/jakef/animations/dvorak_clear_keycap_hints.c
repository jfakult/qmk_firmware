/*

The purpose of this animation is for users on dvorak keyboards using clearcap keycaps to have a visual indicator of the layer they are on
After a period of user inactivity, the animation will pulse a list of keys (u, h, volume up/down, brightness up/down, 1/56/9)

While the user is typing it reverts to a more normal animation (pulling source code from raindrops for now)

*/

#include "dvorak_clear_keycap_hints.h"

static uint8_t user_type_inactivity;
static void DVORAK_CLEAR_KEYCAP_HINTS_init(effect_params_t* params) {
  user_type_inactivity = 0;
}

bool DVORAK_CLEAR_KEYCAP_HINTS(effect_params_t* params) {
    if (params->init) {
        DVORAK_CLEAR_KEYCAP_HINTS_init(params);
    }

    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    RGB rgb = rgb_matrix_hsv_to_rgb(rgb_matrix_config.hsv);
    for (uint8_t i = led_min + 5; i < led_max - 5; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
    return rgb_matrix_check_finished_leds(led_max);
}