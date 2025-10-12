zephyr_include_directories(.)
add_library(custom_cpp_lib STATIC filter.cpp)
target_compile_options(custom_cpp_lib PRIVATE -std=c++17 -mcpu=cortex-m33 -mthumb -mfloat-abi=softfp -mabi=aapcs -mfpu=auto -mfloat-abi=softfp)
target_link_libraries(app PUBLIC custom_cpp_lib)