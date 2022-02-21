cmake_minimum_required(VERSION 3.13.1)

set(OVERLAY_CONFIG debug.conf rtt.conf)
list(APPEND BOARD_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND DTS_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(BOARD nrf52840_dummy)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
add_subdirectory(drivers)

project(zephyr_testrepo LANGUAGES C VERSION 0.0.1)

configure_file(app_version.h.in ${CMAKE_BINARY_DIR}/app/include/app_version.h)
target_include_directories(app PRIVATE ${CMAKE_BINARY_DIR}/app/include src)

target_sources(app PRIVATE src/main.c)
