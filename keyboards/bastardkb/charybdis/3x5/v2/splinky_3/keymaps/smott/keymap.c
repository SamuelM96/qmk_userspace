/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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

#include <string.h>

#include "casemodes.h"

#include "quantum/keymap_extras/keymap_uk.h"
#include "quantum/keymap_extras/sendstring_uk.h"

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

enum layers {
    _QWERTY = 0,
    _NAV,
    _NUM,
    _SYM,
    _FUNCTION,
    _MEDIA,
    _OTHER,
    _POINTER,
    _MACRO,
};

enum custom_keycodes {
    SNAKECASE = SAFE_RANGE,
    JIGGLE,
};

#define ESC_MED LT(_MEDIA, KC_ESC)
#define SPC_NAV LT(_NAV, KC_SPC)
#define TAB_FUN LT(_FUNCTION, KC_TAB)
#define ENT_SYM LT(_SYM, KC_ENT)
#define BSP_NUM LT(_NUM, KC_BSPC)

// Aliases for readability
#define QWERTY DF(_QWERTY)

#define NAV MO(_NAV)
#define NUM MO(_NUM)
#define SYM MO(_SYM)
#define FKEYS MO(_FUNCTION)
#define MEDIA MO(_MEDIA)
#define OTHER MO(_OTHER)
#define L_PTR(KC) LT(_POINTER, KC)
#define MACRO MO(_MACRO)

#define SPC_NAV LT(_NAV, KC_SPC)
#define NUM_ESC LT(_NUM, KC_ESC)
#define CTL_ESC MT(MOD_LCTL, KC_ESC)
#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define CTL_MINS MT(MOD_RCTL, KC_MINUS)
#define ALT_ENT MT(MOD_LALT, KC_ENT)

#define OSM_LGUI OSM(MOD_LGUI)
#define OSM_LCTL OSM(MOD_LCTL)
#define OSM_LALT OSM(MOD_LALT)
#define OSM_LSFT OSM(MOD_LSFT)

#define OSM_RGUI OSM(MOD_RGUI)
#define OSM_RCTL OSM(MOD_RCTL)
#define OSM_RALT OSM(MOD_RALT)
#define OSM_RSFT OSM(MOD_RSFT)

bool            mouse_jiggler_enabled = false;
static uint16_t mouse_jiggler_timer;

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
            UK_Q,       UK_W,       UK_E,       UK_R,       UK_T,               UK_Y,       UK_U,       UK_I,       UK_O,       UK_P,
            UK_A,       UK_S,       UK_D,       UK_F,       UK_G,               UK_H,       UK_J,       UK_K,       UK_L,       UK_SCLN,
            L_PTR(UK_Z),UK_X,       UK_C,       UK_V,       UK_B,               UK_N,       UK_M,       UK_COMM,    UK_DOT,     L_PTR(UK_SLSH),
                                    KC_LCTL,    SPC_NAV,    NUM_ESC,            SYM,        KC_LSFT),

	[_NAV] = LAYOUT(
            MACRO,      KC_TRNS,    QK_AREP,    QK_REP,     KC_ESC,             KC_TRNS,    KC_HOME,    KC_PGDN,    KC_PGUP,    KC_END,
            OSM_LCTL,   OSM_LGUI,   OSM_LALT,   OSM_LSFT,   KC_ENT,             KC_TAB,     KC_LEFT,    KC_DOWN,    KC_UP,      KC_RGHT,
            KC_CAPS,    KC_TRNS,    OSM_RALT,   CW_TOGG,    SNAKECASE,          KC_DEL,     KC_UNDO,    KC_COPY,    KC_PSTE,    KC_AGIN,
                                    OTHER,      KC_TRNS,    KC_TRNS,            MEDIA, KC_BSPC),

	[_NUM] = LAYOUT(
            UK_QUOT,    UK_LBRC,    UK_RBRC,    UK_DLR,     KC_PERC,            UK_ASTR,    KC_7,       KC_8,       KC_9,       KC_MINS,
            OSM_LCTL,   OSM_LGUI,   OSM_LALT,   OSM_LSFT,   UK_HASH,            UK_SLSH,    KC_4,       KC_5,       KC_6,       UK_PLUS,
            UK_BSLS,    UK_LCBR,    UK_RCBR,    UK_EXLM,    UK_PIPE,            UK_EQL,     KC_1,       KC_2,       KC_3,       UK_DOT,
                                    KC_TRNS,    KC_TRNS,    KC_TRNS,            UK_0,       KC_BSPC),

	[_SYM] = LAYOUT(
            UK_LBRC,    UK_LABK,    UK_MINS,    UK_RABK,    UK_RBRC,            UK_CIRC,    UK_QUES,    UK_GRV,    UK_DQUO,    UK_QUOT,
            UK_LCBR,    UK_LPRN,    UK_EQL,     UK_RPRN,    UK_RCBR,            UK_PERC,    UK_DLR,     UK_HASH,   UK_AT,      UK_EXLM,
            UK_BSLS,    UK_ASTR,    UK_COLN,    UK_PLUS,    UK_UNDS,            UK_AMPR,    UK_TILD,    UK_SCLN,   UK_PIPE,    UK_PND,
                                    FKEYS,      KC_TRNS,    KC_TRNS,            KC_TRNS,    KC_BSPC),

	[_FUNCTION] = LAYOUT(
            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_F10,     KC_F7,      KC_F8,      KC_F9,      KC_PSCR,
            OSM_LCTL,   OSM_LGUI,   OSM_LALT,   OSM_LSFT,   OTHER,              KC_F11,     KC_F4,      KC_F5,      KC_F6,      KC_INS,
            OSM_RCTL,   OSM_RGUI,   OSM_RALT,   OSM_RSFT,   KC_TRNS,            KC_F12,     KC_F1,      KC_F2,      KC_F3,      KC_TRNS,
                                    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS,    KC_TRNS),

	[_MEDIA] = LAYOUT(
            KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,              KC_BRIU,    KC_NO,      KC_MSTP,    KC_MPLY,    KC_NO,
            KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,              KC_BRID,    KC_MPRV,    KC_VOLD,    KC_VOLU,    KC_MNXT,
            KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,              KC_NO,      KC_MUTE,    KC_NO,      KC_NO,      KC_NO,
                                    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS,    KC_TRNS),
	[_OTHER] = LAYOUT(
            KC_TRNS,    RGB_RMOD,   RGB_TOG,    RGB_MOD,    KC_TRNS,            KC_TRNS,    RGB_RMOD,   RGB_TOG,    RGB_MOD,    QK_BOOT,
            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS,    JIGGLE,     KC_TRNS,    KC_TRNS,    KC_TRNS,
            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS,    QK_MAKE,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                                    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_LCTL,    KC_LSFT),

	[_POINTER] = LAYOUT(
            KC_TRNS,    KC_TRNS,    KC_TRNS,    DPI_MOD,    S_D_MOD,            S_D_MOD,    DPI_MOD,    KC_TRNS,    KC_TRNS,    KC_TRNS,
            KC_TRNS,    SNIPING,    KC_TRNS,    DPI_RMOD,   S_D_RMOD,           S_D_RMOD,   DPI_RMOD,   KC_BTN3,    SNIPING,    KC_TRNS,
            KC_TRNS,    DRGSCRL,    KC_TRNS,    KC_TRNS,    SNP_TOG,            SNP_TOG,    KC_BTN1,    KC_BTN2,    DRGSCRL,    KC_TRNS,
                                    KC_BTN2,    KC_BTN1,    KC_BTN3,            KC_WBAK,    KC_WFWD),

	[_MACRO] = LAYOUT(
            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS,    DM_REC1,    DM_RSTP,    DM_REC2,    KC_TRNS,
            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS,    DM_PLY1,    KC_TRNS,    DM_PLY2,    KC_TRNS,
                                    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS,    KC_TRNS),

     // [_TEMPLATE] = LAYOUT(
     //        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
     //        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
     //        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
     //                                KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS,    KC_TRNS),
};
// clang-format on

bool has_mouse_report_changed(report_mouse_t* new_report, report_mouse_t* old_report) {
    // Only report every 5 seconds.
    if (mouse_jiggler_enabled && timer_elapsed(mouse_jiggler_timer) > 5000) {
        mouse_jiggler_timer = timer_read();
        return mouse_jiggler_enabled;
    }

    return memcmp(new_report, old_report, sizeof(report_mouse_t));
}

void mouse_jiggle_toggle(void) {
    mouse_jiggler_timer   = timer_read();
    mouse_jiggler_enabled = !mouse_jiggler_enabled;
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    // Proccess case modes
    if (!process_case_modes(keycode, record)) {
        return false;
    }

    switch (keycode) {
        case SNAKECASE:
            if (record->event.pressed) {
                enable_xcase_with(KC_UNDS);
            }
            return false;
        case JIGGLE:
            if (record->event.pressed) {
                mouse_jiggle_toggle();
            }
            return false;
        default:
            return true;
    }
}
