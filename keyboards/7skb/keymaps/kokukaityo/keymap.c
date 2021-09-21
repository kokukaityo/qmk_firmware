#include QMK_KEYBOARD_H
#include "twpair_on_jis.h"

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
  _QWERTY = 0,
  _SYMBOL,
  _NUM,
  _ARROW,
  // _FN,
  // _ADJUST,
};

enum custom_keycodes {
  RGB_RST = SAFE_RANGE,

  CK_C_CAPS,      // 長押しCtrl, 単押しCapsLock
  CK_SPC_MHN,     // 長押しSpace, 単押し無変換

  // 長押しLayer, 単押しキー
  CK_SBL_SPC,
  CK_ARW_ENT,
};

// ショートカット
#define CK_ZKHK LALT(KC_GRV)  // 全角半角
#define sPAUSE LCA(KC_P)      // Ctrl+Alt+P     最前面でポーズ
#define sCAHOME LCA(KC_HOME)  // Ctrl+Alt+HOME  リモートの接続バーを表示

uint16_t hold_timers[MATRIX_ROWS][MATRIX_COLS];
//bool layer_pressed[4] = {false};
bool key_pressed[MATRIX_ROWS][MATRIX_COLS] = {false};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
  //,-----------------------------------------------------|   |--------------------------------------------------------------------------------.
      CK_ZKHK,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0, sCAHOME,  sPAUSE, XXXXXXX, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC, KC_RBRC, KC_JYEN,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------+--------|
    CK_C_CAPS,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------+--------|
               KC_LGUI, KC_LALT,CK_SPC_MHN, CK_SBL_SPC,      CK_ARW_ENT,MO(_NUM),          KC_RALT,  KC_APP 
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

// CapsLock　単押し
void set_caps(void) {
  register_code(KC_LSFT);
  register_code(KC_CAPS);
  unregister_code(KC_CAPS);
  unregister_code(KC_LSFT);
}

// 無変換　単押し
void set_mhen(void) {
  register_code(KC_MHEN);
  unregister_code(KC_MHEN);
};

// 押されていたかどうかの判定
bool is_pressed (keyrecord_t *record) {
  return key_pressed[record->event.key.row][record->event.key.col];
}
// 単押しかどうかの判定
bool is_tap (keyrecord_t *record) {
  return hold_timers[record->event.key.row][record->event.key.col]
  && timer_elapsed(hold_timers[record->event.key.row][record->event.key.col]) < TAPPING_TERM;
}

// 長押しと単押しでキーを変更する
void separate_tap_hold(keyrecord_t *record, uint8_t hold, void (*cb)(void)) {
  if (record->event.pressed) {
    // add_mods(MOD_BIT(hold));
    key_pressed[record->event.key.row][record->event.key.col] = true;
    register_code(hold);
  } else {
    unregister_code(hold);
    // if (is_tap(record)) {
    if (is_pressed(record)&& is_tap(record)) {
      cb();
    // } else {
    //   unregister_code(hold);
    }
    key_pressed[record->event.key.row][record->event.key.col] = false;
  }
}

// 長押しでレイヤー移動、単押しでキー入力
void my_LT(keyrecord_t *record, uint8_t layer, uint8_t tap) {
  if (record->event.pressed) {
    // layer_pressed[layer] = true;
    key_pressed[record->event.key.row][record->event.key.col] = true;
    layer_on(layer);
  } else {
    layer_off(layer);
    // if (layer_pressed[layer] && is_tap(record)) {
    if (is_pressed(record)&& is_tap(record)) {
      register_code(tap);
      unregister_code(tap);
    }
    // layer_pressed[layer] = false;
    key_pressed[record->event.key.row][record->event.key.col] = false;
  }
}


//A description for expressing the layer position in LED mode.
layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef RGBLIGHT_ENABLE
    switch (get_highest_layer(state)) {
    case _SYMBOL:
      rgblight_sethsv_at(HSV_BLUE, 0);
      break;
    case _NUM:
      rgblight_sethsv_at(HSV_RED, 0);
      break;
    case _ARROW:
      rgblight_sethsv_at(HSV_PURPLE, 0);
      break;
    default: //  for any other layers, or the default layer
      rgblight_sethsv_at( 0, 0, 0, 0);
      break;
    }
    rgblight_set_effect_range( 1, 4);
#endif
return state;
}

int RGB_current_mode;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool result = false;

  if (record->event.pressed) {
    hold_timers[record->event.key.row][record->event.key.col] = timer_read();
  }

  switch (keycode) {
    #ifdef RGBLIGHT_ENABLE
      case RGB_MOD:
          if (record->event.pressed) {
            rgblight_mode(RGB_current_mode);
            rgblight_step();
            RGB_current_mode = rgblight_config.mode;
          }
        break;
      case RGB_RST:
          if (record->event.pressed) {
            eeconfig_update_rgblight_default();
            rgblight_enable();
            RGB_current_mode = rgblight_config.mode;
          }
        break;
    #endif
    case CK_C_CAPS:     // 長押し"Ctrl", 単押し"CapsLock"
      separate_tap_hold(record, KC_LCTL, set_caps);
      result = false;
      break;
    case CK_SPC_MHN:    // 長押し"Space", 単押し"無変換"
      separate_tap_hold(record, KC_LCTL, set_mhen);
      result = false;
      break;
    case CK_SBL_SPC:    // 長押し"_SYMBOL"レイヤー, 単押し"Space"
      my_LT(record, _SYMBOL, KC_SPC);
      result = false;
      break;
    case CK_ARW_ENT:    // 長押し"_ARROW", 単押し"Enter"
      my_LT(record, _ARROW, KC_ENT);
      result = false;
      break;
    default:
      result = true;
      break;
  }

  if (!twpair_on_jis(keycode, record))
    return false;

  return result;
}
