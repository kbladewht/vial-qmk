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

enum layers {
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    WIN_FN,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = {
        {KC_F7, KC_F2,  KC_F3,  KC_F6,  KC_F1,  KC_F5,  KC_F9,  KC_0,   KC_F11},
        {KC_7,  KC_8,   KC_9,   KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO },
        {KC_4,  KC_5,   KC_6,   KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO },
        {KC_1,  KC_2,   KC_3,   KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO },
        {KC_0,  KC_DEL, KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO },
    },
    [1] = {
        {KC_ESC,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO   },
        {KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8   },
        {KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO   },
        {KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO   },
        {KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO   },
    },
};
extern void bootloader_jump(void);
#include "raw_hid.h"
// Keyboard level code can override this to handle custom messages from VIA.
// See raw_hid_receive() implementation.
// DO NOT call raw_hid_send() in the override function.
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


// extern void bootloader_jump_new(void);

// void qf_bootloader_jump(void) {
//     bootloader_jump_new();
// }
