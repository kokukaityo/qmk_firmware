/* Copyright 2019 sekigon-gonnoc
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
#include "bmp.h"
#include "bmp_custom_keycode.h"
#include "keycode_str_converter.h"
#include "twpair_on_jis.h"

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    CUSTOM_KEYCODE_START = BMP_SAFE_RANGE,
};

const key_string_map_t custom_keys_user =
{
    .start_kc    = CUSTOM_KEYCODE_START,
    .end_kc      = CUSTOM_KEYCODE_START,
    .key_strings = "\0"
};

enum layers {
    _QWERTY, _SYMBOL, _ARROW, _NUM
};

// ショートカット
#define sPAUSE LCA(KC_P)      // Ctrl+Alt+P     最前面でポーズ
#define sCAHOME LCA(KC_HOME)  // Ctrl+Alt+HOME  リモートの接続バーを表示
// 拡張キーコード
// #define TH_CAPS EX(TDH(LSFT(KC_CAPS),KC_LCTL))
// #define TH_MHEN EX(TDH(KC_MHEN,KC_SPC))
// #define LT_SMBL EX(LTE(_SYMBOL,KC_SPC))
// #define LT_AROW EX(LTE(_ARROW,KC_ENT))
#define LT_SMBL LT(_SYMBOL, KC_SPC)
#define LT_AROW LT(_ARROW, KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
      KC_ZKHK,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0, sCAHOME,  sPAUSE, XXXXXXX, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC, KC_RBRC, KC_JYEN,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
     KC_LCTRL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
               KC_LGUI, KC_LALT, KC_MHEN, LT_SMBL,              LT_AROW,MO(_NUM),          KC_RALT,  KC_APP
          //`---------------------------------------------|   |--------------------------------------------'
  ),

  [_SYMBOL] = LAYOUT(
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
       KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
      _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILD, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
      _______, KC_HOME, KC_LEFT,   KC_UP, KC_RGHT,  KC_END,     KC_MINS,  KC_EQL, KC_LCBR, KC_RCBR, KC_PIPE,  KC_GRV, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, KC_DOWN, XXXXXXX, XXXXXXX,     KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_BSLS, _______, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
               _______, _______, XXXXXXX, _______,              XXXXXXX, XXXXXXX,          _______, _______
          //`---------------------------------------------|   |--------------------------------------------'
  ),

  [_ARROW] = LAYOUT(
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
       KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     KC_HOME, KC_LEFT,   KC_UP, KC_RGHT,  KC_END, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------|   |---------+--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, KC_DOWN, XXXXXXX, KC_PGDN, _______, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
               _______, _______, XXXXXXX, XXXXXXX,              _______, XXXXXXX,          _______, _______
          //`---------------------------------------------|   |--------------------------------------------'
  ),

  [_NUM] = LAYOUT(
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
     KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MPRV, KC_PAUS, KC_MNXT, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      KC_TAB,   KC_P7,   KC_P8,   KC_P9, KC_PSLS, KC_PAST, XXXXXXX, KC_MPLY,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     KC_COLN,   KC_P4,   KC_P5,   KC_P6, KC_PMNS, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       KC_P0,   KC_P1,   KC_P2,   KC_P3, KC_PPLS, _______, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
               _______, _______, XXXXXXX, XXXXXXX,              XXXXXXX, _______,          KC_PDOT, XXXXXXX
          //`---------------------------------------------|   |--------------------------------------------'
  )
};

uint32_t keymaps_len() {
    return sizeof(keymaps) / sizeof(uint16_t);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool continue_process = process_record_user_bmp(keycode, record);
    bool result = false;
    if (continue_process == false) {
        return false;
    }

    switch (keycode) {
        default:
            result = true;
            break;
    }

    if (!twpair_on_jis(keycode, record)) {
        return false;
    }

    return result;
}

void matrix_init_user(void) {}

void matrix_scan_user(void) {}

void led_set_user(uint8_t usb_led) {}
