#ifdef ENABLE_RGB_MATRIX_KITT
RGB_MATRIX_EFFECT(KITT)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// variable for startup animation
bool BASE_EFFECT_NOT_STARTED_YET = true;
uint8_t base_effect_startup_counter = 255;

uint8_t led_count = 14;
uint8_t led_first = 45;
uint8_t led_count_two = 15;
uint8_t led_second = 30;


static uint8_t time_to_led(uint8_t time, uint8_t led_behind) {
    uint16_t led_time = led_count * time;
    uint16_t step = ((2 * led_count + (led_time / 128)) - led_behind) % (2 * led_count);
    uint8_t led;

    if (step < led_count) {
        led = step;
    } else {
        led = led_count - 1 - (step - led_count);
    }

    return led;
}

static uint8_t time_to_led2(uint8_t time, uint8_t led_behind) {
    uint16_t led_time2 = led_count_two * time;
    uint16_t step = ((2 * led_count_two + (led_time2 / 128)) - led_behind) % (2 * led_count_two);
    uint8_t led;

    if (step < led_count_two) {
        led = step;
    } else {
        led = led_count_two - 1 - (step - led_count_two);
    }

    return led;
}

static HSV KITT_math(HSV hsv, uint8_t i, uint8_t time) {

    // reset base effect startup
    if (i == 0) {
        BASE_EFFECT_NOT_STARTED_YET = true;
    }

    hsv.h = rgb_matrix_config.hsv.h;
    hsv.s = 255;

    if (i >= led_first && i < led_first + led_count) {
        uint8_t j = i - led_first;
        if (j == time_to_led(time, 0)) {
            hsv.v = hsv.v;
        } else if (j == time_to_led(time, 1)) {
            hsv.v = hsv.v/2;
        } else if (j == time_to_led(time, 2)) {
            hsv.v = hsv.v/4;
        } else if (j == time_to_led(time, 3)) {
            hsv.v = hsv.v/8;
        } else {
            hsv.v = 0;
        }
    } 
      else if (i >= led_second && i < led_second + led_count_two) {
      uint8_t k = i - led_second;
      if (k == time_to_led2(time, 0)) {
          hsv.v = hsv.v;
      } else if (k == time_to_led2(time, 1)) {
          hsv.v = hsv.v/2;
      } else if (k == time_to_led2(time, 2)) {
          hsv.v = hsv.v/4;
      } else if (k == time_to_led2(time, 3)) {
          hsv.v = hsv.v/8;
      } else {
          hsv.v = 0;
      }
      }
    else {
        hsv.v = 0;
    }




    return hsv;
}

bool KITT(effect_params_t* params) { return effect_runner_i(params, &KITT_math); }

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_KITT
