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
  _COLEMAK,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  BACKLIT,
  ACCENTS,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define TMUX_PREFIX LCTL(KC_SPACE)
#define ___X___ KC_NO
#define SELECT_LEFT LSFT(LALT(KC_LEFT))
#define SELECT_RIGHT LSFT(LALT(KC_RIGHT))
#define SELECT_UP LSFT(KC_UP)
#define SELECT_DOWN LSFT(KC_DOWN)
#define SELECT_HOME LSFT(KC_HOME)
#define SELECT_END LSFT(KC_END)

// Tap dance
enum {
  TD_LSHIFT_CAPS = 0,
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_LSHIFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
};

// Util
void flash_backlight(int count) {
  for (int i = 0; i < count; i++) {
    backlight_toggle();
    if (i == 0) {
      wait_ms(100);
    } else {
      wait_ms(250);
    }
    backlight_toggle();

    if (i != count - 1) {
      wait_ms(250);
    }

  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* _QWERTY
    * ,-----------------------------------------------------------------------------------.
    * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | C/Esc|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |   '  |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | S/Ent|
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Ctrl |  OS  |  Alt |      | Lower|    Space    | Raise|      |      | Tmux | Ctrl |
    * `-----------------------------------------------------------------------------------'
    */
    [_QWERTY] = LAYOUT_planck_grid(
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
        CTL_T(KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, RSFT_T(KC_ENT),
        KC_LCTL, KC_LGUI, KC_LALT, ___X___, LOWER, KC_SPACE, KC_SPACE, RAISE, ___X___, ___X___, TMUX_PREFIX, KC_RCTL),

    /* Colemak
    * ,-----------------------------------------------------------------------------------.
    * |  Tab |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
    * |------+------+------+------+------+-------------+------+------+------+------+------|
    * | C/Esc|   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |   '  |
    * |------+------+------+------+------+------|------+------+------+------+------+------|
    * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  | S/Ent|
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Ctrl |  OS  | Alt  |      |Lower |    Space    |Raise |      |      | Tmux | Ctrl |
    * `-----------------------------------------------------------------------------------'
    */
    [_COLEMAK] = LAYOUT_planck_grid(
        KC_TAB, KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_BSPC,
        CTL_T(KC_ESC), KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E, KC_I, KC_O, KC_QUOT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_K, KC_M, KC_COMM, KC_DOT, KC_SLSH, RSFT_T(KC_ENT),
        KC_LCTL, KC_LGUI, KC_LALT, ___X___, LOWER, KC_SPACE, KC_SPACE, RAISE, ___X___, ___X___, TMUX_PREFIX, KC_RCTL),

    /* LOWER
    * ,-----------------------------------------------------------------------------------.
    * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |   -  |   +  |   (  |   )  |      |      |      |      |      |      |   \  |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |   [  |   ]  |   {  |   }  |      |      |      |   <  |   >  |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |             |      |      |      |      |      |
    * `-----------------------------------------------------------------------------------'
    */
    [_LOWER] = LAYOUT_planck_grid(
        KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
        _______, KC_MINS, KC_PLUS, KC_LPRN, KC_RPRN, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, KC_BSLS,
        _______, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, ___X___, ___X___, ___X___, KC_LABK, KC_RABK, ___X___, _______,
        _______, _______, _______, ___X___, _______, _______, _______, _______, ___X___, ___X___, ___X___, _______),

    /* RAISE
    * ,-----------------------------------------------------------------------------------.
    * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   _  |   =  | Bksp |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      | Home | Left | Down |  Up  | Right|  End |   |  |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |      |      |      |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |             |      |      |      |      |  Del |
    * `-----------------------------------------------------------------------------------'
    */
    [_RAISE] = LAYOUT_planck_grid(
        KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_UNDS, KC_EQL, KC_BSPC,
        _______, _______, _______, _______, _______, KC_HOME, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_END, KC_PIPE,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL),

    /* _ADJUST
    * ,-----------------------------------------------------------------------------------.
    * |  F10 |  F11 |  F12 |      |      |      |      |      |      |      |      | Reset|
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |  F7  |  F8  |  F9  |      |Qwerty| sHome| sLeft| sDown|  sUp |sRight| sEnd |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |  F4  |  F5  |  F6  |      |Colemk|  Win | macOS|      |      |Vol Dn|Vol Up| Mute |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |  F1  |  F2  |  F3  |      |      |  Brightness |      |      |Prev | Next | Pl/Pa|
    * `-----------------------------------------------------------------------------------'
    */
    [_ADJUST] = LAYOUT_planck_grid(
        KC_F10, KC_F11, KC_F12, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, ___X___, RESET,
        KC_F7, KC_F7, KC_F9, ___X___, QWERTY, SELECT_HOME, SELECT_LEFT, SELECT_DOWN, SELECT_UP, SELECT_RIGHT, SELECT_END, ___X___,
        KC_F4, KC_F5, KC_F6, ___X___, COLEMAK, AG_NORM, AG_SWAP, ___X___, ___X___, KC_VOLD, KC_VOLU, KC_MUTE,
        KC_F1, KC_F2, KC_F3, _______, _______, BL_STEP, BL_STEP, _______, ___X___, KC_MEDIA_PREV_TRACK, KC_MEDIA_NEXT_TRACK, KC_MEDIA_PLAY_PAUSE),

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

    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
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

    case AG_NORM:
      if (record->event.pressed) {
        print("mode just switched to win/linux\n");
        #ifdef BACKLIGHT_ENABLE
          flash_backlight(2);
        #endif
      }
      return true;
      break;

    case AG_SWAP:
      if (record->event.pressed) {
        print("mode just switched to macos\n");
        #ifdef BACKLIGHT_ENABLE
          flash_backlight(3);
        #endif
      }
      return true;
      break;

  }
  return true;
}
