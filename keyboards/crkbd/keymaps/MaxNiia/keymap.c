/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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
#include <stdio.h>

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Tap dance enums
enum {
    F_SFT,
    D_CTL,
    S_ALT,
    J_SFT,
    K_CTL,
    L_ALT,
};

td_state_t cur_dance(tap_dance_state_t *state);

void f_finished(tap_dance_state_t *state, void *user_data);
void f_reset(tap_dance_state_t *state, void *user_data);
void d_finished(tap_dance_state_t *state, void *user_data);
void d_reset(tap_dance_state_t *state, void *user_data);
void s_finished(tap_dance_state_t *state, void *user_data);
void s_reset(tap_dance_state_t *state, void *user_data);
void j_finished(tap_dance_state_t *state, void *user_data);
void j_reset(tap_dance_state_t *state, void *user_data);
void k_finished(tap_dance_state_t *state, void *user_data);
void k_reset(tap_dance_state_t *state, void *user_data);
void l_finished(tap_dance_state_t *state, void *user_data);
void l_reset(tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------------------------.                    ,-----------------------------------------------------------------------------.
          KC_LBRC,        KC_Q,        KC_W,        KC_E,        KC_R,        KC_T,                             KC_Y,        KC_U,        KC_I,        KC_O,        KC_P,     KC_RBRC,
  //|------------+------------+------------+------------+------------+------------|                    |------------+------------+------------+------------+------------+------------|
           KC_TAB,        KC_A,  TD(S_ALT),    TD(D_CTL),   TD(F_SFT),        KC_G,                             KC_H,   TD(J_SFT),   TD(K_CTL),   TD(L_ALT),     KC_SCLN,     KC_QUOT,
  //|------------+------------+------------+------------+------------+------------|                    |------------+------------+------------+------------+------------+------------|
          CW_TOGG,        KC_Z,        KC_X,        KC_C,        KC_V,        KC_B,                             KC_N,        KC_M,     KC_COMM,      KC_DOT,     KC_SLSH,     KC_LGUI,
  //|------------+------------+------------+------------+------------+------------|                    |------------+------------+------------+------------+------------+------------|
                                          LT(1,KC_MINUS),      KC_SPC,      KC_ENT,                           KC_ESC,     KC_BSPC,LT(2,KC_DEL)
                                         //`--------------------------------------'                    `--------------------------------------'
  ),

  [1] = LAYOUT_split_3x6_3(
  //|------------+------------+------------+------------+------------+------------|                    |------------+------------+------------+------------+------------+------------|
          KC_TRNS,    KC_MINUS,        KC_7,        KC_8,        KC_9,     KC_PLUS,                            KC_NO,       KC_F9,      KC_F10,      KC_F11,      KC_F12,     KC_TRNS,
  //|------------+------------+------------+------------+------------+------------|                    |------------+------------+------------+------------+------------+------------|
          KC_TRNS,        KC_0,LALT_T(KC_4),LCTL_T(KC_5),LSFT_T(KC_6),     KC_PERC,                            KC_NO,RSFT_T(KC_F5),RCTL_T(KC_F6),RALT_T(KC_F7),    KC_F8,       KC_NO,
  //|------------+------------+------------+------------+------------+------------|                    |------------+------------+------------+------------+------------+------------|
          KC_TRNS,    KC_EQUAL,        KC_1,        KC_2,        KC_3,     KC_ASTR,                            KC_NO,       KC_F1,       KC_F2,       KC_F3,       KC_F4,     KC_TRNS,
  //|------------+------------+------------+------------+------------+------------|                    |------------+------------+------------+------------+------------+------------|
                                                 KC_TRNS,     KC_TRNS,     KC_TRNS,                          KC_TRNS,     KC_TRNS,LT(3,KC_DEL)
                                         //`--------------------------------------'                    `--------------------------------------'
  ),

  [2] = LAYOUT_split_3x6_3(
  //|------------+------------+------------+------------+------------+------------|                    |------------+------------+------------+------------+------------+------------|
          KC_TRNS,     KC_QUES,      KC_GRV,     KC_TILD,     KC_LPRN,     KC_RPRN,                          KC_CIRC,     KC_AMPR,    KC_MINUS,     KC_UNDS,      KC_DLR,     KC_TRNS,
  //|------------+------------+------------+------------+------------+------------|                    |------------+------------+------------+------------+------------+------------|
          KC_TRNS,     KC_EXLM,       KC_AT,     KC_HASH,     KC_LCBR,     KC_RCBR,                          KC_PERC,     KC_ASTR,     KC_PLUS,    KC_EQUAL,     KC_TRNS,     KC_TRNS,
  //|------------+------------+------------+------------+------------+------------|                    |------------+------------+------------+------------+------------+------------|
          KC_TRNS,     KC_BSLS,     KC_PIPE,     KC_PERC,     KC_LBRC,     KC_RBRC,                          KC_QUOT,      KC_DLR,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,
  //|------------+------------+------------+------------+------------+------------|                    |------------+------------+------------+------------+------------+------------|
                                          LT(3,KC_MINUS),     KC_TRNS,     KC_TRNS,                          KC_TRNS,     KC_TRNS,     KC_TRNS
                                         //`--------------------------------------'                    `--------------------------------------'
  ),

  [3] = LAYOUT_split_3x6_3(
  //|------------+------------+------------+------------+------------+------------|                    |------------+------------+------------+------------+------------+------------|
          KC_TRNS,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       TO(5),                            TO(4),       KC_NO,      KC_INS,       KC_NO,     KC_PSCR,     KC_TRNS,
  //|------------+------------+------------+------------+------------+------------|                    |------------+------------+------------+------------+------------+------------|
          KC_TRNS, KC_HOME,LALT_T(KC_PGDN),LCTL_T(KC_PGUP), LSFT_T(KC_END),  KC_NO,                          KC_LEFT,     KC_DOWN,       KC_UP,     KC_RGHT,       KC_NO,     KC_TRNS,
  //|------------+------------+------------+------------+------------+------------|                    |------------+------------+------------+------------+------------+------------|
          KC_TRNS,       KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,                            KC_NO,       KC_NO,       KC_NO,       KC_NO,       KC_NO,     KC_TRNS,
  //|------------+------------+------------+------------+------------+------------|                    |------------+------------+------------+------------+------------+------------|
                                                KC_TRNS,      KC_TRNS,     KC_TRNS,                          KC_TRNS,     KC_TRNS,     KC_TRNS
                                         //`--------------------------------------'                    `--------------------------------------'
  ),

  [4] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        NK_ON, RGB_TOG,   KC_NO,   KC_NO, QK_BOOT,  QK_RBT,                        TO(0),   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_NO, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_NO,RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_NO,   KC_NO,   KC_NO,      KC_NO,   KC_NO,   KC_NO
                                      //`--------------------------'  `--------------------------'
  ),

  [5] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,    TO(0),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H, KC_RIGHT,  KC_UP, KC_LEFT, KC_SCLN,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_DOWN,  KC_DOT, KC_SLSH, KC_RCTL,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--ff-----+--------+--------+--------|
                                            MO(1),  KC_SPC, KC_LALT,     KC_DEL, KC_BSPC,   KC_NO
                                      //`--------------------------'  `--------------------------'
  )
};

td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }
    else return TD_UNKNOWN;
}

#define CREATE_TAP_DANCE(name, kc, kc_hold) \
static td_tap_t name##tap_state = { \
    .is_press_action = true, \
    .state = TD_NONE \
}; \
void name##_finished(tap_dance_state_t *state, void *user_data) { \
    name##tap_state.state = cur_dance(state); \
    switch (name##tap_state.state) { \
        case TD_SINGLE_TAP: register_code(kc); break; \
        case TD_SINGLE_HOLD: register_code(kc_hold); break; \
        case TD_DOUBLE_HOLD: register_code(kc); break; \
        case TD_DOUBLE_TAP: \
            tap_code(kc); \
            register_code(kc); \
            break; \
        default: break; \
    } \
} \
void name##_reset(tap_dance_state_t *state, void *user_data) { \
    switch (name##tap_state.state) { \
        case TD_SINGLE_TAP: unregister_code(kc); break; \
        case TD_SINGLE_HOLD: unregister_code(kc_hold); break; \
        case TD_DOUBLE_HOLD: unregister_code(kc); break; \
        case TD_DOUBLE_TAP: unregister_code(kc); break; \
        default: break; \
    } \
}

CREATE_TAP_DANCE(f, KC_F, KC_LSFT)
CREATE_TAP_DANCE(d, KC_D, KC_LCTL)
CREATE_TAP_DANCE(s, KC_S, KC_LALT)
CREATE_TAP_DANCE(j, KC_J, KC_RSFT)
CREATE_TAP_DANCE(k, KC_K, KC_RCTL)
CREATE_TAP_DANCE(l, KC_L, KC_RALT)

tap_dance_action_t tap_dance_actions[] = {
    [F_SFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, f_finished, f_reset),
    [D_CTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, d_finished, d_reset),
    [S_ALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, s_finished, s_reset),
    [J_SFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, j_finished, j_reset),
    [K_CTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, k_finished, k_reset),
    [L_ALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, l_finished, l_reset)
};


/* void f_finished(tap_dance_state_t *state, void *user_data) { */
/*     ftap_state.state = cur_dance(state); */
/*     switch (ftap_state.state) { */
/*         case TD_SINGLE_TAP: register_code(KC_F); break; */
/*         case TD_SINGLE_HOLD: register_code(KC_LSFT); break; */
/*         case TD_DOUBLE_HOLD: register_code(KC_F); break; */
/*         // Last case is for fast typing. Assuming your key is `f`: */
/*         // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`. */
/*         // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms. */
/*         case TD_DOUBLE_SINGLE_TAP: tap_code(KC_F); register_code(KC_F); break; */
/*         default: break; */
/*     } */
/* } */

/* void f_reset(tap_dance_state_t *state, void *user_data) { */
/*     switch (ftap_state.state) { */
/*         case TD_SINGLE_TAP: unregister_code(KC_F); break; */
/*         case TD_SINGLE_HOLD: unregister_code(KC_LSFT); break; */
/*         case TD_DOUBLE_HOLD: unregister_code(KC_F); break; */
/*         case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_F); break; */
/*         default: break; */
/*     } */
/*     ftap_state.state = TD_NONE; */
/* } */
