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

#define CTRL_TAP(kc) { \
    register_mods(MOD_BIT(KC_LCTRL)); \
    tap_code(kc); \
    unregister_mods(MOD_BIT(KC_LCTRL)); \
}


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


#define THUM_L1 MO(_LEFT)
//#define THUM_L1 LT(_LEFT, KC_ESC)
//#define THUM_L1 MT(MOD_LCTL, KC_ESC)
#define THUM_L2 MO(_LOWER)
//#define THUM_L2 LT(_LOWER, KC_ENT)
//#define THUM_L2 MT(MOD_LALT, KC_ENT)
#define THUM_L3 LT(_RIGHT, KC_DEL)
//#define THUM_L3 LT(_LOWER, KC_DEL)
#define THUM_L4 KC_LGUI
#define THUM_L5 KC_MUTE
#define THUM_L6 LT(_RAISE, KC_PGDN)
#define THUM_L7 LT(_LOWER, KC_PGUP)
#define THUM_R1 MT(MOD_LSFT, KC_BSPC)
#define THUM_R2 KC_SPC
#define THUM_R3 MO(_RIGHT)
//#define THUM_R3 LT(_RAISE, KC_DEL)
//#define THUM_R3 LT(_LOWER, KC_DEL)
#define THUM_R4 MT(MOD_RGUI, KC_TAB)
#define THUM_R5 KC_SLCK
#define THUM_R6 LT(_RAISE, KC_HOME)
#define THUM_R7 LT(_LOWER, KC_END)

//#define THUM_L4 KC_LGUI
//#define THUM_R1 MT(MOD_LSFT, KC_BSPC)
//#define THUM_R2 KC_SPC
//#define THUM_R3 LT(_RIGHT, KC_DEL)
//#define THUM_R4 MT(MOD_RGUI, KC_TAB)

#define PINK_L1 KC_TAB
//#define PINK_L2 MT(MOD_LCTL, KC_BSPC)
//#define PINK_L2 TO(_RAISE)
#define PINK_L2 VIM_ESC
#define PINK_L3 KC_LSFT

enum layers {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST,
    _LEFT,
    _RIGHT
};

enum combos {
    CO_QWER
};

typedef enum {
    MOD_SHIFT = 0b0001,
    MOD_CTRL  = 0b0010,
    MOD_ALT   = 0b0100,
    MOD_GUI   = 0b1000
} modifier_t;

void press_key(uint16_t keycode, keyrecord_t *record, modifier_t modifier);


// =============================================================================
// VIM
// =============================================================================
#define VIM_EXIT_VISUAL() { \
    vim.visual = false; \
    RELEASE_SHIFT(); \
}
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
    VIM_ESC = SAFE_RANGE
};

static vim_state_t vim = {false, false, false, false, VIM_NONE};


// =============================================================================
// COMBOS
// =============================================================================
// config.h: #define COMBO_COUNT <count>
// rules.mk: COMBO_ENABLE = yes
const uint16_t PROGMEM qwer_combo[] = {KC_Q, KC_W, KC_E, KC_R, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
    [CO_QWER] = COMBO(qwer_combo, KC_TAB)
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
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
// │       │   Z   │   X   │   C   │   V   │   B   │ LOWER │ RAISE │  │ RAISE │ LOWER │   N   │   M   │   <   │   >   │   ?   │   _   │
// │  NUM  │       │       │       │       │       │  PGUP │ PGDWN │  │  HOME │  END  │       │       │   ,   │   .   │   /   │   -   │
// └───────┴───────┴───────┼───────┼───────┼───────┼───────┼───────┤  ├───────┼───────┼───────┼───────┼───────┼───────┴───────┴───────┘
//                         │  VOL  │  GUI  │ LOWER │  ALT  │  CTRL │  │ SHIFT │       │ RAISE │       │ SCROLL│
//                         │  MUTE │       │  DEL  │ ENTER │  ESC  │  │ BKSPC │ SPACE │  DEL  │  TAB  │SCRLOCK│
//                         └───────┴───────┴───────┴───────┴───────┘  └───────┴───────┴───────┴───────┴───────┘
    [_QWERTY] = LAYOUT(
    // TODO: Figure out why this doesn't work
//  PINK_L1,_______________QWERTY_L1_______________,                                   _______________QWERTY_R1_______________,KC_PIPE,
//  PINK_L2,_______________QWERTY_L2_______________,                                   _______________QWERTY_R2_______________,KC_QUOT,
//  PINK_L3,_______________QWERTY_L3_______________,THUM_L7,THUM_L6,   THUM_R6,THUM_R7,_______________QWERTY_R3_______________,KC_MINS,
    PINK_L1,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                                      KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,KC_PIPE,
    PINK_L2,   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                                      KC_H,   KC_J,   KC_K,   KC_L,KC_SCLN,KC_QUOT,
    PINK_L3,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,THUM_L7,THUM_L6,   THUM_R6,THUM_R7,   KC_N,   KC_M,KC_COMM, KC_DOT,KC_SLSH,KC_MINS,
                            THUM_L5,THUM_L4,THUM_L3,THUM_L2,THUM_L1,   THUM_R1,THUM_R2,THUM_R3,THUM_R4,THUM_R5
    ),

    [_LEFT] = LAYOUT(
    KC_TAB ,KC_ESC ,KC_DEL ,KC_PGUP,KC_PGDN,KC_HOME,                                   _______,_______,_______,_______,_______,_______,
  //_______,OS_SFT ,OS_GUI ,OS_ALT ,OS_CTL ,KC_ENT ,                                   KC_LEFT,KC_DOWN,KC_UP  ,KC_RGHT,_______,_______,
    _______,KC_LSFT,KC_LGUI,KC_LALT,KC_LCTL,KC_ENT ,                                   KC_LEFT,KC_DOWN,KC_UP  ,KC_RGHT,_______,_______,
    _______,KC_UNDO,KC_CUT ,KC_COPY,KC_PSTE,KC_END ,_______,_______,   _______,_______,_______,KC_PGDN,KC_PGUP,_______,_______,_______,
                            _______,_______,_______,_______,_______,   _______,_______,_______,_______,_______

    ),

    [_RIGHT] = LAYOUT(
    _______,KC_F11 ,_______,KC_PGUP,KC_PGDN,_______,                                   _______,_______,_______,_______,KC_F12 ,_______,
    _______,KC_BTN1,KC_BTN3,KC_BTN2,KC_BTN1,_______,                                   _______,KC_LCTL,KC_LALT,KC_LGUI,KC_LSFT,_______,
    _______,KC_F4  ,KC_F3  ,KC_F2  ,KC_F1  ,KC_F5  ,_______,_______,   _______,_______,KC_F6  ,KC_F10 ,KC_F9  ,KC_F8  ,KC_F7  ,_______,
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
    [_LOWER] = LAYOUT(
    _______,KC_LT  ,KC_LBRC,KC_LCBR,KC_LPRN,KC_QUOT,                                   KC_DQUO,KC_RPRN,KC_RCBR,KC_RBRC,KC_GT  ,_______,
    _______,KC_4   ,KC_3   ,KC_2   ,KC_1   ,KC_5   ,                                   KC_6   ,KC_0   ,KC_9   ,KC_8   ,KC_7   ,_______,
    _______,KC_TILD, KC_GRV,KC_BSLS,KC_PIPE,_______,_______,_______,   _______,_______,_______,KC_MINS,KC_UNDS, KC_EQL,KC_PLUS,_______,
                            _______,_______,_______,_______,_______,   _______,_______,_______,_______,_______
    ),


//
// Raise Layer: Number keys, media, navigation
//
// ,-------------------------------------------.                              ,-------------------------------------------.
// |        |   1  |  2   |  3   |  4   |  5   |                              |  6   |  7   |  8   |  9   |  0   |        |
// |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
// |        |      | Prev | Play | Next | VolUp|                              | Left | Down | Up   | Right|      |        |
// |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
// |        |      |      |      | Mute | VolDn|      |      |  |      |      | MLeft| Mdown| MUp  |MRight|      |        |
// `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//                        |      |      |      |      |      |  |      |      |      |      |      |
//                        |      |      |      |      |      |  |      |      |      |      |      |
//                        `----------------------------------'  `----------------------------------'
    [_RAISE] = LAYOUT(
      _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
      _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLU,                                     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
      _______, _______, _______, _______, KC_MUTE, KC_VOLD, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Adjust Layer: Function keys, RGB
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        | F1   |  F2  | F3   | F4   | F5   |                              | F6   | F7   |  F8  | F9   | F10  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | TOG  | SAI  | HUI  | VAI  | MOD  |                              |      |      |      | F11  | F12  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      | SAD  | HUD  | VAD  | RMOD |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_ADJUST] = LAYOUT(
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
      _______, RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD,                                     _______, _______, _______, KC_F11,  KC_F12,  _______,
      _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD,_______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

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
    // QMK Logo and version information
    render_qmk_logo();
    oled_write_P(PSTR("Kyria rev1.0\n\n"), false);

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise\n"), false);
            break;
        case _ADJUST:
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
        case VIM_ESC:
            if(record->event.pressed) {
                vim.enabled = true;
            }
            return true;
    }

    if(vim.enabled)
        return process_vim_key(keycode, record);

    return true;
}

bool process_vim_key(uint16_t keycode, keyrecord_t *record) {
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
                    CTRL_TAP(KC_X);
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
            CTRL_TAP(KC_V);
            break;

        // Copy
        case KC_Y:
            if(vim.visual) {
                vim.visual = false;
                CTRL_TAP(KC_C);
            }
            else {
                // TODO: Implement
            }
            break;

        // Delete (cut)
        case KC_X:
            if(vim.visual) {
                vim.visual = false;
                CTRL_TAP(KC_X);
            }
            else {
                tap_code(KC_DEL);
            }
            break;
        case KC_D:
            if(vim.visual) {
                vim.visual = false;
                CTRL_TAP(KC_X);
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
            CTRL_TAP(KC_Z);
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
            CTRL_TAP(KC_F);
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


#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    // Left knob
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }

    // Right knob
    else if (index == 1) {
        if (clockwise) {
            tap_code(KC_PGUP);
        } else {
            tap_code(KC_PGDN);
        }
    }
}
#endif

