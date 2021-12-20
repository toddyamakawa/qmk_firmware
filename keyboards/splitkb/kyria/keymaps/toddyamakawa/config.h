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

#pragma once

#define ENCODER_RESOLUTION 2

#ifdef OLED_DRIVER_ENABLE
  #define OLED_DISPLAY_128X64
#endif

#ifdef RGBLIGHT_ENABLE
  #define RGBLIGHT_ANIMATIONS
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
  #define RGBLIGHT_LIMIT_VAL 150
#endif

// TODO: Use this
// https://github.com/qmk/qmk_firmware/pull/9404
//#define TAPPING_TERM_PER_KEY
//#define RETRO_TAPPING_PER_KEY
#define RETRO_TAPPING
#define TAPPING_TERM 0

// If you are using an Elite C rev3 on the slave side, uncomment the lines below:
// #define SPLIT_USB_DETECT
// #define NO_USB_STARTUP_CHECK

// Combos
#define COMBO_COUNT 2
#define COMBO_TERM 25

// Global tapping term (default=200)
//#define TAPPING_TERM 150
//#define TAPPING_TERM 0
// Ignore tap intertuptions while modifier held
//#define IGNORE_MOD_TAP_INTERRUPT
// Disable tap-hold auto-repeat
#define TAPPING_FORCE_HOLD
// Apply modifiers held for a short hold
#define PERMISSIVE_HOLD

#define ONESHOT_TAP_TOGGLE 1

