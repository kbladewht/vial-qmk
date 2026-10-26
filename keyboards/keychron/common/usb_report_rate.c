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
#include "usb_report_rate.h"

#include "keychron_raw_hid.h"
#include "raw_hid.h"
#include "state_notify.h"
#include "usb_endpoints.h"
#include "usb_main.h"

enum {
    REPORT_RATE_DIV_1K = 3,
    REPORT_RATE_DIV_4K = 1,
    REPORT_RATE_DIV_8K = 0,
};

static uint8_t report_rate_div = REPORT_RATE_DIV_1K;

void report_rate_update_interval(void) {
    extern void update_usb_report_interval(USBDriver *usbp, uint8_t interval);
    update_usb_report_interval(&USB_DRIVER, (0x01U << report_rate_div) - 1);
}

void report_rate_reset(void) {
    report_rate_div = REPORT_RATE_DIV_1K;
    report_rate_update_interval();
}

void report_rate_init(void) {
    report_rate_update_interval();
}

static bool report_rate_get(uint8_t *data) {
    data[1] = report_rate_div;
    data[2] = 0x7F;
    return true;
}

static bool report_rate_set(uint8_t *data, bool notify) {
    if (data[0] > 6) return false;

    report_rate_div = data[0];
    report_rate_update_interval();

#    ifdef STATE_NOTIFY_ENABLE
    if (notify) {
        usb_report_rate_notify(report_rate_div);
    }
#    endif
    (void)notify;

    return true;
}

void report_rate_hid_rx(uint8_t *data, uint8_t length) {
    uint8_t cmd     = data[1];
    bool    success = true;

    switch (cmd) {
        case REPORT_RATE_GET:
            success = report_rate_get(&data[2]);
            break;

        case REPORT_RATE_SET:
            success = report_rate_set(&data[2], false);
            break;

        default:
            data[0] = 0xFF;
            break;
    }

    data[2] = success ? 0 : 1;
}

bool process_record_report_rate(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KEY_RATE_1K:
            if (record->event.pressed) {
                uint8_t report_rate = REPORT_RATE_DIV_1K;
                report_rate_set(&report_rate, true);
            }
            return false;
        case KEY_RATE_4K:
            if (record->event.pressed) {
                uint8_t report_rate = REPORT_RATE_DIV_4K;
                report_rate_set(&report_rate, true);
            }
            return false;
        case KEY_RATE_8K:
            if (record->event.pressed) {
                uint8_t report_rate = REPORT_RATE_DIV_8K;
                report_rate_set(&report_rate, true);
            }
            return false;
        default:
            return true;
    }
}
