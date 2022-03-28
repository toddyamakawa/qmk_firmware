/*
Copyright 2020 Cole Smith <cole@boadsource.xyz>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

enum layers {
    _QWERTY,
    _NUMBER,
    _LOWER,
    _BLANK,
};

#define MO_NUM MO(_NUMBER)
#define LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// ====================================================================================
// BASE LAYER: QWERTY
// ====================================================================================
// ┌───────┬───────┬───────┬───────┬───────┐  ┌───────┬───────┬───────┬───────┬───────┐
// │   Q   │   W   │   E   │   R   │   T   │  │   Y   │   U   │   I   │   O   │   P   │
// │       │       │       │       │       │  │       │       │       │       │       │
// ├───────┼───────┼───────┼───────┼───────┤  ├───────┼───────┼───────┼───────┼───────┤
// │   A   │   S   │   D   │   F   │   G   │  │   H   │   J   │   K   │   L   │   "   │
// │       │       │       │       │       │  │       │       │       │       │   '   │
// ├───────┼───────┼───────┼───────┼───────┤  ├───────┼───────┼───────┼───────┼───────┤
// │   Z   │   X   │   C   │   V   │   B   │  │   N   │   M   │   <   │   >   │   ?   │
// │       │       │       │       │       │  │       │       │   ,   │   .   │   /   │
// └───────┴───────┼───────┼───────┼───────┤  ├───────┼───────┼───────┼───────┴───────┘
//                 │       │       │       │  │       │       │       │
//                 │       │       │       │  │       │       │       │
//                 └───────┴───────┴───────┘  └───────┴───────┴───────┘
    [_QWERTY] = LAYOUT_split_3x5_3(
    KC_Q   ,KC_W   ,KC_E   ,KC_R   ,KC_T   ,   KC_Y   ,KC_U   ,KC_I   ,   KC_O,KC_P   ,
    KC_A   ,KC_S   ,KC_D   ,KC_F   ,KC_G   ,   KC_H   ,KC_J   ,KC_K   ,   KC_L,KC_SCLN,
    KC_Z   ,KC_X   ,KC_C   ,KC_V   ,KC_B   ,   KC_N   ,KC_M   ,KC_COMM, KC_DOT,KC_SLSH,
                    KC_LCTL,MO_NUM ,KC_SPC ,   KC_SPC ,_______,KC_ENT
    ),

// ====================================================================================
// NUMBER
// ====================================================================================
// Left-handed number pad.
// ┌───────┬───────┬───────┬───────┬───────┐  ┌───────┬───────┬───────┬───────┬───────┐
// │       │   (   │   *   │   &   │       │  │       │       │       │       │       │
// │   ~   │   9   │   8   │   7   │       │  │       │   (   │   )   │   \   │   |   │
// ├───────┼───────┼───────┼───────┼───────┤  ├───────┼───────┼───────┼───────┼───────┤
// │   )   │   #   │   @   │   !   │       │  │       │       │       │       │       │
// │   0   │   3   │   2   │   1   │       │  │       │   {   │   }   │   -   │   _   │
// ├───────┼───────┼───────┼───────┼───────┤  ├───────┼───────┼───────┼───────┼───────┤
// │       │   ^   │   %   │   $   │       │  │       │       │       │       │       │
// │   `   │   6   │   5   │   4   │       │  │       │   [   │   ]   │   =   │   +   │
// └───────┼───────┼───────┼───────┼───────┤  ├───────┼───────┼───────┼───────┴───────┘
//                 │       │       │       │  │       │       │       │
//                 │       │       │       │  │       │       │       │
//                 └───────┴───────┴───────┘  └───────┴───────┴───────┘
    [_NUMBER] = LAYOUT_split_3x5_3(
    KC_TILD,KC_9   ,KC_8   ,KC_7   ,_______,   _______,KC_LPRN,KC_RPRN,KC_BSLS,KC_PIPE,
    KC_0   ,KC_3   ,KC_2   ,KC_1   ,_______,   _______,KC_LCBR,KC_RCBR,KC_MINS,KC_UNDS,
    KC_GRV ,KC_6   ,KC_5   ,KC_4   ,_______,   _______,KC_LBRC,KC_RBRC,KC_EQL ,KC_PLUS,
                    _______,_______,_______,   _______,_______,_______
    ),

    [_LOWER] = LAYOUT_split_3x5_3(
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
    KC_ESC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR,
    KC_CAPS, KC_TILD, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, KC_PIPE,  KC_DQT,
                      XXXXXXX, XXXXXXX, XXXXXXX,      KC_ENT,  XXXXXXX, KC_DEL
    ),

    [_BLANK] = LAYOUT(
    _______,_______,_______,_______,_______,   _______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,   _______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,   _______,_______,_______,_______,_______,
                    _______,_______,_______,   _______,_______,_______
    ),
};

