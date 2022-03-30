
#include QMK_KEYBOARD_H

enum layers {
    _QWERTY,
    _COLEMAK_DH,
    _NAVIGATE,
    _NUMBER,
    _CONTROL,
    _FUNCTION,
    _RGB,
    _BLANK,
};

#define K_F_SPC LT(_FUNCTION, KC_SPC)
#define LAY_CTL  MO(_CONTROL)
#define LAY_FUN  MO(_FUNCTION)

#define THUM_L1 MO(_NAVIGATE)
#define THUM_L2 MO(_NUMBER)
#define THUM_L3 LAY_CTL
#define THUM_R1 MT(MOD_LSFT, KC_BSPC)
#define THUM_R2 KC_SPC
#define THUM_R3 MO(_RGB)

#define CTRL_C LCTL(KC_C)
#define CTRL_F LCTL(KC_F)
#define CTRL_V LCTL(KC_V)
#define CTRL_X LCTL(KC_X)
#define CTRL_Z LCTL(KC_Z)

#define QWERTY   DF(_QWERTY)
#define COLEMAK  DF(_COLEMAK_DH)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// ====================================================================================
// BASE LAYER: QWERTY
// ====================================================================================
// ┌───────┬───────┬───────┬───────┬───────┐  ┌───────┬───────┬───────┬───────┬───────┐
// │   Q   │   W   │   E   │   R   │   T   │  │   Y   │   U   │   I   │   O   │   P   │
// │       │       │       │       │       │  │       │       │       │       │       │
// ├───────┼───────┼───────┼───────┼───────┤  ├───────┼───────┼───────┼───────┼───────┤
// │   A   │   S   │   D   │   F   │   G   │  │   H   │   J   │   K   │   L   │   :   │
// │       │       │       │       │       │  │       │       │       │       │   ;   │
// ├───────┼───────┼───────┼───────┼───────┤  ├───────┼───────┼───────┼───────┼───────┤
// │   Z   │   X   │   C   │   V   │   B   │  │   N   │   M   │   <   │   >   │   ?   │
// │       │       │       │       │       │  │       │       │   ,   │   .   │   /   │
// └───────┴───────┼───────┼───────┼───────┤  ├───────┼───────┼───────┼───────┴───────┘
//                 │       │       │       │  │       │ SHIFT │  FUNC │
//                 │       │ NUMBER│  NAV  │  │ SPACE │ BKSPC │       │
//                 └───────┴───────┴───────┘  └───────┴───────┴───────┘
    [_QWERTY] = LAYOUT_split_3x5_3(
    KC_Q   ,KC_W   ,KC_E   ,KC_R   ,KC_T   ,   KC_Y   ,KC_U   ,KC_I   ,   KC_O,KC_P   ,
    KC_A   ,KC_S   ,KC_D   ,KC_F   ,KC_G   ,   KC_H   ,KC_J   ,KC_K   ,   KC_L,KC_SCLN,
    KC_Z   ,KC_X   ,KC_C   ,KC_V   ,KC_B   ,   KC_N   ,KC_M   ,KC_COMM, KC_DOT,KC_SLSH,
                    THUM_L3,THUM_L2,THUM_L1,   THUM_R1,THUM_R2,THUM_R3
    ),

// ====================================================================================
// ALTERNATE BASE LAYER: COLEMAK DH
// ====================================================================================
// ┌───────┬───────┬───────┬───────┬───────┐  ┌───────┬───────┬───────┬───────┬───────┐
// │   Q   │   W   │   F   │   P   │   B   │  │   J   │   L   │   U   │   Y   │   :   │
// │       │       │       │       │       │  │       │       │       │       │   ;   │
// ├───────┼───────┼───────┼───────┼───────┤  ├───────┼───────┼───────┼───────┼───────┤
// │   A   │   R   │   S   │   T   │   G   │  │   M   │   N   │   E   │   I   │   O   │
// │       │       │       │       │       │  │       │       │       │       │       │
// ├───────┼───────┼───────┼───────┼───────┤  ├───────┼───────┼───────┼───────┼───────┤
// │   Z   │   X   │   C   │   D   │   V   │  │   K   │   H   │   <   │   >   │   ?   │
// │       │       │       │       │       │  │       │       │   ,   │   .   │   /   │
// └───────┴───────┼───────┼───────┼───────┤  ├───────┼───────┼───────┼───────┴───────┘
//                 │       │       │       │  │       │       │       │
//                 │       │       │       │  │       │       │       │
//                 └───────┴───────┴───────┘  └───────┴───────┴───────┘
    [_COLEMAK_DH] = LAYOUT_split_3x5_3(
    KC_Q   ,KC_W   ,KC_F   ,KC_P   ,KC_B   ,   KC_J   ,KC_L   ,KC_U   ,KC_Y   ,KC_SCLN,
    KC_A   ,KC_R   ,KC_S   ,KC_T   ,KC_G   ,   KC_M   ,KC_N   ,KC_E   ,KC_I   ,KC_O   ,
    KC_Z   ,KC_X   ,KC_C   ,KC_D   ,KC_V   ,   KC_K   ,KC_H   ,KC_COMM, KC_DOT,KC_SLSH,
                    THUM_L3,THUM_L2,THUM_L1,   THUM_R1,THUM_R2,THUM_R3
    ),

// ====================================================================================
// NAVIGATE
// ====================================================================================
// ┌───────┬───────┬───────┬───────┬───────┐  ┌───────┬───────┬───────┬───────┬───────┐
// │       │       │       │       │       │  │       │       │       │       │       │
// │  ESC  │  DEL  │  PGUP │  PGDN │  HOME │  │       │       │ INSERT│       │       │
// ├───────┼───────┼───────┼───────┼───────┤  ├───────┼───────┼───────┼───────┼───────┤
// │       │       │       │       │       │  │       │       │       │       │       │
// │ ENTER │  GUI  │  ALT  │  CTRL │ BKSPC │  │   ←   │   ↓   │   ↑   │   →   │  TAB  │
// ├───────┼───────┼───────┼───────┼───────┤  ├───────┼───────┼───────┼───────┼───────┤
// │       │       │       │       │       │  │       │       │       │       │       │
// │       │       │       │       │  END  │  │  HOME │  PGDN │  PGUP │  END  │ CTRL-F│
// └───────┴───────┼───────┼───────┼───────┤  ├───────┼───────┼───────┼───────┴───────┘
//                 │       │       │       │  │       │       │       │
//                 │       │       │       │  │       │       │       │
//                 └───────┴───────┴───────┘  └───────┴───────┴───────┘
    [_NAVIGATE] = LAYOUT_split_3x5_3(
    KC_ESC ,KC_DEL ,KC_PGUP,KC_PGDN,KC_HOME,   _______,_______,KC_INS ,_______,_______,
    KC_ENT ,KC_LGUI,KC_LALT,KC_LCTL,KC_BSPC,   KC_LEFT,KC_DOWN,KC_UP  ,KC_RGHT,KC_TAB ,
    LAY_CTL,CTRL_X ,CTRL_C ,CTRL_V ,KC_END ,   KC_HOME,KC_PGDN,KC_PGUP,KC_END ,CTRL_F ,
                    _______,_______,_______,   _______,K_F_SPC,_______
    ),

// ====================================================================================
// NUMBER
// ====================================================================================
// Left-handed number pad.
// ┌───────┬───────┬───────┬───────┬───────┐  ┌───────┬───────┬───────┬───────┬───────┐
// │       │   (   │   *   │   &   │       │  │       │       │       │       │       │
// │   ~   │   9   │   8   │   7   │       │  │   "   │   (   │   )   │   \   │   |   │
// ├───────┼───────┼───────┼───────┼───────┤  ├───────┼───────┼───────┼───────┼───────┤
// │   )   │   #   │   @   │   !   │       │  │       │       │       │       │       │
// │   0   │   3   │   2   │   1   │   -   │  │   '   │   {   │   }   │   -   │   _   │
// ├───────┼───────┼───────┼───────┼───────┤  ├───────┼───────┼───────┼───────┼───────┤
// │       │   ^   │   %   │   $   │       │  │       │       │       │       │       │
// │   `   │   6   │   5   │   4   │       │  │   `   │   [   │   ]   │   =   │   +   │
// └───────┼───────┼───────┼───────┼───────┤  ├───────┼───────┼───────┼───────┴───────┘
//                 │       │       │       │  │       │       │       │
//                 │       │       │       │  │       │       │       │
//                 └───────┴───────┴───────┘  └───────┴───────┴───────┘
    [_NUMBER] = LAYOUT_split_3x5_3(
    KC_TILD,KC_9   ,KC_8   ,KC_7   ,_______,   KC_GRV ,KC_LPRN,KC_RPRN,KC_BSLS,KC_PIPE,
    KC_0   ,KC_3   ,KC_2   ,KC_1   ,KC_MINS,   KC_DQUO,KC_LCBR,KC_RCBR,KC_MINS,KC_UNDS,
    KC_GRV ,KC_6   ,KC_5   ,KC_4   ,_______,   KC_QUOT,KC_LBRC,KC_RBRC,KC_EQL ,KC_PLUS,
                    _______,_______,_______,   _______,_______,_______
    ),

// ====================================================================================
// CONTROL
// ====================================================================================
// ┌───────┬───────┬───────┬───────┬───────┐  ┌───────┬───────┬───────┬───────┬───────┐
// │       │       │       │       │       │  │       │       │       │       │       │
// │       │       │  VOL+ │  VOL- │       │  │       │       │       │       │       │
// ├───────┼───────┼───────┼───────┼───────┤  ├───────┼───────┼───────┼───────┼───────┤
// │       │       │       │       │       │  │       │       │       │       │       │
// │       │  PREV │  PLAY │  NEXT │       │  │       │ QUERTY│COLEMAK│       │       │
// ├───────┼───────┼───────┼───────┼───────┤  ├───────┼───────┼───────┼───────┼───────┤
// │       │       │       │       │       │  │       │       │       │       │       │
// │       │       │       │       │ RESET │  │       │       │       │       │       │
// └───────┴───────┼───────┼───────┼───────┤  ├───────┼───────┼───────┼───────┴───────┘
//                 │       │       │       │  │       │       │       │
//                 │       │       │       │  │       │       │       │
//                 └───────┴───────┴───────┘  └───────┴───────┴───────┘
    [_CONTROL] = LAYOUT_split_3x5_3(
    _______,_______,KC_VOLU,KC_VOLD,_______,   _______,_______,_______,_______,_______,
    _______,KC_MPRV,KC_MPLY,KC_MNXT,_______,   _______,QWERTY ,COLEMAK,_______,_______,
    _______,_______,_______,_______,RESET  ,   _______,_______,_______,_______,_______,
                    _______,_______,_______,   _______,_______,_______
    ),

// ====================================================================================
// FUNCTION
// ====================================================================================
// ┌───────┬───────┬───────┬───────┬───────┐  ┌───────┬───────┬───────┬───────┬───────┐
// │       │       │       │       │       │  │       │       │       │       │       │
// │  F11  │   F9  │   F8  │   F7  │       │  │       │       │SCRLLCK│CAPSLCK│NUMLOCK│
// ├───────┼───────┼───────┼───────┼───────┤  ├───────┼───────┼───────┼───────┼───────┤
// │       │       │       │       │ PRINT │  │       │       │       │       │       │
// │  F10  │   F3  │   F2  │   F1  │ SCREEN│  │       │  CTRL │  ALT  │  GUI  │ SHIFT │
// ├───────┼───────┼───────┼───────┼───────┤  ├───────┼───────┼───────┼───────┼───────┤
// │       │       │       │       │       │  │       │       │       │       │       │
// │  F12  │   F6  │   F5  │   F4  │       │  │       │       │       │       │       │
// └───────┴───────┼───────┼───────┼───────┤  ├───────┼───────┼───────┼───────┴───────┘
//                 │       │       │       │  │       │       │       │
//                 │       │       │       │  │       │       │       │
//                 └───────┴───────┴───────┘  └───────┴───────┴───────┘
    [_FUNCTION] = LAYOUT_split_3x5_3(
    KC_F11 ,KC_F9  ,KC_F8  ,KC_F7  ,_______,  _______,_______,KC_SLCK,KC_CLCK,KC_NLCK,
    KC_F10 ,KC_F3  ,KC_F2  ,KC_F1  ,KC_PSCR,  _______,KC_LCTL,KC_LALT,KC_LGUI,KC_LSFT,
    KC_F12 ,KC_F6  ,KC_F5  ,KC_F4  ,_______,  _______,_______,_______,_______,_______,
                    _______,_______,LAY_CTL,  _______,_______,_______
    ),

// ====================================================================================
// RGB
// ====================================================================================
// ┌───────┬───────┬───────┬───────┬───────┐  ┌───────┬───────┬───────┬───────┬───────┐
// │       │       │       │       │       │  │       │       │       │       │       │
// │       │ RGB 9 │ RGB 8 │ RGB 7 │       │  │       │       │       │       │       │
// ├───────┼───────┼───────┼───────┼───────┤  ├───────┼───────┼───────┼───────┼───────┤
// │       │       │       │       │       │  │       │       │       │       │       │
// │ ON/OFF│ RGB 3 │ RGB 2 │ RGB 1 │       │  │  HUE+ │  BRI+ │  SAT+ │  SPD+ │ MODE+ │
// ├───────┼───────┼───────┼───────┼───────┤  ├───────┬───────┼───────┼───────┼───────┤
// │       │       │       │       │       │  │       │       │       │       │       │
// │       │ RGB 6 │ RGB 5 │ RGB 4 │       │  │  HUE- │  BRI- │  SAT- │  SPD- │ MODE- │
// └───────┴───────┼───────┼───────┼───────┤  ├───────┼───────┼───────┼───────┼───────┘
//                 │       │       │       │  │       │       │       │
//                 │       │       │       │  │       │       │       │
//                 └───────└───────┴───────┘  └───────┴───────┴───────┘
    [_RGB] = LAYOUT_split_3x5_3(
    _______,RGB_M_T,RGB_M_G,RGB_M_X,_______,  _______,_______,_______,_______,_______,
    RGB_TOG,RGB_M_R,RGB_M_B,RGB_M_P,_______,  RGB_HUI,RGB_VAI,RGB_SAI,RGB_SPI,RGB_MOD,
    _______,RGB_M_K,RGB_M_SN,RGB_M_SW,_______,RGB_HUD,RGB_VAD,RGB_SAD,RGB_SPD,RGB_RMOD,
                    _______,_______,_______,  _______,_______,_______
    ),

// ====================================================================================
// BLANK
// ====================================================================================
// ┌───────┬───────┬───────┬───────┬───────┐  ┌───────┬───────┬───────┬───────┬───────┐
// │       │       │       │       │       │  │       │       │       │       │       │
// │       │       │       │       │       │  │       │       │       │       │       │
// ├───────┼───────┼───────┼───────┼───────┤  ├───────┼───────┼───────┼───────┼───────┤
// │       │       │       │       │       │  │       │       │       │       │       │
// │       │       │       │       │       │  │       │       │       │       │       │
// ├───────┼───────┼───────┼───────┼───────┤  ├───────┼───────┼───────┼───────┼───────┤
// │       │       │       │       │       │  │       │       │       │       │       │
// │       │       │       │       │       │  │       │       │       │       │       │
// └───────┴───────┼───────┼───────┼───────┤  ├───────┼───────┼───────┼───────┴───────┘
//                 │       │       │       │  │       │       │       │
//                 │       │       │       │  │       │       │       │
//                 └───────┴───────┴───────┘  └───────┴───────┴───────┘
    [_BLANK] = LAYOUT_split_3x5_3(
    _______,_______,_______,_______,_______,   _______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,   _______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,   _______,_______,_______,_______,_______,
                    _______,_______,_______,   _______,_______,_______
    ),

};

