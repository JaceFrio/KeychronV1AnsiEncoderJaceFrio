#ifdef ENABLE_RGB_MATRIX_JACEFRIO_BREATHINGCYCLE
RGB_MATRIX_EFFECT(JACEFRIO_BREATHINGCYCLE)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// alphas = color1, mods = color2
bool JACEFRIO_BREATHINGCYCLE(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    HSV hsv = rgb_matrix_config.hsv;
    uint16_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 8);
    hsv.v = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
    hsv.h = scale16by8(g_rgb_timer, add8(rgb_matrix_config.speed, 1) >> 6);
    RGB rgb1 = rgb_matrix_hsv_to_rgb(hsv);
    hsv.h += rgb_matrix_config.speed + 10;
    RGB rgb2 = rgb_matrix_hsv_to_rgb(hsv);

    for (uint8_t i = led_min; i < led_max; i++) {
        if ((i == 1) || (i == 2) || (i == 3) || (i == 4) || (i == 9) || (i == 10) || (i == 11) || (i == 12) || (i == 29) || (i == 30) || (i == 44) || (i == 45) || (i == 58) || (i == 59) || (i == 70) || (i == 72) || (i == 73) || (i == 74) || (i == 76) || (i == 77) || (i == 78)) {
            rgb_matrix_set_color(i, rgb2.r, rgb2.g, rgb2.b);
        } else {
            rgb_matrix_set_color(i, rgb1.r, rgb1.g, rgb1.b);
        }
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_JACEFRIO_BREATHINGCYCLE
