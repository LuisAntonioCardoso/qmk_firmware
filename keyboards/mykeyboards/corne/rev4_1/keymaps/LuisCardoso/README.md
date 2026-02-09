# Corne v4.1 - LuisCardoso Keymap Documentation

## Overview

This is a custom keymap for the **Corne v4.1 split keyboard** with per-key RGB LED support and advanced layer management. The keymap features 10 layers with specialized modes for typing, gaming, coding, shortcuts, menu access, and brightness control.

**Hardware:**
- Processor: RP2040
- Layout: `LAYOUT_split_3x6_3_ex2` (46 keys: 3x6 + 3 thumbs + 2 inner extra keys per side)
- RGB LEDs: 46 addressable per-key LEDs with HSV color model + global brightness control
- Split communication: Serial on GPIO 12
- LED driver: WS2812B (vendor driver via GPIO 10)

**New in v2.2:**
- Shift+tap inner thumb keys (LTR/RTL) toggles Caps Lock
- Red LED indicator on all 6 thumbs when Caps Lock is active
- Colour-coded SWITCHER layer: green (layer toggles), orange (boot), red (reboot)
- Fixed right ESC matrix detection (CONFIG layer now works)
- Fixed EEPROM brightness floor (prevents LEDs staying off)

---

## Table of Contents

1. [Layer Architecture](#layer-architecture)
2. [LED Mapping & Indices](#led-mapping--indices)
3. [Custom Keycodes](#custom-keycodes)
4. [Thumb Key System](#thumb-key-system)
5. [RGB Features](#rgb-features)
6. [Configuration & Build](#configuration--build)
7. [Debugging Guide](#debugging-guide)

---

## Layer Architecture

There are 10 layers organized in a specific hierarchy. Layers 0-2 are base layers (MAIN, QWRT, GAME); layers 3-6 are temporary overlays (NUM, SMB, ARW, COD); layers 7-9 are special (SWX, CNF, SHR).

### Layer Definition
**File:** `keymap.c` line 16

```c
enum layers { MAI, QRT, GAM, NUM, SMB, ARW, COD, SWX, CNF };
```

### Base Layers (0-2)
These are the main layers. Only one is active at a time. Switching between them happens via the SWITCHER layer.

#### **Layer 0: MAIN (MAI)**
**File:** `keymap.c` lines 219-228

Custom Colemak variant optimized for typing. Designed for users migrating from Colemak.

```
Left side:
Row 0: BspDel | NO | Q | O | U | B | BOOT
Row 1: TAB | C/SYM | S/SFT | E/ALT | A/CTL | I | NO
Row 2: ESC | COMM | Z | X | Y | J | (thumb row below)

Right side:
Row 0: BOOT | K | G | L | W | NO | SCLN
Row 1: NO | D | T/CTL | R/ALT | N/SFT | H/CODE | BspDel
Row 2: | F | M | V | P | DOT | ESC | (thumb row below)
```

**Key Features:**
- All keys support **mod-tap** (hold for modifier, tap for key) except vowels and thumb keys
- Pinky columns: Tab/ESC for spacing
- SYMB layer access: Hold C (left row 1, col 0)
- CODE layer access: Hold H (right row 1, col 5)

**Thumb Keys:** LTL, LTM, LTR, RTL, RTM, RTR (see [Thumb Key System](#thumb-key-system))

#### **Layer 1: QWERTY (QRT)**
**File:** `keymap.c` lines 240-249

Standard QWERTY layout for compatibility. Same structure as MAIN but with standard letter positions.

```
Row 0: BspDel | Q | W | E | R | T | ... | Y | U | I | O | P | SCLN
Row 1: TAB | A/SYM | S/SFT | D/ALT | F/CTL | G | ... | H | J/CTL | K/ALT | L/SFT | ;/CODE | BspDel
Row 2: ESC | Z | X | C | V | B | ... | N | M | , | . | ' | ESC
```

**Thumb Keys:** KC_TRNS (transparent, inherits from MAIN)

**Note:** Right thumb keys inherit from MAIN layer, so they function the same way across layers.

#### **Layer 2: GAME (GAM)**
**File:** `keymap.c` lines 261-270

Gaming layout with all letters accessible from the left side for easier reach during games.

```
Left side:
Row 0: BspDel | A | B | C | D | E | BOOT
Row 1: TAB | F | G | H | I | J | NO
Row 2: K | L | M | N | O | P | (thumb row)

Right side: (Standard layout)
Row 0: BOOT | Y | U | I | O | P | SCLN
Row 1: NO | H | J/CTL | K/ALT | L/SFT | ;/CODE | BspDel
Row 2: | N | M | , | . | ' | ESC
```

**Use Case:** When gaming, you can access all alphabet keys from the left hand, freeing up the right hand for mouse movement.

**Thumb Keys:** LTL, LTM, LTR, RTL, RTM, RTR (same as MAIN)

---

### Temporary Layers (3-6)
These layers are activated temporarily by holding keys, and automatically deactivate when released (except NUMB which can be locked).

#### **Layer 3: NUMB (NUM)**
**File:** `keymap.c` lines 273-284

Number pad and operators layer for quick access to numbers and math operations.

```
Row 0: TRNS | 1 | 2 | 3 | 4 | 5 | NO | ... | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS
Row 1: TRNS | 6 | 7/SFT | 8/ALT | 9/CTL | 0 | NO | ... | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS
Row 2: TRNS | / | * | - | + | = | | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS
Thumb:   NUMB_TOGGLE | TRNS | TRNS | TRNS | TRNS | TRNS
```

**Activation:**
- Hold **LTM (left thumb middle)** to temporarily activate
- Tap **NUMB_TOGGLE** (left thumb) to lock/unlock NUMB layer

**Status:** ⚠️ **BACKLOG** - NUMB lock key not defined yet. Currently can be toggled but interface needs refinement.

**LED Pattern (when locked):** Numbers white, +/- cyan, */÷ magenta (LEDs defined but needs review)

#### **Layer 4: SYMB (SMB)**
**File:** `keymap.c` lines 297-305

Symbol and punctuation layer accessed by holding the C key (or via layer-tap).

```
Row 0: TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | ... | - | ] | \| | $ | ¥ | TRNS
Row 1: TRNS | TRNS | SFT | ALT | CTL | TRNS | ... | - | ' | ^ | # | @ | TRNS
Row 2: TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | ... | " | ` | % | & | ; | TRNS
```

**Activation:** Hold **C** (left row 1, col 0 via LT(SMB, KC_C))

**LED Indicator:** Left pinky column (LEDs 1, 8, 15) lights white

#### **Layer 5: AROW (ARW)**
**File:** `keymap.c` lines 313-322

Arrow keys and navigation layer for cursor movement and page navigation.

```
Row 0: TRNS | TRNS | \| | \ | ` | ] | ... | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS
Row 1: TRNS | TRNS | SFT | ALT | CTL | TRNS | ... | TRNS | CTL+LEFT | ALT+UP | SFT+DOWN | RIGHT | TRNS
Row 2: TRNS | TRNS | TRNS | ! | /| | & | ... | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS
```

**Activation:** Hold **RTL (right thumb left)** to temporarily activate

**Note:** Right thumb left key (RTL) is now used for ARW layer. It still participates in 3-thumb SWITCHER detection.

#### **Layer 6: CODE (COD)**
**File:** `keymap.c` lines 331-340

Brackets, braces, and programming syntax layer accessed by holding H.

```
Row 0: TRNS | TRNS | ] | [ | < | > | ... | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS
Row 1: TRNS | = | } | { | ) | ( | ... | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS
Row 2: TRNS | ; | TRNS | \ | / | TRNS | ... | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS
```

**Activation:** Hold **H** (right row 1, col 5 via LT(COD, KC_H))

**LED Indicator:** Right pinky column (LEDs 28, 35, 42) lights white

---

### Special Layers (7-8)

#### **Layer 7: SWITCHER (SWX)**
**File:** `keymap.c` lines 178-182

Menu layer for switching between base layers and accessing boot mode.

**Activation:** Hold **all 3 left OR all 3 right thumb keys for 500ms**

```
Row 0: NO | NO | SW_QWRT | NO | NO | QK_BOOT | NO | NO | NO | SW_GAME | NO | NO | NO | NO
Row 1: NO | CAPS | NO | NO | NO | NO | NO | NO | NO | NO | NO | NO | NO | NO
Row 2: NO | NO | NO | NO | NO | NO | NO | SW_MAIN | NO | NO | NO | NO
Thumb: TRNS | TRNS | TRNS | TRNS | TRNS | TRNS
```

**Key Mappings by Position:**
- **Q (left row 0, col 2, LED 2):** Switch to QWERTY → `SW_QWRT`
- **G (right row 0, col 1, LED 25):** Switch to GAME → `SW_GAME`
- **M (right row 2, col 1, LED 38):** Switch to MAIN → `SW_MAIN`
- **C (left row 1, col 1, LED 8):** Toggle CAPS LOCK
- **B (left row 0, col 5, LED 5):** Enter bootloader → `QK_BOOT`
- **R (right row 1, col 4, LED 33):** Reboot keyboard → `QK_BOOT` (added to exit SWX via reboot)
- **Inner keys (left row 0 col 6, right row 0 col 0, LEDs 6 & 23):** Enter bootloader

**LED Pattern:** All LEDs off except active keys which light white

**Behavior:**
- When you hold all 3 thumbs on one side for 500ms, the SWITCHER layer activates
- GUI and Space keys are suppressed during the hold to prevent accidental keypresses
- NUMB, SYMB, AROW, CODE layers are turned off
- Release any thumb key to exit SWITCHER (unless you press a key to switch layers)
- Layer switch keys immediately activate their target layer and exit SWITCHER

#### **Layer 8: CONFIG (CNF)**
**File:** `keymap.c` lines 184-189

Real-time LED brightness adjustment layer for global brightness control across all layers.

**Activation:** Hold **both ESC keys (left row 2 col 0 & right row 2 col 11) for 500ms**

```
Layout uses finger columns (same as mod indicators):

Row 0 (BRI_UP):   Index | BRI_UP keys highlighted
Row 1 (BRI_UP):   Index | BRI_UP keys highlighted
Row 2 (BRI_DN):   Index | BRI_DN keys highlighted

Left side columns:       Pinky | Ring  | Mid  | Index
Right side columns:      Index | Mid   | Ring | Pinky

Exit keys (red):  Outer columns (left row 0, right row 0)
```

**Key Functions:**
- **Brightness Up (index col, rows 0-1):** BRI_UP - Increase global LED brightness by BRIGHTNESS_STEP (25)
- **Brightness Down (index col, row 2):** BRI_DN - Decrease global LED brightness by BRIGHTNESS_STEP (25)
- **Exit (outer col, row 0):** CFG_EXIT - Exit CONFIG layer, returns to previous layer

**LED Pattern:**
- Background: Current base layer color (MAI=Blue, QRT=Green, GAM=Red)
- White highlights: BRI_UP/BRI_DN keys in index columns
- Red highlights: Exit keys (outer columns)

**Persistence:** Global brightness automatically saves to EEPROM after each adjustment

**Scope:** Global brightness applies to all LEDs across all layers uniformly

**Note:** Base layer colors are fixed at boot (LAYER_HSV_MAI, LAYER_HSV_QRT, LAYER_HSV_GAM). Global brightness modulates the V (Value) component of all LEDs.

---

## LED Mapping & Indices

Understanding the LED index mapping is crucial for debugging RGB features. The Corne v4.1 uses sequential indexing across the keyboard.

### Physical Layout

```
Left side:           Right side:
0   1   2   3   4   5   6        23  24  25  26  27  28  29
7   8   9  10  11  12  13        30  31  32  33  34  35  36
14 15  16  17  18  19             37  38  39  40  41  42
20 21  22                          43  44  45
```

**Row 0 (top):** 7 keys per side (6 main + 1 inner extra) = LEDs 0-6 (left), 23-29 (right)
**Row 1 (middle):** 7 keys per side (6 main + 1 inner extra) = LEDs 7-13 (left), 30-36 (right)
**Row 2 (bottom):** 6 keys per side (no inner extra) = LEDs 14-19 (left), 37-42 (right)
**Thumbs:** 3 keys per side = LEDs 20-22 (left), 43-45 (right)

### LED Index by Key Name

**Left Side:**
```
Row 0:  BspDel(0) | NO(1) | Q(2) | O(3) | U(4) | B(5) | BOOT(6)
Row 1:  TAB(7) | C(8) | S(9) | E(10) | A(11) | I(12) | NO(13)
Row 2:  ESC(14) | COMM(15) | Z(16) | X(17) | Y(18) | J(19)
Thumbs: LTL(20) | LTM(21) | LTR(22)
```

**Right Side:**
```
Row 0:  BOOT(23) | K(24) | G(25) | L(26) | W(27) | NO(28) | SCLN(29)
Row 1:  NO(30) | D(31) | T(32) | R(33) | N(34) | H(35) | BspDel(36)
Row 2:  F(37) | M(38) | V(39) | P(40) | DOT(41) | ESC(42)
Thumbs: RTL(43) | RTM(44) | RTR(45)
```

### Finger Column Indices

Used for modifier indicators and CONFIG layer adjustments:

```
Pinky (col 0/6):   Left: 0,7,14 | Right: 29,36,42
Ring (col 2/4):    Left: 2,9,16 | Right: 27,34,41
Middle (col 3/3):  Left: 3,10,17 | Right: 26,33,40
Index (col 4/2):   Left: 4,11,18 | Right: 25,32,39
```

### LED Index Calculation Function

**File:** `keymap.c` lines 303-337

```c
uint8_t get_led_index(uint8_t row, uint8_t col)
```

This function maps keyboard matrix positions (row, col) to LED indices. It handles:
- Rows 0-1 (14 columns each: 7 left + 7 right)
- Row 2 (12 columns: 6 left + 6 right)
- Row 3 (6 columns: 3 left + 3 right, thumbs)

Used by the heatmap animation to track which keys are pressed.

---

## Custom Keycodes

Custom keycodes allow complex key behaviors not available in standard QMK.

**File:** `keymap.c` lines 19-39

### Definition

```c
enum custom_keycodes {
    CKC_QU = SAFE_RANGE,
    CKC_BSD,     // Smart Backspace/Delete
    NUMB_T,      // NUMB toggle
    SW_MAIN, SW_QWRT, SW_GAME,  // Layer switches
    LTL, LTM, LTR,               // Left thumb keys
    RTL, RTM, RTR,               // Right thumb keys
    BRI_UP, BRI_DN,              // Brightness control
    CFG_EXIT                     // Exit CONFIG layer
};
```

### Custom Keycode Handlers

**File:** `keymap.c` lines 392-625+ (in `process_record_user`)

#### **CKC_QU: Smart Q-U combo**
**Lines:** 307-322

```c
case CKC_QU:
    if (mod_state & MOD_MASK_CS) {  // Ctrl+Shift held?
        del_mods(MOD_MASK_CS);
        register_code(KC_Q);        // Send Q only
        ...
    } else {
        tap_code(KC_Q);
        tap_code(KC_U);             // Send Q then U
    }
```

**Behavior:**
- Normal tap: `QU` (useful in Colemak where Q-U appears frequently)
- Ctrl+Shift held: `Q` only (to bypass the combo)

**Use Case:** Faster typing of the "qu" digraph in Colemak

#### **CKC_BSD: Context-aware backspace/delete**
**Lines:** 433-453

```c
case CKC_BSD:
    if (mod_state & MOD_MASK_SHIFT) {
        register_code(KC_DEL);      // Shift+tap = Delete
    } else {
        register_code(KC_BSPC);     // Normal = Backspace
    }
```

**Behavior:**
- Tap alone: Backspace (delete left)
- Shift+tap: Delete (delete right)

**Use Case:** Single key for both backspace and delete without mode switching

#### **NUMB_T: Lock/unlock number layer**
**Lines:** 455-468

```c
case NUMB_T:
    if (!numb_locked) {
        numb_locked = true;
        layer_on(NUM);
    } else {
        numb_locked = false;
        layer_off(NUM);
        layer_move(previous_layer);
    }
```

**Behavior:**
- Press: Toggle NUMB layer on/off
- When locked: NUMB layer stays active until toggled again
- When unlocked: Returns to the previous base layer

**Status:** ⚠️ Currently toggles via left thumb key, but lock key interface needs redesign

#### **SW_MAIN, SW_QWRT, SW_GAME: Layer switching**
**Lines:** 471-496

```c
case SW_MAIN:
    current_base_layer = MAI;
    numb_locked = false;           // Reset NUMB lock
    layer_off(SWX);
    layer_move(MAI);
```

**Behavior:**
- Immediately switch to target base layer
- Exit SWITCHER layer
- Disable NUMB lock (to avoid confusion when switching layouts)
- Update `current_base_layer` (used for LED color/heatmap)

#### **LTL, LTM, LTR, RTL, RTM, RTR: Thumb keys with SWITCHER detection + Caps Lock**
**Lines:** 390-446

These keys implement complex logic:

1. **Track press/release state** for each thumb key
2. **Detect 3-thumb hold** (500ms) to activate SWITCHER
3. **Suppress actions** when SWITCHER might activate
4. **Defer key actions** to release time
5. **(NEW) Shift+tap on LTR/RTL toggles Caps Lock**

**Key Details:**

| Key | Primary Function | Hold Behavior | Shift+Tap | SWITCHER Role |
|-----|------------------|---------------|-----------|---------------|
| **LTL** | GUI tap | (none) | (none) | Detect 3-thumb hold (left) |
| **LTM** | Enter tap / NUMB hold | Activate NUMB layer | (none) | Detect 3-thumb hold (left) |
| **LTR** | SHR layer hold | SHR on (unless Shift held) | **Toggle Caps Lock** | Detect 3-thumb hold (left) |
| **RTL** | Caps Lock toggle | (none) | **Toggle Caps Lock** | Detect 3-thumb hold (right) |
| **RTM** | Space tap / ARW hold | Activate ARW layer | (none) | Detect 3-thumb hold (right) |
| **RTR** | (none) | (none) | (none) | Detect 3-thumb hold (right) |

**Caps Lock Toggle Mechanism:**
- Hold Shift + tap LTR (left inner thumb) → toggles Caps Lock
- Hold Shift + tap RTL (right inner thumb) → toggles Caps Lock
- When Shift is held, LTR does NOT activate SHR layer (reserved for caps toggle)
- Uses `get_mods()` to read current modifier state, not stale `mod_state` variable
- Detection window: `TAPPING_TERM_MS` (200ms) — tap must be quick

**Action Suppression Logic:**

When all 3 thumbs on one side are pressed:
- LTL: GUI tap deferred to release
- LTM: NUMB layer suppressed
- RTL: AROW layer suppressed
- RTM: Space suppressed

If SWITCHER activates during the hold (500ms), none of these actions trigger.

**Example: LTM behavior (lines 413-435)**

```c
case LTM:
    if (record->event.pressed) {
        ltm_pressed = true;
        ltm_tap_timer = timer_read();
        if (ltl_pressed && ltr_pressed && left_thumb_timer == 0) {
            left_thumb_timer = timer_read();  // Start SWITCHER detection
        }
        // Only activate NUMB if NOT all 3 thumbs pressed
        if (!switcher_activated && !(ltl_pressed && ltr_pressed)) {
            layer_on(_NUMB);
        }
    } else {
        ltm_pressed = false;
        left_thumb_timer = 0;
        if (!switcher_activated && !numb_locked) {
            layer_off(_NUMB);
            // Check for tap (quick press/release)
            if (timer_elapsed(ltm_tap_timer) < TAPPING_TERM_MS) {
                tap_code(KC_ENT);  // Send Enter on quick tap
            }
        }
    }
```

#### **CFG_LED_TOG, CFG_BRI_UP/DN, CFG_HUE_UP/DN, CFG_SAT_UP/DN: LED adjustment**
**Lines:** 496-567

```c
case CFG_LED_TOG:
    if (record->event.pressed) {
        uint8_t idx = get_layer_settings_idx(current_base_layer);
        layer_led_settings[idx].enabled = !layer_led_settings[idx].enabled;
        save_led_settings();
    }
```

**Behavior:**
- Get current base layer index (0=MAIN, 1=QWRT, 2=GAME)
- Adjust HSV settings (hue, saturation, value/brightness)
- Save to EEPROM for persistence

**Parameters:**
- `HUE_STEP = 8` (steps of 8 in 0-255 range)
- `SAT_STEP = 16` (steps of 16 in 0-255 range)
- `VAL_STEP = 8` (steps of 8 in 0-255 range for brightness)

#### **ESC key handling for CONFIG access**
**Lines:** 576-620

```c
case KC_ESC:
    {
        uint8_t row = record->event.key.row;
        uint8_t col = record->event.key.col;
        bool is_left_esc = (row == 2 && col == 0);
        bool is_right_esc = (row == 2 && col == 11);
        
        if (is_left_esc || is_right_esc) {
            if (record->event.pressed) {
                left_esc_pressed = true;  // (or right_esc_pressed)
                if (left_esc_pressed && right_esc_pressed && config_hold_timer == 0) {
                    config_hold_timer = timer_read();
                }
            } else {
                left_esc_pressed = false;
                if (!config_activated) {
                    tap_code(KC_ESC);  // Send ESC if CONFIG didn't activate
                }
                config_hold_timer = 0;
            }
            return false;
        }
    }
    return true;
```

**Behavior:**
- Intercepts both outer ESC keys (bottom row)
- Tracks dual-press to detect 500ms hold
- If CONFIG activates, ESC keypress is suppressed
- If not held long enough, sends normal ESC on release

**ESC Key Positions:**
- Left: Row 2, Col 0 → LED 14
- Right: Row 2, Col 11 → LED 42

---

## Thumb Key System

The thumb keys are the most complex part of the keymap because they:
1. Serve multiple functions (modifier, layer activation, etc.)
2. Participate in SWITCHER detection (3-thumb hold)
3. Suppress their normal actions when SWITCHER might activate

### Thumb Key State Tracking

**File:** `keymap.c` lines 45-58

```c
// Left side thumb tracking
static bool ltl_pressed = false;
static bool ltm_pressed = false;
static bool ltr_pressed = false;
static uint16_t left_thumb_timer = 0;
static uint16_t ltm_tap_timer = 0;

// Right side thumb tracking
static bool rtl_pressed = false;
static bool rtm_pressed = false;
static bool rtr_pressed = false;
static uint16_t right_thumb_timer = 0;

static bool switcher_activated = false;
```

### SWITCHER Activation Logic

**File:** `keymap.c` lines 627-707+ (in `matrix_scan_user`)

```c
void matrix_scan_user(void) {
    // Check LEFT side: all 3 thumbs held and timer running
    if (ltl_pressed && ltm_pressed && ltr_pressed && left_thumb_timer > 0) {
        if (timer_elapsed(left_thumb_timer) >= SWITCHER_HOLD_TIME) {
            if (!switcher_activated) {
                switcher_activated = true;
                // Turn off any temporary layers
                layer_off(NUM);
                layer_off(SMB);
                layer_off(ARW);
                layer_off(COD);
                // Unregister any held keys
                unregister_code(KC_LGUI);
                unregister_code(KC_SPC);
                // Activate SWITCHER
                layer_on(SWX);
                left_thumb_timer = 0;
            }
        }
    }
    
    // [Same logic for RIGHT side]
    
    // Reset switcher_activated when SWITCHER layer is no longer active
    if (switcher_activated && !layer_state_is(SWX)) {
        switcher_activated = false;
    }
}
```

### Configuration

**File:** `config.h` line 19

```c
#define TAPPING_TERM 275  // Time in ms for tap vs hold detection
```

This affects:
- LTM: Determines if release is a tap (Enter) or hold (NUMB)
- RTL: Determines if release is no-op or AROW activation

**File:** `keymap.c` line 42

```c
#define SWITCHER_HOLD_TIME 500  // ms to hold all 3 thumbs
```

Time to hold all 3 thumbs before SWITCHER activates.

---

## RGB Features

The keyboard has sophisticated RGB LED support with per-key HSV color control and global brightness adjustment.

### LED System Design

**File:** `keymap.c` lines 225-240

The LED system uses HSV color space (Hue, Saturation, Value) with:
- Fixed base layer colors (defined at compile time)
- Global brightness multiplier (adjustable via CONFIG layer, persisted to EEPROM)
- NO animations (RGB_MATRIX_NONE mode for pure indicator control)

```c
// Base layer HSV palette (indexed by MAI / QRT / GAM)
static const HSV BASE_LAYER_HSV[3] = {
    LAYER_HSV_MAI,  // {152, 210, 217} — Blue
    LAYER_HSV_QRT,  // {85, 193, 139} — Green
    LAYER_HSV_GAM   // {0, 193, 139} — Red
};

// Global brightness multiplier (0-255, default 200)
static uint8_t global_brightness = DEFAULT_BRIGHTNESS;
```

**Color Values (config.h lines 56-58):**
- **MAIN (MAI):** HSV(152, 210, 217) — Blue
- **QWERTY (QRT):** HSV(85, 193, 139) — Green
- **GAME (GAM):** HSV(0, 193, 139) — Red

These are fixed per base layer. Global brightness adjustment in CONFIG layer modulates the Value (brightness) component uniformly across all LEDs.

### How LED Colors Work

1. **Color Selection:** Based on current base layer (MAI/QRT/GAM)
2. **Brightness Scaling:** `HSV.value = (BASE_HSV.value * global_brightness) / 255`
3. **HSV→RGB Conversion:** Done in `get_base_layer_color()` function
4. **Applied to:** All 46 per-key LEDs, plus overlay indicators (modifiers, layer states)

### Base Layer LED Colors

**File:** `keymap.c` lines 635-641

All keys on base layers (MAIN, QRT, GAME) light with the corresponding base layer color, scaled by global brightness.

**Implementation (lines 635-641):**

```c
// --- All other layers: solid base-layer colour ---
RGB color = get_base_layer_color(layer);
rgb_matrix_set_color_all(color.r, color.g, color.b);
```

**Color Calculation (lines 235-240):**

```c
RGB get_base_layer_color(uint8_t layer) {
    uint8_t base_idx = (layer < 3) ? layer : current_base_layer;
    HSV     hsv      = BASE_LAYER_HSV[base_idx];
    hsv.v            = (uint16_t)hsv.v * global_brightness / 255;
    return hsv_to_rgb(hsv);
}
```

This function:
1. Maps the current layer to a base layer index (0=MAI, 1=QRT, 2=GAM)
2. Gets the HSV color for that base layer
3. **Multiplies the Value (brightness) by global_brightness / 255**
4. Converts HSV to RGB and returns for per-key LED setting

**Result:** All base layer keys show a solid color that brightens/dims based on CONFIG layer adjustments.

### Modifier Column Indicators

**File:** `keymap.c` lines 643-671

When modifier keys (CTRL, SHIFT, ALT) are held or one-shot, their corresponding finger columns light with LED_MOD_BRIGHTNESS (100).

**CTRL (Index finger column):**
- Left: LEDs 4, 11, 18 (U, A, Y)
- Right: LEDs 25, 32, 39 (G, T, V)

**SHIFT (Ring finger column):**
- Left: LEDs 2, 9, 16 (Q, S, Z)
- Right: LEDs 27, 34, 41 (W, N, P)

**ALT (Middle finger column):**
- Left: LEDs 3, 10, 17 (O, E, X)
- Right: LEDs 26, 33, 40 (L, R, P)

```c
if (mods & MOD_MASK_CTRL) {
    rgb_matrix_set_color(4, mod_brightness, mod_brightness, mod_brightness);
    rgb_matrix_set_color(11, mod_brightness, mod_brightness, mod_brightness);
    // ... rest of index column
}
```

### Layer Activation Indicators

**File:** `keymap.c` lines 698-708

**SYMB layer (left pinky column):** LEDs 17, 16, 15 light white when SMB layer is active
**CODE layer (right pinky column):** LEDs 40, 39, 38 light white when COD layer is active

These indicator columns stay lit as long as their layer is active, providing visual feedback about which temporary layer is engaged.

### Caps Lock LED Indicator

**File:** `keymap.c` lines 710-718

**All 6 thumb LEDs go red when Caps Lock is active:**
- Left: LTL (LED 8), LTM (LED 7), LTR (LED 0)
- Right: RTL (LED 23), RTM (LED 30), RTR (LED 31)

This provides immediate visual feedback for Caps Lock status. The red overlay applies on top of all other LED coloring, so it's always visible regardless of which layer is active.

### SWITCHER Layer LED Pattern

**File:** `keymap.c` lines 597-612

Shows which keys are available for switching with colour-coded feedback:

```
Green (0, LED_BRIGHTNESS, 0) – Layer toggles:
- Q: LED 12 (QWERTY)
- G: LED 27 (GAME)
- M: LED 29 (MAIN)

Orange (LED_BRIGHTNESS, LED_BRIGHTNESS/2, 0) – Bootloader:
- B: LED 3 (BOOT)

Red (LED_BRIGHTNESS, 0, 0) – Reboot:
- R: LED 33 (REBOOT - emergency keyboard reset)
```

All other LEDs are black (off). This makes it instantly clear which keys do what:
- **Green** = switch base layer
- **Orange** = enter bootloader (for firmware updates)
- **Red** = reboot firmware

**Implementation:**
```c
rgb_matrix_set_color_all(0, 0, 0);  // All off
rgb_matrix_set_color(12, 0, LED_BRIGHTNESS, 0); // Q – QWERTY (green)
rgb_matrix_set_color(3, LED_BRIGHTNESS, LED_BRIGHTNESS/2, 0); // B – BOOT (orange)
rgb_matrix_set_color(33, LED_BRIGHTNESS, 0, 0); // R – REBOOT (red)
```

**Note:** KC_CAPS was removed from SWX layer. Use Shift+LTR or Shift+RTL to toggle Caps Lock instead (more ergonomic).

### CONFIG Layer LED Pattern

**File:** `keymap.c` lines 590-607

Background: Target layer color (current_base_layer)

Highlighted columns (white, LED_BRIGHTNESS):
- **Index (brightness up/down):** LEDs 4,5,6,27,28,29

Exit keys (red, LED_BRIGHTNESS):
- **Outer columns (exit):** LEDs 18, 41

**Implementation:**
```c
RGB color = get_base_layer_color(current_base_layer);
rgb_matrix_set_color_all(color.r, color.g, color.b);  // Background

// Brightness adjustment keys (white)
rgb_matrix_set_color(4, LED_BRIGHTNESS, LED_BRIGHTNESS, LED_BRIGHTNESS);
// ... more brightness keys

// Exit keys (red)
rgb_matrix_set_color(18, LED_BRIGHTNESS, 0, 0);
rgb_matrix_set_color(41, LED_BRIGHTNESS, 0, 0);
```

Users press the white highlighted index column keys to increase/decrease brightness. Red outer keys exit CONFIG layer.

### RGB Matrix Indicator Update

**File:** `keymap.c` lines 573-687 (in `rgb_matrix_indicators_user`)

This function is called every frame to update all 46 LED colors based on:
1. Current active layer
2. Current base layer (for color selection)
3. Global brightness (for brightness scaling)
4. Pressed modifiers (for column highlighting)
5. Active layer-tap keys (for pinky column indicators)

**Key Decision Flow:**
```
1. If SWITCHER layer (SWX) → Black background, white spotlight on active keys (Q, G, M, C, B, R)
2. Else if CONFIG layer (CNF) → Base layer color background, white highlight on brightness keys, red on exit keys
3. Else if NUMB locked (NUM) → Black background with white digits, yellow operators, orange multipliers, green lock key
4. Else → Solid base layer color (scaled by global brightness)
5. Then overlay: modifier columns (white) when mods held + layer indicators (white) when SMB/COD active
6. Return false → we fully own the LED output, no other effects run
```

**Note:** RGB_MATRIX_NONE mode is used, so no animation effects run. All LED coloring is done purely through this indicator callback.

### EEPROM Persistence

**File:** `keymap.c` lines 246-281

Global brightness is automatically saved to EEPROM after each CONFIG layer adjustment.

```c
void save_brightness(void) {
    uint8_t data[1] = {global_brightness};
    eeconfig_update_user_datablock(data);
}

static void load_brightness(void) {
    uint8_t data[1];
    eeconfig_read_user_datablock(data);
    if (data[0] != 0xFF) {  // Check for uninitialized EEPROM
        global_brightness = data[0];
    }
}

void eeconfig_init_user(void) {
    save_brightness();
}
```

**EEPROM Structure:**
- 1 byte total (config.h line 29: `EECONFIG_USER_DATA_SIZE = 1`)
- Offset 0: `global_brightness` (0-255)

**Called at:**
- Keyboard boot: `keyboard_post_init_user()` (line 268) - loads from EEPROM
- First time: `eeconfig_init_user()` (line 259) - initializes with DEFAULT_BRIGHTNESS (200)
- On BRI_UP/BRI_DN: `save_brightness()` called immediately (lines 456, 463)

---

## Configuration & Build

### Files

| File | Purpose |
|------|---------|
| `keymap.c` | Main keymap with all layers and logic |
| `config.h` | Configuration parameters and QMK settings |
| `rules.mk` | Feature enables/disables |

### Build Command

```bash
cd /home/razu/qmk_firmware
qmk compile -kb mykeyboards/corne/rev4_1 -km LuisCardoso
```

Output: `mykeyboards_corne_rev4_1_LuisCardoso.uf2`

### Configuration Parameters

**File:** `config.h` (lines 1-66)

**Split Keyboard Sync:**
```c
#define SPLIT_LAYER_STATE_ENABLE  // Sync layer state to slave
#define SPLIT_MODS_ENABLE         // Sync modifier state to slave
#define SPLIT_TRANSPORT_MIRROR    // Mirror master state to slave
```

**RGB Matrix (no animations):**
```c
#define RGB_MATRIX_KEYPRESSES  // React to keypresses
#define RGB_MATRIX_SLEEP       // Turn off when host sleeps
```

**Tap-Hold Tuning:**
```c
#define TAPPING_TERM 275       // ms for tap vs hold
#define PERMISSIVE_HOLD        // Allow hold to activate even during typing
```

**Timing (Custom):**
```c
#define SWITCHER_HOLD_TIME 500   // ms: all 3 thumbs held to enter SWITCHER
#define CONFIG_HOLD_TIME 500     // ms: both ESCs held to enter CONFIG
#define TAPPING_TERM_MS 200      // ms: tap vs hold cutoff for thumb keys
```

**LED Configuration:**
```c
#define LED_BRIGHTNESS 50        // Fixed brightness for indicators (0-255)
#define LED_MOD_BRIGHTNESS 100   // Modifier column indicator brightness
#define BRIGHTNESS_STEP 25       // Step size per BRI_UP / BRI_DN press
#define DEFAULT_BRIGHTNESS 200   // Global brightness on first boot (0-255)
```

**EEPROM:**
```c
#define EECONFIG_USER_DATA_SIZE 1  // 1 byte: global_brightness
```

**Key setting:** `TAPPING_TERM 275` - Controls how quickly you need to release a key for it to be a "tap" vs. "hold". Affects mod-tap behavior (LCTL_T, LSFT_T, etc.).

### Feature Enables

**File:** `rules.mk`

```makefile
RGB_MATRIX_ENABLE = yes
LTO_ENABLE = yes
```

---

## Debugging Guide

### Common Issues and Solutions

#### **Issue: SWITCHER layer doesn't activate**

**Symptoms:** Holding all 3 thumbs for 500ms doesn't enter SWITCHER

**Debugging Steps:**

1. **Check thumb key states:** Add debug output to `process_record_user`
   ```c
   if (record->event.pressed) {
       uprintf("LTL: %d, LTM: %d, LTR: %d\n", ltl_pressed, ltm_pressed, ltr_pressed);
   }
   ```

2. **Verify 500ms timing:** In `matrix_scan_user`, check if `timer_elapsed()` is reaching SWITCHER_HOLD_TIME
   ```c
   uprintf("Left elapsed: %d\n", timer_elapsed(left_thumb_timer));
   ```

3. **Check layer state:** Ensure layer doesn't disable before timer finishes
   ```c
   uprintf("Layer state: 0x%X\n", layer_state);
   ```

4. **Verify custom keycodes work:** Test pressing individual thumb keys in isolation

**Common Causes:**
- Thumb keys not registering press/release events
- Matrix scanning not fast enough to detect simultaneous presses
- One thumb key physically not working

#### **Issue: LEDs show wrong colors or don't light up**

**Symptoms:** Heatmap not working, modifier indicators don't light, or random LEDs light

**Debugging Steps:**

1. **Verify LED indices:** Use `get_led_index()` function to check mapping
   ```c
   uint8_t led = get_led_index(2, 0);  // Should return 14 for ESC
   uprintf("LED index for (2,0): %d\n", led);
   ```

2. **Check HSV to RGB conversion:** Test with known colors
   ```c
   HSV test = {.h = 0, .s = 255, .v = 255};
   RGB rgb = hsv_to_rgb(test);
   uprintf("Red: R=%d G=%d B=%d\n", rgb.r, rgb.g, rgb.b);
   ```

3. **Test heatmap directly:** Press keys and watch `key_heat[]` array
   ```c
   uprintf("Heat[0]: %d\n", key_heat[0]);
   ```

4. **Verify layer settings loaded:** Check if EEPROM load is working
   ```c
   uprintf("MAIN hue: %d sat: %d val: %d\n", 
           layer_led_settings[0].hue,
           layer_led_settings[0].sat,
           layer_led_settings[0].val);
   ```

**Common Causes:**
- LED indices calculated incorrectly (verify with keyboard layout)
- EEPROM not initialized (check `eeconfig_init_user` called)
- HSV values out of range
- RGB matrix not enabled in `rules.mk`

#### **Issue: Heatmap animation not showing**

**Symptoms:** Base layers (MAIN, QWRT, GAME) show flat color instead of heatmap

**Debugging Steps:**

1. **Verify heatmap called:** Check `render_heatmap()` is being called
   ```c
   uprintf("render_heatmap called\n");
   ```

2. **Check heat values updating:** Press keys and watch `key_heat[led_idx]`
   ```c
   if (record->event.pressed) {
       uint8_t led = get_led_index(record->event.key.row, record->event.key.col);
       uprintf("Key pressed, heat[%d]: %d\n", led, key_heat[led]);
   }
   ```

3. **Verify decay happening:** Let keyboard sit and check if heat decreases
   ```c
   // In matrix_scan after decay
   uprintf("Key heat after decay: %d\n", key_heat[0]);
   ```

**Common Causes:**
- `get_led_index()` returning invalid indices
- Heat values capped at HEATMAP_MAX before decay can show
- Decay interval too long (HEATMAP_DECAY_INTERVAL = 50ms)

#### **Issue: Mod-tap keys not working correctly**

**Symptoms:** LCTL_T(KC_A) sends Control instead of A, or vice versa

**Debugging Steps:**

1. **Check TAPPING_TERM:** Currently 275ms. Try different values
   ```c
   #define TAPPING_TERM 300  // Try 50ms increments
   ```

2. **Test with simple key:** Replace problematic key with basic key to isolate
   ```c
   KC_A  // Instead of LCTL_T(KC_A)
   ```

3. **Check for PERMISSIVE_HOLD interaction:** Disable if causing issues
   ```c
   // #define PERMISSIVE_HOLD
   ```

**Common Causes:**
- TAPPING_TERM too short for your typing speed
- PERMISSIVE_HOLD causing unexpected behavior
- Macro or layer change triggering during tap detection

#### **Issue: CONFIG layer doesn't activate**

**Symptoms:** Holding both ESC keys doesn't open CONFIG

**Debugging Steps:**

1. **Verify ESC key positions:** Check if ESCs are at (2,0) and (2,11)
   ```c
   uprintf("ESC at (2,0)? %s\n", (row == 2 && col == 0) ? "yes" : "no");
   ```

2. **Check dual-press detection:**
   ```c
   uprintf("Left ESC: %d, Right ESC: %d, Timer: %d\n",
           left_esc_pressed, right_esc_pressed, timer_elapsed(config_hold_timer));
   ```

3. **Verify CONFIG layer exists:**
   ```c
   uprintf("Layer state before: 0x%X\n", layer_state);
   layer_on(_CONFIG);
   uprintf("Layer state after: 0x%X\n", layer_state);
   ```

**Common Causes:**
- ESC keys not physically working
- Timing calculation wrong (check `CONFIG_HOLD_TIME = 500`)
- CONFIG layer definition missing

#### **Issue: NUMB layer toggling unexpectedly**

**Symptoms:** NUMB layer locks/unlocks when you don't want it to

**Debugging Steps:**

1. **Verify NUMB_TOGGLE key:** Check that only intended key activates it
   ```c
   uprintf("NUMB_TOGGLE pressed, numb_locked: %d\n", numb_locked);
   ```

2. **Check layer state preservation:**
   ```c
   uprintf("Previous layer before lock: 0x%X\n", previous_layer);
   uprintf("Previous layer after unlock: 0x%X\n", previous_layer);
   ```

3. **Verify lock persistence:** Ensure `numb_locked` isn't being reset elsewhere

**Status:** ⚠️ Known issue: NUMB lock key not properly defined. Lock logic works but interface needs redesign.

### Performance Debugging

**Enable QMK debug output:**

```bash
qmk console
```

Then:
```bash
qmk set debug.enable=true
qmk set debug.matrix=true
qmk set debug.keyboard=true
```

Add debug output in code:
```c
#include "debug.h"
uprintf("Debug message: %d\n", value);
```

---

## Recent Changes (v2.2)

1. ✅ **Caps Lock Toggle** — Shift+LTR or Shift+RTL to toggle Caps Lock
   - Ergonomic access on inner thumb keys
   - Suppresses SHR layer when Shift is held to avoid conflicts
   
2. ✅ **Caps Lock LED Indicator** — All 6 thumbs go red when active
   - Always visible overlay on top of other LEDs
   
3. ✅ **SWITCHER Colour Coding** — Green/Orange/Red for layer/boot/reboot
   - Instantly visible which key does what
   - KC_CAPS removed (use Shift+thumb instead)
   
4. ✅ **CONFIG Layer Bug Fix** — Right ESC matrix check corrected
   - Was checking `row == 2 && col == 11` (never matched)
   - Now correctly checks `row == 6 && col == 0`
   - CONFIG layer fully functional
   
5. ✅ **EEPROM Brightness Floor** — Prevents LEDs staying off
   - Validates loaded brightness >= BRIGHTNESS_STEP (25)
   - Falls back to DEFAULT_BRIGHTNESS if corrupted

## Future Improvements (Backlog)

1. **NUMB Layer Lock UI Refinement**
   - Current toggle works well, but could add visual lock state indicator
   
2. **Oneshot Modifier Enhancements**
   - Add visual feedback for oneshot state
   - Extend to layer keys

---

## Contributing

When modifying this keymap:

1. **Update LED indices:** Keep the mapping comment at top of keymap.c in sync
2. **Test all layers:** Verify each layer's keys and LEDs
3. **Document changes:** Add comments explaining complex logic
4. **Rebuild and test:** `qmk compile -kb mykeyboards/corne/rev4_1 -km LuisCardoso`

---

## References

- [QMK Docs](https://docs.qmk.fm/)
- [RGB Matrix Reference](https://docs.qmk.fm/features/rgb_matrix)
- [Custom Keycodes](https://docs.qmk.fm/features/custom_quantum_functions)
- [Mod-Tap](https://docs.qmk.fm/features/mod_tap)
- [Split Keyboard](https://docs.qmk.fm/features/split_keyboard)

---

**Last Updated:** 2026-01-31  
**Keymap Version:** 2.0  
**Hardware:** Corne v4.1 (RP2040)
