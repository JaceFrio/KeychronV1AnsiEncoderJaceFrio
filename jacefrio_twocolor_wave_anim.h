#ifdef ENABLE_RGB_MATRIX_JACEFRIO_TWOCOLOR_WAVE
RGB_MATRIX_EFFECT(JACEFRIO_TWOCOLOR_WAVE)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static HSV JACEFRIO_TWOCOLOR_WAVE_math(HSV hsv, int16_t dx, int16_t dy, uint8_t time) {
    hsv.h = (2 * dx + dy + 5) + (2 * dy + dx + 5) + time;
    if (hsv.h > 0 && hsv.h < 87) {
      hsv = rgb_matrix_config.hsv;
    }
    else if (hsv.h > 86 && hsv.h < 173) {
      hsv = rgb_matrix_config.hsv;
      hsv.h += rgb_matrix_config.speed + 10;
    }
    else {
      hsv = rgb_matrix_config.hsv;
    }
    return hsv;
}

bool JACEFRIO_TWOCOLOR_WAVE(effect_params_t* params) {
    return effect_runner_dx_dy(params, &JACEFRIO_TWOCOLOR_WAVE_math);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_JACEFRIO_TWOCOLOR_WAVE
