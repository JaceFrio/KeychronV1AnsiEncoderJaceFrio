#ifdef ENABLE_RGB_MATRIX_FIRE
RGB_MATRIX_EFFECT(FIRE)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

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

uint8_t * heat;
// fire effect controls
uint8_t cooling = 80;
// lower sparking -> more flicker 
// higher sparking -> more consistent flame
uint8_t sparking = 50;
uint8_t sparks = 3;
uint8_t spark_height = 4;

const uint8_t blend_self = 2;
const uint8_t blend_neighbor_one = 3;
const uint8_t blend_neighbor_two = 2;
const uint8_t blend_neighbor_three = 1;
const uint8_t blend_total = (blend_self + blend_neighbor_one + blend_neighbor_two + blend_neighbor_three);

typedef HSV (*fire_i_f)(uint8_t i, uint8_t time, uint8_t row_count, uint8_t row_start);

static HSV FIRE_math(uint8_t l, uint8_t time, uint8_t row_count, uint8_t row_start) {
  // TODO: Try using rand() instead of random8();
  // row_count = row_count - random16_max(row_count - 1);
  HSV hsv = rgb_matrix_config.hsv;

  for (uint8_t i = row_start; i >= row_start && i < row_start + row_count; i++) {
    heat[i] = fmax(0L, heat[i] - random16_min_max(0, ((cooling * 10) / row_count) + 2));
  }

  for (uint8_t i = row_start; i >= row_start && i < row_start + row_count; i++) {
    heat[i] = (heat[i] * blend_self + heat[(i + 1) % row_count] * blend_neighbor_one + heat[(i + 2) % row_count] * blend_neighbor_two + heat[(i + 3) % row_count] * blend_neighbor_three) / blend_total;
  }

  for (uint8_t k = 0; k < sparks; k++) {
    if (random16_max(255) < sparking) {
      uint8_t y = row_count - 1 - random16_max(spark_height);
      heat[y] = heat[y] + random16_min_max(160, 255);
    }
  }

  for (uint8_t i = row_start; i >= row_start && i < row_start + row_count; i++) {
    hsv.v += qsub8(time, heat[i]);
    // hsv.v = heat[i];
    RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }
  
  return hsv;
}

bool fire_effect_runner_i(effect_params_t* params, fire_i_f effect_func) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  
  bool run_once_one = false;
  bool run_once_two = false;
  bool run_once_three = false;
  bool run_once_four = false;
  bool run_once_five = false;
  bool run_once_six = false;

  uint8_t time = scale16by8(g_rgb_timer, qadd8(rgb_matrix_config.speed / 2, 1));
  for (uint8_t i = led_min; i < led_max; i++) {
    RGB_MATRIX_TEST_LED_FLAGS();
    // row 1
    if (i >= row_one_start && i < row_one_start + row_one_count) {
      if (!run_once_one) {
        random16_add_entropy(random16());
        effect_func(i, time, row_one_count, row_one_start);
        run_once_one = true;
      }
    }
    // row 2
    if (i >= row_two_start && i < row_two_start + row_two_count) {
      if (!run_once_two) {
        random16_add_entropy(random16());
        effect_func(i, time, row_two_count, row_two_start);
        run_once_two = true;
      }
    }
    // 3
    if (i >= row_three_start && i < row_three_start + row_three_count) {
      if (!run_once_three) {
        random16_add_entropy(random16());
        effect_func(i, time, row_three_count, row_three_start);
        run_once_three = true;
      }
    }
    // row 4
    if (i >= row_four_start && i < row_four_start + row_four_count) {
      if (!run_once_four) {
        random16_add_entropy(random16());
        effect_func(i, time, row_four_count, row_four_start);
        run_once_four = true;
      }
    }
    // row 5
    if (i >= row_five_start && i < row_five_start + row_five_count) {
      if (!run_once_five) {
        random16_add_entropy(random16());
        effect_func(i, time, row_five_count, row_five_start);
        run_once_five = true;
      }
    }
    // row 6
    if (i >= row_six_start && i < row_six_start + row_six_count) {
      if (!run_once_six) {
        random16_add_entropy(random16());
        effect_func(i, time, row_six_count, row_six_start);
        run_once_six = true;
      }
    }
  }
  
  run_once_one = false;
  run_once_two = false;
  run_once_three = false;
  run_once_four = false;
  run_once_five = false;
  run_once_six = false;

  return rgb_matrix_check_finished_leds(led_max);
}

bool FIRE(effect_params_t* params) {
  return fire_effect_runner_i(params, &FIRE_math); 
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_FIRE
