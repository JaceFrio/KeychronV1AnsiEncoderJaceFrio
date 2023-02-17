#ifdef ENABLE_RGB_MATRIX_JACEFRIO
RGB_MATRIX_EFFECT(JACEFRIO)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// alphas = color1, mods = color2
bool JACEFRIO(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    HSV hsv = rgb_matrix_config.hsv; // + mod;
    RGB rgb1 = rgb_matrix_hsv_to_rgb(hsv);
    hsv.h += rgb_matrix_config.speed + 10;
    RGB rgb2 = rgb_matrix_hsv_to_rgb(hsv);

    for (uint8_t i = led_min; i < led_max; i++) {
        if ((i == 1) || (i == 2) || (i == 3) || (i == 4) || (i == 9) || (i == 10) || (i == 11) || (i == 12) || (i == 29) || (i == 30) || (i == 44) || (i == 45) || (i == 58) || (i == 59) || (i == 70) || (i == 72) || (i == 73) || (i == 74) || (i == 76) || (i == 77) || (i == 78)) {
            rgb_matrix_set_color(i, rgb2.r, rgb2.g, rgb2.b);
        }
        else if (i == 0) {
          uint8_t time = scale16by8(g_rgb_timer, qadd8(rgb_matrix_config.speed / 4, 1));
          HSV hsv3 = rgb_matrix_config.hsv;
          hsv3.h = time;
          RGB rgb3 = rgb_matrix_hsv_to_rgb(hsv3);
          rgb_matrix_set_color(i, rgb3.r, rgb3.g, rgb3.b);
        } 
        else {
            rgb_matrix_set_color(i, rgb1.r, rgb1.g, rgb1.b);
        }
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_JACEFRIO
