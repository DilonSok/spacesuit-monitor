#pragma once

#include <stdint.h>

/*
 * Space Suit Monitor - Inter-task Messages
 *
 * Units:
 * - temperature: C x100 (e.g., 25.34°C -> 2534)
 * - battery: millivolts (mV)
 */

typedef enum {
    APP_MSG_TEMP_SAMPLE = 0,
    APP_MSG_BATT_SAMPLE = 1,
} app_msg_type_t;

typedef struct {
    app_msg_type_t type;
    int32_t value;
    uint32_t seq;
    uint32_t uptime_ms;
} app_msg_t;