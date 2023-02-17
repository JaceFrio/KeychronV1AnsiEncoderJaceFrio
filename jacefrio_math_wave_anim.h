#ifdef ENABLE_RGB_MATRIX_JACEFRIO_MATH_WAVE
RGB_MATRIX_EFFECT(JACEFRIO_MATH_WAVE)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static HSV JACEFRIO_MATH_WAVE_math(HSV hsv, uint8_t i, uint8_t time) {
    hsv.h = g_led_config.point[i].y * sin(2 / (g_led_config.point[i].x - (10 * time)));
    return hsv;
}

bool customeffect_runner_i(effect_params_t* params, i_f effect_func) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    uint8_t time = scale16by8(g_rgb_timer, qadd8(rgb_matrix_config.speed / 8, 1));
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        RGB rgb = rgb_matrix_hsv_to_rgb(effect_func(rgb_matrix_config.hsv, i, time));
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
    return rgb_matrix_check_finished_leds(led_max);
}

bool JACEFRIO_MATH_WAVE(effect_params_t* params) {
    return customeffect_runner_i(params, &JACEFRIO_MATH_WAVE_math);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_JACEFRIO_MATH_WAVE