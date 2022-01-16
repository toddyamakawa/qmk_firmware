/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// vim: ts=4 et

#include QMK_KEYBOARD_H

#define HOLD_SHIFT()      register_mods(MOD_BIT(KC_LSFT))
#define RELEASE_SHIFT() unregister_mods(MOD_BIT(KC_LSFT))
#define HOLD_CTRL()       register_mods(MOD_BIT(KC_LCTRL))
#define RELEASE_CTRL()  unregister_mods(MOD_BIT(KC_LCTRL))
#define HOLD_ALT()        register_mods(MOD_BIT(KC_LALT))
#define RELEASE_ALT()   unregister_mods(MOD_BIT(KC_LALT))
#define HOLD_GUI()        register_mods(MOD_BIT(KC_LGUI))
#define RELEASE_GUI()   unregister_mods(MOD_BIT(KC_LGUI))

// Idea from: https://github.com/winterNebs/qmk_firmware/blob/master/users/winternebs/winternebs.h
#define _______________QWERTY_L1_______________ KC_Q, KC_W, KC_E   , KC_R  , KC_T
#define _______________QWERTY_L2_______________ KC_A, KC_S, KC_D   , KC_F  , KC_G
#define _______________QWERTY_L3_______________ KC_Z, KC_X, KC_C   , KC_V  , KC_B
#define _______________QWERTY_R1_______________ KC_Y, KC_U, KC_I   , KC_O  , KC_P
#define _______________QWERTY_R2_______________ KC_H, KC_J, KC_K   , KC_L  , KC_SCLN
#define _______________QWERTY_R3_______________ KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH


#define OS_SFT OSM(MOD_LSFT)
#define OS_CTL OSM(MOD_LCTL)
#define OS_ALT OSM(MOD_LALT)
#define OS_GUI OSM(MOD_LGUI)

// Examples
// - KC_LCTL
// - LT(_NUMBER, KC_ENT)
// - LT(_NUMBER, KC_DEL)
// - LT(_NUMBER, KC_PGUP)
// - LT(_NUMBER, KC_DEL)
// - MT(MOD_LCTL, KC_BSPC)
// - MT(MOD_LCTL, KC_ESC)
// - MT(MOD_LALT, KC_ENT)

#define THUM_L1 MO(_LEFT)
//#define THUM_L2 MO(_NUMBER)
#define THUM_L2 MO(_NUMBER_TEST)
#define THUM_L3 LT(_RIGHT, KC_DEL)
#define THUM_L4 KEY_ENABLE_MOD
//#define THUM_L4 KC_DEL
#define THUM_L5 KC_SLCK
#define THUM_L6 KC_LCTL
#define THUM_L7 KC_LSFT
#define THUM_R1 MT(MOD_LSFT, KC_BSPC)
#define THUM_R2 KC_SPC
#define THUM_R3 MO(_RIGHT)
#define THUM_R4 MO(_RGB)
#define THUM_R5 KC_MUTE
#define THUM_R6 MO(_NUMBER)
#define THUM_R7 LT(_NUMBER, KC_END)

#define PINK_L1 KC_TAB
#define PINK_L2 VIM_ESC
#define PINK_L3 KC_LSFT
#define PINK_R1 _______
#define PINK_R2 KC_QUOT
#define PINK_R3 LGUI(KC_L)

// LOL
#define TO_LOL  TO(_LOL)
#define MO_LOL2 MO(_LOL2)
#define TO_QWER TO(_QWERTY)

#define CTRL_Q LCTL(KC_Q)
#define CTRL_W LCTL(KC_W)
#define CTRL_E LCTL(KC_E)
#define CTRL_R LCTL(KC_R)


enum layers {
    _QWERTY = 0,
    _NUMBER,
    _NUMBER_TEST,
    _LEFT,
    _RIGHT,
    _LOL,
    _LOL2,
    _RGB
};

enum combos {
    COMBO_QWER,
    COMBO_MOD_AS,
    COMBO_MOD_AD,
    COMBO_MOD_AF,
    COMBO_MOD_SD,
    COMBO_MOD_SF,
    COMBO_MOD_DF,
    COMBO_MOD_ASD,
    COMBO_MOD_ASF,
    COMBO_MOD_ADF,
    COMBO_MOD_SDF,
    COMBO_MOD_ASDF
};

typedef enum {
    MOD_SHIFT  = 0b00001,
    MOD_CTRL   = 0b00010,
    MOD_ALT    = 0b00100,
    MOD_GUI    = 0b01000,
    MOD_ENABLE = 0b10000
} modifier_t;

modifier_t get_modifiers(void);
bool process_mod_key(uint16_t keycode, keyrecord_t *record);
static modifier_t mod_enable;
void press_key(uint16_t keycode, keyrecord_t *record, modifier_t modifier);


// =============================================================================
// VIM
// =============================================================================
bool process_vim_key(uint16_t keycode, keyrecord_t *record);

#define MOD_VIM_VISUAL ((vim.visual) ? MOD_SHIFT : 0)

typedef enum {
    VIM_NONE,
    VIM_DELETE,
    VIM_CHANGE,
    VIM_YANK
} vim_action_t;
typedef struct {
    bool enabled;
    bool visual;
    bool set_go;
    bool go;
    vim_action_t action;
} vim_state_t;

enum custom_keycodes {
    VIM_ESC = SAFE_RANGE,
    MY_UNDO,
    MY_CUT,
    MY_COPY,
    MY_PSTE,
    KEY_HOLD_S,

    KEY_ENABLE_MOD,
};

static vim_state_t vim = {false, false, false, false, VIM_NONE};


// =============================================================================
// COMBOS
// =============================================================================
// config.h: #define COMBO_COUNT <count>
// rules.mk: COMBO_ENABLE = yes
enum combo_events {
    COMBO_SELECT_ROW
};
const uint16_t PROGMEM qwer_combo[] = {KC_Q, KC_W, KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM ctrl_combo[] = {KC_SPC, KC_F, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
    [COMBO_QWER] = COMBO(qwer_combo, COMBO_SELECT_ROW)
    //[COMBO_CTRL] = COMBO(ctrl_combo, KC_LCTL)
};

//const uint16_t PROGMEM control[] = {KC_DEL, KC_F, COMBO_END};
//const uint16_t PROGMEM control[] = {KC_A, KC_S, COMBO_END};
//combo_t key_combos[COMBO_COUNT] = {
//	COMBO(control, KC_LCTL)
//};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// ====================================================================================================================================
// BLANK
// ====================================================================================================================================
// ┌───────┬───────┬───────┬───────┬───────┬───────┐                                  ┌───────┬───────┬───────┬───────┬───────┬───────┐
// │       │       │       │       │       │       │                                  │       │       │       │       │       │       │
// │       │       │       │       │       │       │                                  │       │       │       │       │       │       │
// ├───────┼───────┼───────┼───────┼───────┼───────┤                                  ├───────┼───────┼───────┼───────┼───────┼───────┤
// │       │       │       │       │       │       │                                  │       │       │       │       │       │       │
// │       │       │       │       │       │       │                                  │       │       │       │       │       │       │
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┬───────┐  ┌───────┬───────┼───────┼───────┼───────┼───────┼───────┼───────┤
// │       │       │       │       │       │       │       │       │  │       │       │       │       │       │       │       │       │
// │       │       │       │       │       │       │       │       │  │       │       │       │       │       │       │       │       │
// └───────┴───────┴───────┼───────┼───────┼───────┼───────┼───────┤  ├───────┼───────┼───────┼───────┼───────┼───────┴───────┴───────┘
//                         │       │       │       │       │       │  │       │       │       │       │       │
//                         │       │       │       │       │       │  │       │       │       │       │       │
//                         └───────┴───────┴───────┴───────┴───────┘  └───────┴───────┴───────┴───────┴───────┘
//  _______,_______,_______,_______,_______,_______,                                   _______,_______,_______,_______,_______,_______,
//  _______,_______,_______,_______,_______,_______,                                   _______,_______,_______,_______,_______,_______,
//  _______,_______,_______,_______,_______,_______,_______,_______,   _______,_______,_______,_______,_______,_______,_______,_______,
//                          _______,_______,_______,_______,_______,   _______,_______,_______,_______,_______
//

// ====================================================================================================================================
// BASE LAYER: QWERTY
// ====================================================================================================================================
// ┌───────┬───────┬───────┬───────┬───────┬───────┐                                  ┌───────┬───────┬───────┬───────┬───────┬───────┐
// │       │   Q   │   W   │   E   │   R   │   T   │                                  │   Y   │   U   │   I   │   O   │   P   │   |   │
// │  TAB  │       │       │       │       │       │                                  │       │       │       │       │       │   \   │
// ├───────┼───────┼───────┼───────┼───────┼───────┤                                  ├───────┼───────┼───────┼───────┼───────┼───────┤
// │       │   A   │   S   │   D   │   F   │   G   │                                  │   H   │   J   │   K   │   L   │   :   │   "   │
// │  VIM  │       │       │       │       │       │                                  │       │       │       │       │   ;   │   '   │
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┬───────┐  ┌───────┬───────┼───────┼───────┼───────┼───────┼───────┼───────┤
// │       │   Z   │   X   │   C   │   V   │   B   │ SHIFT │  CTRL │  │ NUMBER│ NUMBER│   N   │   M   │   <   │   >   │   ?   │   _   │
// │  NUM  │       │       │       │       │       │       │       │  │       │  END  │       │       │   ,   │   .   │   /   │   -   │
// └───────┴───────┴───────┼───────┼───────┼───────┼───────┼───────┤  ├───────┼───────┼───────┼───────┼───────┼───────┴───────┴───────┘
//                         │ SCROLL│  MOD  │ RIGHT │ NUMBER│  LEFT │  │ SHIFT │       │ RIGHT │  RGB  │  VOL  │
//                         │SCRLOCK│       │  DEL  │       │       │  │ BKSPC │ SPACE │       │       │  MUTE │
//                         └───────┴───────┴───────┴───────┴───────┘  └───────┴───────┴───────┴───────┴───────┘
    [_QWERTY] = LAYOUT(
    // TODO: Figure out why this doesn't work
//  PINK_L1,_______________QWERTY_L1_______________,                                   _______________QWERTY_R1_______________,KC_PIPE,
//  PINK_L2,_______________QWERTY_L2_______________,                                   _______________QWERTY_R2_______________,KC_QUOT,
//  PINK_L3,_______________QWERTY_L3_______________,THUM_L7,THUM_L6,   THUM_R6,THUM_R7,_______________QWERTY_R3_______________,KC_MINS,
    PINK_L1,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                                      KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,PINK_R1,
    PINK_L2,   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                                      KC_H,   KC_J,   KC_K,   KC_L,KC_SCLN,PINK_R2,
    PINK_L3,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,THUM_L7,THUM_L6,   THUM_R6,THUM_R7,   KC_N,   KC_M,KC_COMM, KC_DOT,KC_SLSH,PINK_R3,
                            THUM_L5,THUM_L4,THUM_L3,THUM_L2,THUM_L1,   THUM_R1,THUM_R2,THUM_R3,THUM_R4,THUM_R5
    ),

    [_LEFT] = LAYOUT(
    KC_TAB ,KC_ESC ,KC_DEL ,KC_PGUP,KC_PGDN,KC_HOME,                                   _______,_______,_______,_______,_______,_______,
  //_______,OS_SFT ,OS_GUI ,OS_ALT ,OS_CTL ,KC_ENT ,                                   KC_LEFT,KC_DOWN,KC_UP  ,KC_RGHT,_______,_______,
  //_______,KC_LSFT,KC_LGUI,KC_LALT,KC_LCTL,KC_ENT ,                                   KC_LEFT,KC_DOWN,KC_UP  ,KC_RGHT,_______,_______,
    _______,KC_ENT ,KC_LGUI,KC_LALT,KC_LCTL,KC_BSPC,                                   KC_LEFT,KC_DOWN,KC_UP  ,KC_RGHT,_______,_______,
    TO_LOL ,MY_UNDO,MY_CUT ,MY_COPY,MY_PSTE,KC_END ,_______,_______,   _______,_______,_______,KC_PGDN,KC_PGUP,_______,_______,_______,
                            _______,_______,_______,_______,_______,   _______,_______,_______,_______,_______
    ),

    [_RIGHT] = LAYOUT(
    _______,KC_F11 ,_______,KC_PGUP,KC_PGDN,_______,                                   _______,KC_MPRV,KC_MPLY,KC_MNXT,KC_F12 ,_______,
    _______,KC_BTN1,KC_BTN3,KC_BTN2,KC_BTN1,_______,                                   _______,KC_LCTL,KC_LALT,KC_LGUI,KC_LSFT,_______,
    _______,KC_F4  ,KC_F3  ,KC_F2  ,KC_F1  ,KC_F5  ,_______,_______,   _______,_______,KC_F6  ,KC_F10 ,KC_F9  ,KC_F8  ,KC_F7  ,_______,
                            _______,_______,_______,_______,_______,   _______,_______,_______,_______,_______
    ),

// ====================================================================================================================================
// LEAGUE OF LEGENDS
// ====================================================================================================================================
    [_LOL] = LAYOUT(
    KC_ESC ,KC_1   ,KC_2   ,KC_3   ,KC_4   ,KC_T   ,                                   _______,_______,_______,_______,_______,_______,
    KC_TAB ,KC_Q   ,KC_W   ,KC_E   ,KC_R   ,KC_G   ,                                   _______,TO_QWER,_______,_______,_______,_______,
    KC_Z   ,KC_A   ,KC_S   ,KC_D   ,KC_F   ,KC_V   ,KC_B   ,_______,   _______,_______,_______,_______,_______,_______,_______,KC_P   ,
                            _______,_______,KC_LALT,KC_SPC ,KC_LCTL,  _______,_______,_______,_______,_______
    ),
    [_LOL2] = LAYOUT(
    _______,_______,_______,_______,_______,_______,                                   _______,_______,_______,_______,_______,_______,
    _______,CTRL_Q ,CTRL_W ,CTRL_E ,CTRL_R ,_______,                                   _______,_______,_______,_______,_______,_______,
    TO_QWER,_______,_______,_______,_______,_______,_______,_______,   _______,_______,_______,_______,_______,_______,_______,_______,
                            _______,_______,_______,_______,_______,   _______,_______,_______,_______,_______
    ),

// ====================================================================================================================================
// VIM MODE
// ====================================================================================================================================
// ┌───────┬───────┬───────┬───────┬───────┬───────┐                                  ┌───────┬───────┬───────┬───────┬───────┬───────┐
// │       │       │       │       │       │       │                                  │       │       │       │       │       │       │
// │       │  ESC  │  C-→  │  C-→  │       │       │                                  │  C-c  │  C-z  │  <I>  │NEWLINE│ PASTE │       │
// ├───────┼───────┼───────┼───────┼───────┼───────┤                                  ├───────┼───────┼───────┼───────┼───────┼───────┤
// │       │       │       │       │       │       │                                  │       │       │       │       │       │       │
// │       │  <A>  │  <S>  │  DEL  │       │  GOTO │                                  │   ←   │   ↓   │   ↑   │   →   │       │       │
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┬───────┐  ┌───────┬───────┼───────┼───────┼───────┼───────┼───────┼───────┤
// │       │       │       │       │       │       │       │       │  │       │       │       │       │       │       │       │       │
// │       │       │  DEL  │  <C>  │<SHIFT>│  C-←  │       │       │  │       │       │  <F3> │       │       │       │  C-F  │       │
// └───────┴───────┴───────┼───────┼───────┼───────┼───────┼───────┤  ├───────┼───────┼───────┼───────┼───────┼───────┴───────┴───────┘
//                         │       │       │       │       │       │  │       │       │       │       │       │
//                         │       │       │       │       │       │  │       │       │       │       │       │
//                         └───────┴───────┴───────┴───────┴───────┘  └───────┴───────┴───────┴───────┴───────┘


// ====================================================================================================================================
// LOWER LAYER: NUMBER ROW
// ====================================================================================================================================
// Number row layout from: https://youtu.be/yiwUjLaebuw?t=185
//
// ┌───────┬───────┬───────┬───────┬───────┬───────┐                                  ┌───────┬───────┬───────┬───────┬───────┬───────┐
// │       │       │       │       │       │       │                                  │       │       │       │       │       │       │
// │       │   <   │   [   │   {   │   (   │   '   │                                  │   "   │   )   │   }   │   ]   │   >   │       │
// ├───────┼───────┼───────┼───────┼───────┼───────┤                                  ├───────┼───────┼───────┼───────┼───────┼───────┤
// │       │   $   │   #   │   @   │   !   │   %   │                                  │   ^   │   )   │   (   │   *   │   &   │       │
// │       │   4   │   3   │   2   │   1   │   5   │                                  │   6   │   0   │   9   │   8   │   7   │       │
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┬───────┐  ┌───────┬───────┼───────┼───────┼───────┼───────┼───────┼───────┤
// │       │       │       │       │       │       │       │       │  │       │       │       │       │       │       │       │       │
// │       │   ~   │   `   │   \   │   |   │       │       │       │  │       │       │       │   -   │   _   │   =   │   +   │       │
// └───────┴───────┴───────┼───────┼───────┼───────┼───────┼───────┤  ├───────┼───────┼───────┼───────┼───────┼───────┴───────┴───────┘
//                         │       │       │       │       │       │  │       │       │       │       │       │
//                         │       │       │       │       │       │  │       │       │       │       │       │
//                         └───────┴───────┴───────┴───────┴───────┘  └───────┴───────┴───────┴───────┴───────┘
    [_NUMBER] = LAYOUT(
    _______,KC_LT  ,KC_LBRC,KC_LCBR,KC_LPRN,KC_QUOT,                                   KC_DQUO,KC_RPRN,KC_RCBR,KC_RBRC,KC_GT  ,_______,
    _______,KC_4   ,KC_3   ,KC_2   ,KC_1   ,KC_5   ,                                   KC_6   ,KC_0   ,KC_9   ,KC_8   ,KC_7   ,_______,
    _______,KC_TILD,KC_GRV ,KC_BSLS,KC_PIPE,_______,_______,_______,   _______,_______,_______,KC_MINS,KC_UNDS, KC_EQL,KC_PLUS,_______,
                            _______,_______,_______,_______,_______,   _______,_______,_______,_______,_______
    ),

// ┌───────┬───────┬───────┬───────┬───────┬───────┐                                  ┌───────┬───────┬───────┬───────┬───────┬───────┐
// │       │       │   (   │   *   │   &   │       │                                  │       │       │       │       │       │       │
// │       │   ~   │   9   │   8   │   7   │       │                                  │       │   (   │   )   │   \   │   |   │SCRLLCK│
// ├───────┼───────┼───────┼───────┼───────┼───────┤                                  ├───────┼───────┼───────┼───────┼───────┼───────┤
// │       │   )   │   #   │   @   │   !   │       │                                  │       │       │       │       │       │       │
// │       │   0   │   3   │   2   │   1   │       │                                  │       │   {   │   }   │   -   │   _   │CAPSLCK│
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┬───────┐  ┌───────┬───────┼───────┼───────┼───────┼───────┼───────┼───────┤
// │       │       │   ^   │   %   │   $   │       │       │       │  │       │       │       │       │       │       │       │       │
// │       │   `   │   6   │   5   │   4   │       │       │       │  │       │       │       │   [   │   ]   │   =   │   +   │NUMLOCK│
// └───────┴───────┴───────┼───────┼───────┼───────┼───────┼───────┤  ├───────┼───────┼───────┼───────┼───────┼───────┴───────┴───────┘
//                         │       │       │       │       │       │  │       │       │       │       │       │
//                         │       │       │       │       │       │  │       │       │       │       │       │
//                         └───────┴───────┴───────┴───────┴───────┘  └───────┴───────┴───────┴───────┴───────┘
    // TODO: Experiment with a number/nav hybrid layer
    [_NUMBER_TEST] = LAYOUT(
    _______,KC_TILD,KC_9   ,KC_8   ,KC_7   ,_______,                                   _______,KC_LPRN,KC_RPRN,KC_BSLS,KC_PIPE,KC_SLCK,
    _______,KC_0   ,KC_3   ,KC_2   ,KC_1   ,_______,                                   _______,KC_LCBR,KC_RCBR,KC_MINS,KC_UNDS,KC_CLCK,
    _______,KC_GRV ,KC_6   ,KC_5   ,KC_4   ,_______,_______,_______,   _______,_______,_______,KC_LBRC,KC_RBRC,KC_EQL ,KC_PLUS,KC_NLCK,
                            _______,_______,_______,_______,_______,   KC_LSFT,KC_LCTL,KC_LALT,_______,_______
    ),

// Raise Layer: Number keys, media, navigation
//  [_RAISE] = LAYOUT(
//    _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
//    _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLU,                                     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
//    _______, _______, _______, _______, KC_MUTE, KC_VOLD, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, _______,
//                               _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//  ),

// TESmart 4x2 KVM Keyboard Shortcuts
// - SL = Scroll Lock.
// - SL+SL+F1: Switches Scroll Lock to Right Control. (Good for Mac users that don't have a Scroll Lock key.)
// - R-Ctrl + R-Ctrl + F1: Switches Right Control to Scroll Lock.
// - SL+SL+F2: Toggle keyboard/mouse "pass through" mode.
// - SL+SL+F3: Beeps once if keyboard/mouse is in emulation mode and twice for pass through mode.
// - SL+SL+F11: Toggle buzzer.
// - Display Mode 1.
//   - SL+SL+1: Select input source 1.
//   - SL+SL+2: Select input source 2.
// - Display Mode 2.
//   - R-Alt + R-Alt: Change active computer.
//   - SL+SL+3: Focus on input source 1.
//   - SL+SL+4: Focus on input source 2.


// ====================================================================================================================================
// RGB
// ====================================================================================================================================
// ┌───────┬───────┬───────┬───────┬───────┬───────┐                                  ┌───────┬───────┬───────┬───────┬───────┬───────┐
// │       │       │       │       │       │       │                                  │       │       │       │       │       │       │
// │       │       │ RGB 9 │ RGB 8 │ RGB 7 │       │                                  │       │  BRI+ │  BRI- │       │       │       │
// ├───────┼───────┼───────┼───────┼───────┼───────┤                                  ├───────┼───────┼───────┼───────┼───────┼───────┤
// │       │       │       │       │       │       │                                  │       │       │       │       │       │       │
// │       │ ON/OFF│ RGB 3 │ RGB 2 │ RGB 1 │       │                                  │       │  HUE+ │  HUE- │ MODE+ │ MODE- │       │
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┬───────┐  ┌───────┬───────┼───────┼───────┼───────┼───────┼───────┼───────┤
// │       │       │       │       │       │       │       │       │  │       │       │       │       │       │       │       │       │
// │       │       │ RGB 6 │ RGB 5 │ RGB 4 │       │       │       │  │       │       │       │  SAT+ │  SAT- │  SPD+ │  SPD- │       │
// └───────┴───────┴───────┼───────┼───────┼───────┼───────┼───────┤  ├───────┼───────┼───────┼───────┼───────┼───────┴───────┴───────┘
//                         │       │       │       │       │       │  │       │       │       │       │       │
//                         │       │       │       │       │       │  │       │       │       │       │       │
//                         └───────┴───────┴───────┴───────┴───────┘  └───────┴───────┴───────┴───────┴───────┘
    [_RGB] = LAYOUT(
    _______,_______,RGB_M_T,RGB_M_G,RGB_M_X,_______,                                   _______,RGB_VAI,RGB_VAD,_______,_______,_______,
    _______,RGB_TOG,RGB_M_R,RGB_M_B,RGB_M_P,_______,                                   _______,RGB_HUI,RGB_HUD,RGB_MOD,RGB_RMOD,_______,
    _______,_______,RGB_M_K,RGB_M_SN,RGB_M_SW,_______,_______,_______, _______,_______,_______,RGB_SAI,RGB_SAD,RGB_SPI,RGB_SPD,_______,
                            _______,_______,_______,_______,_______,   _______,_______,_______,_______,_______
    ),
};

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

static void render_kyria_logo(void) {
    static const char PROGMEM kyria_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
        0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
    };
    oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
}

static void render_qmk_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(qmk_logo, false);
}

static void render_status(void) {
    // Host Keyboard Layer Status
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            rgblight_enable_noeeprom();
            rgblight_sethsv_noeeprom(HSV_RED);
            break;
            break;
        case _NUMBER:
        case _NUMBER_TEST:
            rgblight_enable_noeeprom();
            rgblight_sethsv_noeeprom(HSV_BLUE);
            break;
        case _LEFT:
            rgblight_enable_noeeprom();
            rgblight_sethsv_noeeprom(HSV_GREEN);
            break;
        case _RIGHT:
            rgblight_enable_noeeprom();
            rgblight_sethsv_noeeprom(HSV_GREEN);
            break;
        case _LOL:
            rgblight_enable_noeeprom();
            rgblight_sethsv_noeeprom(HSV_PURPLE);
            break;
        default:
            break;
    }

    // TODO: Uncomment this to get more memory
    return;

    // QMK Logo and version information
    render_qmk_logo();
    oled_write_P(PSTR("Kyria rev1.0\n\n"), false);

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _NUMBER:
            oled_write_P(PSTR("Number\n"), false);
            break;
        case _RGB:
            oled_write_P(PSTR("Adjust\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }

    // Host Keyboard LED Status
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_kyria_logo();
    }
}
#endif


// =============================================================================
// VIM
// =============================================================================
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case MY_UNDO:
            if(record->event.pressed) {
                tap_code16(LCTL(KC_Z));
            }
            return false;
        case MY_CUT:
            if(record->event.pressed) {
                tap_code16(LCTL(KC_X));
            }
            return false;
        case MY_COPY:
            if(record->event.pressed) {
                tap_code16(LCTL(KC_C));
            }
            return false;
        case MY_PSTE:
            if(record->event.pressed) {
                tap_code16(LCTL(KC_V));
            }
            return false;

        case KEY_HOLD_S:
            if(record->event.pressed) {
                tap_code(KC_S);
                oled_write_P(PSTR("S\n"), false);
            }
            return false;

        case VIM_ESC:
            if(record->event.pressed) {
                vim.enabled = true;
            }
            return true;
    }

    if(!process_mod_key(keycode, record)) return false;

    if(vim.enabled)
        return process_vim_key(keycode, record);

    return true;
}


bool process_mod_key(uint16_t keycode, keyrecord_t *record) {

    // Check mod key
    if(keycode == KEY_ENABLE_MOD) {
        if(record->event.pressed) {
            mod_enable = MOD_ENABLE;
        }
        else {
            if(mod_enable & MOD_GUI  ) RELEASE_GUI();
            if(mod_enable & MOD_ALT  ) RELEASE_ALT();
            if(mod_enable & MOD_CTRL ) RELEASE_CTRL();
            if(mod_enable & MOD_SHIFT) RELEASE_SHIFT();
            mod_enable = 0;
        }
        return false;
    }

    if(!(mod_enable & MOD_ENABLE)) return true;

    if(mod_enable == MOD_ENABLE) {
        switch(keycode) {
            case KC_Z:
            case KC_X:
            case KC_C:
            case KC_V:
                if(record->event.pressed) {
                    tap_code16(LCTL(keycode));
                }
                return false;

            case KC_F:
                if(record->event.pressed) {
                    HOLD_CTRL();
                    mod_enable |= MOD_CTRL;
                }
                return false;
            case KC_D:
                if(record->event.pressed) {
                    HOLD_ALT();
                    mod_enable |= MOD_ALT;
                }
                return false;
            case KC_S:
                if(record->event.pressed) {
                    HOLD_GUI();
                    mod_enable |= MOD_GUI;
                }
                return false;
            case KC_A:
                if(record->event.pressed) {
                    HOLD_SHIFT();
                    mod_enable |= MOD_SHIFT;
                }
                return false;
        }
    }

    return true;
}


// TODO: Add process_mod_key() function
// Basically it will hold down any mod keys until the special key is released.


bool process_vim_key(uint16_t keycode, keyrecord_t *record) {
    // TODO: Add this later
    return true;

    // Nothing fancy in here
    if(!record->event.pressed) return true;

    switch(keycode) {
        // Enter 'insert' mode
        case KC_ESC:
        case KC_A:
        case KC_I:
        case KC_O:
        case KC_C:
            vim.enabled = false;
            if(vim.visual) {
                vim.visual = false;
                if(keycode == KC_C)
                    tap_code16(LCTL(KC_X));
            }
            if(keycode == KC_A) {
                tap_code(KC_RIGHT);
            }
            else if(keycode == KC_O) {
                tap_code(KC_END);
                tap_code(KC_ENTER);
            }
            break;

        // Navigation
        case KC_G:
            vim.set_go = true;
            break;
        case KC_H:
            press_key(vim.go ? KC_HOME : KC_LEFT, record, MOD_VIM_VISUAL);
            break;
        case KC_J:
            press_key(vim.go ? KC_PGDN : KC_DOWN, record, MOD_VIM_VISUAL);
            break;
        case KC_K:
            press_key(vim.go ? KC_PGUP : KC_UP, record, MOD_VIM_VISUAL);
            break;
        case KC_L:
            press_key(vim.go ? KC_END : KC_RIGHT, record, MOD_VIM_VISUAL);
            break;
        case KC_W:
            press_key(KC_RIGHT, record, MOD_CTRL | MOD_VIM_VISUAL);
            break;
        case KC_E:
            press_key(KC_RIGHT, record, MOD_CTRL | MOD_VIM_VISUAL);
            break;
        case KC_B:
            press_key(KC_LEFT, record, MOD_CTRL | MOD_VIM_VISUAL);
            break;

        // Paste
        case KC_P:
            if(vim.visual) {
                vim.visual = false;
                RELEASE_SHIFT();
            }
            tap_code16(LCTL(KC_V));
            break;

        // Copy
        case KC_Y:
            if(vim.visual) {
                vim.visual = false;
                tap_code16(LCTL(KC_C));
            }
            else {
                // TODO: Implement
            }
            break;

        // Delete (cut)
        case KC_X:
            if(vim.visual) {
                vim.visual = false;
                tap_code16(LCTL(KC_X));
            }
            else {
                tap_code(KC_DEL);
            }
            break;
        case KC_D:
            if(vim.visual) {
                vim.visual = false;
                tap_code16(LCTL(KC_X));
            }
            else {
                // TODO: Implement
            }
            break;

        // Visual
        case KC_V:
            if(vim.visual) {
                vim.visual = false;
            }
            else {
                vim.visual = true;
            }
            break;

        // Undo
        case KC_U:
            tap_code16(LCTL(KC_Z));
            break;

        // Escape
        case KC_Q:
            if(vim.visual) {
                vim.visual = false;
            }
            tap_code(KC_ESC);
            break;

        // Find
        case KC_SLSH:
            tap_code16(LCTL(KC_F));
            break;
        case KC_N:
            tap_code(KC_F3);
            break;

        default:
            return true;
    }
    vim.go = vim.set_go;
    vim.set_go = false;
    return false;
}

modifier_t get_modifiers(void) {
    modifier_t mod_state;
    uint8_t qmk_mod_state;
    qmk_mod_state = get_mods();

    if(qmk_mod_state & MOD_MASK_SHIFT) mod_state |= MOD_SHIFT;
    if(qmk_mod_state & MOD_MASK_CTRL)  mod_state |= MOD_CTRL;
    if(qmk_mod_state & MOD_MASK_ALT)   mod_state |= MOD_ALT;
    if(qmk_mod_state & MOD_MASK_GUI)   mod_state |= MOD_GUI;
    mod_state |= mod_enable | MOD_ENABLE;
    return mod_state;
}

void press_key(uint16_t keycode, keyrecord_t *record, modifier_t modifier) {
    if(modifier & MOD_SHIFT) HOLD_SHIFT();
    if(modifier & MOD_CTRL ) HOLD_CTRL();
    if(modifier & MOD_ALT  ) HOLD_ALT();
    if(modifier & MOD_GUI  ) HOLD_GUI();
    tap_code(keycode);
    if(modifier & MOD_GUI  ) RELEASE_GUI();
    if(modifier & MOD_ALT  ) RELEASE_ALT();
    if(modifier & MOD_CTRL ) RELEASE_CTRL();
    if(modifier & MOD_SHIFT) RELEASE_SHIFT();
}


// =============================================================================
// COMBOS
// =============================================================================
void process_combo_event(uint16_t combo_index, bool pressed) {
    if(!pressed) return;

    switch(combo_index) {
        case COMBO_SELECT_ROW:
            tap_code(KC_HOME);
            HOLD_SHIFT();
            tap_code(KC_END);
            RELEASE_SHIFT();
            //tap_code(KC_BSPC);
            break;
    }
}

//void process_mod_combo(uint16_t combo_index, bool pressed) {
//    if(!pressed) return;
//
//    switch(combo_index) {
//        case COMBO_SELECT_ROW:
//            tap_code(KC_HOME);
//            HOLD_SHIFT();
//            tap_code(KC_END);
//            RELEASE_SHIFT();
//            //tap_code(KC_BSPC);
//            break;
//        }
//    }
//}


//uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
//    switch(keycode) {
//        case THUM_L2:
//            return 0;
//        default:
//            return TAPPING_TERM;
//    }
//}

//bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
//    switch(keycode) {
//        case THUM_L2:
//            return true;
//        default:
//            return false;
//    }
//}

#ifdef ENCODER_ENABLE
//#define ENCODER_MOUSE
bool encoder_update_user(uint8_t index, bool clockwise) {
#ifdef ENCODER_MOUSE
    // Left knob
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_MS_L);
        } else {
            tap_code(KC_MS_R);
        }
    }

    // Right knob
    else if (index == 1) {
        if (clockwise) {
            tap_code(KC_MS_U);
        } else {
            tap_code(KC_MS_D);
        }
    }
#else
    // Left knob
    if (index == 0) {
        if (clockwise) {
            //tap_code(KC_PGUP);
            for(int i = 0; i < 12; i++) {
                tap_code(KC_UP);
            }
        } else {
            //tap_code(KC_PGDN);
            for(int i = 0; i < 12; i++) {
                tap_code(KC_DOWN);
            }
        }
    }

    // Right knob
    else if (index == 1) {
        if (clockwise) {
            tap_code(KC_VOLD);
        } else {
            tap_code(KC_VOLU);
        }
    }
#endif
    return false;
}
#endif

// vim: ts=4 et

