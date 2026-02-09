/* Config for Corne v4.1 - LuisCardoso */

#pragma once

// =============================================================================
// QMK CORE — Split sync, RGB, disabled features
// =============================================================================

// Split keyboard sync
#define SPLIT_LAYER_STATE_ENABLE                    // Sync layer state to slave
#define SPLIT_MODS_ENABLE                           // Sync modifier state to slave
#define SPLIT_TRANSPORT_MIRROR                      // Mirror master state to slave
#define SPLIT_LED_STATE_ENABLE                      // Sync LED lock indicators
#define SPLIT_TRANSACTION_IDS_USER USER_SYNC_CONFIG // Custom sync for HSV configs

// RGB Matrix
#define RGB_MATRIX_KEYPRESSES // React to keypresses
#define RGB_MATRIX_SLEEP      // Turn off when host sleeps

// Disabled features (saves flash)
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

// EEPROM — stores per-layer configs (3 layers x 4 bytes + 1 flags byte)
#define EECONFIG_USER_DATA_SIZE 13

// =============================================================================
// TAP-HOLD TIMING — All tap vs hold detection windows
// =============================================================================
//
// Homerow mods (LCTL_T, LSFT_T, LT(), etc.) use QMK's TAPPING_TERM.
// Thumb keys (LTM, RTM, etc.) use custom THUMB_* timing in process_record_user.
//
//   TAPPING_TERM      → QMK built-in: homerow mod tap/hold cutoff
//   THUMB_TAP_TERM    → Custom: thumb key tap/hold cutoff
//   THUMB_REPEAT_TERM → Custom: double-tap-hold window for key repeat
//
// NOTE: PERMISSIVE_HOLD removed - caused accidental holds when typing fast

#define TAPPING_TERM 150      // Homerow mods: tap if released within this (ms)
#define THUMB_TAP_TERM 150    // Thumb keys: tap if released within this (ms)
#define THUMB_REPEAT_TERM 150 // Thumb keys: double-tap-hold triggers key repeat

// =============================================================================
// SPECIAL HOLD COMBOS — Multi-key hold detection
// =============================================================================

#define SWITCHER_HOLD_TIME 400 // 3-thumb hold to enter SWITCHER layer
#define CONFIG_HOLD_TIME 400   // Dual-ESC hold to enter CONFIG layer

// =============================================================================
// LED INDICATORS — Brightness and warm white color
// =============================================================================

#define LED_BRIGHTNESS 200     // Indicator brightness (0-255)
#define LED_MOD_BRIGHTNESS 200 // Modifier column brightness

// Warm white (slight orange tint) - scaled RGB values
#define WARM_MOD_R LED_MOD_BRIGHTNESS
#define WARM_MOD_G ((LED_MOD_BRIGHTNESS * 200) / 255)
#define WARM_MOD_B ((LED_MOD_BRIGHTNESS * 150) / 255)

#define WARM_LED_R LED_BRIGHTNESS
#define WARM_LED_G ((LED_BRIGHTNESS * 200) / 255)
#define WARM_LED_B ((LED_BRIGHTNESS * 150) / 255)

// =============================================================================
// HSV CONTROLS — CNF layer adjustment step size
// =============================================================================

#define HSV_STEP 10 // Per-keypress step (~25 levels per value)
#define HSV_MIN 0
#define HSV_MAX 255

// =============================================================================
// DEFAULT LAYER COLORS — HSV per base layer (first boot / EEPROM reset)
// =============================================================================

#define DEFAULT_HUE_MAI 105
#define DEFAULT_SAT_MAI 215
#define DEFAULT_VAL_MAI 37

#define DEFAULT_HUE_QRT 155
#define DEFAULT_SAT_QRT 255
#define DEFAULT_VAL_QRT 69

#define DEFAULT_HUE_GAM 0
#define DEFAULT_SAT_GAM 215
#define DEFAULT_VAL_GAM 59

// =============================================================================
// NUMPAD COLORS — Operator key tints (scaled G value, R=full, B=0)
// =============================================================================

#define NUMPAD_YELLOW_G 200 // + and - keys
#define NUMPAD_ORANGE_G 100 // * and / keys
