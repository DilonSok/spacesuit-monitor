#pragma once

/*
 * Space Suit Monitor - Configuration
 *
 * - sampling rates
 * - thresholds
 * - RTOS sizing (stacks, queue depth)
 * - thread priorities
 *
 */

/* -----------------------------
 * Timing (milliseconds)
 * ----------------------------- */
#define TEMP_SAMPLE_PERIOD_MS     1000   /* sample temperature every 1s */
#define BATT_SAMPLE_PERIOD_MS     2000   /* sample battery every 2s */
#define TELEMETRY_PERIOD_MS       2000   /* print telemetry every 2s */

/* -----------------------------
 * Thresholds
 * temp is stored as "C x100" (e.g., 25.34°C => 2534)
 * battery is stored in millivolts (mV)
 * ----------------------------- */


#define TEMP_CAUTION_MIN_C_X100     1500   /* 15.00°C */
#define TEMP_CAUTION_MAX_C_X100     4500   /* 45.00°C */
#define TEMP_WARNING_MIN_C_X100     500   /* 5.00°C */
#define TEMP_WARNING_MAX_C_X100     5500   /* 55.00°C */
#define TEMP_VALID_MIN_C_X100      -2000   /* -20.00°C */
#define TEMP_VALID_MAX_C_X100       8000   /* 80.00°C */

#define BATT_CAUTION_MV           3600   /* 3.60V */
#define BATT_WARNING_MV           3400   /* 3.40V */
#define BATT_VALID_MIN_MV         3000
#define BATT_VALID_MAX_MV         4300

/* -----------------------------
 * RTOS / IPC sizing
 * ----------------------------- */
#define APP_MSGQ_DEPTH              16   /* number of messages buffered */

/* Thread stacks (bytes)*/
#define SENSOR_THREAD_STACK_SZ    1024
#define HEALTH_THREAD_STACK_SZ    1024
#define TELEMETRY_THREAD_STACK_SZ 1024

/* Thread priorities  */
#define SENSOR_THREAD_PRIO           5
#define HEALTH_THREAD_PRIO           4 
#define TELEMETRY_THREAD_PRIO        6

/* -----------------------------
 * tbd
 * ----------------------------- */
/* #define O2_SAMPLE_PERIOD_MS      500 */
/* #define O2_WARNING_PCT           195 */ /* example: 19.5% O2 (scaled) */


/* -----------------------------
 * Default Init Values
 * ----------------------------- */
#define DEFAULT_INIT_SUIT_TEMP_C_X100 2500 /* 25.00°C */
#define DEFAULT_BATT_MV               4200 /* 4.2V */