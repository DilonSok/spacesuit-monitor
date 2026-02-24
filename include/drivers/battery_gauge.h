#pragma once

#include <stdint.h>
#include <stdbool.h>

/*
 * Battery Gauge Driver Interface:
 * battery voltage in millivolts (mV)
 */

typedef struct {
    int32_t batt_mv;   /* battery voltage in mV */
    bool    valid;     /* false if reading is invalid */
} batt_sample_t;

int battery_gauge_init(void);
int battery_gauge_read(batt_sample_t *out);