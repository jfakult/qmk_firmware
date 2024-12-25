// !!! DO NOT ADD #pragma once !!! //
//#include "rgb_matrix_types.h"

// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)

// #ifndef RGB_MATRIX_CUSTOM_EFFECTS_H
// #define RGB_MATRIX_CUSTOM_EFFECTS_H

//#define RGB_MATRIX_JAKE_CUSTOM_EFFECTS
//#define RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#ifdef RGB_MATRIX_JAKE_CUSTOM_EFFECTS

RGB_MATRIX_EFFECT(my_cool_effect)
RGB_MATRIX_EFFECT(my_cool_effect1_5)
RGB_MATRIX_EFFECT(my_cool_effect2)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// e.g: A simple effect, self-contained within a single method
static bool my_cool_effect(effect_params_t *params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  for (uint8_t i = led_min; i < led_max; i++) {
    rgb_matrix_set_color(i, 0xff, 0xff, 0x00);
  }
  return rgb_matrix_check_finished_leds(led_max);
}

static HSV my_cool_effect1_5_math(HSV hsv, int8_t sin, int8_t cos, uint8_t i, uint8_t time) {
    hsv.h += ((g_led_config.point[i].y - k_rgb_matrix_center.y) * 2 * cos + (g_led_config.point[i].x - k_rgb_matrix_center.x) * 2 * sin) / 128;
    return hsv;
}

bool my_cool_effect1_5(effect_params_t* params) {
    return effect_runner_sin_cos_i(params, &my_cool_effect1_5_math);
}

// e.g: A more complex effect, relying on external methods and state, with
// dedicated init and run methods
static uint8_t some_global_state;
static void    my_cool_effect2_complex_init(effect_params_t* params) {
    some_global_state = 1;
    // return 1;
}
static bool my_cool_effect2_complex_run(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (uint8_t i = led_min; i < led_max; i++) {
        rgb_matrix_set_color(i, 0xff, some_global_state++, 0xff);
    }

    if (some_global_state > 255) {
        some_global_state = 1;
    }
    return rgb_matrix_check_finished_leds(led_max);
}
static bool my_cool_effect2(effect_params_t* params) {
    if (params->init) my_cool_effect2_complex_init(params);
    return my_cool_effect2_complex_run(params);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#endif // RGB_MATRIX_JAKE_CUSTOM_EFFECTS

// #endif // RGB_MATRIX_CUSTOM_EFFECTS_H