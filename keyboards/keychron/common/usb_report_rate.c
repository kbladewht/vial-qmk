
#include "usb_report_rate.h"

#include "eeconfig.h"
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
    eeconfig_update_kb_datablock(&report_rate_div, 0, sizeof(report_rate_div));
    report_rate_update_interval();
}

void eeconfig_init_kb_datablock(void) {
    report_rate_div = REPORT_RATE_DIV_1K;
    eeconfig_update_kb_datablock(&report_rate_div, 0, sizeof(report_rate_div));
}

void report_rate_init(void) {
    eeconfig_read_kb_datablock(&report_rate_div, 0, sizeof(report_rate_div));
    if (report_rate_div > 6) {
        report_rate_div = REPORT_RATE_DIV_1K;
        eeconfig_update_kb_datablock(&report_rate_div, 0, sizeof(report_rate_div));
    }
    report_rate_update_interval();
}

static bool report_rate_set(uint8_t *data, bool notify) {
    if (data[0] > 6) return false;

    report_rate_div = data[0];
    eeconfig_update_kb_datablock(&report_rate_div, 0, sizeof(report_rate_div));
    report_rate_update_interval();

#    ifdef STATE_NOTIFY_ENABLE
    if (notify) {
        usb_report_rate_notify(report_rate_div);
    }
#    endif
    (void)notify;

    return true;
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
        case KEY_FN:
            if (record->event.pressed) {
                layer_on(1);
            } else {
                layer_off(1);
            }
            return false;
        default:
            return true;
    }
}
