#include <zephyr/device.h>
#include <zephyr/drivers/led_strip.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include <zmk/event_manager.h>
#include <zmk/events/hid_indicators_changed.h>
#include <dt-bindings/zmk/hid_usage.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#if !DT_HAS_CHOSEN(zmk_led_numlock)

#error "A zmk,led-numlock chosen node must be declared"

#endif

#define LED_NUMLOCK_CHOSEN DT_CHOSEN(zmk_led_numlock)

static const struct device *led_numlock;
static struct led_rgb pixel;

static int numlock_off(void) {
    if (!led_numlock)
        return -ENODEV;

    pixel = (struct led_rgb){.r = 0, .g = 0, .b = 0};
    led_strip_update_rgb(led_numlock, &pixel, 1);

    return 0;
}

static int numlock_on(void) {
    if (!led_numlock)
        return -ENODEV;

    pixel = (struct led_rgb){.r = 2, .g = 2, .b = 2};
    led_strip_update_rgb(led_numlock, &pixel, 1);

    return 0;
}

int numlock_status_event_handler(const zmk_event_t *eh) {
    struct zmk_hid_indicators_changed *ev = as_zmk_hid_indicators_changed(eh);
    if (ev == NULL) {
        return -ENOTSUP;
    }

    switch (ev->indicators) {
    case HID_USAGE_LED_UNDEFINED:
        numlock_on();
        break;
    case HID_USAGE_LED_NUM_LOCK:
        numlock_off();
        break;
    default:
        LOG_WRN("Unhandled indicators: %d", ev->indicators);
        return -EINVAL;
    }

    return 0;
}

ZMK_LISTENER(numlock_status, numlock_status_event_handler);
ZMK_SUBSCRIPTION(numlock_status, zmk_hid_indicators_changed);

static int zmk_hid_indicators_init(void) {
    led_numlock = DEVICE_DT_GET(LED_NUMLOCK_CHOSEN);
    numlock_on();
    return 0;
}

SYS_INIT(zmk_hid_indicators_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
