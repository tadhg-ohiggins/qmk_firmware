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

/*
 * Trying to get : on tap ; on hold to work; from https://docs.qmk.fm/#/feature_tap_dance?id=example-3
*/
// Enums for the tap dance keys that send specific non-modifier keys on hold.
enum {
    A_AUDIO,
    SCLN_MISC,
};

enum layernames {
    _BASE,
    _NUMBER1,
    _SYMBOL1,
    _CONTROL,
    _NUMBER2,
    _SYMBOL2,
};

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    tap_dance_action_t *action;

    switch (keycode) {
        case LT(2, C(KC_A)):
          if (record->tap.count && record->event.pressed) {
                tap_code16(C(KC_A)); // Send Ctrl-A on tap
                return false;         // Return false to ignore further processing of key
            }
            break;
        case TD(A_AUDIO):  // list all tap dance keycodes with tap-hold configurations
            action = &tap_dance_actions[TD_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
            return true;
        // case TD(L_SYM):  // list all tap dance keycodes with tap-hold configurations
        //     action = &tap_dance_actions[TD_INDEX(keycode)];
        //     if (!record->event.pressed && action->state.count && !action->state.finished) {
        //         tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
        //         tap_code16(tap_hold->tap);
        //     }
        //     return true;
        // case TD(S_SYM):  // list all tap dance keycodes with tap-hold configurations
        //     action = &tap_dance_actions[TD_INDEX(keycode)];
        //     if (!record->event.pressed && action->state.count && !action->state.finished) {
        //         tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
        //         tap_code16(tap_hold->tap);
        //     }
        //     return true;
        case TD(SCLN_MISC):  // list all tap dance keycodes with tap-hold configurations
            action = &tap_dance_actions[TD_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
            return true;
    }
    return true;
}

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

tap_dance_action_t tap_dance_actions[] = {
    [A_AUDIO] = ACTION_TAP_DANCE_TAP_HOLD(KC_A, KC_F14),
    // [L_SYM] = ACTION_TAP_DANCE_TAP_HOLD(KC_L, KC_F15),
    // [S_SYM] = ACTION_TAP_DANCE_TAP_HOLD(KC_S, KC_F15),
    [SCLN_MISC] = ACTION_TAP_DANCE_TAP_HOLD(KC_SCLN, KC_F13),
};

// const uint16_t PROGMEM test_combo1[] = {KC_A, KC_B, COMBO_END};
// combo_t key_combos[] = {
//     COMBO(test_combo1, MO(4)),
// };


// Experimental leader work I eventually gave up on:
// #define LEADER_TIMEOUT 350
// void leader_start_user(void) {
//     // Do something when the leader key is pressed
// }
//
// void leader_end_user(void) {
//     bool did_leader_succeed = false;
//
//     if (leader_sequence_one_key(QK_LEAD)) {
//         // leader, ; -> —
//         tap_code16(LSA(KC_MINUS));
//         did_leader_succeed = true;
//     } else if (leader_sequence_one_key(KC_SPACE)) {
//         // leader, space -> ;space
//         tap_code16(KC_SEMICOLON);
//         tap_code16(KC_SPACE);
//         did_leader_succeed = true;
//     } else if (leader_sequence_one_key(KC_ENTER)) {
//         // leader, enter -> ;enter
//         tap_code16(KC_SEMICOLON);
//         tap_code16(KC_ENTER);
//         did_leader_succeed = true;
//     } else if (leader_sequence_one_key(KC_Q)) {
//         // leader, q -> “
//         tap_code16(A(KC_LEFT_BRACKET));
//         did_leader_succeed = true;
//     } else if (leader_sequence_two_keys(KC_LSFT, KC_Q) || leader_sequence_two_keys(KC_RSFT, KC_Q)) {
//         // leader, Q -> “
//         tap_code16(LSA(KC_LEFT_BRACKET));
//         did_leader_succeed = true;
//     // } else if (leader_sequence_two_keys(KC_RSFT, KC_Q)) {
//     //     // leader, Q -> “
//     //     tap_code16(LSA(KC_LEFT_BRACKET));
//     //     did_leader_succeed = true;
//     } else if (leader_sequence_one_key(KC_P)) {
//         // leader, p -> (
//         tap_code16(S(KC_9));
//         did_leader_succeed = true;
//     } else if (leader_sequence_two_keys(KC_LSFT, KC_P) || leader_sequence_two_keys(KC_RSFT, KC_P)) {
//         // leader, P -> )
//         tap_code16(S(KC_0));
//         did_leader_succeed = true;
//     } else if (leader_sequence_one_key(KC_B)) {
//         // leader, b -> [
//         tap_code16(KC_LEFT_BRACKET);
//         did_leader_succeed = true;
//     } else if (leader_sequence_two_keys(KC_LSFT, KC_B) || leader_sequence_two_keys(KC_RSFT, KC_B)) {
//         // leader, B -> ]
//         tap_code16(KC_RIGHT_BRACKET);
//         did_leader_succeed = true;
//     }
//
//     if (did_leader_succeed) {
//     } else {
//         tap_code16(KC_SEMICOLON);
//     }
// }
//
//
// const key_override_t semicolon_key_override = ko_make_basic(MOD_MASK_SHIFT, QK_LEAD, S(KC_SEMICOLON));
//
// // This globally defines all key overrides to be used
// const key_override_t **key_overrides = (const key_override_t *[]){
//     &semicolon_key_override,
//     NULL // Null terminate the array of overrides!
// };




const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  LT(3, KC_BSPC),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, TD(A_AUDIO),LT(2, KC_S),ALT_T(KC_D),CMD_T(KC_F),KC_G,            KC_H,    CMD_T(KC_J),ALT_T(KC_K),LT(2, KC_L),TD(SCLN_MISC),RCTL_T(KC_QUOT),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_BSLS,//KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          //KC_LGUI,   MO(1),SFT_T(KC_SPC), SFT_T(KC_ENT),MO(2), KC_RALT
                                          KC_LGUI,   MO(1),SFT_T(KC_SPC), SFT_T(KC_ENT),LT(2, C(KC_A)), KC_RALT
                                      //`--------------------------'  `--------------------------'

  ),
  // Number layout 1

    [_NUMBER1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     LGUI(KC_GRV), KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, KC_PGUP,                      KC_MINS,    KC_4,    KC_5,    KC_6, S(KC_8),  KC_EQL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, KC_HOME,  KC_END, KC_PGDN,                      KC_PLUS,    KC_1,    KC_2,    KC_3, KC_SLSH, KC_BSLS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT,   MO(3),    KC_0
                                      //`--------------------------'  `--------------------------'
  ),
  // Symbol layout 1

    [_SYMBOL1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------------------------------.                    ,-----------------------------------------------------------------------------------.
        // TAB          Q             W             E             R             T                                  Y             U             I           O             P                BACKSPACE
        // ⇥            !             @             #             $             %                                  ^             &             *           +             ~                ⌦
           KC_TAB,      S(KC_1),      S(KC_2),      S(KC_3),      S(KC_4),      S(KC_5),                           S(KC_6),      S(KC_7),      S(KC_8),    S(KC_EQL),    S(KC_GRV),       KC_DEL,
  //|-------------+-------------+-------------+-------------+-------------+-------------|                    |-------------+-------------+-------------+-------------+-------------+-------------|
       // CONTROL    A           S                  D             F            G                                   H          J                 K         L           SEMICOLON         QUOTE
       // ⎈          “           ”                  (             )            `                                   -          _                 =         – (en dash) — (em dash)       '
          KC_LCTL,   A(KC_LBRC), LSA(KC_LBRC),      S(KC_9),      S(KC_0),     KC_GRAVE,                           KC_MINS,   S(KC_MINS),       KC_EQL,   A(KC_MINS), LSA(KC_MINS),     KC_QUOTE,
  //|-------------+-------------+-------------+-------------+-------------+-------------|                    |-------------+-------------+-------------+-------------+-------------+-------------|
       //   SHIFT       Z             X          C             V                B                                  N          M             COMMA         PERIOD      SLASH             SHIFT
       //               [             ]          {             }                •                                  \          |             …             «           »
            MO(5),      KC_LBRC,      KC_RBRC,   S(KC_LBRC),   S(KC_RBRC),      A(KC_8),                           KC_BSLS,   S(KC_BSLS),   A(KC_SCLN),   A(KC_BSLS), LSA(KC_BSLS),     MO(5),
  //|-------------+-------------+-------------+-------------+-------------+-------------+-------------|  |------+----------+-------------+-------------+-------------+-------------+-------------|
                                                                    KC_LGUI,        MO(3),       MO(5),   MO(5),      _______,      KC_RALT
                                                                  //`---------------------------------'  `----------------------------------'
  ),
  // Control layout

    [_CONTROL] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_KB_POWER,                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
    ),
  // Number layout 2

    [_NUMBER2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     LGUI(KC_GRV), KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                         KC_0,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, S(KC_SCLN), KC_COMM, KC_DOT,KC_SLSH, KC_PGUP,                      KC_MINS,    KC_4,    KC_5,    KC_6, S(KC_SCLN),RCTL_T(KC_QUOT),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, KC_HOME,  KC_END, KC_PGDN,                         KC_0,    KC_1,    KC_2,    KC_3, KC_SLSH, KC_BSLS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT,   MO(3),    KC_0
                                      //`--------------------------'  `--------------------------'
    ),
  // Symbol layout 2

    [_SYMBOL2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------------------------------.                    ,-----------------------------------------------------------------------------------.
         // TAB          Q            W           E            R            T                                      Y             U          I              O            P                BACKSPACE
         // ⇥                                     €            ®            ∴                                                               ∞              °            ¢                 ⌦
            KC_TAB,      XXXXXXX,     XXXXXXX,    RSA(KC_2),   RALT(KC_R),  RSA(KC_F13),                           XXXXXXX,      XXXXXXX,   RALT(KC_5),    RSA(KC_8),   RALT(KC_4),       KC_DEL,
  //|-------------+-------------+-------------+-------------+-------------+-------------|                    |-------------+-------------+-------------+-------------+-------------+-------------|
        // CONTROL  A              S              D               F             G                              H                 J         K                 L           SEMICOLON         QUOTE
          //        Ⓐ              √              ‡               Reserved                                     ― (horiz. dash)             ™
           KC_LCTL, RSA(KC_F14),   RALT(KC_V),    RSA(KC_7),      XXXXXXX,      XXXXXXX,                       RSA(KC_F15),      XXXXXXX,   RALT(KC_2),      XXXXXXX,       XXXXXXX,      XXXXXXX,
  //|-------------+-------------+-------------+-------------+-------------+-------------|                    |-------------+-------------+-------------+-------------+-------------+-------------|
        // SHIFT    Z             X              C            V                 B                                  N         M                 COMMA         PERIOD        SLASH         SHIFT
          //        ℞             ×              ©            ∕ (division slash)                                   Reserved  − (minus)
           KC_LSFT, RSA(KC_F16),  RSA(KC_F19),   RALT(KC_G),  RSA(KC_F17),      XXXXXXX,                           XXXXXXX,  RSA(KC_F18),      XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,
  //|-------------+-------------+-------------+-------------+-------------+-------------+-------------|  |------+----------+-------------+-------------+-------------+-------------+-------------|
                                                                    KC_LGUI,        MO(3),       KC_SPC,   KC_ENT,      _______,      KC_RALT
                                                                  //`---------------------------------'  `----------------------------------'
  ),
  // ),
  //
  //   [4] = LAYOUT_split_3x6_3(
  // //,-----------------------------------------------------.                    ,-----------------------------------------------------.
  //     XXXXXXX, RALT(KC_LBRC), RSA(KC_LBRC), KC_PIPE, KC_DLR, KC_TILD,             KC_LBRC, KC_RBRC, KC_PLUS, KC_ASTR, KC_PERC, XXXXXXX,
  // //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
  //     XXXXXXX, KC_AT, RALT(KC_8), RALT(KC_MINS), KC_UNDS, KC_GRV,           KC_MINS, KC_LPRN, KC_RPRN, KC_EQL, RSA(KC_MINS), XXXXXXX,
  // //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
  //     XXXXXXX, KC_AMPR, RSA(KC_F19), KC_HASH, KC_CIRC, KC_EXLM,                 S(KC_LBRC), S(KC_RBRC), RALT(KC_SCLN), RALT(KC_BSLS), RSA(KC_BSLS), XXXXXXX,
  // //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
  //                                         KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
  //                                     //`--------------------------'  `--------------------------'
  // )
};



