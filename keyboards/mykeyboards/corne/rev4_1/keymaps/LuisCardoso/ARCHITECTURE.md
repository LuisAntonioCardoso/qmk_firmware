# Corne v4.1 - LuisCardoso Architecture & Design

This document explains the architectural design decisions and provides visual diagrams for understanding the system.

---

## System Architecture Overview

```
┌──────────────────────────────────────────────────────────────────┐
│                     KEYBOARD INPUT LAYER                         │
│  (Matrix scanning, debouncing, key press/release detection)      │
└───────────────────────────┬──────────────────────────────────────┘
                            │
┌───────────────────────────▼──────────────────────────────────────┐
│               CUSTOM KEYCODE PROCESSING                          │
│  (CKC_QU, CKC_BSD, custom thumb logic, brightness adjustment)   │
│                  [process_record_user]                           │
└───────────────────────────┬──────────────────────────────────────┘
                            │
        ┌───────────────────┼───────────────────┐
        │                   │                   │
        ▼                   ▼                   ▼
   ┌─────────┐        ┌─────────┐        ┌──────────────┐
   │ Tracking│        │ SWITCHER│        │ CONFIG Layer│
   │ Thumb   │        │ Detection        │ Detection    │
   │ States  │        │ (500ms hold)    │ (500ms hold) │
   └─────────┘        └─────────┘        └──────────────┘
        │                   │                   │
        └───────────────────┼───────────────────┘
                            │
                            ▼
        ┌───────────────────────────────────┐
        │   LAYER STATE MANAGEMENT          │
        │  [layer_state_set_user]           │
        │  Update current_base_layer,       │
        │  RGB colors, heatmap              │
        └───────────────────────────────────┘
                            │
        ┌───────────────────┼───────────────────┐
        │                   │                   │
        ▼                   ▼                   ▼
   ┌──────────────┐  ┌──────────────┐  ┌──────────────┐
   │ Heatmap      │  │ Mod Tracking │  │ Layer        │
   │ Tracking     │  │              │  │ Persistence  │
   │              │  │              │  │ (EEPROM)     │
   └──────────────┘  └──────────────┘  └──────────────┘
                            │
┌───────────────────────────▼──────────────────────────────────────┐
│               RGB MATRIX UPDATE                                  │
│        [rgb_matrix_indicators_user] - Called every frame         │
│  Calculate LED colors based on layer, modifiers, heatmap        │
└──────────────────────────────────────────────────────────────────┘
```

---

## Layer Hierarchy

```
                        ┌─────────────────────┐
                        │  SPECIAL LAYERS     │
                        └─────────────────────┘
                               │       │
                    ┌──────────┘       └──────────┐
                    ▼                             ▼
            ┌─────────────────┐          ┌─────────────────┐
            │  SWX (7)        │          │  CNF (8)        │
            │  Menu layer     │          │  LED tuning     │
            │  [500ms hold:   │          │  [500ms hold:   │
            │   all 3 thumbs] │          │   both ESCs]    │
            └─────────────────┘          └─────────────────┘
                    │                             │
                    └──────────────┬──────────────┘
                                   │
             ┌──────────────────────▼──────────────────────┐
             │       TEMPORARY LAYERS (3-6)                │
             │     Active while held or via layer-tap      │
             └───────────────────┬────────────────────────┘
                     ┌───────────┼───────────┬────────────┐
                     ▼           ▼           ▼            ▼
             ┌──────────┐ ┌──────────┐ ┌──────────┐ ┌──────────┐
             │NUM (3)   │ │SMB (4)   │ │ARW (5)   │ │COD (6)   │
             │ Numbers  │ │Symbols   │ │Arrows    │ │Brackets  │
             │ & ops    │ │ & punct  │ │ & nav    │ │& syntax  │
             └──────────┘ └──────────┘ └──────────┘ └──────────┘
                     │           │           │            │
                     └───────────┴───────────┴────────────┘
                                    │
             ┌──────────────────────▼──────────────────────┐
             │     BASE LAYERS (0-2)                       │
             │  Only one active at a time                  │
             │  Switching via SWX layer                    │
             └───────────────────┬────────────────────────┘
                     ┌───────────┼───────────┐
                     ▼           ▼           ▼
             ┌──────────┐ ┌──────────┐ ┌──────────┐
             │MAI (0)   │ │QRT (1)   │ │GAM (2)   │
             │Colemak   │ │QWERTY    │ │Gaming    │
             │variant   │ │compat    │ │layout    │
             └──────────┘ └──────────┘ └──────────┘
```

---

## State Machine: Thumb Key Behavior

When you press thumb keys, the system tracks which keys are pressed and decides what action to take:

```
                      START
                        │
    ┌─────────────────────────────────────┐
    │ Press any thumb key                 │
    └──────────────────┬──────────────────┘
                       │
        ┌──────────────▼──────────────────┐
        │ Set button_pressed = true       │
        │ Check if all 3 thumbs pressed   │
        └──────────────┬───────────────────┘
                       │
          ┌────────────┴────────────┐
          │                         │
    YES   ▼                    NO   ▼
   ┌─────────────────┐      ┌──────────────────┐
   │ Start 500ms     │      │ Perform normal   │
   │ hold timer      │      │ action:          │
   │ for SWITCHER    │      │ - LTL: GUI       │
   └────────┬────────┘      │ - LTM: NUMB      │
            │               │ - RTL: AROW      │
            │               │ - RTM: Space     │
            ▼               └────────┬─────────┘
    ┌─────────────────┐             │
    │ Wait for:       │             │
    │ A) 500ms pass   │             │
    │    OR           │             │
    │ B) Key release  │             │
    └────────┬────────┘             │
             │                      │
    ┌────────┴────────┐             │
    │                 │             │
    ▼ 500ms           ▼ Released   │
┌──────────────┐  ┌────────────┐   │
│ SWITCHER     │  │ Action sent│   │
│ activates!   │  │ normally   │   │
│              │  │ (too late) │   │
└──────────────┘  └────────────┘   │
         │                         │
         └────────────┬────────────┘
                      │
                      ▼
                   DONE
```

**Key Decision Points:**

1. **Did all 3 thumbs press before 500ms elapsed?**
   - NO → Send the normal action (GUI, Space, NUMB, AROW)
   - YES → Suppress action, activate SWITCHER instead

2. **Is SWITCHER currently active?**
   - YES → Don't send any key action
   - NO → Proceed to send the action

---

## LED Index Calculation

The keyboard matrix is laid out sequentially in the LED index space:

```
Matrix Layout (LAYOUT_split_3x6_3_ex2):

        0   1   2   3   4   5   6              7   8   9  10  11  12  13
Row 0:  ●───●───●───●───●───●───●              ●───●───●───●───●───●───●
        (6+1 keys per side, including 1 inner extra key per side)

        0   1   2   3   4   5   6              7   8   9  10  11  12  13
Row 1:  ●───●───●───●───●───●───●              ●───●───●───●───●───●───●
        (6+1 keys per side)

        0   1   2   3   4   5                  6   7   8   9  10  11
Row 2:  ●───●───●───●───●───●                  ●───●───●───●───●───●
        (6 keys per side, no inner extra)

        0   1   2                               3   4   5
Row 3:  ●───●───●                              ●───●───●
        (3 keys per side - THUMBS)
```

**LED Index Mapping Formula:**

```c
Row 0-1 (left side):  LED_index = row * 7 + col
Row 2 (left side):    LED_index = 14 + col
Row 3 (left side):    LED_index = 20 + col

Row 0-1 (right side): LED_index = 23 + (row * 7) + col
Row 2 (right side):   LED_index = 37 + col
Row 3 (right side):   LED_index = 43 + col
```

**Implementation:** See `get_led_index()` in keymap.c lines 303-337

---

## Base Layer LED Coloring

The keyboard displays a solid base layer color on all keys, scaled by global brightness:

```
┌────────────────────────────────────────────────────────────┐
│ USER PRESSES ANY KEY ON BASE LAYER                         │
│ Example: Press Q on MAIN layer                             │
└─────────────────┬──────────────────────────────────────────┘
                  │
┌─────────────────▼──────────────────────────────────────────┐
│ [rgb_matrix_indicators_user] called EVERY FRAME (60 FPS)   │
│ Get current_base_layer (MAIN = index 0)                   │
│ Fetch BASE_LAYER_HSV[0] → {152, 210, 217} (Blue)         │
│ Adjust value: V = (217 * global_brightness) / 255         │
│ Convert HSV→RGB via qmk API                               │
│ rgb_matrix_set_color_all(r, g, b) for all 46 LEDs        │
└─────────────────┬──────────────────────────────────────────┘
                  │
                  │ (User adjusts brightness via CONFIG layer)
┌─────────────────▼──────────────────────────────────────────┐
│ [BRI_UP / BRI_DN] handler                                  │
│ global_brightness += BRIGHTNESS_STEP (25)                  │
│ OR global_brightness -= BRIGHTNESS_STEP (25)               │
│ save_brightness() → EEPROM                                 │
│ Next frame: get_base_layer_color() recalculates with new V│
└─────────────────┬──────────────────────────────────────────┘
                  │
                  ▼
┌────────────────────────────────────────────────────────────┐
│ VISUAL RESULT                                              │
│ MAIN layer:  All LEDs blue, brightness adjusted            │
│ QWRT layer:  All LEDs green, brightness adjusted           │
│ GAME layer:  All LEDs red, brightness adjusted             │
│ PLUS: Modifier columns, layer indicators overlay on top    │
└────────────────────────────────────────────────────────────┘
```

**Brightness Adjustment Levels:**

```
255 ■■■ Maximum (full color saturation + brightness)
    ■■■
200 ■■■ DEFAULT_BRIGHTNESS (on first boot)
    ■■■
100 ■■■ Medium brightness
    ■■■
 50 ■■■ Dim
    ■░░
  1 ░░░ Nearly off
  0 ░░░ Off (minimum brightness = 0)
    ↑   Adjusted via CONFIG layer (BRI_UP/BRI_DN)
    └─ BRIGHTNESS_STEP = 25 per press
```

**Note:** No animations run. RGB_MATRIX_NONE mode means only the indicator callback controls LEDs.

---

## RGB Matrix Update Flowchart

This is called every frame (60 FPS) to update all 46 LED colors:

```
┌────────────────────────────────────────────────────────────┐
│ rgb_matrix_indicators_user() called every ~16ms            │
│ [keymap.c lines 573-687]                                   │
└────────────────┬──────────────────────────────────────────┘
                 │
         ┌───────▼───────┐
         │ Which layer?  │
         └───────┬───────┘
                 │
    ┌────────────┼────────────┬───────────────┐
    │            │            │               │
    ▼            ▼            ▼               ▼
   SWX           CNF        NUM_LOCKED    OTHERS
    (7)          (8)           (3)        (0-2,4-6)
     │            │            │               │
     ▼            ▼            ▼               ▼
 ┌─────────┐  ┌─────────┐  ┌─────────┐  ┌──────────────┐
 │All LEDs │  │Base     │  │Number   │  │Solid color   │
 │off      │  │layer    │  │pattern: │  │Get base layer│
 │then     │  │color    │  │- white  │  │color scaled  │
 │highlight   │bg +     │  │  digits │  │by global_    │
 │active   │  │white    │  │- yellow │  │brightness    │
 │keys:    │  │BRI_UP   │  │  +, -   │  │              │
 │Q,G,M,C  │  │keys,    │  │- orange │  │rgb_matrix_   │
 │,B,R     │  │red exit │  │  *, /   │  │set_color_all()
 │white    │  │         │  │- green  │  │              │
 │         │  │         │  │  lock   │  │              │
 └─────────┘  └─────────┘  └─────────┘  └──────────────┘
     │            │            │               │
     └────────────┼────────────┼───────────────┘
                  │            │
          ┌───────▼────────────▼──────────┐
          │ Overlay (all layers):         │
          │ Modifiers & Layer Indicators  │
          │                               │
          │ IF CTRL → index cols white    │
          │ IF SHIFT → ring cols white    │
          │ IF ALT → middle cols white    │
          │ IF SMB → left pinky white     │
          │ IF COD → right pinky white    │
         └───────┬──────────────────────┘
                 │
    ┌────────────▼───────────┐
    │ return false           │
    │ (we fully own LEDs)    │
    │                        │
    │ WS2812B driver sends   │
    │ RGB data to all 46     │
    │ addressable LEDs       │
    └────────────────────────┘
```

---

## Configuration Layer State Machine

The CONFIG layer allows real-time brightness adjustment with immediate visual feedback:

```
┌──────────────────────────────────────────────────────────┐
│ Hold both ESC keys (bottom row, outer columns)           │
│ Left ESC: (2,0) → LED 14                                │
│ Right ESC: (2,11) → LED 42                              │
└────────────┬─────────────────────────────────────────────┘
             │
     ┌───────▼────────┐
     │ Start 500ms    │
     │ hold timer     │
     └────────┬───────┘
              │
              ▼
     ┌────────────────┐
     │ Timer reaches  │
     │ 500ms?         │
     └────────┬───────┘
              │
       YES ───┴────── NO
       │              │
       ▼              ▼
  ┌──────────┐    ┌──────────┐
  │CONFIG    │    │Send ESC  │
  │layer on  │    │normally  │
  │(CNF)     │    │on release│
  └───┬──────┘    └──────────┘
      │
      ▼
 ┌──────────────────────────┐
 │ Display:                 │
 │ - Background: current    │
 │   base layer color       │
 │ - White: BRI_UP/BRI_DN   │
 │   index column keys      │
 │ - Red: exit keys         │
 └────────┬─────────────────┘
          │
  ┌───────▼──────────────┐
  │ Press adjustment key │
  │ in CONFIG layer:     │
  │ - Index cols:        │
  │   BRI_UP or BRI_DN   │
  └────────┬─────────────┘
           │
  ┌────────▼──────────────┐
  │ Adjust global_        │
  │ brightness           │
  │ (0-255)              │
  │ save_brightness()    │
  │ → EEPROM (1 byte)    │
  │ Next frame: LEDs     │
  │ updated via GET func │
  └────────┬──────────────┘
           │
   ┌───────▼──────────────┐
   │ Release ESC key      │
   │ (or press CFG_EXIT)  │
   │ Exit CONFIG layer    │
   │ Brightness persists  │
   │ across boots         │
   └──────────────────────┘
```

**EEPROM Structure:**

```
Offset  Value
------  -----
0       global_brightness (0-255)
        Used to scale HSV.V for all LEDs
```

Each brightness adjustment in CONFIG saves 1 byte to EEPROM immediately via `save_brightness()`.

---

## Modifier Tracking & Indicator Logic

When you hold modifier keys, their corresponding finger columns light up:

```
MODIFIER HELD
    │
    ├─ get_mods() | get_oneshot_mods()
    │
    ▼
PARSE MODIFIER STATE
    │
    ├─ MOD_MASK_CTRL  → Light INDEX columns
    ├─ MOD_MASK_SHIFT → Light RING columns
    └─ MOD_MASK_ALT   → Light MIDDLE columns

For each modifier:
    FOR each LED in corresponding column:
        rgb_matrix_set_color(led_index, mod_brightness, ...)
```

**Column Mapping:**

```
Left Hand Fingers        Right Hand Fingers
──────────────────────   ──────────────────────
Pinky  (Outer):  0,7,14  Pinky  (Outer):  29,36,42
Ring   (Ring ):  2,9,16  Ring   (Ring ):  27,34,41
Middle (Mid  ):  3,10,17 Middle (Mid  ):  26,33,40
Index  (Index):  4,11,18 Index  (Index):  25,32,39
```

---

## Key Interaction Timeline Example

Let's trace what happens when you press and hold Q (a mod-tap key with LSFT_T):

```
Timeline (ms)    Event                           Action
────────────     ──────────────────────────────  ──────────────────────
0                Press Q with left hand          - ltl_pressed=true
                                                 - left_thumb_timer=0 (no 3-tap)
                                                 - LSFT_T tracking starts
                                                 - Key press registered

0-200            Held (no release)               - Waiting for 200ms tap window

200              TAPPING_TERM reached            - Not yet released
                 (TAPPING_TERM=275ms now)       - Treat as HOLD
                                                 - Activate SHIFT modifier

200-500          Still held                      - SHIFT indicator lights ring column
                 Continue holding Q              - Normal Q character repeats

500              Release Q                       - ltl_pressed=false
                 Q key released                  - left_thumb_timer=0
                                                 - LSFT modifier released
                                                 - SHIFT indicator goes off
```

**Alternative: Quick tap (< 275ms):**

```
Timeline (ms)    Event                           Action
────────────     ──────────────────────────────  ──────────────────────
0                Press Q                         - tracking starts

150              Release Q (quick)               - Under TAPPING_TERM
                                                 - Treat as TAP
                                                 - Send just 'q' character
                                                 - Don't activate SHIFT
```

---

## Build & Compilation Process

```
$ qmk compile -kb mykeyboards/corne/rev4_1 -km LuisCardoso

  1. QMK reads keyboard definition
     └─ info.json (layout, matrix)

  2. QMK reads keymap files
     ├─ config.h   (parameters)
     ├─ rules.mk   (features)
     └─ keymap.c   (layers & logic)

  3. Compilation
     ├─ Compile QMK core
     ├─ Compile platform code (ChibiOS for RP2040)
     ├─ Compile RGB matrix driver
     ├─ Link with keymap code
     └─ Optimize (LTO enabled)

  4. Output
     └─ mykeyboards_corne_rev4_1_LuisCardoso.uf2
        (Ready to flash via USB bootloader)
```

---

## Performance Considerations

**Frame Rate:**
- RGB matrix updates: ~60 FPS (every 16ms)
- Heatmap decay: Every 50ms
- Matrix scan: ~125 scans/sec
- Total latency: < 20ms typical

**Memory Usage:**
- Keymap struct: ~4 KB
- Heatmap array (46 bytes): Very small
- LED settings (12 bytes): Minimal
- State tracking: ~50 bytes
- **Total: ~5 KB** (plenty of room on RP2040)

**CPU Usage:**
- Per-key processing: ~100μs
- LED update: Offloaded to driver (async)
- Heatmap calculation: ~1ms every 50ms
- Mod-tap logic: ~50μs per frame

---

## Debugging Techniques

### Visual LED Feedback Technique

Use LEDs as debugging output:

```c
// Show current base layer
// Off = problem, specific color = state
if (current_base_layer == MAI) {
    rgb_matrix_set_color_all(0, 0, 255);      // Blue = MAI
} else if (current_base_layer == QRT) {
    rgb_matrix_set_color_all(0, 255, 0);      // Green = QRT
} else {
    rgb_matrix_set_color_all(255, 0, 0);      // Red = problem!
}
```

### Console Debug Output

Enable console and send debug strings:

```c
uprintf("Key press: layer=%d, heatmap[%d]=%d\n", 
        get_highest_layer(layer_state), 
        led_idx, 
        key_heat[led_idx]);
```

Then access via:
```bash
qmk console
```

---

## Caps Lock Toggle Logic (v2.2)

When Shift is held and LTR or RTL is tapped quickly (< 200ms):

```
1. User presses Shift (modifier is held)
2. User presses LTR/RTL (cap press detected)
   - ltr_pressed = true
   - ltr_tap_timer = timer_read()
   - Check: is Shift held? YES → don't activate SHR layer
   
3. User releases LTR/RTL (on release)
   - ltr_pressed = false
   - Check: was this a quick tap (< TAPPING_TERM_MS)? YES
   - Check: is Shift STILL held (get_mods() check)? YES
   - Action: tap_code(KC_CAPS) to toggle Caps Lock
   
4. User releases Shift (modifier released)
   - SHR layer stays off (it was suppressed during Shift hold)
```

**Key Implementation Detail:**
- Uses `get_mods()` on release, NOT stale `mod_state` from press time
- This ensures accurate modifier detection even if modifiers change during hold

## Fixed Bugs (v2.2)

1. **CONFIG Layer Right ESC** — Was checking `row == 2 && col == 11` (never matched right ESC at [6,0])
   - Fixed to: `row == 6 && col == 0`
   - CONFIG layer now fully functional

2. **EEPROM Brightness Floor** — Prevented loading corrupted or 0 values that left LEDs off
   - Now validates: `data[0] != 0xFF && data[0] >= BRIGHTNESS_STEP`
   - Fallback: uses DEFAULT_BRIGHTNESS if validation fails

## Future Architecture Improvements

1. **Debounce Tuning**
   - Currently using default QMK debounce
   - Could add adaptive debounce based on key

2. **State Persistence**
   - Save heatmap state between boots
   - Persistent layer history

3. **Multi-Profile Support**
   - Switch between full keyboard profiles
   - Save/load entire state (layers, LEDs, macros)

---

**Architecture Version:** 2.0  
**Last Updated:** 2026-01-31
