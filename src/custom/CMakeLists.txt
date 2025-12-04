zephyr_include_directories(.)
add_library(custom_lib STATIC cgatt.c cadc.c callbacks.c cgpio.c cuart.c)
target_link_libraries(custom_lib PUBLIC zephyr_interface)
target_link_libraries(app PUBLIC custom_lib)