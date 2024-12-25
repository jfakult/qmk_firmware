// https://docs.qmk.fm/features/rgb_matrix

// Note: For key positions, see framework/ansi/ansi.c. Its a pain

#ifdef RGB_MATRIX_JAKE_CUSTOM_EFFECTS

// FWA == FrameWork ANSI
#define FWA_F2 19
#define FWA_F3 18
#define FWA_F7 26
#define FWA_F8 67
#define FWA_K5 9
#define FWA_K6 14
#define FWA_KU 43
#define FWA_KH 49


RGB_MATRIX_EFFECT(my_cool_effect)
RGB_MATRIX_EFFECT(my_cool_effect1_5)
RGB_MATRIX_EFFECT(my_cool_effect2)
// https://www.reddit.com/r/olkb/comments/hxtuf7/custom_qmk_effect_i_made_3_led_effects_that_cycle/
RGB_MATRIX_EFFECT(HUE_BREATHING1)
RGB_MATRIX_EFFECT(HUE_PENDULUM1)
RGB_MATRIX_EFFECT(HUE_WAVE1)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// Convert a value from one range to another
int map(int x, int in_min, int in_max, int out_min, int out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// e.g: A simple effect, self-contained within a single method
static bool my_cool_effect(effect_params_t *params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  for (uint8_t i = led_min; i < led_max; i++)
  {
    uint8_t r = (g_led_config.point[i].x + g_led_config.point[i].y) / 2;
    uint8_t g = (g_led_config.point[i].x + g_led_config.point[i].y) / 2;
    uint8_t b = (g_led_config.point[i].x + g_led_config.point[i].y) / 2;

    r = 0;
    g = 0;
    b = 0;
    
    int num_leds = led_max - led_min;
    int index = i - led_min;
    if (index < num_leds / 3)
    {
      
      r = map(index, 0, num_leds / 3, 0, 0xff);
    }
    else if (index >= num_leds / 3 && i < (num_leds * 2) / 3)
    {
      g = map(index, num_leds / 3, (num_leds * 2) / 3, 0, 0xff);
    }
    else if (index >= (num_leds * 2) / 3)
    {
      b = map(index, (num_leds * 2) / 3, num_leds, 0, 0xff); 
    }
    else
    {
      r = (index * 0xff) / num_leds;
      g = (index * 0xff) / num_leds;
      b = (index * 0xff) / num_leds;
    }

    b = 0;
    r = 0;
    g = 10;

    //uint8_t x = g_led_config.point[i].x;
    //uint8_t y = g_led_config.point[i].y;
    // Grab label from g_led_config.point
    
    if (i == FWA_F2 ||
        i == FWA_F3 ||
        i == FWA_F7 ||
        i == FWA_F8 ||
        i == FWA_K5 ||
        i == FWA_K6 ||
        i == FWA_KU ||
        i == FWA_KH
    )
    {
      r = 0xff;
      g = 0;
      b = 0xff;
    }

    rgb_matrix_set_color(i, r, g, b);
  }
  return rgb_matrix_check_finished_leds(led_max);
}

static HSV my_cool_effect1_5_math(HSV hsv, int8_t sin, int8_t cos, uint8_t i, uint8_t time) {
    // If i matches one of the FWA keys, shift the hue by some degrees
    if (i == FWA_F2 ||
        i == FWA_F3 ||
        i == FWA_F7 ||
        i == FWA_F8 ||
        i == FWA_K5 ||
        i == FWA_K6 ||
        i == FWA_KU ||
        i == FWA_KH
    )
    {
      hsv.h += 128;
    }
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

//Change huedelta to adjust range of hue change. 0-255 I think.
//Hue Breathing - All LED's light up
bool HUE_BREATHING1(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
	uint8_t huedelta = 100;
    HSV      hsv  = rgb_matrix_config.hsv;
    uint16_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 8);
    hsv.h         = hsv.h + scale8(abs8(sin8(time) - 128) * 2, huedelta);
    RGB rgb       = hsv_to_rgb(hsv);
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
    return rgb_matrix_check_finished_leds(led_max);
}

//Change huedelta to adjust range of hue change. 0-255 I think. Looks better with a low value and slow speed for subtle change.
//Hue Pendulum - color changes in a wave to the right before reversing direction
static HSV HUE_PENDULUM1_math(HSV hsv, uint8_t i, uint8_t time) {
	uint8_t huedelta = 100;
    hsv.h = hsv.h + scale8(abs8(sin8(time) + (g_led_config.point[i].x) - 128) * 2, huedelta);
    return hsv;
}

bool HUE_PENDULUM1(effect_params_t* params) { return effect_runner_i(params, &HUE_PENDULUM1_math); }

//Change huedelta to adjust range of hue change. 0-255 I think. Looks better with a low value and slow speed for subtle change.
//Hue Wave - color changes in a wave to the right
static HSV HUE_WAVE1_math(HSV hsv, uint8_t i, uint8_t time) {
	uint8_t huedelta = 100;
	 hsv.h = hsv.h + scale8(abs8(g_led_config.point[i].x - time), huedelta);
    return hsv;
}

bool HUE_WAVE1(effect_params_t* params) { return effect_runner_i(params, &HUE_WAVE1_math); }


#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#endif // RGB_MATRIX_JAKE_CUSTOM_EFFECTS

// #endif // RGB_MATRIX_CUSTOM_EFFECTS_H