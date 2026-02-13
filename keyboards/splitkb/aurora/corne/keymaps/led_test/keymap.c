// LED Test Firmware - Press any key to cycle through LEDs
// Note which physical key lights up for each LED index

#include QMK_KEYBOARD_H

// Track current LED being tested
static uint8_t current_led = 0;
static uint8_t max_leds    = 54; // Adjust if needed

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {[0] = LAYOUT_split_3x6_3(KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_SPC, KC_ENT, KC_BSPC, KC_TAB, KC_ESC, KC_DEL)};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        // Any key press advances to next LED
        current_led++;
        if (current_led >= max_leds) {
            current_led = 0;
        }
    }
    return true;
}

bool rgb_matrix_indicators_user(void) {
    // Turn all LEDs off
    rgb_matrix_set_color_all(0, 0, 0);

    // Light up only the current test LED in bright white
    rgb_matrix_set_color(current_led, 255, 255, 255);

    return false;
}

void keyboard_post_init_user(void) {
    // Start with LED 0
    current_led = 0;
    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv(0, 0, 255);
}
