# LuisCardoso Corne v4.1 Documentation Index

## 📚 Documentation Suite

This folder contains comprehensive documentation for the LuisCardoso custom Corne v4.1 keyboard keymap. Total documentation: **~2100 lines** covering all aspects of the implementation.

**Current Status:** Updated for v2.2 with Caps Lock toggle, colour-coded SWITCHER, CONFIG layer fix, EEPROM brightness floor validation.

### Quick Navigation

**Start here based on your goal:**

| Goal | Document | Size | Content |
|------|----------|------|---------|
| 🎯 I want quick answers | **QUICK_REFERENCE.md** | 7 KB | Cheat sheets, quick links, troubleshooting |
| 📖 I want to understand everything | **README.md** | 32 KB | Complete feature documentation |
| 🏗️ I want to understand design | **ARCHITECTURE.md** | 28 KB | System design, diagrams, flowcharts |
| 💻 I want to modify code | **keymap.c** | 46 KB | Main implementation with comments |

---

## 📄 Document Descriptions

### QUICK_REFERENCE.md (7 KB, 260 lines)
**Best for:** Finding specific information quickly

**Covers:**
- File overview table
- Layer access quick reference
- Thumb key reference
- LED index cheat sheet
- Custom keycode quick reference
- RGB LED pattern guide
- Common modifications guide
- Build & flash instructions
- Parameter tuning tips
- Troubleshooting quick links

**Use this when:** You know what you're looking for and just need the line number or quick explanation.

---

### README.md (33 KB, 1170 lines)
**Best for:** Comprehensive understanding of all features

**Covers:**

1. **Overview** - Hardware specs, file listing
2. **Layer Architecture** - All 10 layers with detailed descriptions
   - Base layers (MAIN, QWRT, GAME)
   - Temporary layers (NUMB, SYMB, AROW, CODE, SHR)
   - Special layers (SWITCHER, CONFIG)
   - Layer hierarchy and interactions

3. **LED Mapping & Indices** - Complete physical layout
   - LED index table (46 total)
   - LED index by key name
   - Finger column indices
   - LED calculation function

4. **Custom Keycodes** - All custom codes with implementation details
   - CKC_QU, CKC_BSD
   - NUMB_TOGGLE
   - SW_MAIN/QWRT/GAME
   - Thumb keys (LTL, LTM, LTR, RTL, RTM, RTR)
   - Brightness adjustment keys (BRI_UP, BRI_DN, CFG_EXIT)

5. **Thumb Key System** - Complex thumb behavior
   - State tracking variables
   - SWITCHER activation logic (500ms hold, 3-thumb detection)
   - Configuration parameters

6. **RGB Features** - LED functionality (NO ANIMATIONS)
   - Base layer HSV colors (fixed per layer)
   - Global brightness multiplier (adjustable, EEPROM-persisted)
   - Modifier column indicators
   - Layer indicators (pinky columns)
   - SWITCHER LED pattern (spotlight keys)
   - CONFIG LED pattern (brightness control)
   - EEPROM brightness persistence

7. **Configuration & Build** - Setup and compilation
   - File descriptions
   - Build command
   - Configuration parameters
   - Feature enables (RGB_MATRIX_NONE for pure indicator control)

8. **Debugging Guide** - Common issues and solutions
   - SWITCHER won't activate
   - LEDs off or wrong color
   - Brightness not changing
   - Modifiers not working
   - CONFIG can't access
   - NUMB layer stuck

9. **Future Improvements** - Backlog items
10. **References** - QMK documentation links

**Use this when:** You want detailed information about a specific feature and how it works.

---

### ARCHITECTURE.md (28 KB, 589 lines)
**Best for:** Understanding system design and implementation strategy

**Covers:**

1. **System Architecture Overview** - Complete data flow diagram
2. **Layer Hierarchy** - Visual layer structure
3. **State Machine: Thumb Key Behavior** - Timeline-based FSM
4. **LED Index Calculation** - Matrix to LED mapping formula
5. **Heatmap Animation System** - Heat tracking lifecycle
6. **RGB Matrix Update Flowchart** - Frame-by-frame LED update process
7. **Configuration Layer State Machine** - CONFIG layer workflow
8. **Modifier Tracking & Indicator Logic** - Mod processing pipeline
9. **Key Interaction Timeline** - Detailed trace of key press lifecycle
10. **Build & Compilation Process** - QMK compilation steps
11. **Performance Considerations** - Frame rate, memory, CPU usage
12. **Debugging Techniques** - Visual LED feedback, console output
13. **Future Architecture Improvements** - Proposed enhancements

**Use this when:** You want to understand how the system works, trace data flow, or design new features.

---

### keymap.c (46 KB, implementation file)
**Best for:** Implementation details and code reference

**Key sections (with line references):**

| Section | Lines | Purpose |
|---------|-------|---------|
| Layer definitions | 17 | Enum for all 10 layers |
| Custom keycodes | 19-39 | All custom code definitions |
| State tracking | 195-227 | Global state variables |
| Keymap arrays | 92-189 | All 10 layer definitions |
| get_led_index() | 83-86 | Matrix position to LED index |
| get_base_layer_color() | 235-240 | HSV→RGB conversion with brightness |
| process_record_user() | 289-446 | Custom keycode handlers (incl. Caps Lock) |
| matrix_scan_user() | 548-588 | Timer checks, SWITCHER/CONFIG detection |
| rgb_matrix_indicators_user() | 594-720 | Main LED update logic + Caps Lock indicator |
| LED patterns | 597-718 | All LED indicator patterns: SWITCHER (colour), CONFIG, NUMB, modifiers, layers, Caps |
| EEPROM functions | 246-260 | Save/load global brightness with floor validation |
| keyboard_post_init_user() | 267-281 | Init RGB_MATRIX_NONE, boot on MAI |

**Use this when:** You need to modify code or understand specific implementation details.

---

### config.h (1.1 KB, configuration)
**Key settings:**
- SPLIT keyboard configuration (layer/mods/transport sync)
- RGB matrix settings (no animations)
- **TAPPING_TERM = 275** - Tap vs hold timing
- **SWITCHER_HOLD_TIME = 500** - 3-thumb detection
- **LED_BRIGHTNESS = 50** - Indicator brightness
- **DEFAULT_BRIGHTNESS = 200** - Initial global brightness
- EEPROM size (1 byte) for global brightness

---

### rules.mk (290 B, feature enables)
**Enabled features:**
- RGB_MATRIX_ENABLE = yes
- LTO_ENABLE = yes (firmware size optimization)

---

## 🎯 Common Tasks & Where to Find Help

### I want to...

#### 1. **Add a new layer**
- Read: README.md → Layer Architecture section
- Find: Layer definitions (keymap.c lines 15-16)
- Edit: Add layer to enum, add keymap array, add LED pattern
- Reference: README.md → Layer Architecture for examples

#### 2. **Change a key's behavior**
- Quick help: QUICK_REFERENCE.md → Custom Keycode Reference
- Detailed: README.md → Custom Keycodes section
- Code: keymap.c → process_record_user() function
- Line reference: See QUICK_REFERENCE.md table

#### 3. **Fix LED indicators**
- Quick help: QUICK_REFERENCE.md → LED Index Cheat Sheet
- Detailed: README.md → LED Mapping & Indices
- Architecture: ARCHITECTURE.md → LED Index Calculation
- Code: keymap.c → get_led_index() & rgb_matrix_indicators_user()

#### 4. **Adjust heatmap animation**
- Parameters: QUICK_REFERENCE.md → Parameter Tuning Guide
- Details: README.md → RGB Features → Heatmap Animation
- Implementation: keymap.c lines 114-120, 739-775

#### 5. **Customize LED colors**
- Quick: QUICK_REFERENCE.md → Change LED Colors
- Full guide: README.md → RGB Features → LED Settings Per Base Layer
- Default values: keymap.c lines 99-103

#### 6. **Debug a problem**
- Start: QUICK_REFERENCE.md → Troubleshooting Quick Links
- Detailed: README.md → Debugging Guide
- Design context: ARCHITECTURE.md → Debugging Techniques

#### 7. **Understand thumb key logic**
- Overview: README.md → Thumb Key System
- Visual: ARCHITECTURE.md → State Machine: Thumb Key Behavior
- Code: keymap.c lines 390-494 (handlers), 627-672 (SWITCHER detection)

#### 8. **Modify SWITCHER behavior**
- Parameters: QUICK_REFERENCE.md → Change SWITCHER_HOLD_TIME
- Details: README.md → Thumb Key System
- Architecture: ARCHITECTURE.md → State Machine diagrams
- Code: keymap.c lines 47, 627-672

#### 9. **Change CONFIG layer**
- Details: README.md → Layer Architecture → CONFIG layer
- Parameters: QUICK_REFERENCE.md → Adjustment keys
- Architecture: ARCHITECTURE.md → Configuration Layer State Machine
- Code: keymap.c lines 234-254, 496-567, 1010-1057

#### 10. **Modify tap-hold timing**
- Quick: QUICK_REFERENCE.md → Change TAPPING_TERM
- Details: README.md → Configuration & Build → Configuration Parameters
- Code: config.h line 19

---

## 📋 File Structure Reference

```
/home/razu/qmk_firmware/keyboards/mykeyboards/corne/rev4_1/keymaps/LuisCardoso/
├── README.md                    (33 KB) - Complete feature guide
├── ARCHITECTURE.md              (28 KB) - Design & diagrams
├── QUICK_REFERENCE.md           (7 KB)  - Quick lookup
├── INDEX.md                     (this file) - Navigation guide
├── keymap.c                     (46 KB) - Main implementation (699 lines)
├── config.h                     (1.1 KB) - Configuration (66 lines)
└── rules.mk                     (290 B)  - Feature enables (16 lines)

Total Documentation: ~2100 lines, ~95 KB
```

---

## 🔑 Key Concepts Reference

### Layers (10 total)
- **Base layers:** MAIN (MAI), QWRT (QRT), GAME (GAM) - only one active at a time
- **Temporary layers:** NUMB (NUM), SYMB (SMB), AROW (ARW), CODE (COD), SHR (SHR) - activated by holding keys
- **Special layers:** SWITCHER (SWX) for 3-thumb menu, CONFIG (CNF) for brightness control

### Thumb Keys
- **LTL:** Left outer (GUI tap, SWITCHER participant)
- **LTM:** Left middle (Enter tap, NUM hold)
- **LTR:** Left inner (SWITCHER participant)
- **RTL:** Right inner (ARW layer hold)
- **RTM:** Right middle (Space hold)
- **RTR:** Right outer (SWITCHER participant)

### LED Indices
- Left side: 0-22 (rows 0-2: 0-6, 7-13, 14-19; thumbs: 20-22)
- Right side: 23-45 (rows 0-2: 23-29, 30-36, 37-42; thumbs: 43-45)

### State Variables
- `current_base_layer` - Which base layer is active (MAI/QRT/GAM)
- `global_brightness` - Global LED brightness multiplier (0-255, persisted to EEPROM)
- `numb_locked` - Whether NUM layer is toggled on
- `switcher_activated` - Whether SWX layer is active
- `config_activated` - Whether CNF layer is active
- `left_thumb_timer` / `right_thumb_timer` - SWITCHER detection timers

### Important Timers & Constants
- `TAPPING_TERM = 275ms` - Time to distinguish tap vs hold (config.h:19)
- `SWITCHER_HOLD_TIME = 500ms` - Time to hold 3 thumbs for SWX (keymap.c:35)
- `CONFIG_HOLD_TIME = 500ms` - Time to hold both ESCs for CNF (keymap.c:36)
- `BRIGHTNESS_STEP = 25` - LED brightness increment per BRI_UP/BRI_DN (config.h:45)
- `DEFAULT_BRIGHTNESS = 200` - Initial global brightness on first boot (config.h:46)

---

## 🐛 Debugging Strategy

1. **LEDs not working?**
   - Check: LED index calculation (keymap.c lines 303-337)
   - Read: README.md → LED Mapping section

2. **Layer switching issues?**
   - Check: Layer definitions (keymap.c lines 122-254)
   - Debug: Layer state tracking (keymap.c line 627-707)
   - Read: README.md → Layer Architecture

3. **Thumb key behavior wrong?**
   - Check: Thumb key handlers (keymap.c lines 390-494)
   - Check: SWITCHER detection (keymap.c lines 627-672)
   - Read: ARCHITECTURE.md → State Machine diagram

4. **Heatmap not showing?**
   - Check: get_led_index() returns valid indices
   - Check: render_heatmap() is called (keymap.c line 935)
   - Debug: key_heat[] values updating
   - Read: README.md → Heatmap Animation

5. **CONFIG layer won't open?**
   - Check: ESC key positions (row 2, col 0 & 11)
   - Check: config_hold_timer logic (keymap.c lines 674-691)
   - Read: README.md → Layer Architecture → CONFIG layer

---

## 📚 Reading Recommendations

**For beginners:**
1. Start: QUICK_REFERENCE.md
2. Then: README.md → Overview & Layer Architecture
3. Finally: Try ARCHITECTURE.md diagrams

**For debugging:**
1. Start: QUICK_REFERENCE.md → Troubleshooting
2. Then: README.md → Debugging Guide
3. Finally: ARCHITECTURE.md → Debugging Techniques

**For feature development:**
1. Start: README.md → Feature section you're working on
2. Then: ARCHITECTURE.md → Related design diagrams
3. Finally: keymap.c → Implementation code

**For complete understanding:**
1. Read: README.md (cover to cover)
2. Review: ARCHITECTURE.md → System Overview
3. Study: ARCHITECTURE.md → State Machine diagrams
4. Reference: keymap.c → Specific implementations

---

## 🔗 Related Files in Repo

**Keyboard hardware definition:**
```
/home/razu/qmk_firmware/keyboards/mykeyboards/corne/rev4_1/
├── info.json     - Keyboard layout & matrix
├── config.h      - Hardware config
└── rules.mk      - Feature enables
```

**Other keymaps (if you need examples):**
```
/home/razu/qmk_firmware/keyboards/splitkb/aurora/sofle_v2/keymaps/LuisAntonioCardoso/
```

---

## 📝 Document Maintenance

**Last Updated:** 2026-02-04  
**Keymap Version:** 2.2  
**Documentation Version:** 2.2  
**Total Lines:** ~2200  
**Total Size:** ~98 KB

### When updating documentation:
1. Keep line references current
2. Update version numbers
3. Update modification dates
4. Keep QUICK_REFERENCE synchronized with README
5. Update ARCHITECTURE diagrams if logic changes

---

## ✅ Verification Checklist

When modifying the keymap:

- [ ] Read relevant section in README.md
- [ ] Check ARCHITECTURE.md for design context
- [ ] Verify line numbers in code reference
- [ ] Test the modification
- [ ] Update documentation if behavior changed
- [ ] Build and verify: `qmk compile -kb mykeyboards/corne/rev4_1 -km LuisCardoso`

---

## 🤝 Contributing

To maintain documentation quality:

1. **Keep it current:** Update references if line numbers change
2. **Add examples:** Include code snippets for complex features
3. **Visual aids:** Use diagrams for system design
4. **Be specific:** Reference exact line numbers and files
5. **Link related:** Cross-reference between documents
6. **Explain why:** Document not just what, but why design decisions were made

---

**Questions?** Check the appropriate document from the table above, then consult the Debugging Guide if still unclear.

**Found an error in documentation?** Update it and keep future maintainers happy! 🎉
