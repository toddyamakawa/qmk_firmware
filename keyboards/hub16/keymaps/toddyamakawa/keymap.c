/* Copyright 2019 Josh Johnson
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
#include QMK_KEYBOARD_H

enum custom_keycodes {
	KVM_1 = SAFE_RANGE,
	KVM_2
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT( /* Base */
       KC_MUTE,        KC_MPLY,
    KC_7,   KC_8,   KC_9,   MO(2),
    KC_4,   KC_5,   KC_6,   KC_PMNS,
    KC_1,   KC_2,   KC_3,   KC_PPLS,
    MO(1),  KC_0,   KC_PDOT,KC_PENT
  ),

  [1] = LAYOUT( /* LED Control */
        _______,           _______,
    _______, RGB_MOD, RGB_RMOD, RGB_TOG,
    RGB_VAD, RGB_VAI, RGB_HUD,  RGB_HUI,
    RGB_SAD, RGB_SAI, _______,  _______,
    _______, _______, RESET,    _______
  ),

  [2] = LAYOUT(
        _______,           _______,
    KVM_1  , KVM_2  , KC_SLCK, _______,
    _______, _______, _______, _______,
    _______, _______, _______, _______,
    KC_RCTL, KC_F1  , _______, _______
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch(keycode) {
		case KVM_1:
			if(record->event.pressed) {
				tap_code(KC_SCROLLLOCK);
				tap_code(KC_SCROLLLOCK);
				tap_code(KC_1);
			}
			return false;
		case KVM_2:
			if(record->event.pressed) {
				tap_code(KC_SCROLLLOCK);
				tap_code(KC_SCROLLLOCK);
				tap_code(KC_2);
			}
			return false;
	}
	return true;
}


bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* Left Encoder */
        if (clockwise) {
            tap_code(KC_VOLD);
        } else {
            tap_code(KC_VOLU);
        }
    } else if (index == 1) { /* Right Encoder */
        if (clockwise) {
            tap_code(KC_MPRV);
        } else {
            tap_code(KC_MNXT);
        }
    }
    return true;
}
