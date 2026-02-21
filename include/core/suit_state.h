#pragma once

#include <stdint.h>
#include <stdbool.h>

/*
 * Suit operating modes.
 * NOMINAL: normal operation
 * CAUTION: degraded but not immediately dangerous
 * WARNING: critical, immediate attention
 * FAULT: invalid sensor or serious failure 
 */
typedef enum {
    SUIT_MODE_NOMINAL = 0,
    SUIT_MODE_CAUTION = 1,
    SUIT_MODE_WARNING = 2,
    SUIT_MODE_FAULT   = 3,
} suit_mode_t;

/* Bitmask for active conditions */
typedef enum {
    SUIT_FLAG_NONE          = 0,       // 00000000
    SUIT_FLAG_TEMP_CAUTION  = 1u << 0, // 00000001
    SUIT_FLAG_TEMP_WARNING  = 1u << 1, // 00000010
    SUIT_FLAG_BATT_CAUTION  = 1u << 2, // 00000100
    SUIT_FLAG_BATT_WARNING  = 1u << 3, // 00001000
    SUIT_FLAG_SENSOR_FAULT  = 1u << 4, // 00010000
} suit_flags_t;

typedef struct {
    suit_mode_t mode;
    uint32_t flags;

    int32_t last_temp_c_x100;   /* temp in C x100 */
    int32_t last_batt_mv;       /* battery in mV */

    uint32_t mode_transitions;
    uint32_t fault_count;
} suit_state_t;

void suit_state_init(suit_state_t *s);

/*
 * Update functions: feed new readings into the state machine.
 * Return true if the mode changed.
 */
bool suit_state_update_temp(suit_state_t *s, int32_t temp_c_x100);
bool suit_state_update_batt(suit_state_t *s, int32_t batt_mv);

/* Accessors */
static inline suit_mode_t suit_state_mode(const suit_state_t *s) { return s->mode; }
static inline uint32_t suit_state_flags(const suit_state_t *s) { return s->flags; }