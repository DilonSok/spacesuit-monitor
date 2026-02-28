#include "drivers/battery_gauge.h"
#include "app/app_config.h"

#include <stdlib.h>
#include <stdint.h>

static int32_t g_batt_mv = 4200;
static uint32_t g_reads = 0;

static int32_t clamp_i32(int32_t v, int32_t lo, int32_t hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

int battery_gauge_init(void) {
  g_batt_mv = 4200;
  g_reads = 0;
  return 0;
}

int battery_gauge_read(batt_sample_t *out) {
  if (!out) {
    return -1;
  }
  
  g_reads++;
  
  int drain = 5 + (rand() % 11); //simulate battery drain for random mV 5-15 each read 
  g_batt_mv -= drain;

  
  if ((rand() % 120) == 0) {
      g_batt_mv -= 120; // simulate sudden load/measurement glitch
  }

  // clamp to plausible range for simulation 
  // (best practice would be to record these and if it consistently happens it should handle accordingly
  g_batt_mv = clamp_i32(g_batt_mv, BATT_VALID_MIN_MV, BATT_VALID_MAX_MV);

  bool valid = true;
  if ((rand() % 250) == 0) { // simulate rare invalid reading/glitch
      valid = false;
  }

  out->batt_mv = g_batt_mv;
  out->valid = valid;
  return 0;
}