cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(spacesuit_monitor)

target_include_directories(app PRIVATE include)

target_sources(app PRIVATE
  src/main.c
  src/app/app_init.c
  src/core/suit_state.c
  src/drivers/temp_sensor.c
  src/drivers/battery_gauge.c
)