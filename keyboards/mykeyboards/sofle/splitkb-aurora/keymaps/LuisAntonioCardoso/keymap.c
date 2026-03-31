#include QMK_KEYBOARD_H

enum layers {
    _MAIN,
    _QWRT,
    _GAME,
    _SHRT,
    _SYMB,
    _AROW,
    _CODE,
    _NUMB,
    _MDIA
};
// add here new keycodes needed
enum custom_keycodes {
    CKC_QU = SAFE_RANGE, // safe range is used to not overlap the codes from the key codes 
    CKC_BSPCDEL
//    CUSTOM_3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_MAIN]  = LAYOUT(
        RGB_TOG         ,CKC_BSPCDEL     ,KC_NO           ,KC_DEL          ,C(KC_O)         ,C(KC_N)         ,                                      KC_NO           ,KC_NO           ,KC_NO           ,KC_NO           ,KC_NO           ,TG(_GAME)       ,
        S(KC_8)         ,KC_NO           ,KC_Q            ,KC_O            ,KC_U            ,KC_B            ,                                      KC_K            ,KC_G            ,KC_L            ,KC_W            ,KC_NO           ,KC_SCLN         ,
        KC_TAB          ,LT(_SYMB,KC_C)  ,LSFT_T(KC_S)    ,LALT_T(KC_E)    ,LCTL_T(KC_A)    ,KC_I            ,                                      KC_D            ,LCTL_T(KC_T)    ,LALT_T(KC_R)    ,LSFT_T(KC_N)    ,LT(_CODE,KC_H)  ,CKC_BSPCDEL     ,
        KC_ESC          ,KC_COMM         ,KC_Z            ,KC_X            ,KC_Y            ,KC_J            ,LT(_MDIA,KC_MUTE) ,LT(_MDIA,KC_MPLY) ,KC_F            ,KC_M            ,KC_V            ,KC_P            ,KC_DOT          ,KC_ESC          , 
                                          TG(_QWRT)       ,KC_LGUI         ,LT(_NUMB,KC_ENT),TG(_NUMB)       ,MO(_SHRT)  		,MO(_SHRT)  	   ,LT(_AROW,KC_SPC),TG(_NUMB)		 ,KC_NO           ,KC_CAPS 
    ) ,
    [_QWRT] = LAYOUT(
        QK_BOOT         ,KC_TRNS         ,KC_NO           ,KC_NO           ,KC_NO           ,KC_NO           ,                                       KC_NO          ,KC_NO           ,KC_NO           ,KC_NO           ,KC_NO           ,KC_NO           ,
        KC_TRNS         ,KC_Q            ,KC_W            ,KC_E            ,KC_R            ,KC_T            ,                                       KC_Y           ,KC_U            ,KC_I            ,KC_O            ,KC_P            ,KC_NO           ,
        KC_TRNS         ,LT(_SYMB,KC_A)  ,LSFT_T(KC_S)    ,LALT_T(KC_D)    ,LCTL_T(KC_F)    ,KC_G            ,                                       KC_H           ,LCTL_T(KC_J)    ,LALT_T(KC_K)    ,LSFT_T(KC_L)    ,LT(_CODE,KC_SCLN),KC_TRNS        ,
        KC_TRNS         ,KC_Z            ,KC_X            ,KC_C            ,KC_V            ,KC_B            ,KC_TRNS           ,KC_TRNS            ,KC_N           ,KC_M            ,KC_COMM         ,KC_DOT          ,KC_QUOT         ,KC_TRNS         ,
                                          KC_TRNS         ,KC_TRNS         ,KC_TRNS         ,KC_TRNS         ,KC_TRNS           ,KC_TRNS            ,KC_TRNS        ,KC_TRNS         ,KC_NO           ,KC_TRNS
    ) ,
    [_GAME] = LAYOUT(
        CKC_BSPCDEL     ,KC_A            ,KC_B            ,KC_C            ,KC_D            ,KC_E            ,                                       KC_NO          ,KC_NO           ,KC_NO           ,KC_NO           ,KC_NO           ,KC_TRNS         ,
        KC_TAB          ,KC_F            ,KC_G            ,KC_H            ,KC_I            ,KC_J            ,                                       KC_Y           ,KC_U            ,KC_I            ,KC_O            ,KC_P            ,KC_NO           ,
        KC_K            ,KC_L            ,KC_M            ,KC_N            ,KC_O            ,KC_P            ,                                       KC_H           ,LCTL_T(KC_J)    ,LALT_T(KC_K)    ,LSFT_T(KC_L)    ,LT(_CODE,KC_SCLN),KC_TRNS        ,
        KC_TRNS         ,KC_Q            ,KC_R            ,KC_S            ,KC_T            ,KC_U            ,KC_TRNS           ,KC_TRNS            ,KC_N           ,KC_M            ,KC_COMM         ,KC_DOT          ,KC_QUOT         ,KC_TRNS         ,
                                          KC_V            ,KC_ESC          ,LCTL_T(KC_Y)    ,KC_X            ,KC_Z              ,KC_TRNS            ,KC_TRNS        ,KC_TRNS         ,KC_NO           ,KC_TRNS
    ) ,
    [_SHRT]  = LAYOUT(
        KC_NO           ,KC_TRNS         ,KC_NO           ,KC_NO           ,KC_NO           ,KC_NO           ,                                      KC_NO           ,KC_NO           ,KC_NO           ,KC_NO           ,KC_NO           ,KC_TRNS         ,
        KC_TRNS         ,KC_NO           ,KC_NO           ,C(KC_S)         ,C(KC_C)         ,C(KC_O)         ,                                      C(KC_O)         ,C(KC_C)         ,C(KC_S)         ,KC_NO           ,KC_NO           ,KC_TRNS         ,
        KC_TRNS         ,KC_NO           ,KC_NO           ,C(KC_A)         ,C(KC_X)         ,C(KC_E)         ,                                      C(KC_E)         ,C(KC_X)         ,C(KC_A)         ,KC_NO           ,KC_NO           ,KC_TRNS         ,
        KC_TRNS         ,KC_NO           ,KC_NO           ,C(KC_F)         ,C(KC_V)         ,C(KC_N)         ,LT(_MDIA,KC_MUTE) ,LT(_MDIA,KC_MPLY) ,C(KC_N)         ,C(KC_V)         ,C(KC_F)         ,KC_NO           ,KC_NO           ,KC_TRNS         ,
                                          TG(_QWRT)       ,KC_LGUI         ,KC_TRNS         ,LT(_NUMB,KC_ENT),KC_TRNS           ,KC_TRNS           ,LT(_AROW,KC_SPC),KC_TRNS         ,KC_NO           ,KC_CAPS
    ) ,
	[_SYMB]  = LAYOUT(
        KC_NO          ,KC_TRNS          ,KC_NO           ,KC_NO           ,KC_NO           ,KC_NO           ,                                       KC_NO          ,KC_NO           ,KC_NO           ,KC_NO           ,KC_NO           ,KC_NO          ,
        KC_TRNS        ,KC_NO            ,KC_NO           ,KC_NO           ,KC_NO           ,KC_NO           ,                                       KC_MINS        ,KC_RBRC         ,S(KC_BSLS)      ,S(KC_4)         ,C(A(KC_5))      ,KC_NO          ,
        KC_TRNS        ,KC_NO            ,LSFT_T(KC_NO)   ,LALT_T(KC_NO)   ,LCTL_T(KC_NO)   ,KC_NO           ,                                       S(KC_MINS)     ,KC_QUOT         ,S(KC_7)         ,S(KC_3)         ,S(KC_2)         ,KC_TRNS        ,
        KC_TRNS        ,KC_NO            ,KC_NO           ,KC_NO           ,KC_NO           ,KC_NO           ,KC_TRNS           ,KC_TRNS            ,S(KC_QUOT)     ,KC_GRV          ,S(KC_5)         ,S(KC_8)         ,S(KC_SCLN)      ,KC_TRNS        ,
                                          KC_TRNS         ,KC_TRNS         ,KC_TRNS         ,KC_TRNS         ,KC_NO             ,KC_NO              ,KC_TRNS        ,KC_TRNS         ,KC_NO           ,KC_TRNS
    ) ,
	[_AROW] = LAYOUT(
        KC_NO           ,KC_TRNS         ,KC_NO           ,KC_NO           ,KC_NO           ,KC_NO           ,                                       KC_NO          ,KC_NO           ,KC_NO           ,KC_NO           ,KC_NO           ,KC_NO          ,
        KC_TRNS         ,KC_NO           ,S(KC_BSLS)      ,LSFT_T(KC_BSLS) ,KC_GRV          ,KC_RBRC      	 ,                                       KC_NO          ,KC_NO           ,KC_NO           ,KC_NO           ,KC_NO           ,KC_NO          ,
        KC_TRNS         ,KC_NO  		 ,LSFT_T(KC_NO)   ,LALT_T(KC_NO)   ,LCTL_T(KC_NO)   ,KC_NO           ,                                       KC_NO          ,LCTL_T(KC_LEFT) ,LALT_T(KC_UP)   ,LSFT_T(KC_DOWN) ,KC_RGHT         ,KC_TRNS        ,
        KC_TRNS         ,KC_NO           ,KC_NO           ,S(KC_1)         ,S(KC_SLSH)      ,S(KC_8)         ,KC_TRNS           ,KC_TRNS            ,KC_NO          ,KC_NO           ,KC_NO           ,KC_NO           ,KC_NO           ,KC_TRNS        ,
                                          KC_NO           ,KC_TRNS         ,KC_TRNS         ,KC_NO           ,KC_NO             ,KC_TRNS            ,KC_TRNS        ,KC_TRNS         ,KC_NO           ,KC_TRNS
    ) ,
	[_CODE]  = LAYOUT(
        KC_NO          ,KC_TRNS          ,KC_NO           ,KC_NO           ,KC_NO           ,KC_NO           ,                                      KC_NO           ,KC_NO           ,KC_NO           ,KC_NO           ,KC_NO           ,KC_NO           ,
        KC_TRNS        ,KC_NO            ,KC_RBRC         ,KC_LBRC         ,S(KC_COMM)      ,S(KC_DOT)       ,                                      KC_NO           ,KC_NO           ,KC_NO           ,KC_NO           ,KC_NO           ,KC_NO           ,
        KC_TRNS        ,KC_EQL           ,S(KC_RBRC)      ,S(KC_LBRC)      ,S(KC_9)         ,S(KC_0)         ,                                      KC_NO           ,LCTL_T(KC_NO)   ,LALT_T(KC_NO)   ,LSFT_T(KC_NO)   ,KC_NO           ,KC_TRNS         ,
        KC_TRNS        ,KC_SCLN          ,KC_TRNS         ,KC_BSLS         ,KC_SLSH         ,KC_NO           ,KC_MUTE           ,KC_MPLY           ,KC_NO           ,KC_NO           ,KC_NO           ,KC_NO           ,KC_NO           ,KC_TRNS         ,
                                          KC_NO           ,KC_TRNS         ,KC_TRNS         ,KC_TRNS         ,KC_NO             ,KC_NO             ,KC_TRNS         ,KC_TRNS         ,KC_NO           ,KC_TRNS
    ) ,
	[_NUMB]  = LAYOUT(
        KC_NO           ,KC_TRNS         ,KC_NO           ,KC_NO           ,KC_NO           ,KC_NO           ,                                       KC_NO          ,KC_NO           ,KC_NO           ,KC_NO           ,KC_NO           ,KC_NO          ,
        KC_TRNS         ,KC_1            ,KC_2            ,KC_3            ,KC_4            ,KC_5            ,                                       KC_NO          ,KC_NO           ,KC_NO           ,KC_NO           ,KC_NO           ,KC_NO          ,
        KC_TRNS         ,KC_6            ,LSFT_T(KC_7)    ,LALT_T(KC_8)    ,LCTL_T(KC_9)    ,KC_0            ,                                       KC_NO          ,LCTL_T(KC_NO)   ,LALT_T(KC_NO)   ,LSFT_T(KC_NO)   ,KC_NO           ,KC_TRNS        ,
        KC_TRNS         ,KC_SLSH         ,S(KC_8)         ,KC_MINS         ,S(KC_EQL)       ,KC_EQL          ,KC_TRNS           ,KC_TRNS            ,KC_NO          ,KC_NO           ,KC_NO           ,KC_NO           ,KC_NO           ,KC_TRNS        ,
                                          KC_NO           ,KC_TRNS         ,KC_TRNS         ,KC_TRNS         ,KC_TRNS           ,KC_NO              ,KC_TRNS        ,KC_TRNS         ,KC_NO           ,KC_TRNS
    ) ,
    [_MDIA] = LAYOUT(
        KC_NO           ,KC_TRNS         ,KC_NO           ,KC_NO           ,KC_NO           ,KC_NO           ,                                       KC_NO          ,KC_NO           ,KC_NO           ,KC_NO           ,KC_NO           ,KC_NO          ,
        KC_TRNS         ,KC_1            ,KC_2            ,KC_3            ,KC_4            ,KC_5            ,                                       KC_NO          ,KC_NO           ,KC_NO           ,KC_NO           ,KC_NO           ,KC_NO          ,
        KC_TRNS         ,KC_6            ,LSFT_T(KC_7)    ,LALT_T(KC_8)    ,LCTL_T(KC_9)    ,KC_0            ,                                       KC_NO          ,LCTL_T(KC_NO)   ,LALT_T(KC_NO)   ,LSFT_T(KC_NO)   ,KC_NO           ,KC_TRNS        ,
        KC_TRNS         ,KC_PPLS         ,KC_PMNS         ,KC_PAST         ,KC_PSLS         ,KC_PEQL         ,KC_TRNS           ,KC_TRNS            ,KC_NO          ,KC_NO           ,KC_NO           ,KC_NO           ,KC_NO           ,KC_TRNS        ,
                                          KC_NO           ,KC_TRNS         ,KC_TRNS         ,KC_TRNS         ,KC_TRNS           ,KC_NO              ,KC_TRNS        ,KC_TRNS         ,KC_NO           ,KC_TRNS
    )
};


uint8_t mod_state; // this is used to modify the the key based on active modifiers like alt or ctrl
// if you want to define the behavior of a keycode or extend its behavior
// if you want to keep the current behavior your should return true , and the normal behavior will be executed along side other defined behaviors
// if you want to remove default behavior you should return false , and only the defined behavior will be executed
bool process_record_user(uint16_t keycode , keyrecord_t *record) {
//  below is a simple example of how to use the process_record_user function
//  the behavior for FOO is created , and the behavior for KC_ENTER is extended

	mod_state = get_mods();
    switch (keycode) {
        case CKC_QU:
			if(mod_state & MOD_MASK_CS) {
				
				del_mods(MOD_MASK_CS);

				if (record->event.pressed) {
					register_code(KC_Q);
				} else {
					unregister_code(KC_Q);
				}
				set_mods(mod_state);
			} else {
				if (record->event.pressed) {
					tap_code(KC_Q);
					tap_code(KC_U);
				}
			}
			return true;
			// Let QMK process the KC_BSPC keycode as usual outside of shift
			case CKC_BSPCDEL:
			// Initialize a boolean variable that keeps track
			// of the delete key status: registered or not?
			static bool delkey_registered;
			if (record->event.pressed) {
				// Detect the activation of either shift keys
				if (mod_state & MOD_MASK_SHIFT) {
					// First temporarily canceling both shifts so that
					// shift isn't applied to the KC_DEL keycode
					del_mods(MOD_MASK_SHIFT);
					register_code(KC_DEL);
					// Update the boolean variable to reflect the status of KC_DEL
					delkey_registered = true;
					// Reapplying modifier state so that the held shift key(s)
					// still work even after having tapped the Backspace/Delete key.
					set_mods(mod_state);
				} else {
					register_code(KC_BSPC);
				}
			} else { // on release of KC_BSPC
				// In case KC_DEL is still being sent even after the release of KC_BSPC
				if (delkey_registered) {
					unregister_code(KC_DEL);
					delkey_registered = false;
				} else {
					unregister_code(KC_BSPC);
				}
			}
			// Let QMK process the KC_BSPC keycode as usual outside of shift
			return true;
//  	case KC_ENTER:
//    		// Play a tone when enter is pressed
//  		if (record->event.pressed) {
//  			PLAY_SONG(tone_qwerty);
//  		}  else {
//      		     Do something else when release
//          }
//    		return true; // Let QMK send the enter press/release events
        default:
    		return true; // Process all other keycodes normally
    }
};


#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_MAIN] = { ENCODER_CCW_CW( KC_VOLU               , KC_VOLD             ), ENCODER_CCW_CW( KC_RIGHT              , KC_LEFT             ) },
    [_QWRT] = { ENCODER_CCW_CW( KC_TRNS               , KC_TRNS             ), ENCODER_CCW_CW( KC_TRNS               , KC_TRNS             ) },
    [_GAME] = { ENCODER_CCW_CW( KC_TRNS               , KC_TRNS             ), ENCODER_CCW_CW( KC_TRNS               , KC_TRNS             ) },
    [_SHRT] = { ENCODER_CCW_CW( KC_TRNS               , KC_TRNS             ), ENCODER_CCW_CW( KC_PGDN               , KC_PGUP             ) },
    [_SYMB] = { ENCODER_CCW_CW( KC_PGDN               , KC_PGUP             ), ENCODER_CCW_CW( KC_TRNS               , KC_TRNS             ) },
    [_AROW] = { ENCODER_CCW_CW( S(KC_TAB)             , KC_TAB              ), ENCODER_CCW_CW( KC_TRNS               , KC_TRNS             ) },
    [_CODE] = { ENCODER_CCW_CW( KC_TRNS               , KC_TRNS             ), ENCODER_CCW_CW( S(KC_TAB)             , KC_TAB              ) },
    [_NUMB] = { ENCODER_CCW_CW( KC_TRNS               , KC_TRNS             ), ENCODER_CCW_CW( S(C(KC_Z))            , C(KC_Z)             ) },
    [_MDIA] = { ENCODER_CCW_CW( KC_MEDIA_NEXT_TRACK   , KC_MEDIA_PREV_TRACK ), ENCODER_CCW_CW( KC_VOLU               , KC_VOLD             ) }
};

// similar to the above function process_record_user , but for the encoders
// if you want to define the behavior of the encoders or extend its behavior
// its not really the same since the encoders work as keys , not keycodes
// Just like the other function , returning false overwrites the functionality and returning true extends it
//bool encoder_update_user(uint8_t index , bool clockwise) {
//  switch(get_highest_layer(layer_state)) {
//      case _MAIN:
//      case _SYMB:
//      case _AROW:
//      case _CODE:
//      case _NUMB:
//      case _QWERT:
//      case default:
//          break;
//  if (index == 0) { /* First encoder */
//      if (clockwise) {
//          tap_code(KC_PGDN);
//      } else {
//          tap_code(KC_PGUP);
//      }
//  } else if (index == 1) { /* Second encoder */
//      if (clockwise) {
//          rgb_matrix_increase_hue();
//      } else {
//          rgb_matrix_decrease_hue();
//      }
//  }
//  return false;
//  }
//}
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)