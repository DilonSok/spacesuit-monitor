#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#include <stdlib.h>

#include "drivers/temp_sensor.h"
#include "drivers/battery_gauge.h"
#include "core/suit_state.h"

static const char *mode_str(suit_mode_t m)
{
    switch (m) {
    case SUIT_MODE_NOMINAL: return "NOMINAL";
    case SUIT_MODE_CAUTION: return "CAUTION";
    case SUIT_MODE_WARNING: return "WARNING";
    case SUIT_MODE_FAULT:   return "FAULT";
    default:                return "UNKNOWN";
    }
}

int main(void)
{
    printk("Space Suit Monitor v0 - drivers + state machine\n");
    
    srand((unsigned)k_uptime_get_32()); // for seeding rand with uptime to vary behavior each run

    temp_sensor_init();
    battery_gauge_init();

    suit_state_t suit;
    suit_state_init(&suit);

    while (1) {
        temp_sample_t t;
        batt_sample_t b;

        temp_sensor_read(&t);
        battery_gauge_read(&b);

        // if invalid, push out of range to trigger a fault via suit state logic
        if (!t.valid) {
            suit_state_update_temp(&suit, 999999);
        } else {
            suit_state_update_temp(&suit, t.temp_c_x100);
        }

        if (!b.valid) {
            suit_state_update_batt(&suit, -1);
        } else {
            suit_state_update_batt(&suit, b.batt_mv);
        }

        printk("mode=%s temp=%d.%02dC batt=%dmV transitions=%u faults=%u flags=0x%08x\n",
               mode_str(suit.mode),
               suit.last_temp_c_x100 / 100, abs(suit.last_temp_c_x100 % 100),
               suit.last_batt_mv,
               suit.mode_transitions,
               suit.fault_count,
               suit.flags);

        k_sleep(K_MSEC(1000));
    }

    return 0;
}