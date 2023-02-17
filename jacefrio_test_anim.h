#ifdef ENABLE_RGB_MATRIX_JACEFRIO_TEST
RGB_MATRIX_EFFECT(JACEFRIO_TEST)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static HSV JACEFRIO_TEST_math(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {    
    uint16_t effect = tick - dist;
    if (effect > 255) effect = 255;
    hsv.h = qadd8(hsv.h, 255 - effect) - 20;
    return hsv;
}

bool effect_runner_test(uint8_t start, effect_params_t* params, reactive_splash_f effect_func) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    uint8_t count = g_last_hit_tracker.count;
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        HSV hsv = rgb_matrix_config.hsv;
        // hsv.v   = 0;
        for (uint8_t j = start; j < count; j++) {
            int16_t  dx   = g_led_config.point[i].x - g_last_hit_tracker.x[j];
            int16_t  dy   = g_led_config.point[i].y - g_last_hit_tracker.y[j];
            uint8_t  dist = sqrt16(dx * dx + dy * dy);
            uint16_t tick = scale16by8(g_last_hit_tracker.tick[j], qadd8(rgb_matrix_config.speed, 1));
            hsv           = effect_func(hsv, dx, dy, dist, tick);
        }
        hsv.v   = scale8(hsv.v, rgb_matrix_config.hsv.v);

        RGB rgb1 = rgb_matrix_hsv_to_rgb(hsv);
        hsv.h += rgb_matrix_config.speed + 20;
        RGB rgb2 = rgb_matrix_hsv_to_rgb(hsv);
        
        if ((i == 1) || (i == 2) || (i == 3) || (i == 4) || (i == 9) || (i == 10) || (i == 11) || (i == 12) || (i == 29) || (i == 30) || (i == 44) || (i == 45) || (i == 58) || (i == 59) || (i == 70) || (i == 72) || (i == 73) || (i == 74) || (i == 76) || (i == 77) || (i == 78)) {
          if (host_keyboard_led_state().caps_lock) {
            rgb_matrix_set_color(i, rgb1.r, rgb1.g, rgb1.b);
          }
          else {
            rgb_matrix_set_color(i, rgb2.r, rgb2.g, rgb2.b);
          }
          } else {
            if (host_keyboard_led_state().caps_lock) {
              rgb_matrix_set_color(i, rgb2.r, rgb2.g, rgb2.b);
            }
            else {
              rgb_matrix_set_color(i, rgb1.r, rgb1.g, rgb1.b);
            }
        }
    }
    return rgb_matrix_check_finished_leds(led_max);
}

// alphas = color1, mods = color2
bool JACEFRIO_TEST(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    //return rgb_matrix_check_finished_leds(led_max);
    return effect_runner_test(qsub8(g_last_hit_tracker.count, 1), params, &JACEFRIO_TEST_math);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_JACEFRIO_TEST
