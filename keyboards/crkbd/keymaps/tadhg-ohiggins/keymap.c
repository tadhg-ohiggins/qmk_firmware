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
    [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, RCTL_T(KC_QUOT),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   MO(1),  KC_SPC,     KC_ENT,   MO(2), KC_RALT
                                      //`--------------------------'  `--------------------------'

  ),

    [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     LGUI(KC_GRV), KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, XXXXXXX,                      KC_PLUS,    KC_4,    KC_5,    KC_6, OSL(2),  KC_EQL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_MINS,    KC_1,    KC_2,    KC_3, KC_SLSH, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT,   MO(3),    KC_0
                                      //`--------------------------'  `--------------------------'
  ),




    [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       //KC_TAB, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
         KC_TAB,   S(KC_1),   S(KC_2),   S(KC_3),   S(KC_4),   S(KC_5),                        S(KC_6),   S(KC_7),   S(KC_8), S(KC_EQL), S(KC_GRV),    KC_BSPC,
  //|----------+----------+----------+----------+----------+----------|                    |----------+----------+----------+----------+----------+----------|
      // KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
        KC_LCTL, A(KC_LBRC), LSA(KC_LBRC), S(KC_9), S(KC_0),  KC_GRAVE,                        KC_MINS, S(KC_MINS),   KC_EQL, A(KC_MINS), LSA(KC_MINS), KC_QUOTE,
  //|----------+----------+----------+----------+----------+----------|                    |----------+----------+----------+----------+----------+----------|
      // KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
        KC_LSFT,   KC_LBRC,   KC_RBRC, S(KC_LBRC), S(KC_RBRC), A(KC_8),                        KC_BSLS, S(KC_BSLS), A(KC_SCLN), A(KC_BSLS), LSA(KC_BSLS), XXXXXXX,
  //|----------+----------+----------+----------+----------+----------+----------|  |------+----------+----------+----------+----------+----------+----------|
                                                    KC_LGUI,     MO(3),    KC_SPC,   KC_ENT,   _______,   KC_RALT
                                                    //`--------------------------'  `--------------------------'
  ),

    [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
    )
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



