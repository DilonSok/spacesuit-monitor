#include "drivers/temp_sensor.h"
#include "app/app_config.h"

#include <stdlib.h>
#include <stdint.h>

static int32_t g_temp_c_x100 = 2500;
static uint32_t g_reads = 0;

static int32_t clamp_i32(int32_t v, int32_t lo, int32_t hi)
{
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

int temp_sensor_init(void) {
  g_temp_c_x100 = 2500;
  g_reads = 0;
  return 0;
}

int temp_sensor_read(temp_sample_t *out) {
  if (!out) {
    return -1;
  }
  
  g_reads++;

  
  int step = (rand() % 61) - 30; // simulates taking a step and temp changing due to that random -0.30C/+0.30C
  g_temp_c_x100 += step;

  if ((rand() % 60) == 0) {
        g_temp_c_x100 += 1500; // simulate rare spike in temp
  }

  // clamp to plausible range for simulation 
  // (best practice would be to record these and if it consistently happens it should handle accordingly
  g_temp_c_x100 = clamp_i32(g_temp_c_x100, TEMP_VALID_MIN_C_X100, TEMP_VALID_MAX_C_X100);

  bool valid = true;
  if ((rand() % 250) == 0) { // simulate rare invalid reading/glitch
      valid = false;
  }

  out->temp_c_x100 = g_temp_c_x100;
  out->valid  = valid;
  return 0;
}