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
#define HOLD_ALT()        register_mods(MOD_BIT(KC_LALT))
#define RELEASE_ALT()   unregister_mods(MOD_BIT(KC_LALT))
#define HOLD_CTRL()       register_mods(MOD_BIT(KC_LCTRL))
#define RELEASE_CTRL()  unregister_mods(MOD_BIT(KC_LCTRL))
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

#define THUM_L1 MT(MOD_LCTL, MY_ESC)
#define THUM_L2 MT(MOD_LALT, KC_ENT)
#define THUM_L3 LT(_LOWER, KC_TAB)
#define THUM_L4 KC_LGUI
#define THUM_L5 KC_MUTE
#define THUM_L6 LT(_RAISE, KC_PGDN)
#define THUM_L7 LT(_LOWER, KC_PGUP)
#define THUM_R1 LT(_RAISE, KC_BSPC)
#define THUM_R2 MT(MOD_LSFT, KC_SPC)
#define THUM_R3 LT(_LOWER, KC_DEL)
#define THUM_R4 KC_TAB
#define THUM_R5 KC_SLCK
#define THUM_R6 LT(_RAISE, KC_HOME)
#define THUM_R7 LT(_LOWER, KC_END)

#define PINK_L1 KC_TAB
//#define PINK_L2 MT(MOD_LCTL, KC_BSPC)
#define PINK_L2 TO(_RAISE)
#define PINK_L3 KC_LSFT

bool vim_key(uint16_t keycode, keyrecord_t *record);


enum layers {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST
};


// =============================================================================
// VIM
// =============================================================================
enum custom_keycodes {
    MY_ESC = SAFE_RANGE,
    VIM_A,
    VIM_B,
    VIM_C,
    VIM_D,
    VIM_E,
    VIM_F,
    VIM_G,
    VIM_H,
    VIM_I,
    VIM_J,
    VIM_K,
    VIM_L,
    VIM_M,
    VIM_N,
    VIM_O,
    VIM_P,
    VIM_Q,
    VIM_R,
    VIM_S,
    VIM_T,
    VIM_U,
    VIM_V,
    VIM_W,
    VIM_X,
    VIM_Y,
    VIM_Z
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// ====================================================================================================================================
// BASE LAYER: QWERTY
// ====================================================================================================================================
// ┌───────┬───────┬───────┬───────┬───────┬───────┐                                  ┌───────┬───────┬───────┬───────┬───────┬───────┐
// │       │   Q   │   W   │   E   │   R   │   T   │                                  │   Y   │   U   │   I   │   O   │   P   │   |   │
// │  TAB  │       │       │       │       │       │                                  │       │       │       │       │       │   \   │
// ├───────┼───────┼───────┼───────┼───────┼───────┤                                  ├───────┼───────┼───────┼───────┼───────┼───────┤
// │       │   A   │   S   │   D   │   F   │   G   │                                  │   H   │   J   │   K   │   L   │   :   │   "   │
// │  NAV  │       │       │       │       │       │                                  │       │       │       │       │   ;   │   '   │
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┬───────┐  ┌───────┬───────┼───────┼───────┼───────┼───────┼───────┼───────┤
// │       │   Z   │   X   │   C   │   V   │   B   │ LOWER │ RAISE │  │ RAISE │ LOWER │   N   │   M   │   <   │   >   │   ?   │   _   │
// │  NUM  │       │       │       │       │       │  PGUP │ PGDWN │  │  HOME │  END  │       │       │   ,   │   .   │   /   │   -   │
// └───────┴───────┴───────┼───────┼───────┼───────┼───────┼───────┤  ├───────┼───────┼───────┼───────┼───────┼───────┴───────┴───────┘
//                         │  VOL  │  GUI  │ LOWER │  ALT  │  CTRL │  │ RAISE │ SHIFT │ LOWER │       │ SCROLL│
//                         │  MUTE │       │  TAB  │ ENTER │  ESC  │  │ BKSPC │ SPACE │  DEL  │  TAB  │SCRLOCK│
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

// ====================================================================================================================================
// LOWER LAYER: NUMBER ROW
// ====================================================================================================================================
// Number row layout from: https://youtu.be/yiwUjLaebuw?t=185
//
// ┌───────┬───────┬───────┬───────┬───────┬───────┐                                  ┌───────┬───────┬───────┬───────┬───────┬───────┐
// │       │       │       │       │       │       │                                  │       │       │       │       │       │       │
// │       │   <   │   [   │   {   │   (   │       │                                  │       │   )   │   }   │   ]   │   >   │       │
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
    _______,  KC_LT,KC_LBRC,KC_LCBR,KC_LPRN,_______,                                   _______,KC_RPRN,KC_RCBR,KC_RBRC,  KC_GT,_______,
    _______,   KC_4,   KC_3,   KC_2,   KC_1,   KC_5,                                      KC_6,   KC_0,   KC_9,   KC_8,   KC_7,_______,
    _______,KC_TILD, KC_GRV,KC_BSLS,KC_PIPE,_______,_______,_______,   _______,_______,_______,KC_MINS,KC_UNDS, KC_EQL,KC_PLUS,_______,
                            _______,_______,_______,_______,_______,   _______,_______,_______,_______,_______
    ),


// =============================================================================
// RAISE LAYER: NAVIGATION
// =============================================================================
// ┌───────┬───────┬───────┬───────┬───────┬───────┐                                  ┌───────┬───────┬───────┬───────┬───────┬───────┐
// │       │       │       │       │       │       │                                  │       │       │       │       │       │       │
// │       │       │       │       │       │       │                                  │       │       │  BASE │       │       │       │
// ├───────┼───────┼───────┼───────┼───────┼───────┤                                  ├───────┼───────┼───────┼───────┼───────┼───────┤
// │       │       │       │       │       │       │                                  │       │       │       │       │       │       │
// │       │       │       │       │       │       │                                  │   ←   │   ↓   │   ↑   │   →   │       │       │
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┬───────┐  ┌───────┬───────┼───────┼───────┼───────┼───────┼───────┼───────┤
// │       │       │       │       │       │       │       │       │  │       │       │       │       │       │       │       │       │
// │       │       │       │       │       │  C-←  │       │       │  │       │       │       │       │       │       │  C-F  │       │
// └───────┴───────┴───────┼───────┼───────┼───────┼───────┼───────┤  ├───────┼───────┼───────┼───────┼───────┼───────┴───────┴───────┘
//                         │       │       │       │       │       │  │       │       │       │       │       │
//                         │       │       │       │       │       │  │       │       │       │       │       │
//                         └───────┴───────┴───────┴───────┴───────┘  └───────┴───────┴───────┴───────┴───────┘
    [_RAISE] = LAYOUT(
    _______,  VIM_Q,  VIM_W,  VIM_E,  VIM_R,  VIM_T,                                     VIM_Y,  VIM_U,  VIM_I,  VIM_O,  VIM_P,_______,
    _______,  VIM_A,  VIM_S,  VIM_D,  VIM_F,  VIM_G,                                     VIM_H,  VIM_J,  VIM_K,  VIM_L,_______,_______,
    _______,  VIM_Z,  VIM_X,  VIM_C,  VIM_V,  VIM_B,_______,_______,   _______,_______,  VIM_N,  VIM_M,_______,_______,_______,_______,
                            _______,_______,_______,_______,_______,   _______,_______,_______,_______,_______
    ),


/*
 * Raise Layer: Number keys, media, navigation
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |   1  |  2   |  3   |  4   |  5   |                              |  6   |  7   |  8   |  9   |  0   |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      | Prev | Play | Next | VolUp|                              | Left | Down | Up   | Right|      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      | Mute | VolDn|      |      |  |      |      | MLeft| Mdown| MUp  |MRight|      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
    [_RAISE] = LAYOUT(
      _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
      _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLU,                                       VIM_H, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
      _______, _______, _______, _______, KC_MUTE, KC_VOLD, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
 */

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
        case MY_ESC:
            if(record->event.pressed) {
                layer_on(0);
                tap_code(KC_ESC);
            }
            return true;
    }

    return vim_key(keycode, record);
}

bool vim_key(uint16_t keycode, keyrecord_t *record) {
    // Nothing fancy in here
    if(!record->event.pressed) return true;

    switch(keycode) {
        // Enter 'normal' mode
        case VIM_I:
            layer_on(_QWERTY);
            break;
        case VIM_O:
            tap_code(KC_END);
            tap_code(KC_ENTER);
            layer_on(_QWERTY);
            break;

        // Navigation
        case VIM_H:
            tap_code(KC_LEFT);
            break;
        case VIM_J:
            tap_code(KC_DOWN);
            break;
        case VIM_K:
            tap_code(KC_UP);
            break;
        case VIM_L:
            tap_code(KC_RIGHT);
            break;
        case VIM_W:
            CTRL_TAP(KC_RIGHT);
            break;
        case VIM_E:
            CTRL_TAP(KC_RIGHT);
            break;
        case VIM_B:
            CTRL_TAP(KC_LEFT);
            break;

        // Cut
        case VIM_X:
            tap_code(KC_DEL);
            break;
    }
    return true;
}


#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_PGUP);
        } else {
            tap_code(KC_PGDN);
        }
    }
}
#endif
