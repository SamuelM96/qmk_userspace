#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif

#include <string.h>

#include "casemodes.h"

#include "quantum/keymap_extras/keymap_uk.h"
#include "quantum/keymap_extras/sendstring_uk.h"

enum layers {
    _QWERTY = 0,
    _FOCAL,
    _NAV,
    _NUM,
    _SYM,
    _FUNCTION,
    _MEDIA,
    _OTHER,
    _WEB,
    _MOUSE,
    _MACRO,
};

enum custom_keycodes {
    SNAKECASE = SAFE_RANGE,
    JIGGLE,
};

#define LAYOUT LAYOUT_split_3x5_2

#define ESC_MED LT(_MEDIA, KC_ESC)
#define SPC_NAV LT(_NAV, KC_SPC)
#define TAB_FUN LT(_FUNCTION, KC_TAB)
#define ENT_SYM LT(_SYM, KC_ENT)
#define BSP_NUM LT(_NUM, KC_BSPC)

// Aliases for readability
#define QWERTY DF(_QWERTY)
#define FOCAL DF(_FOCAL)

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
// TODO: Needs Focal support. KC_TRNS didn't work
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

bool mouse_jiggler_enabled = false;
uint32_t idle_timeout   = 30000; // (after 30s)
uint32_t mouse_interval = 10000; // (every 10s)

#define COMBO_SHOULD_TRIGGER
enum combos {
    // L/R is used to denote keyboard side, not keycodes
    COMBO_QWERTY_LCTL,
    COMBO_QWERTY_LALT,
    COMBO_QWERTY_LGUI,
    COMBO_QWERTY_LCTLALT,
    COMBO_QWERTY_LALTGUI,
    COMBO_QWERTY_LCTLALTGUI,
    COMBO_QWERTY_MOUSE,

    COMBO_QWERTY_RCTL,
    COMBO_QWERTY_RALT,
    COMBO_QWERTY_RGUI,
    COMBO_QWERTY_RCTLALT,
    COMBO_QWERTY_RALTGUI,
    COMBO_QWERTY_RCTLALTGUI,
    COMBO_QWERTY_CTLSPC,

    COMBO_FOCAL_LCTL,
    COMBO_FOCAL_LALT,
    COMBO_FOCAL_LGUI,
    COMBO_FOCAL_LCTLALT,
    COMBO_FOCAL_LALTGUI,
    COMBO_FOCAL_LCTLALTGUI,
    COMBO_FOCAL_MOUSE,

    COMBO_FOCAL_RCTL,
    COMBO_FOCAL_RALT,
    COMBO_FOCAL_RGUI,
    COMBO_FOCAL_RCTLALT,
    COMBO_FOCAL_RALTGUI,
    COMBO_FOCAL_RCTLALTGUI,
    COMBO_FOCAL_CTLSPC,

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
const uint16_t PROGMEM cv_combo[]   = {KC_C, KC_V, COMBO_END};

const uint16_t PROGMEM jk_combo[]      = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM jl_combo[]      = {KC_J, KC_L, COMBO_END};
const uint16_t PROGMEM jscln_combo[]   = {KC_J, UK_SCLN, COMBO_END};
const uint16_t PROGMEM jkl_combo[]     = {KC_J, KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM jkscln_combo[]  = {KC_J, KC_K, UK_SCLN, COMBO_END};
const uint16_t PROGMEM jklscln_combo[] = {KC_J, KC_K, KC_L, UK_SCLN, COMBO_END};
const uint16_t PROGMEM commam_combo[]  = {UK_COMM, KC_M, COMBO_END};

// Focal layer
const uint16_t PROGMEM tn_combo[]   = {KC_T, KC_N, COMBO_END};
const uint16_t PROGMEM tr_combo[]   = {KC_T, KC_R, COMBO_END};
const uint16_t PROGMEM ts_combo[]   = {KC_T, KC_S, COMBO_END};
const uint16_t PROGMEM tnr_combo[]  = {KC_T, KC_N, KC_S, COMBO_END};
const uint16_t PROGMEM tns_combo[]  = {KC_T, KC_R, KC_S, COMBO_END};
const uint16_t PROGMEM tnrs_combo[] = {KC_T, KC_N, KC_R, KC_S, COMBO_END};
const uint16_t PROGMEM md_combo[]   = {KC_M, KC_D, COMBO_END};

const uint16_t PROGMEM ca_combo[]     = {KC_C, KC_A, COMBO_END};
const uint16_t PROGMEM ce_combo[]     = {KC_C, KC_E, COMBO_END};
const uint16_t PROGMEM ci_combo[]     = {KC_C, KC_I, COMBO_END};
const uint16_t PROGMEM cae_combo[]    = {KC_C, KC_A, KC_E, COMBO_END};
const uint16_t PROGMEM cai_combo[]    = {KC_C, KC_A, KC_I, COMBO_END};
const uint16_t PROGMEM caei_combo[]   = {KC_C, KC_A, KC_E, KC_I, COMBO_END};
const uint16_t PROGMEM wdot_combo[]   = {KC_W, UK_DOT, COMBO_END};

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
    [COMBO_QWERTY_MOUSE]      = COMBO(cv_combo, MO(_MOUSE)),

    [COMBO_QWERTY_RCTL]        = COMBO(jk_combo, KC_LCTL),
    [COMBO_QWERTY_RALT]        = COMBO(jl_combo, KC_LALT),
    [COMBO_QWERTY_RGUI]        = COMBO(jscln_combo, KC_LGUI),
    [COMBO_QWERTY_RCTLALT]     = COMBO(jkl_combo, LALT(KC_LCTL)),
    [COMBO_QWERTY_RALTGUI]     = COMBO(jkscln_combo, LALT(KC_LGUI)),
    [COMBO_QWERTY_RCTLALTGUI]  = COMBO(jklscln_combo, LCA(KC_LGUI)),
    [COMBO_QWERTY_CTLSPC]      = COMBO(commam_combo, LCTL(KC_SPC)),

    [COMBO_FOCAL_LCTL]       = COMBO(tn_combo, KC_LCTL),
    [COMBO_FOCAL_LALT]       = COMBO(tr_combo, KC_LALT),
    [COMBO_FOCAL_LGUI]       = COMBO(ts_combo, KC_LGUI),
    [COMBO_FOCAL_LCTLALT]    = COMBO(tnr_combo, LALT(KC_LCTL)),
    [COMBO_FOCAL_LALTGUI]    = COMBO(tns_combo, LALT(KC_LGUI)),
    [COMBO_FOCAL_LCTLALTGUI] = COMBO(tnrs_combo, LCA(KC_LGUI)),
    [COMBO_FOCAL_MOUSE]      = COMBO(md_combo, MO(_MOUSE)),

    [COMBO_FOCAL_RCTL]       = COMBO(ca_combo, KC_LCTL),
    [COMBO_FOCAL_RALT]       = COMBO(ce_combo, KC_LALT),
    [COMBO_FOCAL_RGUI]       = COMBO(ci_combo, KC_LGUI),
    [COMBO_FOCAL_RCTLALT]    = COMBO(cae_combo, LALT(KC_LCTL)),
    [COMBO_FOCAL_RALTGUI]    = COMBO(cai_combo, LALT(KC_LGUI)),
    [COMBO_FOCAL_RCTLALTGUI] = COMBO(caei_combo, LCA(KC_LGUI)),
    [COMBO_FOCAL_CTLSPC]      = COMBO(wdot_combo, LCTL(KC_SPC)),

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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
            UK_Q,       UK_W,       UK_E,       UK_R,       UK_T,               UK_Y,       UK_U,       UK_I,       UK_O,         UK_P,
            UK_A,       UK_S,       UK_D,       UK_F,       UK_G,               UK_H,       UK_J,       UK_K,       UK_L,         UK_SCLN,
            L_WEB(UK_Z),UK_X,       UK_C,       UK_V,       UK_B,               UK_N,       UK_M,       UK_COMM,    UK_DOT,  L_WEB(UK_SLSH),
                                                SPC_NAV,    NUM_ESC,            SYM,    KC_LSFT),

    [_FOCAL] = LAYOUT(
            UK_V,       UK_L,       UK_H,       UK_G,       UK_K,               UK_Q,       UK_F,       UK_O,       UK_U,         UK_J,
            UK_S,       UK_R,       UK_N,       UK_T,       UK_B,               UK_Y,       UK_C,       UK_A,       UK_E,         UK_I,
            L_WEB(UK_Z),UK_X,       UK_M,       UK_D,       UK_P,               UK_QUOT,    UK_W,       UK_DOT,     UK_SCLN,      L_WEB(UK_COMM),
                                                SPC_NAV,    NUM_ESC,            SYM,    KC_LSFT),

	[_NAV] = LAYOUT(
            MACRO,      KC_TRNS,    QK_AREP,    QK_REP,     KC_ESC,             G(S(KC_PSCR)),KC_HOME,    KC_PGDN,    KC_PGUP,    KC_END,
            OSM_LGUI,   OSM_LALT,   OSM_LCTL,   OSM_LSFT,   KC_ENT,             KC_TAB,       KC_LEFT,    KC_DOWN,    KC_UP,      KC_RGHT,
            KC_CAPS,    OSM_RALT,   CW_TOGG,    SNAKECASE,  KC_SPC,             KC_DEL,       KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                                                KC_TRNS,    OTHER,              MEDIA,      KC_BSPC),

	[_NUM] = LAYOUT(
            UK_LBRC,    UK_LABK,    UK_MINS,    UK_RABK,    UK_RBRC,            KC_LEFT,    KC_7,       KC_8,       KC_9,       KC_RIGHT,
            OSM_LGUI,   OSM_LALT,   OSM_LCTL,   OSM_LSFT,   UK_RCBR,            KC_DOWN,    KC_4,       KC_5,       KC_6,       KC_UP,
            UK_BSLS,    UK_ASTR,    UK_COLN,    UK_PLUS,    UK_UNDS,            UK_EQL,     KC_1,       KC_2,       KC_3,       UK_DOT,
                                                OTHER,      KC_TRNS,            UK_0,       KC_BSPC),

	[_SYM] = LAYOUT(
            UK_LBRC,    UK_LABK,    UK_MINS,    UK_RABK,    UK_RBRC,            UK_CIRC,    UK_SLSH,    UK_GRV,     UK_HASH,    UK_AT,
            UK_LCBR,    UK_LPRN,    UK_EQL,     UK_RPRN,    UK_RCBR,            UK_PERC,    UK_DLR,     UK_DQUO,    UK_QUOT,    UK_EXLM,
            UK_BSLS,    UK_ASTR,    UK_COLN,    UK_PLUS,    UK_UNDS,            UK_AMPR,    UK_TILD,    UK_QUES,    UK_PIPE,    UK_PND,
                                                ALT_SPC,    FKEYS,              KC_TRNS,    KC_BSPC),

	[_FUNCTION] = LAYOUT(
            KC_F13,     KC_F14,     KC_F15,     KC_F16,     KC_F17,             KC_F10,     KC_F7,      KC_F8,      KC_F9,      KC_PSCR,
            OSM_LGUI,   OSM_LALT,   OSM_LCTL,   OSM_LSFT,   OTHER,              KC_F11,     KC_F4,      KC_F5,      KC_F6,      KC_INS,
            OSM_RGUI,   OSM_RALT,   OSM_RCTL,   OSM_RSFT,   KC_TRNS,            KC_F12,     KC_F1,      KC_F2,      KC_F3,      KC_TRNS,
                                                KC_TRNS,    KC_TRNS,            KC_TRNS,    KC_TRNS),

	[_MEDIA] = LAYOUT(
            KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,              KC_BRIU,    KC_NO,      KC_MSTP,    KC_MPLY,    KC_NO,
            KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,              KC_BRID,    KC_MPRV,    KC_VOLD,    KC_VOLU,    KC_MNXT,
            KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,              KC_NO,      KC_MUTE,    KC_NO,      KC_NO,      KC_NO,
                                                KC_TRNS,    KC_TRNS,            KC_TRNS,    KC_TRNS),

	[_OTHER] = LAYOUT(
            QWERTY,     KC_NO,      KC_NO,      KC_NO,      KC_ESC,             KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,
            QK_MAKE,    KC_NO,      KC_NO,      KC_NO,      KC_ENT,             KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,
            QK_BOOT,    KC_NO,      FOCAL,      KC_NO,      KC_NO,              JIGGLE,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                                                KC_TRNS,    KC_TRNS,            KC_LCTL,    KC_LSFT),

    [_WEB] = LAYOUT(
           KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,             KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
           KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,             KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
           KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,             KC_TRNS,    KC_WSCH,    KC_WREF,    KC_WSTP,    KC_TRNS,
                                               KC_TRNS,    KC_TRNS,             KC_WBAK,    KC_WFWD),

    [_MOUSE] = LAYOUT(
           KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
           KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS,    MS_LEFT,    MS_DOWN,    MS_UP,      MS_RGHT,
           KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS,    KC_TRNS,    MS_BTN3,    KC_TRNS,    KC_TRNS,
                                               KC_TRNS,    KC_TRNS,            MS_BTN1,    MS_BTN2),

	[_MACRO] = LAYOUT(
            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS,    DM_REC1,    DM_RSTP,    DM_REC2,    KC_TRNS,
            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS,    DM_PLY1,    KC_TRNS,    DM_PLY2,    KC_TRNS,
                                                KC_TRNS,    KC_TRNS,            KC_TRNS,    KC_TRNS),

     // [_TEMPLATE] = LAYOUT(
     //        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
     //        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
     //        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
     //                                            KC_TRNS,    KC_TRNS,            KC_TRNS,    KC_TRNS),
};
// clang-format on

static uint32_t idle_callback(uint32_t trigger_time, void* cb_arg) {
    // now idle
    if (mouse_jiggler_enabled) {
        SEND_STRING(SS_TAP(X_F15));
    }
    return mouse_interval;
}

void mouse_jiggle_toggle(void) {
    /* mouse_jiggler_timer   = timer_read(); */
    mouse_jiggler_enabled = !mouse_jiggler_enabled;
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    // on every key event start or extend `idle_callback()` deferred execution after IDLE_TIMEOUT_MS
    static deferred_token idle_token = INVALID_DEFERRED_TOKEN;

    if (!extend_deferred_exec(idle_token, idle_timeout)) {
        idle_token = defer_exec(idle_timeout, idle_callback, NULL);
    }

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

bool combo_should_trigger(uint16_t combo_index, combo_t* combo, uint16_t keycode, keyrecord_t* record) {
    switch (combo_index) {
        case COMBO_QWERTY_LALT:
        case COMBO_QWERTY_LGUI:
        case COMBO_QWERTY_LCTL:
        case COMBO_QWERTY_LALTGUI:
        case COMBO_QWERTY_LCTLALT:
        case COMBO_QWERTY_LCTLALTGUI:
        case COMBO_QWERTY_MOUSE:
        case COMBO_QWERTY_CTLSPC:
        case COMBO_QWERTY_RALT:
        case COMBO_QWERTY_RGUI:
        case COMBO_QWERTY_RCTL:
        case COMBO_QWERTY_RALTGUI:
        case COMBO_QWERTY_RCTLALT:
        case COMBO_QWERTY_RCTLALTGUI: {
            return !layer_state_is(_FOCAL);
        }
        case COMBO_FOCAL_LALT:
        case COMBO_FOCAL_LGUI:
        case COMBO_FOCAL_LCTL:
        case COMBO_FOCAL_LALTGUI:
        case COMBO_FOCAL_LCTLALT:
        case COMBO_FOCAL_LCTLALTGUI:
        case COMBO_FOCAL_MOUSE:
        case COMBO_FOCAL_CTLSPC:
        case COMBO_FOCAL_RALT:
        case COMBO_FOCAL_RGUI:
        case COMBO_FOCAL_RCTL:
        case COMBO_FOCAL_RALTGUI:
        case COMBO_FOCAL_RCTLALT:
        case COMBO_FOCAL_RCTLALTGUI: {
            return !layer_state_is(_QWERTY);
        }
    }

    return true;
}
