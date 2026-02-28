#include "app/app_init.h"

#include "drivers/temp_sensor.h"
#include "drivers/battery_gauge.h"
#include "core/suit_state.h"

int app_init(app_ctx_t *ctx)
{
    if (!ctx) {
      return -1;
    }

    int rc = temp_sensor_init();
    if (rc != 0) {
      return rc;
    }

    rc = battery_gauge_init();
    if (rc != 0) {
      return rc;
    }

    suit_state_init(&ctx->suit);

    return 0;
}