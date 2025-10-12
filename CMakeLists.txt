cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

set(CUSTOM_HEADERS)
set(CUSTOM_SOURCES)
add_subdirectory(src/custom)
add_subdirectory(src/customCPP)

project(SmartHome_EdgeDevice LANGUAGES C CXX)

target_sources(app PRIVATE src/main.c)
