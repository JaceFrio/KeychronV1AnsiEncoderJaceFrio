#ifdef ENABLE_RGB_MATRIX_JACEFRIO_FLOW
RGB_MATRIX_EFFECT(JACEFRIO_FLOW)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

typedef HSV (*flow_i_f)(uint8_t i, uint8_t time, uint8_t row_count, uint8_t row_start);

static HSV jacefrio_flow_math(uint8_t i, uint8_t time, uint8_t row_count, uint8_t row_start) {
  HSV hsv = rgb_matrix_config.hsv;

  hsv.v += time + 64;
  RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
  rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);

  if (i + 1 >= row_count) {
    i = row_start;
  }
  else {
    i += 1;
  }
  hsv.v += 64;
  rgb = rgb_matrix_hsv_to_rgb(hsv);
  rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);

  if (i + 2 >= row_count + 1) {
    i = row_start + 1;
  }
  else if (i + 1 >= row_count) {
    i = row_start;
  }
  else {
    i += 1;
  }
  hsv.v += 64;
  rgb = rgb_matrix_hsv_to_rgb(hsv);
  rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);

  if (i + 3 >= row_count + 2) {
    i = row_start + 2;
  }
  else if (i + 2 >= row_count + 1) {
    i = row_start + 1;
  }
  else if (i + 1 >= row_count) {
    i = row_start;
  }
  else {
    i += 1;
  }
  hsv.v += 64;
  rgb = rgb_matrix_hsv_to_rgb(hsv);
  rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);

  return hsv;
}

bool jacefrio_flow_effect_runner_i(effect_params_t* params, flow_i_f effect_func) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);

  // index of each row and number of keys in each row
  uint8_t row_one_start = 0;
  uint8_t row_one_count = 15;
  uint8_t row_two_start = 15;
  uint8_t row_two_count = 15;
  uint8_t row_three_start = 30;
  uint8_t row_three_count = 15;
  uint8_t row_four_start = 45;
  uint8_t row_four_count = 14;
  uint8_t row_five_start = 59;
  uint8_t row_five_count = 13;
  uint8_t row_six_start = 72;
  uint8_t row_six_count = 10;

  uint8_t time = scale16by8(g_rgb_timer, qadd8(rgb_matrix_config.speed / 2, 1));
  for (uint8_t i = led_min; i < led_max; i++) {
    RGB_MATRIX_TEST_LED_FLAGS();
    // row 1
    if (i >= row_one_start && i < row_one_start + row_one_count) {
        effect_func(i, time, row_one_count, row_one_start);
    }
    // row 2
    if (i >= row_two_start && i < row_two_start + row_two_count) {
        effect_func(i, time, row_two_count, row_two_start);
    }
    // 3
    if (i >= row_three_start && i < row_three_start + row_three_count) {
        effect_func(i, time, row_three_count, row_three_start);
    }
    // row 4
    if (i >= row_four_start && i < row_four_start + row_four_count) {
        effect_func(i, time, row_four_count, row_four_start);
    }
    // row 5
    if (i >= row_five_start && i < row_five_start + row_five_count) {
        effect_func(i, time, row_five_count, row_five_start);
    }
    // row 6
    if (i >= row_six_start && i < row_six_start + row_six_count) {
        effect_func(i, time, row_six_count, row_six_start);
    }
  }

  return rgb_matrix_check_finished_leds(led_max);
}

bool JACEFRIO_FLOW(effect_params_t* params) {
  return jacefrio_flow_effect_runner_i(params, &jacefrio_flow_math); 
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_JACEFRIO_FLOW
