// Add your new core rgb matrix effect here, order determines enum order
#include "jacefrio_anim.h"
#include "jacefrio_coldmap_anim.h"
#include "jacefrio_heatmap_anim.h"
#include "jacefrio_lightmap_anim.h"
#include "jacefrio_math_wave_anim.h"
#include "jacefrio_twocolor_wave_anim.h"
#include "jacefrio_wave_anim.h"
#include "jacefrio_breathingcycle_anim.h"
#include "jacefrio_flow_anim.h"
#include "jacefrio_test_anim.h"
#include "fire_anim.h"
#include "flower_blooming_anim.h"
#include "kitt_anim.h"

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

bool effect_runner_sin_cos_i(effect_params_t* params, sin_cos_i_f effect_func) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    uint16_t time      = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 4);
    int8_t   cos_value = cos8(time) - 128;
    int8_t   sin_value = sin8(time) - 128;
    for (uint8_t i = led_min; i < led_max; i++) {
        if (i == 35) {
          HSV hsvc = rgb_matrix_config.hsv;
          hsvc.h = 0;
          hsvc.s = 0;
          RGB rgbc = rgb_matrix_hsv_to_rgb(hsvc);
          rgb_matrix_set_color(i, rgbc.r, rgbc.g, rgbc.b);
        }
        else {
          RGB_MATRIX_TEST_LED_FLAGS();
          RGB rgb = rgb_matrix_hsv_to_rgb(effect_func(rgb_matrix_config.hsv, cos_value, sin_value, i, time));
          rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#endif