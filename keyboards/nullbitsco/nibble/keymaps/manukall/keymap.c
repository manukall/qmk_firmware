/* Copyright 2020 Jay Greco
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

#define _MA 0
#define _FN 1

enum custom_keycodes {
  A_UMLAUT = SAFE_RANGE, U_UMLAUT, O_UMLAUT, SHARP_S};

// relies on the keyboard layout variant to be altgr-intl
// (setxkbmap -layout "us" -variant "altgr-intl")

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_MA] = LAYOUT_ansi(
            KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_ESC,
    KC_MUTE, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,
    _______, MO(_FN), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP,
    _______, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN,
    _______, KC_LCTL, KC_LALT, KC_LGUI,                   KC_SPC,                    KC_RGUI, KC_RALT, KC_RCTL, KC_LEFT,          KC_DOWN, KC_RGHT
  ),
  [_FN] = LAYOUT_ansi(
               RESET,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, KC_HOME,  KC_INS,
    RGB_TOG, _______, KC_HOME, KC_END, _______, _______, _______, _______, U_UMLAUT, _______, O_UMLAUT, _______, _______, _______, _______, _______,
    _______, MO(_FN), A_UMLAUT, SHARP_S, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, _______, _______, _______,          _______,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_PGDN, KC_PGUP, _______, _______, _______,          _______, _______,
    _______, _______, _______, _______,                   _______,                   _______, _______, _______, _______,          _______, _______
  ),

};


// relies on the keyboard layout variant to be altgr-intl
// (setxkbmap -layout "us" -variant "altgr-intl")

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


// RGB config, for changing RGB settings on non-VIA firmwares
void change_RGB(bool clockwise) {
    bool shift = get_mods() & MOD_MASK_SHIFT;
    bool alt = get_mods() & MOD_MASK_ALT;
    bool ctrl = get_mods() & MOD_MASK_CTRL;

    if (clockwise) {
        if (alt) {
            rgblight_increase_hue();
        } else if (ctrl) {
            rgblight_increase_val();
        } else if (shift) {
            rgblight_increase_sat();
        } else {
            rgblight_step();
        }

  } else {
      if (alt) {
            rgblight_decrease_hue();
        } else if (ctrl) {
            rgblight_decrease_val();
        } else if (shift) {
            rgblight_decrease_sat();
        } else {
            rgblight_step_reverse();
        }
    } 
}

void encoder_update_kb(uint8_t index, bool clockwise) {
  if (layer_state_is(1)) {
    //change RGB settings
    change_RGB(clockwise);
  }
  else {
    if (clockwise) {
      tap_code(KC_VOLU);
  } else {
      tap_code(KC_VOLD);
    }  
  }
}

void matrix_init_user(void) {
  // Initialize remote keyboard, if connected (see readme)
  matrix_init_remote_kb();
}

void matrix_scan_user(void) {
  // Scan and parse keystrokes from remote keyboard, if connected (see readme)
  matrix_scan_remote_kb();
}


// jk as escape
const uint16_t PROGMEM escape_combo[] = {KC_F, KC_D, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {COMBO(escape_combo, KC_ESC)};


#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

static void render_ma(void) {
  static const char PROGMEM ma_image[] = {
    // 'pixil-frame-0', 128x32px
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
    0x80, 0xe0, 0xe0, 0xf8, 0xf8, 0xfe, 0xfe, 0xfe, 0xfe, 0x78, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x80, 0x80, 0xe0, 0xe0, 0xf8, 0xf8, 0xfe, 0xfe, 0xfe, 0xfe, 0x78, 0x78, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x80, 0x80, 0xe0, 0xe0, 0xf8, 0xf8, 0xfe, 0xfe, 0xfe, 0xfe, 0x78, 0x78, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x80, 0x80, 0xe0, 0xe0, 0xf8, 0xf8, 0xfe, 0xfe, 0xfe, 0xfe, 0x78, 0x78, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x80, 0x80, 0xe0, 0xe0, 0xf8, 0xf8, 0xfe, 0xfe, 0xfe, 0xfe, 0x78, 0x78, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xcc, 
    0xcc, 0xf3, 0xf3, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
    0x01, 0x07, 0x07, 0x1f, 0x1f, 0x7f, 0x7f, 0x7f, 0x7f, 0x1e, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x01, 0x01, 0x07, 0x07, 0x1f, 0x1f, 0x7f, 0x7f, 0x7f, 0x7f, 0x1e, 0x1e, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x01, 0x01, 0x07, 0x07, 0x1f, 0x1f, 0x7f, 0x7f, 0x7f, 0x7f, 0x1e, 0x1e, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x01, 0x01, 0x07, 0x07, 0x1f, 0x1f, 0x7f, 0x7f, 0x7f, 0x7f, 0x1e, 0x1e, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x01, 0x01, 0x07, 0x07, 0x1f, 0x1f, 0x7f, 0x7f, 0x7f, 0x7f, 0x1e, 0x1e, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x0c, 0x0c, 0x0c, 0xfc, 
    0xfc, 0x0c, 0x0c, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 
    0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  };

  oled_write_raw_P(ma_image, sizeof(ma_image));
}



static void render_fn(void) {
  static const char PROGMEM ma_image[] = {


    // 'pixil-frame-0', 128x32px
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 
    0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 
    0x7f, 0x1f, 0x1f, 0x07, 0x07, 0x01, 0x01, 0x01, 0x01, 0x87, 0x87, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0x7f, 0x7f, 0x1f, 0x1f, 0x07, 0x07, 0x01, 0x01, 0x01, 0x01, 0x87, 0x87, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0x7f, 0x7f, 0x1f, 0x1f, 0x07, 0x07, 0x01, 0x01, 0x01, 0x01, 0x87, 0x87, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0x7f, 0x7f, 0x1f, 0x1f, 0x07, 0x07, 0x01, 0x01, 0x01, 0x01, 0x87, 0x87, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0x7f, 0x7f, 0x1f, 0x1f, 0x07, 0x07, 0x01, 0x01, 0x01, 0x01, 0x87, 0x87, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xe0, 
    0xe0, 0xfe, 0xfe, 0x80, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 
    0xfe, 0xf8, 0xf8, 0xe0, 0xe0, 0x80, 0x80, 0x80, 0x80, 0xe1, 0xe1, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xfe, 0xfe, 0xf8, 0xf8, 0xe0, 0xe0, 0x80, 0x80, 0x80, 0x80, 0xe1, 0xe1, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xfe, 0xfe, 0xf8, 0xf8, 0xe0, 0xe0, 0x80, 0x80, 0x80, 0x80, 0xe1, 0xe1, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xfe, 0xfe, 0xf8, 0xf8, 0xe0, 0xe0, 0x80, 0x80, 0x80, 0x80, 0xe1, 0xe1, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xfe, 0xfe, 0xf8, 0xf8, 0xe0, 0xe0, 0x80, 0x80, 0x80, 0x80, 0xe1, 0xe1, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x79, 0x79, 0x79, 0x79, 0x19, 
    0x19, 0x61, 0x61, 0x79, 0x79, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 
    0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
  };

  oled_write_raw_P(ma_image, sizeof(ma_image));
}

void oled_task_user(void) {
    switch (get_highest_layer(layer_state)) {
        case _MA:
            /* oled_write_P(PSTR("Def\n"), false); */
            render_ma();
            break;
        case _FN:
            render_fn();
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

  /*   // Host Keyboard LED Status */
  /*   led_t led_state = host_keyboard_led_state(); */
  /*   oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false); */
  /*   oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false); */
  /*   oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false); */
}
#endif
