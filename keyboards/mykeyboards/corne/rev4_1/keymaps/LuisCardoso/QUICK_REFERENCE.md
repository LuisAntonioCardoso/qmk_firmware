# Quick Reference - LuisCardoso Corne v4.1 Keymap

## Files at a Glance

| File | Purpose | Size |
|------|---------|------|
| `README.md` | Comprehensive feature documentation | 32 KB |
| `ARCHITECTURE.md` | Design diagrams and system overview | 28 KB |
| `keymap.c` | Main implementation | 46 KB |
| `config.h` | Configuration parameters | 1.1 KB |
| `rules.mk` | QMK feature enables | 290 B |

---

## Layer Access Quick Reference

| Layer | Access Method | Purpose |
|-------|---------------|---------|
| **MAIN (0) - MAI** | Default base layer | Custom Colemak |
| **QWRT (1) - QRT** | Via SWITCHER (Q key) | QWERTY compatibility |
| **GAME (2) - GAM** | Via SWITCHER (G key) | Gaming mode |
| **NUMB (3) - NUM** | Hold LTM (left middle thumb) | Numbers + operators |
| **SYMB (4) - SMB** | Hold C key | Symbols & punctuation |
| **AROW (5) - ARW** | Hold RTL (right inner thumb) | Arrows & navigation |
| **CODE (6) - COD** | Hold H key | Brackets & syntax |
| **SWITCHER (7) - SWX** | Hold all 3 thumbs for 500ms | Base layer switcher |
| **CONFIG (8) - CNF** | Hold both ESC keys for 500ms | LED customization |

---

## Thumb Key Reference

### Left Thumb Cluster (3 keys)
```
Outer:  LTL (GUI tap, SWITCHER detection)
Middle: LTM (Enter tap / NUMB hold)
Inner:  LTR (SHR layer / Shift+tap → Caps Lock toggle)
```

### Right Thumb Cluster (3 keys)
```
Inner:  RTL (Shift+tap → Caps Lock toggle)
Middle: RTM (Space tap / ARW hold)
Outer:  RTR (SWITCHER detection)
```

**Caps Lock Toggle:**
- Hold Shift (either side) + tap LTR or RTL = toggle Caps Lock
- Quick tap required (< 200ms)
- Red LEDs on all 6 thumbs when Caps Lock active

---

## LED Index Cheat Sheet

### By Position
```
Row 0 (top):    0-6 (L), 23-29 (R)
Row 1 (middle): 7-13 (L), 30-36 (R)
Row 2 (bottom): 14-19 (L), 37-42 (R)
Thumbs:         20-22 (L), 43-45 (R)
```

### Important Keys
- Q (LED 2): SWITCHER access key
- ESC (LED 14 & 42): CONFIG access keys
- A (LED 11): CTRL indicator
- S (LED 9): SHIFT indicator
- E (LED 10): ALT indicator
- C (LED 8): SYMB indicator
- H (LED 35): CODE indicator

---

## Custom Keycode Reference

| Keycode | Behavior | File Line |
|---------|----------|-----------|
| `CKC_QU` | Type QU (or Q if Ctrl+Shift) | 415-430 |
| `CKC_BSD` | Backspace or Delete (if Shift) | 433-453 |
| `NUMB_T` | Lock/unlock NUMB layer | 455-468 |
| `SW_MAIN` | Switch to MAIN layer | 471-478 |
| `SW_QWRT` | Switch to QWERTY layer | 480-487 |
| `SW_GAME` | Switch to GAME layer | 489-496 |
| `LTL`, `LTM`, `LTR` | Left thumb keys | 498-560+ |
| `RTL`, `RTM`, `RTR` | Right thumb keys | 560+... |
| `BRI_UP` | Brightness increase | 560+... |
| `BRI_DN` | Brightness decrease | 560+... |
| `CFG_EXIT` | Exit CONFIG layer | 560+... |

---

## RGB LED Patterns

### Base Layers (MAIN, QWRT, GAME)
- **Cold keys** (unused): Dim base color
- **Hot keys** (frequently used): Bright + shifted white
- Updates every 50ms with decay

### SWITCHER Layer
- All off except: Q, G, M, C, B, R keys (white)
- Shows available switching options + emergency reboot on R

### CONFIG Layer
- Background: Current base layer color
- Highlight: Brightness adjustment columns (index, white)
- Exit keys: Outer columns (red)

### Modifier Indicators
- CTRL → Index columns (white)
- SHIFT → Ring columns (white)
- ALT → Middle columns (white)

### Layer Indicators
- SYMB active → Left pinky column (white)
- CODE active → Right pinky column (white)

---

## Common Modifications

### Change TAPPING_TERM
**File:** `config.h` line 19
```c
#define TAPPING_TERM 275  // ms for tap vs hold
```
- Lower = faster response, harder to hold
- Higher = more time to tap, easier to hold

### Change SWITCHER_HOLD_TIME
**File:** `keymap.c` line 42
```c
#define SWITCHER_HOLD_TIME 500  // ms to hold all 3 thumbs
```
- Lower = faster SWITCHER access
- Higher = less accidental triggers

### Change Global Brightness Default
**File:** `config.h` line 46
```c
#define DEFAULT_BRIGHTNESS 200  // Global brightness on first boot (0-255)
```
- Lower = dimmer on boot
- Higher = brighter on boot
- Can be adjusted per session via CONFIG layer (persists to EEPROM)

### Change LED Colors
**File:** `keymap.c` lines 99-103
```c
{170, 255, 50, true}  // MAIN: Blue (H=170)
{85,  255, 50, true}  // QWRT: Green (H=85)
{0,   255, 50, true}  // GAME: Red (H=0)
```
- Hue: 0-255 (color wheel)
- Sat: 0-255 (intensity)
- Val: 0-255 (brightness)

---

## Key Position Reference

### MAIN Layer Layout
```
L0:  BspDel NO   Q    O    U    B   BOOT | BOOT K    G    L    W   NO  SCLN
L1:  TAB    C/SY S/SF E/AL A/CT I   NO   | NO   D    T/CT R/AL N/SF H/CD BspDel
L2:  ESC    CM   Z    X    Y    J        | F    M    V    P    DOT  ESC
Th:  LTL    LTM  LTR                     | RTL  RTM  RTR
```

Where:
- `SY` = SYMB layer-tap
- `SF` = SHIFT mod-tap
- `AL` = ALT mod-tap
- `CT` = CTRL mod-tap
- `CD` = CODE layer-tap

---

## Troubleshooting Quick Links

| Issue | Solution | File |
|-------|----------|------|
| SWITCHER won't activate | Check thumb timers in matrix_scan_user | 527-567 |
| LEDs all off or wrong color | Check brightness loaded from EEPROM (min floor = BRIGHTNESS_STEP) | 254-260 |
| LEDs stuck off | Rewrite EEPROM or press BRI_UP in CONFIG layer to set minimum | config.h:45 |
| CONFIG layer won't activate | Right ESC must be at [6,0], left at [2,0] | 479-480 |
| Brightness not changing | Press BRI_UP/BRI_DN on CONFIG layer, verify EEPROM writes | 473-485 |
| Caps Lock toggle not working | Hold Shift + tap LTR (inner left) or RTL (inner right) quickly | 413-417, 433-441 |
| Caps Lock thumbs not red | Check `host_keyboard_led_state().caps_lock` in LED code | 710-718 |
| NUMB layer stuck | Check numb_locked variable and previous_layer tracking | 195-197 |

---

## Build & Flash

```bash
# Compile
cd /home/razu/qmk_firmware
qmk compile -kb mykeyboards/corne/rev4_1 -km LuisCardoso

# Output file
mykeyboards_corne_rev4_1_LuisCardoso.uf2

# Flash (bootloader mode)
1. Hold BOOT button on keyboard
2. Drag .uf2 file to USB drive (RPI-RP2)
3. Done!
```

---

## File Navigation

### To find a specific feature:

1. **Looking for LED code?**
   - `keymap.c` lines 820-1000 (rgb_matrix_indicators_user)

2. **Looking for layer definitions?**
   - `keymap.c` lines 123-254 (all keymaps)

3. **Looking for thumb key logic?**
   - `keymap.c` lines 390-494 (thumb key handlers)
   - `keymap.c` lines 627-672 (SWITCHER detection)

4. **Looking for CONFIG logic?**
   - `keymap.c` lines 496-567 (CONFIG keycodes)
   - `keymap.c` lines 1010-1057 (EEPROM persistence)

5. **Looking for LED settings?**
   - `keymap.c` lines 91-103 (default colors)
   - `keymap.c` lines 715-790 (render functions)

---

## Parameter Tuning Guide

### For Typing Comfort
- **Increase TAPPING_TERM** if mod-taps register as holds
- **Decrease TAPPING_TERM** if quick taps don't register

### For Gaming
- **Increase SWITCHER_HOLD_TIME** to avoid accidental triggers
- **Switch to GAME layer** via SWITCHER for better accessibility

### For LED Feedback
- **Adjust HEATMAP_DECAY** for faster/slower cooling
- **Adjust HEATMAP_INCREASE** for brighter/dimmer hot keys
- **Use CONFIG layer** to customize per-layer colors

---

## Version History

- **2.2** (2026-02-04): Caps Lock toggle (Shift+LTR/RTL), red thumb LED indicator, colour-coded SWITCHER, CONFIG layer bug fix (right ESC), EEPROM brightness floor validation, updated all documentation
- **2.1** (2026-02-04): Fixed RGB animation issue (RGB_MATRIX_NONE), fixed reboot on SWX layer, fixed keyboard init to always boot on MAI layer
- **2.0** (2026-01-31): Fixed LED mapping, AROW access, ESC positions, tapping term, CONFIG layer for brightness only
- **1.0** (2026-01-30): Initial implementation with all major features

---

**Quick Start:** Read README.md for features, ARCHITECTURE.md for design, this file for quick answers.
