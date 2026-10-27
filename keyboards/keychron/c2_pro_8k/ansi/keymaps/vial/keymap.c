/* Copyright 2025 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "keychron_common.h"
#include "usb_report_rate.h"

enum layers {
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    WIN_FN,
};

void keyboard_post_init_user(void) {
    report_rate_init();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return process_record_report_rate(keycode, record);
}

#define LAYOUT_20( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, \
    K10, K11, K12, \
    K20, K21, K22, \
    K30, K31, K32, \
    K40, K41 \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08 }, \
    { K10, K11, K12, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { K20, K21, K22, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { K30, K31, K32, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { K40, K41, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO } \
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_20(
        KC_F7, KC_F2,  KC_F3,   KC_F6, KC_F1, KC_F5,   KC_F9, KC_O,  KC_F11,
                                KC_7,  KC_8,   KC_9,
                                KC_4,  KC_5,   KC_6,
                                KC_1,  KC_2,   KC_3,
                                    KC_0,  KEY_FN
    ),
    [1] = LAYOUT_20(
        QK_BOOT, XXXXXXX, XXXXXXX,  KEY_RATE_1K, KEY_RATE_4K, KEY_RATE_8K, XXXXXXX, XXXXXXX, XXXXXXX,
                                    XXXXXXX, XXXXXXX, XXXXXXX,
                                    XXXXXXX, XXXXXXX, XXXXXXX,
                                    XXXXXXX, XXXXXXX, XXXXXXX,
                                    XXXXXXX, XXXXXXX
    ),
};
extern void bootloader_jump(void);
#include "raw_hid.h"

void raw_hid_receive_kb(uint8_t *data, uint8_t length) {
    uint8_t *command_id = &(data[0]);
    //*command_id         = id_unhandled;

    // NRF_LOG_INFO("data[0] is 3 *************** %d",data[0]);
    switch (*command_id) {
        case 0x0B:
            raw_hid_send(data, length);
            bootloader_jump();
            break;

        default:
            break;
    }
}
