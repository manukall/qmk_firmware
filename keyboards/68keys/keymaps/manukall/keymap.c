#include QMK_KEYBOARD_H
#include "68keys.h"
#include <print.h>

enum custom_keycodes {
  A_UMLAUT = SAFE_RANGE,
  U_UMLAUT,
  O_UMLAUT,
  SHARP_S
};

// relies on the keyboard layout variant to be altgr-intl
// (setxkbmap -layout "us" -variant "altgr-intl")
)
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case A_UMLAUT:
      if (record->event.pressed) {
        SEND_STRING(SS_DOWN(X_RALT)"\""SS_UP(X_RALT)"a");
      }
      break;
    case U_UMLAUT:
      if (record->event.pressed) {
        // when keycode QMKURL is pressed
        SEND_STRING(SS_DOWN(X_RALT)"\""SS_UP(X_RALT)"u");
      }
      break;
    case O_UMLAUT:
      if (record->event.pressed) {
        // when keycode QMKURL is pressed
        SEND_STRING(SS_DOWN(X_RALT)"\""SS_UP(X_RALT)"o");
      }
      break;
    case SHARP_S:
      if (record->event.pressed) {
        // when keycode QMKURL is pressed
        SEND_STRING(SS_DOWN(X_RALT)"s"SS_UP(X_RALT));
      }
      break;
  }
  return true;
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_68_ansi(
        KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_ESC, KC_PGUP,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL, KC_PGDN,
        MO(1), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP,
        KC_LCTL, KC_LALT, KC_LGUI, KC_SPC, KC_RGUI, KC_RALT, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),
    [1] = LAYOUT_68_ansi(
        RESET, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, U_UMLAUT, KC_TRNS, O_UMLAUT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        MO(1), A_UMLAUT, SHARP_S, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_MPLY, KC_MSTP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLU,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPRV, KC_VOLD, KC_MNXT)
};

// jk as escape
const uint16_t PROGMEM test_combo[] = {KC_F, KC_D, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {COMBO(test_combo, KC_ESC)};
