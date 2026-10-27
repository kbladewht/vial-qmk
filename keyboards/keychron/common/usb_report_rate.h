/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#include "quantum.h"

enum usb_report_rate_keycodes {
    KEY_RATE_1K = QK_KB_0,
    KEY_RATE_4K,
    KEY_RATE_8K,
    KEY_FN,
};

void report_rate_init(void);
uint8_t report_rate_get_div(void);
bool process_record_report_rate(uint16_t keycode, keyrecord_t *record);
