#include QMK_KEYBOARD_H

#include "quantum/keymap_extras/keymap_uk.h"
#include "quantum/keymap_extras/sendstring_uk.h"

#define LAYOUT LAYOUT_split_3x6_3

enum layers
{
    _QWERTY = 0,
    _NAV,
    _NUM,
    _SYM,
    _FUNC,
    _MEDIA,
    _OTHER,
    _GAME,
    _GAME2,
};

#define QWERTY DF(_QWERTY)
#define NAV    MO(_NAV)
#define NUM    MO(_NUM)
#define SYM    MO(_SYM)
#define FUNC   MO(_FUNC)
#define MEDIA  MO(_MEDIA)
#define OTHER  MO(_OTHER)
#define GAME   DF(_GAME)
#define GAME2  MO(_GAME2)

#define SPC_NAV LT(_NAV, KC_SPC)
#define NUM_ESC LT(_NUM, KC_ESC)

#define OSM_LGUI OSM(MOD_LGUI)
#define OSM_LCTL OSM(MOD_LCTL)
#define OSM_LALT OSM(MOD_LALT)
#define OSM_LSFT OSM(MOD_LSFT)

#define OSM_RGUI OSM(MOD_RGUI)
#define OSM_RCTL OSM(MOD_RCTL)
#define OSM_RALT OSM(MOD_RALT)
#define OSM_RSFT OSM(MOD_RSFT)

#define TMUX_LDR LCTL(KC_A)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
      KC_LALT,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
      KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
      KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
                                          KC_LCTL, SPC_NAV, NUM_ESC,        SYM, KC_LSFT, KC_LALT
  ),

    [_NAV] = LAYOUT(
      KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_ESC,                     KC_TRNS, KC_HOME, KC_PGDN, KC_PGUP,   KC_END, KC_TRNS,
      KC_TRNS, OSM_LGUI, OSM_LALT, OSM_LSFT, OSM_LCTL, KC_ENT,                     KC_TAB,  KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_TRNS,
      KC_TRNS,  KC_CAPS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,                    KC_DEL,  KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,
                                                OTHER, KC_TRNS,  KC_SPC,      MEDIA, KC_BSPC, KC_TRNS
  ),

    [_NUM] = LAYOUT(
      KC_TRNS, UK_LBRC,  UK_LABK,  UK_MINS,  UK_RABK,  UK_RBRC,                    TMUX_LDR,   KC_7, KC_8, KC_9, KC_UP,   KC_TRNS,
      KC_TRNS, OSM_LGUI, OSM_LALT, OSM_LCTL, OSM_LSFT, UK_RCBR,                    KC_SLSH,    KC_4, KC_5, KC_6, KC_DOWN, KC_TRNS,
      KC_TRNS, UK_BSLS,  UK_ASTR,  UK_COLN,  UK_PLUS,  UK_UNDS,                       KC_X,    KC_1, KC_2, KC_3, UK_DOT,  GAME,
                                             KC_TRNS,  OTHER, KC_TRNS,       KC_0, KC_BSPC,    KC_ENT
  ),

    [_SYM] = LAYOUT(
      KC_TRNS, UK_LBRC, UK_LABK, UK_MINS, UK_RABK, UK_RBRC,                        UK_CIRC, UK_SLSH, UK_GRV,  UK_HASH, UK_AT,   KC_TRNS,
      KC_TRNS, UK_LCBR, UK_LPRN, UK_EQL,  UK_RPRN, UK_RCBR,                        UK_PERC, UK_DLR,  UK_DQUO, UK_QUOT, UK_EXLM, KC_TRNS,
      KC_TRNS, UK_BSLS, UK_ASTR, UK_COLN, UK_PLUS, UK_UNDS,                        UK_AMPR, UK_TILD, UK_QUES, UK_PIPE, UK_PND,  KC_TRNS,
                                          KC_TRNS, KC_TRNS, FUNC,          KC_TRNS,KC_BSPC, KC_ENT
  ),

    [_FUNC] = LAYOUT(
      KC_TRNS, KC_F13,   KC_F14,   KC_F15,   KC_F16,   KC_F17,                     KC_F12, KC_F7, KC_F8, KC_F9, KC_PSCR, KC_TRNS,
      KC_TRNS, OSM_LGUI, OSM_LALT, OSM_LCTL, OSM_LSFT, KC_TRNS,                    KC_F11, KC_F4, KC_F5, KC_F6, KC_INS,  KC_TRNS,
      KC_TRNS, OSM_RGUI, OSM_RALT, OSM_RCTL, OSM_RSFT, KC_TRNS,                    KC_F10, KC_F1, KC_F2, KC_F3, KC_TRNS, KC_TRNS,
                                              KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,KC_TRNS, KC_TRNS
  ),

    [_MEDIA] = LAYOUT(
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, LALT(KC_F4),                              KC_NO,   KC_MPRV, KC_BRID, KC_BRIU, KC_MNXT, KC_NO,
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                    KC_NO,   KC_MPLY, KC_VOLD, KC_VOLU, KC_MUTE, KC_NO,
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                    KC_NO,   KC_MUTE, KC_NO,   KC_NO,   KC_NO,   KC_NO,
                              KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,KC_TRNS, KC_TRNS
  ),

    [_OTHER] = LAYOUT(
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, QK_BOOT, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                          KC_TRNS, KC_TRNS,  KC_SPC,     KC_ENT, KC_TRNS, KC_TRNS
  ),

    [_GAME] = LAYOUT(
      KC_ESC, KC_TAB, KC_Q, KC_W, KC_E, KC_R,                                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_LCTL,KC_LSFT, KC_A, KC_S, KC_D, KC_F,                                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_M,  KC_LCTL, KC_Z, KC_X, KC_C, KC_V,                                    KC_UP,   KC_N,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                             KC_LALT, KC_SPC, GAME2,                    KC_LEFT, KC_DOWN, KC_RIGHT
  ),

    [_GAME2] = LAYOUT(
      KC_F8,  KC_GRAVE, KC_1, KC_2, KC_3, KC_T,                                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_F5,  KC_TRNS,  KC_4, KC_5, KC_6, KC_G,                                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_ENT, KC_0,     KC_7, KC_8, KC_9, KC_B,                                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, QWERTY,
                              KC_TRNS, KC_TRNS, KC_SPC,                 KC_TRNS, KC_TRNS, KC_TRNS
  ),

};
// clang-format on
