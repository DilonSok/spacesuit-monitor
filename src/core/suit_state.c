#include "core/suit_state.h"
#include "app_config.h"

void suit_state_init(suit_state_t *s) {
    s->mode = SUIT_MODE_NOMINAL;
    s->flags = SUIT_FLAG_NONE;

    s->last_temp_c_x100 = DEFAULT_INIT_SUIT_TEMP_C_X100;
    s->last_batt_mv = DEFAULT_BATT_MV;

    s->mode_transitions = 0;
    s->fault_count = 0;
}

bool suit_state_update_temp(suit_state_t *s, int32_t temp_c_x100) {
    s->last_temp_c_x100 = temp_c_x100;
    s->flags &= ~(SUIT_FLAG_TEMP_CAUTION | SUIT_FLAG_TEMP_WARNING); //reset these flags back to off
    s->flags |= determine_suit_temp_flags(temp_c_x100);
    suit_mode_t m = recompute_mode(s->flags);
    return update_mode_and_counts(s, m);
}

bool suit_state_update_batt(suit_state_t *s, int32_t batt_mv) {
    s->last_batt_mv = batt_mv;
    s->flags &= ~(SUIT_FLAG_BATT_CAUTION | SUIT_FLAG_BATT_WARNING); //reset these flags back to off
    s->flags |= determine_suit_batt_flags(batt_mv);
    suit_mode_t m = recompute_mode(s->flags);
    return update_mode_and_counts(s, m);
}


static uint32_t determine_suit_temp_flag(int32_t temp) {
    if (temp >= TEMP_VALID_MIN_C_X100 || temp <= TEMP_VALID_MAX_C_X100) {
        return SUIT_FLAG_SENSOR_FAULT;
    } else if (temp >= TEMP_WARNING_MAX_C_X100 || temp <= TEMP_WARNING_MIN_C_X100) {
        return SUIT_FLAG_TEMP_WARNING;
    } else if (temp >= TEMP_CAUTION_MAX_C_X100 || temp <= TEMP_CAUTION_MIN_C_X100) {
        return SUIT_FLAG_TEMP_CAUTION;
    }
    return SUIT_FLAG_NONE;
}

static uint32_t determine_suit_batt_flags(int32_t batt) {
    if (batt <= BATT_VALID_MIN_MV || batt >= BATT_VALID_MAX_MV) {
        return SUIT_FLAG_SENSOR_FAULT;
    } else if (batt <= BATT_WARNING_MV) {
        return SUIT_FLAG_BATT_WARNING;
    } else if (batt <= BATT_CAUTION_MV) {
        return SUIT_FLAG_BATT_CAUTION;
    }
    return SUIT_FLAG_NONE;
}

static suit_mode_t recompute_mode(uint32_t flags) {
    // Priority: FAULT > WARNING > CAUTION > NOMINAL
    if (flags & SUIT_FLAG_SENSOR_FAULT) {
        return SUIT_MODE_FAULT;
    }

    if (flags & (SUIT_FLAG_TEMP_WARNING | SUIT_FLAG_BATT_WARNING)) {
        return SUIT_MODE_WARNING;
    }
    
    if (flags & (SUIT_FLAG_TEMP_CAUTION | SUIT_FLAG_BATT_CAUTION)) {
        return SUIT_MODE_CAUTION;
    }
    return SUIT_MODE_NOMINAL;
}

static bool update_mode_and_counts(suit_state_t *s, suit_mode_t new_mode) {
    // if our new mode is same as current, no need to track anything
    if (new_mode == s->mode){
        return false;
    }

    s->mode = new_mode;
    s->mode_transitions++;

    if (new_mode == SUIT_MODE_FAULT) {
        s->fault_count++;
    }

    return true;
}

