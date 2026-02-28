#pragma once

#include "core/suit_state.h"

/*
 * App initialization:
 * - initializes drivers
 * - initializes suit state
 * - initializes queues + starts tasks
 */

typedef struct {
    suit_state_t suit;
} app_ctx_t;

int app_init(app_ctx_t *ctx);