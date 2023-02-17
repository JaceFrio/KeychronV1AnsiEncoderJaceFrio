#ifdef ENABLE_RGB_MATRIX_JACEFRIO_HEATMAP
RGB_MATRIX_EFFECT(JACEFRIO_HEATMAP)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static HSV JACEFRIO_HEATMAP_math(HSV hsv, uint16_t offset) {
  // Try removing ifdef to see what it does.
#            ifdef RGB_MATRIX_SOLID_REACTIVE_GRADIENT_MODE
    hsv.h = scale16by8(g_rgb_timer, add8(rgb_matrix_config.speed, 1) >> 6);
#            endif
    hsv.h += qsub8(90, offset);
    return hsv;
}

bool effect_runner_customreactive(effect_params_t* params, reactive_f effect_func) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    uint16_t max_tick = 65535 / qadd8(rgb_matrix_config.speed, 1);
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();

        uint16_t tick = max_tick;
        // Reverse search to find most recent key hit
        for (int8_t j = g_last_hit_tracker.count - 1; j >= 0; j--) {
            if (g_last_hit_tracker.index[j] == i && g_last_hit_tracker.tick[j] < tick) {
                tick = g_last_hit_tracker.tick[j];
                break;
            }
        }

        uint16_t offset = scale16by8(tick, qadd8(rgb_matrix_config.speed, 1));
        HSV hsv0 = rgb_matrix_config.hsv;
        RGB rgb1 = rgb_matrix_hsv_to_rgb(effect_func(hsv0, offset));
        hsv0.h += rgb_matrix_config.speed + 55;
        RGB rgb2 = rgb_matrix_hsv_to_rgb(effect_func(hsv0, offset));
        
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
bool JACEFRIO_HEATMAP(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    //return rgb_matrix_check_finished_leds(led_max);
    return effect_runner_customreactive(params, &JACEFRIO_HEATMAP_math);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_JACEFRIO_HEATMAP
