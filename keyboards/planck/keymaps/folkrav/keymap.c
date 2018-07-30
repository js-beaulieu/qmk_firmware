/* Copyright 2015-2017 Jack Humbert
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

#include "planck.h"
#include <print.h>
#include "action_layer.h"

extern keymap_config_t keymap_config;

// Layers configuration
enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  BACKLIT,
  ACCENTS,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* _QWERTY
    * ,-----------------------------------------------------------------------------------.
    * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | C/Esc|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |   '  |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Enter|
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Ctrl |  Fn  |  Alt |  OS  | Lower|    Space    | Raise|  OS  |  Alt |  Fn  | Ctrl |
    * `-----------------------------------------------------------------------------------'
    */
    [_QWERTY] = LAYOUT_planck_grid(
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
        CTL_T(KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_ENT,
        KC_LCTL, BACKLIT, KC_LALT, KC_LGUI, LOWER, KC_SPACE, KC_SPACE, RAISE, KC_RGUI, KC_RALT, BACKLIT, KC_RCTL),

    /* LOWER
    * ,-----------------------------------------------------------------------------------.
    * |   ~  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |      |      |   -  |   +  |   (  |   )  |  \   |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |  Cut | Copy | Paste|      |      |      |   [  |   ]  |   {  |   }  |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |             |      |      |      |      |      |
    * `-----------------------------------------------------------------------------------'()<>{}
    */
    [_LOWER] = LAYOUT_planck_grid(
        KC_TILD, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
        _______, _______, _______, _______, _______, _______, _______, KC_MINS, KC_PLUS, KC_LPRN, KC_RPRN, S(KC_NUBS),
        _______, _______, KC_CUT, KC_COPY, LSFT(KC_INS), _______, _______, _______, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),

    /* RAISE
    * ,-----------------------------------------------------------------------------------.
    * |   `  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   =  |  Ins |  Del |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |      | Left | Down |  Up  | Right|      |   |  |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |      |      |      |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |             |      |      |      |      |      |
    * `-----------------------------------------------------------------------------------'
    */
    [_RAISE] = LAYOUT_planck_grid(
        KC_GRV, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_EQL, KC_INS, KC_DEL,
        _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, _______, KC_PIPE,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),

    /* _ADJUST
    * ,-----------------------------------------------------------------------------------.
    * |      | RESET|      |      |      |      |      |      | F10  | F11  | F12  |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |      |      |      |  F7  |  F8  |  F9  |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |  WIN | macOS|      |  F4  |  F5  |  F6  |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |             |      |  F1  |  F2  |  F3  |      |
    * `-----------------------------------------------------------------------------------'
    */
    [_ADJUST] = LAYOUT_planck_grid(
        _______, RESET, _______, _______, _______, _______, _______, _______, KC_F10, KC_F11, KC_F11, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_F7, KC_F8, KC_F9, _______,
        _______, _______, _______, _______, _______, AG_NORM, AG_SWAP, _______, KC_F4, KC_F5, KC_F6, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_F1, KC_F2, KC_F3, _______),

};

// Toggle adjust layer when pressing both LOWER and RAISE
uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        #ifdef KEYBOARD_planck_rev5
          PORTE &= ~(1<<6);
        #endif
      } else {
        unregister_code(KC_RSFT);
        #ifdef KEYBOARD_planck_rev5
          PORTE |= (1<<6);
        #endif
      }
      return false;
      break;
  }
  return true;
}
