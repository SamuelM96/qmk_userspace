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

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 500
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 0
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif     // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

enum layers {
    _QWERTY = 0,
    _COLEMAK_DH,
    _NAV,
    _NUM,
    _SYM,
    _FUNCTION,
    _MEDIA,
    _OTHER,
    _POINTER,
    _WEB,
    _MACRO,
};

/* #define CHARYBDIS_AUTO_SNIPING_ON_LAYER _POINTER */

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
#define COLEMAK_DH DF(_COLEMAK_DH)

#define NAV MO(_NAV)
#define NUM MO(_NUM)
#define SYM MO(_SYM)
#define FKEYS MO(_FUNCTION)
#define MEDIA MO(_MEDIA)
#define OTHER MO(_OTHER)
#define L_WEB(KC) LT(_WEB, KC)
#define MACRO MO(_MACRO)

#define SPC_NAV LT(_NAV, KC_SPC)
#define NUM_ESC LT(_NUM, KC_ESC)
#define CTL_ESC MT(MOD_LCTL, KC_ESC)
#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define CTL_MINS MT(MOD_RCTL, KC_MINUS)
#define ALT_ENT MT(MOD_LALT, KC_ENT)
#define ALT_SPC MT(MOD_LALT, KC_SPC)
// TODO: Needs Colemak DH support. KC_TRNS didn't work
#define SFT_TRNS MT(MOD_LSFT, KC_F)
#define CTL_TRNS MT(MOD_LCTL, KC_D)
#define ALT_TRNS MT(MOD_LALT, KC_S)
#define GUI_TRNS MT(MOD_LGUI, KC_A)

#define OSM_LGUI OSM(MOD_LGUI)
#define OSM_LCTL OSM(MOD_LCTL)
#define OSM_LALT OSM(MOD_LALT)
#define OSM_LSFT OSM(MOD_LSFT)

#define OSM_RGUI OSM(MOD_RGUI)
#define OSM_RCTL OSM(MOD_RCTL)
#define OSM_RALT OSM(MOD_RALT)
#define OSM_RSFT OSM(MOD_RSFT)

bool            pointer_key_held      = false;
bool            mouse_jiggler_enabled = false;
static uint16_t mouse_jiggler_timer;

#define COMBO_SHOULD_TRIGGER
enum combos {
    // L/R is used to denote keyboard side, not keycodes
    COMBO_QWERTY_LCTL,
    COMBO_QWERTY_LALT,
    COMBO_QWERTY_LGUI,
    COMBO_QWERTY_LCTLALT,
    COMBO_QWERTY_LALTGUI,
    COMBO_QWERTY_LCTLALTGUI,

    COMBO_QWERTY_RCTL,
    COMBO_QWERTY_RALT,
    COMBO_QWERTY_RGUI,
    COMBO_QWERTY_RCTLALT,
    COMBO_QWERTY_RALTGUI,
    COMBO_QWERTY_RCTLALTGUI,
    COMBO_QWERTY_CTLSPC,

    COMBO_COLEMAK_LCTL,
    COMBO_COLEMAK_LALT,
    COMBO_COLEMAK_LGUI,
    COMBO_COLEMAK_LCTLALT,
    COMBO_COLEMAK_LALTGUI,
    COMBO_COLEMAK_LCTLALTGUI,

    COMBO_COLEMAK_RCTL,
    COMBO_COLEMAK_RALT,
    COMBO_COLEMAK_RGUI,
    COMBO_COLEMAK_RCTLALT,
    COMBO_COLEMAK_RALTGUI,
    COMBO_COLEMAK_RCTLALTGUI,
    COMBO_COLEMAK_CTLSPC,

    COMBO_SYM_LCTL,
    COMBO_SYM_LALT,
    COMBO_SYM_LGUI,
    COMBO_SYM_LCTLALT,
    COMBO_SYM_LALTGUI,
    COMBO_SYM_LCTLALTGUI,

    COMBO_SYM_RALT,
    COMBO_SYM_RGUI,
    COMBO_SYM_RCTL,
    COMBO_SYM_RALTGUI,
    COMBO_SYM_RALTCTL,
    COMBO_SYM_RALTCTLGUI,

    COMBO_LENGTH
};

// Qwerty layer
const uint16_t PROGMEM fd_combo[]   = {KC_F, KC_D, COMBO_END};
const uint16_t PROGMEM fs_combo[]   = {KC_F, KC_S, COMBO_END};
const uint16_t PROGMEM fa_combo[]   = {KC_F, KC_A, COMBO_END};
const uint16_t PROGMEM fds_combo[]  = {KC_F, KC_D, KC_S, COMBO_END};
const uint16_t PROGMEM fda_combo[]  = {KC_F, KC_D, KC_A, COMBO_END};
const uint16_t PROGMEM fdsa_combo[] = {KC_F, KC_D, KC_S, KC_A, COMBO_END};

const uint16_t PROGMEM jk_combo[]      = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM jl_combo[]      = {KC_J, KC_L, COMBO_END};
const uint16_t PROGMEM jscln_combo[]   = {KC_J, UK_SCLN, COMBO_END};
const uint16_t PROGMEM jkl_combo[]     = {KC_J, KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM jkscln_combo[]  = {KC_J, KC_K, UK_SCLN, COMBO_END};
const uint16_t PROGMEM jklscln_combo[] = {KC_J, KC_K, KC_L, UK_SCLN, COMBO_END};
const uint16_t PROGMEM commam_combo[]  = {UK_COMM, KC_M, COMBO_END};

// Colemak layer
const uint16_t PROGMEM ts_combo[]   = {KC_T, KC_S, COMBO_END};
const uint16_t PROGMEM tr_combo[]   = {KC_T, KC_R, COMBO_END};
const uint16_t PROGMEM ta_combo[]   = {KC_T, KC_A, COMBO_END};
const uint16_t PROGMEM tsr_combo[]  = {KC_T, KC_S, KC_R, COMBO_END};
const uint16_t PROGMEM tsa_combo[]  = {KC_T, KC_S, KC_A, COMBO_END};
const uint16_t PROGMEM tsra_combo[] = {KC_T, KC_S, KC_R, KC_A, COMBO_END};

const uint16_t PROGMEM ne_combo[]     = {KC_N, KC_E, COMBO_END};
const uint16_t PROGMEM ni_combo[]     = {KC_N, KC_I, COMBO_END};
const uint16_t PROGMEM no_combo[]     = {KC_N, KC_O, COMBO_END};
const uint16_t PROGMEM nei_combo[]    = {KC_N, KC_E, KC_I, COMBO_END};
const uint16_t PROGMEM neo_combo[]    = {KC_N, KC_E, KC_O, COMBO_END};
const uint16_t PROGMEM neio_combo[]   = {KC_N, KC_E, KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM commah_combo[] = {UK_COMM, KC_H, COMBO_END};

// Symbol layer
const uint16_t PROGMEM sym_fd_combo[]   = {UK_RPRN, UK_EQL, COMBO_END};
const uint16_t PROGMEM sym_fs_combo[]   = {UK_RPRN, UK_LPRN, COMBO_END};
const uint16_t PROGMEM sym_fa_combo[]   = {UK_RPRN, UK_LCBR, COMBO_END};
const uint16_t PROGMEM sym_fds_combo[]  = {UK_RPRN, UK_EQL, UK_LPRN, COMBO_END};
const uint16_t PROGMEM sym_fda_combo[]  = {UK_RPRN, UK_EQL, UK_LCBR, COMBO_END};
const uint16_t PROGMEM sym_fdsa_combo[] = {UK_RPRN, UK_EQL, UK_LPRN, UK_LCBR, COMBO_END};

const uint16_t PROGMEM sym_jk_combo[]      = {UK_DLR, UK_HASH, COMBO_END};
const uint16_t PROGMEM sym_jl_combo[]      = {UK_DLR, UK_AT, COMBO_END};
const uint16_t PROGMEM sym_jscln_combo[]   = {UK_DLR, UK_EXLM, COMBO_END};
const uint16_t PROGMEM sym_jkl_combo[]     = {UK_DLR, UK_HASH, UK_AT, COMBO_END};
const uint16_t PROGMEM sym_jkscln_combo[]  = {UK_DLR, UK_HASH, UK_EXLM, COMBO_END};
const uint16_t PROGMEM sym_jklscln_combo[] = {UK_DLR, UK_HASH, UK_AT, UK_EXLM, COMBO_END};

// clang-format off
combo_t key_combos[] = {
    [COMBO_QWERTY_LCTL]        = COMBO(fd_combo, KC_LCTL),
    [COMBO_QWERTY_LALT]        = COMBO(fs_combo, KC_LALT),
    [COMBO_QWERTY_LGUI]        = COMBO(fa_combo, KC_LGUI),
    [COMBO_QWERTY_LCTLALT]     = COMBO(fds_combo, LALT(KC_LCTL)),
    [COMBO_QWERTY_LALTGUI]     = COMBO(fda_combo, LALT(KC_LGUI)),
    [COMBO_QWERTY_LCTLALTGUI]  = COMBO(fdsa_combo, LCA(KC_LGUI)),

    [COMBO_QWERTY_RCTL]        = COMBO(jk_combo, KC_LCTL),
    [COMBO_QWERTY_RALT]        = COMBO(jl_combo, KC_LALT),
    [COMBO_QWERTY_RGUI]        = COMBO(jscln_combo, KC_LGUI),
    [COMBO_QWERTY_RCTLALT]     = COMBO(jkl_combo, LALT(KC_LCTL)),
    [COMBO_QWERTY_RALTGUI]     = COMBO(jkscln_combo, LALT(KC_LGUI)),
    [COMBO_QWERTY_RCTLALTGUI]  = COMBO(jklscln_combo, LCA(KC_LGUI)),
    [COMBO_QWERTY_CTLSPC]      = COMBO(commam_combo, LCTL(KC_SPC)),

    [COMBO_COLEMAK_LCTL]       = COMBO(ts_combo, KC_LCTL),
    [COMBO_COLEMAK_LALT]       = COMBO(tr_combo, KC_LALT),
    [COMBO_COLEMAK_LGUI]       = COMBO(ta_combo, KC_LGUI),
    [COMBO_COLEMAK_LCTLALT]    = COMBO(tsr_combo, LALT(KC_LCTL)),
    [COMBO_COLEMAK_LALTGUI]    = COMBO(tsa_combo, LALT(KC_LGUI)),
    [COMBO_COLEMAK_LCTLALTGUI] = COMBO(tsra_combo, LCA(KC_LGUI)),

    [COMBO_COLEMAK_RCTL]       = COMBO(ne_combo, KC_LCTL),
    [COMBO_COLEMAK_RALT]       = COMBO(ni_combo, KC_LALT),
    [COMBO_COLEMAK_RGUI]       = COMBO(no_combo, KC_LGUI),
    [COMBO_COLEMAK_RCTLALT]    = COMBO(nei_combo, LALT(KC_LCTL)),
    [COMBO_COLEMAK_RALTGUI]    = COMBO(neo_combo, LALT(KC_LGUI)),
    [COMBO_COLEMAK_RCTLALTGUI] = COMBO(neio_combo, LCA(KC_LGUI)),
    [COMBO_COLEMAK_CTLSPC]      = COMBO(commah_combo, LCTL(KC_SPC)),

    [COMBO_SYM_LCTL]           = COMBO(sym_fd_combo, KC_LCTL),
    [COMBO_SYM_LALT]           = COMBO(sym_fs_combo, KC_LALT),
    [COMBO_SYM_LGUI]           = COMBO(sym_fa_combo, KC_LGUI),
    [COMBO_SYM_LCTLALT]        = COMBO(sym_fds_combo, LALT(KC_LCTL)),
    [COMBO_SYM_LALTGUI]        = COMBO(sym_fda_combo, LALT(KC_LGUI)),
    [COMBO_SYM_LCTLALTGUI]     = COMBO(sym_fdsa_combo, LCA(KC_LGUI)),

    [COMBO_SYM_RALT]           = COMBO(sym_jk_combo, KC_LALT),
    [COMBO_SYM_RGUI]           = COMBO(sym_jl_combo, KC_LGUI),
    [COMBO_SYM_RCTL]           = COMBO(sym_jscln_combo, KC_LCTL),
    [COMBO_SYM_RALTCTL]        = COMBO(sym_jkl_combo, LALT(KC_LCTL)),
    [COMBO_SYM_RALTGUI]        = COMBO(sym_jkscln_combo, LALT(KC_LGUI)),
    [COMBO_SYM_RALTCTLGUI]     = COMBO(sym_jklscln_combo, LCA(KC_LGUI)),
};
// clang-format on

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
            UK_Q,       UK_W,       UK_E,       UK_R,       UK_T,               UK_Y,       UK_U,       UK_I,       UK_O,         UK_P,
            UK_A,       UK_S,       UK_D,       UK_F,       UK_G,               UK_H,       UK_J,       UK_K,       UK_L,         UK_SCLN,
            L_WEB(UK_Z),UK_X,       UK_C,       UK_V,       UK_B,               UK_N,       UK_M,       UK_COMM,    UK_DOT,  L_WEB(UK_SLSH),
                                    KC_LCTL,    SPC_NAV,    NUM_ESC,            SYM,        KC_LSFT),

    [_COLEMAK_DH] = LAYOUT(
            UK_Q,       UK_W,       UK_F,       UK_P,       UK_B,               UK_J,       UK_L,       UK_U,       UK_Y,         UK_SCLN,
            UK_A,       UK_R,       UK_S,       UK_T,       UK_G,               UK_M,       UK_N,       UK_E,       UK_I,         UK_O,
            L_WEB(UK_Z),UK_X,       UK_C,       UK_D,       UK_V,               UK_K,       UK_H,       UK_COMM,    UK_DOT,  L_WEB(UK_SLSH),
                                    KC_LCTL,    SPC_NAV,    NUM_ESC,            SYM,        KC_LSFT),

	[_NAV] = LAYOUT(
            MACRO,      KC_TRNS,    QK_AREP,    QK_REP,     KC_ESC,             G(S(KC_PSCR)),KC_HOME,    KC_PGDN,    KC_PGUP,    KC_END,
            OSM_LGUI,   OSM_LALT,   OSM_LCTL,   OSM_LSFT,   KC_ENT,             KC_TAB,       KC_LEFT,    KC_DOWN,    KC_UP,      KC_RGHT,
            KC_CAPS,    OSM_RALT,   CW_TOGG,    SNAKECASE,  KC_SPC,             KC_DEL,       KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                                    OTHER,      KC_TRNS,    KC_TRNS,            MEDIA,        KC_BSPC),

	[_NUM] = LAYOUT(
            UK_LBRC,    UK_LABK,    UK_MINS,    UK_RABK,    UK_RBRC,            UK_ASTR,    KC_7,       KC_8,       KC_9,       KC_MINS,
            OSM_LGUI,   OSM_LALT,   OSM_LCTL,   OSM_LSFT,   UK_RCBR,            UK_SLSH,    KC_4,       KC_5,       KC_6,       UK_PLUS,
            UK_BSLS,    UK_ASTR,    UK_COLN,    UK_PLUS,    UK_UNDS,            UK_EQL,     KC_1,       KC_2,       KC_3,       UK_DOT,
                                    KC_TRNS,    KC_TRNS,    KC_TRNS,            UK_0,       KC_BSPC),

	[_SYM] = LAYOUT(
            UK_LBRC,    UK_LABK,    UK_MINS,    UK_RABK,    UK_RBRC,            UK_SCLN,    UK_CIRC,    UK_QUES,   UK_HASH,    UK_AT,
            UK_LCBR,    UK_LPRN,    UK_EQL,     UK_RPRN,    UK_RCBR,            UK_PERC,    UK_DLR,     UK_DQUO,   UK_QUOT,    UK_EXLM,
            UK_BSLS,    UK_ASTR,    UK_COLN,    UK_PLUS,    UK_UNDS,            UK_AMPR,    UK_TILD,    UK_GRV,    UK_PIPE,    UK_PND,
                                    KC_LCTL,    ALT_SPC,    FKEYS,              KC_TRNS,    KC_BSPC),

	[_FUNCTION] = LAYOUT(
            KC_F13,     KC_F14,     KC_F15,     KC_F16,     KC_F17,             KC_F10,     KC_F7,      KC_F8,      KC_F9,      KC_PSCR,
            OSM_LGUI,   OSM_LALT,   OSM_LCTL,   OSM_LSFT,   OTHER,              KC_F11,     KC_F4,      KC_F5,      KC_F6,      KC_INS,
            OSM_RGUI,   OSM_RALT,   OSM_RCTL,   OSM_RSFT,   KC_TRNS,            KC_F12,     KC_F1,      KC_F2,      KC_F3,      KC_TRNS,
                                    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS,    KC_TRNS),

	[_MEDIA] = LAYOUT(
            KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,              KC_BRIU,    KC_NO,      KC_MSTP,    KC_MPLY,    KC_NO,
            KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,              KC_BRID,    KC_MPRV,    KC_VOLD,    KC_VOLU,    KC_MNXT,
            KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,              KC_NO,      KC_MUTE,    KC_NO,      KC_NO,      KC_NO,
                                    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS,    KC_TRNS),
	[_OTHER] = LAYOUT(
            QWERTY,     KC_NO,      KC_NO,      KC_NO,      KC_ESC,             RGB_VAI,    RGB_RMOD,   RGB_TOG,    RGB_MOD,    RGB_M_P,
            QK_MAKE,    KC_NO,      KC_NO,      KC_NO,      KC_ENT,             RGB_VAD,    RGB_SPI,    RGB_HUI,    RGB_SAI,    RGB_M_B,
            QK_BOOT,    QK_MAKE,    COLEMAK_DH, KC_NO,      KC_NO,              KC_NO,      RGB_SPD,    RGB_HUD,    RGB_SAD,    RGB_M_SW,
                                    KC_NO,      KC_NO,      KC_NO,              KC_LCTL,    KC_LSFT),

	[_POINTER] = LAYOUT(
            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
            GUI_TRNS,   ALT_TRNS,   CTL_TRNS,   SFT_TRNS,   KC_TRNS,            KC_TRNS,    KC_TRNS,    KC_BTN3,    KC_TRNS,    KC_TRNS,
            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS,    KC_BTN1,    KC_BTN2,    DRGSCRL,    KC_TRNS,
                                    KC_LCTL,    KC_TRNS,    KC_TRNS,            KC_TRNS,    KC_TRNS),

     [_WEB] = LAYOUT(
            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS,    KC_WSCH,    KC_WREF,    KC_WSTP,    KC_TRNS,
                                    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_WBAK,    KC_WFWD),

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

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
void disable_pointer_layer(void) {
    auto_pointer_layer_timer = 0;
    pointer_key_held         = false;
    layer_off(_POINTER);
#    ifdef RGB_MATRIX_ENABLE
    rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
#    endif // RGB_MATRIX_ENABLE
}
#endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    // Proccess case modes
    if (!process_case_modes(keycode, record)) {
        return false;
    }

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
    // Turn off pointer layer if keys on other layers are pressed.
    // Helps with typing soon after using the trackball.
    if (record->event.pressed) {
        if (IS_LAYER_ON(_POINTER)) {
            uint16_t pointer_keycode = keymap_key_to_keycode(_POINTER, record->event.key);
            switch (pointer_keycode) {
                case KC_NO:
                case KC_TRNS:
                    disable_pointer_layer();
                    break;
                default:
                    pointer_key_held         = true;
                    auto_pointer_layer_timer = timer_read();
                    break;
            }
        }
    } else {
        if (IS_LAYER_ON(_POINTER)) {
            auto_pointer_layer_timer = timer_read();
            pointer_key_held         = false;
        }
    }
#endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

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

#ifdef POINTING_DEVICE_ENABLE
#    ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
        if (auto_pointer_layer_timer == 0) {
            layer_on(_POINTER);
#        ifdef RGB_MATRIX_ENABLE
            rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
            rgb_matrix_sethsv_noeeprom(RGB_MATRIX_DEFAULT_HUE, RGB_MATRIX_DEFAULT_SAT, 200);
#        endif // RGB_MATRIX_ENABLE
        }
        auto_pointer_layer_timer = timer_read();
    }
    return mouse_report;
}

void matrix_scan_user(void) {
    if (!pointer_key_held && auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        disable_pointer_layer();
    }
}
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // CHARYBDIS_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

bool combo_should_trigger(uint16_t combo_index, combo_t* combo, uint16_t keycode, keyrecord_t* record) {
    switch (combo_index) {
        case COMBO_QWERTY_LALT:
        case COMBO_QWERTY_LGUI:
        case COMBO_QWERTY_LCTL:
        case COMBO_QWERTY_LALTGUI:
        case COMBO_QWERTY_LCTLALT:
        case COMBO_QWERTY_LCTLALTGUI:
        case COMBO_QWERTY_RALT:
        case COMBO_QWERTY_RGUI:
        case COMBO_QWERTY_RCTL:
        case COMBO_QWERTY_RALTGUI:
        case COMBO_QWERTY_RCTLALT:
        case COMBO_QWERTY_RCTLALTGUI: {
            return !layer_state_is(_COLEMAK_DH);
        }
        case COMBO_COLEMAK_LALT:
        case COMBO_COLEMAK_LGUI:
        case COMBO_COLEMAK_LCTL:
        case COMBO_COLEMAK_LALTGUI:
        case COMBO_COLEMAK_LCTLALT:
        case COMBO_COLEMAK_LCTLALTGUI:
        case COMBO_COLEMAK_RALT:
        case COMBO_COLEMAK_RGUI:
        case COMBO_COLEMAK_RCTL:
        case COMBO_COLEMAK_RALTGUI:
        case COMBO_COLEMAK_RCTLALT:
        case COMBO_COLEMAK_RCTLALTGUI: {
            return !layer_state_is(_QWERTY);
        }
    }

    return true;
}
