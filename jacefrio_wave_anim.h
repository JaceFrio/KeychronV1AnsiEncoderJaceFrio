#ifdef ENABLE_RGB_MATRIX_JACEFRIO_WAVE
RGB_MATRIX_EFFECT(JACEFRIO_WAVE)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static HSV JACEFRIO_WAVE_math(HSV hsv, int16_t dx, int16_t dy, uint8_t time) {
    hsv.h = (2 * dx + dy + 5) + (2 * dy + dx + 5) + time;
    return hsv;
}

bool JACEFRIO_WAVE(effect_params_t* params) {
    return effect_runner_dx_dy(params, &JACEFRIO_WAVE_math);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_JACEFRIO_WAVE
