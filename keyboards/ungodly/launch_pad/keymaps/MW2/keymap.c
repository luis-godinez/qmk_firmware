/* Copyright 2020 Ungodly Design <hello@ungodly.design>
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
#include "analog.h"
#include "qmk_midi.h"

/* Force Numlock on */
void matrix_init_user (void) {
  if (!host_keyboard_led_state().num_lock) {
      tap_code(KC_NUMLOCK);
  }
}

// Advanced Tap Dance

// Keycode declarations
enum {
    ALT_L1_TOGGLE,
    NUMLOCK_L1_TOGGLE,
    TD_4_6,
    TD_3_5,
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [ALT_L1_TOGGLE] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_LALT, 1),
    [NUMLOCK_L1_TOGGLE] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_NUMLOCK, 1),
    [TD_4_6] = ACTION_TAP_DANCE_DOUBLE(KC_4, KC_6),
    [TD_3_5] = ACTION_TAP_DANCE_DOUBLE(KC_3, KC_5),
};

// LCTL(LALT(KC_TAB))

// Layers

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: (Base Layer) Default Numpad Layer
  * ,-------------------.
  * | NV | /  | *  |BK/FN|
  * |----|----|----|-----|
  * | 7  | 8  | 9  |  -  |
  * |----|----|----|-----|
  * | 4  | 5  | 6  |  +  |
  * |----|----|----|-----|
  * | 1  | 2  | 3  | En  |
  * |----|----|----|-----|
  * | 0  | 0  | .  | En  |
  * `--------------------'
  */
  [0] = LAYOUT_ortho_5x4(
   TD(NUMLOCK_L1_TOGGLE),  KC_PSLS,  KC_PAST, LT(2, KC_BSPC),
   KC_P7,    KC_P8,    KC_P9,        KC_PMNS,
   KC_P4,    KC_P5,    KC_P6,        KC_PPLS,
   KC_P1,    KC_P2,    KC_P3,        KC_PENT,
   KC_P0,    KC_P0,  KC_PDOT,        KC_PENT
  ),
  /* Keymap _WAR: (Warzone Layer) Default Numpad Layer for COD Warzone N00BS
  * ,-------------------.
  * | R  | F  | V  | Spc |
  * |----|----|----|-----|
  * | E  | D  | C  | Alt |
  * |----|----|----|-----|
  * | W  | S  | X  |  4  |
  * |----|----|----|-----|
  * | Q  | A  | Z  |  3  |
  * |----|----|----|-----|
  * | Esc|Ctrl|Shift| M |
  * `--------------------'
  */
  [1] = LAYOUT_ortho_5x4(
    KC_R,    KC_F,    KC_V,     KC_SPACE,
    KC_E,    KC_D,    KC_C,     TD(ALT_L1_TOGGLE),
    KC_W,    KC_S,    KC_X,     TD(TD_4_6),
    KC_Q,    KC_A,    KC_Z,     TD(TD_3_5),
    KC_ESC, KC_LCTRL, KC_LSHIFT, KC_M
  ),
  /* Keymap _FN: RGB Function Layer
   * ,-------------------.
   * |LAYR|    |    |RTOG|
   * |----|----|----|----|
   * |HUD |HUI |    |RGBP|
   * |----|----|----|----|
   * |SAD |SAI |    |RMOD|
   * |----|----|----|----|
   * |VAD |VAS |    |    |
   * |----|----|----|----|
   * |RST |RST |    |    |
   * `-------------------'
   */
    [2] = LAYOUT_ortho_5x4(
      XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,
      RGB_HUD,  RGB_HUI,  XXXXXXX,   RGB_TOG,
      RGB_SAD,  RGB_SAI,  XXXXXXX,   RGB_M_P,
      RGB_VAD,  RGB_VAI,  XXXXXXX,   RGB_MOD,
        RESET,    RESET,  XXXXXXX,   XXXXXXX
  ),
};

// (Optional) Rotary Encoder, Volume Control
bool encoder_update_user(uint8_t index, bool clockwise) {
  if (clockwise) {
      tap_code(KC_VOLU);
  } else {
      tap_code(KC_VOLD);
  }
  return true;
}

// Potentiometer Slider, MIDI Control
uint8_t divisor = 0;
void slider(void){
  if (divisor++) { // only run the slider function 1/256 times it's called
      return;
  }
  midi_send_cc(&midi_device, 2, 0x3E, 0x7F - (analogReadPin(SLIDER_PIN) >> 3));
}

void matrix_scan_user(void) {
  slider();
}

// 0.91" OLED, 128x32 resolution
#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

static void render_rocket_logo(void) {
  static const char PROGMEM rocket_logo[]={
    // Rocket Screen
    // 'home', 128x32px
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
    0x80, 0x80, 0xc0, 0x40, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd0, 0x20, 0x50, 0x50, 0x90,
    0x10, 0x10, 0x20, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x40, 0x40, 0x40, 0x40, 0x20, 0x10, 0x10, 0xf0, 0x10, 0x10, 0x08, 0x08, 0x08, 0x04, 0x04,
    0x04, 0xfc, 0xfc, 0xfc, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0xfc, 0x7c, 0x7e, 0x7e, 0x7f,
    0x81, 0x81, 0x81, 0x81, 0xff, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xff,
    0xff, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0x01, 0x01, 0x01, 0xf9, 0x01, 0xf9, 0x01,
    0xf9, 0x01, 0xf9, 0x01, 0x01, 0x01, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe6,
    0xe6, 0xe6, 0xe6, 0xe6, 0xff, 0x8c, 0x52, 0x52, 0x52, 0xde, 0x84, 0x08, 0x84, 0x08, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x04, 0x04,
    0x05, 0x05, 0x02, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x01, 0x01, 0x01, 0x01, 0x02, 0x04, 0x04, 0x07, 0x04, 0x04, 0x08, 0x08, 0x08, 0x10, 0x10,
    0x10, 0x1f, 0x1f, 0x1f, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1f, 0x10, 0x20, 0x20, 0x40,
    0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x7f,
    0x7f, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x40, 0x40, 0x40, 0x4a, 0x44, 0x4a, 0x40,
    0x4f, 0x40, 0x4f, 0x40, 0x40, 0x40, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x5c, 0x9c,
    0x9c, 0x9c, 0x9c, 0x1c, 0xff, 0x31, 0x4a, 0x4a, 0x4a, 0x7b, 0x10, 0x21, 0x10, 0x21, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  };
  oled_write_raw_P(rocket_logo, sizeof(rocket_logo));
}
static void render_warzone_logo(void) {
  static const char PROGMEM warzone_logo[]={
    // Home Screen
    // 'warzone_bit', 128x32px
    0x00, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xe0, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0x00, 0xe0, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x3f, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfe,
    0xfc, 0xf0, 0x00, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0x7f, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x80, 0x00, 0x00, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xc0, 0xc0, 0xc0,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xf8, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xe0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0xf8, 0xfe, 0xff, 0xff, 0xff, 0x7f, 0x1f,
    0x07, 0x01, 0x00, 0x00, 0x00, 0x03, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xf0, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x1f, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xff,
    0xff, 0x00, 0xfc, 0xff, 0xff, 0xff, 0xff, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0x00, 0x80, 0xe0, 0xf8, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x07, 0x01, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0x03, 0x03, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xfe, 0xff,
    0xff, 0xff, 0xff, 0xff, 0x03, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
    0x00, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x00,
    0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x00, 0x00, 0x01, 0x0f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f,
    0x00, 0x03, 0x1f, 0x3f, 0x3f, 0x7f, 0x7f, 0x7f, 0x7e, 0x7e, 0x7e, 0x7f, 0x7f, 0x7f, 0x3f, 0x3f,
    0x1f, 0x07, 0x00, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f,
    0x7f, 0x7f, 0x7f, 0x00, 0x00, 0x1f, 0x3f, 0x3f, 0x7f, 0x7f, 0x7f, 0x7e, 0x7e, 0x7e, 0x7f, 0x7f,
    0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x00, 0x00, 0x00, 0x01, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f,
    0x7f, 0x7f, 0x7f, 0x00, 0x00, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x00, 0x00, 0x07, 0x7f, 0x7f,
    0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x00, 0x00, 0x0f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7e, 0x00
  };
  oled_write_raw_P(warzone_logo, sizeof(warzone_logo));
}
static void render_light_logo(void) {
  static const char PROGMEM light_logo[]={
    // RGB Screen
    // 'rgb', 128x32px
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x9c, 0x80, 0x80,
    0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80,
    0x80, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd0, 0x20, 0x50, 0x50, 0x90,
    0x10, 0x10, 0x20, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x80, 0x80, 0x00, 0x00, 0xe0, 0x19, 0x04, 0x62, 0x11, 0x09, 0x04, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x01, 0x01, 0x02, 0x04, 0x19, 0x10, 0x10, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0xf0, 0xe0, 0xc0,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc7, 0x24, 0x04,
    0x07, 0xe4, 0x24, 0x24, 0xc7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x04, 0x04,
    0x05, 0x05, 0x02, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x88, 0x30, 0x40, 0x40, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x80, 0x40, 0x60, 0x30, 0x98, 0x08, 0x08, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x0f, 0x07, 0x03,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc1, 0x22, 0x24,
    0x24, 0xc4, 0x44, 0x22, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x1d, 0x01, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x02, 0x02,
    0x02, 0x03, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  };
  oled_write_raw_P(light_logo, sizeof(light_logo));
}

void oled_task_user(void) {
  switch (get_highest_layer(layer_state)) {
    case 0:
      render_rocket_logo();
      break;
    case 1:
      render_warzone_logo();
      break;
    case 2:
      render_light_logo();
      break;
    default:
      // Or use the write_ln shortcut over adding '\n' to the end of your string
      oled_write_ln_P(PSTR(" UND"), false);
      break;
    }
}
#endif
