#pragma once

#include <stdint.h>
#include <stdbool.h>

/*
 * Temperature Sensor Driver Interface:
 * temperature is returned as C x100 (e.g., 25.34°C -> 2534)
 */

typedef struct {
    int32_t temp_c_x100;   /* temperature in C x100 */
    bool    valid;         /* false if reading is invalid */
} temp_sample_t;

int temp_sensor_init(void);
int temp_sensor_read(temp_sample_t *out);